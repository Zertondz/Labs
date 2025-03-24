#include <random>
#include "Personage.hpp"
#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include "Inventory.hpp"
#include "Cell.hpp"
#include "game_algorithm.hpp"
[[nodiscard]] int Smart::get_accuracy()
{
    return _accuracy;
}
[[nodiscard]] std::vector<Coordinates>& Smart::get_listStoragePoint()
{
    return _listStoragePoint;
}
[[nodiscard]] std::shared_ptr<Weapon> Smart::get_curretWeapon()
{
    return _curretWeapon;
}
void Smart::makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy)
{
    if((get_timePoint() - _curretWeapon->get_timeShoot()) < 0)
    {
        throw std::runtime_error("No Time Point");
    }
    if(_curretWeapon->get_bulletType() == WeaponType::none)
    {
        throw std::runtime_error("No Weapon");
    }
    if(possibility_of_a_shoot(field, _position, enemy->get_position(), _accuracy))
    {
        int new_HP = enemy->get_HP() -_curretWeapon->makeShoots();
        if(new_HP < 0){new_HP = 0;}
        enemy->set_HP(new_HP);
        set_timePoint(get_timePoint() - _curretWeapon->get_timeShoot());
    }
    else
    {
        set_timePoint(get_timePoint() - _curretWeapon->get_timeShoot());
        throw std::runtime_error("Miss");
    }
}
nlohmann::json& Smart::make_json(nlohmann::json& jEntity)
{
    nlohmann::json jItems;
    nlohmann::json list_stpot = nlohmann::json::array();
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
    jEntity["curretWeapon"] = _curretWeapon->make_json(jItems);
    jEntity["listStoragePoint"] = ListJson(_listStoragePoint, list_stpot);
    jEntity["sizeListSP"] = _listStoragePoint.size();
    jEntity["accuracy"] = _accuracy;
    return jEntity;
}
void Smart::pickUPWeapon()
{
    int i = 0;
    bool flag = false;
    for(auto iter = get_position()->get_listItems().get_matrItem().begin(); iter != get_position()->get_listItems().get_matrItem().end(); ++iter,i++)
    {
        if((*iter)->get_itemType() == ItemType::weapon)
        {
            std::shared_ptr<Weapon> WeaponF{std::static_pointer_cast<Weapon>((*iter))};
            if(_curretWeapon->get_bulletType() == WeaponType::none)
            {
                _curretWeapon = WeaponF;
            }
            else
            {
                get_position()->get_listItems().addItem(_curretWeapon);
                _curretWeapon = WeaponF;
            }
            get_position()->get_listItems().popItem(i);
            flag = true;
            break;
        }
    }
    if(!flag)
    {
        throw std::runtime_error("Оружия нет");
    }
}

Smart::Smart(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity) : 
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
    _curretWeapon(std::make_shared<Weapon>(
            jEntity["curretWeapon"]["itemName"],
            ItemType(jEntity["curretWeapon"]["itemType"]),
            jEntity["curretWeapon"]["itemHeavy"],
            WeaponType(jEntity["curretWeapon"]["bulletType"]),
            jEntity["curretWeapon"]["timeShoot"],
            jEntity["curretWeapon"]["baseDamage"],
            jEntity["curretWeapon"]["shootsPerRound"],
            jEntity["curretWeapon"]["timeReload"],
            jEntity["curretWeapon"]["cartridgeSize"],
            jEntity["curretWeapon"]["shootsLeft"])),
    _listStoragePoint(),
    _accuracy(jEntity["accuracy"])
{
    std::vector<Coordinates> listStoragePoint;
    for(int i = 0; i < jEntity["sizeListSP"]; i++)
    {
        listStoragePoint.push_back(Coordinates(jEntity["listStoragePoint"][i][0], jEntity["listStoragePoint"][i][1]));
    }
    _listStoragePoint = listStoragePoint;
}

void Smart::dropWeapon()
{
    if(_curretWeapon->get_bulletType() != WeaponType::none)
    {
        get_position()->get_listItems().addItem(_curretWeapon);
        _curretWeapon = std::make_shared<Weapon>();
    }
    else
    {
        throw std::runtime_error("Нет оружия");
    }
}
void Smart::logic(Level& level)
{
    std::vector<Coordinates> enemy_position;
    for(auto entity : level.get_listEntity()){
        if(entity->get_team() == Team::Radiant){
            enemy_position.push_back(entity->get_position()->get_position());
        }
    }
    while(get_timePoint() != 0)
    {
        bool shoot = false;
        bool not_enough_TP = false;
        std::vector<std::pair<int, int>> visible_cell = gen_visible_cell(level, get_position()->get_position(), get_viewRadius());
        for(auto cell : visible_cell){
            auto pos_enemy = std::find(enemy_position.begin(), enemy_position.end(), Coordinates(cell.first, cell.second));
            if(pos_enemy != enemy_position.end()){
                std::shared_ptr<Entity> enemy;
                for(auto entity : level.get_listEntity()){
                    if(entity->get_position()->get_position() == *pos_enemy) enemy = entity;
                }                
                try{                    
                    makeShoot(level.get_field(), enemy);
                    shoot = true;
                }
                catch(const std::exception& e){
                    if(std::string(e.what()) == "Miss") shoot = true;
                    break;
                }
            }
        }
        if(get_curretWeapon()->get_bulletType() == WeaponType::none){}
        else if(get_curretWeapon()->get_shootsLeft() == 0) dropWeapon();
        if(get_curretWeapon()->get_bulletType() == WeaponType::none){
            std::vector<Coordinates> storage_point_with_weapon;
            for(auto pos_storage_point : get_listStoragePoint()){
                if(level.get_field()[pos_storage_point.x][pos_storage_point.y]->get_listItems().get_amountItem() != 0){
                    for(auto item : level.get_field()[pos_storage_point.x][pos_storage_point.y]->get_listItems().get_matrItem()){
                        if(item->get_itemType() == ItemType::weapon){
                            storage_point_with_weapon.push_back(pos_storage_point);
                            break;
                        }
                    }
                }
            }
            if(storage_point_with_weapon.size() != 0){
                int min_i = -1;
                int min_path = 10e+8;
                for(size_t i = 0; i < storage_point_with_weapon.size(); i++){
                    if(min_path > static_cast<int>(possibility_of_a_path(level, get_position(), level.get_field()
                    [storage_point_with_weapon[i].x]
                    [storage_point_with_weapon[i].y], false).size())){
                        min_path = possibility_of_a_path(level, get_position(), level.get_field()
                        [storage_point_with_weapon[i].x][storage_point_with_weapon[i].y], false).size();
                        min_i = i;
                    }
                }
                std::vector<Coordinates> path_to_Weapon = possibility_of_a_path(level, get_position(), level.get_field()[storage_point_with_weapon[min_i].x][storage_point_with_weapon[min_i].y], false);
                for(auto cell : path_to_Weapon)
                {
                    try{
                        makeStep(level, level.get_field()[cell.x][cell.y]);
                    }
                    catch(...){not_enough_TP = true; break;}
                }
                pickUPWeapon();
            }
            else{break;}
        }
        else if(!shoot)
        {
            std::vector<Coordinates> nearby_cell = gen_nearby_cell(level, get_position()->get_position(), false);
            if(nearby_cell.size() == 0) break;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, nearby_cell.size() - 1);
            int random_index = dist(gen);
            try{
                makeStep(level, level.get_field()[nearby_cell[random_index].x][nearby_cell[random_index].y]);
            }
            catch(...){break;}
        }        
        if(not_enough_TP){
            break;
        }
    }
}