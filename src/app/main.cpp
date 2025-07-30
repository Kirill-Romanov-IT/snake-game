#include <iostream>

// Подключаем все наши модули
#include <GameLogic/Game.h>
#include <Renderer/ConsoleRenderer.h>
#include <Input/ConsoleInput.h>

int main() {
    // Создаем экземпляры классов из наших библиотек
    GameLogic::Game game;
    Renderer::ConsoleRenderer renderer;
    Input::ConsoleInput input; // Создали объект для ввода

    // Вызываем методы-заглушки
    game.run();
    renderer.draw();
    input.getDirection(); // Вызвали метод из библиотеки Input

    std::cout << "\nAll modules linked successfully!" << std::endl;
    
    return 0;
}