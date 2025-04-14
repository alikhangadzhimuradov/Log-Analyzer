#include <iostream>
#include "/Users/alikhangadzhimuradov/Desktop/LogAnalyzer/include/LogAnalyzer.h"
#include <vector>
#include <string>

int main() {
    LogAnalyzer analyzer;
    
    std::vector<std::string> logFiles = {
        "/Users/alikhangadzhimuradov/Desktop/LogAnalyzer/logs/access.log",
        "/Users/alikhangadzhimuradov/Desktop/LogAnalyzer/logs/error.log"
    };

    analyzer.analyze(logFiles);
    
    std::cout << "Analysis results:\n";
    analyzer.printTopErrors();
    analyzer.printRequestsByHour();

    return 0;
}