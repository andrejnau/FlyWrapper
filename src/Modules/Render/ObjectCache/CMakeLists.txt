list(APPEND headers
    ObjectCache.h
)

list(APPEND sources
    ObjectCache.cpp
)

add_library(ObjectCache ${headers} ${sources})

target_include_directories(ObjectCache
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

target_link_libraries(ObjectCache
    Instance
    Utilities
)

set_target_properties(ObjectCache PROPERTIES FOLDER "Modules/Render")
