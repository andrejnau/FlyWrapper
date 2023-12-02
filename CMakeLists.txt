cmake_minimum_required(VERSION 3.15)
project(FlyWrapper)

if (CMAKE_SYSTEM_NAME STREQUAL "iOS" OR CMAKE_SYSTEM_NAME STREQUAL "tvOS")
    set(IOS_OR_TVOS TRUE)
endif()

include(CMakeDependentOption)
option(VULKAN_SUPPORT "Vulkan support" ON)
cmake_dependent_option(DIRECTX_SUPPORT "DirectX 12 support" ON "WIN32" OFF)
cmake_dependent_option(METAL_SUPPORT "Metal support" ON "APPLE" OFF)
cmake_dependent_option(BUILD_SAMPLES "Build samples" ON "NOT IOS_OR_TVOS" OFF)
cmake_dependent_option(BUILD_TESTING "Build unit tests" ON "NOT IOS_OR_TVOS" OFF)

set(project_root "${CMAKE_CURRENT_SOURCE_DIR}")
set(assets_path "${project_root}/assets/")
add_library(FlyWrapperAssets INTERFACE)
target_compile_definitions(FlyWrapperAssets INTERFACE ASSETS_PATH="${assets_path}")

list(PREPEND CMAKE_MODULE_PATH "${project_root}/cmake")
include(cmake_settings)
include(compiler_settings)

add_subdirectory(3rdparty/FlyCube)
include(3rdparty/assimp)
include(3rdparty/mustache)

if (BUILD_TESTING)
    enable_testing()
endif()

add_subdirectory(src)
