#include <gtest/gtest.h>
#include <thread>
#include <future>
#include <chrono>
#include <condition_variable>
#include "client.hpp"
#include "server.hpp"
#include "serverGr.hpp"
using namespace std::chrono_literals;

TEST(pep1, ConnectsToBothServers1) {
    Client_K cl;
    testing::internal::CaptureStdout();
    cl.send_request("ip ip ip");
    std::this_thread::sleep_for(250ms);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output == "message : \"ip\"\n");
}
TEST(pep2, ConnectsToBothServers2) {
    Client_K cl;
    testing::internal::CaptureStdout();
    cl.send_request("p p p p p p");
    std::this_thread::sleep_for(250ms);
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output << std::endl;
    EXPECT_TRUE(output == "message : \"p\"\n");
}
TEST(pep2, ConnectsToBothServers3) {
    Client_K cl;
    testing::internal::CaptureStdout();
    cl.send_request("       ");
    std::this_thread::sleep_for(250ms);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output == "message : ");
}
TEST(pep2, ConnectsToBothServers4) {
    Client_K cl;
    testing::internal::CaptureStdout();
    cl.send_request("       pppppp ooo ooo          p p p p      qq q       ");
    std::this_thread::sleep_for(250ms);
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output << std::endl;
    EXPECT_TRUE(output == "message : \"pppppp ooo p qq q\"\n");
}
TEST(pep2, ConnectsToBothServers5) {
    Client_K cl;
    std::string result(1999 * 2 + 1, 'p');
    for (size_t i = 1; i < result.size(); i += 2) {
        result[i] = ' ';
    }
    testing::internal::CaptureStdout();
    cl.send_request(result);
    std::this_thread::sleep_for(250ms);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output == "message : \"p\"\n");
}
TEST(pep2, ConnectsToBothServers6) {
    Client_K cl;
    std::string result(19990 * 2 + 1, 'p');
    for (size_t i = 1; i < result.size(); i += 2) {
        result[i] = ' ';
    }
    testing::internal::CaptureStdout();
    cl.send_request(result);
    std::this_thread::sleep_for(250ms);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output == "message : \"p\"\n");
}
TEST(pep2, ConnectsToBothServers7) {
    EXPECT_THROW(Client_K cl(1000), std::exception);
}

int main(int argc, char **argv) {
    Graph_server g_ser;
    Main_server m_ser;
    std::thread([&]() { g_ser.start(); }).detach();
    std::thread([&]() { m_ser.start(); }).detach();
    std::this_thread::sleep_for(250ms);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}