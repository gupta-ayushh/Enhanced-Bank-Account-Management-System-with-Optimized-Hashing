#include "LinearProbing.h"
#include <cmath>

LinearProbing::LinearProbing()
{
    Account t;
    t.balance = -1;
    t.id = "";
    bankStorage1d.resize(100000, t);
    cursize = 0;
}
void LinearProbing::createAccount(std::string id, int count)
{
    int h = hash(id);
    Account temp;
    temp.id = id;
    temp.balance = count;
    while (bankStorage1d[h].balance != -1)
    {
        h++;
        h = h % 100000;
    }
    bankStorage1d[h] = temp;
    cursize++;
}
void LinearProbing::merge(std::vector<int> &v, int l, int m, int r)
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
void LinearProbing::mSort(std::vector<int> &v, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mSort(v, left, mid);
        mSort(v, mid + 1, right);

        merge(v, left, mid, right);
    }
}

std::vector<int> LinearProbing::getTopK(int k)
{
    std::vector<int> balances;
    for (int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[i].balance != -1)
        {
            balances.push_back(bankStorage1d[i].balance);
        }
    }
    mSort(balances, 0, balances.size() - 1);
    std::vector<int> temp;
    if (cursize <= k)
    {
        for (int i = balances.size() - 1; i >= 0; i--)
        {
            temp.push_back(balances[i]);
        }
    }
    else
    {
        for (int i = balances.size() - 1; i > balances.size() - 1 - k; i--)
        {
            temp.push_back(balances[i]);
        }
    }
    return temp;
}

int LinearProbing::getBalance(std::string id)
{
    int x = hash(id);
    for (int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            return bankStorage1d[x].balance;
        }
        x++;
        x %= 100000;
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count)
{
    int x = hash(id);
    int flag = 0;
    for (int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            bankStorage1d[x].balance+=count;
            flag=1;
            break;
        }
        x++;
        x %= 100000;
    }
    if (flag == 0)
    {
        Account temp;
        temp.id = id;
        temp.balance = count;
        int x = hash(id);
        while (bankStorage1d[x].balance != -1)
        {
            x++;
            x %= 100000;
        }
        bankStorage1d[x] = temp;
        cursize++;
    }
}

bool LinearProbing::doesExist(std::string id)
{
    int x = hash(id);
    for (int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            return true;
        }
        x++;
        x %= 100000;
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id)
{
    int x = hash(id);
    for (int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            bankStorage1d[x].balance = -1;
            bankStorage1d[x].id = "";
            cursize--;
            return true;
        }
        x++;
        x %= 100000;
    }
    return false;
}

int LinearProbing::databaseSize()
{
    return cursize;
}

int LinearProbing::hash(std::string id)
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
