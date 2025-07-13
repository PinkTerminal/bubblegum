cmake_minimum_required( VERSION 3.28 )

project( bubblegum )

add_subdirectory( vendor/SDL EXCLUDE_FROM_ALL )

add_executable(
    bubblegum	
    editor.cpp
)

target_include_directories(
    bubblegum
    PRIVATE
    vendor/SDL/include
)

target_link_libraries(
    bubblegum
    PRIVATE
    SDL3::SDL3
)
