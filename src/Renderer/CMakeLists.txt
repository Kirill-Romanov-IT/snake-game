add_library(Renderer STATIC src/ConsoleRenderer.cpp)
target_include_directories(Renderer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")