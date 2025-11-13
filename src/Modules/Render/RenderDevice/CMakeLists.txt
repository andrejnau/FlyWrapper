list(APPEND headers
    BufferLayout.h
    Program.h
    ProgramHolder.h
    RenderDevice.h
    RenderDeviceImpl.h
    ResourceStateTracker.h
)

list(APPEND sources
    BufferLayout.cpp
    Program.cpp
    RenderDeviceImpl.cpp
    ResourceStateTracker.cpp
)

add_library(RenderDevice ${headers} ${sources})

target_include_directories(RenderDevice
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

target_link_libraries(RenderDevice
    RenderCommandList
    AppSettings
)

set_target_properties(RenderDevice PROPERTIES FOLDER "Modules/Render")
