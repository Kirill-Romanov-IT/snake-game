#pragma once

#include <string>
#include <memory>

// Прямое объявление (forward declaration), чтобы не включать <SFML/Graphics.hpp>
namespace sf {
    class RenderWindow;
    class Event;
}

class GameWindow {
public:
    GameWindow(unsigned int width, unsigned int height, const std::string& title);
    ~GameWindow(); // Деструктор обязателен для std::unique_ptr с неполным типом

    bool isOpen() const;
    void close();

    // Обработка событий (нажатие на крестик, изменение размера и т.д.)
    bool pollEvent(sf::Event& event);

    void clear();    // Очистить окно (залить цветом)
    void display();  // Показать нарисованное на экране

    // Метод для доступа к "родному" окну SFML, понадобится для Рендерера
    sf::RenderWindow& getNativeWindow();

private:
    // Используем умный указатель, чтобы автоматически управлять памятью
    // Это и есть наш "указатель на реализацию" (PIMPL)
    std::unique_ptr<sf::RenderWindow> m_window;
};