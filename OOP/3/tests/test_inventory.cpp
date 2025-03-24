#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch_all.hpp>
#include "Inventory.hpp"
#include "game_algorithm.hpp"
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
TEST_CASE("Empty Inventory")
{
    Inventory inventory;
    REQUIRE(inventory.get_currteWeight() == 0);
    REQUIRE(inventory.get_matrItem().size() == 0);
    REQUIRE_THROWS(inventory.get_CaseBullets(3));
}
TEST_CASE("Weapon functionality", "[Weapon]") {
    Weapon weapon("Rifle", ItemType::weapon, 7, WeaponType::rifle, 5, 50, 3, 10, 30, 10);

    SECTION("Properties") {
        REQUIRE(weapon.get_timeShoot() == 5);
        REQUIRE(weapon.get_baseDamage() == 50);
        REQUIRE(weapon.get_shootsPerRound() == 3);
        REQUIRE(weapon.get_timeReload() == 10);
        REQUIRE(weapon.get_cartridgeSize() == 30);
        REQUIRE(weapon.get_shootsLeft() == 10);
    }

    SECTION("Setting shoots left") {
        weapon.set_shootsLeft(20);
        REQUIRE(weapon.get_shootsLeft() == 20);
    }
    SECTION("Shooting functionality") {
        int shotsFired = weapon.makeShoots();
        REQUIRE(shotsFired == 150); // Should fire a full round
        REQUIRE(weapon.get_shootsLeft() == 7);

        shotsFired = weapon.makeShoots();
        REQUIRE(shotsFired == 150);
        REQUIRE(weapon.get_shootsLeft() == 4);

        shotsFired = weapon.makeShoots();
        REQUIRE(shotsFired == 150);
        REQUIRE(weapon.get_shootsLeft() == 1);

        shotsFired = weapon.makeShoots();
        REQUIRE(shotsFired == 50); // Fires the remaining bullet
        REQUIRE(weapon.get_shootsLeft() == 0);
        REQUIRE_THROWS(weapon.makeShoots());
    }

    SECTION("Reloading1") {
        auto caseB = std::make_shared<CaseBullets>("Ammo Case", ItemType::caseBullets, 2, 10, 50, WeaponType::rifle);
        auto caseBP = std::make_shared<CaseBullets>("Ammo Case", ItemType::caseBullets, 2, 10, 50, WeaponType::pistol);
        weapon.reload(caseB);
        REQUIRE_THROWS(weapon.reload(caseBP));
        REQUIRE(weapon.get_shootsLeft() == 20); // Fully reloaded
        REQUIRE(caseB->get_amountBullet() == 0); // Case is emptied
    }
    SECTION("Reloading2") {
        auto caseB = std::make_shared<CaseBullets>("Ammo Case", ItemType::caseBullets, 2, 50, 50, WeaponType::rifle);
        auto caseBP = std::make_shared<CaseBullets>("Ammo Case", ItemType::caseBullets, 2, 10, 50, WeaponType::pistol);
        weapon.reload(caseB);
        REQUIRE_THROWS(weapon.reload(caseBP));
        REQUIRE(weapon.get_shootsLeft() == 30); // Fully reloaded
        REQUIRE(caseB->get_amountBullet() == 30); // Case is emptied
    }

    SECTION("JSON serialization") {
        nlohmann::json j;
        j = weapon.make_json(j);
        REQUIRE(j["itemName"] == "Rifle");
        REQUIRE(j["itemType"] == static_cast<int>(ItemType::weapon));
        REQUIRE(j["itemHeavy"] == 7);
        REQUIRE(j["bulletType"] == static_cast<int>(WeaponType::rifle));
        REQUIRE(j["baseDamage"] == 50);
        REQUIRE(j["cartridgeSize"] == 30);
        REQUIRE(j["shootsLeft"] == 10);
    }
}
TEST_CASE("CaseBullets functionality", "[CaseBullets]") {
    CaseBullets bullets("Ammo Case", ItemType::caseBullets, 2, 10, 50, WeaponType::rifle);

    SECTION("Properties") {
        REQUIRE(bullets.get_amountBullet() == 10);
        REQUIRE(bullets.get_caseSize() == 50);
        REQUIRE(bullets.get_bulletType() == WeaponType::rifle);
    }

    SECTION("Setting bullets") {
        bullets.set_amountBullets(30);
        REQUIRE(bullets.get_amountBullet() == 30);

        bullets.set_amountBullets(60); // Exceeding the case size
        REQUIRE(bullets.get_amountBullet() == 50);
    }

    SECTION("JSON serialization") {
        nlohmann::json j;
        j = bullets.make_json(j);
        REQUIRE(j["itemName"]== "Ammo Case");
        REQUIRE(j["itemType"] == static_cast<int>(ItemType::caseBullets));
        REQUIRE(j["itemHeavy"] == 2);
        REQUIRE(j["amountBullet"] == 10);
        REQUIRE(j["caseSize"] == 50);
        REQUIRE(j["bulletType"] == static_cast<int>(WeaponType::rifle));
    }
}
TEST_CASE("FirstAidKit functionality", "[FirstAidKit]") {
    FirstAidKit kit("Advanced Kit", ItemType::firstAidKit, 5, 100, 20);

    SECTION("Properties") {
        REQUIRE(kit.get_healthRecover() == 100);
        REQUIRE(kit.get_timePoint() == 20);
    }

    SECTION("JSON serialization") {
        nlohmann::json j;
        j = kit.make_json(j);
        REQUIRE(j["itemName"] == "Advanced Kit");
        REQUIRE(j["itemType"] == static_cast<int>(ItemType::firstAidKit));
        REQUIRE(j["itemHeavy"] == 5);
        REQUIRE(j["healthRecover"] == 100);
        REQUIRE(j["timePoint"] == 20);
    }
}
TEST_CASE("Item base class functionality", "[Item]") {
    std::shared_ptr<Item> item = std::make_shared<FirstAidKit>("Basic Kit", ItemType::firstAidKit, 3, 50, 10);

    SECTION("Default item properties") {
        REQUIRE(item->get_itemName() == "Basic Kit");
        REQUIRE(item->get_itemHeavy() == 3);
        REQUIRE(item->get_itemType() == ItemType::firstAidKit);
    }
}
TEST_CASE("function") {
    Inventory inventory;
    std::shared_ptr<Weapon> dudcina1{std::make_shared<Weapon>("Dudkina3001", ItemType::weapon, 5, WeaponType::rifle, 5, 5, 3, 2, 30, 30)};
    std::shared_ptr<CaseBullets> caseB{std::make_shared<CaseBullets>("Patron", ItemType::caseBullets, 3, 50, 50, WeaponType::rifle)};
    std::shared_ptr<FirstAidKit> aptech{std::make_shared<FirstAidKit>("aptech", ItemType::firstAidKit, 4, 100, 2)};
    inventory.addItem(dudcina1);
    inventory.addItem(caseB);
    inventory.addItem(aptech);
    REQUIRE(inventory.get_amountItem() == 3);
    REQUIRE(inventory.get_currteWeight() == 12);
    SECTION("popWeapon") {
        std::shared_ptr<Weapon> exmW = inventory.popWeapon(0);
        REQUIRE_THROWS(inventory.popWeapon(1));
        REQUIRE(exmW->get_shootsLeft() == 30);
        REQUIRE(exmW->get_cartridgeSize() == 30);
        REQUIRE(exmW->get_timeReload() == 2);
        REQUIRE(exmW->get_shootsPerRound() == 3);
        REQUIRE(exmW->get_baseDamage() == 5);
        REQUIRE(exmW->get_timeShoot() == 5);
        REQUIRE(exmW->get_bulletType() == WeaponType::rifle);
        REQUIRE(exmW->get_itemHeavy() == 5);
        REQUIRE(exmW->get_itemType() == ItemType::weapon);
        REQUIRE(exmW->get_itemName() == "Dudkina3001");
    }
    SECTION("popCaseBullets") {
        std::shared_ptr<CaseBullets> exmB = inventory.popCaseBullets(1);
        REQUIRE_THROWS(inventory.popCaseBullets(0));
        REQUIRE(exmB->get_caseSize() == 50);
        REQUIRE(exmB->get_amountBullet() == 50);
        REQUIRE(exmB->get_bulletType() == WeaponType::rifle);
        REQUIRE(exmB->get_itemHeavy() == 3);
        REQUIRE(exmB->get_itemType() == ItemType::caseBullets);
        REQUIRE(exmB->get_itemName() == "Patron");
    }
    SECTION("popFirstAidKit") {
        std::shared_ptr<FirstAidKit> exmF = inventory.popFirstAidKit(2);
        REQUIRE_THROWS(inventory.popFirstAidKit(1));
        REQUIRE(exmF->get_timePoint() == 2);
        REQUIRE(exmF->get_healthRecover() == 100);
        REQUIRE(exmF->get_itemHeavy() == 4);
        REQUIRE(exmF->get_itemType() == ItemType::firstAidKit);
        REQUIRE(exmF->get_itemName() == "aptech");
    }
    SECTION("getWeapon") {
        REQUIRE_THROWS(inventory.get_Weapon(1));
        REQUIRE_THROWS(inventory.get_Weapon(5));
        REQUIRE(inventory.get_Weapon(0)->get_shootsLeft() == 30);
        REQUIRE(inventory.get_Weapon(0)->get_cartridgeSize() == 30);
        REQUIRE(inventory.get_Weapon(0)->get_timeReload() == 2);
        REQUIRE(inventory.get_Weapon(0)->get_shootsPerRound() == 3);
        REQUIRE(inventory.get_Weapon(0)->get_baseDamage() == 5);
        REQUIRE(inventory.get_Weapon(0)->get_timeShoot() == 5);
        REQUIRE(inventory.get_Weapon(0)->get_bulletType() == WeaponType::rifle);
        REQUIRE(inventory.get_Weapon(0)->get_itemHeavy() == 5);
        REQUIRE(inventory.get_Weapon(0)->get_itemType() == ItemType::weapon);
        REQUIRE(inventory.get_Weapon(0)->get_itemName() == "Dudkina3001");
    }
    SECTION("getCaseBullets") {
        REQUIRE_THROWS(inventory.get_CaseBullets(2));
        REQUIRE_THROWS(inventory.get_CaseBullets(5));
        REQUIRE(inventory.get_CaseBullets(1)->get_caseSize() == 50);
        REQUIRE(inventory.get_CaseBullets(1)->get_amountBullet() == 50);
        REQUIRE(inventory.get_CaseBullets(1)->get_bulletType() == WeaponType::rifle);
        REQUIRE(inventory.get_CaseBullets(1)->get_itemHeavy() == 3);
        REQUIRE(inventory.get_CaseBullets(1)->get_itemType() == ItemType::caseBullets);
        REQUIRE(inventory.get_CaseBullets(1)->get_itemName() == "Patron");
    }
    SECTION("getFirstAidKit") {
        REQUIRE_THROWS(inventory.get_FirstAidKit(1));
        REQUIRE_THROWS(inventory.get_FirstAidKit(5));
        REQUIRE(inventory.get_FirstAidKit(2)->get_timePoint() == 2);
        REQUIRE(inventory.get_FirstAidKit(2)->get_healthRecover() == 100);
        REQUIRE(inventory.get_FirstAidKit(2)->get_itemHeavy() == 4);
        REQUIRE(inventory.get_FirstAidKit(2)->get_itemType() == ItemType::firstAidKit);
        REQUIRE(inventory.get_FirstAidKit(2)->get_itemName() == "aptech");
    }
    SECTION("popFirstAidKit") {
        std::shared_ptr<Item> exmF = inventory.popItem(2);
        REQUIRE(exmF->get_itemHeavy() == 4);
        REQUIRE(exmF->get_itemType() == ItemType::firstAidKit);
        REQUIRE(exmF->get_itemName() == "aptech");
    }
    SECTION("addItems") {
        Inventory inventory2;
        inventory2.addItems(inventory);
        REQUIRE(inventory2.get_Weapon(0)->get_itemType() == ItemType::weapon);
        REQUIRE(inventory2.get_CaseBullets(1)->get_itemType() == ItemType::caseBullets);
        REQUIRE(inventory2.get_FirstAidKit(2)->get_itemType() == ItemType::firstAidKit);
        REQUIRE(inventory.get_amountItem() == 0);
    }
    SECTION("Inventory json") {
        nlohmann::json JInvent;
        JInvent = inventory.InventoryJson(JInvent);
        Inventory inventory2;
        makeInvntoeyJson(inventory2, JInvent["Items"], 3);
        REQUIRE(inventory2.get_Weapon(0)->get_itemType() == ItemType::weapon);
        REQUIRE(inventory2.get_CaseBullets(1)->get_itemType() == ItemType::caseBullets);
        REQUIRE(inventory2.get_FirstAidKit(2)->get_itemType() == ItemType::firstAidKit);
        REQUIRE(inventory2.get_amountItem() == 3);
    }
}