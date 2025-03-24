#ifndef ENTITY
#define ENTITY
#include <string>
#include <memory>
#include "Vector.hpp"
#include "Cell.hpp"
#include <SFML/Graphics.hpp>
class Game_stat;
class Game_texts;
class Level;
/*!
    \file Entity.hpp
    \brief Базовый класс для всех сущностей игрового мира.

    Этот файл содержит определение класса \c Entity, который предоставляет общую функциональность для всех сущностей, таких как персонажи или нейтральные объекты.
*/

/*!
    \enum Team
    \brief Команда, к которой принадлежит сущность.

    Возможные значения:
    - \c Radiant — команда Radiant.
    - \c Dire — команда Dire.
    - \c None — отсутствие команды.
*/
enum class Team { Radiant, Dire, None };


/*!
    \class Entity
    \brief Базовый класс для сущностей игрового мира.

    Класс предоставляет интерфейс и основные данные для работы с сущностями, такими как тип, команда, здоровье, скорость, радиус обзора и т.д.
*/
class Entity
{
protected:
    std::string _typeEntity;          /*!< Тип сущности. */
    std::string _name;               /*!< Имя сущности. */
    Team _team;                      /*!< Команда, к которой принадлежит сущность. */
    int _speed;                      /*!< Скорость передвижения. */
    int _HP;                         /*!< Текущее здоровье сущности. */
    int _maxHP;                      /*!< Максимальное здоровье сущности. */
    int _viewRadius;                 /*!< Радиус обзора сущности. */
    int _maxTimePoint;               /*!< Максимальное количество очков времени. */
    int _timePoint;                  /*!< Текущее количество очков времени. */
    std::shared_ptr<Cell> _position; /*!< Текущая позиция сущности. */

public:
    virtual void logic(Level& level) = 0;
    /*!
        \brief Получить тип сущности.
        \return Тип сущности (\c TypeEntity).
    */
    [[nodiscard]] std::string get_typeEntity();

    /*!
        \brief Получить текущее количество очков времени.
        \return Текущее количество очков времени.
    */
    [[nodiscard]] int get_timePoint();

    /*!
        \brief Получить максимальное количество очков времени.
        \return Максимальное количество очков времени.
    */
    [[nodiscard]] int get_maxTimePoint();

    /*!
        \brief Получить радиус обзора сущности.
        \return Радиус обзора сущности.
    */
    [[nodiscard]] int get_viewRadius();

    /*!
        \brief Получить максимальное здоровье сущности.
        \return Максимальное здоровье сущности.
    */
    [[nodiscard]] int get_maxHP();

    /*!
        \brief Получить текущее здоровье сущности.
        \return Текущее здоровье сущности.
    */
    [[nodiscard]] int get_HP();

    /*!
        \brief Получить скорость сущности.
        \return Скорость сущности.
    */
    [[nodiscard]] int get_speed();

    /*!
        \brief Получить команду сущности.
        \return Команда сущности (\c Team).
    */
    [[nodiscard]] Team get_team();

    /*!
        \brief Получить имя сущности.
        \return Имя сущности.
    */
    [[nodiscard]] std::string& get_name();

    /*!
        \brief Получить текущую позицию сущности.
        \return Указатель на текущую ячейку сущности (\c std::shared_ptr<Cell>).
    */
    [[nodiscard]] std::shared_ptr<Cell> get_position();

    /*!
        \brief Установить текущее количество очков времени.
        \param timePoint Новое значение очков времени.
        \return Ссылка на текущий объект.
    */
    Entity& set_timePoint(int timePoint);

    /*!
        \brief Установить текущее здоровье сущности.
        \param HP Новое значение здоровья.
        \return Ссылка на текущий объект.
    */
    Entity& set_HP(int HP);

    /*!
        \brief Установить позицию сущности.
        \param position Новая позиция сущности (\c std::shared_ptr<Cell>).
        \return Ссылка на текущий объект.
    */
    Entity& set_position(std::shared_ptr<Cell> position);

    /*!
        \brief Получить список видимых сущностей.
        \param listEntity Список всех сущностей.
        \return Список видимых сущностей.
    */
    std::vector<std::shared_ptr<Entity>> visiable_Entity(Vector<Vector<std::shared_ptr<Cell>>>& field, std::vector<std::shared_ptr<Entity>> listEntity);

    /*!
        \brief Создать JSON-объект, представляющий сущность.
        \param jEntity JSON-объект для заполнения.
        \return Ссылка на JSON-объект.
    */
    virtual nlohmann::json& make_json(nlohmann::json& jEntity) = 0;

    /*!
        \brief Переместить сущность на новую позицию.
        \param field Игровое поле.
        \param newPosition Новая позиция сущности.
    */
    void makeStep(Level& level, std::shared_ptr<Cell>& newPosition);

    /*!
        \brief Конструктор класса \c Entity.
        \param typeEntity Тип сущности.
        \param name Имя сущности.
        \param team Команда сущности.
        \param speed Скорость сущности.
        \param HP Текущее здоровье сущности.
        \param maxHP Максимальное здоровье сущности.
        \param viewRadius Радиус обзора сущности.
        \param maxTimePoint Максимальное количество очков времени.
        \param timePoint Текущее количество очков времени.
        \param position Позиция сущности.
    */
    Entity(std::string typeEntity,
           std::string name,
           Team team,
           int speed,
           int HP,
           int maxHP,
           int viewRadius,
           int maxTimePoint,
           int timePoint,
           std::shared_ptr<Cell> position)
        : _typeEntity(typeEntity), _name(name), _team(team), _speed(speed),
          _HP(HP), _maxHP(maxHP), _viewRadius(viewRadius), _maxTimePoint(maxTimePoint), _timePoint(timePoint),
          _position(position) {}

    virtual void makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy) = 0;
    /*!
        \brief Деструктор по умолчанию.
    */
    virtual ~Entity() = default;
    virtual void update_menu(std::shared_ptr<Entity> entity, sf::Text& Text) {}
    virtual void menu_button_pressed(Game_stat& Stat, sf::Event& event, Game_texts& Text, Level& level) {}
};

#endif