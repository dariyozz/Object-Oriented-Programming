#include<iostream>
#include<cstring>

using namespace std;

class Vozac {
protected:
    char name[100];
    int age;
    int tracks;
    bool isVeteran;
public:
    Vozac(char *name = " ", int age = 0, int tracks = 0, bool isVeteran = true) {
        strcpy(this->name, name);
        this->age = age;
        this->tracks = tracks;
        this->isVeteran = isVeteran;
    }

    friend ostream &operator<<(ostream &os, const Vozac &v) {
        os << v.name << endl << v.age << endl << v.tracks << endl;
        if (v.isVeteran) {
            os << "VETERAN" << endl;
        }
        return os;
    }

    virtual float danok() = 0;

    virtual float zarabotuvacka() = 0;

};

class Avtomobilist : public Vozac {
    float carPrice;
public:
    Avtomobilist(char *name = " ", int age = 0, int tracks = 0, bool isVeteran = true, float carPrice = 0.0)
            : Vozac(name, age, tracks, isVeteran) {
        this->carPrice = carPrice;
    }

    float zarabotuvacka() {
        return this->carPrice / 5.0;
    }

    float danok() {
        return tracks > 10 ? zarabotuvacka() * 0.15 : zarabotuvacka() * 0.1;
    }

    bool operator==(Avtomobilist &a) {
        return this->danok() == a.danok();
    }
};

class Motociklist : public Vozac {
    int power;
public:
    Motociklist(char *name = " ", int age = 0, int tracks = 0, bool isVeteran = true, int power = 0)
            : Vozac(name, age, tracks, isVeteran) {
        this->power = power;
    }

    float zarabotuvacka() {
        return this->power * 20;
    }

    float danok() {
        return isVeteran ? zarabotuvacka() * 0.25 : zarabotuvacka() * 0.2;
    }

    bool operator==(Motociklist &a) {
        return this->danok() == a.danok();
    }

};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (vozaci[i]->zarabotuvacka() == v->zarabotuvacka()) {
            cnt++;
        }
    }
    return cnt;
}


int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}