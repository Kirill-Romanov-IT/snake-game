# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.15)

# Название проекта и используемый язык (C++)
project(SnakeGame CXX)

# Устанавливаем стандарт C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- БЛОК ДЛЯ ПОДКЛЮЧЕНИЯ SFML ---
include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1 # Используем конкретную стабильную версию
)

# Делаем SFML доступным для нашего проекта
# Эта команда скачает SFML (если еще не скачан) и настроит его цели (targets)
FetchContent_MakeAvailable(sfml)
# ----------------------------------------

# --- ДОБАВЬТЕ ЭТОТ БЛОК В КОНЕЦ ФАЙЛА snake-game/CMakeLists.txt ---

# Функция для копирования DLL-файлов SFML к исполняемому файлу
# Работает только под Windows
function(copy_sfml_dlls_to_target target_name)
    if(NOT WIN32)
        return()
    endif()

    # Путь, куда CMake скачал и собрал SFML
    set(SFML_LIB_DIR "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib")

    # Список модулей SFML, которые мы используем
    set(SFML_COMPONENTS
        window
        graphics
        system
        # audio # Если будете использовать звук, раскомментируйте
        # network # Если будете использовать сеть, раскомментируйте
    )

    # Добавляем команду, которая выполнится после сборки нашей цели (target_name)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMENT "Copying SFML DLLs to executable directory"
        # Для каждого компонента копируем нужную DLL (отладочную или релизную)
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-system>
            # $<TARGET_FILE:sfml-audio>
            # $<TARGET_FILE:sfml-network>
            $<TARGET_FILE_DIR:${target_name}>
    )

    # Копируем внешние зависимости SFML (для freetype и ogg/vorbis/flac)
    # Путь к ним немного другой
    if(EXISTS "${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64/")
        add_custom_command(
            TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
                "${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64/"
                $<TARGET_FILE_DIR:${target_name}>
        )
    endif()
endfunction()






# Указываем CMake, что нужно зайти в папки с нашими библиотеками и приложением
# и обработать их CMakeLists.txt
add_subdirectory(src/GameLogic)
add_subdirectory(src/Renderer)
add_subdirectory(src/Input)
add_subdirectory(src/Window)
add_subdirectory(src/app)




