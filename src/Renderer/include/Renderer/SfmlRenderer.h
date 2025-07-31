#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// Прямое объявление, чтобы не включать полный заголовок GameWindow.h
// Это уменьшает зависимости и ускоряет компиляцию.
class GameWindow; 

class SfmlRenderer {
public:
    // Конструктор принимает ссылку на окно, в котором будет рисовать
    explicit SfmlRenderer(GameWindow& window);

    // Старые методы (пока оставим для совместимости)
    void drawSnake(float x, float y);
    void drawFood(float x, float y);
    
    // Один метод для отрисовки всей игры
    void draw(const std::vector<sf::Vector2i>& snakeBody, const sf::Vector2i& foodPosition);
    
private:
    GameWindow& m_window; // Храним ссылку на наше окно
    sf::RectangleShape m_shape; // Добавим для эффективности
};