#include<iostream>
#include<cstring>

using namespace std;

class OutOfBoundException {
public:
    void message() {
        cout << "Brojot na pin kodovi ne moze da go nadmine dozvolenoto" << endl;
    }
};

class Karticka {
private:
    void copyK(const Karticka &c) {
        strcpy(this->smetka, c.smetka);
        this->pin = c.pin;
        this->povekjePin = c.povekjePin;
    }

protected:
    char smetka[16];
    int pin;
    bool povekjePin;
    const static int P;
public:
    Karticka(const char *smetka = " ", int pin = 0) {
        strcpy(this->smetka, smetka);
        this->pin = pin;
        this->povekjePin = false;
    }

    Karticka(const Karticka &c) {
        copyK(c);
    }

    Karticka &operator=(const Karticka &o) {
        if (this != &o) {
            copyK(o);
        }
        return *this;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }

    const char *getSmetka() const {
        return smetka;
    }

    virtual int tezinaProbivanje() {
        int s = 0, c = pin;
        while (c) {
            s++;
            c /= 10;
        }
        return s;
    }

    friend ostream &operator<<(ostream &os, Karticka &k) {
        os << k.smetka << ": " << k.tezinaProbivanje() << endl;
        return os;
    }

    ~Karticka() {}
};

class SpecijalnaKarticka : public Karticka {
    int *additionalPins;
    int n;

    void copy(const SpecijalnaKarticka &c) {
        strcpy(this->smetka, c.smetka);
        this->pin = c.pin;
        this->povekjePin = c.povekjePin;
        this->additionalPins = new int[c.n];
        for(int i = 0; i < c.n; i++) {
            this->additionalPins[i] = c.additionalPins[i];
        }
        this->n = c.n;
    }

public:
    SpecijalnaKarticka() : Karticka() {
        this->povekjePin = true;
        this->additionalPins = nullptr;
        this->n = 0;
    }

    SpecijalnaKarticka(const char *smetka = " ", int pin = 0) : Karticka(smetka, pin) {
        this->additionalPins = nullptr;
        this->n = 0;
        this->povekjePin = true;
    }

    SpecijalnaKarticka(const SpecijalnaKarticka &c) : Karticka(c) {
        copy(c);
    }

    SpecijalnaKarticka &operator=(const SpecijalnaKarticka &o) {
        if (this != &o) {
            Karticka::operator=(o);
            delete[] additionalPins;
            copy(o);
        }
        return *this;
    }

    int tezinaProbivanje() override {
        return Karticka::tezinaProbivanje() + n;
    }

    SpecijalnaKarticka &operator+=(int addPin) {
        if (n == P) {
            throw OutOfBoundException();
        }
        int *tmp = new int[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = additionalPins[i];
        }
        tmp[n++] = addPin;

        delete[] additionalPins;
        this->additionalPins = new int[n];
        for (int i = 0; i < n; i++) {
            this->additionalPins[i] = tmp[i];
        }
        delete[] tmp;
        return *this;
    }

    ~SpecijalnaKarticka() {
        delete[]additionalPins;
    }
};


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka() {
        strcpy(this->naziv, "banka");
        this->broj = 0;
    }

    Banka(char *naziv, Karticka **karticki, int broj) {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++) {
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()) {
                this->karticki[i] = new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka *>(karticki[i]));
            } else this->karticki[i] = new Karticka(*karticki[i]);
        }
        this->broj = broj;
    }

    static void setLIMIT(int limit) {
        LIMIT = limit;
    }

    ~Banka() {
        for (int i = 0; i < broj; i++) delete karticki[i];
    }

    void pecatiKarticki() {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; ++i) {
            if (this->karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i];
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin) {
        for (int i = 0; i < broj; ++i) {
            if (karticki[i]->getDopolnitelenPin() && !strcmp(this->karticki[i]->getSmetka(), smetka)) {
                *dynamic_cast<SpecijalnaKarticka *>(karticki[i]) += novPin;
            }
        }
    }
};

int Banka::LIMIT = 7;
const int Karticka::P = 4;

int main() {

    Karticka **niza;
    int n, m, pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin >> n;
    niza = new Karticka *[n];
    for (int i = 0; i < n; i++) {
        cin >> smetka;
        cin >> pin;
        cin >> daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i] = new Karticka(smetka, pin);
        else
            niza[i] = new SpecijalnaKarticka(smetka, pin);
    }

    Banka komercijalna("Komercijalna", niza, n);
    for (int i = 0; i < n; i++) delete niza[i];
    delete[] niza;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> smetka >> pin;

        try { komercijalna.dodadiDopolnitelenPin(smetka, pin); }
        catch (OutOfBoundException &e) { e.message(); }

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
