#include "Items.hpp"

[[nodiscard]] const std::string& Item::get_itemName()
{
    return Item::_itemName;
}
[[nodiscard]] int Item::get_itemHeavy() {return Item::_itemHeavy;}

[[nodiscard]] ItemType Item::get_itemType(){return Item::_itemType;}

[[nodiscard]] int FirstAidKit::get_healthRecover(){return FirstAidKit::_healthRecover;}

[[nodiscard]] int FirstAidKit::get_timePoint(){return FirstAidKit::_timePoint;}

nlohmann::json& FirstAidKit::make_json(nlohmann::json& jItems)
{
    jItems["itemName"] = _itemName;
    jItems["itemType"] = _itemType;
    jItems["itemHeavy"] = _itemHeavy;
    jItems["healthRecover"] = _healthRecover;
    jItems["timePoint"] = _timePoint;
    return jItems;
}

[[nodiscard]] int CaseBullets::get_caseSize(){ return CaseBullets::_caseSize;}

[[nodiscard]] int CaseBullets::get_amountBullet(){ return CaseBullets::_amountBullet;}

[[nodiscard]] WeaponType CaseBullets::get_bulletType() {return CaseBullets::_bulletType;}

CaseBullets& CaseBullets::set_amountBullets(int amount_Bullets)
{
    int curret_amount = 0;
    if(amount_Bullets >= _caseSize)
    {
        curret_amount = _caseSize;
    }
    else
    {
        curret_amount = amount_Bullets;
    }
    CaseBullets::_amountBullet = curret_amount;
    return (*this);
}
nlohmann::json& CaseBullets::make_json(nlohmann::json& jItems)
{
    jItems["itemName"] = _itemName;
    jItems["itemType"] = _itemType;
    jItems["itemHeavy"] = _itemHeavy;
    jItems["amountBullet"] = _amountBullet;
    jItems["caseSize"] = _caseSize;
    jItems["bulletType"] = _bulletType;
    return jItems;
}


[[nodiscard]] int Weapon::get_timeShoot(){return Weapon::_timeShoot;}

[[nodiscard]] int Weapon::get_baseDamage(){return Weapon::_baseDamage;}

[[nodiscard]] int Weapon::get_shootsPerRound(){return Weapon::_shootsPerRound;}

[[nodiscard]] int Weapon::get_timeReload(){return Weapon::_timeReload;}

[[nodiscard]] int Weapon::get_cartridgeSize(){return Weapon::_cartridgeSize;}

[[nodiscard]] WeaponType Weapon::get_bulletType(){return Weapon::_bulletType;}

[[nodiscard]] int Weapon::get_shootsLeft(){return Weapon::_shootsLeft;}

Weapon& Weapon::set_shootsLeft(int amount_shoots)
{
    _shootsLeft = amount_shoots;
    return (*this);
}
void Weapon::reload(std::shared_ptr<CaseBullets> caseB)
{
    if (caseB->get_bulletType() != this->_bulletType)
    {
        throw std::runtime_error("Неправильный тип патронов");
    }
    if((this->_cartridgeSize - this->_shootsLeft) >= (caseB->get_amountBullet()))
    {
        this->_shootsLeft += caseB->get_amountBullet();
        caseB->set_amountBullets(0);
    }
    else
    {
        int size_Bullet_in_case = this->_cartridgeSize - this->_shootsLeft;
        this->_shootsLeft = this->_cartridgeSize;
        caseB->set_amountBullets(caseB->get_amountBullet() - size_Bullet_in_case);
    }
}
nlohmann::json& Weapon::make_json(nlohmann::json& jItems)
{
    jItems["itemName"] = _itemName;
    jItems["itemType"] = _itemType;
    jItems["itemHeavy"] = _itemHeavy;
    jItems["bulletType"] = _bulletType;
    jItems["timeShoot"] = _timeShoot;
    jItems["baseDamage"] = _baseDamage;
    jItems["shootsPerRound"] = _shootsPerRound;
    jItems["timeReload"] = _timeReload;
    jItems["cartridgeSize"] = _cartridgeSize;
    jItems["shootsLeft"] = _shootsLeft;
    return jItems;
}
int Weapon::makeShoots()
{
    int damage = 0;    
    if(_shootsLeft == 0)
    {
        throw std::runtime_error("Нет патронов");
    }
    else if(_shootsLeft <= _shootsPerRound)
    {
        damage =  _baseDamage * _shootsLeft;
        _shootsLeft = 0;
    }
    else if(_shootsLeft > _shootsPerRound)
    {
        damage =  _baseDamage * _shootsPerRound;
        _shootsLeft -= _shootsPerRound;
    }

    return damage;
}