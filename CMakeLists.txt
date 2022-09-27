cmake_minimum_required(VERSION 3.14)

project(
    untitled
    VERSION 0.1.0
    DESCRIPTION "When it is a feature not a bug"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

add_executable(untitled_exe src/main.cpp)
add_executable(untitled::exe ALIAS untitled_exe)

set_target_properties(
    untitled_exe PROPERTIES
    OUTPUT_NAME untitled_exe
    EXPORT_NAME exe
)

target_compile_features(untitled_exe PRIVATE cxx_std_17)

# Header files (relative to "include" directory)
set(HEADERS
    app.hpp
    game/entity.hpp
    game/player.hpp
)

# Source files (relative to "src" directory)
set(SOURCES
    main.cpp
    app.cpp
    game/entity.cpp
    game/player.cpp
)

list(TRANSFORM HEADERS PREPEND "include/")
list(TRANSFORM SOURCES PREPEND "src/")

target_sources(untitled_exe PRIVATE ${HEADERS} ${SOURCES})
target_include_directories(untitled_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (PLATFORM_PSP)
    set(PSP_LARGE_MEMORY ON)
    target_compile_definitions(untitled_exe PRIVATE PLATFORM_PSP)
    target_link_libraries(untitled_exe PRIVATE 
        stdc++
        SDL2main
		SDL2
		GL
		png
		z
		pspvram
		pspdisplay
		pspvfpu
		pspgu
		pspge
		pspdebug
		psphprm
		pspctrl
		pspaudio
        jsoncpp
    )

    create_pbp_file(
        TARGET untitled_exe
        TITLE "${CMAKE_PROJECT_NAME}"
        ICON_PATH NULL # "${CMAKE_CURRENT_SOURCE_DIR}/icon0.png"
        BUILD_PRX
    )

    file(COPY "${CMAKE_SOURCE_DIR}/res/map.json" DESTINATION ${CMAKE_BINARY_DIR})

else()
    find_package(SDL2 REQUIRED)
    target_compile_definitions(untitled_exe PRIVATE PLATFORM_PC)
    target_link_libraries(untitled_exe PRIVATE SDL2::SDL2 SDL2::SDL2main jsoncpp)
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
                                                               ${CMAKE_BINARY_DIR}/res)
endif()

