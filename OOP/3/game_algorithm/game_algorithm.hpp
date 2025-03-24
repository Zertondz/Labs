#ifndef GAMEA
#define GAMEA

#include "Vector.hpp"
#include "Cell.hpp"
#include "Level.hpp"
/*!
    \file GameActions.hpp
    \brief Заголовочный файл для реализации игровых действий, таких как перемещение, стрельба и работа с инвентарем.

    Этот файл содержит функции, связанные с игровой механикой, включая проверку доступности пути, возможность стрельбы и работу с JSON-представлением данных.
*/

/*!
    \brief Определение возможных путей для перемещения.

    Проверяет возможность перемещения между указанными ячейками на игровом поле и возвращает список координат доступных путей.
    
    \param field Игровое поле, представленное двухмерным вектором указателей на объекты \c Cell.
    \param oldPosition Указатель на текущую позицию.
    \param newPosition Указатель на целевую позицию.
    \return Список координат (\c std::vector<Coordinates>) возможных путей для перемещения.
*/
std::vector<Coordinates> possibility_of_a_path(
    Level& level, 
    std::shared_ptr<Cell> oldPosition, 
    std::shared_ptr<Cell> newPosition,
    bool flag_entity_position_enable
);

/*!
    \brief Проверка возможности стрельбы по врагу.

    Определяет, можно ли произвести выстрел по указанной позиции врага, основываясь на точности и расположении.
    
    \param field Игровое поле, представленное двухмерным вектором указателей на объекты \c Cell.
    \param oldPosition Указатель на текущую позицию стреляющего.
    \param enemyPosition Указатель на позицию врага.
    \param accuracy Точность выстрела (в процентах или иной шкале).
    \return \c true, если стрельба возможна; \c false, если стрельба невозможна.
*/
bool possibility_of_a_shoot(
    Vector<Vector<std::shared_ptr<Cell>>>& field, 
    std::shared_ptr<Cell> oldPosition, 
    std::shared_ptr<Cell> enemyPosition, 
    int accuracy
);

/*!
    \brief Преобразование списка координат в JSON-формат.

    Конвертирует список координат в JSON-объект для сохранения или передачи данных.
    
    \param list Список координат (\c std::vector<Coordinates>), который нужно преобразовать.
    \param list_stpot JSON-объект, в который записываются координаты.
    \return Ссылка на заполненный JSON-объект.
*/
nlohmann::json& ListJson(
    std::vector<Coordinates>& list, 
    nlohmann::json& list_stpot
);

/*!
    \brief Преобразование JSON-формата в инвентарь.

    Создает инвентарь из JSON-представления, включая информацию о предметах и их количестве.
    
    \param inventory Объект инвентаря (\c Inventory), который нужно преобразовать.
    \param jItems JSON-объект для записи информации о предметах.
    \param amountitems Количество предметов, которые нужно учесть.
    \return Ссылка на объект \c Inventory с добавленным JSON-представлением.
*/
Inventory& makeInvntoeyJson(
    Inventory& inventory, 
    nlohmann::json& jItems, 
    int amountitems
);
std::vector<Coordinates> gen_nearby_cell(Level& level, Coordinates old_position, bool entity_enable);
bool propobility_see(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Cell> startPosition, std::shared_ptr<Cell> endPosition);
std::vector<std::pair<int, int>> gen_visible_cell(Level& level, Coordinates start_position, int viewRadius);
#endif