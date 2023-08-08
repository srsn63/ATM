#include <bits/stdc++.h>
using namespace std;
class bank_account
{
    int acc_no;
    string user_name;
    double balance;

public:
    bank_account(){};
    bank_account(int a, string b, double c)
    {
        acc_no = a;
        user_name = b;
        balance = c;
    }
    void setAccno()
    {
        cout << "enter account number:";
        cin >> acc_no;
    }
    void setuserName()
    {
        cout << "enter account holder name:";

        getline(cin, user_name);
    }
    void setBalance()
    {
        cout << "enter balance:";
        cin >> balance;
    }
    void setBalance(double a)
    {
        balance = a;
    }
    friend void setAccountInfo(bank_account &b1);
    int get_acc_no()
    {
        return acc_no;
    }
    string getUsername()
    {
        return user_name;
    }
    double getBalance()
    {
        return balance;
    }

    void display_acc_details(bank_account &acc);
    void deposit(double a)
    {
        double b = getBalance();
        double f = b + a;
        setBalance(f);
    }
    void withdraw(double a)
    {
        double b = getBalance();
        double f = b - a;
        setBalance(f);
    }
};
void setAccountInfo(bank_account &b1)
{
    b1.setAccno();
    getchar();
    b1.setuserName();
    b1.setBalance();
}
void bank_account::display_acc_details(bank_account &acc)
{
    cout << "account no: " << acc.get_acc_no() << endl;
    cout << "user name : " << acc.getUsername() << endl;
    cout << "balance = " << acc.getBalance() << " Taka" << endl;
}
class user
{
    string name;
    int age;
    string address;
    vector<bank_account> accounts;

public:
    user() {}
    user(string name, int age, string address) : name(name), age(age), address(address) {}
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    string getAddress()
    {
        return address;
    }
    void addAcoount(bank_account acc)
    {
        accounts.push_back(acc);
    }
    vector<bank_account> &get_accounts()
    {
        return accounts;
    }
};
class transaction
{
public:
    static void withdraw(bank_account &acc, double a)
    {
        double b = acc.getBalance();
        if (a <= b)
        {
            acc.withdraw(a);
            cout << "Withdrawal Successfull . Current Balance = " << acc.getBalance() << " Taka." << endl;
        }
        else
        {
            cout << "Failed to withdraw due to insuffucuent balance" << endl;
        }
    }

    static void deposit(bank_account &acc, double a)
    {
        acc.deposit(a);
        cout << "Successfully Deposited.Current balance = " << acc.getBalance() << " Taka" << endl;
    }
    static void transfer(bank_account &sender, bank_account &receiver, double a)
    {
        if (a <= sender.getBalance())
        {
            sender.withdraw(a);
            receiver.deposit(a);
            cout << "Trannsaction Successfull" << endl;
            cout << "current balance of sender = " << sender.getBalance() << " Taka" << endl;
            cout << "current balance of receiver = " << receiver.getBalance() << " Taka" << endl;
        }
        else
        {
            cout << "Transaction failed due to insufficient Balance" << endl;
        }
    }
};
class ATM
{
    user *current_user;

public:
    ATM() {}
    void insert_card(user &user)
    {
        current_user = &user;
        cout << "Greetings Mr " << current_user->getName() << endl;
    }
    void withdrawMoney(bank_account &acc, double a)
    {
        transaction::withdraw(acc, a);
    }
    void depositMoney(bank_account &acc, double a)
    {
        transaction::deposit(acc, a);
    }
    void transferMoney(bank_account &sender, bank_account &receiver, double a)
    {
        transaction::transfer(sender, receiver, a);
    }
};
class ATMbooth
{
    vector<ATM> atms;

public:
    void add_ATM(ATM atm)
    {
        atms.push_back(atm);
    }
    ATM &get_ATM(int i)
    {
        return atms[i];
    }
};
class Bank
{
    vector<user> users;

public:
    void adduser(user u)
    {
        users.push_back(u);
    }
    user &getuser(int i)
    {
        return users[i];
    }
};
class Bank_Manager
{
    vector<Bank> banks;

public:
    void addBank(Bank b)
    {
        banks.push_back(b);
    }
    Bank &getbank(int i)
    {
        return banks[i];
    }
};
void options()
{
    cout << "------------------------" << endl;
    cout << endl;
    cout << "1. Withdraw Money " << endl;
    cout << "2. Deposit Money " << endl;
    cout << "3. Transfer Money " << endl;
    cout << "4. view account information " << endl;
    cout << "5. Exit " << endl;
    cout << "Choose any of the above: ";
    cout << "------------------------" << endl;
    cout << endl;
}

int main()
{
    ATMbooth atmb1;
    Bank_Manager bm1;
    Bank b1;
    user u1("Rahul Sheikh", 25, "67 green road");
    user u2("cr7", 38, "Portugal");
    bank_account acc1(12345, u1.getName(), 1000.89);
    bank_account acc2(6789, u2.getName(), 12000);
    u1.addAcoount(acc1);
    u2.addAcoount(acc2);
    b1.adduser(u1);
    b1.adduser(u2);
    bm1.addBank(b1);
    ATM atm1;
    atmb1.add_ATM(atm1);
    int account_choice;
    double amount;
    int choice;
    user &currentUser = u1;
    user &currentUser2 = u2;
    cout << "Welcome to the ATM made by KUET CSE 21 !!!!" << endl;
    cout << "Select your account : " << endl;
    cin >> account_choice;
    if (account_choice == 1)
    {
        cout << "It is " << u1.getName() << "'s account" << endl;

        atm1.insert_card(currentUser);
    }
    if (account_choice == 2)
    {
        cout << "It is " << u2.getName() << "'s account" << endl;
        atm1.insert_card(currentUser2);
    }

    do
    {
        options();
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter withdraw amount"<<endl;
            cin >> amount;
            if (account_choice == 1)
                atm1.withdrawMoney(currentUser.get_accounts()[0], amount);
            if (account_choice == 2)
                atm1.withdrawMoney(currentUser2.get_accounts()[0], amount);
            break;
        case 2:
            cout << "Enter deposit amount : "<<endl;
            cin >> amount;
            if (account_choice == 1)
                atm1.depositMoney(currentUser.get_accounts()[0], amount);
            if (account_choice == 2)
                atm1.depositMoney(currentUser2.get_accounts()[0], amount);
            break;
        case 3:
            cout << "enter transfer amount : ";
            cin >> amount;
            cout << "enter the account number to transfer to : ";
            cin >> account_choice;
            if (account_choice == 1)
                atm1.transferMoney(currentUser2.get_accounts()[0], currentUser.get_accounts()[0], amount);
            if (account_choice == 2)
                atm1.transferMoney(currentUser.get_accounts()[0], currentUser2.get_accounts()[0], amount);
            break;

        case 4:
            if (account_choice == 1)
                acc1.display_acc_details(acc1);
            else
                acc2.display_acc_details(acc2);
            break;

        case 5:
            cout << "Thank You for being with us." << endl;
            break;
        default:
            cout << "Inavlid choice~~~~~~~~~Try Again" << endl;
        }

    } while (choice != 5);
}