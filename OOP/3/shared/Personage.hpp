#ifndef PERSONAGE
#define PERSONAGE

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
class Gentity;
/*!
    \class Wild
    \brief Класс, представляющий диких существ, наследует от \c Entity.

    Данный класс описывает поведение диких существ в игре, которые могут стрелять по врагам, обладают точностью и минимальным уроном в бою.
*/
class Wild : public Entity
{
private:
    int _accuracy;           /*!< Точность стрельбы сущности. */
    int _minCombatDamage;    /*!< Минимальный урон от атаки сущности. */
    int _timeShoot = 3;          /*!< Время на выстрел. */

public:
    void logic(Level& level) override;
    /*!
        \brief Получить точность стрельбы.
        \return Точность стрельбы сущности.
    */
    [[nodiscard]] int get_accuracy();

    /*!
        \brief Получить минимальный урон.
        \return Минимальный урон, который может нанести сущность.
    */
    [[nodiscard]] int get_minCombatDamage();

    /*!
        \brief Получить время на выстрел.
        \return Время на выстрел для этой сущности.
    */
    [[nodiscard]] int get_timeShoot();

    /*!
        \brief Создать JSON-представление сущности.
        \param jEntity JSON-объект для сохранения информации.
        \return Ссылка на измененный JSON-объект.
    */
    nlohmann::json& make_json(nlohmann::json& jEntity) override;

    /*!
        \brief Конструктор класса \c Wild.
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
        \param accuracy Точность стрельбы.
        \param minCombatDamage Минимальный урон от атаки.
    */
    Wild(std::string typeEntity,
         std::string name,
         Team team,
         int speed,
         int HP,
         int maxHP,
         int viewRadius,
         int maxTimePoint,
         int timePoint,
         std::shared_ptr<Cell> position,
         int accuracy,
         int minCombatDamage)
        : Entity(typeEntity, name, team, speed, HP, maxHP, viewRadius, maxTimePoint, timePoint, position),
          _accuracy(accuracy), _minCombatDamage(minCombatDamage) {}

    /*!
        \brief Конструктор класса \c Wild, который загружает сущность из JSON-объекта.
        \param field Игровое поле.
        \param jEntity JSON-объект, содержащий данные сущности.
    */
    Wild(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity);

    /*!
        \brief Сделать выстрел по врагу.
        \param field Игровое поле, где происходят выстрелы.
        \param enemy Враг, по которому будет произведен выстрел.
    */
    void makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy) override;

    /*!
        \brief Деструктор класса \c Wild.
    */
    ~Wild() = default;
};


/*!
    \class Smart
    \brief Класс, представляющий умных существ, наследует от \c Entity.

    Этот класс описывает умных существ, которые могут иметь оружие, а также точность стрельбы и минимальный урон в бою. Умные существа могут подбирать и сбрасывать оружие, а также атаковать врагов.
*/
class Smart : public Entity
{
private:
    std::shared_ptr<Weapon> _curretWeapon;            /*!< Текущее оружие сущности. */
    std::vector<Coordinates> _listStoragePoint;       /*!< Местоположения, где хранятся оружие и другие предметы. */
    int _accuracy;                                    /*!< Точность стрельбы сущности. */

public:
    void logic(Level& level) override;
    /*!
        \brief Получить точность стрельбы.
        \return Точность стрельбы сущности.
    */
    [[nodiscard]] int get_accuracy();

    /*!
        \brief Получить список точек хранения.
        \return Список точек хранения для предметов.
    */
    [[nodiscard]] std::vector<Coordinates>& get_listStoragePoint();

    /*!
        \brief Получить текущее оружие.
        \return Указатель на текущее оружие сущности.
    */
    [[nodiscard]] std::shared_ptr<Weapon> get_curretWeapon();

    /*!
        \brief Подобрать оружие.
        Данный метод позволяет сущности подобрать оружие, если оно находится в одном из мест хранения.
    */
    void pickUPWeapon();

    /*!
        \brief Отбросить оружие.
        Данный метод позволяет сущности отбросить текущее оружие, если оно есть.
    */
    void dropWeapon();

    /*!
        \brief Создать JSON-представление сущности.
        \param jEntity JSON-объект для сохранения информации.
        \return Ссылка на измененный JSON-объект.
    */
    nlohmann::json& make_json(nlohmann::json& jEntity) override;

    /*!
        \brief Конструктор класса \c Smart.
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
        \param accuracy Точность стрельбы.
        \param minCombatDamage Минимальный урон от атаки.
        \param curretWeapon Указатель на текущее оружие.
        \param listStoragePoint Список точек хранения предметов.
    */
    Smart(std::string typeEntity,
          std::string name,
          Team team,
          int speed,
          int HP,
          int maxHP,
          int viewRadius,
          int maxTimePoint,
          int timePoint,
          std::shared_ptr<Cell> position,
          int accuracy,
          std::shared_ptr<Weapon> curretWeapon,
          std::vector<Coordinates>& listStoragePoint)
        : Entity(typeEntity, name, team, speed, HP, maxHP, viewRadius, maxTimePoint, timePoint, position),
          _curretWeapon(curretWeapon), _listStoragePoint(listStoragePoint),
          _accuracy(accuracy) {}

    /*!
        \brief Конструктор класса \c Smart, который загружает сущность из JSON-объекта.
        \param field Игровое поле.
        \param jEntity JSON-объект, содержащий данные сущности.
    */
    Smart(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity);

    /*!
        \brief Сделать выстрел по врагу.
        \param field Игровое поле, где происходят выстрелы.
        \param enemy Враг, по которому будет произведен выстрел.
    */
    void makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy) override;

    /*!
        \brief Деструктор класса \c Smart.
    */
    ~Smart() = default;
};


/*!
    \class Forager
    \brief Класс, представляющий существа, занимающиеся сбором предметов и их хранением. Наследует от \c Entity.

    Этот класс описывает существа, которые могут собирать оружие и другие предметы в инвентарь, а также имеют определенные точки хранения. Кроме того, они могут подбирать и сбрасывать оружие.
*/
class Forager : public Entity
{
private:
    Inventory _inventory;                        /*!< Инвентарь сущности, хранящий предметы. */
    std::vector<Coordinates> _listStoragePoint;   /*!< Местоположения, где хранятся предметы. */

public:
    void logic(Level& level) override;
    void makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy) override;
    /*!
        \brief Получить инвентарь.
        \return Ссылка на инвентарь сущности.
    */
    [[nodiscard]] Inventory& get_inventory();

    /*!
        \brief Получить список точек хранения.
        \return Ссылка на список точек хранения предметов.
    */
    [[nodiscard]] std::vector<Coordinates>& get_listStoragePoint();

    /*!
        \brief Подобрать оружие.
        Метод позволяет сущности подобрать оружие из одного из мест хранения.
    */
    void pickUPWeapon();

    /*!
        \brief Отбросить оружие.
        Метод позволяет сущности сбросить текущее оружие.
    */
    void dropWeapon();

    /*!
        \brief Создать JSON-представление сущности.
        \param jEntity JSON-объект, куда будет сохранена информация о сущности.
        \return Ссылка на измененный JSON-объект.
    */
    nlohmann::json& make_json(nlohmann::json& jEntity) override;

    /*!
        \brief Конструктор класса \c Forager.
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
        \param listStoragePoint Список точек хранения предметов.
        \param inventory Инвентарь сущности, из которого будут добавлены предметы.
    */
    Forager(std::string typeEntity,
            std::string name,
            Team team,
            int speed,
            int HP,
            int maxHP,
            int viewRadius,
            int maxTimePoint,
            int timePoint,
            std::shared_ptr<Cell> position,
            std::vector<Coordinates>& listStoragePoint,
            Inventory& inventory)
        : Entity(typeEntity, name, team, speed, HP, maxHP, viewRadius, maxTimePoint, timePoint, position),
          _inventory(), _listStoragePoint(listStoragePoint)
    {
        size_t size = inventory.get_matrItem().size();
        for(size_t i = 0; i < size; i++) {
            _inventory.addItem(inventory.popItem(0));
        }
    }

    /*!
        \brief Конструктор класса \c Forager, загружает сущность из JSON.
        \param field Игровое поле.
        \param jEntity JSON-объект, содержащий данные сущности.
    */
    Forager(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity);

    /*!
        \brief Конструктор класса \c Forager.
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
        \param listStoragePoint Список точек хранения предметов.
    */
    Forager(std::string typeEntity,
            std::string name,
            Team team,
            int speed,
            int HP,
            int maxHP,
            int viewRadius,
            int maxTimePoint,
            int timePoint,
            std::shared_ptr<Cell> position,
            std::vector<Coordinates>& listStoragePoint)
        : Entity(typeEntity, name, team, speed, HP, maxHP, viewRadius, maxTimePoint, timePoint, position),
          _inventory(), _listStoragePoint(listStoragePoint) {}

    /*!
        \brief Деструктор класса \c Forager.
    */
    ~Forager() = default;
};


/*!
    \class Oper
    \brief Класс, представляющий оператора с оружием, инвентарем и способностью использовать различные предметы. Наследует от \c Entity.

    Этот класс описывает сущности, которые могут использовать оружие, предметы из инвентаря, а также выполнять действия с боеприпасами и аптечками. Операторы могут подбирать, сбрасывать и использовать различные предметы, а также выбирать оружие для сражений.
*/
class Oper : public Entity
{
private:
    std::shared_ptr<Weapon> _curretWeapon;  /*!< Текущее оружие оператора. */
    Inventory _inventory;                   /*!< Инвентарь оператора. */
    int _accuracy;                          /*!< Точность стрельбы оператора. */
    int _strength;                          /*!< Сила оператора, влияет на урон. */
    int _minCombatDamage;                   /*!< Минимальный боевой урон. */

public:
    void logic(Level& level) override;
    /*!
        \brief Получить точность оператора.
        \return Точность стрельбы оператора.
    */
    [[nodiscard]] int get_accuracy() const;

    /*!
        \brief Получить силу оператора.
        \return Сила оператора, влияющая на урон.
    */
    [[nodiscard]] int get_strength() const;

    /*!
        \brief Получить минимальный боевой урон.
        \return Минимальный боевой урон.
    */
    [[nodiscard]] int get_minCombatDamage() const;

    /*!
        \brief Получить инвентарь оператора.
        \return Ссылка на инвентарь оператора.
    */
    [[nodiscard]] Inventory& get_inventory();

    /*!
        \brief Получить текущее оружие оператора.
        \return Ссылка на текущее оружие оператора.
    */
    [[nodiscard]] std::shared_ptr<Weapon> get_curretWeapon() const;

    /*!
        \brief Подобрать предмет из инвентаря.
        \param num_item Индекс предмета в инвентаре.
    */
    void pickUpItem(int num_item);

    /*!
        \brief Сбросить предмет из инвентаря.
        \param num_item_inventory Индекс предмета в инвентаре для сброса.
    */
    void dropItem(int num_item_inventory);

    /*!
        \brief Сделать выстрел.
        \param field Игровое поле.
        \param enemy Враг, по которому нужно выстрелить.
    */
    void makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy) override;

    /*!
        \brief Использовать боеприпасы.
        \param numItem Индекс предмета с боеприпасами.
    */
    void useCaseBullets(int numItem);

    /*!
        \brief Использовать боеприпасы (по умолчанию используется первый предмет с боеприпасами).
    */
    void useCaseBullets();

    /*!
        \brief Использовать аптечку.
        \param numItem Индекс аптечки в инвентаре.
    */
    void useFirstAidKit(int numItem);

    /*!
        \brief Использовать аптечку (по умолчанию используется первая аптечка).
    */
    void useFirstAidKit();

    /*!
        \brief Выбрать оружие.
        \param numItem Индекс оружия в инвентаре.
    */
    void chooseWeapon(int numItem);

    /*!
        \brief Создать JSON-представление оператора.
        \param jEntity JSON-объект, куда будет сохранена информация о операторе.
        \return Ссылка на измененный JSON-объект.
    */
    nlohmann::json& make_json(nlohmann::json& jEntity) override;

    /*!
        \brief Конструктор класса \c Oper, загружает данные из JSON.
        \param field Игровое поле.
        \param jEntity JSON-объект, содержащий данные о операторе.
    */
    Oper(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity);

    /*!
        \brief Конструктор класса \c Oper.
        \param typeEntity Тип сущности.
        \param name Имя оператора.
        \param team Команда оператора.
        \param speed Скорость оператора.
        \param HP Текущее здоровье оператора.
        \param maxHP Максимальное здоровье оператора.
        \param viewRadius Радиус обзора оператора.
        \param maxTimePoint Максимальное количество очков времени.
        \param timePoint Текущее количество очков времени.
        \param position Позиция оператора.
        \param accuracy Точность стрельбы оператора.
        \param strength Сила оператора.
        \param minCombatDamage Минимальный боевой урон.
        \param curretWeapon Текущее оружие.
    */
    Oper(std::string typeEntity,
         std::string name,
         Team team,
         int speed,
         int HP,
         int maxHP,
         int viewRadius,
         int maxTimePoint,
         int timePoint,
         std::shared_ptr<Cell> position,
         int accuracy,
         int strength,
         int minCombatDamage,
         std::shared_ptr<Weapon> curretWeapon)
        : Entity(typeEntity, name, team, speed, HP, maxHP, viewRadius, maxTimePoint, timePoint, position),
          _curretWeapon(curretWeapon), _inventory(), _accuracy(accuracy), _strength(strength), _minCombatDamage(minCombatDamage) {}

    /*!
        \brief Конструктор класса \c Oper с инвентарем.
        \param typeEntity Тип сущности.
        \param name Имя оператора.
        \param team Команда оператора.
        \param speed Скорость оператора.
        \param HP Текущее здоровье оператора.
        \param maxHP Максимальное здоровье оператора.
        \param viewRadius Радиус обзора оператора.
        \param maxTimePoint Максимальное количество очков времени.
        \param timePoint Текущее количество очков времени.
        \param position Позиция оператора.
        \param accuracy Точность оператора.
        \param strength Сила оператора.
        \param minCombatDamage Минимальный боевой урон.
        \param curretWeapon Текущее оружие.
        \param inventory Инвентарь оператора.
    */
    Oper(std::string typeEntity,
         std::string name,
         Team team,
         int speed,
         int HP,
         int maxHP,
         int viewRadius,
         int maxTimePoint,
         int timePoint,
         std::shared_ptr<Cell> position,
         int accuracy,
         int strength,
         int minCombatDamage,
         std::shared_ptr<Weapon> curretWeapon,
         Inventory& inventory)
        : Entity(typeEntity, name, team, speed, HP, maxHP, viewRadius, maxTimePoint, timePoint, position),
          _curretWeapon(curretWeapon), _inventory(), _accuracy(accuracy), _strength(strength), _minCombatDamage(minCombatDamage)
    {
        size_t size = inventory.get_matrItem().size();
        for(size_t i = 0; i < size; i++) {
            _inventory.addItem(inventory.popItem(0));
        }
    }
    Oper(Oper& oper);
    /*!
        \brief Деструктор класса \c Oper.
    */
    ~Oper() = default;
    void update_menu(std::shared_ptr<Entity> entity, sf::Text& Text) override;
    void menu_button_pressed(Game_stat& Stat, sf::Event& event, Game_texts& Text, Level& level) override;
};
class FAK : public Oper
{
private:
    /* data */
public:
    FAK(std::string typeEntity,
        std::string name,
        Team team,
        int speed,
        int HP,
        int maxHP,
        int viewRadius,
        int maxTimePoint,
        int timePoint,
        std::shared_ptr<Cell> position,
        int accuracy,
        int strength,
        int minCombatDamage,
        std::shared_ptr<Weapon> curretWeapon) : Oper(typeEntity,
        name,
        team,
        speed,
        HP,
        maxHP,
        viewRadius,
        maxTimePoint,
        timePoint,
        position,
        accuracy,
        strength,
        minCombatDamage,
        curretWeapon) {}
    ~FAK() = default;
    FAK(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) :Oper(field, jEntity){}
};
#endif