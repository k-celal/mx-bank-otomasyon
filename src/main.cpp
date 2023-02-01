#include <iostream>
#include <fstream>
#include "Account.h"
using namespace std;
int main(int argc, char const *argv[])
{
    fflush(NULL);
    double money;
    string password;
    string identityNum;
    string userName;
    while (true)
    {
    silme:
    anamenu:
        
        cout << "MX BANK Banka islemlerine hosgeldiniz..." << endl;
        cout << "Yapmak istediginiz islemi giriniz..." << endl;
        cout << "1-Hesap islemlerine giris" << endl;
        cout << "2-Hesap olusturma" << endl;
        cout << "q-cikis" << endl;
        string choice;
        cin >> choice;
        if (choice == "1")
        {
            system("cls");
            cout << "TC kimlik no giriniz" << endl;
            cin >> identityNum;
            cout << "Sifre giriniz" << endl;
            cin >> password;
            Account acc = loginAcc(identityNum, password);
            system("cls");
            if (acc.getIdentitynum() == "0" && acc.getPassword() == "0")
            {
                cout << "sifre yanlis" << endl;
            }
            else
            {
                while (true)
                {
                    cout << "Merhaba " << acc.getUsername() << " hos geldin yapmak istedigin islemi secermisin? " << endl;
                    cout << "1-Hesap goruntuleme -> 1" << endl;
                    cout << "2-Sifre Degisme -> 2" << endl;
                    cout << "3-Hesap silme -> 3" << endl;
                    cout << "4-Para yatirma icin -> 4" << endl;
                    cout << "5-Para cekme -> 5" << endl;
                    cout << "6-Hesaplar arasi transfer -> 6" << endl;
                    cout << "7-Cikis icin -> 7" << endl;
                    if (acc.getUsername()=="AdminMX")
                    {
                        cout<<"8-Tum hesaplari listele"<<endl;
                    }
                    
                    string choice;
                    cin >> choice;
                    if (choice == "1")
                    {
                        cout << "Hesap gorutuleme islemlerine hosgeldiniz..." << endl;
                        showAccount(acc);
                    }
                    else if (choice == "2")
                    {
                        cout << "Sifre degisme islemine hosgeldiniz" << endl;
                        ;
                        changePassword(acc);
                        add_to_CheckUpFile("checkup.txt");
                        clearExcess("checkup.txt");
                    }
                    else if (choice == "3")
                    {
                        cout << "Hesap silme islemine hosgeldiniz. Hesabinizi silmek istediginizden eminmisiniz?(evet/hayir): ";
                        string secim;
                        cin >> secim;
                        if (secim == "evet")
                        {
                            cout << "Hesabiniz silindi iyi gunler " << endl;
                            deleteAccount(acc);
                            add_to_CheckUpFile("checkup.txt");
                            clearExcess("checkup.txt");
                            goto silme;
                        }
                        else if (secim == "hayir")
                        {
                            cout << "Ana menuye donuluyor... " << endl;
                            goto silme;
                        }
                        else
                        {
                            cout << "Lutfen evet veya hayir yaziniz!" << endl;
                        }
                    }
                    else if (choice == "4")
                    {
                        cout << "Lutfen yatirilacak parayi giriniz:" << endl;
                        cin >> money;
                        paraYatir(acc, money);
                        acc.setAccbalance((money) + acc.getAccbalance());
                        add_to_CheckUpFile("checkup.txt");
                        clearExcess("checkup.txt");
                    }

                    else if (choice == "5")
                    {
                        cout << "Lutfen cekilecek parayi giriniz:" << endl;
                        cin >> money;
                        if (money > acc.getAccbalance())
                        {
                            cout << "bakiye yetersiz" << endl;
                        }
                        else
                        {
                            paraCek(acc, money);
                            acc.setAccbalance(acc.getAccbalance() - (money));
                            add_to_CheckUpFile("checkup.txt");
                            clearExcess("checkup.txt");
                        }
                    }
                    else if (choice == "6")
                    {
                        string transferAcc;
                        cout << "Transfer yapmak istediginiz hesabin TC no sunu giriniz." << endl;
                        cin >> transferAcc;
                        if (accControl(transferAcc))
                        {
                            cout << "Transfer yapmak istediginiz miktrari giriniz." << endl;
                            cin >> money;
                            if (money > acc.getAccbalance())
                            {
                                cout << "bakiye yetersiz" << endl;
                            }
                            else
                            {
                                paraCek(acc, money);
                                acc.setAccbalance(acc.getAccbalance() - (money));
                                add_to_CheckUpFile("checkup.txt");
                                hesabaTransfer(transferAcc, money);
                                add_to_CheckUpFile("checkup.txt");
                                clearExcess("checkup.txt");
                            }
                        }
                        else
                        {
                            cout << "Transfer edilecek hesap bulunamadi" << endl;
                        }
                    }
                    else if (choice == "7")
                    {
                        cout << "Hoscakalin." << endl;
                        system("cls");
                        goto anamenu;
                        return 0;
                    }
                    else if(acc.getUsername()=="AdminMX" && choice=="8"){
                        showAccounts();
                    }
                    else
                    {
                        cout << "hatali islem..." << endl;
                    }
                }
            }
        }
        else if (choice == "2")
        {
            system("cls");
            cout << "Hesap ekleme islemine hosgeldiniz..." << endl;
            cout << "Lutfen TC No giriniz..." << endl;
            cin >> identityNum;
            if (accControl(identityNum))
            {
                cout << "Boyle bir hesap var lutfen giris yapiniz..."<<endl;
            }
            else
            {
                cout << "Lutfen kullanici adinizi giriniz..." << endl;
                cin >> userName;
                cout << "Lutfen sifrenizi giriniz..." << endl;
                cin >> password;
                addAccount(identityNum, userName, password);
            }
        }
        else if (choice == "q")
        {
            add_to_CheckUpFile("checkup.txt");
            clearExcess("checkup.txt");
            break;
        }
        else
        {
            cout << "yanlis secim" << endl;
        }
    }

    system("pause");
    return 0;
}
