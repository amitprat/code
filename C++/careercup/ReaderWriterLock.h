#include "../header.h"

class ReaderWriteLock {
    static std::map<std::string, int> teleBook{{"Dijkstra", 1972}, {"Scott", 1976}, {"Ritchie", 1983}};
    std::shared_timed_mutex teleBookMutex;

   public:
    void addToTeleBook(const std::string& na, int tele) {
        std::lock_guard<std::shared_timed_mutex> writerLock(teleBookMutex);

        std::cout << "\nSTARTING UPDATE " << na;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        teleBook[na] = tele;
        std::cout << " ... ENDING UPDATE " << na << std::endl;
    }

    void printNumber(const std::string& na) {
        std::shared_lock<std::shared_timed_mutex> readerLock(teleBookMutex);

        std::cout << na << ": " << teleBook[na];
    }

   public:
    static void test() {
        ReaderWriteLock obj;
        std::thread reader1([&obj] { obj.printNumber("Scott"); });
        std::thread reader2([&obj] { obj.printNumber("Ritchie"); });
        std::thread w1([&obj] { obj.addToTeleBook("Scott", 1968); });
        std::thread reader3([&obj] { obj.printNumber("Dijkstra"); });
        std::thread reader4([&obj] { obj.printNumber("Scott"); });
        std::thread w2([&obj] { obj.addToTeleBook("Bjarne", 1965); });
        std::thread reader5([&obj] { obj.printNumber("Scott"); });
        std::thread reader6([&obj] { obj.printNumber("Ritchie"); });
        std::thread reader7([&obj] { obj.printNumber("Scott"); });
        std::thread reader8([&obj] { obj.printNumber("Bjarne"); });

        reader1.join();
        reader2.join();
        reader3.join();
        reader4.join();
        reader5.join();
        reader6.join();
        reader7.join();
        reader8.join();
        w1.join();
        w2.join();

        std::cout << std::endl;

        std::cout << "\nThe new telephone book" << std::endl;
        for (auto teleIt : teleBook) {
            std::cout << teleIt.first << ": " << teleIt.second << std::endl;
        }

        std::cout << std::endl;
    }
};