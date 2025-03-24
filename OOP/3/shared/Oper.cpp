#include <SFML/Graphics.hpp>
#include "Personage.hpp"
#include "game_algorithm.hpp"
#include "logicDire.hpp"
#include "Gentity.hpp"
#include "gravic.hpp"


[[nodiscard]] int Oper::get_accuracy() const
{
    return _accuracy;
}
[[nodiscard]] int Oper::get_strength() const
{
    return _strength;
}
[[nodiscard]] int Oper::get_minCombatDamage() const
{
    return _minCombatDamage;
}
[[nodiscard]] Inventory& Oper::get_inventory()
{
    return _inventory;
}
[[nodiscard]] std::shared_ptr<Weapon> Oper::get_curretWeapon() const
{
    return _curretWeapon;
}

Oper::Oper(Oper& oper) : Entity(
    oper.get_typeEntity(), oper.get_name(), oper.get_team(), oper.get_speed(), 
    oper.get_HP(), oper.get_maxHP(), oper.get_viewRadius(), oper.get_maxTimePoint(), 
    oper.get_timePoint(), oper.get_position()), _inventory()
{
    _accuracy = oper.get_accuracy();
    _strength = oper.get_strength();
    _minCombatDamage = oper.get_minCombatDamage();
    _curretWeapon = get_curretWeapon();
    _inventory.addItems(oper.get_inventory());
}
void Oper::pickUpItem(int num_item)
{
    if(_position->get_listItems().get_matrItem()[num_item]->get_itemHeavy() + _inventory.get_currteWeight() <=_strength)
    {
        _inventory.addItem(_position->get_listItems().popItem(num_item));
    }
    else{
        throw std::runtime_error("Перегруз");
    }
}
void Oper::dropItem(int num_item_inventory)
{
    _position->get_listItems().addItem(_inventory.popItem(num_item_inventory));
}
nlohmann::json& Oper::make_json(nlohmann::json& jEntity)
{
    nlohmann::json jItems;
    nlohmann::json jLCI;
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
    jEntity["inventory"] = _inventory.InventoryJson(jLCI);
    jEntity["amountItem"] = _inventory.get_matrItem().size();
    jEntity["accuracy"] = _accuracy;
    jEntity["strength"] = _strength;
    jEntity["minCombatDamage"] = _minCombatDamage;
    return jEntity;
}
void Oper::makeShoot(Vector<Vector<std::shared_ptr<Cell>>>& field, std::shared_ptr<Entity> enemy)
{
    if(_curretWeapon->get_bulletType() == WeaponType::none)
    {
        throw std::runtime_error("No Weapon");
    }
    if((get_timePoint() - _curretWeapon->get_timeShoot()) < 0)
    {
        throw std::runtime_error("No Time Point");
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
        throw std::runtime_error("Lose");
    }
}
void Oper::useCaseBullets()
{
    bool flag = false;
    int i = 0;
    if(get_curretWeapon()->get_timeReload() > get_timePoint())
    {
        throw std::runtime_error("Нехватка очков действия");
    }
    if(_curretWeapon->get_bulletType() == WeaponType::none)
    {
        throw std::runtime_error("Нет оружия");
    }
    for(auto iter = get_inventory().get_matrItem().begin(); iter != get_inventory().get_matrItem().end(); ++iter,i++)
    {
        if((*iter)->get_itemType() == ItemType::caseBullets)
        {
            std::shared_ptr<CaseBullets> caseB{std::static_pointer_cast<CaseBullets>((*iter))};
            if(caseB->get_bulletType() == _curretWeapon->get_bulletType())
            {
                get_curretWeapon()->reload(caseB); //Используется первый кейс(а не лучший)
                if(caseB->get_amountBullet() == 0){get_inventory().popItem(i);}
                set_timePoint(get_timePoint() - get_curretWeapon()->get_timeReload());
                flag = true;
                break;
            }
        }
    }
    if(!flag)
    {
        throw std::runtime_error("Нет патронов");
    }
}
void Oper::useCaseBullets(int numItem)
{
    if(get_curretWeapon()->get_timeReload() > get_timePoint())
    {
        throw std::runtime_error("No time Point");
    }
    if(_curretWeapon->get_bulletType() == WeaponType::none)
    {
        throw std::runtime_error("No weapon");
    }
    if(get_inventory().get_matrItem()[numItem]->get_itemType() == ItemType::caseBullets)
    {
        std::shared_ptr<CaseBullets> caseB{std::static_pointer_cast<CaseBullets>(get_inventory().get_matrItem()[numItem])};
        if(caseB->get_bulletType() == _curretWeapon->get_bulletType())
        {
            get_curretWeapon()->reload(caseB);
            if(caseB->get_amountBullet() == 0){get_inventory().popItem(numItem);}
            set_timePoint(get_timePoint() - get_curretWeapon()->get_timeReload());
        }
        else{
            throw std::runtime_error("Wrong type of bullets");
        }
    }
    else
    {
        throw std::runtime_error("No bullets");
    }
}
void Oper::useFirstAidKit()
{
    int i = 0;
    bool flag = false;
    for(auto iter = get_inventory().get_matrItem().begin(); iter != get_inventory().get_matrItem().end(); ++iter, i++)
    {
        if((*iter)->get_itemType() == ItemType::firstAidKit)
        {
            std::shared_ptr<FirstAidKit> aptechki{std::static_pointer_cast<FirstAidKit>((*iter))};
            if(aptechki->get_timePoint() > get_timePoint())
            {
                throw std::runtime_error("Нехватка очков действия");
            }
            int nado_vostanoviti_zdorovia = get_maxHP() - get_HP();
            if(nado_vostanoviti_zdorovia > aptechki->get_healthRecover())
            {
                set_HP(get_HP() + aptechki->get_healthRecover());
            }
            else
            {
                set_HP(get_maxHP());//Используется первый кейс(а не лучший)
            }
            set_timePoint(get_timePoint() - aptechki->get_timePoint());
            get_inventory().popItem(i);
            flag = true;
            break;
        }
    }
    if(!flag)
    {
        throw std::runtime_error("Нет аптечек");
    }
}
Oper::Oper(Vector<Vector<std::shared_ptr<Cell>>>& field, nlohmann::json& jEntity): 
    Entity(jEntity["typeEntity"],
        jEntity["name"], 
        jEntity["team"], 
        jEntity["speed"], 
        jEntity["HP"], 
        jEntity["maxHP"], 
        jEntity["viewRadius"], 
        jEntity["maxTimePoint"], 
        jEntity["timePoint"], 
        field[jEntity["position"][0]][jEntity["position"][1]]
    ),
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
        jEntity["curretWeapon"]["shootsLeft"]
    )), 
    _inventory(), _accuracy(jEntity["accuracy"]), _strength(jEntity["strength"]), _minCombatDamage(jEntity["minCombatDamage"])
{
    Inventory inventory;
    _inventory.addItems(makeInvntoeyJson(inventory, jEntity["inventory"]["Items"], jEntity["inventory"]["amountItem"]));
}
void Oper::useFirstAidKit(int numItem)
{
    if(get_inventory().get_matrItem()[numItem]->get_itemType() == ItemType::firstAidKit)
    {
        std::shared_ptr<FirstAidKit> aptechki{std::static_pointer_cast<FirstAidKit>(get_inventory().get_matrItem()[numItem])};
        if(aptechki->get_timePoint() > get_timePoint())
        {
            throw std::runtime_error("Нехватка очков действия");
        }
        int nado_vostanoviti_zdorovia = get_maxHP() - get_HP();
        if(nado_vostanoviti_zdorovia > aptechki->get_healthRecover())
        {
            set_HP(get_HP() + aptechki->get_healthRecover());
        }
        else
        {
            set_HP(get_maxHP());
        }
        set_timePoint(get_timePoint() - aptechki->get_timePoint());
        get_inventory().popItem(numItem);
    }
    else
    {
        throw std::runtime_error("Нет аптечка");
    }
}
void Oper::chooseWeapon(int numItem)
{
    if(get_inventory().get_matrItem()[numItem]->get_itemType() != ItemType::weapon)
    {
        throw std::runtime_error("Не оружие");
    }
    get_inventory().addItem(_curretWeapon);
    _curretWeapon = get_inventory().popWeapon(numItem);
}
void Oper::logic(Level& Level){throw std::runtime_error("Искусственный интелект не предусмотрен!!");}
void Oper::update_menu(std::shared_ptr<Entity> entity, sf::Text& Text)
{
    std::shared_ptr<Oper> oper{std::static_pointer_cast<Oper>(entity)};
    std::string texts = entity->get_name() + "\n" +
    "HP: " + std::to_string(entity->get_HP()) + "/" + std::to_string(entity->get_maxHP())+"\n"
    +  "TP : " + std::to_string(entity->get_timePoint()) + "/" + std::to_string(entity->get_maxTimePoint()) + "\n"
    + "Bullets : " + std::to_string(oper->get_curretWeapon()->get_shootsLeft()) + "/" + std::to_string(oper->get_curretWeapon()->get_cartridgeSize()) + "\n"
    + "Damage : " + std::to_string(oper->get_curretWeapon()->get_baseDamage()) + "  Rate of fire : " + std::to_string(oper->get_curretWeapon()->get_shootsPerRound()) + "\n"
    + "makeStep\n"
    + "makeShoot\n"
    + "Inventory\n"
    + "Pick up Item\n"
    + "End turn\n"
    + "Save\n";
    Text.setString(texts);
}
void Oper::menu_button_pressed(Game_stat& Stat, sf::Event& event, Game_texts& Text, Level& level)
{
    Stat.active_shoot = false;
    Stat.active_step = false;
    if(event.mouseButton.y/(Text.font_size + Stat.pixel_correction) == 5){
        Stat.active_step = true;
    }
    if(event.mouseButton.y/(Text.font_size + Stat.pixel_correction) == 6) Stat.active_shoot = true;
    if(event.mouseButton.y/(Text.font_size + Stat.pixel_correction) == 7) Stat.inventory.create(sf::VideoMode(400, 400), "inventory : oper", sf::Style::Default);
    if(event.mouseButton.y/(Text.font_size + Stat.pixel_correction) == 8){
        Stat.inventory.create(sf::VideoMode(Stat.inventory_size, Stat.inventory_size), "inventory : cell", sf::Style::Default);
        Stat.cell_inventory = true;
    }
    if(event.mouseButton.y/(Text.font_size + Stat.pixel_correction) == 9){
        Dire_turn(level);
        update_TP(level);
        try{
            update_list_Entity(level, Text.Text_gen);
        }
        catch(const std::exception& e){
            Stat.gameEnd = true;
            Stat.beginTime = Stat.clock.getElapsedTime();
        }
    }
    if(event.mouseButton.y/(Text.font_size + Stat.pixel_correction) == 10){
        level.save(Stat.file_save_in_time);
        Stat.gameEnd = true;
    }
}