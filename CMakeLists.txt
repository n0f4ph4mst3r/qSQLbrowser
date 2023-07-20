cmake_minimum_required(VERSION 3.26.0)

if(NOT DEFINED ${CMAKE_TOOLCHAIN_FILE})
	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif()

set(VCPKG_OVERLAY_TRIPLETS ${CMAKE_CURRENT_SOURCE_DIR}/triplets)
if (WIN32)
	set(VCPKG_TARGET_TRIPLET x64-windows-mixed)
	set(VCPKG_HOST_TRIPLET x64-windows-mixed)
elseif (UNIX)
	set(VCPKG_HOST_TRIPLET x64-linux-mixed)
	set(VCPKG_TARGET_TRIPLET x64-linux-mixed)
endif()

project(qSQLbrowser)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
qt_standard_project_setup()

if(CMAKE_GENERATOR MATCHES "Visual Studio")
	set_directory_properties(
	PROPERTIES
		VS_STARTUP_PROJECT qSQLbrowser
	)
endif()

add_subdirectory(src)
target_link_libraries(qSQLbrowser PRIVATE Qt6::Widgets Qt6::Sql)
target_compile_features(qSQLbrowser PRIVATE cxx_std_20)
qt_finalize_executable(qSQLbrowser)

set_target_properties(qSQLbrowser PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

set(CMAKE_INSTALL_MESSAGE "-- Installing: ${CMAKE_INSTALL_PREFIX}")
install(TARGETS qSQLbrowser
    BUNDLE  DESTINATION bin
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET QSqlBrowser
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})