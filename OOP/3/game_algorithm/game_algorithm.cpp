#include <memory>
#include <vector>
#include "Cell.hpp"
#include "Vector.hpp"
#include "Level.hpp"
#include <deque>
#include <algorithm>
#include <random>
#include <iostream>
#include <unordered_set>
#include <mutex>
#include <thread>
#include <future>
std::vector<Coordinates> gen_nearby_cell(Level& level, Coordinates old_position, bool entity_enable){
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
            if(cell_x >= static_cast<int>(level.get_field().size())) continue;
            if(cell_x < 0) continue;
            if(cell_y >= static_cast<int>(level.get_field()[0].size())) continue;
            if(cell_y < 0) continue;
            if((j == 0)&&(i == 0)) continue;
            if((std::find(entity_position.begin(), entity_position.end(), Coordinates(cell_x, cell_y)) != entity_position.end())&&(!entity_enable)) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() == TypeCell::glass) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() == TypeCell::wall) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() == TypeCell::partition) continue;
            neibors.push_back(Coordinates(cell_x, cell_y));
        }
    }
    return neibors;
}
std::vector<std::pair<int, int>> gen_visible_cell(Level& level, Coordinates start_position, int viewRadius)
{
    int x_start = start_position.x;
    int y_start = start_position.y;
    std::vector<std::pair<int, int>> visible_cells;
    for (int i = -viewRadius; i <= viewRadius; ++i) {
        for (int j = -viewRadius; j <= viewRadius; ++j) {
            int cell_x = x_start + i;
            int cell_y = y_start + j;
            if(cell_y < 0) continue;
            if(cell_x < 0) continue;
            if(cell_x >= static_cast<int>(level.get_field().size())) continue;
            if(cell_y >= static_cast<int>(level.get_field()[0].size())) continue;
            if(level.get_field()[cell_x][cell_y]->get_typeCell() != TypeCell::field) continue;
            if (std::sqrt(i * i + j * j) <= viewRadius) {
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
bool possibility_of_a_shoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Cell> oldPosition, std::shared_ptr<Cell> enemyPosition, int accuracy)
{
    std::vector<Coordinates> trajectory;
    int x_old = oldPosition->get_position().x;
    int y_old = oldPosition->get_position().y;
    int x_enemy = enemyPosition->get_position().x;
    int y_enemy = enemyPosition->get_position().y;
    int dx = abs(x_enemy - x_old);
    int dy = abs(y_enemy - y_old);
    int sx = (x_old < x_enemy) ? 1 : -1;
    int sy = (y_old < y_enemy) ? 1 : -1;
    int err = dx - dy;
    int x = x_old, y = y_old;
    while (true)
    {
        trajectory.push_back(Coordinates(x,y));
        if((x == x_enemy)&&(y == y_enemy)) break;
        int e2 = 2 * err;
        if(e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if(e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
    for(auto iter = trajectory.begin(); iter != trajectory.end(); ++iter)
    {
        if(field[(*iter).x][(*iter).y]->get_typeCell() == TypeCell::wall)
        {
            return false;
        }
        else if((field[(*iter).x][(*iter).y]->get_typeCell() == TypeCell::glass)||(field[(*iter).x][(*iter).y]->get_typeCell() == TypeCell::partition))
        {
            field[(*iter).x][(*iter).y]->set_typecell(TypeCell::field);
            return false;
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,100);
    return dist(gen) < accuracy;
}

std::vector<Coordinates> possibility_of_a_path(Level& level, std::shared_ptr<Cell> oldPosition, std::shared_ptr<Cell> newPosition, bool flag_entity_position_enable)
{
    std::deque<std::vector<Coordinates>> queue;
    std::unordered_set<Coordinates> visited;
    std::vector<Coordinates> old_p;
    std::vector<Coordinates> entity_position;
    //std::cout << oldPosition->get_position().x << oldPosition->get_position().y << " : " << newPosition->get_position().x << newPosition->get_position().y << std::endl;
    for(auto entity : level.get_listEntity()){
        entity_position.push_back(entity->get_position()->get_position());
    }
    old_p.push_back(Coordinates(oldPosition->get_position().x, oldPosition->get_position().y));
    queue.push_front(old_p);
    //std::cout << "queue_t : " << queue.size() << std::endl;
    while(!queue.empty())
    {
        std::vector<Coordinates> path(queue.front());
        queue.pop_front();
        Coordinates node = (*(path.end() - 1));
        if(visited.find(node) != visited.end())
        {
            continue;
        }
        visited.insert(node);
        if((node.x == newPosition->get_position().x)&&(node.y == newPosition->get_position().y))
        {
            //std::cout << "path.size() : " << path.size() << std::endl;
            return (path);
        }
        std::vector<Coordinates> neibors = gen_nearby_cell(level, node, flag_entity_position_enable);
        for(auto neibor : neibors)
        {
            std::vector<Coordinates> new_path(path);
            new_path.push_back(neibor);
            queue.push_back(new_path);
        }
    }
    //std::cout << "path.size() : " << 0 << std::endl;
    return std::vector<Coordinates>();
}


nlohmann::json& ListJson(std::vector<Coordinates>& list, nlohmann::json& list_stpot)
{
    for(size_t i = 0; i < list.size(); i++)
    {
        nlohmann::json Jcoord;
        Jcoord = {list[i].x, list[i].y};
        list_stpot.push_back(Jcoord);
    }
    return list_stpot;
}
Inventory& makeInvntoeyJson(Inventory& inventory, nlohmann::json& jItems, int amountitems)
{
    for(int i = 0; i < amountitems; i++)
    {
        if(ItemType(jItems[i]["itemType"]) == ItemType::caseBullets)
        {
            inventory.addItem(std::make_shared<CaseBullets>(
                jItems[i]["itemName"],
                ItemType(jItems[i]["itemType"]),
                jItems[i]["itemHeavy"],
                jItems[i]["amountBullet"],
                jItems[i]["caseSize"],
                WeaponType(jItems[i]["bulletType"])
            ));
        }
        else if(ItemType(jItems[i]["itemType"]) == ItemType::weapon)
        {
            inventory.addItem(std::make_shared<Weapon>(
                jItems[i]["itemName"],
                ItemType(jItems[i]["itemType"]),
                jItems[i]["itemHeavy"],
                WeaponType(jItems[i]["bulletType"]),
                jItems[i]["timeShoot"],
                jItems[i]["baseDamage"],
                jItems[i]["shootsPerRound"],
                jItems[i]["timeReload"],
                jItems[i]["cartridgeSize"],
                jItems[i]["shootsLeft"]
            ));
        }
        else if(ItemType(jItems[i]["itemType"]) == ItemType::firstAidKit)
        {
            inventory.addItem(std::make_shared<FirstAidKit>(
                jItems[i]["itemName"],
                ItemType(jItems[i]["itemType"]),
                jItems[i]["itemHeavy"],
                jItems[i]["healthRecover"],
                jItems[i]["timePoint"]
            ));
        }
    }
    return inventory;
}
bool propobility_see(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Cell> startPosition, std::shared_ptr<Cell> endPosition)
{
    std::vector<Coordinates> trajectory;
    int x_old = startPosition->get_position().x;
    int y_old = startPosition->get_position().y;
    int x_enemy = endPosition->get_position().x;
    int y_enemy = endPosition->get_position().y;
    int dx = abs(x_enemy - x_old);
    int dy = abs(y_enemy - y_old);
    int sx = (x_old < x_enemy) ? 1 : -1;
    int sy = (y_old < y_enemy) ? 1 : -1;
    int err = dx - dy;
    int x = x_old, y = y_old;
    while (true)
    {
        trajectory.push_back(Coordinates(x,y));
        if((x == x_enemy)&&(y == y_enemy)) break;
        int e2 = 2 * err;
        if(e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if(e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
    for(auto iter = trajectory.begin(); iter != trajectory.end(); ++iter)
    {
        if((field[(*iter).x][(*iter).y]->get_typeCell() == TypeCell::wall)||(field[(*iter).x][(*iter).y]->get_typeCell() == TypeCell::partition))
        {
            return false;
        }
    }
    return true;
}