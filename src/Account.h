#include <iostream>
#include <fstream>
using namespace std;

class Account
{
private:
    string pasword;
    string userName;
    string identityNum;
    double accountBalance = 0;

public:
    Account(string userName, string pasword, string identityNum)
    {

        this->userName = userName;
        this->pasword = pasword;
        this->identityNum = identityNum;
        accountBalance = 0.0;
    }
    string getPassword()
    {
        return this->pasword;
    }
    void setPassword(string password)
    {
        this->pasword = password;
    }
    string getUsername()
    {
        return this->userName;
    }
    void setUsername(string username)
    {
        this->userName = username;
    }
    string getIdentitynum()
    {
        return this->identityNum;
    }
    void setIdentitynum(string identityNum)
    {
        this->identityNum = identityNum;
    }
    double getAccbalance()
    {
        return this->accountBalance;
    }
    void setAccbalance(double accountBalance)
    {
        this->accountBalance = accountBalance;
    }

    friend Account *addAccount();
    friend void add_to_File(Account *acc);
    friend void add_to_CheckUpFile();
    friend Account loginAcc();
    friend void showAccount();
    friend void changePassword();
    friend void deleteAccount();
    friend void paraYatir();
    friend void paraCek();
    friend void hesabaTransfer();
    friend bool accControl();
    friend void showAccounts();
};

void add_to_File(Account *acc)
{

    ofstream accountsOut;

    accountsOut.open("accounts.txt", ios::app);
    accountsOut << acc->getIdentitynum() << " ";
    accountsOut << acc->getPassword() << " ";
    accountsOut << acc->getUsername() << " ";
    accountsOut << acc->getAccbalance() << endl;

    accountsOut.close();
}
void add_to_CheckUpFile(string ChechUpFile)
{
    string word;
    ofstream accountsCheckupOut(ChechUpFile);
    ifstream accoutsIn("accounts.txt");
    while (!accoutsIn.eof())
    {
        accoutsIn >> word;
        accountsCheckupOut << word << " ";
    }
    accountsCheckupOut.close();
    accoutsIn.close();
}
void clearExcess(string checkuptxtfile)
{
    ifstream accountIn(checkuptxtfile);
    ofstream accountOut("accounts.txt");
    string w1, w2;
    while (!(accountIn.eof()))
    {

        accountIn >> w1;
        accountIn >> w2;
        if (w1 == "0" && w2 == "0")
        {
            accountOut << w1 << " ";
            break;
        }
        accountOut << w1 << " ";
        accountOut << w2 << " ";
    }
    accountIn.close();
    accountOut.close();
    add_to_CheckUpFile("checkup.txt");
}
Account *addAccount(string identityNum, string username, string password)
{
    Account *h = new Account(username, password, identityNum);
    add_to_File(h);
    add_to_CheckUpFile("checkup.txt");
    return h;
}
Account loginAcc(string identityNum, string password)
{
    ifstream accounts("accounts.txt");
    Account reAcc("", "", "");
    string word;
    while (!(accounts.eof()))
    {
        accounts >> word;
        if (word == identityNum)
        {
            reAcc.setIdentitynum(word);
            accounts >> word;
            if (password == word)
            {
                reAcc.setPassword(word);
                accounts >> word;
                reAcc.setUsername(word);
                accounts >> word;
                reAcc.setAccbalance(stod(word));
                return reAcc;
            }
            else
            {
                cout << "Sifre yanlis" << endl;
            }
        }
    }
    reAcc.setIdentitynum("0");
    reAcc.setPassword("0");
    cout << "hesap bulunamadi" << endl;
    return reAcc;
}
void showAccount(Account acc)
{
    cout << "Hesap Bilgileri: \n"
         << "TC Kimlik No: " << acc.getIdentitynum() << endl
         << "Hesap sahibi adi: " << acc.getUsername() << endl
         << "Hesap bakiyesi: " << acc.getAccbalance() << endl;
}
void changePassword(Account acc)
{
    fflush(NULL);
    string newPassword;
    string word;
    ifstream accountsIn("checkup.txt");
    ofstream accountsOut("accounts.txt");

    while (!(accountsIn.eof()))
    {
        accountsIn >> word;
        if (word == acc.getIdentitynum())
        {
            accountsOut << word << " ";
            accountsIn >> word;
            cout << "Lutfen yeni sifreyi giriniz:"
                 << " ";
            cin >> newPassword;
            accountsOut << newPassword << " ";
            continue;
        }
        accountsOut << word << " ";
    }
    accountsIn.close();
    accountsOut.close();
}
void deleteAccount(Account acc)
{
    string word;
    ifstream accountsIn("checkup.txt");
    ofstream accountsOut("accounts.txt");

    while (!(accountsIn.eof()))
    {
        accountsIn >> word;
        if (word == acc.getIdentitynum())
        {
            for (int i = 0; i < 3; i++)
                accountsIn >> word;

            continue;
        }
        accountsOut << word << " ";
    }
    accountsIn.close();
    accountsOut.close();
}
void paraYatir(Account acc, double money)
{
    string word;
    ifstream accountsIn("checkup.txt");
    ofstream accountsOut("accounts.txt");

    while (!(accountsIn.eof()))
    {
        accountsIn >> word;
        if (word == acc.getIdentitynum())
        {
            accountsOut << word << " ";
            for (int i = 0; i < 2; i++)
            {
                accountsIn >> word;
                accountsOut << word << " ";
            }
            accountsIn >> word;
            double moneyBeyond = stod(word);
            money += moneyBeyond;
            accountsOut << money << " ";

            continue;
        }
        accountsOut << word << " ";
    }
    accountsIn.close();
    accountsOut.close();
}
void paraCek(Account acc, double money)
{
    string word;
    ifstream accountsIn("checkup.txt");
    ofstream accountsOut("accounts.txt");

    while (!(accountsIn.eof()))
    {
        accountsIn >> word;
        if (word == acc.getIdentitynum())
        {
            accountsOut << word << " ";
            for (int i = 0; i < 2; i++)
            {
                accountsIn >> word;
                accountsOut << word << " ";
            }
            accountsIn >> word;
            double moneyBeyond = stod(word);
            moneyBeyond -= money;
            accountsOut << moneyBeyond << " ";
            continue;
        }
        accountsOut << word << " ";
    }
    accountsIn.close();
    accountsOut.close();
}
void hesabaTransfer(string identityNum, double money)
{
    string word;
    ifstream accountsIn("checkup.txt");
    ofstream accountsOut("accounts.txt");

    while (!(accountsIn.eof()))
    {
        accountsIn >> word;
        if (word == identityNum)
        {
            accountsOut << word << " ";
            for (int i = 0; i < 2; i++)
            {
                accountsIn >> word;
                accountsOut << word << " ";
            }
            accountsIn >> word;
            double moneyBeyond = stod(word);
            money += moneyBeyond;
            accountsOut << money << " ";
            continue;
        }
        accountsOut << word << " ";
    }
    accountsIn.close();
    accountsOut.close();
}
bool accControl(string identityNum)
{
    string word;
    ifstream accountsIn("checkup.txt");
    while (!(accountsIn.eof()))
    {
        accountsIn >> word;
        if (word == identityNum)
        {
            return true;
        }
    }
    accountsIn.close();
    return false;
}
void showAccounts()
{
    ifstream accountsIn("accounts.txt");
    string word1;
    string word2;
    cout<<"HesapTC UserName Pass Balance"<<endl;
    while (!accountsIn.eof())
    {
        for (int i = 0; i < 2; i++)
        {
            accountsIn>>word1;
            accountsIn>>word2;
            if (word1=="0"&&word2=="0")
            {
               break; 
            }
            cout<<word1<<" ";
            cout<<word2<<" ";
            
            
        }
        cout<<endl;
    }
    accountsIn.close();
}
