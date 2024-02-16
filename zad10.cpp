#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class NegativnaVrednost {
public:
    void message() {
        cout << "Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!" << endl;
    }
};

class Oglas {
    char header[50];
    char category[30];
    char description[100];
    double price;
public:
    Oglas(const char *header = "", const char *category = "", const char *description = "", double price = 0.0) {
        strcpy(this->header, header);
        strcpy(this->category, category);
        strcpy(this->description, description);
        this->price = price;
    }

    Oglas(const Oglas &c) {
        strcpy(this->header, c.header);
        strcpy(this->category, c.category);
        strcpy(this->description, c.description);
        this->price = c.price;
    }

    double getPrice() const {
        return price;
    }

    const char *getHeader() const {
        return header;
    }

    const char *getCategory() const {
        return category;
    }

    const char *getDescription() const {
        return description;
    }

    bool operator>(const Oglas &a) {
        return price > a.price;
    }

    friend ostream &operator<<(ostream &out, Oglas &other) {
        out << other.header << "\n" << other.description << "\n" << other.price << " evra"<<endl;
        return out;
    }

    ~Oglas() {}
};

class Oglasnik {
    char owner[20];
    Oglas *oglasi;
    int n;

    void copy(const Oglasnik &c) {
        strcpy(this->owner, c.owner);
        this->n = c.n;
        this->oglasi = new Oglas[c.n];
        for (int i = 0; i < c.n; ++i) {
            this->oglasi[i] = c.oglasi[i];
        }
    }

public:
    Oglasnik(const char *owner = "") {
        strcpy(this->owner, owner);
        this->n = 0;
        this->oglasi = new Oglas[0];
    }

    Oglasnik(const Oglasnik &c) {
        copy(c);
    }

    Oglasnik &operator=(const Oglasnik &other) {
        if (this != &other) {
            delete[] oglasi;
            copy(other);
        }
        return *this;
    }

    Oglasnik &operator+=(const Oglas &addNew) {
        if (addNew.getPrice() < 0) {
            throw NegativnaVrednost();
        }
        Oglas *tmp = new Oglas[n + 1];
        for (int i = 0; i < n; ++i) {
            tmp[i] = oglasi[i];
        }
        tmp[n++] = addNew;
        delete[]oglasi;
        oglasi = tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Oglasnik &o) {
        out << o.owner << "\n";
        for (int i = 0; i < o.n; i++) {
            out << o.oglasi[i] << "\n";
        }
        return out;
    }

    void oglasiOdKategorija(const char *k) {
        for (int i = 0; i < n; ++i) {
            if (strcmp(k, oglasi[i].getCategory()) == 0) {
                cout << oglasi[i]<<endl;
            }
        }
    }

    void najniskaCena() {
        int min = -1;
        for (int i = 0; i < n; ++i) {
            if (min == -1 || oglasi[i].getPrice() < min) {
                min = i;
            }
        }
        cout << oglasi[min]<<endl;
    }

    ~Oglasnik() {
        delete[] oglasi;
    }

};

int main() {

    char naslov[50];
    char kategorija[30];
    char opis[100];
    double cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1) {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    } else if (tip == 2) {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2) cout << "Prviot oglas e poskap." << endl;
        else cout << "Prviot oglas ne e poskap." << endl;
    } else if (tip == 3) {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout << ogl;
    } else if (tip == 4) {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

    } else if (tip == 5) {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout << ogl;

    } else if (tip == 6) {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    } else if (tip == 7) {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++) {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try { ogl+=o; }
            catch(NegativnaVrednost& n) { n.message(); }
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();

    }

    return 0;
}
