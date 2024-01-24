#pragma once
#include "../header.h"

class IBank {

};

class CitiBank : public IBank {

};

class ChaseBank : public IBank {

};

class IFinanceManager {

};

class FinanceManager : public IFinanceManager
{

};

class FinaanceManagerTest {
public:
    static void test() {
        IBank* bank1 = new CitiBank();
        IBank* bank2 = new ChaseBank();
        CreateSomeSpendings(bank1, bank2);

        IAlertManager* alertManager = new AlertManager();

        IFinanceManager* manager = new FinanceManager();
        manager->init();
        manager->addBankAccount(bank1);
        manager->addBankAccount(bank2);
        manager->addAlertManager(alertManager);

        auto spendings = manager->getHistory(Duration::LastMonth);
        manager->prettyPrint(spendings);

        manager->assignCategory(fromSet, targetName1);
        manager->assignCategory(timeWindows, targetName2);

        spendings = manager->getHistory(Duration::LastMonth);
        manager->prettyPrint(spendings);

        spendings = manager->getHistory(Duration::LastMonth, SortBy::MostSpendingCategory);
        manager->prettyPrint(spendings);

        auto res = manager->setLimit(category, amount, Type::Alert);
        CreateSomeSpendings(bank1, bank2);

        manager->printAlerts();

        manager->removeBankAccount(bank1->getId());

        CreateSomeSpendings(bank1, bank2);

        spendings = manager->getHistory(Duration::LastMonth, SortBy::MostSpendingCategory);
        manager->prettyPrint(spendings);
    }
};