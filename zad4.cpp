#include <cstring>
#include <iostream>

using namespace std;

enum Size {
    small, big, family
};
char SizeText[3][7] = {"small", "large", "family"};

class Pizza {
protected:
    char name[20];
    char ingrediants[100];
    float cena;
public:
    Pizza(char *name = " ", char *ingrediants = " ", float cena = 0.0) {
        strcpy(this->name, name);
        strcpy(this->ingrediants, ingrediants);
        this->cena = cena;
    }

    virtual float price() = 0;

    float getCena() const {
        return cena;
    }


    void setCena(float c) {
        Pizza::cena = c;
    }

    bool operator<(Pizza &p) {
        return this->price() < p.price();
    }

    friend ostream &operator<<(ostream &out, Pizza &p);
};


class FlatPizza : public Pizza {
    Size size;
public:
    FlatPizza(char *name = " ", char *ingrediants = " ", float cena = 0.0, enum Size size = small)
            : Pizza(name, ingrediants, cena) {
        this->size = size;
    }

    float price() {
        switch (size) {
            case small:
                return cena * 1.1;
            case big:
                return cena * 1.2;
            case family:
                return cena * 1.3;
        }

        return cena;
    }

    char *getSize() const {
        return SizeText[size];
    }
};

class FoldedPizza : public Pizza {
    bool hasFlower;
public:
    FoldedPizza(char *name = " ", char *ingrediants = " ", float cena = 0.0, bool hasFlower = true)
            : Pizza(name, ingrediants, cena) {
        this->hasFlower = hasFlower;
    }

    void setWhiteFlour(bool flower) {
        this->hasFlower = flower;
    }

    bool isHasFlower() const {
        return hasFlower;
    }


    float price() { return cena * (hasFlower ? 1.1 : 1.3); }

};

ostream &operator<<(ostream &out, Pizza &p) {
    out << p.name << ": " << p.ingrediants << ", ";

    if (dynamic_cast<FlatPizza *>(&p)) {
        out << dynamic_cast<FlatPizza *>(&p)->getSize();
    } else if (dynamic_cast<FoldedPizza *>(&p)) {
        out << (dynamic_cast<FoldedPizza *>(&p)->isHasFlower() ? "wf" : "nwf");
    }

    out << " - " << p.price() << "\n";
    return out;
}

void expensivePizza(Pizza **pici, int n) {
    int maxInx = -1;
    for (int i = 0; i < n; ++i) {
        if (maxInx == -1 || pici[i]->price() > pici[maxInx]->price()) {
            maxInx = i;
        }
    }
    if (maxInx == -1) {
        return;
    }
    cout << *pici[maxInx];
}

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, cena
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, cena
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        int s;
        cin >> s;
        FlatPizza fp(name, ingredients, inPrice, (Size) s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, cena
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, cena
        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, cena
        int s;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp1;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        cin >> s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size) s);
        cout << *fp2;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name, 20);
        cin.getline(ingredients, 100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout << "Lower price: " << endl;
        if (*fp1 < *fp2)
            cout << fp1->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp1 < *fp3)
            cout << fp1->price() << endl;
        else cout << fp3->price() << endl;

        if (*fp4 < *fp2)
            cout << fp4->price() << endl;
        else cout << fp2->price() << endl;

        if (*fp3 < *fp4)
            cout << fp3->price() << endl;
        else cout << fp4->price() << endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name, 20);

                cin.getline(ingredients, 100);
                cin >> inPrice;
                int s;
                cin >> s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size) s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name, 20);
                cin.getline(ingredients, 100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza(name, ingredients, inPrice);
                if (j % 2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi, num_p);


    }
    return 0;
}
