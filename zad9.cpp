#include<iostream>
#include<cstring>

using namespace std;

class Exception {
public:
    void message() {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class Trud {
    char type;
    int year;
public:
    Trud(char type = 'C', int year = 2000) {
        this->type = type;
        this->year = year;
    }

    Trud(const Trud &c) {
        this->type = c.type;
        this->year = c.year;
    }

    char getType() const {
        return type;
    }

    int getYear() const {
        return year;
    }

    friend istream &operator>>(istream &in, Trud &t) {
        in >> t.type >> t.year;
        return in;
    }

    ~Trud() {}
};

class Student {
private:

    void copy(const Student &c) {
        strcpy(this->name, c.name);
        this->enrollYear = c.enrollYear;
        this->index = c.index;
        this->passedSubjects = c.passedSubjects;
        this->grades = new int[c.passedSubjects];
        for (int i = 0; i < c.passedSubjects; ++i) {
            this->grades[i] = c.grades[i];
        }
    }

protected:
    char name[30];
    int index;
    int enrollYear;
    int *grades;
    int passedSubjects;


public:
    Student(const char *name = " ", int index = 0, int enrollYear = 2000, int *grades = nullptr,
            int passedSubjects = 0) {
        strcpy(this->name, name);
        this->enrollYear = enrollYear;
        this->index = index;
        this->passedSubjects = passedSubjects;
        this->grades = new int[passedSubjects];
        for (int i = 0; i < passedSubjects; ++i) {
            this->grades[i] = grades[i];
        }
    }

    Student(const Student &c) {
        copy(c);
    }

    Student &operator=(const Student &o) {
        if (this != &o) {
            delete[] grades;
            copy(o);
        }
        return *this;
    }

    int getIndex() const {
        return index;
    }

    virtual double rang() {
        double s = 0.0;
        for (int i = 0; i < passedSubjects; ++i) {
            s += grades[i];
        }
        return s / passedSubjects;
    }

    friend ostream &operator<<(ostream &os, Student &s) {
        os << s.index << " " << s.name << " " << s.enrollYear << " " << s.rang() << endl;
        return os;
    }

    ~Student() {
        delete[] grades;
    }
};

class PhDStudent : public Student {
    Trud *trudovi;
    int numOfTrudovi;
    static int c;
    static int j;

    void copy_phd(const PhDStudent &cc) {
        this->trudovi = new Trud[cc.numOfTrudovi];
        for (int i = 0; i < cc.numOfTrudovi; ++i) {
            this->trudovi[i] = cc.trudovi[i];
        }
        this->numOfTrudovi = cc.numOfTrudovi;
    }

public:
    PhDStudent(const char *name = " ", int index = 0, int enrollYear = 2000, int *grades = nullptr,
               int passedSubjects = 0, Trud *trudovi = nullptr, int numOfTrudovi = 0)
            : Student(name, index, enrollYear, grades, passedSubjects) {
        this->trudovi = new Trud[numOfTrudovi];
        for (int i = 0; i < numOfTrudovi; ++i) {
            try {
                trudovi[i].getYear() < enrollYear ? throw Exception() : this->trudovi[i] = trudovi[i];
            } catch(Exception& e) {
                e.message();
            }

        }
        this->numOfTrudovi = numOfTrudovi;
    }

    PhDStudent(const PhDStudent &cc) : Student(cc) {
        copy_phd(cc);
    }

    PhDStudent &operator=(const PhDStudent &ot) {
        if (this != &ot) {
            delete[] trudovi;
            Student::operator=(ot);
            copy_phd(ot);
        }
        return *this;
    }

    double rang() override {
        double s = Student::rang();
        for (int i = 0; i < numOfTrudovi; ++i) {
            if (tolower(trudovi[i].getType()) == 'c') {
                s += c;
            } else if (tolower(trudovi[i].getType()) == 'j') {
                s += j;
            }
        }
        return s;
    }

    static void setC(int c) {
        PhDStudent::c = c;
    }

    static void setJ(int j) {
        PhDStudent::j = j;
    }

    PhDStudent &operator+=(const Trud &obj) {
        if (obj.getYear() < enrollYear) {
            throw Exception();
        }
        Trud *tmp = new Trud[numOfTrudovi + 1];
        for (int i = 0; i < numOfTrudovi; ++i) {
            tmp[i] = trudovi[i];
        }
        tmp[numOfTrudovi++] = obj;
        delete[] trudovi;
        trudovi = tmp;
        return *this;

    }

    ~PhDStudent() {
        delete[] trudovi;
    }
};
int PhDStudent::c = 1;
int PhDStudent::j = 3;
int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool found = false;

        try {
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                    found = true;
                }
            }
        } catch(Exception& e) {
            e.message();
        }

        if(!found) cout << "Ne postoi PhD student so indeks " << indeks << "\n";
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        try {
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                }
            }
        } catch(Exception& e) {
            e.message();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try {
            for(int i = 0; i < m; i++) {
                if(niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent*>(niza[i])) {
                    *dynamic_cast<PhDStudent*>(niza[i]) += t;
                }
            }
        } catch(Exception& e) {
            e.message();
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}