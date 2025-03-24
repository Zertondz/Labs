#include "Inventory.hpp"
#include "Level.hpp"
#include "Personage.hpp"
#include "game_algorithm.hpp"
#include <iostream>
#include "gravic.hpp"
#include <random>

void Dire_turn(Level& level)
{
    for(auto entity : level.get_listEntity()){
        try{entity->logic(level);}
        catch(const std::exception& e){continue;}
    }
}