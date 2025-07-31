#include "GameLogic/Game.h"
#include "GameLogic/Constants.h"
#include <algorithm> // для std::find

// Конструктор инициализирует игру
Game::Game() 
    : m_randomEngine(std::random_device{}()), // Инициализируем генератор
      m_isGameOver(false),
      m_direction(Direction::Right),
      m_timePerMove(0.2f),
      m_timeSinceLastMove(0.0f)
{
    // Создаем начальную змейку
    const int startX = GameConfig::WINDOW_WIDTH / GameConfig::TILE_SIZE / 2;
    const int startY = GameConfig::WINDOW_HEIGHT / GameConfig::TILE_SIZE / 2;
    m_snakeBody.push_back({startX, startY});
    m_snakeBody.push_back({startX - 1, startY});
    m_snakeBody.push_back({startX - 2, startY});

    // Создаем первую еду
    spawnFood();
}

// Пока оставим остальные методы пустыми
void Game::update(float deltaTime) {
    if (m_isGameOver) {
        return;
    }

    m_timeSinceLastMove += deltaTime;
    if (m_timeSinceLastMove >= m_timePerMove) {
        m_timeSinceLastMove -= m_timePerMove;
        
        moveSnake(); // Двигаем змею
        checkCollisions(); // Проверяем столкновения
    }
}
void Game::changeDirection(Direction newDirection) {
    // Не даем изменить направление, если игра окончена
    if (m_isGameOver) return;
    
    // Запрещаем разворот на 180 градусов
    if (m_direction == Direction::Up && newDirection == Direction::Down) return;
    if (m_direction == Direction::Down && newDirection == Direction::Up) return;
    if (m_direction == Direction::Left && newDirection == Direction::Right) return;
    if (m_direction == Direction::Right && newDirection == Direction::Left) return;

    m_direction = newDirection;
}
void Game::spawnFood() {
    const int gridWidth = GameConfig::WINDOW_WIDTH / GameConfig::TILE_SIZE;
    const int gridHeight = GameConfig::WINDOW_HEIGHT / GameConfig::TILE_SIZE;
    
    std::uniform_int_distribution<int> distX(0, gridWidth - 1);
    std::uniform_int_distribution<int> distY(0, gridHeight - 1);

    // Генерируем позицию для еды, пока она не окажется в свободном месте
    do {
        m_foodPosition = {distX(m_randomEngine), distY(m_randomEngine)};
    } while (std::find(m_snakeBody.begin(), m_snakeBody.end(), m_foodPosition) != m_snakeBody.end());
}
void Game::moveSnake() {
    sf::Vector2i newHeadPosition = m_snakeBody.front();

    switch (m_direction) {
        case Direction::Up:    newHeadPosition.y -= 1; break;
        case Direction::Down:  newHeadPosition.y += 1; break;
        case Direction::Left:  newHeadPosition.x -= 1; break;
        case Direction::Right: newHeadPosition.x += 1; break;
        case Direction::None:  return; // Если направления нет, ничего не делаем
    }

    m_snakeBody.insert(m_snakeBody.begin(), newHeadPosition);

    if (newHeadPosition == m_foodPosition) {
        spawnFood(); // Съели еду, создаем новую
    } else {
        m_snakeBody.pop_back(); // Не съели, просто движемся
    }

    // Прохождение сквозь стены
    sf::Vector2i& head = m_snakeBody.front();
    const int gridWidth = GameConfig::WINDOW_WIDTH / GameConfig::TILE_SIZE;
    const int gridHeight = GameConfig::WINDOW_HEIGHT / GameConfig::TILE_SIZE;

    if (head.x < 0) head.x = gridWidth - 1;
    else if (head.x >= gridWidth) head.x = 0;
    if (head.y < 0) head.y = gridHeight - 1;
    else if (head.y >= gridHeight) head.y = 0;
}
void Game::checkCollisions() {
    const sf::Vector2i& head = m_snakeBody.front();
    for (size_t i = 1; i < m_snakeBody.size(); ++i) {
        if (head == m_snakeBody[i]) {
            m_isGameOver = true;
            return;
        }
    }
}

// Реализуем геттеры
const std::vector<sf::Vector2i>& Game::getSnakeBody() const { return m_snakeBody; }
const sf::Vector2i& Game::getFoodPosition() const { return m_foodPosition; }
bool Game::isGameOver() const { return m_isGameOver; }