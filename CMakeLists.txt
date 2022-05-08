cmake_minimum_required(VERSION 3.21)

enable_language(CXX)
set(PROJECT_NAME "lhwservice")
set(PROJECT_VERSION 0.2.0)
set(PROJECT_DESCRIPTION "Library to retrieve sensors data from LibreHardwareService")
set(PROJECT_HOMEPAGE_URL "https://github.com/epinter/lhwservice")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(src)
if (NOT PROJECT_IS_TOP_LEVEL)
    set(LHWSERVICE_SOURCEFILES ${LHWSERVICE_SOURCEFILES} PARENT_SCOPE)
endif ()

if (PROJECT_IS_TOP_LEVEL)
    message("Configuring CMAKE_INSTALL_PREFIX to ${CMAKE_CURRENT_SOURCE_DIR}/install")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "Installation directory" FORCE)
    message("CMAKE_INSTALL_PREFIX = ${CMAKE_CURRENT_SOURCE_DIR}/install")

    include(GNUInstallDirs)

    install(TARGETS ${MAINTARGET}
            EXPORT ${PROJECT_NAME}Targets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            )
    install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}" FILES_MATCHING PATTERN *.h)

    #export file
    install(EXPORT "${PROJECT_NAME}Targets"
            FILE "${PROJECT_NAME}Targets.cmake"
            DESTINATION cmake
            )

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            VERSION "${version}"
            COMPATIBILITY AnyNewerVersion
    )

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            INSTALL_DESTINATION cmake
            )

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            DESTINATION cmake
            )

    export(EXPORT "${PROJECT_NAME}Targets"
            FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake")

    target_include_directories(${MAINTARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${Boost_INCLUDE_DIR}"
            #when the library part of another source tree
            PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
            #when external projects search for the library
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
endif ()