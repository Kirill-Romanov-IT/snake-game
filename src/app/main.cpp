// Подключаем все наши модули и необходимые заголовки SFML
#include <Window/GameWindow.h>
#include <Renderer/SfmlRenderer.h>
#include <Input/SfmlInput.h>
#include <GameLogic/Game.h>
#include <GameLogic/Constants.h>
#include <GameLogic/Direction.h>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp> // Для sf::sleep

#include <SFML/System/Time.hpp>   // sf::seconds
#include <SFML/System/Sleep.hpp>  // sf::sleep
#include <iostream>

int main() {
    // --- 1. ИНИЦИАЛИЗАЦИЯ ---
    // Создаем все наши объекты. Логика инициализации игры теперь внутри конструктора Game.
    Game game;
    GameWindow window(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, "Snake Game");
    SfmlRenderer renderer(window);
    sf::Clock clock;

    // --- 2. ГЛАВНЫЙ ЦИКЛ ИГРЫ ---
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // --- Обработка событий ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Получаем направление от Input и передаем его в объект Game
            Direction newDirection = SfmlInput::getDirectionFromEvent(event);
            if (newDirection != Direction::None) {
                game.changeDirection(newDirection);
            }
        }
        
        // --- Обновление логики ---
        // Просто вызываем один метод, вся сложность внутри него.
        game.update(deltaTime);

        // --- Отрисовка ---
        window.clear();
        
        // Получаем данные для отрисовки из объекта Game и передаем их в Renderer
        renderer.draw(game.getSnakeBody(), game.getFoodPosition());
        
        window.display();
        
        // --- Проверка на Game Over ---
        if (game.isGameOver()) {
            std::cout << "Game Over!" << std::endl;
            // Ждем 2 секунды и закрываем окно
            sf::sleep(sf::seconds(2.0f));
            window.close();
        }
    }

    return 0;
}