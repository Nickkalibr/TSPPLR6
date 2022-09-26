#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

class Client;

class ATM;

class Security;

class Bank;

class Client
{
    friend class ATM;
public:
    int Card_Number,
        Password,
        Attempt;
    double Money, 
        Card_Money;
    bool Check_Numb, Check_Pass;

    Client()
    {
        Card_Number = 0;
        Password = 0;
        Attempt = 0;
        Card_Money = 0; 
        Money = rand() % 10000 + 1;
        Check_Numb = Check_Pass = false;
    }

    void Set_Card_Number();
    void Set_Card_Pass();
    
};

class ATM
{
    friend class Client;

public:
    int tmpPass = 0, tmpNumb = 0;
    double tmpMoney = 0;
    void Enter_Pass();
    void Enter_Card_Number();
    void Money_Transfer(Client& c);
    void Give_Money(Client& c);
    void Add_Money(Client& c);
};

class Security
{
    friend class Client;
    friend class ATM;
public:
    void Check_Pass(Client& c, ATM& a);
};

class Bank
{
    friend class Client;
    friend class ATM;
public:
    void Check_Quan_Money(Client& c, ATM& a);
    void Check_Card_Number(Client& c, ATM& a);
    void Add_Money(Client& c, ATM& a);
};

void Client::Set_Card_Number()
{
    cout << "Введите номер карты (Номер должен состоять из 8 цифр): ";
    cin >> Card_Number;
    while (Card_Number < 10000000 || Card_Number > 100000000)
    {
        cout << "\nВы ввели неверный номер карты\n";
        cout << "Введите номер карты (Номер должен состоять из 8 цифр): ";
        cin >> Card_Number;
    }
    cout << "Ваш номер карты: " << Card_Number;
    Sleep(2000);
    _getch;
}

void Client::Set_Card_Pass()
{
    cout << "Введите PIN-код (PIN-код должен состоять из 4 цифр): ";
    cin >> Password;
    while (Password < 1000 || Password > 10000)
    {
        cout << "\nВы ввели неверный PIN-код\n";
        cout << "Введите PIN-код (PIN-код должен состоять из 4 цифр): ";
        cin >> Password;
    }
        cout << "Ваш PIN-код: " << Password;
        Sleep(2000);
    _getch;
}

void ATM::Enter_Pass()
{
    cout << "Введите PIN-код: ";
    cin >> tmpPass;
    while (tmpPass < 1000 || tmpPass > 10000)
    {
        cout << "\nВы ввели неверный PIN-код\n";
        cout << "Введите PIN-код (PIN-код должен состоять из 4 цифр): ";
        cin >> tmpPass;
    }
    cout << "Вы ввели следующий PIN-код: " << tmpPass;
    Sleep(2000);
    _getch;
}

void ATM::Enter_Card_Number()
{
    cout << "Введите номер карты: ";
    cin >> tmpNumb;
    while (tmpNumb < 10000000 || tmpNumb > 100000000)
    {
        cout << "\nВы ввели неверный номер карты\n";
        cout << "Введите номер карты (Номер должен состоять из 8 цифр): ";
        cin >> tmpNumb;
    }
    cout << "Вы ввели следующий номер карты: " << tmpNumb;
    Sleep(2000);
    _getch;
}

void ATM::Give_Money(Client& c)
{
    cout << "На вашем счету находится " << c.Card_Money << " рублей" << endl;
    cout << "Введите сумму которую необходимо выдать (Сумма не должна превышать 10000 рублей): ";
    cin >> tmpMoney;
    while (tmpMoney < 0 || tmpMoney > 10000)
    {
        cout << "\nВведена неверная сумма\n";
        cout << "Введите сумму которую необходимо выдать (Сумма не должна превышать 10000 рублей): ";
        cin >> tmpMoney;
    }
    cout << "Вы запросили следующую сумму: " << tmpMoney;
}

void ATM::Add_Money(Client& c)
{
    cout << "Введите сумму которую необходимо внести (Сумма не должна превышать 10000 рублей)";
    cin >> tmpMoney;
    while (tmpMoney < 0 || tmpMoney > 10000)
    {
        cout << "\nВведена неверная сумма\n";
        cout << "Введите сумму которую необходимо внести (Сумма не должна превышать 10000 рублей): ";
        cin >> tmpMoney;
    }
    cout << "Вы внесли следующую сумму: " << tmpMoney;
    c.Money = 0;
}

void Security::Check_Pass(Client& c, ATM& a)
{
    if (c.Password == a.tmpPass)
    {
        cout << "PIN-код введен верно\n";
        c.Check_Pass = true;
    }
    else
    {
        cout << "Введен неверный PIN-код, осталось попыток: " << c.Attempt++;
    }

    a.tmpPass = 0;
    _getch;
}

void Bank::Check_Card_Number(Client& c, ATM& a)
{
    if (c.Card_Number == a.tmpNumb)
    {
        cout << "Вы ввели верный номер карты ";
        c.Check_Numb = true;
    }
    else 
    {
        cout << "Вы ввели неверный номер карты ";
        c.Check_Numb = false;
    }
    Sleep(2000);
}

void Bank::Check_Quan_Money(Client& c, ATM& a)
{
    if (c.Card_Money < a.tmpMoney)
        cout << "Сумма превышает число денежных средств на счету";
    else 
    {
        cout << "Сумма не превышает число денежных средств на счету клиента";
        c.Card_Money = a.tmpMoney;
    }
    a.tmpMoney = 0;
    Sleep(2000);
}

void Bank::Add_Money(Client& c, ATM& a)
{
    c.Card_Money = a.tmpMoney;
    cout << "Сумма успешно внесена ";
    Sleep(2000);
    a.tmpMoney = 0;
}

int main()
{
    setlocale(LC_ALL, "rus");
    Client c;
    ATM a;
    Security s;
    Bank b;
    while (1)
    {
        int menu = 0;
        system("cls");
        cout << "Выберите пользователя: " << endl;
        cout << "1. Клиент" << endl;
        cout << "2. Банкомат" << endl;
        cout << "3. Служба безопасности" << endl;
        cout << "4. Банк" << endl;
        cout << "5. Выход" << endl;
        cin >> menu;
        switch (menu)
        {
        case 1:
            while (menu != 5)
            {
            system("cls");
            cout << "Выберите необходимый пункт:" << endl;
            cout << "1. Задать номер карты" << endl;
            cout << "2. Задать PIN-код" << endl;
            cout << "3. Выход" << endl;
            cin >> menu;
            switch (menu)
            {
            case 1:
                if (c.Card_Number != 0)
                {
                    cout << "Номер карты уже был задан";
                    Sleep(2000);
                }else 
                c.Set_Card_Number();
                break;
            case 2:
                if (c.Card_Number == 0)
                {
                    cout << "Вы не ввели номер карты";
                    Sleep(2000);
                }
                else
                if (c.Password != 0)
                {
                    cout << "PIN-код уже задан\n";
                    Sleep(2000);
                }
                else
                c.Set_Card_Pass();
                
                break;
            case 3: break;
            default:
                break;
            }
            
            }break;
        case 2:
            while (menu != 5)
            {
                system("cls");
                cout << "Выберите необходимы пункт: " << endl;
                cout << "1. Ввести номер карты" << endl;
                cout << "2. Ввести PIN-код" << endl;
                cout << "3. Запросить количество денежных средств имеющихся на счету клиента" << endl;
                cout << "4. Внос денежных средств на счёт клиента" << endl;
                cout << "5. Выход" << endl;
                cin >> menu;
                if (menu == 5)
                    break;
                switch (menu)
                {
                case 1: 
                    if (a.tmpNumb != 0)
                    {
                        cout << "Номер карты уже введен";
                        Sleep(2000);
                    } else
                    a.Enter_Card_Number();
                    break;
                case 2:
                    if (c.Check_Numb == false)
                    {
                        cout << "Невозможно ввести PIN-код предварительно не проверив номер карты";
                        Sleep(2000);
                        break;
                    }
                    else
                    {
                        if (a.tmpNumb == 0)
                        {
                            cout << "Вы не ввели номер карты";
                            Sleep(2000);
                            break;
                        }
                        if (c.Password == 0)
                        {
                            cout << "Вы не ввели PIN-код";
                            Sleep(2000);
                            break;
                        }
                        else if (a.tmpPass != 0)
                        {
                            cout << "PIN-код уже введён\n";
                            Sleep(2000);
                            break;
                        }
                        else
                            a.Enter_Pass();
                    }break;
                case 3:
                    if (a.tmpPass == 0 || a.tmpNumb == 0)
                    {
                        cout << "Вы не ввели номер карты или PIN-код";
                        Sleep(2000);
                        break;
                    }
                    else if (c.Check_Numb == false || c.Check_Pass == false)
                    {
                        cout << "Невозможно запросить денежные средства без проверки номера карты или PIN-кода";
                        Sleep(2000);
                        break;
                    }else
                        a.Give_Money(c);
                case 4:
                    if (a.tmpPass == 0 || a.tmpNumb == 0)
                    {
                        cout << "Вы не ввели номер карты или PIN-код";
                        Sleep(2000);
                        break;
                    }
                    else if (c.Check_Numb == false || c.Check_Pass)
                    {
                        cout << "Невозможно внести денежные средства без проверки номера карты или PIN-кода";
                        Sleep(2000);
                        break;
                    }
                    else
                        a.Add_Money(c);
                case 5: break;
                default:
                    break;
                }
                
            }break;
        case 3:
            while (menu != 2)
            {
                system("cls");
                cout << "Выберите необходимый пункт: " << endl;
                cout << "1. Проверить PIN-код" << endl;
                cout << "2. Выход" << endl;
                cin >> menu;
                if (menu == 2)
                    break;
                switch (menu)
                {
                case 1:
                    if (c.Password == 0 || a.tmpPass == 0)
                    {
                        cout << "Вы не задали PIN-код или не ввели его";
                        Sleep(2000);
                    }
                    else s.Check_Pass(c, a);
                    if (c.Attempt == 3)
                    { 
                        cout << "Вы трижды ввели неверный PIN-код. Вам отказано в доступе";
                        Sleep(2000);
                        return 0;
                    }
                default:
                    break;
                }
            }break;
        case 4:
            while (1)
            {
                system("cls");
                cout << "Выберите необходимый пункт: " << endl;
                cout << "1. Проверить номер карты" << endl;
                cout << "2. Выдать информацию о количестве денежных средств на счету клиента" << endl;
                cout << "3. Подтвердить внос денежных средств на счёт клиента" << endl;
                cout << "4. Выход" << endl;
                cin >> menu;
                if (menu == 4)
                    break;
                switch (menu)
                {
                case 1:
                    if (c.Card_Number == 0 || a.tmpNumb == 0)
                    {
                        cout << "Вы не задали номер карты или не ввели его";
                        Sleep(2000);
                        a.tmpNumb = 0;
                        break;
                    }
                    else b.Check_Card_Number(c, a); 
                    break;
                case 2:
                    if (c.Card_Number == 0 || a.tmpNumb == 0)
                    {
                        cout << "Вы не задали номер карты или не ввели его";
                        Sleep(2000);
                        a.tmpNumb = 0;
                        break;
                    }else 
                    b.Check_Quan_Money(c, a);
                    break;
                case 3:
                    if (c.Card_Number == 0 || a.tmpNumb == 0)
                    {
                        cout << "Вы не задали номер карты или не ввели его";
                        Sleep(2000);
                        a.tmpNumb = 0;
                        break;
                    }
                    else b.Add_Money(c, a);
                    break;
                default:
                    break;
                }
            }break;
        case 5: return 0;
        default:
            break;
        }
    }
}

