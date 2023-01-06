set(playable_characters_source_files PlayableCharacter.cpp Shepherd.cpp)
add_library(playable_characters SHARED ${playable_characters_source_files})
# target_include_directories(playable_characters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
