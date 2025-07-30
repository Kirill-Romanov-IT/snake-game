add_library(Input STATIC src/ConsoleInput.cpp)
target_include_directories(Input PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")