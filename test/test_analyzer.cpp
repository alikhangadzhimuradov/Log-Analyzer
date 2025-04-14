#include "/Users/alikhangadzhimuradov/Desktop/LogAnalyzer/include/LogAnalyzer.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>

using namespace std;

TEST(LogAnalyzerTest, BasicParsing) {
    ofstream tmpFile("test.log");
    tmpFile << "[2023-10-01 12:34:56] ERROR 404 Not Found\n";
    tmpFile << "[2023-10-01 12:35:01] INFO 200 OK\n";
    tmpFile.close();

    LogAnalyzer analyzer;
    analyzer.analyze({"test.log"});

    testing::internal::CaptureStdout();
    analyzer.printTopErrors(1);
    string output = testing::internal::GetCapturedStdout();

    ASSERT_TRUE(output.find("404 Not Found") != string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}