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
TEST_CASE("words")
{
    const int len = 3;
    const char ** line = new const char*[3]("Tui","yui", "oop");
    Word exm("terra");
    Words el1(exm);
    Words el2;
    Words el3(len, line);
    Words el4(el3);
    REQUIRE(std::strcmp(el1[0].get_word(), "terra") == 0);
    REQUIRE_THROWS(el2[0]);
    REQUIRE(std::strcmp(el3[0].get_word(), "Tui") == 0);
    REQUIRE(std::strcmp(el4[1].get_word(), "yui") == 0);
    Words el5(std::move(el3));
    REQUIRE(std::strcmp(el4[2].get_word(), "oop") == 0);
}
TEST_CASE("words sort")
{
    const int len = 3;
    const char ** line = new const char*[3]("aui","cui", "bop");
    Word exm("terra");
    Words el1(len, line);
    el1.sort_up();
    REQUIRE(std::strcmp(el1[0].get_word(), "aui") == 0);
    REQUIRE(std::strcmp(el1[1].get_word(), "bop") == 0);
    REQUIRE(std::strcmp(el1[2].get_word(), "cui") == 0);
}
TEST_CASE("words input1")
{
    std::stringstream stream1;
    std::stringstream stream2;
    Word exm("uiop");
    Word exm1("pen");
    Words exm2;
    Words el1(exm1);
    stream1 << el1;
    REQUIRE(std::strcmp((stream1.str()).c_str(), "pen\n") == 0);
    stream2 << exm;
    stream2 >> exm2;
    
    REQUIRE(std::strcmp(exm2[0].get_word(), "uiop") == 0);
}
TEST_CASE("words input2")
{
    std::stringstream stream1;
    Words exm2;
    Words exm1;
    stream1 << "3"<<"pep"<< std::endl<<"pip"<< std::endl<<"pop"<< std::endl;
    exm2.insert_words(stream1);
    exm2.print_words(std::cout);
    REQUIRE(std::strcmp(exm2[0].get_word(), "pep") == 0);
    stream1 << "3"<<"pep"<< std::endl<<"pep"<< std::endl<<"pop"<< std::endl;
    REQUIRE_THROWS(exm1.insert_words(stream1));
}
TEST_CASE("words +=")
{
    const int len = 3;
    const char ** line = new const char*[3]("Tui", "yui", "oop");
    Word exm("terra");
    Words el1(exm);
    Words el2;
    Words el3(len, line);
    Words el4;
    el2+=el3;
    el3+=exm;
    REQUIRE_THROWS(el3+=exm);
    REQUIRE_THROWS(el2+=el3);
    REQUIRE(std::strcmp(el2[0].get_word(), "Tui") == 0);
    REQUIRE(std::strcmp(el3[3].get_word(), "terra") == 0);
}
TEST_CASE("words =")
{
    const int len = 3;
    const char ** line = new const char*[3]("Tui","yui", "oop");
    Word exm("terra");
    Words el1(exm);
    Words el2;
    Words el3(len, line);
    Words el4;
    el2 = el3;
    el4 = std::move(el3);
    REQUIRE(std::strcmp(el2[0].get_word(), "Tui") == 0);
    REQUIRE(std::strcmp(el4[2].get_word(), "oop") == 0);
}
TEST_CASE("words sub_let")
{
    const int len = 3;
    const char ** line = new const char*[3]("ypui","yui", "oop");
    Words el3(len, line);
    Vector<Word> pop = el3.sub_let('y');
    REQUIRE(std::strcmp(pop[0].get_word(), "ypui") == 0);
}
TEST_CASE("words find")
{
    const int len = 3;
    const char ** line = new const char*[3]("ypui","yui", "oop");
    Words el3(len, line);
    Word pip("ypui");
    Word pip1("ypui2");
    REQUIRE(std::strcmp((*el3.find_word(pip))->get_word(), "ypui") == 0);
    REQUIRE_THROWS((*el3.find_word(pip1)));
}