Выбор структур:

std::deque взял, так как
O(1) добавление/удаление с обоих концов

std::vector взял из-за того что это
стандартный контейнер для возврата результатов

Для запуска тестов
из директории Part_2 выполнить

mkdir bin
g++ -std=c++23 -Iinclude -o bin/TopTrackerTests tests/TopTrackerTests.cpp src/TopTracker.cpp
.\bin\TopTrackerTests