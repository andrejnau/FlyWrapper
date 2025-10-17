set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options("/MP")
    add_compile_definitions(UNICODE _UNICODE)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(NOMINMAX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-array-bounds>
        $<$<COMPILE_LANGUAGE:CXX>:-Wno-stringop-overflow>
    )
endif()

if (APPLE)
    add_compile_options(
        -Wno-missing-template-arg-list-after-template-kw
    )
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
    set(CMAKE_INSTALL_RPATH "/usr/local/lib")
endif()
