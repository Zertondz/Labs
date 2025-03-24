#include <random>
#include "Personage.hpp"
#include "game_algorithm.hpp"
void Forager::makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy)
{
    throw std::runtime_error("Can not shoot");
}
[[nodiscard]] Inventory& Forager::get_inventory()
{
    return _inventory;
}
[[nodiscard]] std::vector<Coordinates>& Forager::get_listStoragePoint()
{
    return _listStoragePoint;
}
void Forager::pickUPWeapon()
{
    int i = 0;
    bool flag = false;
    for(auto iter = get_position()->get_listItems().get_matrItem().begin(); iter != get_position()->get_listItems().get_matrItem().end(); ++iter,i++)
    {
        if((*iter)->get_itemType() == ItemType::weapon)
        {
            std::shared_ptr<Weapon> WeaponF{std::static_pointer_cast<Weapon>((*iter))};
            _inventory.addItem(WeaponF);
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
void Forager::dropWeapon()
{
    if(!_inventory.get_matrItem().empty())
    {
        get_position()->get_listItems().addItem(_inventory.popWeapon(_inventory.get_amountItem() - 1));
    }
    else
    {
        throw std::runtime_error("Нет оружия");
    }
}
Forager::Forager(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity): 
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
        _inventory(),
        _listStoragePoint()
{
    Inventory inventory;
    std::vector<Coordinates> listStoragePoint;
    for(int i = 0; i < jEntity["sizeListSP"]; i++)
    {
        listStoragePoint.push_back(Coordinates(jEntity["listStoragePoint"][i][0], jEntity["listStoragePoint"][i][1]));
    }
    _inventory.addItems(makeInvntoeyJson(inventory, jEntity["inventory"]["Items"], jEntity["inventory"]["amountItem"]));
    _listStoragePoint = listStoragePoint;
}
nlohmann::json& Forager::make_json(nlohmann::json& jEntity)
{
    nlohmann::json jLCI;
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
    jEntity["amountItem"] = _inventory.get_matrItem().size();
    jEntity["inventory"] = _inventory.InventoryJson(jLCI);
    jEntity["listStoragePoint"] = ListJson(_listStoragePoint, list_stpot);
    jEntity["sizeListSP"] = _listStoragePoint.size();
    return jEntity;
}
void Forager::logic(Level& level)
{
    while(get_timePoint() != 0){
        std::vector<std::pair<int, int>> visible_cells = gen_visible_cell(level, get_position()->get_position(), get_viewRadius());  
        bool find_weapon = false;
        bool to_get_to_SP = false;
        // Поиск оружия на поле
        for(auto coordinate : visible_cells)
        {
            if((level.get_field()[coordinate.first][coordinate.second]->get_listItems().get_amountItem() != 0)&&(level.get_field()[coordinate.first][coordinate.second]->get_typeCell() != TypeCell::storagePoint))
            {
                
                std::vector<Coordinates> path_to_Weapon = possibility_of_a_path(level, get_position(), level.get_field()[coordinate.first][coordinate.second], false);
                for(auto cell : path_to_Weapon)
                {
                    try{
                        makeStep(level, level.get_field()[cell.x][cell.y]);
                    }
                    catch(...){find_weapon = false; break;}
                }
                while (true)
                {
                    try{pickUPWeapon();}
                    catch(...){ break;}
                }
                find_weapon = true;
                break;
            }
        }
        // Если не нашли идем на рандомную клетку рядом
        if(!find_weapon)
        {
            std::vector<Coordinates> nearby_cell = gen_nearby_cell(level, get_position()->get_position(), false);
            if(nearby_cell.size() == 0) continue;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, nearby_cell.size() - 1);
            int random_index = dist(gen);
            try{
                makeStep(level, level.get_field()[nearby_cell[random_index].x][nearby_cell[random_index].y]);
            }
            catch(...){break;}
            continue;
        }
        else{
            // Поиск ближайшего SP
            int path_size = 10e+8;
            Coordinates target_cell;
            std::vector<Coordinates> target_path;
            for(size_t i = 0; i < get_listStoragePoint().size(); i++)
            {
                std::vector<Coordinates> path = possibility_of_a_path(level, get_position(), level.get_field()
                    [get_listStoragePoint()[i].x]
                    [get_listStoragePoint()[i].y], false);
                if(path.size() == 0) continue;
                if(static_cast<int>(path.size()) < path_size)
                {
                    path_size = path.size();
                    target_cell = Coordinates(get_listStoragePoint()[i].x, get_listStoragePoint()[i].y);
                    target_path = path;
                }
            }


            // Идет к нему
            if(target_path.size() > 0)
            {
                for(auto cell : target_path)
                {
                    try{
                        makeStep(level, level.get_field()[cell.x][cell.y]);
                    }
                    catch(const std::exception& e){to_get_to_SP= false; break;}
                }
            }
            else{
                to_get_to_SP = true;
            }



            // если дошел то сбрасывает оружие
            if(to_get_to_SP){
                while(true){
                    try{
                        dropWeapon();
                    }
                    catch(...){ find_weapon = false; break;}
                }
            }
            else{ // Если не дошел значит нет очков дествия(очки могут остаться но из за скорости передвижения их может не хватить на один шаг)
                break;
            }
        }
        find_weapon = false;
        to_get_to_SP = true;
    }
}