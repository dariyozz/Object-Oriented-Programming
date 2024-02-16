#include <iostream>
#include <cstring>

using namespace std;
enum tip {
    smartphone, computer
};

class InvalidProductionDate {
public:
    void message() {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device {
    char model[100];
    int type;
    static double BASIC_CHECK;
    int year;
public:
    Device(const char *model = "", int type = 0, int year = 2000) {
        strcpy(this->model, model);
        this->type = (tip) type;
        this->year = year;
    }

    Device(const Device &c) {
        strcpy(this->model, c.model);
        this->type = (tip) c.type;
        this->year = c.year;
    }

    static void setPocetniCasovi(double basicCheck) {
        BASIC_CHECK = basicCheck;
    }

    const char *getModel() const {
        return model;
    }

    int getYear() const {
        return year;
    }

    int calcHour() const {
        double s = Device::BASIC_CHECK;
        if (year > 2015) {
            s += 2;
        }
        if (type == computer) {
            s += 2;
        }
        return s;
    }

    friend ostream &operator<<(ostream &os, const Device &d) {
        os << d.model << endl;
        switch (d.type) {
            case smartphone:
                os << "Mobilen ";
                break;
            case computer:
                os << "Laptop ";
                break;
        }
        os << d.calcHour() << endl;
        return os;
    }
};

class MobileServis {
    char address[100];
    Device *dev;
    int n;

    void copy(const MobileServis &c) {
        strcpy(this->address, c.address);
        this->dev = new Device[c.n];
        for (int i = 0; i < c.n; ++i) {
            this->dev[i] = c.dev[i];
        }
        this->n = c.n;
    }

public:
    MobileServis(const char *address = "") {
        strcpy(this->address, address);
        this->dev = new Device[0];
        this->n = 0;
    }

    MobileServis(const MobileServis &c) {
        copy(c);
    }

    MobileServis &operator=(const MobileServis &o) {
        if (this != &o) {
            delete[] dev;
            copy(o);
        }
        return *this;
    }

    MobileServis &operator+=(const Device &newDev) {
        if (newDev.getYear() > 2019 || newDev.getYear() < 2000) {
            throw InvalidProductionDate();
        }
        Device *tmp = new Device[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = dev[i];
        }
        tmp[n++] = newDev;
        delete[] dev;
        dev = tmp;
        return *this;
    }

    void pecatiCasovi() {
        cout << "Ime: " << address << endl;
        for (int i = 0; i < n; ++i) {
            cout << dev[i];
        }
    }

    ~MobileServis() {
        delete[] dev;
    }
};

double Device::BASIC_CHECK = 1;

int main() {
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip) tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try { t += tmp; }
            catch (InvalidProductionDate &e) { e.message(); }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try { t += tmp; }
            catch (InvalidProductionDate &e) { e.message(); }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4) {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try { t += tmp; }
            catch (InvalidProductionDate &e) { e.message(); }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);

            try { t += tmp; }
            catch (InvalidProductionDate &e) { e.message(); }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6) {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip) tipDevice, godina);
            try { t += tmp; }
            catch (InvalidProductionDate &e) { e.message(); }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

