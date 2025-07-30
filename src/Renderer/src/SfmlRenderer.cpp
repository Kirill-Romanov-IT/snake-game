#include "Renderer/SfmlRenderer.h"
#include "Window/GameWindow.h"
#include "GameLogic/Constants.h"
#include <SFML/Graphics.hpp> // Здесь SFML можно и нужно

SfmlRenderer::SfmlRenderer(GameWindow& window) : m_window(window) {}

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