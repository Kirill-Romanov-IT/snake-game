add_library(Window STATIC
    src/GameWindow.cpp
)

target_include_directories(Window PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Наша библиотека Window зависит от SFML.
# Мы линкуем ее с модулями sfml-window, sfml-graphics и sfml-system.
# Ключевое слово PUBLIC означает, что любой, кто подключит нашу библиотеку Window,
# автоматически получит доступ к заголовочным файлам SFML и будет слинкован с ним.
target_link_libraries(Window PUBLIC
    sfml-window
    sfml-graphics # Нужен для sf::Color и других графических примитивов
    sfml-system
)