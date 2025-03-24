#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch_all.hpp>
#include "Inventory.hpp"
#include "game_algorithm.hpp"
#include "Personage.hpp"
#include "Level.hpp"
TEST_CASE("Empty Inventory")
{
    std::vector<Coordinates> listSP{Coordinates(1,2), Coordinates(3,7)};
    Inventory inventory;
    Level level1{};
    std::shared_ptr<Weapon> Telykovskiy{std::make_shared<Weapon>("Telyk3000", ItemType::weapon, 2, WeaponType::revolver, 3, 10, 1, 1, 6, 6)};
    std::shared_ptr<Weapon> dudcina{std::make_shared<Weapon>("Dudkina3000", ItemType::weapon, 5, WeaponType::rifle, 2, 5, 3, 2, 30, 30)};
    std::shared_ptr<Weapon> dudcina1{std::make_shared<Weapon>("Dudkina3001", ItemType::weapon, 5, WeaponType::rifle, 2, 5, 3, 2, 30, 30)};
    std::shared_ptr<CaseBullets> caseB{std::make_shared<CaseBullets>("Patron", ItemType::caseBullets, 3, 3, 50, WeaponType::rifle)};
    std::shared_ptr<FirstAidKit> aptech{std::make_shared<FirstAidKit>("aptech", ItemType::firstAidKit, 4, 100, 2)};
    std::shared_ptr<Oper> oper{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 150, 150, 4, 4, 4, level1.get_field()[3][4], 100, 50, 4, dudcina)};
    std::shared_ptr<Smart> smart{std::make_shared<Smart>(TypeEntity::Smart, "Dofigaumi", Team::Dire, 1, 50, 50, 4, 12, 12, level1.get_field()[0][9], 100, 4, dudcina1, listSP)};
    std::shared_ptr<Wild> wild{std::make_shared<Wild>(TypeEntity::Wild, "Tupich", Team::Dire, 1, 200, 200, 5, 10, 10, level1.get_field()[6][7], 100, 30)};

    std::shared_ptr<Entity> wildE{std::make_shared<Wild>(TypeEntity::Wild, "Tupich", Team::Dire, 1, 200, 200, 5, 10, 10, level1.get_field()[6][8], 100, 4)};
    std::shared_ptr<Forager> forager{std::make_shared<Forager>(TypeEntity::Forager, "Shesterka", Team::Dire, 7, 250, 250, 5, 15, 15, level1.get_field()[1][4], listSP)};
    

    SECTION("Path") {
        REQUIRE(oper->get_position()->get_position() == Coordinates(3, 4));
        oper->makeStep(level1.get_field(), level1.get_field()[4][4]);
        REQUIRE(oper->get_position()->get_position() == Coordinates(4, 4));
        REQUIRE(oper->get_timePoint() == 3);
        oper->makeStep(level1.get_field(), level1.get_field()[7][7]);
        REQUIRE(oper->get_timePoint() == 0);
        REQUIRE_THROWS(oper->makeStep(level1.get_field(), level1.get_field()[9][9]));
        for(auto iter = level1.get_field()[5].begin(); iter != level1.get_field()[5].end(); ++iter)
        {
            (*iter)->set_typecell(TypeCell::wall);
        }
        REQUIRE_THROWS(forager->makeStep(level1.get_field(), level1.get_field()[6][4]));
    }
    SECTION("Entiti ini")
    {
        REQUIRE(wildE->get_typeEntity() == TypeEntity::Wild);
        REQUIRE(wildE->get_name() == "Tupich");
        REQUIRE(wildE->get_team() == Team::Dire);
        REQUIRE(wildE->get_speed() == 1);
        REQUIRE(wildE->get_HP() == 200);
        REQUIRE(wildE->get_maxHP() == 200);
        REQUIRE(wildE->get_viewRadius() == 5);
        REQUIRE(wildE->get_maxTimePoint() == 10);
        REQUIRE(wildE->get_timePoint() == 10);
        REQUIRE(wildE->get_position()->get_position() == Coordinates(6, 8));
    }
    SECTION("OPER ini")
    {
        REQUIRE(oper->get_typeEntity() == TypeEntity::Oper);
        REQUIRE(oper->get_name() == "PensilCaseovich");
        REQUIRE(oper->get_team() == Team::Radiant);
        REQUIRE(oper->get_speed() == 1);
        REQUIRE(oper->get_HP() == 150);
        REQUIRE(oper->get_maxHP() == 150);
        REQUIRE(oper->get_viewRadius() == 4);
        REQUIRE(oper->get_maxTimePoint() == 4);
        REQUIRE(oper->get_timePoint() == 4);
        REQUIRE(oper->get_position()->get_position() == Coordinates(3, 4));
        REQUIRE(oper->get_accuracy() == 100);
        REQUIRE(oper->get_strength() == 50);
        REQUIRE(oper->get_minCombatDamage() == 4);
        REQUIRE(oper->get_curretWeapon()->get_itemName() == "Dudkina3000");
        REQUIRE(oper->get_inventory().get_amountItem() == 0);
    }
    SECTION("WILD ini")
    {
        REQUIRE(wild->get_typeEntity() == TypeEntity::Wild);
        REQUIRE(wild->get_name() == "Tupich");
        REQUIRE(wild->get_team() == Team::Dire);
        REQUIRE(wild->get_speed() == 1);
        REQUIRE(wild->get_HP() == 200);
        REQUIRE(wild->get_maxHP() == 200);
        REQUIRE(wild->get_viewRadius() == 5);
        REQUIRE(wild->get_maxTimePoint() == 10);
        REQUIRE(wild->get_timePoint() == 10);
        REQUIRE(wild->get_position()->get_position() == Coordinates(6, 7));
        REQUIRE(wild->get_accuracy() == 100);
        REQUIRE(wild->get_minCombatDamage() == 30);
        REQUIRE(wild->get_timeShoot() == 3);
    }
    SECTION("SMART ini")
    {
        REQUIRE(smart->get_typeEntity() == TypeEntity::Smart);
        REQUIRE(smart->get_name() == "Dofigaumi");
        REQUIRE(smart->get_team() == Team::Dire);
        REQUIRE(smart->get_speed() == 1);
        REQUIRE(smart->get_HP() == 50);
        REQUIRE(smart->get_maxHP() == 50);
        REQUIRE(smart->get_viewRadius() == 4);
        REQUIRE(smart->get_maxTimePoint() == 12);
        REQUIRE(smart->get_timePoint() == 12);
        REQUIRE(smart->get_position()->get_position() == Coordinates(0, 9));
        REQUIRE(smart->get_accuracy() == 100);
        REQUIRE(smart->get_minCombatDamage() == 4);
        REQUIRE(smart->get_curretWeapon()->get_itemName() == "Dudkina3001");
        REQUIRE(smart->get_listStoragePoint().size() == 2);
    }
    SECTION("FORAGER ini")
    {
        REQUIRE(forager->get_typeEntity() == TypeEntity::Forager);
        REQUIRE(forager->get_name() == "Shesterka");
        REQUIRE(forager->get_team() == Team::Dire);
        REQUIRE(forager->get_speed() == 7);
        REQUIRE(forager->get_HP() == 250);
        REQUIRE(forager->get_maxHP() == 250);
        REQUIRE(forager->get_viewRadius() == 5);
        REQUIRE(forager->get_maxTimePoint() == 15);
        REQUIRE(forager->get_timePoint() == 15);
        REQUIRE(forager->get_position()->get_position() == Coordinates(1, 4));
        REQUIRE(forager->get_listStoragePoint().size() == 2);
        REQUIRE(forager->get_inventory().get_amountItem() == 0);
    }
    SECTION("SET")
    {
        wildE->set_HP(10);
        wildE->set_position(level1.get_field()[6][9]);
        REQUIRE(wildE->get_HP() == 10);
        REQUIRE(wildE->get_position()->get_position() == Coordinates(6, 9));
    }
    SECTION("Entity visible")
    {
        level1.get_listEntity().push_back(oper);
        level1.get_listEntity().push_back(wild);
        level1.get_listEntity().push_back(forager);
        level1.get_listEntity().push_back(smart);
        std::vector<std::shared_ptr<Entity>> list(oper->visiable_Entity(level1.get_listEntity()));
        REQUIRE(list[0]->get_name() == "Shesterka");
        REQUIRE(list.size() == 1);
    }
    SECTION("Oper func")
    {
        level1.get_field()[3][4]->get_listItems().addItem(aptech);
        oper->pickUpItem(0);
        REQUIRE(oper->get_inventory().get_matrItem()[0]->get_itemType() == ItemType::firstAidKit);
        oper->dropItem(0);
        REQUIRE(level1.get_field()[3][4]->get_listItems().get_matrItem()[0]->get_itemType() == ItemType::firstAidKit);
        std::shared_ptr<Weapon> Telykovskiy80{std::make_shared<Weapon>("Telyk30004", ItemType::weapon, 500, WeaponType::revolver, 3, 10, 1, 1, 6, 6)};
        level1.get_field()[3][4]->get_listItems().addItem(Telykovskiy80);
        REQUIRE_THROWS(oper->pickUpItem(1));
        oper->makeShoot(level1.get_field(), smart);
        REQUIRE(smart->get_HP() == 35);
        REQUIRE(oper->get_timePoint() == 2);
        REQUIRE(oper->get_curretWeapon()->get_shootsLeft() == 27);
        oper->get_inventory().addItem(caseB);
        oper->useCaseBullets();
        REQUIRE(oper->get_curretWeapon()->get_shootsLeft() == 30);
        REQUIRE(oper->get_inventory().get_amountItem() == 0);
    }
    SECTION("Oper func 2")
    {
        std::shared_ptr<Oper> operE{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 150, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, std::make_shared<Weapon>())};
        REQUIRE_THROWS(operE->makeShoot(level1.get_field(), wild));
        std::shared_ptr<Oper> operFr{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 150, 150, 4, 4, 4, level1.get_field()[3][4], 0, 50, 4, dudcina)};
        REQUIRE_THROWS(operFr->makeShoot(level1.get_field(), operFr));
        std::shared_ptr<Oper> operJ{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 150, 150, 4, 4, 0, level1.get_field()[3][4], 0, 50, 4, dudcina)};
        REQUIRE_THROWS(operJ->useFirstAidKit());
        REQUIRE_THROWS(operJ->useCaseBullets());
        operJ->get_inventory().addItem(aptech);
        REQUIRE_THROWS(operJ->makeShoot(level1.get_field(), operFr));
        REQUIRE_THROWS(operJ->useCaseBullets());
        REQUIRE_THROWS(operJ->useCaseBullets(1));
        REQUIRE_THROWS(operJ->useFirstAidKit());
        REQUIRE_THROWS(operJ->useFirstAidKit(0));
    }
    SECTION("Oper json")
    {
        nlohmann::json jEntity;
        jEntity = oper->make_json(jEntity);
        std::shared_ptr<Oper> opir(std::make_shared<Oper>(level1.get_field(), jEntity));
        REQUIRE(opir->get_typeEntity() == TypeEntity::Oper);
        REQUIRE(opir->get_name() == "PensilCaseovich");
        REQUIRE(opir->get_team() == Team::Radiant);
        REQUIRE(opir->get_speed() == 1);
        REQUIRE(opir->get_HP() == 150);
        REQUIRE(opir->get_maxHP() == 150);
        REQUIRE(opir->get_viewRadius() == 4);
        REQUIRE(opir->get_maxTimePoint() == 4);
        REQUIRE(opir->get_timePoint() == 4);
        REQUIRE(opir->get_position()->get_position() == Coordinates(3, 4));
        REQUIRE(opir->get_accuracy() == 100);
        REQUIRE(opir->get_strength() == 50);
        REQUIRE(opir->get_minCombatDamage() == 4);
        REQUIRE(opir->get_curretWeapon()->get_itemName() == "Dudkina3000");
        REQUIRE(opir->get_inventory().get_amountItem() == 0);
    }
    SECTION("Wild json")
    {
        nlohmann::json jEntity;
        jEntity = wild->make_json(jEntity);
        std::shared_ptr<Wild> wildt(std::make_shared<Wild>(level1.get_field(), jEntity));
        REQUIRE(wildt->get_typeEntity() == TypeEntity::Wild);
        REQUIRE(wildt->get_name() == "Tupich");
        REQUIRE(wildt->get_team() == Team::Dire);
        REQUIRE(wildt->get_speed() == 1);
        REQUIRE(wildt->get_HP() == 200);
        REQUIRE(wildt->get_maxHP() == 200);
        REQUIRE(wildt->get_viewRadius() == 5);
        REQUIRE(wildt->get_maxTimePoint() == 10);
        REQUIRE(wildt->get_timePoint() == 10);
        REQUIRE(wildt->get_position()->get_position() == Coordinates(6, 7));
        REQUIRE(wildt->get_accuracy() == 100);
        REQUIRE(wildt->get_minCombatDamage() == 30);
    }
    SECTION("Smart json")
    {
        nlohmann::json jEntity;
        jEntity = smart->make_json(jEntity);
        std::shared_ptr<Smart> smartt(std::make_shared<Smart>(level1.get_field(), jEntity));
        REQUIRE(smartt->get_typeEntity() == TypeEntity::Smart);
        REQUIRE(smartt->get_name() == "Dofigaumi");
        REQUIRE(smartt->get_team() == Team::Dire);
        REQUIRE(smartt->get_speed() == 1);
        REQUIRE(smartt->get_HP() == 50);
        REQUIRE(smartt->get_maxHP() == 50);
        REQUIRE(smartt->get_viewRadius() == 4);
        REQUIRE(smartt->get_maxTimePoint() == 12);
        REQUIRE(smartt->get_timePoint() == 12);
        REQUIRE(smartt->get_position()->get_position() == Coordinates(0, 9));
        REQUIRE(smartt->get_accuracy() == 100);
        REQUIRE(smartt->get_minCombatDamage() == 4);
        REQUIRE(smartt->get_curretWeapon()->get_itemName() == "Dudkina3001");
        REQUIRE(smartt->get_listStoragePoint().size() == 2);
    }
    SECTION("Forager json")
    {
        nlohmann::json jEntity;
        jEntity = forager->make_json(jEntity);
        std::shared_ptr<Forager> foragert(std::make_shared<Forager>(level1.get_field(), jEntity));
        REQUIRE(foragert->get_typeEntity() == TypeEntity::Forager);
        REQUIRE(foragert->get_name() == "Shesterka");
        REQUIRE(foragert->get_team() == Team::Dire);
        REQUIRE(foragert->get_speed() == 7);
        REQUIRE(foragert->get_HP() == 250);
        REQUIRE(foragert->get_maxHP() == 250);
        REQUIRE(foragert->get_viewRadius() == 5);
        REQUIRE(foragert->get_maxTimePoint() == 15);
        REQUIRE(foragert->get_timePoint() == 15);
        REQUIRE(foragert->get_position()->get_position() == Coordinates(1, 4));
        REQUIRE(foragert->get_listStoragePoint().size() == 2);
        REQUIRE(foragert->get_inventory().get_amountItem() == 0);
    }
    SECTION("forager func")
    {
        level1.get_field()[1][4]->get_listItems().addItem(Telykovskiy);
        forager->pickUPWeapon();
        REQUIRE(forager->get_inventory().get_matrItem()[0]->get_itemType() == ItemType::weapon);
        level1.get_field()[1][4]->get_listItems().addItem(aptech);
        REQUIRE_THROWS(forager->pickUPWeapon());
        forager->dropWeapon();
        REQUIRE_THROWS(forager->dropWeapon());
        REQUIRE(level1.get_field()[1][4]->get_listItems().get_matrItem()[1]->get_itemType() == ItemType::weapon);
    }
    SECTION("smart func")
    {
        smart->dropWeapon();
        smart->pickUPWeapon();
        REQUIRE(smart->get_curretWeapon()->get_itemType() == ItemType::weapon);
        REQUIRE(smart->get_curretWeapon()->get_itemName() == "Dudkina3001");
        level1.get_field()[0][9]->get_listItems().addItem(aptech);
        REQUIRE_THROWS(smart->pickUPWeapon());
        smart->dropWeapon();
        REQUIRE(level1.get_field()[0][9]->get_listItems().get_matrItem()[1]->get_itemType() == ItemType::weapon);
    }
    SECTION("Smart func 2")
    {
        level1.get_field()[0][9]->get_listItems().addItem(Telykovskiy);
        smart->pickUPWeapon();
        REQUIRE(smart->get_curretWeapon()->get_itemName() == "Telyk3000");
        smart->dropWeapon();
        REQUIRE(smart->get_curretWeapon()->get_bulletType() == WeaponType::none);
        REQUIRE_THROWS(smart->dropWeapon());
    }
    SECTION("Smart func 3")
    {
        smart->makeShoot(level1.get_field(), oper);
        REQUIRE(smart->get_timePoint() == (12 - 2));
        REQUIRE(smart->get_curretWeapon()->get_shootsLeft() == 27);
        REQUIRE(oper->get_HP() == 135);
        std::shared_ptr<Smart> smartE{std::make_shared<Smart>(TypeEntity::Smart, "Dofigaumi", Team::Dire, 1, 50, 50, 4, 12, 12, level1.get_field()[0][9], 0, 4, dudcina1, listSP)};
        REQUIRE_THROWS(smartE->makeShoot(level1.get_field(), oper));
        std::shared_ptr<Smart> smartF{std::make_shared<Smart>(TypeEntity::Smart, "Dofigaumi", Team::Dire, 1, 50, 50, 4, 12, 12, level1.get_field()[0][9], 100, 4, std::make_shared<Weapon>(), listSP)};
        REQUIRE_THROWS(smartF->makeShoot(level1.get_field(), oper));
        std::shared_ptr<Smart> smartJ{std::make_shared<Smart>(TypeEntity::Smart, "Dofigaumi", Team::Dire, 1, 50, 50, 4, 12, 0, level1.get_field()[0][9], 100, 4, dudcina1, listSP)};
        REQUIRE_THROWS(smartJ->makeShoot(level1.get_field(), oper));
    }
    SECTION("Wild func 3")
    {
        REQUIRE_THROWS(wild->makeShoot(level1.get_field(), oper));
        std::shared_ptr<Oper> operE{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 150, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, dudcina)};
        wild->makeShoot(level1.get_field(), operE);
        REQUIRE(wild->get_timePoint() == (10 - 3));
        REQUIRE(operE->get_HP() == 120);
        std::shared_ptr<Wild> wildF{std::make_shared<Wild>(TypeEntity::Wild, "Tupich", Team::Dire, 1, 200, 200, 5, 10, 10, level1.get_field()[6][7], 0, 30)};
        REQUIRE_THROWS(wildF->makeShoot(level1.get_field(), operE));
        std::shared_ptr<Wild> wildJ{std::make_shared<Wild>(TypeEntity::Wild, "Tupich", Team::Dire, 1, 200, 200, 5, 10, 0, level1.get_field()[6][7], 0, 30)};
        REQUIRE_THROWS(wildJ->makeShoot(level1.get_field(), operE));
    }
    SECTION("Oper func 3")
    {
        oper->get_inventory().addItem(Telykovskiy);
        oper->get_inventory().addItem(aptech);
        REQUIRE_THROWS(oper->chooseWeapon(1));
        oper->chooseWeapon(0);
        REQUIRE(oper->get_curretWeapon()->get_itemName() == "Telyk3000");
        REQUIRE(oper->get_inventory().get_amountItem() == 2);
        oper->useFirstAidKit();
        REQUIRE(oper->get_inventory().get_amountItem() == 1);
    }
    SECTION("Oper func 4")
    {
        std::shared_ptr<FirstAidKit> aptech1{std::make_shared<FirstAidKit>("aptech", ItemType::firstAidKit, 4, 100, 2)};
        std::shared_ptr<FirstAidKit> aptech2{std::make_shared<FirstAidKit>("aptech", ItemType::firstAidKit, 4, 100, 2)};
        std::shared_ptr<FirstAidKit> aptech3{std::make_shared<FirstAidKit>("aptech", ItemType::firstAidKit, 4, 100, 2)};
        std::shared_ptr<FirstAidKit> aptech4{std::make_shared<FirstAidKit>("aptech", ItemType::firstAidKit, 4, 100, 2)};
        std::shared_ptr<Oper> operE{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 10, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, std::make_shared<Weapon>())};
        REQUIRE_THROWS(operE->useFirstAidKit());
        operE->get_inventory().addItem(aptech1);
        operE->useFirstAidKit();
        REQUIRE(operE->get_HP() == 110);
        REQUIRE(operE->get_inventory().get_amountItem() == 0);
        std::shared_ptr<Oper> operF{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 100, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, std::make_shared<Weapon>())};
        operF->get_inventory().addItem(aptech2);
        operF->useFirstAidKit();
        REQUIRE(operF->get_HP() == 150);
        REQUIRE(operF->get_inventory().get_amountItem() == 0);
        std::shared_ptr<Oper> operG{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 10, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, std::make_shared<Weapon>())};
        operG->get_inventory().addItem(aptech3);
        operG->useFirstAidKit(0);
        REQUIRE(operG->get_HP() == 110);
        REQUIRE(operG->get_inventory().get_amountItem() == 0);
        std::shared_ptr<Oper> operJ{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 100, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, std::make_shared<Weapon>())};
        operJ->get_inventory().addItem(caseB);
        REQUIRE_THROWS(operJ->useFirstAidKit(0));
        operJ->get_inventory().addItem(aptech4);
        operJ->useFirstAidKit(1);
        REQUIRE(operJ->get_HP() == 150);
        REQUIRE(operJ->get_inventory().get_amountItem() == 1);
    }
    SECTION("Oper func 4")
    {
        std::shared_ptr<Weapon> Telykovskiy2{std::make_shared<Weapon>("Telyk3000", ItemType::weapon, 2, WeaponType::rifle, 3, 10, 1, 1, 6, 0)};
        std::shared_ptr<Oper> operE{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 10, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, Telykovskiy2)};
        operE->get_inventory().addItem(caseB);
        operE->useCaseBullets(0);
        REQUIRE(operE->get_curretWeapon()->get_shootsLeft() == 3);
        std::shared_ptr<Oper> operl{std::make_shared<Oper>(TypeEntity::Oper, "PensilCaseovich", Team::Radiant, 1, 10, 150, 4, 4, 4, level1.get_field()[7][7], 100, 50, 4, std::make_shared<Weapon>())};
        operl->get_inventory().addItem(aptech);
        REQUIRE_THROWS(operl->useCaseBullets());
        REQUIRE_THROWS(operl->useCaseBullets(0));
        operl->get_inventory().addItem(caseB);
        REQUIRE_THROWS(operl->useCaseBullets());
        REQUIRE_THROWS(operl->useCaseBullets(1));
    }
}