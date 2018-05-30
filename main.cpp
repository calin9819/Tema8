#include <iostream>
#include <string.h>
using namespace std;

class Informatie {
public:
    char nume[50];
    int id;
    int tip_informatie;
    Informatie() {

    }

    Informatie(char name[]) {
        strcpy(nume, name);
        tip_informatie = 0;
    }

    Informatie &operator=(const Informatie &c);
    Informatie *citire_info();
    virtual void afisare_info() {
        cout << "Id: " << id << '\n';
        cout << "Nume informatie: " << nume << '\n';
    }
};

class Text : public Informatie {
public:
    char text[500];

    Text() {
        tip_informatie = 1;
    }

    Text(char txt[], char name[]) {
        strcpy(text, txt);
        strcpy(nume, name);
        tip_informatie = 1;
    }

    Text &operator=(const Text &c);

    void afisare_info() {
        cout << "Id: " << id << '\n';
        cout << "Numele textului: " << nume << '\n';
        cout << "Textul: " << text << '\n';
    }
};

class Numar_Natural : public Informatie {
public:
    int valoare;

    Numar_Natural() {
        tip_informatie = 2;
    }

    Numar_Natural(int val, char name[]) {
        valoare = val;
        strcpy(nume, name);
        tip_informatie = 2;
    }

    Numar_Natural &operator= (const Numar_Natural &c);

    void afisare_info() {
        cout << "Id: " << id << '\n';
        cout << "Numele numarului natural: " << nume << '\n';
        cout << "Numarul natural: " << valoare << '\n';
    }
};

class Numar_Complex : public Informatie {
public:
    double re, im;

    Numar_Complex() {
        tip_informatie = 3;
    }

    Numar_Complex(double real, double imag, char name[]) {
        re = real;
        im = imag;
        strcpy(nume, name);
        tip_informatie = 3;
    }

    Numar_Complex &operator= (const Numar_Complex &c);

    void afisare_info() {
        cout << "Id: " << id << '\n';
        cout << "Numele numarului complex: " << nume << '\n';
        cout << "Numarul complex: " << re << " + i" << im << '\n';
    }

};

class Adresa : public Informatie {
public:
    char tara[50], judet[50], oras[50], strada[50];
    int numar;

    Adresa() {
        tip_informatie = 4;
    }

    Adresa(char t[], char j[], char o[], char s[], int nr, char name[]) {
        strcpy(nume, name);
        strcpy(tara, t);
        strcpy(judet, j);
        strcpy(oras, o);
        strcpy(strada, s);
        numar = nr;
        tip_informatie = 4;
    }

    Adresa &operator= (const Adresa &c);

    void afisare_info() {
        cout << "Id: " << id << '\n';
        cout << "Numele adresei: " << nume << '\n';
        cout << "Adresa: " << tara << ", " << judet << ", " << oras << ", " << strada << ", " << numar << '\n';
    }
};

Informatie &Informatie::operator=(const Informatie &c)  {
    strcpy(this->nume, c.nume);
    tip_informatie = c.tip_informatie;
    return *this;
}

Text &Text::operator=(const Text &c) {
    strcpy(this->text, c.text);
    tip_informatie = c.tip_informatie;
    return *this;
}

Numar_Natural &Numar_Natural::operator= (const Numar_Natural &c) {
    this->valoare = c.valoare;
    tip_informatie = c.tip_informatie;
    return *this;
}

Numar_Complex &Numar_Complex::operator= (const Numar_Complex &c) {
    this->re = c.re;
    this->im = c.im;
    tip_informatie = c.tip_informatie;
    return *this;
}

Adresa &Adresa::operator= (const Adresa &c) {
    strcpy(this->nume, c.nume);
    strcpy(this->tara, c.tara);
    strcpy(this->judet, c.judet);
    strcpy(this->oras, c.oras);
    strcpy(this->strada, c.strada);
    this->numar = c.numar;
    tip_informatie = c.tip_informatie;
    return *this;
}

class Biblioteca {
public:
    Informatie* b[2000];
    int viz[2000];
    int numar_inregistrari;

    Biblioteca() {
        numar_inregistrari = 0;
        for (int i = 1; i < 2000; i++)
            viz[i] = 0;
    }

    virtual void Adaugare_Informatie(Informatie* info) {
        int poz = 0;
        bool gasit = 0, existent = 0;
        for (int i = 1; i <= numar_inregistrari; i++) {
            if (viz[i] == 0 && gasit == 0) {
                poz = i;
                gasit = 1;
            }
            if (strcmp(b[i]->nume, info->nume) == 0) {
                existent = 1;
                poz = i;
                break;
            }
        }
        if (existent) {
            if (b[poz]->tip_informatie != info->tip_informatie) {
                cout << "Eroare la adaugare! Tipuri de informatii diferite!\n";
                return;
            }
            if (info->tip_informatie == 4) {
                cout << "Eroare! Tipul informatiei este adresa!\n";
                return;
            }
            if (info->tip_informatie == 1) {
                Text *p = dynamic_cast<Text*>(b[poz]);
                Text *q = dynamic_cast<Text*>(info);
                strcat(p->text, q->text);
                return;
            }
            if (info->tip_informatie == 2) {
                Numar_Natural *p = dynamic_cast<Numar_Natural*>(b[poz]);
                Numar_Natural *q = dynamic_cast<Numar_Natural*>(info);
                p->valoare += q->valoare;
                return;
            }
            if (info->tip_informatie == 3) {
                Numar_Complex *p = dynamic_cast<Numar_Complex*>(b[poz]);
                Numar_Complex *q = dynamic_cast<Numar_Complex*>(info);
                p->re += q->re;
                p->im += q->im;
                return;
            }

        } else {
            if (!gasit) {
                poz = ++numar_inregistrari;
                b[poz] = new Informatie();
                b[poz] = info;
                b[poz]->id = poz;
                viz[poz] = 1;
            } else {
                delete b[poz];
                b[poz] = new Informatie();
                b[poz] = info;
                b[poz]->id = poz;
                viz[poz] = 1;
            }

        }
    }

    void stergere_informatie(int id) {
        viz[id] = 0;
    }

    void stergere_informatie(char nume[]) {
        for (int i = 1; i <= numar_inregistrari; i++)
            if (strcmp(nume, b[i]->nume) == 0 && viz[i] == 1) {
                viz[i] = 0;
                return;
            }
    }

    void regasire_informatii(int id) {
        if (viz[id] == 0) {
            cout << "Nu exista\n";
            return;
        }
        b[id]->afisare_info();
    }

    void regasire_informatii(char nume[]) {
        for (int i = 1; i <= numar_inregistrari; i++)
            if (viz[i] == 1 && strcmp(b[i]->nume, nume) == 0) {
                b[i]->afisare_info();
                return;
            }
        cout << "Nu exista\n";
    }

    void cautare_informatie(char txt[]) {
        for (int i = 1; i <= numar_inregistrari; i++)
            if (viz[i] == 1 && b[i]->tip_informatie == 1) {
                Text *p = dynamic_cast<Text*>(b[i]);
                if (strcmp(p->text, txt) == 0)
                    b[i]->afisare_info();
                return;
            }
        cout << "Nu exista\n";
    }

    void cautare_informatie(int val) {
        for (int i = 1; i <= numar_inregistrari; i++)
            if (viz[i] == 1 && b[i]->tip_informatie == 2) {
                Numar_Natural *p = dynamic_cast<Numar_Natural*>(b[i]);
                if (p->valoare == val) {
                    b[i]->afisare_info();
                    return;
                }
            }
        cout << "Nu exista\n";
    }

    void cautare_informatie(int re, int im) {
        for (int i = 1; i <= numar_inregistrari; i++)
            if (viz[i] == 1 && b[i]->tip_informatie == 3) {
                Numar_Complex *p = dynamic_cast<Numar_Complex*>(b[i]);
                if (p->re == re)
                    if (p->im == im) {
                        b[i]->afisare_info();
                        return;
                    }
            }
        cout << "Nu exista\n";
    }

    void cautare_informatie(char tara[], char judet[], char oras[], char strada[], int numar) {
        for (int i = 1; i <= numar_inregistrari; i++)
            if (viz[i] == 1 && b[i]->tip_informatie == 4) {
                Adresa *p = dynamic_cast<Adresa*>(b[i]);
                if (strcmp(p->tara, tara) == 0)
                    if (strcmp(p->judet, judet) == 0)
                        if (strcmp(p->oras, oras) == 0)
                            if (strcmp(p->strada, strada) == 0)
                                if (p->numar == numar) {
                                    b[i]->afisare_info();
                                    return;
                                }

            }
        cout << "Nu exista\n";
    }
};


Informatie* Informatie::citire_info() {
    cout << "Alegeti tipul informatiei citite: ";
    cin >> tip_informatie;
    if (tip_informatie == 1) {
        Text *txt = new Text();
        txt->tip_informatie = 1;
        cout << "Dati numele textului: ";
        cin >> txt->nume;
        cout << "Dati textul: ";
        cin >> txt->text;
        return txt;
    } else if (tip_informatie == 2) {
        Numar_Natural *nr = new Numar_Natural();
        nr->tip_informatie = 2;
        cout << "Dati numele numarului natural: ";
             cin >> nr->nume;
        cout << "Dati numarul natural: ";
        cin >> nr->valoare;
        return nr;
    } else if (tip_informatie == 3) {
        Numar_Complex *nrC = new Numar_Complex();
        nrC->tip_informatie = 3;
        cout << "Dati numele numarului complex: ";
            cin >> nrC->nume;
        cout << "Dati partea reala: ";
            cin >> nrC->re;
        cout << "Dati partea imaginara: ";
            cin >> nrC->im;
        return nrC;
    } else if (tip_informatie == 4) {
        Adresa *adr = new Adresa();
        adr->tip_informatie = 4;
        cout << "Dati numele adresei: ";
            cin >> adr->nume;
        cout << "Dati tara: ";
            cin >> adr->tara;
        cout << "Dati judetul: ";
            cin >> adr->judet;
        cout << "Dati orasul: ";
            cin >> adr->oras;
        cout << "Dati strada: ";
            cin >> adr->strada;
        cout << "Dati numarul: ";
            cin >> adr->numar;
        return adr;
    }
    Informatie *info = new Informatie();
    return info;
}

int main() {
try{
    Informatie *info = new Informatie();
    info = info->citire_info();
    Biblioteca b;
    b.Adaugare_Informatie(info);
    for (int i = 1; i <= b.numar_inregistrari; i++) {
        if (b.viz[i] == 1)
            b.b[i]->afisare_info();
    }

    b.stergere_informatie("Doi");
    Informatie *inf = new Informatie();
    inf = inf->citire_info();
    b.Adaugare_Informatie(inf);
    for (int i = 1; i <= b.numar_inregistrari; i++) {
        if (b.viz[i] == 1)
            b.b[i]->afisare_info();
    }
    return 0;
}
catch (...) {
    cerr << "Eroare!!!!!!";
    return 1;
}



}
