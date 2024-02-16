#include<iostream>
#include<cstring>

#define MAX 50
using namespace std;

enum typeC {
    standard, loyal, vip
};

class UserExistsException {
public:
    void message() {
        cout << "The user already exists in the list!" << endl;
    }
};

class Customer {
    char name[MAX];
    char email[MAX];
    int type;
    int purchasedProducts;

    void copyC(const Customer &c) {
        strcpy(this->name, c.name);
        strcpy(this->email, c.email);
        this->type = (typeC) c.type;
        this->purchasedProducts = c.purchasedProducts;
    }

public:
    static int BASIC_DISCOUNT;
    const static int ADDITIONAL_DISCOUNT;

    Customer(const char *name = " ",const char *email = " ", int type = 0, int purchasedProducts = 0) {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->type = (typeC) type;
        this->purchasedProducts = purchasedProducts;
    }

    Customer(const Customer &c) {
        copyC(c);
    }

    Customer &operator=(const Customer &ot) {
        if (this != &ot) {
            copyC(ot);
        }
        return *this;
    }

    ~Customer() {

    }

    static void setDiscount1(int basicDiscount) {
        BASIC_DISCOUNT = basicDiscount;
    }

    friend ostream& operator<<(ostream& out, const Customer& c) {
        out << c.name << "\n" << c.email << "\n" << c.purchasedProducts << "\n";

        if(c.type == standard) {
            out << "standard 0";
        } else if(c.type == loyal) {
            out << "loyal " << c.BASIC_DISCOUNT;
        } else if(c.type == vip) {
            out << "vip " << c.BASIC_DISCOUNT + c.ADDITIONAL_DISCOUNT;
        }

        out << "\n";
        return out;
    }


    const char *getName() const {
        return name;
    }

    const char *getEmail() const {
        return email;
    }

    int getType() const {
        return type;
    }

    int getPurchasedProducts() const {
        return purchasedProducts;
    }

    void setType(int type) {
        Customer::type = type;
    }

};

class FINKI_bookstore {
    Customer *customers;
    int n;

    void copy(const FINKI_bookstore &c) {
        this->n = c.n;
        this->customers = new Customer[c.n];
        for (int i = 0; i < c.n; ++i) {
            this->customers[i] = c.customers[i];
        }
    }

public:
    FINKI_bookstore() {
        this->n = 0;
        this->customers = new Customer[n];
    }

    FINKI_bookstore(const FINKI_bookstore &c) {
        copy(c);
    }

    FINKI_bookstore &operator=(const FINKI_bookstore &o) {
        if (this != &o) {
            delete[] customers;
            copy(o);
        }
        return *this;
    }


    Customer *getCustomers() const {
        return customers;
    }


    int getN() const {
        return n;
    }

    FINKI_bookstore &operator+=(Customer &newCostumer) {
        for (int i = 0; i < n; ++i) {
            if (!strcmp(this->customers[i].getEmail(), newCostumer.getEmail())) {
                throw UserExistsException();
            }
        }
        Customer *tmp = new Customer[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = customers[i];
        }
        tmp[n++] = newCostumer;
        delete[] customers;
        customers = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const FINKI_bookstore &b) {
        for (int i = 0; i < b.n; i++) {
            os << b.customers[i];
        }
        return os;
    }

    void update() {
        for (int i = 0; i < n; i++) {
            if (customers[i].getPurchasedProducts() > 5 && customers[i].getType() == standard) {
                customers[i].setType(loyal);
            } else if (customers[i].getPurchasedProducts() > 10 && customers[i].getType() == loyal) {
                customers[i].setType(vip);
            }
        }
    }

    void setCustomers(Customer *customers, int n) {
        this->n = n;
        this->customers = new Customer[n];
        for (int i = 0; i < n; i++) {
            this->customers[i] = customers[i];
        }
    }

    ~FINKI_bookstore() {
        delete[] customers;
    }
};

int Customer::BASIC_DISCOUNT = 10;
const int Customer::ADDITIONAL_DISCOUNT = 20;


int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc += c;

        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;

        try {
            Customer c(name, email, (typeC) tC, numProducts);
            fc += c;
        } catch (UserExistsException &e) { e.message(); }

        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
