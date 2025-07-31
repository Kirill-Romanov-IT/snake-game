#include <Window/GameWindow.h>
#include <Renderer/SfmlRenderer.h>
#include <Input/SfmlInput.h>
#include <GameLogic/Constants.h>
#include <GameLogic/Direction.h>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <random>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp> // <-- Включаем таймер
#include <thread> // <-- Для std::this_thread::sleep_for
#include <chrono> // <-- Для std::chrono::seconds
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

 

// ДОБАВЬТЕ ЭТИ СТРОКИ:
const int gridWidth = GameConfig::WINDOW_WIDTH / GameConfig::TILE_SIZE;
const int gridHeight = GameConfig::WINDOW_HEIGHT / GameConfig::TILE_SIZE;

bool isGameOver = false;

// Генератор случайных чисел для новой позиции еды
std::random_device rd;
std::mt19937 randomEngine(rd());
std::uniform_int_distribution<int> distX(0, gridWidth - 1);
std::uniform_int_distribution<int> distY(0, gridHeight - 1);

sf::Vector2i foodPosition = {distX(randomEngine), distY(randomEngine)};
    
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

        // --- НАЧАЛО ИЗМЕНЕНИЙ ---
        // Обновляем логику, только если игра еще не окончена
        if (!isGameOver) {
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

                // 4. Проверяем, съели ли мы еду
                if (newHeadPosition == foodPosition) {
                    // Еда съедена!
                    // Хвост не удаляем, змея выросла.
                    // Генерируем новую позицию для еды.
                    // Нужно убедиться, что еда не появится на теле змеи.
                    do {
                        foodPosition = {distX(randomEngine), distY(randomEngine)};
                    } while (std::find(snakeBody.begin(), snakeBody.end(), foodPosition) != snakeBody.end());

                } else {
                    // Еду не съели, просто движемся.
                    // Удаляем хвост.
                    snakeBody.pop_back();
                }
            }

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

            // --- ПРОВЕРКА СТОЛКНОВЕНИЙ ---
            const sf::Vector2i& headPos = snakeBody.front();
            // Проходим по всему телу, начиная со второго сегмента (индекс 1)
            for (size_t i = 1; i < snakeBody.size(); ++i) {
                if (headPos == snakeBody[i]) {
                    // Столкновение! Голова находится там же, где и один из сегментов тела.
                    isGameOver = true;
                    break; // Выходим из цикла, т.к. игра уже окончена
                }
            }
        }
        // --- КОНЕЦ ИЗМЕНЕНИЙ ---

       // --- ОТРИСОВКА ---
window.clear();

// Рисуем каждый сегмент змеи (без изменений)
for (const auto& segment : snakeBody) {
    float posX = segment.x * GameConfig::TILE_SIZE;
    float posY = segment.y * GameConfig::TILE_SIZE;
    renderer.drawSnake(posX, posY);
}

// --- НАЧАЛО ИЗМЕНЕНИЙ ---
// Рисуем еду по ее координатам на сетке
renderer.drawFood(foodPosition.x * GameConfig::TILE_SIZE, foodPosition.y * GameConfig::TILE_SIZE);
// --- КОНЕЦ ИЗМЕНЕНИЙ ---

window.display();

        // --- НОВЫЙ БЛОК: ЗАВЕРШЕНИЕ ИГРЫ ---
        if (isGameOver) {
            // Ждем 2 секунды
            std::this_thread::sleep_for(std::chrono::seconds(2));
            // Закрываем окно
            window.close();
        }
        // --- КОНЕЦ НОВОГО БЛОКА ---
    }

    return 0;
}