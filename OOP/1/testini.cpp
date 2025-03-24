#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch_all.hpp>
#include "struct.h"
#include <cstring>
using namespace lab1;
TEST_CASE("xml to str1")
{
    Dict_m* exm = strcr("<record><word>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>");
    REQUIRE(std::strcmp(exm->word,"apple") == 0);
    REQUIRE(std::strcmp(exm->meaning, "fruit") == 0);
    REQUIRE(exm->emp == 1);
    delete_str(exm);
}
TEST_CASE("xml to str2")
{
    Dict_m* exm = create_str("<record><word>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>");
    REQUIRE(std::strcmp(exm->word,"apple") == 0);
    REQUIRE(std::strcmp(exm->meaning, "fruit") == 0);
    REQUIRE(exm->emp == 1);
    delete_str(exm);
}
TEST_CASE("xml to str3")
{
    REQUIRE_THROWS(strcr("<record><wor>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>"));
}
TEST_CASE("xml to str4")
{
    std::string str = "<record><word>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>";
    Dict_m* exm = create_str(str);
    REQUIRE(std::strcmp(exm->word,"apple") == 0);
    REQUIRE(std::strcmp(exm->meaning, "fruit") == 0);
    REQUIRE(exm->emp == 1);
    delete_str(exm);
}
TEST_CASE("xml to str5")
{
    Dict_m* exm = create_str("<record><word>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>", 81);
    REQUIRE(std::strcmp(exm->word,"apple") == 0);
    REQUIRE(std::strcmp(exm->meaning, "fruit") == 0);
    REQUIRE(exm->emp == 1);
    delete_str(exm);
}
TEST_CASE("xml to str6")
{
    Dict_m* exm = create_str("<record><word>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>", 81);
    delete_str(exm);
    REQUIRE(exm == nullptr);
}
TEST_CASE("xml to str7")
{
    REQUIRE_THROWS(create_str("<record><word>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>", 80));
}
TEST_CASE("xml to str8")
{
    std::string str = "<record><wor>apple</word><meaning>fruit</meaning><emphisis>1</emphasis></record>";
    REQUIRE_THROWS(create_str(str));
}
TEST_CASE("xml to str9")
{
    REQUIRE_THROWS(create_str("<record><word>applewewewrefdsfsdfsdfsdferfwsefwf</word><meaning>fruit</meaning><emphisis>1</emphasis></record>", 110));
}
TEST_CASE("xml to str10")
{
    std::string str = "<record><wor>appledsfsdfdsfdsfsdfsdfrefefsdffrsdfesfdfesfesfe</word><meaning>fruit</meaning><emphisis>1</emphasis></record>";
    REQUIRE_THROWS(create_str(str));
}
TEST_CASE("xml to str11")
{
    REQUIRE_THROWS(strcr("<record><wor>applsdadadadasdasdasdasdasdsadwdadae</word><meaning>fruit</meaning><emphisis>1</emphasis></record>"));
}