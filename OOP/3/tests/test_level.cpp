#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch_all.hpp>
#include "Inventory.hpp"
#include "game_algorithm.hpp"
#include "Personage.hpp"
#include "Level.hpp"
TEST_CASE("Level jSon")
{
    Level level{"level.json"};
    REQUIRE(level.get_field().size() == 15);
    REQUIRE(level.get_field()[0].size() == 15);
    REQUIRE(level.get_listEntity().size() == 4);
    level.save("level_t.json");
    Level level2("level_t.json");
    REQUIRE(level2.get_field().size() == 15);
    REQUIRE(level2.get_field()[0].size() == 15);
    REQUIRE(level2.get_listEntity().size() == 4);
    REQUIRE(level2.get_activeTeam() == Team::None);
    level2.set_activeTeam(Team::Dire);
    REQUIRE(level2.get_activeTeam() == Team::Dire);
    Level level3{};
    level3.resizeField(8,8);
    REQUIRE(level3.get_field()[0].size() == 8);
    REQUIRE(level3.get_field().size() == 8);
    level3.resizeField(11,11);
    REQUIRE(level3.get_field()[0].size() == 11);
    REQUIRE(level3.get_field().size() == 11);
    level3.resizeField(9,12);
    REQUIRE(level3.get_field()[0].size() == 12);
    REQUIRE(level3.get_field().size() == 9);
    level3.resizeField(13,10);
    REQUIRE(level3.get_field()[0].size() == 10);
    REQUIRE(level3.get_field().size() == 13);
}