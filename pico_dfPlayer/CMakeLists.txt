add_library(pico_dfPlayer INTERFACE)

target_sources(pico_dfPlayer INTERFACE
#        ${CMAKE_CURRENT_LIST_DIR}/dfPlayerDriver.h
#        ${CMAKE_CURRENT_LIST_DIR}/dfPlayer/dfPlayer.h
        ${CMAKE_CURRENT_LIST_DIR}/dfPlayer/dfPlayer.cpp
)

target_include_directories(pico_dfPlayer INTERFACE
        dfPlayer
        driver
)

target_link_libraries(pico_dfPlayer INTERFACE
        pico_stdlib
)
