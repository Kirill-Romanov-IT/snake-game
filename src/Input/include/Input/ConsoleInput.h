#pragma once

// Объявляем перечисление для направлений движения.
// Это хорошая практика - держать такие общие типы данных
// в заголовочных файлах, чтобы они были доступны другим модулям.
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE // Нет ввода
};

namespace Input {

class ConsoleInput {
public:
    /**
     * @brief Получает последнее направление движения от пользователя.
     * @return Направление из перечисления Direction.
     */
    Direction getDirection();
};

} // namespace Input