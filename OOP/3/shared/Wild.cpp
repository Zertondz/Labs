#include "Personage.hpp"
#include "game_algorithm.hpp"

[[nodiscard]] int Wild::get_accuracy()
{
    return _accuracy;
}
[[nodiscard]] int Wild::get_minCombatDamage()
{
    return _minCombatDamage;
}
[[nodiscard]] int Wild::get_timeShoot()
{
    return _timeShoot;
}
nlohmann::json& Wild::make_json(nlohmann::json& jEntity)
{
    jEntity["typeEntity"] = _typeEntity;
    jEntity["name"] = _name;
    jEntity["team"] = _team;
    jEntity["speed"] = _speed;
    jEntity["HP"] = _HP;
    jEntity["maxHP"] = _maxHP;
    jEntity["viewRadius"] = _viewRadius;
    jEntity["maxTimePoint"] = _maxTimePoint;
    jEntity["timePoint"] = _timePoint;
    jEntity["position"] = {_position->get_position().x, _position->get_position().y};
    jEntity["accuracy"] = _accuracy;
    jEntity["minCombatDamage"] = _minCombatDamage;
    return jEntity;
}

Wild::Wild(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) : 
        Entity(jEntity["typeEntity"], 
        jEntity["name"], 
        Team(jEntity["team"]), 
        jEntity["speed"], 
        jEntity["HP"], 
        jEntity["maxHP"], 
        jEntity["viewRadius"], 
        jEntity["maxTimePoint"], 
        jEntity["timePoint"], 
        field[jEntity["position"][0]][jEntity["position"][1]]),
        _accuracy(jEntity["accuracy"]), _minCombatDamage(jEntity["minCombatDamage"]){}

void Wild::makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy)
{
    if((get_timePoint() - _timeShoot) < 0)
    {
        throw std::runtime_error("No Time Point");
    }
    if((std::abs(enemy->get_position()->get_position().x - _position->get_position().x) >= 2)||(std::abs(enemy->get_position()->get_position().y - _position->get_position().y) >= 2))
    {
        throw std::runtime_error("No Entity nearby");
    }
    if(possibility_of_a_shoot(field, _position, enemy->get_position(), _accuracy))
    {
        int new_HP = enemy->get_HP() - _minCombatDamage;
        if(new_HP < 0){new_HP = 0;}
        enemy->set_HP(new_HP);
        set_timePoint(get_timePoint() - _timeShoot);
    }
    else
    {
        set_timePoint(get_timePoint() - _timeShoot);
        throw std::runtime_error("Lose");
    }
}
void Wild::logic(Level& level)
{
    int min_i = -1;
    int min_path = 10e+8;
    int i_o = -1;
    for(auto entity : level.get_listEntity())
    {
        i_o++;
        if(entity->get_team() == Team::Radiant)
        {
            std::vector<Coordinates> path(possibility_of_a_path(level, get_position(), get_position(), false));
            if(min_path > static_cast<int>(path.size()))
            {
                min_i = i_o;
                min_path = path.size();
            }
        }
    }
    if(min_i == -1)
    {
        throw std::runtime_error("Нет врагов");
    }
    std::vector<Coordinates> neibors = gen_nearby_cell(level, level.get_listEntity()[min_i]->get_position()->get_position(), false);
    std::unordered_map<Coordinates, std::vector<Coordinates>> neibors_path;
    int min_path_size = 10e+8;
    Coordinates target;
    for(auto neibor : neibors)
    {
        neibors_path[neibor] = possibility_of_a_path(level, get_position(), level.get_field()[neibor.x][neibor.y], false);
    }
    for(auto neibor : neibors)
    {
        if(min_path_size > static_cast<int>(neibors_path[neibor].size()))
        {
            min_path_size = neibors_path[neibor].size();
            target = neibor;
        }
    }
    for(auto cell : neibors_path[target])
    {
        try
        {
            makeStep(level, level.get_field()[cell.x][cell.y]);
        }
        catch(...){ break;}
    }
    while(get_timePoint() != 0)
    {
        try
        {
            makeShoot(level.get_field(), level.get_listEntity()[min_i]);
        }
        catch(...){ break;}
    }
}