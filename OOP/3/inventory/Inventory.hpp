#ifndef INVENTORY
#define INVENTORY

#include "Items.hpp"

/*!
    \class Inventory
    \brief Класс для управления инвентарем.

    Класс отвечает за хранение и управление предметами, содержащимися в инвентаре. 
    Поддерживает добавление, удаление и получение предметов различных типов. 
    Реализует функционал сериализации в формате JSON.
*/
class Inventory
{
private:
    /*!
        \brief Хранилище предметов.
        \details Вектор, содержащий указатели на объекты типа `Item` и его производных.
    */
    std::vector<std::shared_ptr<Item>> _matrItem;

    /*!
        \brief Текущий вес инвентаря.
        \details Суммарный вес всех предметов, находящихся в инвентаре.
    */
    int _currteWeight;

    /*!
        \brief Текущее количество предметов.
        \details Число предметов, хранящихся в инвентаре.
    */
    int _amountItem;

    /*!
        \brief Конструктор копирования (удалён).
        \details Инвентарь нельзя копировать.
    */
    Inventory(const Inventory&) = delete;

    /*!
        \brief Оператор присваивания (удалён).
        \details Инвентарь нельзя присваивать.
    */
    void operator=(const Inventory&) = delete;

public:
    /*!
        \brief Конструктор по умолчанию.
        \details Создаёт пустой инвентарь с нулевым весом и количеством предметов.
    */
    Inventory() : _matrItem(), _currteWeight(0), _amountItem(0) {}

    /*!
        \brief Деструктор по умолчанию.
        \details Уничтожает объект инвентаря. Используется реализация по умолчанию.
    */
    ~Inventory() = default;

    /*!
        \brief Сериализует инвентарь в формат JSON.
        \param jLCI Объект JSON, куда будет добавлена информация об инвентаре.
        \return Ссылка на обновлённый объект JSON.
    */
    nlohmann::json& InventoryJson(nlohmann::json& jLCI);

    /*!
        \brief Добавляет предмет в инвентарь.
        \param item Указатель на предмет типа `Item` для добавления.
    */
    void addItem(std::shared_ptr<Item> item);

    /*!
        \brief Перемещает предметы из другого инвентаря.
        \param inventory Ссылка на объект инвентаря, предметы из которого будут добавлены.
    */
    void addItems(Inventory& inventory);

    /*!
        \brief Удаляет и возвращает предмет из инвентаря.
        \param position Позиция предмета в инвентаре.
        \return Указатель на удалённый предмет.
    */
    std::shared_ptr<Item> popItem(int position);

    /*!
        \brief Удаляет и возвращает оружие из инвентаря.
        \param position Позиция оружия в инвентаре.
        \return Указатель на удалённое оружие.
    */
    std::shared_ptr<Weapon> popWeapon(int position);

    /*!
        \brief Удаляет и возвращает аптечку из инвентаря.
        \param position Позиция аптечки в инвентаре.
        \return Указатель на удалённую аптечку.
    */
    std::shared_ptr<FirstAidKit> popFirstAidKit(int position);

    /*!
        \brief Удаляет и возвращает контейнер с патронами из инвентаря.
        \param position Позиция контейнера в инвентаре.
        \return Указатель на удалённый контейнер с патронами.
    */
    std::shared_ptr<CaseBullets> popCaseBullets(int position);

    /*!
        \brief Возвращает оружие из инвентаря по указанной позиции.
        \param position Позиция оружия в инвентаре.
        \return Указатель на объект оружия (константный).
    */
    const std::shared_ptr<Weapon> get_Weapon(int position);

    /*!
        \brief Возвращает аптечку из инвентаря по указанной позиции.
        \param position Позиция аптечки в инвентаре.
        \return Указатель на объект аптечки (константный).
    */
    const std::shared_ptr<FirstAidKit> get_FirstAidKit(int position);

    /*!
        \brief Возвращает контейнер с патронами из инвентаря по указанной позиции.
        \param position Позиция контейнера в инвентаре.
        \return Указатель на объект контейнера с патронами (константный).
    */
    const std::shared_ptr<CaseBullets> get_CaseBullets(int position);

    /*!
        \brief Возвращает список предметов в инвентаре.
        \return Константная ссылка на вектор предметов.
    */
    [[nodiscard]] const std::vector<std::shared_ptr<Item>>& get_matrItem();

    /*!
        \brief Возвращает текущий вес инвентаря.
        \return Текущий вес инвентаря.
    */
    [[nodiscard]] int get_currteWeight();

    /*!
        \brief Возвращает текущее количество предметов в инвентаре.
        \return Количество предметов.
    */
    [[nodiscard]] int get_amountItem();
};

#endif