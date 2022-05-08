cmake_minimum_required(VERSION VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)

set(MAINTARGET "${PROJECT_NAME}")
set(MAINTARGET "${MAINTARGET}" PARENT_SCOPE)

message("TARGET=${MAINTARGET}")

set(SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/HardwareService.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/exceptions/GenericException.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/Hardware.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/IndexItem.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/Sensor.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/SensorValue.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/HwStatus.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/SmartAttribute.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/NvmeSmart.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/models/Metadata.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/SensorsDataLoader.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/SensorsParser.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/Converters.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/DataLoader.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/HwStatusLoader.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/HwStatusParser.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/HardwareTreeLoader.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/data/HardwareTreeParser.cpp"
        )

set_property(GLOBAL PROPERTY LHWSERVICE_SOURCEFILES ${SOURCE_FILES})

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

if (BUILD_SHARED_LIBS)
    add_library(${MAINTARGET} SHARED ${SOURCE_FILES})
else ()
    add_library(${MAINTARGET} STATIC ${SOURCE_FILES})
endif ()

target_compile_features(${MAINTARGET} PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
target_compile_definitions(${MAINTARGET} PRIVATE "$<$<CONFIG:Debug>:DEBUGBUILD>")
set_property(TARGET ${MAINTARGET} PROPERTY DEBUG_POSTFIX -d)

message("C++ Compiler (${CMAKE_CXX_COMPILER_ID}) ${CMAKE_CXX_COMPILER}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    message("Compiler is MSVC")
    if (BUILD_SHARED_LIBS)
        target_compile_options(${MAINTARGET} PRIVATE /W4 /WX /EHs /fp:fast)
    else ()
        target_compile_options(${MAINTARGET} PRIVATE /W4 /WX /EHs /fp:fast "$<$<CONFIG:Release>:/MD>" "$<$<CONFIG:Debug>:/MDd>")
        target_compile_definitions(${MAINTARGET} PRIVATE _Boost_USE_STATIC_LIBS BOOST_ALL_NO_LIB)
        set_property(TARGET ${MAINTARGET} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif ()
else ()
    message("UNSUPPORTED COMPILER")
endif ()

set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_WARN_NEW_VERSIONS ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
message("VCPKG_TARGET_TRIPLET=${VCPKG_TARGET_TRIPLET}")
message("CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

find_package(Boost 1.79.0 REQUIRED COMPONENTS thread json)

set(MSGPACK_CXX17 ON)
set(MSGPACK_USE_X3_PARSE ON)
set(MSGPACK_USE_STATIC_BOOST ON)
find_package(msgpack 3.3.0 CONFIG REQUIRED)

set_property(GLOBAL APPEND PROPERTY LHWSERVICE_PRIV_INCLUDEDIRS "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
set_property(GLOBAL APPEND PROPERTY LHWSERVICE_PRIV_INCLUDEDIRS "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>")
set_property(GLOBAL APPEND PROPERTY LHWSERVICE_PUB_INCLUDEDIR "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>")

target_include_directories(${MAINTARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${Boost_INCLUDE_DIR}"
        #when the library part of another source tree
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        #when external projects search for the library
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set(CPACK_GENERATOR ZIP)
include(CPack)