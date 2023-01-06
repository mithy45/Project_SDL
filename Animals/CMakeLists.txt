set(animals_source_files Animal.cpp Sheep.cpp Wolf.cpp ShepherdDog.cpp)
add_library(animals SHARED ${animals_source_files})

include_directories(${CMAKE_SOURCE_DIR}/Objects)