cmake_minimum_required(VERSION 3.14)

project(
    untitled
    VERSION 0.1.0
    DESCRIPTION "When it is a feature not a bug"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(BUILD_STATIC_DEFAULT OFF)
if(WIN32)
    SET(BUILD_STATIC_DEFAULT ON)
endif()
option(BUILD_STATIC "Build a static binary" ${BUILD_STATIC_DEFAULT})

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
    game/state/base.hpp
    game/state/states.hpp
    game/state/controller.hpp
    game/state/menu.hpp
    game/state/game.hpp
    game/state/gameScreen.hpp
    game/state/pauseScreen.hpp
    game/state/winScreen.hpp
    game/state/not_implemented.hpp
)

# Source files (relative to "src" directory)
set(SOURCES
    main.cpp
    app.cpp
    utils/constants.cpp
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
    game/state/base.cpp
    game/state/menu.cpp
    game/state/controller.cpp
    game/state/game.cpp
    game/state/pauseScreen.cpp
    game/state/winScreen.cpp
    game/state/not_implemented.cpp
)

list(TRANSFORM HEADERS PREPEND "include/")
list(TRANSFORM SOURCES PREPEND "src/")

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 src/main.cpp ${SOURCES} ${HEADERS})
else()
    add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES} ${HEADERS})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (PLATFORM_PSP)

    set(PSP_LARGE_MEMORY ON)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_PSP PSP_LARGE_MEMORY)
    if (VERBOSE)
        message("Verbose option enabled")
        target_compile_definitions(${PROJECT_NAME} PRIVATE VERBOSE)
    endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE 
        stdc++
        SDL2_mixer
        SDL2_image
        SDL2main
		SDL2
        SDL2_ttf
        SDL2_gfx
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
        TARGET ${PROJECT_NAME}
        TITLE "${CMAKE_PROJECT_NAME}"
        ICON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/res/glitch.png"
        BUILD_PRX
    )

    file(COPY "${CMAKE_SOURCE_DIR}/res/map.json" DESTINATION ${CMAKE_BINARY_DIR})
else()
    include(FindPkgConfig)
    pkg_search_module(SDL2 REQUIRED sdl2)
    pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
    pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)
    pkg_search_module(SDL2_GFX REQUIRED SDL2_gfx)
    pkg_search_module(JSONCPP REQUIRED jsoncpp)

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_GFX_INCLUDE_DIRS}
        ${JSONCPP_INCLUDE_DIRS}
    )

    if (BUILD_STATIC)
        set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")
        target_link_libraries(${PROJECT_NAME} PRIVATE
            ${SDL2_STATIC_LIBRARIES}
            ${SDL2_MIXER_STATIC_LIBRARIES}
            ${SDL2_IMAGE_STATIC_LIBRARIES}
            ${SDL2_TTF_STATIC_LIBRARIES}
            ${SDL2_GFX_STATIC_LIBRARIES}
            ${JSONCPP_STATIC_LIBRARIES}
        )
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE
            ${SDL2_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_TTF_LIBRARIES}
            ${SDL2_GFX_LIBRARIES}
            ${JSONCPP_LIBRARIES}
        )
    endif()
    
    if (WIN32)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main)
    endif()

    if (NOT WIN32)
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res
            ${CMAKE_BINARY_DIR}/res)
    endif()
    if (VERBOSE)
        message(STATUS "Setting verbose flag")
        target_compile_definitions(${PROJECT_NAME} PRIVATE VERBOSE)
    endif()

endif()

