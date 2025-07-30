add_library(GameLogic STATIC
    src/Game.cpp
)

target_include_directories(GameLogic PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)