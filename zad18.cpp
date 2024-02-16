#include <iostream>
#include <cstring>

using namespace std;

class MonthlyInvoice {
protected:
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
private:
    void copy_monthly(const MonthlyInvoice &other) {
        strcpy(this->username, other.username);
        this->userNumber = other.userNumber;
        this->basic_price = other.basic_price;
        this->spent_gigabytes = other.spent_gigabytes;
    }

public:
    MonthlyInvoice(char *username = "", int userNumber = 0, float basic_price = 0.0, int spent_gigabytes = 0) {
        strcpy(this->username, username);
        this->userNumber = userNumber;
        this->basic_price = basic_price;
        this->spent_gigabytes = spent_gigabytes;
    }

    MonthlyInvoice(const MonthlyInvoice &c) {
        copy_monthly(c);
    }

    virtual int total_price() = 0;

    MonthlyInvoice &operator=(const MonthlyInvoice &other) {
        if (this == &other) {
            return *this;
        }
        copy_monthly(other);
        return *this;
    }

    bool operator>(MonthlyInvoice &other) {
        return this->total_price() > other.total_price();
    }

    virtual ~MonthlyInvoice() {}
};

class BusinessInvoice : public MonthlyInvoice {
    bool optical;
    int free_gigabytes;
public:
    BusinessInvoice(char *username = "", int userNumber = 0, float basic_price = 0.0, int spent_gigabytes = 0,
                    bool optical = false, int free_gigabytes = 0) : MonthlyInvoice(username, userNumber, basic_price,
                                                                                   spent_gigabytes) {
        this->optical = optical;
        this->free_gigabytes = free_gigabytes;
    }

    BusinessInvoice(const BusinessInvoice &c) : MonthlyInvoice(c) {
        this->optical = c.optical;
        this->free_gigabytes = c.free_gigabytes;
    }

    int total_price() override {
        int s = optical ? basic_price * 1.5 : basic_price;
        return s + spent_gigabytes * 100;
    }

    BusinessInvoice operator++(int) {
        BusinessInvoice tmp = *this;
        spent_gigabytes++;
        return tmp;
    }

    friend ostream &operator<<(ostream &os, BusinessInvoice &b) {
        os << b.userNumber << " - " << b.username << ", " << b.basic_price << endl;
        b.optical ? os << "optical link" : os << "cable link";
        os << ", " << b.free_gigabytes << endl;
    }

    ~BusinessInvoice() {}
};

class PrivateInvoice : public MonthlyInvoice {
    char *id_number[14];
    int *movies;
    int moviesNo;
public:
    PrivateInvoice(char *username = "", int userNumber = 0, float basic_price = 0.0, int spent_gigabytes = 0)
            : MonthlyInvoice(username, userNumber, basic_price, spent_gigabytes) {
        this->moviesNo = 0;
        this->movies = new int[0];
    }

    PrivateInvoice(const PrivateInvoice &c) : MonthlyInvoice(c) {
        this->moviesNo = c.moviesNo;
        this->movies = new int[c.moviesNo];
        for (int i = 0; i < c.moviesNo; ++i) {
            this->movies[i] = c.movies[i];
        }
    }

    int getMoviesNo() const {
        return moviesNo;
    }

    int getMoviesGBspend() {
        int sum = 0;
        for (int i = 0; i < moviesNo; ++i) {
            sum += movies[i];
        }
        return sum;
    }

    int total_price() override {
        return basic_price + spent_gigabytes * 50 + getMoviesGBspend() * 10;
    }

    int operator[](int index) {
//        if (index < moviesNo || index > moviesNo) return -1;
        return movies[index];
    }

    PrivateInvoice &operator+=(int newMovieSize) {
        int *tmp = new int[moviesNo + 1];
        for (int i = 0; i < moviesNo; ++i) {
            tmp[i] = movies[i];
        }
        tmp[moviesNo++] = newMovieSize;
        delete[] movies;
        movies = tmp;
        return *this;
    }

    PrivateInvoice operator++(int) {
        PrivateInvoice tmp = *this;
        spent_gigabytes++;
        return tmp;
    }

    friend ostream &operator<<(ostream &os, PrivateInvoice &p) {
        os << p.userNumber << " - " << p.username << ", " << p.basic_price << endl;
        os << p.spent_gigabytes << endl;
        os << p.moviesNo << ", " << p.getMoviesGBspend() << endl;
    }

    ~PrivateInvoice() {
        delete[] movies;
    }
};

MonthlyInvoice &biggestInvoice(MonthlyInvoice **mi, int num_invoices) {
    MonthlyInvoice *max = mi[0];
    for (int i = 1; i < num_invoices; ++i) {
        if (*mi[i] > *max) {
            max = mi[i];
        }
    }
    return *max;
}

int main() {
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case Business Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice Created:\n";
        cout << bi;
    } else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            bi++;
        }
        cout << bi;
    } else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout << bi.total_price() << endl;
        bi++;
        cout << bi;
        cout << bi.total_price() << endl;
    } else if (test_case == 4) {
        // Test Case Private Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;

        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << "Private Invoice Created:\n";
        cout << pi;
    } else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
    } else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
    } else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i = 0; i < pi.getMoviesNo(); ++i) {
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    } else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << pi;
        cout << pi.total_price() << endl;
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
        cout << pi.total_price() << endl;
    } else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >> num_invoices;
        MonthlyInvoice **mi = new MonthlyInvoice *[num_invoices];
        for (int j = 0; j < num_invoices; ++j) {

            cin >> invoice_type;
            if (invoice_type == 1) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice *bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout << bip->total_price() << endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice *pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice &invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice *m = &invoice;
        BusinessInvoice *bip;
        PrivateInvoice *pip;
        if (dynamic_cast<BusinessInvoice *> (m)) {
            bip = dynamic_cast<BusinessInvoice *> (m);
            cout << *bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *> (m)) {
            pip = dynamic_cast<PrivateInvoice *> (m);
            cout << *pip << pip->total_price();
        }

    }
    return 0;
}