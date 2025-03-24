#include "Entity.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include "Cell.hpp"
#include "game_algorithm.hpp"
[[nodiscard]] std::string Entity::get_typeEntity()
{
    return _typeEntity;
}
[[nodiscard]] int Entity::get_timePoint()
{
    return _timePoint;
}
[[nodiscard]] int Entity::get_maxTimePoint()
{
    return _maxTimePoint;
}
[[nodiscard]] int Entity::get_viewRadius()
{
    return _viewRadius;
}
[[nodiscard]] int Entity::get_maxHP()
{
    return _maxHP;
}
[[nodiscard]] int Entity::get_HP()
{
    return _HP;
}
[[nodiscard]] int Entity::get_speed()
{
    return _speed;
}
[[nodiscard]] Team Entity::get_team()
{
    return _team;
}
[[nodiscard]] std::string& Entity::get_name()
{
    return _name;
}
[[nodiscard]] std::shared_ptr<Cell> Entity::get_position()
{
    return _position;
}
Entity& Entity::set_timePoint(int timePoint) 
{
    _timePoint = timePoint;
    return (*this);
}
Entity& Entity::set_HP(int HP)
{
    _HP = HP;
    return (*this);
}
Entity& Entity::set_position(std::shared_ptr<Cell> position)
{
    _position = position;
    return (*this);
}
void Entity::makeStep(Level& level, std::shared_ptr<Cell>& newPosition)
{
    std::vector<Coordinates> path = possibility_of_a_path(level, _position, newPosition, false);
    if(!path.empty())
    {
        if((static_cast<int>(path.size() - 1) * get_speed()) > _timePoint)
        {
            throw std::runtime_error("No Time Point");
        }//else if((path.size() - 1) == 0) throw std::runtime_error("that cell");
        else
        {
            _position = newPosition;
            set_timePoint(get_timePoint() - (path.size() - 1) * get_speed());
        }

    }
    else
    {
        throw std::runtime_error("No Path : (" + std::to_string(_position->get_position().x) + ", " + std::to_string(_position->get_position().x) + ") -> "+
        "(" + std::to_string(newPosition->get_position().x) + ", " + std::to_string(newPosition->get_position().x) + ")");
    }
}

std::vector<std::shared_ptr<Entity>> Entity::visiable_Entity(Vector<Vector<std::shared_ptr<Cell>>>& field, std::vector<std::shared_ptr<Entity>> listEntity)
{
    
    std::vector<std::shared_ptr<Entity>> listE;
    for(size_t i = 0; i < listEntity.size(); i++)
    {
        int x_enemy = listEntity[i]->get_position()->get_position().x, x_this = _position->get_position().x;
        int y_enemy = listEntity[i]->get_position()->get_position().y, y_this = _position->get_position().y;
        if(((x_enemy - x_this) == 0)&&((y_enemy - y_this) == 0))
        {
            continue;
        }
        if((std::pow((x_enemy - x_this),2) + std::pow((y_enemy - y_this),2)) <= std::pow(_viewRadius, 2))
        {
            if(propobility_see(field, _position, listEntity[i]->get_position()))
            {
                listE.push_back(listEntity[i]);
            }
        }
    }
    return listE;
}
