#include <Window/GameWindow.h>
#include <Renderer/SfmlRenderer.h>
#include <Input/SfmlInput.h>
#include <GameLogic/Constants.h>
#include <GameLogic/Direction.h>
#include <vector>
#include <SFML/System/Vector2i.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp> // <-- Включаем таймер
#include <iostream>

int main() {
    GameWindow window(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, "Snake Game");
    SfmlRenderer renderer(window);

    // --- НАСТРОЙКА ДЛЯ DELTA TIME ---
    sf::Clock clock; // Создаем и запускаем таймер
    float deltaTime = 0.f;

    const float timePerMove = 0.2f;
    float timeSinceLastMove = 0.0f;

    int startX = GameConfig::WINDOW_WIDTH / GameConfig::TILE_SIZE / 2;
    int startY = GameConfig::WINDOW_HEIGHT / GameConfig::TILE_SIZE / 2;

    // Создаем тело змеи. Первый элемент - голова.
    std::vector<sf::Vector2i> snakeBody;
    snakeBody.push_back({startX, startY});      // Голова
    snakeBody.push_back({startX - 1, startY});  // Сегмент тела
    snakeBody.push_back({startX - 2, startY});  // Хвост
    


    Direction currentDirection = Direction::Right;

    float foodX = 300.f;
    float foodY = 300.f;
    
    while (window.isOpen()) {
        // --- В НАЧАЛЕ ЦИКЛА ОБНОВЛЯЕМ DELTA TIME ---
        // restart() возвращает прошедшее время и сбрасывает таймер
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            // ... обработка событий без изменений ...
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            Direction newDirection = SfmlInput::getDirectionFromEvent(event);
            if (newDirection != Direction::None) {
                currentDirection = newDirection;
            }
        }

        // --- ОБНОВЛЕНИЕ ЛОГИКИ ПО СЕТКЕ ---
// 1. Накапливаем время, прошедшее с прошлого кадра
timeSinceLastMove += deltaTime;

// 2. Проверяем, достаточно ли времени накопилось для следующего хода
if (timeSinceLastMove >= timePerMove) {
    // Времени достаточно, делаем ход!

    // Сбрасываем счетчик (вычитаем время одного хода)
    timeSinceLastMove -= timePerMove;

    sf::Vector2i newHeadPosition = snakeBody.front(); 

    // 2. Смещаем новую голову на одну клетку в нужном направлении
    switch (currentDirection) {
        case Direction::Up:    newHeadPosition.y -= 1; break;
        case Direction::Down:  newHeadPosition.y += 1; break;
        case Direction::Left:  newHeadPosition.x -= 1; break;
        case Direction::Right: newHeadPosition.x += 1; break;
        case Direction::None:  break;
    }

    // 3. Добавляем новую голову в начало змеи
    snakeBody.insert(snakeBody.begin(), newHeadPosition);

    // 4. Удаляем хвост
    snakeBody.pop_back();

}

        // --- ВСТАВЬТЕ ЭТОТ БЛОК ---
// --- ПРОВЕРКА ГРАНИЦ ОКНА ---
sf::Vector2i& head = snakeBody.front(); // Получаем ссылку на голову, чтобы ее можно было изменить

// Вычисляем размеры нашей сетки в клетках
const int gridWidth = GameConfig::WINDOW_WIDTH / GameConfig::TILE_SIZE;
const int gridHeight = GameConfig::WINDOW_HEIGHT / GameConfig::TILE_SIZE;

// Проверяем и корректируем координаты головы
if (head.x < 0) {
    head.x = gridWidth - 1; // Если ушли влево, появляемся справа
} else if (head.x >= gridWidth) {
    head.x = 0; // Если ушли вправо, появляемся слева
}

if (head.y < 0) {
    head.y = gridHeight - 1; // Если ушли вверх, появляемся снизу
} else if (head.y >= gridHeight) {
    head.y = 0; // Если ушли вниз, появляемся сверху
}
// --- КОНЕЦ НОВОГО БЛОКА ---

        // --- ОТРИСОВКА ---
window.clear();
// renderer.drawSnake(snakeX, snakeY); // Удаляем старый вызов
// renderer.drawFood(foodX, foodY);

// Рисуем каждый сегмент змеи
for (const auto& segment : snakeBody) {
    // Преобразуем координаты сетки в пиксельные координаты
    float posX = segment.x * GameConfig::TILE_SIZE;
    float posY = segment.y * GameConfig::TILE_SIZE;
    renderer.drawSnake(posX, posY);
}
// Еду пока оставим на месте
renderer.drawFood(foodX, foodY);

window.display();
    }

    return 0;
}