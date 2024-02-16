#include<iostream>
#include<cstring>

using namespace std;

class Transport {
    void copy(const Transport &c) {
        this->destination = new char[strlen(c.destination) + 1];
        strcpy(this->destination, c.destination);
        this->price = c.price;
        this->distance = c.distance;
    }

protected:
    char *destination;
    int price;
    int distance;
public:
    Transport(const char *destination = "", int price = 0, int distance = 0) {
        this->destination = new char[strlen(destination) + 1];
        strcpy(this->destination, destination);
        this->price = price;
        this->distance = distance;
    }

    Transport(const Transport &c) {
        copy(c);
    }

    Transport &operator=(const Transport &o) {
        if (this != &o) {
            delete[] destination;
            copy(o);
        }
        return *this;
    }

    int getDistance() const {
        return distance;
    }

    char *getDestination() const {
        return destination;
    }

    int getPrice() const {
        return price;
    }

    virtual int cenaTransport() = 0;

    virtual ~Transport() {
        delete[] destination;
    }
};

class AvtomobilTransport : public Transport {
    bool paidDriver;
public:
    AvtomobilTransport(const char *destination = "", int price = 0, int distance = 0, bool paidDriver = true)
            : Transport(destination, price, distance) {
        this->paidDriver = paidDriver;
    }

    AvtomobilTransport(const AvtomobilTransport &c) : Transport(c) {
        this->paidDriver = c.paidDriver;
    }

    AvtomobilTransport &operator=(const AvtomobilTransport &o) {
        if (this != &o) {
            Transport::operator=(o);
            this->paidDriver = o.paidDriver;
        }
        return *this;
    }

    int cenaTransport() override {
        return paidDriver ? price * 1.2 : price;
    }

    ~AvtomobilTransport() {}
};

class KombeTransport : public Transport {
    int numberOfPeople;
public:
    KombeTransport(const char *destination = "", int price = 0, int distance = 0, int numberOfPeople = 0)
            : Transport(destination, price, distance) {
        this->numberOfPeople = numberOfPeople;
    }

    KombeTransport(const KombeTransport &c) : Transport(c) {
        this->numberOfPeople = c.numberOfPeople;
    }

    KombeTransport &operator=(const KombeTransport &o) {
        if (this != &o) {
            Transport::operator=(o);
            this->numberOfPeople = o.numberOfPeople;
        }
        return *this;
    }

    int cenaTransport() override {
        return price - (numberOfPeople * 200);
    }

    ~KombeTransport() {}
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &t) {
    Transport **tempPonudi = new Transport *[n];
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (ponudi[i]->cenaTransport() > t.cenaTransport()) {
            tempPonudi[j++] = ponudi[i];
        }
    }
    Transport *tmp;
    for (int i = 0; i < j - 1; ++i) {
        for (int k = 0; k < j - 1 - i; ++k) {
            if (tempPonudi[k]->getDistance() > tempPonudi[k + 1]->getDistance()) {
                tmp = tempPonudi[k];
                tempPonudi[k] = tempPonudi[k + 1];
                tempPonudi[k + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < j; ++i) {
        cout << tempPonudi[i]->getDestination() << " " << tempPonudi[i]->getDistance() << " "
             << tempPonudi[i]->cenaTransport() << endl;
    }
}

int main() {

    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {

        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }


    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++) delete ponudi[i];
    delete[] ponudi;
    return 0;
}
