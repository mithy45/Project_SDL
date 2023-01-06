cmake_minimum_required (VERSION 3.0)
project("Project_SDL_PART_2")

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
IF(WIN32)
    message(STATUS "Building for windows")

    set(SDL2_INCLUDE_DIRS "SDL2/include")
    set(SDL2IMAGE_INCLUDE_DIRS "SDL2_image/include")

    # Support both 32 and 64 bit builds
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        message(STATUS "Building for 64bit")
        set(SDL2_LINK_DIRS "SDL2/lib/x64")
        set(SDL2IMAGE_LINK_DIRS "SDL2_image/lib/x64")
    else ()
        message(STATUS "Building for 32bit")
        set(SDL2_LINK_DIRS "SDL2/lib/x86")
        set(SDL2IMAGE_LINK_DIRS "SDL2_image/lib/x86")
    endif ()

    include_directories(${SDL2_INCLUDE_DIRS})
    include_directories(${SDL2IMAGE_INCLUDE_DIRS})
    include_directories(${CMAKE_SOURCE_DIR}/)

    add_subdirectory(Objects)
    add_subdirectory(Animals)
    add_subdirectory(PlayableCharacters)
    add_subdirectory(GameEngine)

    link_directories(${SDL2_LINK_DIRS}, ${SDL2IMAGE_LINK_DIRS})

    add_executable(main main.cpp)
    target_link_libraries(main PUBLIC SDL2 SDL2main SDL2_image objects animals playable_characters game_engine)
ELSE()
    message(STATUS "Building for Linux or Mac")

    find_package(SDL2 REQUIRED)
    find_package(SDL2_IMAGE REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
    include_directories(${CMAKE_SOURCE_DIR}/)

    add_subdirectory(Objects)
    add_subdirectory(Animals)
    add_subdirectory(PlayableCharacters)
    add_subdirectory(GameEngine)

    add_executable(main main.cpp)

    target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} objects animals playable_characters game_engine)
ENDIF()