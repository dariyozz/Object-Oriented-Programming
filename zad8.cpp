#include <iostream>
#include <cstring>

using namespace std;

class Koncert {
protected:
    char naziv[20];
    char location[20];
    float priceTicket;
public:
    static float discount;

    Koncert(const char *naziv = " ", const char *location = " ", float priceTicket = 0.0) {
        strcpy(this->naziv, naziv);
        strcpy(this->location, location);
        this->priceTicket = priceTicket;
    }

    Koncert(const Koncert &c) {
        strcpy(this->naziv, c.naziv);
        strcpy(this->location, c.location);
        this->priceTicket = c.priceTicket;
    }

    const char *getNaziv() const {
        return naziv;
    }

    static float getSezonskiPopust() {
        return discount;
    }

    static void setSezonskiPopust(float discount) {
        Koncert::discount = discount;
    }

    virtual float cena() {
        return priceTicket * (1 - discount);
    }

    virtual ~Koncert() {}
};

class ElektronskiKoncert : public Koncert {
    char *nameDj;
    float timeDuration;
    bool dayNight;

    void copy(const ElektronskiKoncert &c) {
        this->nameDj = new char[strlen(c.nameDj) + 1];
        strcpy(this->nameDj, c.nameDj);
        this->timeDuration = c.timeDuration;
        this->dayNight = c.dayNight;
    }

public:
    ElektronskiKoncert(const char *naziv = " ", const char *loation = " ", float priceTicket = 0.0,
                       const char *nameDj = " ", float partyDuration = 0.0, bool dayNight = true)
            : Koncert(naziv, loation, priceTicket) {
        this->nameDj = new char[strlen(nameDj) + 1];
        strcpy(this->nameDj, nameDj);
        this->timeDuration = partyDuration;
        this->dayNight = dayNight;
    }

    ElektronskiKoncert(const ElektronskiKoncert &c) : Koncert(c) {
        copy(c);
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &o) {
        if (this != &o) {
            delete[] nameDj;
            Koncert::operator=(o);
            copy(o);
        }
        return *this;
    }

    float cena() override {
        float c = Koncert::cena();
        if (timeDuration > 7) {
            c += 360;
        } else if (timeDuration > 5) {
            c += 150;
        }
        if (dayNight) {
            c -= 50;
        } else {
            c += 100;
        }
        return c;
    }

    ~ElektronskiKoncert() {
        delete[] nameDj;
    }
};

void najskapKoncert(Koncert **koncerti, int n) {
    Koncert *max = koncerti[0];
    int vkElek = 0;
    for (int i = 1; i < n; ++i) {
        if (dynamic_cast<ElektronskiKoncert *>(koncerti[i])) {
            vkElek++;
        }
        if (max->cena() < koncerti[i]->cena()) {
            max = koncerti[i];
        }
    }
    cout << "Najskap koncert: " << max->getNaziv() << " " << max->cena() << endl;
    cout << "Elektronski koncerti: " << vkElek << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski) {
    if (elektronski) {
        for (int i = 0; i < n; ++i) {
            if (dynamic_cast<ElektronskiKoncert * >(koncerti[i]) && strcmp(koncerti[i]->getNaziv(),naziv)  == 0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                return true;
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            if (strcmp((koncerti[i])->getNaziv(), naziv) == 0) {
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                return true;
            }
        }
    }
    return false;
}


float Koncert::discount = 0.2;

int main() {

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin >> tip;
    if (tip == 1) {//Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    } else if (tip == 2) {//cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    } else if (tip == 3) {//ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust "
             << s.getSezonskiPopust() << endl;
    } else if (tip == 4) {//cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    } else if (tip == 5) {//najskapKoncert

    } else if (tip == 6) {//prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    } else if (tip == 7) {//prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski)) {
            cout << "Pronajden" << endl;
        } else { cout << "Ne e pronajden" << endl; }

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski)) {
            cout << "Pronajden" << endl;
        } else { cout << "Ne e pronajden" << endl; }

    } else if (tip == 8) {//smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
