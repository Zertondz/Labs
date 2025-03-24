#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch_all.hpp>
#include "Vector.hpp"
#include "Word.hpp"
#include "Words.hpp"
#include "tools.hpp"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
TEST_CASE("word low_case")
{
    Word exm("terrA");
    exm.lowwer_case();
    REQUIRE(std::strcmp(exm.get_word(), "terra") == 0);
    exm.set_word("PENSILCASe");
    exm.lowwer_case();
    REQUIRE(std::strcmp(exm.get_word(), "pensilcase") == 0);
    exm.set_word("case");
    REQUIRE(std::strcmp(exm.get_word(), "case") == 0);
}
TEST_CASE("word get")
{
    Word exm("terra");
    REQUIRE(exm.get_lenght() == 5);
    REQUIRE(std::strcmp(exm.get_word(), "terra") == 0);
}
TEST_CASE("word th")
{
    Word exmi("iuo");
    REQUIRE_THROWS(Word("te rra"));
    REQUIRE_THROWS(exmi.set_word("sds  sds"));
}
TEST_CASE("word set")
{
    Word copy1;
    Word exm("terra");
    exm.set_word("pen",3);
    REQUIRE(std::strcmp(exm.get_word(), "pen") == 0);
}
TEST_CASE("word =")
{
    Word copy1;
    Word exm("terra");
    copy1 = exm;
    REQUIRE(std::strcmp(copy1.get_word(), "terra") == 0);
}
TEST_CASE("word <=>")
{
    Word copy1;
    Word exm("terra");
    copy1 = exm;
    REQUIRE((copy1 <=> exm) == 0);
}
TEST_CASE("word chstr")
{
    Word copy1;
    Word exm("terra");
    copy1 = exm;
    REQUIRE(copy1.chstr("ter") == true);
    REQUIRE(copy1.chstr("teri") == false);
    REQUIRE_THROWS(copy1.chstr("terrdsdsd"));
}
TEST_CASE("word ewf")
{
    Word exm1;
    Word exm2("edfg");
    Word exm3("peni", 5);
    Word exm4(Word("tui"));
    Word exm5(exm1);
    REQUIRE(std::strcmp(exm2.get_word(), "edfg") == 0);
    REQUIRE(std::strcmp(exm3.get_word(), "peni") == 0);
    REQUIRE(std::strcmp(exm4.get_word(), "tui") == 0);
    REQUIRE(exm5.get_word() == nullptr);
    Word exm6(std::move(exm2));
    Word exm7(std::move(exm1));
    REQUIRE(std::strcmp(exm6.get_word(), "edfg") == 0);
    REQUIRE(exm7.get_word() == nullptr);
}
TEST_CASE("word input")
{
    std::stringstream stream1;
    std::stringstream stream2;
    Word exm("uiop");
    Word exm1("pen");
    stream1 << exm;
    REQUIRE(std::strcmp((stream1.str()).c_str(), "uiop\n") == 0);
    stream1 >> exm1;
    REQUIRE(std::strcmp(exm1.get_word(), "uiop") == 0);
}