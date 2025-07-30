#include <Window/GameWindow.h>
#include <Renderer/SfmlRenderer.h>
#include <GameLogic/Constants.h>
#include <SFML/Window/Event.hpp>

// Убираем зависимость от SFML/System/Vector2f.hpp
// #include <SFML/System/Vector2f.hpp> 

#include <iostream>

int main() {
    GameWindow window(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, "Snake Game");
    SfmlRenderer renderer(window);

    // Используем простые переменные для координат
    float snakeX = 100.f;
    float snakeY = 100.f;
    float foodX = 300.f;
    float foodY = 300.f;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        snakeX += 0.05f; // Или даже быстрее, чтобы было заметно: snakeX += 0.1f;

        window.clear();

        // Передаем простые float в наши методы отрисовки
        renderer.drawSnake(snakeX, snakeY);
        renderer.drawFood(foodX, foodY);

        window.display();
    }

    return 0;
}