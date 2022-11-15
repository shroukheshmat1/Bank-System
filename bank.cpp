#include <bits/stdc++.h>
using namespace std;
class Client;
class BankAccount;
class SavingsBankAccount;
class Bankapplication;

class Client
{
private:
    string name,address,phone_number;
    BankAccount* ptr1;
    SavingsBankAccount* ptr2;
public:
    Client (){};
    Client(string str,string addr,string phone)
    {
        name=str;
        address=addr;
        phone_number=phone;
    };
    Client(BankAccount &acc)
    {
        ptr1=&acc;
    };
    Client(SavingsBankAccount &acc){
        ptr2=&acc;
    };

};

class BankAccount
{
protected:
    string id;
    double balance;
    Client* cptr;
public:
    //BankAccount(string Id)
    BankAccount(double b){
        balance=b;
    }
    BankAccount(Client& c){
        cptr=&c;
    }
    BankAccount(){
//        id="FCAI-";

        balance=0.0;
    }
    void SetBalance(double b){
        balance=b;
    }
    double GetBalance(){
        return balance;
    }
    void SetID(string str){
        id=str;
    }

    string GetID(){
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
    using BankAccount::BankAccount;
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

class Bankapplication
{
    int choice;
public:
    static int no;
    void newacc();
    void loadfile (vector<string>& text, fstream& file)
    {
        char filename[100],line[100];
        cout<<"please enter your filename"<<endl;
        cin>>filename;
        file.open(filename);
        if (file.is_open())
        {
            cout<<"file is opened successfully"<<endl;
            while (!file.eof())
            {
                file.getline(line, 200, '\n');
                text.push_back(string (line) );
            }
        }
        else
        {
            char name[100];
            cout<<"this file couldn't be opened"<<endl;
            cout<<"please enter the name of the new file you want to create"<<endl;
            cin>>name;
            cout<<"a new file will be created when saving";
        }
    }
    void save_updated(vector<string>& text)
    {
        ofstream file;
        char filename[100];
        cout<<"please enter the name of the file you want to save changes on it: "<<endl;
        cin>>filename;
        file.open(filename, ios :: out | ios::trunc);
        for (string line: text){
            file << line << endl;
        }
        file.close();
    }
    void withdraw(vector<string>& text, fstream& file)
    {
        loadfile(text,file);
        cout<<"please enter your id: ";
        string id;
        cin>>id;
        for (int i=3;i<text.size();i+=5)
        {
            if (id==text[i])
            {
                cout<<"please enter the type of your account:\n 1-normal bank account \n 2-saving account: "<<endl;
                int ans;
                cin>>ans;
                if (ans==1)
                {
                    cout<<"please enter the amount you want to withdraw it";
                    float withdraw_money;
                    cin>>withdraw_money;
                    float balance=stoi(text[i+1]);
                    if (balance-withdraw_money>=0)
                    {
                        balance -= withdraw_money;
                        text[i+1]= to_string(balance);
                    }
                    else
                        cout<<"you can't withdraw this money,as there's no sufficient money"<<endl;
                    if (i<text.size()-1)
                        continue;
                }
                else if (ans==2)
                {
                    cout<<"please enter the amount you want to withdraw it which MUST be less than or equal 1000 LE";
                    float withdraw_money;
                    cin>>withdraw_money;
                    if (withdraw_money>1000)
                    {
                        cout<<"you put greater than 1000 as a deposit which is NOT available \n please choose whether to:"<<endl;
                        cout<<"1-re-enter a withdraw money \n 2-exit";
                        int anss;
                        cin>>anss;
                        if (anss==1)
                            continue;
                        else if (anss==2)
                            break;
                    }
                    float balance=stoi(text[i+1]);
                    if (balance-withdraw_money>0)
                    {
                        balance -= withdraw_money;
                        text[i+1]= to_string(balance);
                    }
                    else
                        cout<<"you can't withdraw this money,as there's no sufficient money"<<endl;
                    if (i<text.size()-1)
                        continue;
                }

            }
            else if (id!=text[i] && i==text.size()-1)
            {
                cout<<"Invalid ID,please choose whether to 1)enter a valid one or 2)register a new client: "<<endl;
                int choice;
                cin>>choice;
                if (choice==1)
                {
                    continue;
                }
                else if (choice==2)
                {
                    newacc();
                    break;
                }
            }
        }
        save_updated(text);
    }

    void deposit(vector<string>& text, fstream& file)
    {
        loadfile(text,file);
        cout<<"please enter your id: ";
        string id;
        cin>>id;
        for (int i=3;i<text.size();i+=5)
        {
            if (id==text[i])
            {
                cout<<"please enter the amount you want to deposit it";
                float deposit_money;
                cin>>deposit_money;
                float balance=stoi(text[i+1]);
                if (deposit_money>100)
                {
                    balance+=deposit_money;
                    text[i+1]= to_string(balance);
                }
                else
                    cout<<"you can't diposit this amount of money,please put at least 100 LE"<<endl;
            }
            else if (id!=text[i] && i==text.size()-1)
            {
                cout<<"Invalid ID,please choose whether to 1)enter a valid one or 2)register a new client: "<<endl;
                int choice;
                cin>>choice;
                if (choice==1)
                {
                    continue;
                }
                else if (choice==2)
                {
                    newacc();
                    break;
                }
            }
        }
        save_updated(text);
    }

    void displaymenu()
    {
        cout<<"Welcome to FCAI Banking Application\n"
              "1. Create a New Account\n"
              "2. List Clients and Accounts\n"
              "3. Withdraw Money\n"
              "4. Deposit Money\n"
              "Please Enter Choice =========>"<<endl;
        cin>>choice;
        vector <string> bank_vector;
        vector <string> updated_bank_vector;
        fstream file;
        if(choice==1){
            newacc();
        }
        if(choice==2){
            loadfile(bank_vector,file);
            for (int i=0;i<bank_vector.size();i++)
                cout<<bank_vector[i]<<endl;
        }
        if(choice==3)
        {
            withdraw(bank_vector, file);
        }
        if(choice==4){
            deposit(bank_vector, file);
        }
    }

};
    int Bankapplication::no=1;
    void Bankapplication:: newacc()
    {
    ofstream file;
    file.open("Banksystem.txt", ios::app);
    //Client person;
    string name,address,phone;
    cout<<"Please Enter Client FullName"<<endl;
    cin.ignore();
    getline(cin,name);
    file<<name;
    file<<"\n";
    cout<<"Please Enter Client Address"<<endl;
    cin>>address;
    file<<address;
    file<<"\n";
    cout<<"Please Enter Client Phone"<<endl;
    cin>>phone;
    file<<phone;
    file<<"\n";
    Client person(name,address,phone);
    BankAccount B1(person);
    int flag;
//        int static no=1;
    no=1;
    cout<<"What Type of Account Do You Like? (1) Basic (2) Saving : Type 1 or 2"<<endl;
    cin>>flag;
    if(flag==1){
        //BankAccount B1;
        cout<<"Please Enter the Starting Balance"<<endl;
        double bal;
        cin>>bal;
        string id;
        for(int i=0;i<name.length();i++){
            if(isspace(name[i]) ){
                name[i]='_';
            }
        }
        id=name;
        //id = B1.GetID();

        B1.SetID(id);
        file << id;
        file<<"\n";
        file<<bal;
        file<<"\n";
        B1.SetBalance(bal);
        //BankAccount(balance);
        //BankAccount(person);
    }
    else if(flag==2){
        //SavingsBankAccount B2;
        cout<<"Please Enter the Starting Balance at least 1000$"<<endl;
        double  balance;
        cin>>balance;
        SavingsBankAccount B2(person);
        B2.SetBalance(balance);

        string id;
        for(int i=0;i<name.length();i++){
            if(isspace(name[i]) ){
                name[i]='_';
            }
        }
        id=name;
        B1.SetID(id);
        file<<balance;
    }
    file.close();
    //   return file;
    };
    void withdraw(float no)
    {

    };
int main() {
    Bankapplication b;
    b.displaymenu();
//    int flag=2;
//    while(flag--){
//        //ofstream file;
//        b.newacc();
//    }

    return 0;
}
