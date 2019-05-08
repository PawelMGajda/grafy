#include "matrix_graph.h"

static int nieskonczonosc = 1000000;

static int pierwsza_losowa = -1; // do okreslenia jakie wartosci beda losowane, jest to pierwsza mozliwa do wylosowania liczba

//konstruktor
MatrixGraph::MatrixGraph(int s_wiercholek, double s_gestosc)
        : Graph(s_wiercholek, static_cast<int>(s_gestosc* s_wiercholek* (s_wiercholek - 1)), s_gestosc),
          matrix(std::make_unique<std::unique_ptr<int[]>[]>(s_wiercholek)) {

    for (int wiersz = 0; wiersz < ilosc_wierzcholkow; ++wiersz) {

        matrix[wiersz] = std::make_unique<int[]>(s_wiercholek);
        for (int kolumna = 0; kolumna < ilosc_wierzcholkow; ++kolumna) {

            if (wiersz == kolumna) matrix[wiersz][kolumna] = 0; //zera na diagonali
            else matrix[wiersz][kolumna] = nieskonczonosc; //wartosc poczatkowa ustawiona na nieskonczonosc
        }
    }
}


void MatrixGraph::wypelnij_graf(const bool czy_petle) const {

    if (gestosc == 1) {  //pelny graf
        for (int wiersz = 0; wiersz < ilosc_wierzcholkow; ++wiersz) { 
            for (int kolumna = 0; kolumna < ilosc_wierzcholkow; ++kolumna) { 
                if (wiersz != kolumna) //warunek uniemozliwiajacy powstawanie petli
                {
                    int jwaga = rand() % 20  + pierwsza_losowa;
                    while (jwaga == 0) { //kazda waga krawedzi oprocz diagonali musi byc rozna od 0

                        jwaga = rand() % 20 + pierwsza_losowa;
                    }
                    matrix[wiersz][kolumna] = jwaga;
                }
            }
        }
    }
    else { 

        int licznik_i_krawedzi = ilosc_krawedzi; //ilosc_krawedzi zostala wyliczona ze wzoru z powodu gestosci aktualnego grafu

        while (licznik_i_krawedzi) {

            int p_wierzcholek = rand() % ilosc_wierzcholkow; //losowanie wierzcholka poczatkowego
            int k_wierzcholek = rand() % ilosc_wierzcholkow; //losowanie wierzcholka koncowego


            if (matrix[p_wierzcholek][k_wierzcholek] == 0|| matrix[p_wierzcholek][k_wierzcholek]== nieskonczonosc) {

                int jwaga = rand() % 20 + pierwsza_losowa;
                while (jwaga == 0) { //kazda waga krawedzi oprocz diagonali musi byc rozna od 0

                    jwaga = rand() % 20 + pierwsza_losowa;
                }


                if (p_wierzcholek != k_wierzcholek) {

                    matrix[p_wierzcholek][k_wierzcholek] = jwaga;
                    --licznik_i_krawedzi;
                }
                else if (czy_petle) {//umozliwia istnienie petli na zyczenie uzytkownika

                    matrix[p_wierzcholek][k_wierzcholek] = jwaga;
                    --licznik_i_krawedzi;
                }
            }
        }
    }
}



void MatrixGraph::wypisz_graf() const {

    std::cout << std::string(33, '-') << "\n Reprezentacja: Macierz sasiedztwa\n\n ";

    //wypisuje wierzcholki grafu nad macierza sasiedztwa
    for (int i = 0; i < ilosc_wierzcholkow; ++i) {

        if (i <= 10) std::cout << "    " << i;
        else if (i <= 100) std::cout << "   " << i;
        else std::cout << "  " << i;
    }
    std::cout << "\n\n";

    
    for (int wiersz = 0; wiersz < ilosc_wierzcholkow; ++wiersz) {

        //wyrownanie macierzy do lewej w zaleznosci od ilosci wierzcholkow
        if (wiersz < 10) std::cout << wiersz << "   |";
        else if (wiersz < 100) std::cout << wiersz << "  |";
        else std::cout << wiersz << " |";

        
        for (int kolumna = 0; kolumna < ilosc_wierzcholkow; ++kolumna) {

            int waga = matrix[wiersz][kolumna];

            if (waga == nieskonczonosc) std::cout << "*"; //zamiast wypisywac brak polaczenia uzyto znaku gwiazdki
            else std::cout << waga;

            //wyjustowanie macierzy
            if (abs(waga) < 10 || abs(waga) == nieskonczonosc) std::cout << "    ";
            else if (abs(waga) < 100) std::cout << "   ";
            else std::cout << "  ";

            if (waga < 0) std::cout << '\b'; //poprawia ulozenie w przypadku gdy waga byla ujemna
        }
        
        std::cout << "|\n";
    }
    std::cout << std::endl;
}



const int MatrixGraph::czytaj_z_pliku() {

    std::ifstream file("Input.txt");
    if (!file.is_open()) {
        throw "Plik nie zostal otworzony poprawnie!";
        return 1;
    }

    //inicjalizacja atrybutow oraz wierzcholka startowego
    int w_startowy, source, dest, weight;
    file >> ilosc_krawedzi >> ilosc_wierzcholkow >> w_startowy;
    matrix = std::make_unique<std::unique_ptr<int[]>[]>(ilosc_wierzcholkow);
    
    for (int wiersz = 0; wiersz < ilosc_wierzcholkow; ++wiersz) {

        matrix[wiersz] = std::move(std::make_unique<int[]>(ilosc_wierzcholkow));
        for (int kolumna = 0; kolumna < ilosc_wierzcholkow; ++kolumna) {

            if (wiersz == kolumna) matrix[wiersz][kolumna] = 0;
            else matrix[wiersz][kolumna] = nieskonczonosc;
        }
    }

    //wypelnienie wartosciami z pliku
    for (int iEdge = 0; iEdge < ilosc_krawedzi; ++iEdge) {

        file >> source >> dest >> weight;
        matrix[source][dest] = weight;;
    }
    file.close();
    return w_startowy; 
}



void MatrixGraph::stworz_plik(const int w_startowy) const {

    std::ofstream file("sInput.txt");
    if (!file.is_open()) {
        throw  "Plik nie zostal otworzony poprawnie!";
        return;
    }

    file << ilosc_krawedzi << " " << ilosc_wierzcholkow << " " << w_startowy << "\n";
    for (int wiersz = 0; wiersz < ilosc_wierzcholkow; ++wiersz) {
        for (int kolumna = 0; kolumna < ilosc_wierzcholkow; ++kolumna) {

            if (matrix[wiersz][kolumna] != nieskonczonosc && matrix[wiersz][kolumna] != 0) {

                file << wiersz << " ";
                file << kolumna << " ";
                file << matrix[wiersz][kolumna] << "\n";
            }
        }
    }
    file.close();
}
