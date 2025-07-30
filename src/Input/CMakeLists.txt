add_library(Input STATIC src/SfmlInput.cpp)
target_include_directories(Input PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Добавляем зависимости
target_link_libraries(Input PUBLIC
    Window
    GameLogic
)