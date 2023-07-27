#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

class supermarket {
private:
    string pname;
    int pcode;
    float price;

public:
    void menu();
    void seller();
    void buyer();
    void add();
    void edit();
    void del();
    void List();
    void receipt();
    void report();
};

void supermarket::menu() {
start:
    string name;
    string password;
    name = "dave";
    password = "dave";
    int choice;
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "\tSUPERMARKET MAIN MENU" << endl;
    cout << "-------------------------------------------------------------------------" << endl << endl;
    cout << "\t1.Seller" << endl;
    cout << "\t2.Buyer" << endl;
    cout << "\t3.Exit" << endl;
    cout << "Enter your choice :";
    cin >> choice;
    system("cls");
    if (choice == 1) {
        cout << " LOG IN " << endl;
        cout << "Enter your username :";
        cin >> name;
        cout << "Enter your  password :" << endl;
        cin >> password;
        system("cls");
        if (password == "dave") {
            seller();
        }
        else {
            cout << " INVALID LOG IN DETAILS PLEASE ENTER CORRECT USERNAME OR PASSWORD !" << endl;
        }
    }
    else if (choice == 2) {
        buyer();
    }
    else if (choice == 3) {
        cout << "WELCOME BACK AGAIN" << endl;
        exit(0);
    }
    else {
        cout << "INVALID CHOICE TRY AGAIN !!" << endl;
    }
    goto start;
}

void supermarket::seller() {
start2:
    int choice;
    cout << "SELLER MENU" << endl;
    cout << "1.Add product" << endl;
    cout << "2.Delete product" << endl;
    cout << "3.Modify product" << endl;
    cout << "4.Check daily report" << endl;
    cout << "5.Back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    system("cls");
    if (choice == 1) {
        add();
    }
    else if (choice == 2) {
        del();
    }
    else if (choice == 3) {
        edit();
    }
    else if (choice == 4) {
        report();
    }
    else if (choice == 5) {
        menu();
    }
    else {
        cout << "INVALID CHOICE" << endl;
    }
    system("cls");
    goto start2;
}

void supermarket::buyer() {
start1:
    int choice;
    cout << "BUYER MENU" << endl;
    cout << "1.Buy product" << endl;
    cout << "2.Back to main menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    system("cls");
    if (choice == 1) {
        receipt();
    }
    else if (choice == 2) {
        menu();
    }
    else {
        cout << "INVALID CHOICE" << endl;
    }
    goto start1;
}

void supermarket::add() {
start2:
    fstream data;
    int c;
    int token = 0;
    float p;
    string n;

    cout << "ADD NEW PRODUCT" << endl;
    cout << "Product code: ";
    cin >> pcode;
    cout << "Product name: ";
    cin.ignore(); // Ignore the newline character left by previous input
    getline(cin, pname);
    cout << "Product price: ";
    cin >> price;
    system("cls");

    data.open("supermarket_database.txt", ios::in);

    if (!data) {
        data.open("supermarket_database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << endl;
        data.close();
    }
    else {
        data >> c >> n >> p;
        while (!data.eof()) {
            if (c == pcode) {
                token++;
            }
            data >> c >> n >> p;
        }
        data.close();

        if (token == 1) {
            goto start2;
        }
        else {
            data.open("supermarket_database.txt", ios::app | ios::out);
            data << pcode << " " << pname << " " << price << endl;
            data.close();
        }
    }
    cout << "Product added successfully" << endl;
}

void supermarket::edit() {
    fstream data, data1;
    int pkey;
    int c;
    int token = 0;
    float p;
    string n;

    cout << "MODIFY THE PRODUCT RECORD" << endl;
    cout << "Enter the product code: ";
    cin >> pkey;
    data.open("supermarket_database.txt", ios::in);
    if (!data) {
        cout << "The file does not exist" << endl;
    }
    else {
        data1.open("supermarket_database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "Enter new product code: ";
                cin >> c;
                cout << "Enter new product name: ";
                cin.ignore();
                getline(cin, n);
                cout << "Enter new product price: ";
                cin >> p;
                data1 << c << " " << n << " " << p << endl;
                cout << "PRODUCT MODIFIED SUCCESSFULLY" << endl;
                token++;
            }
            else {
                data1 << pcode << " " << pname << " " << price << endl;
            }
            data >> pcode >> pname >> price;
        }
        data.close();
        data1.close();

        remove("supermarket_database.txt");
        rename("supermarket_database1.txt", "supermarket_database.txt");

        if (token == 0) {
            cout << "SORRY RECORD NOT FOUND" << endl;
        }
    }
}

void supermarket::del() {
    fstream data, data1;
    int pkey;
    int c;
    int token = 0;
    float p;

    cout << "DELETE A PRODUCT" << endl;
    cout << "Enter product code: ";
    cin >> pkey;
    data.open("supermarket_database.txt", ios::in);
    if (!data) {
        cout << "The file does not exist" << endl;
    }
    else {
        data1.open("supermarket_database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price;
        while (!data.eof()) {
            if (pcode == pkey) {
                cout << "PRODUCT DELETED SUCCESSFULLY" << endl;
                token++;
            }
            else {
                data1 << pcode << " " << pname << " " << price << endl;
            }
            data >> pcode >> pname >> price;
        }
        data.close();
        data1.close();

        remove("supermarket_database.txt");
        rename("supermarket_database1.txt", "supermarket_database.txt");

        if (token == 0) {
            cout << "PRODUCT RECORD NOT FOUND" << endl;
        }
    }
}

void supermarket::List() {
    fstream data;
    data.open("supermarket_database.txt", ios::in);
    cout << "pcode \tname\tprice" << endl;
    data >> pcode >> pname >> price;
    while (!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << endl;
        data >> pcode >> pname >> price;
    }
    data.close();
}

void supermarket::receipt() {
    fstream data;

    int arc[100];
    char arq[100][100];
    char choice;
    int c = 0;
    float amount = 0;
    float total = 0;
    int choicez;

    cout << "RECEIPT" << endl;
    data.open("supermarket_database.txt", ios::in);
    if (!data) {
        cout << "EMPTY DATABASE" << endl;
    }
    else {
        data.close();
        List();
        cout << "Place an order:" << endl;
        do {
            start3:
            cout << "Enter the product code: ";
            cin >> arc[c];
            cout << "Enter the product name: ";
            cin.ignore();
            cin.getline(arq[c], 100);
            for (int i = 0; i < c; i++) {
                if (arc[c] == arc[i]) {
                    cout << "ERROR DUPLICATION OF PRODUCT" << endl;
                    goto start3;
                }
            }
            c++;
            cout << "Do you want to buy other product:" << endl;
            cout << "1.YES" << endl;
            cout << "2.NO" << endl;
            cin >> choice;

        } while (choice == '1');
        cout << "RECEIPT" << endl;
        cout << "Product no\tproduct name\tquantity\tamount" << endl;
        for (int i = 0; i < c; i++) {
            data.open("supermarket_database.txt", ios::in);
            data >> pcode >> pname >> price;
            while (!data.eof()) {
                if (pcode == arc[i]) {
                    amount = price;
                    total += amount;
                    cout << pcode << "\t" << arq[i] << "\t\t" << price << endl;
                }
                data >> pcode >> pname >> price;
            }
            data.close();
        }
    }
    cout << "Total amount: " << total << endl;
}

void supermarket::report() {
    List();
}

int main() {
    supermarket supermarket;
    supermarket.menu();

    return 0;
}
