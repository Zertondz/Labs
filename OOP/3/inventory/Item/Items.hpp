#ifndef ITEMS
#define ITEMS

#include <nlohmann/json.hpp>

/*!
    \enum WeaponType
    \brief Перечисление типов оружия.

    Описывает возможные типы оружия, используемого в игре.
*/
enum class WeaponType {
    shotgun,    /*!< Дробовик */
    revolver,   /*!< Револьвер */
    rifle,      /*!< Винтовка */
    pistol,     /*!< Пистолет */
    none        /*!< Отсутствие оружия */
};

/*!
    \enum ItemType
    \brief Перечисление типов предметов.

    Описывает возможные типы предметов, доступных в игре.
*/
enum class ItemType {
    weapon,         /*!< Оружие */
    firstAidKit,    /*!< Аптечка */
    caseBullets     /*!< Контейнер с патронами */
};

/*!
    \class Item
    \brief Базовый класс для всех игровых предметов.

    Класс представляет общие свойства всех предметов, такие как имя, тип и вес, и включает виртуальный метод для сериализации в формат JSON.
*/
class Item {
protected:
    std::string _itemName;     /*!< Имя предмета */
    ItemType _itemType;        /*!< Тип предмета */
    const int _itemHeavy;      /*!< Вес предмета */

public:
    /*!
        \brief Получить имя предмета.
        \return Ссылка на строку с именем предмета.
    */
    [[nodiscard]] const std::string& get_itemName();

    /*!
        \brief Получить вес предмета.
        \return Вес предмета в целых числах.
    */
    [[nodiscard]] int get_itemHeavy();

    /*!
        \brief Получить тип предмета.
        \return Значение перечисления \c ItemType.
    */
    [[nodiscard]] ItemType get_itemType();

    /*!
        \brief Создать JSON-представление предмета.

        Этот метод должен быть переопределён в дочерних классах для создания соответствующего JSON-объекта.
        \param jItems Ссылка на JSON-объект для заполнения данными.
        \return JSON-объект с информацией о предмете.
    */
    virtual nlohmann::json& make_json(nlohmann::json& jItems) = 0;

    /*!
        \brief Конструктор по умолчанию.

        Инициализирует предмет с именем "No name", типом \c ItemType::firstAidKit и весом 0.
    */
    Item() : _itemName("No name"), _itemType(ItemType::firstAidKit), _itemHeavy(0) {}

    /*!
        \brief Конструктор с параметрами.

        Позволяет задать имя, тип и вес предмета.
        \param itemName Имя предмета.
        \param itemType Тип предмета (значение из перечисления \c ItemType).
        \param itemHeavy Вес предмета.
    */
    Item(std::string itemName, ItemType itemType, int itemHeavy)
        : _itemName(itemName), _itemType(itemType), _itemHeavy(itemHeavy) {}

    /*!
        \brief Виртуальный деструктор.

        Обеспечивает корректное удаление объектов дочерних классов.
    */
    ~Item() = default;
};

/*!
    \class FirstAidKit
    \brief Класс для представления аптечки в игре.

    Аптечка является разновидностью предмета и используется для восстановления здоровья.
*/
class FirstAidKit : public Item {
private:
    const int _healthRecover; /*!< Количество восстанавливаемого здоровья. */
    const int _timePoint;     /*!< Время действия аптечки в игровых единицах времени. */

public:
    /*!
        \brief Получить количество восстанавливаемого здоровья.
        \return Количество здоровья, которое восстанавливает аптечка.
    */
    [[nodiscard]] int get_healthRecover();

    /*!
        \brief Получить время действия аптечки.
        \return Время действия аптечки в игровых единицах.
    */
    [[nodiscard]] int get_timePoint();

    /*!
        \brief Создать JSON-представление аптечки.

        Создает объект JSON, содержащий информацию об аптечке, включая её имя, тип, вес, восстановление здоровья и время действия.
        \param jItems Ссылка на JSON-объект для заполнения данными.
        \return JSON-объект с информацией об аптечке.
    */
    nlohmann::json& make_json(nlohmann::json& jItems) override;

    /*!
        \brief Конструктор аптечки.

        Инициализирует аптечку с заданными параметрами.
        \param itemName Имя аптечки.
        \param itemType Тип предмета (значение из перечисления \c ItemType).
        \param itemHeavy Вес аптечки.
        \param healthRecover Количество здоровья, которое восстанавливает аптечка.
        \param timePoint Время действия аптечки в игровых единицах.
    */
    FirstAidKit(std::string itemName,
                ItemType itemType,
                int itemHeavy,
                int healthRecover,
                int timePoint)
        : Item(itemName, itemType, itemHeavy), 
          _healthRecover(healthRecover), 
          _timePoint(timePoint) {}

    /*!
        \brief Деструктор аптечки.

        Обеспечивает корректное удаление объекта аптечки.
    */
    ~FirstAidKit() = default;
};

/*!
    \class CaseBullets
    \brief Класс для представления патронтажа в игре.

    Патронтаж является разновидностью предмета и используется для хранения боеприпасов определённого типа.
*/
class CaseBullets : public Item {
private:
    int _amountBullet; /*!< Количество боеприпасов в патронтаже. */
    int _caseSize;     /*!< Максимальная вместимость патронтажа. */
    WeaponType _bulletType; /*!< Тип боеприпасов, хранимых в патронтаже (например, дробовик, револьвер и т.д.). */

public:
    /*!
        \brief Получить максимальную вместимость патронтажа.
        \return Максимальное количество боеприпасов, которое может содержаться в патронтаже.
    */
    [[nodiscard]] int get_caseSize();

    /*!
        \brief Получить текущее количество боеприпасов в патронтаже.
        \return Количество боеприпасов в патронтаже.
    */
    [[nodiscard]] int get_amountBullet();

    /*!
        \brief Получить тип боеприпасов в патронтаже.
        \return Тип боеприпасов (значение из перечисления \c WeaponType).
    */
    [[nodiscard]] WeaponType get_bulletType();

    /*!
        \brief Установить количество боеприпасов в патронтаже.

        Устанавливает новое значение для количества боеприпасов. 
        Если значение превышает вместимость патронтажа, количество боеприпасов будет ограничено \c _caseSize.
        \param amount_Bullets Новое количество боеприпасов.
        \return Ссылка на текущий объект \c CaseBullets для цепочного вызова методов.
    */
    CaseBullets& set_amountBullets(int amount_Bullets);

    /*!
        \brief Создать JSON-представление патронтажа.

        Создает объект JSON, содержащий информацию о патронтаже, включая имя, тип, вес, вместимость, количество и тип боеприпасов.
        \param jItems Ссылка на JSON-объект для заполнения данными.
        \return JSON-объект с информацией о патронтаже.
    */
    nlohmann::json& make_json(nlohmann::json& jItems) override;

    /*!
        \brief Конструктор патронтажа.

        Инициализирует патронтаж с заданными параметрами.
        \param itemName Имя патронтажа.
        \param itemType Тип предмета (значение из перечисления \c ItemType).
        \param itemHeavy Вес патронтажа.
        \param amountBullet Количество боеприпасов в патронтаже.
        \param caseSize Максимальная вместимость патронтажа.
        \param bulletType Тип боеприпасов в патронтаже (значение из перечисления \c WeaponType).
    */
    CaseBullets(std::string itemName,
                ItemType itemType,
                int itemHeavy,
                int amountBullet,
                int caseSize,
                WeaponType bulletType)
        : Item(itemName, itemType, itemHeavy), 
          _amountBullet(amountBullet), 
          _caseSize(caseSize), 
          _bulletType(bulletType) {}

    /*!
        \brief Деструктор патронтажа.

        Обеспечивает корректное удаление объекта патронтажа.
    */
    ~CaseBullets() = default;
};
/*!
    \class Weapon
    \brief Класс для представления оружия в игре.

    Оружие является разновидностью предмета, использующего боеприпасы для нанесения урона.
*/
class Weapon : public Item {
private:
    WeaponType _bulletType; /*!< Тип боеприпасов, используемых оружием (например, дробовик, револьвер и т.д.). */
    int _timeShoot;         /*!< Время, необходимое для одного выстрела (в игровых единицах). */
    int _baseDamage;        /*!< Базовый урон, наносимый оружием за один выстрел. */
    int _shootsPerRound;    /*!< Количество выстрелов за один игровой раунд. */
    int _timeReload;        /*!< Время, необходимое для перезарядки оружия. */
    int _cartridgeSize;     /*!< Размер магазина оружия. */
    int _shootsLeft;        /*!< Количество оставшихся выстрелов в магазине. */

public:
    /*!
        \brief Получить время выстрела.
        \return Время, необходимое для одного выстрела.
    */
    [[nodiscard]] int get_timeShoot();

    /*!
        \brief Получить базовый урон оружия.
        \return Базовый урон за один выстрел.
    */
    [[nodiscard]] int get_baseDamage();

    /*!
        \brief Получить количество выстрелов за один раунд.
        \return Количество выстрелов за раунд.
    */
    [[nodiscard]] int get_shootsPerRound();

    /*!
        \brief Получить время перезарядки.
        \return Время, необходимое для полной перезарядки.
    */
    [[nodiscard]] int get_timeReload();

    /*!
        \brief Получить размер магазина оружия.
        \return Размер магазина.
    */
    [[nodiscard]] int get_cartridgeSize();

    /*!
        \brief Получить тип боеприпасов, используемых оружием.
        \return Тип боеприпасов (значение из перечисления \c WeaponType).
    */
    [[nodiscard]] WeaponType get_bulletType();

    /*!
        \brief Получить количество оставшихся выстрелов.
        \return Количество оставшихся выстрелов в магазине.
    */
    [[nodiscard]] int get_shootsLeft();

    /*!
        \brief Установить количество оставшихся выстрелов в магазине.
        \param amount_shoots Новое количество выстрелов.
        \return Ссылка на текущий объект \c Weapon для цепочного вызова методов.
    */
    Weapon& set_shootsLeft(int amount_shoots);

    /*!
        \brief Перезарядить оружие с использованием указанного патронтажа.

        Пополняет магазин оружия до максимального размера (\c _cartridgeSize), 
        уменьшая количество боеприпасов в указанном патронтаже.
        \param caseB Указатель на патронтаж, содержащий боеприпасы для перезарядки.
    */
    void reload(std::shared_ptr<CaseBullets> caseB);

    /*!
        \brief Выполнить выстрелы из оружия.

        Производит выстрелы из оружия, уменьшая количество оставшихся выстрелов. 
        Если в магазине недостаточно выстрелов для полной очереди, возвращает количество оставшихся выстрелов.
        \return Количество произведенных выстрелов.
    */
    int makeShoots();

    /*!
        \brief Создать JSON-представление оружия.

        Создает объект JSON, содержащий информацию об оружии, включая имя, тип, вес, урон, размер магазина и другие параметры.
        \param jItems Ссылка на JSON-объект для заполнения данными.
        \return JSON-объект с информацией об оружии.
    */
    nlohmann::json& make_json(nlohmann::json& jItems) override;

    /*!
        \brief Конструктор оружия.

        Инициализирует оружие с заданными параметрами.
        \param itemName Имя оружия.
        \param itemType Тип предмета (значение из перечисления \c ItemType).
        \param itemHeavy Вес оружия.
        \param bulletType Тип боеприпасов, используемых оружием.
        \param timeShoot Время выстрела.
        \param baseDamage Базовый урон.
        \param shootsPerRound Количество выстрелов за раунд.
        \param timeReload Время перезарядки.
        \param cartridgeSize Размер магазина.
        \param shootsLeft Количество оставшихся выстрелов в магазине.
    */
    Weapon(std::string itemName,
           ItemType itemType,
           int itemHeavy,
           WeaponType bulletType,
           int timeShoot,
           int baseDamage,
           int shootsPerRound,
           int timeReload,
           int cartridgeSize,
           int shootsLeft)
        : Item(itemName, itemType, itemHeavy),
          _bulletType(bulletType),
          _timeShoot(timeShoot),
          _baseDamage(baseDamage),
          _shootsPerRound(shootsPerRound),
          _timeReload(timeReload),
          _cartridgeSize(cartridgeSize),
          _shootsLeft(shootsLeft) {}

    /*!
        \brief Конструктор по умолчанию.

        Инициализирует оружие с базовыми параметрами (тип боеприпасов — \c none, урон и вместимость равны 0).
    */
    Weapon()
        : Item("none", ItemType::weapon, 0),
          _bulletType(WeaponType::none),
          _timeShoot(0),
          _baseDamage(0),
          _shootsPerRound(0),
          _timeReload(0),
          _cartridgeSize(0),
          _shootsLeft(0) {}

    /*!
        \brief Деструктор оружия.

        Обеспечивает корректное удаление объекта оружия.
    */
    ~Weapon() = default;
};


#endif