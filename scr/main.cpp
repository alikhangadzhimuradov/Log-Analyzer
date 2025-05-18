#include <iostream>
#include "LogAnalyzer.h"
#include <vector>
#include <string>

int main() {
    LogAnalyzer analyzer;
    
    std::vector<std::string> logFiles = {
        "access.log",
        "error.log"
    };

    analyzer.analyze(logFiles);
    
    std::cout << "Analysis results:\n";
    analyzer.printTopErrors();
    analyzer.printRequestsByHour();

    return 0;
}
