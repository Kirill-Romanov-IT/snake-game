# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.15)

# Название проекта и используемый язык (C++)
project(SnakeGame CXX)

# Устанавливаем стандарт C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем CMake, что нужно зайти в папки с нашими библиотеками и приложением
# и обработать их CMakeLists.txt
add_subdirectory(src/GameLogic)
add_subdirectory(src/Renderer)
add_subdirectory(src/Input)
add_subdirectory(src/app)