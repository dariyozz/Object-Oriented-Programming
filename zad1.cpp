#include <iostream>
#include<cstring>

using namespace std;

class Book {
protected:
    char isbn_broj[20];
    char naslov[50];
    char avtor[30];
    double price;

    void copy_book(const Book &other) {
        strcpy(this->isbn_broj, other.isbn_broj);
        strcpy(this->naslov, other.naslov);
        strcpy(this->avtor, other.avtor);
        this->price = other.price;
    }

public:
    Book(const char *isbn_broj = " ", char *naslov = " ", char *avtor = " ", double price = 0.0) {
        strcpy(this->isbn_broj, isbn_broj);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);
        this->price = price;
    }

    Book(const Book &c) {
        copy_book(c);
    }

    Book &operator=(const Book &other) {
        if (this == &other) {
            return *this;
        }
        copy_book(other);
        return *this;
    }

    void setISBN(char *a) {
        strcpy(this->isbn_broj, a);
    }


    friend ostream &operator<<(ostream &os, Book &book) {
        return os << book.isbn_broj << ": " << book.naslov << ", " << book.avtor << " " << book.bookPrice() << endl;
    }

    virtual double bookPrice() = 0;

    ~Book() {

    }
};

class OnlineBook : public Book {
    char *url;
    int size_MB;

    void copy_online(const OnlineBook &c) {
        this->size_MB = c.size_MB;
        this->url = new char[strlen(c.url) + 1];
        strcpy(this->url, c.url);
    }

public:
    OnlineBook() : Book() {
        this->url = new char[4];
        strcpy(this->url, "url");
        this->size_MB = 0;
    }

    OnlineBook(char *isbn_broj = " ", char *naslov = " ", char *avtor = " ", double price = 0.0, char *url = " ",
               int size_MB = 0)
            : Book(isbn_broj, naslov, avtor, price) {
        this->size_MB = size_MB;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    OnlineBook(const OnlineBook &c) : Book(c) {
        copy_online(c);
    }

    OnlineBook &operator=(const OnlineBook &o) {
        if (this != &o) {
            delete[] url;
            copy_online(o);
            Book::operator=(o);
        }
        return *this;
    }


    double bookPrice() {
        return size_MB > 20 ? 1.2f * price : price;
    }

    ~OnlineBook() {
        delete[] url;
    }
};

class PrintBook : public Book {
    double masa_kg;
    bool isAviable;

    void copy_printbook(const PrintBook &other) {
        this->masa_kg = other.masa_kg;
        this->isAviable = other.isAviable;
    }

public:
    PrintBook() : Book() {
        this->masa_kg = 0.0;
        isAviable = false;
    }

    PrintBook(char *isbn_broj = " ", char *naslov = " ", char *avtor = " ", double price = 0.0, double masa_kg = 0.0,
              int isAviable = true)
            : Book(isbn_broj, naslov, avtor, price) {
        this->masa_kg = masa_kg;
        this->isAviable = isAviable;
    }

    PrintBook(const PrintBook &c) : Book(c) {
        copy_printbook(c);
    }

    PrintBook &operator=(const PrintBook &p) {
        if (this != &p) {
            copy_printbook(p);
            Book::operator=(p);
        }
        return *this;
    }

    double bookPrice() override {
        return masa_kg > 0.7 ? 1.15 * price : price;
    }

    ~PrintBook() {

    }
};

bool operator>(Book &a, Book &b) {
    return a.bookPrice() > b.bookPrice();
}

void mostExpensiveBook(Book **books, int n) {
    int onlineBooks = 0, printBooks = 0, flag = -1;
    Book *max;
    for (int i = 0; i < n; ++i) {
        if (flag == -1) {
            max = books[i];
            flag = 1;
        } else if (max->bookPrice() < books[i]->bookPrice()) {
            max = books[i];
        }
        if (dynamic_cast<OnlineBook *>(books[i])) {
            onlineBooks++;
        } else if (dynamic_cast<PrintBook *>(books[i])) {
            printBooks++;
        }
    }
    cout << "FINKI-Education\n";
    cout << "Total number of online books: " << onlineBooks << "\n";
    cout << "Total number of print books: " << printBooks << "\n";
    cout << "The most expensive book is:\n";
    cout << *max << "\n";
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    double price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}

