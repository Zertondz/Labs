#include "Entity.hpp"
#include "Level.hpp"
#include "Inventory.hpp"
#include "game_algorithm.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "gravic.hpp"
#include "logicDire.hpp"
#include "logicDire_multi_thread.hpp"

#include "Personage.hpp"
void test(int entity_count_type)
{
    Level level;
    int size_field = 100;
    std::random_device rd;

    std::vector<Coordinates> used_coord;
    level.resizeField(size_field, size_field);
    for(int i = 0; i < entity_count_type; i ++)
    {    
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, size_field - 1);
        Coordinates random_coord(dist(gen), dist(gen));
        if(std::find(used_coord.begin(), used_coord.end(), random_coord) == used_coord.end()){
            level.get_listEntity().push_back(std::make_shared<Wild>("Wild", "Tupich", Team::Dire, 4, 200, 200, 5, 10, 10, level.get_field()[random_coord.x][random_coord.y], 50, 4));
            used_coord.push_back(random_coord);
        }
    }
    for(int i = 0; i < entity_count_type; i ++)
    {   
        std::shared_ptr<Weapon> dudcina{std::make_shared<Weapon>("Dudkina3000", ItemType::weapon, 5, WeaponType::rifle, 5, 5, 5, 2, 30, 30)};
        std::vector<Coordinates> listSP;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, size_field - 1);
        Coordinates random_coord(dist(gen), dist(gen));
        if(std::find(used_coord.begin(), used_coord.end(), random_coord) == used_coord.end()){
            level.get_listEntity().push_back(std::make_shared<Smart>("Smart", "Dofigaumi", Team::Dire, 1, 50, 50, 4, 12, 12, level.get_field()[random_coord.x][random_coord.y], 50, dudcina, listSP));
            used_coord.push_back(random_coord);
        }
    }
    for(int i = 0; i < entity_count_type; i ++)
    {    
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, size_field - 1);
        Coordinates random_coord(dist(gen), dist(gen));
        std::vector<Coordinates> listSP;
        if(std::find(used_coord.begin(), used_coord.end(), random_coord) == used_coord.end()){
            level.get_listEntity().push_back(std::make_shared<Forager>("Forager", "Shesterka", Team::Dire, 7, 50, 50, 10, 15, 15, level.get_field()[random_coord.x][random_coord.y], listSP));
            used_coord.push_back(random_coord);
        }
    }
    for(int i = 0; i < entity_count_type; i++)
    {   
        std::shared_ptr<Weapon> dudcina{std::make_shared<Weapon>("Dudkina3000", ItemType::weapon, 5, WeaponType::rifle, 5, 5, 5, 2, 30, 30)};
        std::vector<Coordinates> listSP;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, size_field - 1);
        Coordinates random_coord(dist(gen), dist(gen));
        if(std::find(used_coord.begin(), used_coord.end(), random_coord) == used_coord.end()){
            level.get_listEntity().push_back(std::make_shared<Oper>("Oper", "PensilCaseovich", Team::Radiant, 1, 150, 150, 10, 50, 50, level.get_field()[random_coord.x][random_coord.y], 100, 50, 4, dudcina));
            used_coord.push_back(random_coord);
        }
    }
    level.save("test.json");
    auto start_time = std::chrono::system_clock::now();
    Dire_turn(level);
    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;
    Level level2("test.json");
    auto start_time2 = std::chrono::system_clock::now();
    Dire_turn_MT(level2);
    auto end_time2 = std::chrono::system_clock::now();
    std::chrono::duration<double> duration2 = end_time2 - start_time2;
    std::cout << "Время выполнения: " << duration2.count() << " секунд" << std::endl;
}




int main()
{
    try
    {
        std::vector<Coordinates> listSP{Coordinates(4,4), Coordinates(6,6)};
        std::string file_name("save/level.json");
        Level level1{};
        std::shared_ptr<Weapon> Telykovskiy{std::make_shared<Weapon>("Telyk3000", ItemType::weapon, 2, WeaponType::revolver, 3, 10, 1, 1, 6, 6)};
        std::shared_ptr<Weapon> Telykovskiy2{std::make_shared<Weapon>("Telyk3000", ItemType::weapon, 2, WeaponType::revolver, 3, 10, 1, 1, 6, 6)};
        std::shared_ptr<Weapon> dudcina{std::make_shared<Weapon>("Dudkina3000", ItemType::weapon, 5, WeaponType::rifle, 5, 5, 5, 2, 30, 30)};
        std::shared_ptr<Weapon> dudcina1{std::make_shared<Weapon>("Dudkina3001", ItemType::weapon, 5, WeaponType::rifle, 5, 5, 3, 2, 30, 30)};
        std::shared_ptr<Weapon> dudcina2{std::make_shared<Weapon>("Dudkina3000", ItemType::weapon, 5, WeaponType::rifle, 5, 5, 5, 2, 30, 30)};
        std::shared_ptr<CaseBullets> caseB{std::make_shared<CaseBullets>("Patron", ItemType::caseBullets, 3, 50, 50, WeaponType::rifle)};
        std::shared_ptr<FirstAidKit> aptech{std::make_shared<FirstAidKit>("aptech", ItemType::firstAidKit, 4, 100, 2)};
        std::shared_ptr<Oper> oper{std::make_shared<Oper>("Oper", "PensilCaseovich", Team::Radiant, 1, 150, 150, 10, 50, 50, level1.get_field()[3][4], 100, 50, 4, dudcina)};
        std::shared_ptr<Smart> smart{std::make_shared<Smart>("Smart", "Dofigaumi", Team::Dire, 1, 50, 50, 4, 12, 12, level1.get_field()[0][9], 50, dudcina1, listSP)};
        std::shared_ptr<Wild> wild{std::make_shared<Wild>("Wild", "Tupich", Team::Dire, 4, 200, 200, 5, 10, 10, level1.get_field()[6][7], 50, 4)};
        std::shared_ptr<Forager> forager{std::make_shared<Forager>("Forager", "Shesterka", Team::Dire, 7, 50, 50, 10, 15, 15, level1.get_field()[1][4], listSP)};
        std::shared_ptr<FAK> oper2{std::make_shared<FAK>("FAK", "PensilCaseovich", Team::Radiant, 1, 150, 150, 10, 50, 50, level1.get_field()[9][9], 100, 50, 4, dudcina2)};
        oper->get_inventory().addItem(caseB);
        oper->get_inventory().addItem(aptech);
        oper->get_inventory().addItem(Telykovskiy);
        level1.get_field()[7][2]->get_listItems().addItem(Telykovskiy2);
        level1.get_listEntity().push_back(oper);
        level1.get_listEntity().push_back(smart);
        level1.get_listEntity().push_back(wild);
        level1.get_listEntity().push_back(forager);
        level1.get_listEntity().push_back(oper2);
        level1.get_field()[2][1]->set_typecell(TypeCell::glass);
        level1.get_field()[2][0]->set_typecell(TypeCell::glass);
        level1.get_field()[2][2]->set_typecell(TypeCell::glass);
        level1.get_field()[5][5]->set_typecell(TypeCell::wall);
        level1.get_field()[5][6]->set_typecell(TypeCell::wall);
        level1.get_field()[5][7]->set_typecell(TypeCell::wall);
        level1.get_field()[3][9]->set_typecell(TypeCell::partition);
        level1.get_field()[3][8]->set_typecell(TypeCell::partition);
        level1.get_field()[3][7]->set_typecell(TypeCell::partition);
        level1.get_field()[4][4]->set_typecell(TypeCell::storagePoint);
        level1.get_field()[6][6]->set_typecell(TypeCell::storagePoint);
        level1.save(file_name);
        //Dire_turn(level1);
        /*for(int i = 1; i < 102; i += 5)
        {
            std::cout << "i = " << i << std::endl;
            test(i);
        }*/
        vision();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 1;
}
