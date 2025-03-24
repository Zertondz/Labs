#ifndef FACTORIES
#define FACTORIES

#include <unordered_map>
#include <nlohmann/json.hpp>
#include <string>
#include "Personage.hpp"

/*!
    \file EntityFactoryJson.hpp
    \brief Фабрика для создания объектов типа \c Entity из JSON.

    Этот файл содержит определение класса \c EntityFactoryJson, который позволяет регистрировать и создавать объекты сущностей (\c Entity) на основе их типов (\c TypeEntity) и данных из JSON.
*/

/*!
    \class EntityFactoryJson
    \brief Фабричный класс для создания объектов \c Entity на основе типа и JSON-данных.

    Класс позволяет регистрировать функции создания для различных типов сущностей (\c TypeEntity) и создавать их экземпляры на основе JSON-данных.
*/
class EntityFactoryJson
{
private:
    /*!
        \brief Карта функций создания для разных типов сущностей.

        Ключ — тип сущности (\c TypeEntity), значение — функция, которая создает объект типа \c Entity.
    */
    std::unordered_map<std::string, std::function<std::shared_ptr<Entity>(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity)>> _creators;

public:
    /*!
        \brief Конструктор по умолчанию.

        Регистрирует функции создания для стандартных типов сущностей: \c Oper, \c Smart, \c Wild, \c Forager.
    */
    EntityFactoryJson() = default;
    /*!
        \brief Регистрация функции создания для нового типа сущности.

        Позволяет добавить кастомные типы сущностей и их фабричные методы.

        \param TypeEntity Тип сущности (\c TypeEntity), для которой регистрируется функция создания.
        \param creator Функция, которая создает объект типа \c Entity.
    */
    void registerType(std::string TypeEntity, std::function<std::shared_ptr<Entity>(Vector<Vector<std::shared_ptr<Cell>>>&, nlohmann::json&)> creator)
    {
        _creators[TypeEntity] = creator;
    }

    /*!
        \brief Создание объекта сущности.

        Создает объект типа \c Entity на основе переданных данных.

        \param field Игровое поле, представленное двухмерным вектором указателей на объекты \c Cell.
        \param jEntity JSON-объект, содержащий данные для инициализации сущности.
        \param TypeEntity Тип сущности (\c TypeEntity), которую нужно создать.
        \return Указатель на созданный объект (\c std::shared_ptr<Entity>).
    */
    std::shared_ptr<Entity> create(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity, std::string TypeEntity)
    {
        auto it = _creators.find(TypeEntity);
        return static_cast<std::shared_ptr<Entity>>(it->second(field, jEntity));
    }
};

#endif