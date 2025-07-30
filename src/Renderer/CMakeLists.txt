add_library(Renderer STATIC src/SfmlRenderer.cpp)
target_include_directories(Renderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# --- ВОТ ПРАВИЛЬНОЕ МЕСТО ДЛЯ ЭТОЙ КОМАНДЫ ---
# Сообщаем CMake, что Renderer зависит от библиотек Window и GameLogic.
# Он сможет их найти, потому что они были определены в CMakeLists.txt,
# которые главный CMake-файл обработал РАНЬШЕ.
target_link_libraries(Renderer PUBLIC
    Window
    GameLogic
)