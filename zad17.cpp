#include <iostream>
#include <cstring>

using namespace std;

class FudbalskaEkipa {
protected:
    char nameCoach[100];
    int goals[10];
public:
    FudbalskaEkipa(const char *nameCoach = "", int *goals = nullptr) {
        strcpy(this->nameCoach, nameCoach);
        for (int i = 0; i < 10; ++i) {
            this->goals[i] = goals[i];
        }
    }

    FudbalskaEkipa(const FudbalskaEkipa &c) {
        strcpy(this->nameCoach, c.nameCoach);
        for (int i = 0; i < 10; ++i) {
            this->goals[i] = c.goals[i];
        }
    }

    FudbalskaEkipa &operator=(const FudbalskaEkipa &o) {
        if (this != &o) {
            strcpy(this->nameCoach, nameCoach);
            for (int i = 0; i < 10; ++i) {
                this->goals[i] = goals[i];
            }
        }
        return *this;
    }

    FudbalskaEkipa &operator+=(int lastMatchGoals) {
        for (int i = 0; i < 9; i++) {
            this->goals[i] = this->goals[i + 1];
        }
        this->goals[9] = lastMatchGoals;
        return *this;
    }

    bool operator>(FudbalskaEkipa &other) {
        return uspeh() > other.uspeh();
    }

    char *getCoach() {
        return nameCoach;
    }

    virtual int uspeh() = 0;

    virtual ~FudbalskaEkipa() {}
};

class Klub : public FudbalskaEkipa {
    char *nameClub;
    int titles;

    void copyK(const Klub &c) {
        this->nameClub = new char[strlen(c.nameClub) + 1];
        strcpy(this->nameClub, c.nameClub);
        this->titles = c.titles;
    }

public:
    Klub(const char *nameCoach = "", int *goals = nullptr, const char *nameClub = " ", int titles = 0)
            : FudbalskaEkipa(nameCoach, goals) {
        this->nameClub = new char[strlen(nameClub) + 1];
        strcpy(this->nameClub, nameClub);
        this->titles = titles;
    }

    Klub(const Klub &c) : FudbalskaEkipa(c) {
        copyK(c);
    }

    Klub &operator=(const Klub &o) {
        if (this != &o) {
            delete[] nameClub;
            FudbalskaEkipa::operator=(o);
            copyK(o);
        }
        return *this;
    }

    char *getNameClub() const {
        return nameClub;
    }

    int getTitles() const {
        return titles;
    }

    int uspeh() override {
        int g = 0;
        for (int goal: goals) {
            g += goal;
        }
        return (3 * g) + (titles * 1000);
    }

    ~Klub() {
        delete[] nameClub;
    }
};

class Reprezentacija : public FudbalskaEkipa {
    char *nameCountry;
    int international;

    void copyR(const Reprezentacija &c) {
        this->nameCountry = new char[strlen(c.nameCountry) + 1];
        strcpy(this->nameCountry, c.nameCountry);
        this->international = c.international;
    }

public:
    Reprezentacija(const char *nameCoach = "", int *goals = nullptr, const char *nameCountry = " ",
                   int international = 0)
            : FudbalskaEkipa(nameCoach, goals) {
        this->nameCountry = new char[strlen(nameCountry) + 1];
        strcpy(this->nameCountry, nameCountry);
        this->international = international;
    }

    Reprezentacija(const Reprezentacija &c) : FudbalskaEkipa(c) {
        copyR(c);
    }

    Reprezentacija &operator=(const Reprezentacija &o) {
        if (this != &o) {
            delete[] nameCountry;
            FudbalskaEkipa::operator=(o);
            copyR(o);
        }
        return *this;
    }

    char *getNameCountry() const {
        return nameCountry;
    }

    int getInternational() const {
        return international;
    }

    int uspeh() override {
        int g = 0;
        for (int goal: goals) {
            g += goal;
        }
        return (3 * g) + (international * 50);
    }

    ~Reprezentacija() {
        delete[] nameCountry;
    }
};

ostream &operator<<(ostream &out, FudbalskaEkipa &k) {
    if (dynamic_cast<Klub *>(&k)) {
        out << dynamic_cast<Klub *>(&k)->getNameClub();
    } else if (dynamic_cast<Reprezentacija *>(&k)) {
        out << dynamic_cast<Reprezentacija *>(&k)->getNameCountry();
    }
    out << "\n" << k.getCoach() << "\n" << k.uspeh() << "\n";
    return out;
}

void najdobarTrener(FudbalskaEkipa **ekipi, int n) {
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (idx == -1 || ekipi[i]->uspeh() > ekipi[idx]->uspeh()) {
            idx = i;
        }
    }
    if (idx == -1) {
        return;
    }
    cout << *ekipi[idx];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete[] ekipi;
    return 0;
}