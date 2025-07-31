#pragma once

#include "Direction.h"
#include <vector>
#include <random> // Для генератора случайных чисел
#include <SFML/System/Vector2.hpp>

class Game {
public:
    // Конструктор
    Game();

    // Публичные методы для управления игрой извне (из main.cpp)
    void update(float deltaTime);
    void changeDirection(Direction newDirection);

    // "Геттеры" - методы для получения данных для отрисовки
    const std::vector<sf::Vector2i>& getSnakeBody() const;
    const sf::Vector2i& getFoodPosition() const;
    bool isGameOver() const;

private:
    // Все переменные состояния теперь здесь
    std::vector<sf::Vector2i> m_snakeBody;
    sf::Vector2i m_foodPosition;
    Direction m_direction;

    float m_timePerMove;
    float m_timeSinceLastMove;

    bool m_isGameOver;

    // Генератор случайных чисел как член класса
    std::mt19937 m_randomEngine;

    // Приватные вспомогательные методы
    void spawnFood();
    void moveSnake();
    void checkCollisions();
};