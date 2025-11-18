# Kostka Rubika

**Autor:** Jan Ciecierski

## Opis

`Kostka Rubika` to program w języku C, który symuluje operacje i wizualizację sześciennej kostki o kwadratowych ścianach. Domyślnie program działa dla kostki **5x5x5** (`#define N 5`).

Program wczytuje sekwencję ruchów ze standardowego wejścia, modyfikuje wewnętrzny stan kostki, a następnie wypisuje jej bieżącą płaską reprezentację graficzną na standardowym wyjściu.

## Główne Funkcjonalności

* **Dowolny rozmiar `N`**: Rozmiar kostki jest definiowany stałą `#define N` w kodzie źródłowym, domyślnie ustawioną na **5**.
* **Wizualizacja 2D**: Stan kostki jest wypisywany na konsolę w płaskim formacie 2D, z użyciem spacji i separatorów (`|`) dla czytelności.
* **Obsługa warstw**: Możliwość przesuwania dowolnej liczby warstw wewnętrznych, nie tylko zewnętrznych ścian.
* **Intuicyjny zapis ruchów**: Obsługa formatu wejściowego pozwalającego na definiowanie liczby warstw, strony, i typu obrotu (pojedynczy, podwójny, odwrócony).

## Struktura Danych i Logika

Kostka jest reprezentowana przez trójwymiarową tablicę `kostka[SCIANY][N][N]`, gdzie `SCIANY` jest zdefiniowane jako 6.

### Kluczowe operacje:

* **`rotacjaScianyWPrawo` / `rotacjaScianyWLewo`**: Implementują obrót o 90 stopni dla pojedynczej ściany poprzez transpozycję i odwracanie wierszy/kolumn.
* **`przesunPoziom` / `przesunPion`**: Podstawowe funkcje realizujące przenoszenie kolumn/wierszy między sąsiednimi ścianami przy obrocie warstwy.
* **`obrotLR` / `obrotUD`**: Funkcje wyższego poziomu, które koordynują rotacje ścian i przesuwanie warstw dla ruchów poziomych (`u`/`d`) i bocznych (`l`/`r`).

## Budowanie

Projekt używa systemu CMake do budowania.

### Wymagania:

* **CMake** (wersja 3.29 lub nowsza).
* Kompilator C wspierający standard **C11**.

### Komendy budowania:

1.  **Utwórz katalog budowania:**
    ```bash
    mkdir build
    cd build
    ```

2.  **Skonfiguruj projekt:**
    ```bash
    cmake ..
    ```

3.  **Zbuduj plik wykonywalny `Kostka`:**
    ```bash
    cmake --build .
    ```

## Użycie i Format Wejściowy

Program czyta ruchy ze standardowego wejścia. Sekwencja ruchów powinna kończyć się znakiem `.`.

### Format pojedynczego ruchu:

`[LiczbaWarstw] [Strona] [Modyfikator]`

| Element | Opis | Wartości | Domyślnie |
| :--- | :--- | :--- | :--- |
| `LiczbaWarstw` (opcjonalnie) | Określa głębokość warstwy od zewnątrz. | Liczba całkowita (np. `2`) | `1` |
| `Strona` | Określa obracaną oś lub ścianę. | `u`, `d`, `l`, `r`, `f`, `b` | Wymagany |
| `Modyfikator` (opcjonalnie) | Kierunek/krotność obrotu. | Brak (90° w prawo), `'` (270° w prawo / 90° w lewo), `"` (180°) | Brak (90° w prawo) |

**Ważne:** Jeśli po ruchu następuje znak nowej linii (`\n`), program wypisze stan kostki; w przeciwnym razie będzie kontynuował czytanie kolejnych ruchów w tej samej linii.

### Przykłady wejścia:

| Wejście | Opis |
| :--- | :--- |
| `r` | Obrót prawej ściany o 90° w prawo. |
| `2u'` | Obrót dwóch górnych warstw o 90° w lewo. |
| `d""` | Obrót dolnej ściany o 180°. |
| `r u l' .` | Sekwencja ruchów zakończona znakiem `.` |
