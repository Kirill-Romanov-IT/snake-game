#include <Window/GameWindow.h>
#include <Renderer/SfmlRenderer.h>
#include <Input/SfmlInput.h>
#include <GameLogic/Constants.h>
#include <GameLogic/Direction.h>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp> // <-- Включаем таймер
#include <iostream>

int main() {
    GameWindow window(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, "Snake Game");
    SfmlRenderer renderer(window);

    // --- НАСТРОЙКА ДЛЯ DELTA TIME ---
    sf::Clock clock; // Создаем и запускаем таймер
    float deltaTime = 0.f;

    // Скорость теперь измеряется в "пикселях В СЕКУНДУ"
    const float snakeSpeed = 100.0f; 

    float snakeX = 100.f;
    float snakeY = 100.f;
    Direction currentDirection = Direction::Right;

    float foodX = 300.f;
    float foodY = 300.f;
    
    while (window.isOpen()) {
        // --- В НАЧАЛЕ ЦИКЛА ОБНОВЛЯЕМ DELTA TIME ---
        // restart() возвращает прошедшее время и сбрасывает таймер
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            // ... обработка событий без изменений ...
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            Direction newDirection = SfmlInput::getDirectionFromEvent(event);
            if (newDirection != Direction::None) {
                currentDirection = newDirection;
            }
        }

        // --- ОБНОВЛЕНИЕ ЛОГИКИ С УЧЕТОМ DELTA TIME ---
        // Теперь мы умножаем скорость на время, прошедшее с прошлого кадра
        switch (currentDirection) {
            case Direction::Up:    snakeY -= snakeSpeed * deltaTime; break;
            case Direction::Down:  snakeY += snakeSpeed * deltaTime; break;
            case Direction::Left:  snakeX -= snakeSpeed * deltaTime; break;
            case Direction::Right: snakeX += snakeSpeed * deltaTime; break;
            case Direction::None:  break;
        }

        // --- НОВЫЙ БЛОК: ПРОВЕРКА ГРАНИЦ ОКНА ---

        // Проверка по горизонтали (ось X)
        if (snakeX + GameConfig::TILE_SIZE < 0) {
            // Если змейка полностью ушла за левый край, появляемся у правого
            snakeX = GameConfig::WINDOW_WIDTH; 
        } else if (snakeX > GameConfig::WINDOW_WIDTH) {
            // Если змейка начала выходить за правый край, появляемся у левого
            snakeX = -GameConfig::TILE_SIZE;
        }

        // Проверка по вертикали (ось Y)
        if (snakeY + GameConfig::TILE_SIZE < 0) {
            // Если змейка полностью ушла за верхний край, появляемся у нижнего
            snakeY = GameConfig::WINDOW_HEIGHT;
        } else if (snakeY > GameConfig::WINDOW_HEIGHT) {
            // Если змейка начала выходить за нижний край, появляемся у верхнего
            snakeY = -GameConfig::TILE_SIZE;
        }

        // --- КОНЕЦ НОВОГО БЛОКА ---

        // --- ОТРИСОВКА (без изменений) ---
        window.clear();
        renderer.drawSnake(snakeX, snakeY);
        renderer.drawFood(foodX, foodY);
        window.display();
    }

    return 0;
}