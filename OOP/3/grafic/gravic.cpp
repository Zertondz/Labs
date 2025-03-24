#include "Inventory.hpp"
#include "Level.hpp"
#include "Personage.hpp"
#include "game_algorithm.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gentity.hpp"
#include "logicDire.hpp"
#include "logicDire_multi_thread.hpp"
#include "gravic.hpp"
void update_sprite_cell(Level& level, std::vector<sf::Sprite>& sprites_cell, std::vector<sf::Sprite>& sprites_cell_items, Textures& textures)
{
    int CELL_SIZE = 64;
    int ITEM_SIZE = 28;
    for (size_t x = 0; x < level.get_field().size(); ++x) 
    {
        for (size_t y = 0; y < level.get_field()[0].size(); ++y) 
        {
            sf::Sprite cell;
            cell.setTexture(textures.textures_cell[level.get_field()[x][y]->get_typeCell()]);
            cell.setScale(
                static_cast<float>(CELL_SIZE) / textures.textures_cell[level.get_field()[x][y]->get_typeCell()].getSize().x,
                static_cast<float>(CELL_SIZE) / textures.textures_cell[level.get_field()[x][y]->get_typeCell()].getSize().y
            );
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            sprites_cell.push_back(cell);
            for (int itemIndex = 0; itemIndex < level.get_field()[x][y]->get_listItems().get_amountItem() && itemIndex < 4; ++itemIndex) 
            {
                // Позиция для каждого предмета
                float itemX = x * CELL_SIZE + (itemIndex % 2) * (ITEM_SIZE + 2); // 2 - отступ между предметами
                float itemY = y * CELL_SIZE + (itemIndex / 2) * (ITEM_SIZE + 2); 

                // Создаем спрайт для предмета
                sf::Sprite itemSprite;
                if(level.get_field()[x][y]->get_listItems().get_matrItem()[itemIndex]->get_itemType() == ItemType::weapon)
                {
                    itemSprite.setTexture(textures.textures_weapon[level.get_field()[x][y]->get_listItems().get_Weapon(itemIndex)->get_bulletType()]);
                    itemSprite.setScale(
                        static_cast<float>(ITEM_SIZE) / textures.textures_weapon[(level.get_field()[x][y]->get_listItems().get_Weapon(itemIndex)->get_bulletType())].getSize().x,
                        static_cast<float>(ITEM_SIZE) / textures.textures_weapon[(level.get_field()[x][y]->get_listItems().get_Weapon(itemIndex)->get_bulletType())].getSize().y
                    );
                    
                }
                else if(level.get_field()[x][y]->get_listItems().get_matrItem()[itemIndex]->get_itemType() == ItemType::caseBullets)
                {
                    itemSprite.setTexture(textures.textures_caseBullets[level.get_field()[x][y]->get_listItems().get_CaseBullets(itemIndex)->get_bulletType()]);
                    itemSprite.setScale(
                        static_cast<float>(ITEM_SIZE) / textures.textures_caseBullets[level.get_field()[x][y]->get_listItems().get_CaseBullets(itemIndex)->get_bulletType()].getSize().x,
                        static_cast<float>(ITEM_SIZE) / textures.textures_caseBullets[level.get_field()[x][y]->get_listItems().get_CaseBullets(itemIndex)->get_bulletType()].getSize().y
                    );
                }
                else if(level.get_field()[x][y]->get_listItems().get_matrItem()[itemIndex]->get_itemType() == ItemType::firstAidKit)
                {
                    itemSprite.setTexture(textures.textures_item[level.get_field()[x][y]->get_listItems().get_matrItem()[itemIndex]->get_itemType()]);
                    itemSprite.setScale(
                        static_cast<float>(ITEM_SIZE) / textures.textures_item[level.get_field()[x][y]->get_listItems().get_matrItem()[itemIndex]->get_itemType()].getSize().x,
                        static_cast<float>(ITEM_SIZE) / textures.textures_item[level.get_field()[x][y]->get_listItems().get_matrItem()[itemIndex]->get_itemType()].getSize().y
                    );
                }
                itemSprite.setPosition(itemX, itemY);
                sprites_cell_items.push_back(itemSprite);
            }
        }
    }

}
void update_sprite_entity(Textures& textures, std::vector<GEntity>& Gentitys, sf::Font& font)
{
    int CELL_SIZE = 64;
    int size = Gentitys.size();
    for(auto i = 0; i < size; i++){
        if(Gentitys[i].get_entity()->get_HP() != 0){
            Gentitys[i].get_sprite().setTexture(textures.textures_entity[Gentitys[i].get_entity()->get_typeEntity()]);
            Gentitys[i].get_sprite().setScale(
                static_cast<float>(CELL_SIZE) / textures.textures_entity[Gentitys[i].get_entity()->get_typeEntity()].getSize().x,
                static_cast<float>(CELL_SIZE) / textures.textures_entity[Gentitys[i].get_entity()->get_typeEntity()].getSize().y
            );
            Gentitys[i].get_sprite().setPosition(Gentitys[i].get_entity()->get_position()->get_position().x * CELL_SIZE, Gentitys[i].get_entity()->get_position()->get_position().y * CELL_SIZE);
            Gentitys[i].get_text().setString("HP: " + std::to_string(Gentitys[i].get_entity()->get_HP()) + "/" + std::to_string(Gentitys[i].get_entity()->get_maxHP()));
            Gentitys[i].get_text().setFont(font);
            Gentitys[i].get_text().setCharacterSize(12);
            Gentitys[i].get_text().setFillColor(sf::Color::Red);
            sf::FloatRect spriteBounds = Gentitys[i].get_sprite().getGlobalBounds();
            Gentitys[i].get_text().setPosition(spriteBounds.left + spriteBounds.width / 2 - Gentitys[i].get_text().getGlobalBounds().width / 2,
                spriteBounds.top + spriteBounds.height);
        }
        else{
            Gentitys.erase(Gentitys.begin() + i);
            i--;
            size--;
        }
    }
}
void initial_Gentity(Level& level, std::vector<GEntity>& Gentitys)
{
    for(auto iter = level.get_listEntity().begin(); iter != level.get_listEntity().end(); ++iter)
    {
        Gentitys.push_back(GEntity(*iter));
    }
}
void update_sprite_inventory(Inventory& inventory, std::vector<sf::Sprite>& sprites_inventory, Textures& textures)
{
    const int ITEM_SIZE = 64;
    sprites_inventory.resize(inventory.get_amountItem());
    for(int i = 0; i < inventory.get_amountItem(); i++)
    {
        if(inventory.get_matrItem()[i]->get_itemType() == ItemType::weapon)
        {
            sprites_inventory[i].setTexture(textures.textures_weapon[(inventory.get_Weapon(i)->get_bulletType())]);
            sprites_inventory[i].setScale(
                static_cast<float>(ITEM_SIZE) / textures.textures_weapon[(inventory.get_Weapon(i)->get_bulletType())].getSize().x,
                static_cast<float>(ITEM_SIZE) / textures.textures_weapon[(inventory.get_Weapon(i)->get_bulletType())].getSize().y
            );
            
        }
        else if(inventory.get_matrItem()[i]->get_itemType() == ItemType::caseBullets)
        {
            sprites_inventory[i].setTexture(textures.textures_caseBullets[inventory.get_CaseBullets(i)->get_bulletType()]);
            sprites_inventory[i].setScale(
                static_cast<float>(ITEM_SIZE) / textures.textures_caseBullets[inventory.get_CaseBullets(i)->get_bulletType()].getSize().x,
                static_cast<float>(ITEM_SIZE) / textures.textures_caseBullets[inventory.get_CaseBullets(i)->get_bulletType()].getSize().y
            );
        }
        else if(inventory.get_matrItem()[i]->get_itemType() == ItemType::firstAidKit)
        {
            sprites_inventory[i].setTexture(textures.textures_item[inventory.get_matrItem()[i]->get_itemType()]);
            sprites_inventory[i].setScale(
                static_cast<float>(ITEM_SIZE) / textures.textures_item[inventory.get_matrItem()[i]->get_itemType()].getSize().x,
                static_cast<float>(ITEM_SIZE) / textures.textures_item[inventory.get_matrItem()[i]->get_itemType()].getSize().y
            );
        }
        sprites_inventory[i].setPosition(i * ITEM_SIZE, (i/5) * ITEM_SIZE);
    }
}

void update_list_Entity(Level& level, sf::Text& text)
{
    int count_dire = 0;
    int count_Radiant = 0;
    for(size_t i = 0; i < level.get_listEntity().size(); i++){
        if(level.get_listEntity()[i]->get_HP() == 0)
        {
            level.get_listEntity().erase(level.get_listEntity().begin() + i);
            i--;
        }
    }
    for(size_t i = 0; i < level.get_listEntity().size(); i++){
        if(level.get_listEntity()[i]->get_team() == Team::Dire) count_dire++;
        if(level.get_listEntity()[i]->get_team() == Team::Radiant) count_Radiant++;
    }
    if((count_dire == 0)||(count_Radiant == 0)){
        if(count_Radiant == 0) text.setString("Dire win");
        else text.setString("Radiant win");
        throw std::runtime_error("Игра окончена");
    }

}
void update_TP(Level& level)
{
    for(size_t i = 0; i < level.get_listEntity().size(); i++)
    {
        level.get_listEntity()[i]->set_timePoint(level.get_listEntity()[i]->get_maxTimePoint());
    }
}

void player_menu(Game_stat& Stat, sf::Event& event, Game_texts& Text, Level& level){
    while(Stat.menu.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            Stat.menu.close();
            Stat.active_entity = nullptr;
        }
        if(event.type == sf::Event::MouseButtonPressed){
            Stat.active_entity->menu_button_pressed(Stat, event, Text, level);
        }
    }
}

void vision() {
    Game_sprites Sprites;
    Game_stat Stat;
    Game_texts Text;
    Stat.menu.setFramerateLimit(Stat.frame_limit);
    Stat.inventory.setFramerateLimit(Stat.frame_limit);    
    Stat.window.setFramerateLimit(Stat.frame_limit);
    //Вызов первого меню для выбора сохранения
    Stat.menu.create(sf::VideoMode(Stat.menu_size, Stat.menu_size), "menu", sf::Style::Default);
    while(Stat.menu.isOpen()){
        Stat.menu.clear(sf::Color::White);
        sf::Event event;
        while(Stat.menu.pollEvent(event))
        {
            int pixel_correction = 8;
            if (event.type == sf::Event::Closed) {
                Stat.menu.close();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                std::cout << event.mouseButton.y/(Text.font_size + pixel_correction) << std::endl;
                if(event.mouseButton.y/(Text.font_size + pixel_correction) == 1){
                    Stat.file_save = "save/level.json";
                    Stat.save_window = true;
                    break;
                }
                if(event.mouseButton.y/(Text.font_size + pixel_correction) == 2){
                    Stat.file_save = "save/levelpop.json";
                    Stat.save_window = true;
                    break;
                }
            }
        }
        if(Stat.save_window) {Stat.menu.close();break;}
        Stat.menu.draw(Text.save_text);
        Stat.menu.display();
    }
    //Загрузка уровня
    Level level(Stat.file_save);
    initial_Gentity(level, Stat.GEntities);
    Stat.window.create(sf::VideoMode(level.get_field().size() * Stat.CELL_SIZE,  level.get_field()[0].size() * Stat.CELL_SIZE), "10x10 Grid of Images");
    while (Stat.window.isOpen()) {
        std::vector<sf::Sprite> sprites_invent;
        std::vector<sf::Sprite> sprites_cell_items;
        std::vector<sf::Sprite> sprites_cell;
        sf::Event event;
        Stat.window.clear();
        Stat.menu.clear(sf::Color::White);
        Stat.inventory.clear(sf::Color::White);
        while (Stat.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Stat.window.close();
                Stat.menu.close();
                Stat.inventory.close();
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if(Stat.active_step) {
                    try{ Stat.active_entity->makeStep(level, level.get_field()
                    [event.mouseButton.x / Stat.CELL_SIZE]
                    [event.mouseButton.y/Stat.CELL_SIZE]);}
                    catch(const std::exception& e){
                        Text.eventText.setString(e.what()); 
                        Stat.beginTime = Stat.clock.getElapsedTime(); 
                        Stat.showText = true;
                        sf::FloatRect textBoundsE = Text.eventText.getGlobalBounds();
                        Text.eventText.setPosition((Stat.window.getSize().x - textBoundsE.width) / 2, 
                        (Stat.window.getSize().y - textBoundsE.height) / 2);
                    }
                    Stat.active_step = false;
                }
                else{
                    for(auto entity : level.get_listEntity()){
                        //Вызов меню
                        if(entity->get_position()->get_position() == Coordinates(event.mouseButton.x / Stat.CELL_SIZE, event.mouseButton.y/Stat.CELL_SIZE)){
                            if(Stat.active_shoot){
                                try{
                                    std::vector<std::shared_ptr<Entity>> visi = Stat.active_entity->visiable_Entity(level.get_field(), level.get_listEntity());
                                    if(std::find(visi.begin(), visi.end(), entity) != visi.end()){
                                        Stat.active_entity->makeShoot(level.get_field(), entity);
                                    }
                                }
                                catch(const std::exception& e){
                                    Text.eventText.setString(e.what());
                                    Stat.beginTime = Stat.clock.getElapsedTime(); 
                                    Stat.showText = true;
                                    sf::FloatRect textBoundsE = Text.eventText.getGlobalBounds();
                                    Text.eventText.setPosition((Stat.window.getSize().x - textBoundsE.width) / 2, 
                                    (Stat.window.getSize().y - textBoundsE.height) / 2);
                                }                                    
                                Stat.active_shoot = false;
                                break;
                            }
                            else if(entity->get_team() == Team::Radiant)
                            {
                                Stat.active_entity = entity;
                                Stat.menu.create(sf::VideoMode(Stat.menu_size, Stat.menu_size), "menu", sf::Style::Default);
                                break;
                            }
                        }
                    }
                }
            }
        }
        //###############################################################################
        player_menu(Stat, event, Text, level);
        if(Stat.gameEnd && (Stat.clock.getElapsedTime().asSeconds() - Stat.beginTime.asSeconds()) > 5.0f){break;}
        //############################################################################### 
        //Обновление данный графики
        //############################################################################### 
        update_sprite_cell(level, sprites_cell, sprites_cell_items , Stat.textures);
        update_sprite_entity(Stat.textures, Stat.GEntities, Text.font);
        if(!Stat.gameEnd)
        {
            try{
                update_list_Entity(level, Text.Text_gen);
            }
            catch(...) {Stat.gameEnd = true; Stat.beginTime = Stat.clock.getElapsedTime();}
        }
        if(Stat.inventory.isOpen() && !Stat.cell_inventory){
            std::shared_ptr<Oper> oper{std::static_pointer_cast<Oper>(Stat.active_entity)};
            update_sprite_inventory(oper->get_inventory(), sprites_invent, Stat.textures);
        }
        else if(Stat.inventory.isOpen() && Stat.cell_inventory){
            update_sprite_inventory(Stat.active_entity->get_position()->get_listItems(), sprites_invent, Stat.textures);
        }
        if(Stat.menu.isOpen()){
            Stat.active_entity->update_menu(Stat.active_entity, Text.text_menu);
        }
        //###############################################################################        
        //###############################################################################
        // Отрисовка поля        
        //###############################################################################
        Stat.menu.draw(Text.text_menu);
        for (const auto& sprite : sprites_cell) {
            Stat.window.draw(sprite);
        }
        for (auto& cell_item : sprites_cell_items)
        {
            Stat.window.draw(cell_item);
        }
        if(Stat.inventory.isOpen()){
            for (const auto& sprite : sprites_invent) {
            Stat.inventory.draw(sprite);
            }
        }
        std::vector<GEntity> visible_entity;
        for (auto& Gentity : Stat.GEntities) {
            if(Gentity.get_entity()->get_team() == Team::Radiant){
                Gentity.visiable_Entity(level.get_field(), Stat.GEntities, visible_entity);
                Stat.window.draw(Gentity.get_sprite());
                Stat.window.draw(Gentity.get_text());
            }
        }
        for (auto& Gentity : visible_entity)
        {
            Stat.window.draw(Gentity.get_sprite());
            Stat.window.draw(Gentity.get_text());
        }
        if(Stat.menu.isOpen()){
            Stat.menu.draw(Text.text_menu);
        }
        if (Stat.showText && (Stat.clock.getElapsedTime().asSeconds() - Stat.beginTime.asSeconds()) < 0.5f) {
            Stat.window.draw(Text.eventText);
        }
        if (Stat.gameEnd && (Stat.clock.getElapsedTime().asSeconds() - Stat.beginTime.asSeconds()) < 5.0f) {
            Stat.window.draw(Text.Text_gen);
        }
        //###############################################################################
        sf::FloatRect textBoundsEEEEEE = Text.Text_gen.getGlobalBounds();
        Text.Text_gen.setPosition((Stat.window.getSize().x - textBoundsEEEEEE.width) / 2, 
        (Stat.window.getSize().y - textBoundsEEEEEE.height) / 2);
        Stat.window.draw(Text.Text_gen);
        Stat.menu.display();
        Stat.window.display();
        Stat.inventory.display();
    }
}
