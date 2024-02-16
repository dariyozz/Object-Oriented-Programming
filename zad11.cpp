#include<iostream>
#include<cstring>

using namespace std;

class Delo {
    char name[50];
    int year;
    char country[50];
public:
    Delo(const char *name = "", int year = 0, const char *country = "") {
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->year = year;
    }

    Delo(const Delo &c) {
        strcpy(this->name, c.name);
        strcpy(this->country, c.country);
        this->year = c.year;
    }

    const char *getIme() const {
        return name;
    }

    int getYear() const {
        return year;
    }

    void setYear(int year) {
        this->year = year;
    }

    const char *getCountry() const {
        return country;
    }

    bool operator==(const Delo &b) {
        return (strcmp(b.name, name) == 0);
    }
};

class Pretstava {
    Delo delo;
    int soldTickets;
    char date[16];
public:
    Pretstava(Delo delo = nullptr, int soldTickets = 0, const char *date = "") {
        this->delo = delo;
        this->soldTickets = soldTickets;
        strcpy(this->date, date);
    }

    Pretstava(const Pretstava &c) {
        this->delo = c.delo;
        this->soldTickets = c.soldTickets;
        strcpy(this->date, c.date);
    }

    Delo getDelo() {
        return delo;
    }

    void setDelo(const Delo &delo) {
        Pretstava::delo = delo;
    }

    int getSoldTickets() const {
        return soldTickets;
    }

    void setSoldTickets(int soldTickets) {
        Pretstava::soldTickets = soldTickets;
    }

    const char *getime() const {
        return date;
    }

    virtual int cena() {
        int n = delo.getYear() > 1900 ? 50 : delo.getYear() > 1800 ? 75 : 100;
        int m = !strcmp(delo.getCountry(), "Italija") ? 100 : !strcmp(delo.getCountry(), "Rusija") ? 150 : 80;
        return n + m;
    }
};

class Balet : public Pretstava {
    static int addictional;
public:
    Balet(Delo delo = nullptr, int soldTickets = 0, const char *date = "")
            : Pretstava(delo, soldTickets, date) {}

    int cena() override {
        return Pretstava::cena() + addictional;
    }

    static void setCenaBalet(int price) {
        addictional = price;
    }
};

class Opera : public Pretstava {
public:
    Opera() : Pretstava() {}

    Opera(Delo delo, int tickets, char *date) : Pretstava(delo, tickets, date) {}

    ~Opera() {}
};

int prihod(Pretstava **p, int n) {
    int s = 0;
    for (int i = 0; i < n; ++i) {
        s += p[i]->getSoldTickets() * p[i]->cena();
    }
    return s;
}

int brojPretstaviNaDelo(Pretstava **p, int n, Delo d) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i]->getDelo() == d) {
            cnt++;
        }
    }
    return cnt;
}

int Balet::addictional = 150;

//citanje na delo
Delo readDelo() {
    char ime[50];
    int godina;
    char zemja[50];
    cin >> ime >> godina >> zemja;
    return Delo(ime, godina, zemja);
}

//citanje na pretstava
Pretstava *readPretstava() {
    int tip; //0 za Balet , 1 za Opera
    cin >> tip;
    Delo d = readDelo();
    int brojProdadeni;
    char data[15];
    cin >> brojProdadeni >> data;
    if (tip == 0) return new Balet(d, brojProdadeni, data);
    else return new Opera(d, brojProdadeni, data);
}

int main() {
    int test_case;
    cin >> test_case;

    switch (test_case) {
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout << "======TEST CASE 1=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->getDelo().getIme() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->getDelo().getIme() << endl;
        }
            break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout << "======TEST CASE 2=======" << endl;
            Pretstava *p1 = readPretstava();
            cout << p1->cena() << endl;
            Pretstava *p2 = readPretstava();
            cout << p2->cena() << endl;
        }
            break;

        case 3:
            //Testiranje na operator ==
        {
            cout << "======TEST CASE 3=======" << endl;
            Delo f1 = readDelo();
            Delo f2 = readDelo();
            Delo f3 = readDelo();

            if (f1 == f2) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;
            if (f1 == f3) cout << "Isti se" << endl; else cout << "Ne se isti" << endl;

        }
            break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout << "======TEST CASE 4=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();

            }
            cout << prihod(pole, n);
        }
            break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout << "======TEST CASE 5=======" << endl;
            int cenaBalet;
            cin >> cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }
            cout << prihod(pole, n);
        }
            break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout << "======TEST CASE 6=======" << endl;
            int n;
            cin >> n;
            Pretstava **pole = new Pretstava *[n];
            for (int i = 0; i < n; i++) {
                pole[i] = readPretstava();
            }

            Delo f = readDelo();
            cout << brojPretstaviNaDelo(pole, n, f);
        }
            break;

    };


    return 0;
}

