Описание:

Анализатор логов, который обрабатывает несколько файлов параллельно. Считает:


Топ-N самых частых ошибок (HTTP 4xx/5xx).

Количество запросов по часам.


Формат логов:

    [2023-10-01 12:34:56] ERROR 404 Not Found
    
    [2023-10-01 12:35:01] INFO 200 OK

Использование:

    LogAnalyzer analyzer;
    
    analyzer.analyze({"logs/access.log", "logs/error.log"});
    
    analyzer.printTopErrors(3);

Сборка:

    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    ./log_analyzer

Что демонстрирует:

Многопоточную обработку данных.

Работу с файлами и регулярными выражениями.

Использование STL-контейнеров (unordered_map, vector).
