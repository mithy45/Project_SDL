set(objects_source_files RenderedObject.cpp MovingObject.cpp PredatorObject.cpp PreyObject.cpp TimerObject.cpp GameObject.cpp)
add_library(objects SHARED ${objects_source_files})

# target_include_directories(objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# add_library(lifecycleobject LifeCycleObject.h)
# add_library(clickableobject ClickableObject.h)