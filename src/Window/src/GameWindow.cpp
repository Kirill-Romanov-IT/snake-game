#include "Window/GameWindow.h"
#include <SFML/Graphics.hpp> // Включаем полный заголовок SFML здесь

GameWindow::GameWindow(unsigned int width, unsigned int height, const std::string& title) {
    // Создаем окно SFML и помещаем его в наш умный указатель
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
}

// Деструктор должен быть определен в .cpp файле, где sf::RenderWindow является полным типом
GameWindow::~GameWindow() = default;

bool GameWindow::isOpen() const {
    return m_window->isOpen();
}

void GameWindow::close() {
    m_window->close();
}

bool GameWindow::pollEvent(sf::Event& event) {
    return m_window->pollEvent(event);
}

void GameWindow::clear() {
    m_window->clear(sf::Color::Black); // Очищаем черным цветом по умолчанию
}

void GameWindow::display() {
    m_window->display();
}

sf::RenderWindow& GameWindow::getNativeWindow() {
    return *m_window;
}