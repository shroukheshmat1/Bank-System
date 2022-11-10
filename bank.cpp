#include <bits/stdc++.h>
using namespace std;
class BankAccount
{
protected:
    string id;
    double balance;
public:
    BankAccount(double b)
    {
        balance=b;
    }
    BankAccount()
    {
        balance=0.0;
    }
    void SetBalance(double b)
    {
        balance=b;
    }
    double GetBalance()
    {
        return balance;
    }
    void SetID(string str)
    {
        id=str;
    }
    string GetID()
    {
        return id;
    }
    double withdraw(double money)
    {
        if (balance>=money)
        {
             balance-=money;
        }
        else
            cout<<"insufficient money,your account has "<<balance<<" only"<<endl;
        return balance;
    }
    void deposit(double money)
    {
        balance+=money;
    }
};


class SavingsBankAccount: public BankAccount
{
private:
    double minibalance;
public:
    SavingsBankAccount()
    {
        minibalance=1000.0;
    }
    SavingsBankAccount(double b)
    {
        if (b>=minibalance)
            balance=b;
        else
            cout<<"minimum balance is 1000"<<endl;
    }
    double Getmini()
    {
        return minibalance;
    }
    double withdraw(double money)
    {
        if ((balance-money)>=minibalance)
            balance-=money;
        else
            cout<<"withdrawing is below the minimum balance"<<endl;
        return balance;
    }
    void deposit(double money)
    {
        if (money>=100)
            balance+=money;
        else
            cout<<"you can ONLY put 100 pounds or more as a deposit"<<endl;
    }
};



class Client
{
    private:
    string name,address,phone_number;
    public:
    Client(string str,string addr,string phone)
    {
        name=str;
        address=addr;
        phone_number=phone;
    }
};




int main()
{

}