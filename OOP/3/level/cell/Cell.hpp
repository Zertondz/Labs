#ifndef CELL
#define CELL

#include "Inventory.hpp"
#include <mutex>
/*!
    \enum TypeCell
    \brief Типы клеток игрового поля.
    
    Определяет возможные типы клеток, которые могут присутствовать на игровом поле:
    - `field`: Обычное поле, по которому можно передвигаться.
    - `wall`: Стена, которая блокирует движение.
    - `glass`: Стеклянная клетка.
    - `partition`: Перегородка.
    - `storagePoint`: Точка хранения предметов.
*/
enum class TypeCell { field, wall, glass, partition, storagePoint };

/*!
    \struct Coordinates
    \brief Координаты клетки на игровом поле.
    
    Структура для хранения позиции клетки в виде координат `(x, y)`.

    \details Поддерживает сравнение двух объектов типа `Coordinates` на равенство.
*/
typedef struct Coordinates {
    int x; ///< Координата X.
    int y; ///< Координата Y.

    /*!
        \brief Оператор сравнения на равенство.
        \param rhs Другой объект типа `Coordinates` для сравнения.
        \return `true`, если координаты совпадают; иначе `false`.
    */
    bool operator==(const Coordinates& rhs) const
    {
        return ((x == rhs.x) && (y == rhs.y));
    }

} Coordinates;
namespace std {
template <>
    struct hash<Coordinates> {
        size_t operator()(const Coordinates& coords) const {
            return hash<int>()(coords.x) ^ (hash<int>()(coords.y) << 1);
        }
    };
}
/*!
    \class Cell
    \brief Представляет клетку игрового поля.
    
    Класс описывает свойства клетки на игровом поле, включая её тип, список предметов, 
    координаты и статус посещённости.
*/
class Cell
{
private:
    /*!
        \brief Тип клетки.
        \details Определяет, является ли клетка полем, стеной, точкой хранения или другим типом.
    */
    TypeCell _typeCell;

    /*!
        \brief Инвентарь клетки.
        \details Содержит список предметов, которые находятся в данной клетке.
    */
    Inventory _listItems;

    /*!
        \brief Координаты клетки.
        \details Указывает положение клетки на игровом поле.
    */
    Coordinates _position;

public:
    std::mutex cell_mutex;
    /*!
        \brief Конструктор по умолчанию.
        \details Создаёт клетку типа `field` с пустым инвентарём и координатами `(0, 0)`.
    */
    Cell() : _typeCell(TypeCell::field), _listItems(), _position{0, 0} {}

    /*!
        \brief Конструктор с параметрами.
        \param TypeCell Тип клетки.
        \param position Координаты клетки.
        \details Создаёт клетку с заданным типом и координатами. Инвентарь изначально пустой.
    */
    Cell(TypeCell TypeCell, Coordinates position) 
        : _typeCell(TypeCell), _listItems(), _position(position) {}

    /*!
        \brief Возвращает тип клетки.
        \return Тип клетки (`TypeCell`).
    */
    [[nodiscard]] TypeCell get_typeCell();

    /*!
        \brief Возвращает ссылку на инвентарь клетки.
        \return Ссылка на объект инвентаря (`Inventory&`).
    */
    [[nodiscard]] Inventory& get_listItems();

    /*!
        \brief Возвращает координаты клетки.
        \return Ссылка на объект координат (`Coordinates&`).
    */
    [[nodiscard]] Coordinates& get_position();

    /*!
        \brief Устанавливает тип клетки.
        \param typeCell Новый тип клетки.
        \return Ссылка на текущий объект `Cell` для цепочного вызова.
    */
    Cell& set_typecell(TypeCell typeCell);

    /*!
        \brief Деструктор по умолчанию.
        \details Уничтожает объект клетки. Используется реализация по умолчанию.
    */
    ~Cell() = default;
};

#endif