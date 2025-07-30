#pragma once


// Прямое объявление, чтобы не включать полный заголовок GameWindow.h
// Это уменьшает зависимости и ускоряет компиляцию.
class GameWindow; 

class SfmlRenderer {
public:
    // Конструктор принимает ссылку на окно, в котором будет рисовать
    explicit SfmlRenderer(GameWindow& window);

      // Вместо sf::Vector2f будем использовать простые float.
    // А еще лучше, создадим свою простую структуру для вектора.
    // Давайте пока для простоты используем float.
    void drawSnake(float x, float y);
    void drawFood(float x, float y);
private:
    GameWindow& m_window; // Храним ссылку на наше окно
};