#pragma once
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <future>
#include <regex>

class LogAnalyzer {
public:
    void analyze(const std::vector<std::string>& logFiles);

    // Результаты
    void printTopErrors(int topN = 3) const;
    void printRequestsByHour() const;

private:
    std::unordered_map<std::string, int> errorCounts_;
    std::map<int, int> requestsByHour_;
    std::mutex mutex_;

    void processFile(const std::string& filePath);
    
    void parseLine(const std::string& line);
};