#include <future>
#include <thread>
#include "Inventory.hpp"
#include "Level.hpp"
#include "Personage.hpp"
#include "game_algorithm.hpp"
#include <iostream>
#include "gravic.hpp"
#include <random>
void execute_entity_logic(Level& level, std::shared_ptr<Entity> entity, std::function<void(Level&, std::shared_ptr<Entity>)> logic) {
    auto current_cell = entity->get_position();
    if (current_cell) {
        //std::lock_guard<std::mutex> lock(current_cell->cell_mutex);
        logic(level, entity);
    }
}
std::vector<Coordinates> gen_nearby_cell_MT(Level& level, Coordinates old_position){
    std::vector<Coordinates> neibors;
    std::vector<Coordinates> entity_position;
    for(auto entity : level.get_listEntity()){
        entity_position.push_back(entity->get_position()->get_position());
    }
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            int cell_x = old_position.x + i;
            int cell_y = old_position.y + j;
            if((cell_x >= static_cast<int>(level.get_field().size()))||(cell_x < 0)) continue;
            if((cell_y >= static_cast<int>(level.get_field()[0].size()))||(cell_y < 0)) continue;
            if((j == 0)&&(i == 0)) continue;
            if(std::find(entity_position.begin(), entity_position.end(), Coordinates(cell_x, cell_y)) != entity_position.end()) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() == TypeCell::glass) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() == TypeCell::wall) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() == TypeCell::partition) continue;
            neibors.push_back(Coordinates(cell_x, cell_y));
        }
    }
    return neibors;
}
std::vector<std::pair<int, int>> gen_visible_cell_MT(Level& level, std::shared_ptr<Entity> begin_entity)
{
    int x_start = begin_entity->get_position()->get_position().x;
    int y_start = begin_entity->get_position()->get_position().y;
    std::vector<std::pair<int, int>> visible_cells;
    for (int i = -begin_entity->get_viewRadius(); i <= begin_entity->get_viewRadius(); ++i) {
        for (int j = -begin_entity->get_viewRadius(); j <= begin_entity->get_viewRadius(); ++j) {
            int cell_x = x_start + i;
            int cell_y = y_start + j;
            if(cell_y < 0) continue;
            if(cell_x < 0) continue;
            if(cell_x >= static_cast<int>(level.get_field().size())) continue;
            if(cell_y >= static_cast<int>(level.get_field()[0].size())) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() != TypeCell::field) continue;
            if (std::sqrt(i * i + j * j) <= begin_entity->get_viewRadius()) {
                visible_cells.emplace_back(cell_x, cell_y);
            }
        }
    }

    std::sort(visible_cells.begin(), visible_cells.end(), [x_start, y_start](const auto& a, const auto& b) {
        double distance_a = std::sqrt((a.first - x_start) * (a.first - x_start) + (a.second - y_start) * (a.second - y_start));
        double distance_b = std::sqrt((b.first - x_start) * (b.first - x_start) + (b.second - y_start) * (b.second - y_start));
        return distance_a < distance_b;
    });
    return visible_cells;
}
void forager_logic_MT(Level& level, std::shared_ptr<Entity> begin_entity)
{
    std::lock_guard<std::mutex> guard_f(level._field_mutex);
    std::lock_guard<std::mutex> guard_LE(level._listEntity_mutex);
    std::shared_ptr<Forager> begin_forager = std::static_pointer_cast<Forager>(begin_entity);
    
    while(begin_forager->get_timePoint() != 0){
        std::vector<std::pair<int, int>> visible_cells = gen_visible_cell_MT(level, begin_forager);   
        bool find_weapon = false;
        bool to_get_to_SP = false;
        // Поиск оружия на поле
        for(auto coordinate : visible_cells)
        {
            if((level.get_field()[coordinate.first][coordinate.second]->get_listItems().get_amountItem() != 0)&&(level.get_field()[coordinate.first][coordinate.second]->get_typeCell() != TypeCell::storagePoint))
            {
                std::vector<Coordinates> path_to_Weapon = possibility_of_a_path(level, begin_forager->get_position(), level.get_field()[coordinate.first][coordinate.second], false);
                for(auto cell : path_to_Weapon)
                {
                    try{
                        auto next_cell = level.get_field()[cell.x][cell.y];
                        begin_forager->makeStep(level, next_cell);
                    }
                    catch(...){find_weapon = false; break;}
                }
                while (true)
                {
                    try{begin_forager->pickUPWeapon();}
                    catch(...){ break;}
                }
                find_weapon = true;
                break;
            }
        }
        // Если не нашли идем на рандомную клетку рядом
        if(!find_weapon)
        {
            std::vector<Coordinates> nearby_cell = gen_nearby_cell_MT(level, begin_forager->get_position()->get_position());
            if(nearby_cell.size() == 0) continue;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, nearby_cell.size() - 1);
            int random_index = dist(gen);
            try{
                auto next_cell = level.get_field()[nearby_cell[random_index].x][nearby_cell[random_index].y];
                begin_forager->makeStep(level, next_cell);
            }
            catch(...){break;}
            continue;
        }
        else{
            // Поиск ближайшего SP
            int path_size = 10e+8;
            Coordinates target_cell;
            std::vector<Coordinates> target_path;
            for(size_t i = 0; i < begin_forager->get_listStoragePoint().size(); i++)
            {
                std::vector<Coordinates> path = possibility_of_a_path(level, begin_forager->get_position(), level.get_field()
                    [begin_forager->get_listStoragePoint()[i].x]
                    [begin_forager->get_listStoragePoint()[i].y], false);
                if(path.size() == 0) continue;
                if(static_cast<int>(path.size()) < path_size)
                {
                    path_size = path.size();
                    target_cell = Coordinates(begin_forager->get_listStoragePoint()[i].x, begin_forager->get_listStoragePoint()[i].y);
                    target_path = path;
                }
            }


            // Идет к нему
            if(target_path.size() > 0)
            {
                for(auto cell : target_path)
                {
                    try{
                        auto next_cell = level.get_field()[cell.x][cell.y];
                        begin_forager->makeStep(level, next_cell);
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
                        begin_forager->dropWeapon();
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

void wild_logic_MT(Level& level, std::shared_ptr<Entity> begin_entity)
{
    
    int min_i = -1;
    int min_path = 10e+8;
    int i_o = -1;
    int min_path_size = 10e+8;
    std::vector<Coordinates> neibors;
    std::vector<Coordinates> target_path;
    std::lock_guard<std::mutex> guard_f(level._field_mutex);
    std::lock_guard<std::mutex> guard_LE(level._listEntity_mutex);
    std::vector<std::future<std::pair<int, int>>> futures;
    std::vector<std::future<std::vector<Coordinates>>> futures_path;

    for (auto entity : level.get_listEntity()) {
        i_o++;
        if (entity->get_team() == Team::Radiant) {
            auto curret_cell = begin_entity->get_position();
            auto next_cell = entity->get_position();
            futures.push_back(std::async(std::launch::async, [&level, curret_cell, next_cell, i_o]() {
                auto path = possibility_of_a_path(level, curret_cell, next_cell, true);
                return std::make_pair(i_o, static_cast<int>(path.size()));
            }));
        }
    }
    for (auto& future : futures) {
        auto [index, path_size] = future.get();
        if (min_path > path_size) {
            min_path = path_size;
            min_i = index;
        }
    }


    if(min_i == -1)
    {
        throw std::runtime_error("Нет врагов");
    }

    neibors = gen_nearby_cell_MT(level, level.get_listEntity()[min_i]->get_position()->get_position());

    for (auto neibor : neibors) {
        auto curret_cell = begin_entity->get_position();
        auto next_cell = level.get_field()[neibor.x][neibor.y];
        futures_path.push_back(std::async(std::launch::async, [&level, curret_cell, next_cell]() {
            return possibility_of_a_path(level, curret_cell, next_cell, false);
        }));
    }

    for (auto& future1 : futures_path) {
        auto path = future1.get();
        if (min_path_size > static_cast<int>(path.size())) {
            min_path_size = path.size();
            target_path = path;
        }
    }

    for(auto cell : target_path)
    {
        try
        {
            auto next_cell = level.get_field()[cell.x][cell.y];
            begin_entity->makeStep(level, next_cell);
        }
        catch(...){ break;}
    }
    while(begin_entity->get_timePoint() != 0)
    {
        try
        {
            begin_entity->makeShoot(level.get_field(), level.get_listEntity()[min_i]);
        }
        catch(...){ break;}
    }
}
void smart_logic_MT(Level& level, std::shared_ptr<Entity> begin_entity)
{
    std::lock_guard<std::mutex> guard_f(level._field_mutex);
    std::lock_guard<std::mutex> guard_LE(level._listEntity_mutex);
    std::vector<Coordinates> enemy_position;
    std::shared_ptr<Smart> begin_smart = std::static_pointer_cast<Smart>(begin_entity);
    for(auto entity : level.get_listEntity()){
        if(entity->get_team() == Team::Radiant){
            enemy_position.push_back(entity->get_position()->get_position());
        }
    }
    while(begin_smart->get_timePoint() != 0)
    {
        bool shoot = false;
        bool not_enough_TP = false;
        std::vector<std::pair<int, int>> visible_cell = gen_visible_cell_MT(level, begin_smart);
        for(auto cell : visible_cell){
            auto pos_enemy = std::find(enemy_position.begin(), enemy_position.end(), Coordinates(cell.first, cell.second));
            if(pos_enemy != enemy_position.end()){
                std::shared_ptr<Entity> enemy;
                for(auto entity : level.get_listEntity()){
                    if(entity->get_position()->get_position() == *pos_enemy) enemy = entity;
                }                
                try{                    
                    begin_smart->makeShoot(level.get_field(), enemy);
                    shoot = true;
                }
                catch(const std::exception& e){
                    if(std::string(e.what()) == "Miss") shoot = true;
                    break;
                }
            }
        }
        if(begin_smart->get_curretWeapon()->get_bulletType() == WeaponType::none){}
        else if(begin_smart->get_curretWeapon()->get_shootsLeft() == 0) begin_smart->dropWeapon();
        if(begin_smart->get_curretWeapon()->get_bulletType() == WeaponType::none){
            std::vector<Coordinates> storage_point_with_weapon;
            for(auto pos_storage_point : begin_smart->get_listStoragePoint()){
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
                    if(min_path > static_cast<int>(possibility_of_a_path(level, begin_smart->get_position(), level.get_field()
                    [storage_point_with_weapon[i].x]
                    [storage_point_with_weapon[i].y], false).size())){
                        min_path = possibility_of_a_path(level, begin_smart->get_position(), level.get_field()
                        [storage_point_with_weapon[i].x][storage_point_with_weapon[i].y], false).size();
                        min_i = i;
                    }
                }
                std::vector<Coordinates> path_to_Weapon = possibility_of_a_path(level, begin_smart->get_position(), level.get_field()[storage_point_with_weapon[min_i].x][storage_point_with_weapon[min_i].y], false);
                for(auto cell : path_to_Weapon)
                {
                    try{
                        auto next_cell = level.get_field()[cell.x][cell.y];
                        begin_smart->makeStep(level, next_cell);
                    }
                    catch(...){not_enough_TP = true; break;}
                }
                begin_smart->pickUPWeapon();
            }
            else{break;}
        }
        else if(!shoot)
        {
            std::vector<Coordinates> nearby_cell = gen_nearby_cell_MT(level, begin_smart->get_position()->get_position());
            if(nearby_cell.size() == 0) break;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, nearby_cell.size() - 1);
            int random_index = dist(gen);
            try{
                auto next_cell = level.get_field()[nearby_cell[random_index].x][nearby_cell[random_index].y];
                begin_smart->makeStep(level, next_cell);
            }
            catch(...){break;}
        }        
        if(not_enough_TP){
            break;
        }
    }
}


void Dire_turn_MT(Level& level)
{
    std::vector<std::shared_ptr<Entity>> wilds, smarts, foragers;
    for (auto entity : level.get_listEntity()) {
        if (entity->get_typeEntity() == "Wild") {
            wilds.push_back(entity);
        } else if (entity->get_typeEntity() == "Smart") {
            smarts.push_back(entity);
        } else if (entity->get_typeEntity() == "Forager") {
            foragers.push_back(entity);
        }
    }
    auto process_entities = [&level](std::vector<std::shared_ptr<Entity>>& entities, std::function<void(Level&, std::shared_ptr<Entity>)> logic) {
    for (auto entity : entities) {
            execute_entity_logic(level, entity, logic);
        }
    };
    std::jthread wild_thread(process_entities, std::ref(wilds), wild_logic_MT);
    std::jthread smart_thread(process_entities, std::ref(smarts), smart_logic_MT);
    std::jthread forager_thread(process_entities, std::ref(foragers), forager_logic_MT);
}