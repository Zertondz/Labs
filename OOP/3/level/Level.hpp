#ifndef LEVEL
#define LEVEL

#include "Cell.hpp"
#include "iterator_v.hpp"
#include "Vector.hpp"
#include "Entity.hpp"
/*!
    \class Level
    \brief Основной класс игры.

    Класс отвечает за управление игровым полем, активной командой и списком сущностей.
    Позволяет работать с состоянием игры, изменять размеры поля, загружать и сохранять состояние.

    \details
    - Хранит игровое поле в виде прямоугольной матрицы клеток.
    - Поддерживает управление активной командой.
    - Предоставляет доступ к списку всех сущностей на карте.

    Использует пользовательскую реализацию вектора `Vector` для хранения игрового поля.
*/
class Level
{
private:
    /*!
        \brief Игровое поле.
        \details Матрица клеток, каждая из которых представляет отдельный участок игрового поля.
        Использует пользовательскую реализацию контейнера `Vector` для матрицы.
    */
    Vector<Vector<std::shared_ptr<Cell>>> _field;
    
    /*!
        \brief Активная команда.
        \details Хранит текущую команду, которая выполняет свои действия в данный момент.
    */
    Team _activeTeam;

    /*!
        \brief Список всех существ на карте.
        \details Хранит ссылки на всех существ (игроков и врагов) в игре.
    */
    std::vector<std::shared_ptr<Entity>> _listEntity;
    
public:
    std::mutex _listEntity_mutex;
    std::mutex _field_mutex;
    /*!
        \brief Конструктор по умолчанию.
        \details Создает объект класса `Level` с пустым игровым полем и списком сущностей.
    */
    Level();

    /*!
        \brief Конструктор из файла.
        \param file_Name Имя файла, из которого загружается состояние уровня.
        \details Загружает состояние игрового поля, активной команды и списка сущностей из указанного файла.
    */
    Level(std::string file_Name);

    /*!
        \brief Деструктор по умолчанию.
        \details Освобождает ресурсы, связанные с объектом уровня.
    */
    ~Level() = default;

    /*!
        \brief Устанавливает активную команду.
        \param team Новая активная команда.
        \return Ссылка на текущий объект `Level` для цепочного вызова.
    */
    Level& set_activeTeam(Team team);

    /*!
        \brief Возвращает текущую активную команду.
        \return Объект команды `Team`.
    */
    [[nodiscard]] Team get_activeTeam();

    /*!
        \brief Возвращает ссылку на игровое поле.
        \return Матрица клеток типа `Vector<Vector<std::shared_ptr<Cell>>>`.
    */
    [[nodiscard]] Vector<Vector<std::shared_ptr<Cell>>>& get_field();

    /*!
        \brief Возвращает ссылку на список всех сущностей.
        \return Вектор сущностей типа `std::vector<std::shared_ptr<Entity>>`.
    */
    [[nodiscard]] std::vector<std::shared_ptr<Entity>>& get_listEntity();

    /*!
        \brief Изменяет размер игрового поля.
        \param x Новое количество строк игрового поля.
        \param y Новое количество столбцов игрового поля.
        \details Увеличивает или уменьшает размер матрицы `_field`. При увеличении добавляются новые клетки.
    */
    void resizeField(int x, int y);

    /*!
        \brief Сохраняет состояние уровня в файл.
        \param file_Name Имя файла, в который сохраняется состояние уровня.
        \details Сохраняет текущее состояние игрового поля, активной команды и списка сущностей в указанный файл.
    */
    void save(std::string file_Name);
};

#endif