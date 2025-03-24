#include "Inventory.hpp"
#include <nlohmann/json.hpp>
void Inventory::addItem(std::shared_ptr<Item> item)
{
    try
    {
        int currteWeight = item->get_itemHeavy();
        this->_matrItem.push_back(std::move(item));
        this->_currteWeight += currteWeight;
        this->_amountItem += 1;
    }
    catch(const std::exception& e)
    {
        throw e;
    }
}
std::shared_ptr<Item> Inventory::popItem(const int position)
{
    int weight = _matrItem[position]->get_itemHeavy();
    std::shared_ptr<Item> item{_matrItem[position]};
    _matrItem.erase(_matrItem.begin() + position);
    _amountItem -= 1;
    _currteWeight -= weight;
    return item;
}
std::shared_ptr<Weapon> Inventory::popWeapon(const int position)
{
    if((this->_matrItem)[position]->get_itemType() != ItemType::weapon)
    {
        throw std::runtime_error("Неправильный тип предмета");
    }
    int weight = (this->_matrItem)[position]->get_itemHeavy();
    std::shared_ptr<Weapon> item{std::static_pointer_cast<Weapon>((this->_matrItem)[position])};
    this->_matrItem.erase(this->_matrItem.begin() + position);
    this->_amountItem -= 1;
    this->_currteWeight -= weight;
    return item;
}
std::shared_ptr<FirstAidKit> Inventory::popFirstAidKit(const int position)
{
    if((this->_matrItem)[position]->get_itemType() != ItemType::firstAidKit)
    {
        throw std::runtime_error("Неправильный тип предмета");
    }
    int weight = (this->_matrItem)[position]->get_itemHeavy();
    std::shared_ptr<FirstAidKit> item{std::static_pointer_cast<FirstAidKit>((this->_matrItem)[position])};
    this->_matrItem.erase(this->_matrItem.begin() + position);
    this->_amountItem -= 1;
    this->_currteWeight -= weight;
    return item;
}
std::shared_ptr<CaseBullets> Inventory::popCaseBullets(const int position)
{
    if((this->_matrItem)[position]->get_itemType() != ItemType::caseBullets)
    {
        throw std::runtime_error("Неправильный тип предмета");
    }
    int weight = (this->_matrItem)[position]->get_itemHeavy();
    std::shared_ptr<CaseBullets> item{std::static_pointer_cast<CaseBullets>((this->_matrItem)[position])};
    this->_matrItem.erase(this->_matrItem.begin() + position);
    this->_amountItem -= 1;
    this->_currteWeight -= weight;
    return item;
}


const std::shared_ptr<Weapon> Inventory::get_Weapon(const int position)
{
    if(_amountItem <= position)
    {
        throw (std::runtime_error("get_Weapon: Invalid read!!!"));
    }
    if((this->_matrItem)[position]->get_itemType() != ItemType::weapon)
    {
        throw std::runtime_error("Неправильный тип предмета");
    }
    const std::shared_ptr<Weapon> item{std::static_pointer_cast<Weapon>((this->_matrItem)[position])};
    return item;
}
const std::shared_ptr<FirstAidKit> Inventory::get_FirstAidKit(const int position){
    if(_amountItem <= position)
    {
        throw (std::runtime_error("get_FirstAidKit: Invalid read!!!"));
    }
    if((this->_matrItem)[position]->get_itemType() != ItemType::firstAidKit)
    {
        throw std::runtime_error("Неправильный тип предмета");
    }
    const std::shared_ptr<FirstAidKit> item{std::static_pointer_cast<FirstAidKit>((this->_matrItem)[position])};
    return item;
}
const std::shared_ptr<CaseBullets> Inventory::get_CaseBullets(const int position)
{
    if(_amountItem <= position)
    {
        throw (std::runtime_error("get_caseBulltes: Invalid read!!!"));
    }
    if((this->_matrItem)[position]->get_itemType() != ItemType::caseBullets)
    {
        throw std::runtime_error("Неправильный тип предмета");
    }
    const std::shared_ptr<CaseBullets> item{std::static_pointer_cast<CaseBullets>((this->_matrItem)[position])};
    return item;
}
void Inventory::addItems(Inventory& inventory)
{
    int size = inventory.get_matrItem().size();
    for(int i = 0; i < size; i++)
    {        
        int curretWeight = inventory.get_matrItem()[0]->get_itemHeavy();
        _matrItem.push_back(inventory.popItem(0));
        _amountItem++;
        _currteWeight+=curretWeight;
    }
}

[[nodiscard]] const std::vector<std::shared_ptr<Item>>& Inventory::get_matrItem(){return this->_matrItem;}

[[nodiscard]] int Inventory::get_currteWeight(){return this->_currteWeight;}

[[nodiscard]] int Inventory::get_amountItem(){return this->_amountItem;}

nlohmann::json& Inventory::InventoryJson(nlohmann::json& jLCI)
{
    nlohmann::json items_array = nlohmann::json::array();
    for(int numInvent = 0; numInvent < _amountItem; numInvent++)
    {
        nlohmann::json jItems;
        items_array.push_back(_matrItem[numInvent]->make_json(jItems));
    }
    jLCI["ListHeavy"] = _currteWeight;
    jLCI["amountItem"] = _amountItem;
    jLCI["Items"] = items_array;
    return jLCI;
}