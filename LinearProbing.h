#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    LinearProbing();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    void merge(std::vector<int> &v,int l,int m, int r);
    void mSort(std::vector<int> &v,int left,int right);
    int cursize;
    int max_hash;
    int min_hash;
    std::vector <int> balances;
};

#endif // LINEARPROBING_H
