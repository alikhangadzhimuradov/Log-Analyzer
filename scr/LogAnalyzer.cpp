#include "LogAnalyzer.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void LogAnalyzer::analyze(const vector<string>& logFiles) {
    vector<future<void>> futures;

    for (const auto& file : logFiles) {
        futures.emplace_back(async(launch::async, &LogAnalyzer::processFile, this, file));
    }

    for (auto& fut : futures) {
        fut.get();
    }
}

void LogAnalyzer::processFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        parseLine(line);
    }
}

void LogAnalyzer::parseLine(const string& line) {
    static const regex logRegex(R"(\[(\d{4}-\d{2}-\d{2} (\d{2}):\d{2}:\d{2})\]\s+(\w+)\s+(\d+).*)");
    smatch match;

    if (regex_search(line, match, logRegex)) {
        lock_guard<mutex> lock(mutex_);

        int hour = stoi(match[2]);
        requestsByHour_[hour]++;

        string status = match[3];
        int code = stoi(match[4]);
        if (code >= 400 && code < 600) {
            errorCounts_[status + " " + match[4].str()]++;
        }
    }
}

void LogAnalyzer::printTopErrors(int topN) const {
    vector<pair<string, int>> errors(errorCounts_.begin(), errorCounts_.end());
    sort(errors.begin(), errors.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "\nTop-" << topN << " errors:\n";
    for (size_t i = 0; i < min(errors.size(), static_cast<size_t>(topN)); ++i) {
        cout << " - " << errors[i].first << ": " << errors[i].second << " times\n";
    }
}

void LogAnalyzer::printRequestsByHour() const {
    cout << "\nRequests per hour:\n";
    for (const auto& [hour, count] : requestsByHour_) {
        cout << " - " << hour << ":00 - " << count << " requests\n";
    }
}
