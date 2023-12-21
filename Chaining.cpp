#include "Chaining.h"
#include <cmath>

Chaining::Chaining()
{
    std::vector<Account> v;
    bankStorage2d.resize(100003, v);
    cursize = 0;
    max_hash = 0;
    min_hash = 100000;
}

void Chaining::merge(std::vector<int> &v, int l, int m, int r)
{
    int p1 = m - l + 1;
    int p2 = r - m;

    std::vector<int> L(p1), R(p2);

    for (int i = 0; i < p1; i++)
    {
        L[i] = v[l + i];
    }
    for (int i = 0; i < p2; i++)
    {
        R[i] = v[m + 1 + i];
    }

    int i = 0, j = 0, k = l;

    while (i < p1 && j < p2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < p1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < p2)
    {
        v[k] = R[j];
        k++;
        j++;
    }
}

void Chaining::mSort(std::vector<int> &v, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mSort(v, left, mid);
        mSort(v, mid + 1, right);

        merge(v, left, mid, right);
    }
}

void Chaining::createAccount(std::string id, int count)
{
    int h = hash(id);
    Account x;
    x.id = id;
    x.balance = count;
    bankStorage2d[h].push_back(x);
    cursize++;
}

std::vector<int> Chaining::getTopK(int k)
{
    std::vector<int> balances;
    for (int i = 0; i < 100000; i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            if (bankStorage2d[i][j].balance != -1)
            {
                balances.push_back(bankStorage2d[i][j].balance);
            }
        }
    }
    mSort(balances, 0, balances.size() - 1);
    std::vector<int> ans;
    if (cursize <= k)
    {
        for (int i = balances.size() - 1; i >= 0; i--)
        {
            ans.push_back(balances[i]);
        }
    }
    else
    {
        for (int i = balances.size() - 1; i > balances.size() - 1 - k; i--)
        {
            ans.push_back(balances[i]);
        }
    }
    return ans;
}

int Chaining::getBalance(std::string id)
{
    int h = hash(id);
    for (int i = 0; i < bankStorage2d[h].size(); i++)
    {
        if (bankStorage2d[h][i].id == id)
        {
            return bankStorage2d[h][i].balance;
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count)
{
    int h = hash(id);
    int flag = 0;
    for (int i = 0; i < bankStorage2d[h].size(); i++)
    {
        if (bankStorage2d[h][i].id == id)
        {
            bankStorage2d[h][i].balance += count;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        Account x;
        x.id = id;
        x.balance = count;
        bankStorage2d[h].push_back(x);
        cursize++;
    }
}

bool Chaining::doesExist(std::string id)
{
    int h = hash(id);
    for (int i = 0; i < bankStorage2d[h].size(); i++)
    {
        if (bankStorage2d[h][i].id == id)
        {
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id)
{
    int h = hash(id);
    for (int i = 0; i < bankStorage2d[h].size(); i++)
    {
        if (bankStorage2d[h][i].id == id)
        {
            bankStorage2d[h][i].balance = -1;
            bankStorage2d[h][i].id = "";
            cursize--;
            return true;
        }
    }
    return false;
}

int Chaining::databaseSize()
{
    return cursize;
}

int Chaining::hash(std::string id)
{
    int ans = 0;
    int j = 0;
    int tem = 0;
    int count = 0;
    for (auto i : id)
    {
        if (count <= 11)
        {
            tem = i;
            ans += tem * pow(2, j);
            ans %= 100000;
            j++;
        }
        else if (count > 12)
        {
            tem = i;
            ans += tem * pow(2, j);
            ans %= 100000;
            j--;
        }
        count++;
    }
    return ans % 100000;
}