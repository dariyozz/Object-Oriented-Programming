#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image {
protected:
    char *nameImg;
    char nameUser[50];
    int width, height;

    void copy(const Image &c) {
        strcpy(this->nameUser, c.nameUser);
        this->width = c.width;
        this->height = c.height;
        this->nameImg = new char[strlen(c.nameImg) + 1];
        strcpy(this->nameImg, c.nameImg);
    }

public:
    Image(const char *nameImg = "untitled", const char *nameUser = "unknown",
          int width = 800, int height = 800) {
        strcpy(this->nameUser, nameUser);
        this->width = width;
        this->height = height;
        this->nameImg = new char[strlen(nameImg) + 1];
        strcpy(this->nameImg, nameImg);
    }

    Image(const Image &c) {
        copy(c);
    }

    Image &operator=(const Image &o) {
        if (this != &o) {
            delete[] nameImg;
            copy(o);
        }
        return *this;
    }

    virtual int fileSize() {
        return width * height * 3;
    }

    friend ostream &operator<<(ostream &os, Image &i) {
        os << i.nameImg << " " << i.nameUser << " " << i.fileSize()<<endl;
        return os;
    }

    bool operator>(Image &b) {
        return this->fileSize() > b.fileSize();
    }

    ~Image() {
        delete[] nameImg;
    }
};

class TransparentImage : public Image {
    bool transparency;
public:
    TransparentImage(const char *nameImg = "untitled", const char *nameUser = "unknown",
                     int width = 800, int height = 800, bool transparency = false)
            : Image(nameImg, nameUser, width, height) {
        this->transparency = transparency;
    }

    TransparentImage(const TransparentImage &c) : Image(c) {
        this->transparency = c.transparency;
    }

    TransparentImage &operator=(const TransparentImage &other) {
        if (this == &other) {
            return *this;
        }
        Image::operator=(other);
        this->transparency = other.transparency;
        return *this;
    }

    bool operator>(TransparentImage &other) {
        return fileSize() > other.fileSize();
    }

    int fileSize() override {
        return transparency ? width * height * 4 : width * height + (width * height) / 8.0;
    }

    ~TransparentImage() {}
};

class Folder {
    char nameFolder[255];
    char folderOwner[50];
    Image *images[100];
    int n;

    void copy_folder(const Folder &other) {
        strcpy(this->nameFolder, other.nameFolder);
        strcpy(this->folderOwner, other.folderOwner);
        for (int i = 0; i < other.n; i++) {
            this->images[i] = other.images[i];
        }
        this->n = other.n;
    }

public:
    Folder(const char *nameFoler = "unknown", const char *folderOwner = "unknown") {
        this->n = 0;
        strcpy(this->folderOwner, folderOwner);
        strcpy(this->nameFolder, nameFoler);
    }

    Folder(const Folder &c) {
        copy_folder(c);
    }

    Folder &operator=(const Folder &o) {
        if (this != &o) {
            for (int i = 0; i < o.n; ++i) {
                delete images[i];
            }
            copy_folder(o);
        }
        return *this;
    }

    Folder &operator+=(Image &newImg) {
        if (n >= 100) return *this;
        images[n++] = &newImg;
        return *this;
    }

    int folderSize() {
        int s = 0;
        for (int i = 0; i < n; i++) {
            s += images[i]->fileSize();
        }
        return s;
    }

    friend ostream &operator<<(ostream &os, Folder &f) {
        os << f.nameFolder << " " << f.folderOwner << endl << "--" << endl;
        for (int i = 0; i < f.n; ++i) {
            os << *f.images[i];
        }
        os << "--\nFolder size: " << f.folderSize() << "\n";
        return os;
    }

    Image *operator[](int i) {
        return i < n ? images[i] : nullptr;
    }

    Image *getMaxFile() {
        int max = -1;
        for (int i = 0; i < n; i++) {
            max = (max == -1 || *images[i] > *images[max] ) ? i : max;
        }
        if (max == -1) return nullptr;

        return images[max];
    }

    ~Folder() {
        for (int i = 0; i < n; ++i) {
            delete images[i];
        }
    }
};

Folder &max_folder_size(Folder *f, int n) {
    int max = -1;
    for (int i = 0; i < n; ++i) {
        if (max == -1 || f[i].folderSize() > f[max].folderSize()) {
            max = i;
        }
    }
    return f[max];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1) {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, w, h);
        cout << f4;
    } else if (tc == 2) {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout << tf4;
    } else if (tc == 3) {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    } else if (tc == 4) {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << dir;
    } else if (tc == 5) {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    } else if (tc == 6) {
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    } else if (tc == 7) {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i) {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1) {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >> fileType;
                if (fileType == 1) { // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, w, h);
                    dir += *f;
                } else if (fileType == 2) {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout << max_folder_size(dir_list, folders_num);
    }
    return 0;
}
