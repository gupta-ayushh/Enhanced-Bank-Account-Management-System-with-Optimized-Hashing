#include "CubicProbing.h"
#include <cmath>

CubicProbing::CubicProbing()
{
    Account t;
    t.balance = -1;
    t.id = "";
    bankStorage1d.resize(100003, t);
    cursize = 0;
}
void CubicProbing::createAccount(std::string id, int count)
{
    Account temp;
    temp.id = id;
    temp.balance = count;
    long long int x = hash(id);
    long long int j = 1;
    long long int y = x;
    while (bankStorage1d[x].balance != -1)
    {
        x = y;
        x += j * j * j;
        x = x % 100000;
        j++;
    }
    bankStorage1d[x] = temp;
    cursize++;
}

void CubicProbing::merge(std::vector<int> &v, int l, int m, int r)
{
    long long int p1 = m - l + 1;
    long long int p2 = r - m;

    std::vector<long long int> L(p1), R(p2);

    for (long long int i = 0; i < p1; i++)
    {
        L[i] = v[l + i];
    }
    for (long long int i = 0; i < p2; i++)
    {
        R[i] = v[m + 1 + i];
    }

    long long int i = 0, j = 0, k = l;

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
void CubicProbing::mSort(std::vector<int> &v, int left, int right)
{
    if (left < right)
    {
        long long int mid = left + (right - left) / 2;

        mSort(v, left, mid);
        mSort(v, mid + 1, right);

        merge(v, left, mid, right);
    }
}

std::vector<int> CubicProbing::getTopK(int k)
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

int CubicProbing::getBalance(std::string id)
{
    long long int x = hash(id);
    long long int y = x;
    long long int j = 1;
    for (int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            return bankStorage1d[x].balance;
        }
        x = y;
        x += j * j * j;
        j++;
        x %= 100000;
    }
    return -1;
}

void CubicProbing::addTransaction(std::string id, int count)
{
    long long int x = hash(id);
    long long int j = 1;
    long long int y = x;
    long long int flag = 0;
    for (long long int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            bankStorage1d[x].balance+=count;
            flag = 1;
            break;
        }
        x = y;
        x += j * j * j;
        j++;
        x %= 100000;
    }
    if (flag == 0)
    {
        Account temp;
        temp.id = id;
        temp.balance = count;
        x=y;
        long long int j=1;
        while(bankStorage1d[x].balance!=-1){
            x=y;
            x+=j*j*j;
            j++;
            x%=100000;
        }
        bankStorage1d[x] = temp;
        cursize++;
    }
}

bool CubicProbing::doesExist(std::string id)
{
    long long int x = hash(id);
    long long int j = 1;
    long long int y = x;
    for (long long int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            return true;
        }
        x = y;
        x += j * j * j;
        j++;
        x %= 100000;
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id)
{
    long long int x = hash(id);
    long long int j = 1;
    long long int y = x;
    for (int i = 0; i < 100000; i++)
    {
        if (bankStorage1d[x].id == id)
        {
            bankStorage1d[x].balance=-1;
            bankStorage1d[x].id="";
            cursize--;
            return true;
        }
        x = y;
        x += j * j * j;
        j++;
        x %= 100000;
    }
    return false;
}

int CubicProbing::databaseSize()
{
    return cursize;
}

int CubicProbing::hash(std::string id)
{
    long long int ans = 0;
    long long int j = 0;
    long long int tem = 0;
    long long int count = 0;
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
