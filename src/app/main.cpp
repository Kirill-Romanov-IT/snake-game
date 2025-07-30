#include <Window/GameWindow.h>
#include <Renderer/SfmlRenderer.h>
#include <Input/SfmlInput.h>       // <-- Включаем наш Input
#include <GameLogic/Constants.h>
#include <GameLogic/Direction.h>   // <-- Включаем Direction

#include <SFML/Window/Event.hpp>
#include <iostream>

int main() {
    GameWindow window(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, "Snake Game");
    SfmlRenderer renderer(window);

    // Установим скорость движения змейки
    const float snakeSpeed = 0.1f;

    // Начальные координаты и направление
    float snakeX = 100.f;
    float snakeY = 100.f;
    Direction currentDirection = Direction::Right; // Начинаем двигаться вправо

    float foodX = 300.f;
    float foodY = 300.f;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // --- ОБРАБОТКА ВВОДА ---
            Direction newDirection = SfmlInput::getDirectionFromEvent(event);
            if (newDirection != Direction::None) {
                // Здесь нужно будет добавить логику, чтобы змея не могла развернуться на 180 градусов
                currentDirection = newDirection;
            }
        }

        // --- ОБНОВЛЕНИЕ ЛОГИКИ ---
        switch (currentDirection) {
            case Direction::Up:    snakeY -= snakeSpeed; break;
            case Direction::Down:  snakeY += snakeSpeed; break;
            case Direction::Left:  snakeX -= snakeSpeed; break;
            case Direction::Right: snakeX += snakeSpeed; break;
            case Direction::None:  break; // Не двигаемся, если нет направления
        }

        // --- ОТРИСОВКА ---
        window.clear();
        renderer.drawSnake(snakeX, snakeY);
        renderer.drawFood(foodX, foodY);
        window.display();
    }

    return 0;
}