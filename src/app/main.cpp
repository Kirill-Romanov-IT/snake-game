#include <Window/GameWindow.h>
#include <SFML/Window/Event.hpp> // Нам нужен доступ к sf::Event для цикла

#include <iostream>

int main() {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    const std::string WINDOW_TITLE = "Snake Game";

    // Создаем окно через нашу библиотеку-обертку
    GameWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    
    std::cout << "Window created. Starting main loop..." << std::endl;

    // Главный цикл приложения
    while (window.isOpen()) {
        sf::Event event;
        // Обрабатываем все события в очереди
        while (window.pollEvent(event)) {
            // Если было запрошено закрытие окна (нажат крестик)
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Очистка
        window.clear();

        // Отрисовка (пока ничего не рисуем)
        // ...

        // Отображение кадра
        window.display();
    }

    std::cout << "Window closed. Exiting." << std::endl;

    return 0;
}