# Создаем исполняемый файл (executable) с именем SnakeGame из main.cpp
add_executable(SnakeGame
    main.cpp
)

# Подключаем (линкуем) наши библиотеки к исполняемому файлу.
# CMake сам найдет нужные .lib/.a файлы и пути к заголовочным файлам,
# потому что мы использовали `target_include_directories` с опцией PUBLIC.
target_link_libraries(SnakeGame PRIVATE
    GameLogic
    Renderer
    Input
)