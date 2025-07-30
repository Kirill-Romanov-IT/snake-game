#pragma once

#include <GameLogic/Direction.h> // Подключаем наш enum

// Прямое объявление, чтобы не включать "тяжелый" SFML.hpp
namespace sf {
    class Event;
}

class SfmlInput {
public:
    // Статический метод, т.к. ему не нужно хранить состояние.
    // Он просто преобразует одно в другое.
    static Direction getDirectionFromEvent(const sf::Event& event);
};