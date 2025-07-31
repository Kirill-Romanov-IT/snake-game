#include "Renderer/SfmlRenderer.h"
#include "Window/GameWindow.h"
#include "GameLogic/Constants.h"
#include <SFML/Graphics.hpp> // Здесь SFML можно и нужно

SfmlRenderer::SfmlRenderer(GameWindow& window) 
    : m_window(window), m_shape({(float)GameConfig::TILE_SIZE, (float)GameConfig::TILE_SIZE}) {}

// Принимаем простые float, а внутри используем sf::Vector2f
void SfmlRenderer::drawSnake(float x, float y) {
    sf::RectangleShape snakeSegment(sf::Vector2f(GameConfig::TILE_SIZE, GameConfig::TILE_SIZE));
    snakeSegment.setFillColor(sf::Color::Green);
    // Создаем вектор SFML из наших простых координат
    snakeSegment.setPosition(sf::Vector2f(x, y));

    m_window.getNativeWindow().draw(snakeSegment);
}

void SfmlRenderer::drawFood(float x, float y) {
    sf::RectangleShape foodItem(sf::Vector2f(GameConfig::TILE_SIZE, GameConfig::TILE_SIZE));
    foodItem.setFillColor(sf::Color::Red);
    foodItem.setPosition(sf::Vector2f(x, y));

    m_window.getNativeWindow().draw(foodItem);
}

void SfmlRenderer::draw(const std::vector<sf::Vector2i>& snakeBody, const sf::Vector2i& foodPosition) {
    // Рисуем тело змеи
    m_shape.setFillColor(sf::Color::Green);
    // Пропускаем голову, чтобы нарисовать ее отдельно
    for (size_t i = 1; i < snakeBody.size(); ++i) {
        m_shape.setPosition(snakeBody[i].x * GameConfig::TILE_SIZE, snakeBody[i].y * GameConfig::TILE_SIZE);
        m_window.getNativeWindow().draw(m_shape);
    }

    // Рисуем голову другим цветом
    if (!snakeBody.empty()) {
        m_shape.setFillColor(sf::Color(0, 150, 0)); // Темнее
        m_shape.setPosition(snakeBody.front().x * GameConfig::TILE_SIZE, snakeBody.front().y * GameConfig::TILE_SIZE);
        m_window.getNativeWindow().draw(m_shape);
    }
    
    // Рисуем еду
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(foodPosition.x * GameConfig::TILE_SIZE, foodPosition.y * GameConfig::TILE_SIZE);
    m_window.getNativeWindow().draw(m_shape);
}