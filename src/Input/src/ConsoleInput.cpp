#include "Input/ConsoleInput.h"
#include <iostream>

namespace Input {

Direction ConsoleInput::getDirection() {
    // Пока что это просто заглушка.
    // В будущем здесь будет код для считывания нажатий клавиш (например, _kbhit() и _getch() в Windows).
    std::cout << "Input is being processed!" << std::endl;
    
    // Возвращаем значение по умолчанию, так как реальной логики еще нет.
    return Direction::NONE;
}

} // namespace Input