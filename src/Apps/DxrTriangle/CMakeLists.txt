set(target DxrTriangle)

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")
set(shaders_path "${assets_path}/shaders/DxrTriangle")

set(sources
    ${source_path}/main.cpp
)

set(lib_shaders
    ${shaders_path}/RayTracing.hlsl
)

set_property(SOURCE ${lib_shaders} PROPERTY SHADER_ENTRYPOINT " ")
set_property(SOURCE ${lib_shaders} PROPERTY SHADER_TYPE Library)
set_property(SOURCE ${lib_shaders} PROPERTY SHADER_MODEL 6.3)

set(shaders_files ${lib_shaders})

include(shader_parser)
gen_shaders_ref(${target} "${shaders_files}" shaders_ref)

source_group("Shader Files" FILES ${shaders_files})
source_group("Shader Ref Files" FILES ${shaders_ref})

add_executable(${target} WIN32 ${headers} ${sources} ${shaders_files} ${shaders_ref})

if (WIN32)
    set_target_properties(${target} PROPERTIES
                        LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

target_include_directories(${target}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
        ${CMAKE_BINARY_DIR}/gen/${target}
)

target_link_libraries(${target}
    RenderDevice
    assimp
    AppBox
    Texture
    FlyWrapperAssets
)

set_target_properties(${target} PROPERTIES FOLDER "Apps")

install(TARGETS ${target})
