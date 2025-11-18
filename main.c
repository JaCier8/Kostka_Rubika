/*Kostka rubika
* Program wczytuje ruchy kwadratowej kostki rubika o określonej
* w kompilatorze (lub natywnie ustawionej na 5) rozmiarze ścian
* w sposób opisany w zadaniu i pisze w stadardowym wyjściu
* stan kostki, widzianej na płaszczyźnie 2D

* Autorstwa Jan Ciecierski
* Na potrzeby projektu z wdp
* Ostatnia Edycja: 10.12.2024
*/

#include <stdio.h>
#include <stdbool.h>

#define N 5
#define SCIANY 6 // ilość ścian
#define U 0 // sciana górna (up)
#define L 1 // sciana lewa (left)
#define F 2 // sciana przednia (front)
#define R 3 // sciana prawa (right)
#define B 4 // sciana tylnia (back)
#define D 5 // ściana dolna (down)

// Struktura zawierająca wszystkie możliwe parametry pojedyńczego ruchu
struct ruch {
    int liczbaWarstw;
    char strona;
    int typObrotu;
    bool czyCzytac;
};
// Wczytywanie danych do struktury zawierającą: liczbaWarstw do złapania, którą stronę łapiemy,
// jaki typ obrotu (w którą stronę/ile razy), czy po ruchu przeczytać kostke.
bool wejscie(struct ruch *input) {
    int x, mnoznik = 1, suma = 0;
    if ((x = getchar()) != '.') {
        if(x == '\n') {
            (*input).czyCzytac = 1;
            (*input).liczbaWarstw = 0;
            (*input).typObrotu = 0;
            (*input).strona = 0;
        }
        else {
            if(x >= '0' && x <= '9') {
                while(x >= '0' && x <= '9') {
                    suma = suma*10 + (x - '0');
                    x = getchar();
                }
                (*input).liczbaWarstw = suma;
            }
            else (*input).liczbaWarstw = 1;
            (*input).strona = x;
            x = getchar();
            if(x == '\'') {
                (*input).typObrotu = 3;
                x = getchar();
            }
            else if(x == '"') {
                input->typObrotu = 2;
                x = getchar();
            }
            else (*input).typObrotu = 1;
            if(x == '\n') {
                (*input).czyCzytac = true;
            }
            else {
                (*input).czyCzytac = false;
                ungetc(x, stdin);
            }
        }
        return true;
    }
    return false;
}

// Wypisuje ścianę górną i dolną z potrzebnymi N + 1 spacjami z lewej strony
void wypisanieScianyUlubD(int sciana[][N]) {
    for(int i = 0; i < N; i++) {
        printf("%*c", N+1, ' ');
        for(int j = 0; j < N; j++)printf("%d", sciana[i][j]);
        printf("\n");
    }
}

// Wypisuje ściany {lewą, przednią, prawą, tylnią} między którymi wypisuje "|"
void wypisanieSrodkowychScian(int kostka[][N][N]) {
    for(int wiersz = 0; wiersz < N; wiersz++) {
        for(int sciana = L; sciana <= B; sciana++) {
            for(int kolumna = 0; kolumna < N; kolumna++) {
                printf("%d", kostka[sciana][wiersz][kolumna]);
            }
            if(sciana == B) printf("\n");
            else printf("|");
        }
    }
}
// Wypisuje ściany funckjami opisanymi wyżej
void wypisanieKostki(int kostka[][N][N]) {
    wypisanieScianyUlubD(kostka[U]);
    wypisanieSrodkowychScian(kostka);
    wypisanieScianyUlubD(kostka[D]);
}
// Wczytuje do tablicy trójwymiarowej "kostka", dwuwymiarowe ściany.
void wczytywanieSciany(int sciana[][N],int k) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            sciana[i][j] = k;
        }
    }
}
// Wyswołuje funkcję opisaną wyżej dla każdej ściany
void wczytywanieScian(int kostka[][N][N]) {
    for(int i = 0; i < SCIANY; i++) wczytywanieSciany(kostka[i], i);
}
// Obraca daną scianę o 90 stopni w Prawo, poprzez transponowanie i odwrócenie wierszy.
void rotacjaScianyWPrawo(int sciana[][N]) {
    int temp;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            temp = sciana[i][j];
            sciana[i][j] = sciana[j][i];
            sciana[j][i] = temp;
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N/2; j++) {
            temp = sciana[i][j];
            sciana[i][j] = sciana[i][N-1-j];
            sciana[i][N-1-j] = temp;
        }
    }
}
/* Obraca daną scianę o 90 stopni w Prawo, poprzez transponowanie i odwrócenie wierszy.
 * zdefiniowana żeby nie wywoływać tej wyżej 3 razy*/
void rotacjaScianyWLewo(int sciana[][N]) {
    int temp;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < i; j++) {
            temp = sciana[i][j];
            sciana[i][j] = sciana[j][i];
            sciana[j][i] = temp;
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N/2; j++) {
            temp = sciana[j][i];
            sciana[j][i] = sciana[N-1-j][i];
            sciana[N-1-j][i] = temp;
        }
    }
}

// Przenosi kolumny dwóch podanych ścian z pierwszej na drugą
void przeniesKolumne(int kostka[][N][N], int sciana1, int sciana2, int kolumna) {
    if (sciana1 == B) {
        for(int i = 0; i < N; i++) {
            kostka[sciana2][i][kolumna] = kostka[sciana1][N-1- i][N - 1 - kolumna];
        }
    }
    else if (sciana2 == B) {
        for(int i = 0; i < N; i++) {
            kostka[sciana2][N-1- i][N - 1 - kolumna] = kostka[sciana1][i][kolumna];
        }
    }
    else {
        for(int i = 0; i < N; i++) {
            kostka[sciana2][i][kolumna] = kostka[sciana1][i][kolumna];
        }
    }
}
// Kopiuje kolumnę na zapamiętaną tablicę 2D z podanej ściany
void kopiujKolumnę(int kostka[][N][N], int temp[], int sciana, int kolumna) {
    if(sciana == B) {
        for(int i = 0; i< N; i++) {
            temp[i] = kostka[sciana][N-1- i][N-1- kolumna];
        }
    }
    else {
        for(int i = 0; i< N; i++) {
            temp[i] = kostka[sciana][i][kolumna];
        }
    }
}
// Wkleja kolumnę do danej ściany z tablicy 2D
void wklejKolumnę(int kostka[][N][N], int temp[], int sciana, int kolumna) {
    if(sciana == B) {
        for(int i = 0; i< N; i++) {
            kostka[sciana][i][N - 1 - kolumna] = temp[i];
        }
    }
    else {
        for(int i = 0; i< N; i++) {
            kostka[sciana][i][kolumna] = temp[i];
        }
    }
}
// Przenosi wiersz na daych sciana1 na sciana2
void przeniesWiersz(int kostka[][N][N], int sciana1, int sciana2, int wiersz) {
    for(int i = 0; i < N; i++) {
        kostka[sciana2][wiersz][i] = kostka[sciana1][wiersz][i];
    }
}
// Kopiuje wiersz na zapamiętaną tablicę 2D z podanej ściany
void kopiujWiersz(int kostka[][N][N], int temp[], int sciana, int wiersz) {
    for(int i = 0; i< N; i++) {
        temp[i] = kostka[sciana][wiersz][i];
    }
}
// Wkleja wiersz do danej ściany z tablicy 2D
void wklejWiersz(int kostka[][N][N], int temp[], int sciana, int wiersz) {
    for(int i = 0; i< N; i++) {
        kostka[sciana][wiersz][i] = temp[i];
    }
}
/*Wywołuje wcześniej opisane funkcje by wykonać ruch "u" lub "d",
* przenosząc po koleji wiersze scian "przylegających" do "U" lub "D" */
void przesunPoziom(int kostka[][N][N], int wiersz) {
    int temp[N];
    kopiujWiersz(kostka, temp, L, wiersz);
    przeniesWiersz(kostka, F, L, wiersz);
    przeniesWiersz(kostka, R, F, wiersz);
    przeniesWiersz(kostka, B, R, wiersz);
    wklejWiersz(kostka, temp, B, wiersz);
}
/*Wywołuje wcześniej opisane funkcje by wykonać ruch "r" lub "l",
* przenosząc po koleji kolumny ścian "przylegających" do "R" lub "L" */
void przesunPion(int kostka[][N][N],int kolumna) {
    int temp[N];
    kopiujKolumnę(kostka, temp, U, kolumna);
    przeniesKolumne(kostka, F, U, kolumna);
    przeniesKolumne(kostka, D, F, kolumna);
    przeniesKolumne(kostka,B, D, kolumna);
    wklejKolumnę(kostka, temp, B, kolumna);
}

void przesunPionIPoziom(int kostka[][N][N], int wierszoKolumna) {

}

void obrotLR(struct ruch input, int kostka[][N][N]) {
    if (input.strona == 'r') {
        rotacjaScianyWPrawo(kostka[R]);
        if (input.liczbaWarstw == N) rotacjaScianyWLewo(kostka[L]);
        for (int j = 0; j < input.typObrotu; j++) {
            for(int i  = 0; i < input.liczbaWarstw; i++) {
                przesunPion(kostka, N - 1 - i);
            }
        }
    }
    if (input.strona == 'l') {
        rotacjaScianyWPrawo(kostka[L]);
        if (input.liczbaWarstw == N) rotacjaScianyWLewo(kostka[R]);
        for (int j = 3; j >= input.typObrotu; j--) {
            for(int i = 0; i < input.liczbaWarstw; i++) {
                przesunPion(kostka, i);
            }
        }
    }
}

void obrotUD(struct ruch input, int kostka[][N][N]) {
    if (input.strona == 'u') {
        rotacjaScianyWPrawo(kostka[U]);
        if (input.liczbaWarstw == N) rotacjaScianyWLewo(kostka[D]);
        for (int j = 0; j < input.typObrotu; j++) {
            for(int i  = 0; i < input.liczbaWarstw; i++) {
                przesunPoziom(kostka, i);
            }
        }
    }
    if (input.strona == 'd') {
        rotacjaScianyWPrawo(kostka[D]);
        if (input.liczbaWarstw == N) rotacjaScianyWLewo(kostka[U]);
        for (int j = 3; j >= input.typObrotu; j--) {
            for(int i = 0; i < input.liczbaWarstw; i++) {
                przesunPoziom(kostka, N-1-i);
            }
        }
    }
}

void obrotFB(struct ruch input, int kostka[][N][N]) {
    if (input.strona == 'f') {
        rotacjaScianyWPrawo(kostka[F]);
        if (input.liczbaWarstw == N) rotacjaScianyWLewo(kostka[B]);
    }
}

void jakiRuch(struct ruch input, int kostka[][N][N]) {
    if (input.strona == 'l' || input.strona == 'r') {
        obrotLR(input, kostka);
    }
    if (input.strona == 'u' || input.strona == 'd') {
        obrotUD(input, kostka);
    }
    if(input.czyCzytac) wypisanieKostki(kostka);
}


int main(void){
    int kostka[SCIANY][N][N]; // kostka --> kostka[sciana][wiersz][kolumna]
    int tab[1000], liczbaRuchow;
    wczytywanieScian(kostka);
    struct ruch input;
    while(wejscie(&input)) {
        jakiRuch(input, kostka);
    }
    wypisanieKostki(kostka);
    return 0;
}
