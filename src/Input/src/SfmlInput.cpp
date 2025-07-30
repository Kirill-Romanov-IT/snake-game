#include "Input/SfmlInput.h"
#include <SFML/Window/Event.hpp> // Включаем полный заголовок для доступа к sf::Event::KeyEvent

Direction SfmlInput::getDirectionFromEvent(const sf::Event& event) {
    // Проверяем, было ли событие нажатием клавиши
    if (event.type == sf::Event::KeyPressed) {
        // Определяем, какая именно клавиша была нажата
        switch (event.key.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                return Direction::Up;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                return Direction::Down;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                return Direction::Left;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                return Direction::Right;
            default:
                // Была нажата другая клавиша, игнорируем
                break;
        }
    }
    // Если это было не нажатие клавиши или не одна из управляющих,
    // то направление не изменилось.
    return Direction::None;
}