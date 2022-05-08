// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 14/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <boost/json/value.hpp>
#include <boost/json/value_to.hpp>
#include "models/IndexItem.h"
#include "models/Sensor.h"
#include "models/HwStatus.h"
#include "models/SmartAttribute.h"
#include "models/NvmeSmart.h"
#include "models/Hardware.h"
#include <msgpack.hpp>

namespace lhws {
    class Converters {
    public:
        template<typename T>
        T fromJson(boost::json::value const &jv);

        static std::vector<IndexItem> indexFromJson(std::string const &document);

        static Sensor sensorFromJson(std::string const &document);

        static HwStatus hwStatusFromJson(const std::vector<char> &data);

        static void hwStatusDataFromJson(std::vector<SmartAttribute> &attributes, HwStatus &s);

        static void hwStatusDataFromJson(NvmeSmart &nvmeSmart, HwStatus &s);

        static std::vector<Hardware> hardwareTreeFromJson(const std::string &document);
    };

    template<class T>
    [[maybe_unused]]
    T tag_invoke(boost::json::value_to_tag<T>, boost::json::value const &jv) {
        Converters c;
        T obj = c.fromJson<T>(jv);
        return obj;
    }

    template<typename T, template<typename...> class C>
    [[maybe_unused]]
    C<T> tag_invoke(boost::json::value_to_tag<C<T>>, boost::json::value const &jv) {
        boost::json::array ja = jv.as_array();
        C<T> ret;
        for (auto jvi: ja) {
            Converters c;
            T d = c.fromJson<T>(jvi);

            ret.push_back(d);
        }
        return ret;
    }
}

namespace msgpack::v1::adaptor {
    template<>
    struct [[maybe_unused]] convert<lhws::IndexItem> {
        msgpack::object const &operator()(msgpack::object const &o, lhws::IndexItem &v) const {
            if (o.type != msgpack::type::ARRAY) throw msgpack::type_error();
            if (o.via.array.size != 6) throw msgpack::type_error();

            v = lhws::IndexItem(
                    o.via.array.ptr[0].as<std::string>(), //identifier
                    o.via.array.ptr[1].as<int>(), //offset
                    o.via.array.ptr[2].as<int>(), //size
                    o.via.array.ptr[3].as<std::string>(), //sensorName
                    o.via.array.ptr[4].as<std::string>(), //sensorType
                    o.via.array.ptr[5].as<std::string>() //hardwareName
            );
            return o;
        }
    };
}
