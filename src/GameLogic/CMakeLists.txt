# src/GameLogic/CMakeLists.txt

add_library(GameLogic STATIC
    src/Game.cpp
    # Добавьте сюда новые .cpp файлы из GameLogic, если они появятся
)

target_include_directories(GameLogic PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)