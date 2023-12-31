#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass
{
public:
    Comp();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

private:
    int cursize;
    int min_hash;
    int max_hash;
    void merge(std::vector<int> &v, int l, int m, int r);
    void mSort(std::vector<int> &v, int left, int right);
    std::vector<int> balances;
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
