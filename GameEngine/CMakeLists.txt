set(game_engine_source_files Engine.cpp Game.cpp)
add_library(game_engine SHARED ${game_engine_source_files})

# message(STATUS "DIR : ${CMAKE_SOURCE_DIR}") GOOD

# target_include_directories(game_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
