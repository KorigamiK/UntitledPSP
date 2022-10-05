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
    utils/constants.hpp
    utils/logger.hpp
    utils/eventController.hpp
    utils/events.hpp
    utils/audioController.hpp
    utils/sounds.hpp
    utils/fontController.hpp
    utils/textureController.hpp
    utils/colors.hpp
    utils/functions.hpp
    ray_march/ray.hpp
    game/object.hpp
    game/map.hpp
    game/entity.hpp
    game/player.hpp
		game/player_view.hpp
)

# Source files (relative to "src" directory)
set(SOURCES
    main.cpp
    app.cpp
    utils/eventController.cpp
    utils/audioController.cpp
    utils/fontController.cpp
    utils/textureController.cpp
    utils/functions.cpp
    ray_march/ray.cpp
    game/map.cpp
    game/entity.cpp
    game/player.cpp
		game/player_view.cpp
)

list(TRANSFORM HEADERS PREPEND "include/")
list(TRANSFORM SOURCES PREPEND "src/")

target_sources(untitled_exe PRIVATE ${HEADERS} ${SOURCES})
target_include_directories(untitled_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (PLATFORM_PSP)
    set(PSP_LARGE_MEMORY ON)
    target_compile_definitions(untitled_exe PRIVATE PLATFORM_PSP PSP_LARGE_MEMORY)
    if (VERBOSE)
        target_compile_definitions(untitled_exe PRIVATE VERBOSE)
    endif()
    target_link_libraries(untitled_exe PRIVATE 
        stdc++
        SDL2_mixer
        SDL2_image
        SDL2main
		SDL2
        SDL2_ttf
        png
        jpeg
		GL
        freetype
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
        vorbis
        vorbisfile
        ogg
        bz2
    )

    create_pbp_file(
        TARGET untitled_exe
        TITLE "${CMAKE_PROJECT_NAME}"
        ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/res/glitch.png"
        BUILD_PRX
    )

    file(COPY "${CMAKE_SOURCE_DIR}/res/map.json" DESTINATION ${CMAKE_BINARY_DIR})

else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)

    if (NOT WIN32)
        target_link_libraries(untitled_exe PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_mixer SDL2_ttf SDL2_image freetype jsoncpp)
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/res)
    else()
        # copy runtime dependencies to binary directory
        file(COPY ${SDL2_DLL} DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${SDL2_MIXER_DLL} DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${SDL2_TTF_DLL} DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${SDL2_IMAGE_DLL} DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${FREETYPE_DLL} DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${JSONCPP_DLL} DESTINATION ${CMAKE_BINARY_DIR})
        file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
        
        target_link_libraries(untitled_exe PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2::SDL2-static jsoncpp-static SDL2_mixer SDL2_mixer-static SDL2_ttf SDL2_ttf-static SDL2_image SDL2_image-static)
    endif()
        target_compile_definitions(untitled_exe PRIVATE PLATFORM_PC VERBOSE)
endif()

