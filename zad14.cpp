#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

class SMS {
protected:
    double price;
    char num[16];
    static double ddv;
public:
    SMS(char *num = " ", double price = 0.0) {
        strcpy(this->num, num);
        this->price = price;
    }

    SMS(const SMS &other) {
        strcpy(this->num, other.num);
        this->price = other.price;
    }

    SMS &operator=(const SMS &other) {
        if (this == &other) {
            return *this;
        }
        strcpy(this->num, other.num);
        this->price = other.price;
        return *this;
    }

    friend ostream &operator<<(ostream &out, SMS &sms) {
        out << "Tel: " << sms.num << " - cena: " << sms.SMS_cena() << "den.\n";
        return out;
    }

    virtual double SMS_cena() = 0;

    ~SMS() {}
};

class RegularSMS : public SMS {
    bool roaming;
    char message[1000];
    static double procenti_300;
public:
    RegularSMS(char *num = " ", double price = 0.0, char *message = " ", bool roaming = true)
            : SMS(num, price) {
        strcpy(this->message, message);
        this->roaming = roaming;
    }

    RegularSMS(const RegularSMS &other) : SMS(other) {
        this->roaming = other.roaming;
        strcpy(this->message, other.message);

    }

    RegularSMS &operator=(const RegularSMS &other) {
        if (this == &other) {
            return *this;
        }
        SMS::operator=(other);
        this->roaming = other.roaming;
        strcpy(this->message, other.message);
        return *this;
    }

    static void set_rProcent(double val) {
        RegularSMS::procenti_300 = 1.0 + (val / 100);
    }

    double SMS_cena() override {
        double x = roaming ? procenti_300 : ddv;
        return price * x * ceil(strlen(message) / 160.0);
    }

    ~RegularSMS() {}
};

class SpecialSMS : public SMS {
    bool hum;
    static double procenti_150;

public:
    SpecialSMS(char *num = " ", double price = 0.0, bool hum = true)
            : SMS(num, price) {
        this->hum = hum;
    }

    SpecialSMS(const SpecialSMS &other) {
        this->hum = other.hum;
    }

    SpecialSMS &operator=(const SpecialSMS &other) {
        if (this == &other) {
            return *this;
        }
        SMS::operator=(other);
        this->hum = other.hum;
        return *this;
    }

    static void set_sProcent(double val) {
        SpecialSMS::procenti_150 = 1 + (val / 100);
    }

    double SMS_cena() override {
        return hum ? price : price * procenti_150;
    }

    ~SpecialSMS() {}
};

void vkupno_SMS(SMS **poraka, int n) {
    int vkSpec = 0, vkReg = 0;
    double vkSpecCena = 0.0, vkRegCena = 0.0;
    for (int i = 0; i < n; ++i) {
        if (dynamic_cast<RegularSMS *>(poraka[i])) {
            vkReg++;
            vkRegCena += poraka[i]->SMS_cena();
        } else if (dynamic_cast<SpecialSMS *>(poraka[i])) {
            vkSpec++;
            vkSpecCena += poraka[i]->SMS_cena();
        }
    }
    cout << "Vkupno ima " << vkReg << " regularni SMS poraki i nivnata cena e: " << vkRegCena << "\n";
    cout << "Vkupno ima " << vkSpec << " specijalni SMS poraki i nivnata cena e: " << vkSpecCena << "\n";
}

double RegularSMS::procenti_300 = 3.0;
float SpecialSMS::procenti_150 = 2.5;
float SMS::ddv = 1.18;

int main() {

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2) {
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3) {
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            } else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i < n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4) {
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5) {
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
