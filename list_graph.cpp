#include "list_graph.h"

static int pierwsza_losowa = -1; // do okreslenia jakie wartosci beda losowane, jest to pierwsza mozliwa do wylosowania liczba

void ListGraph::dodaj_krawedz(int poczatkowy, int koncowy, int jwaga, int j) const {

    edge[j].source = poczatkowy;
    edge[j].dest = koncowy;
    edge[j].weight = jwaga;
}


bool ListGraph::czy_polaczony(int poczatkowy, int koncowy) const {

    for (int i = 0; i < ilosc_krawedzi; ++i) {

        if (edge[i].dest == koncowy && edge[i].source == poczatkowy) return true;
    }
    return false;
}


void ListGraph::wypelnij_graf(const bool czy_petle) const {

    if (gestosc == 1) {  //graf pelny

        int j = 0;
        for (int ipoczatkowy = 0; ipoczatkowy < ilosc_wierzcholkow; ++ipoczatkowy) {
            for (int ikoncowy = 0; ikoncowy < ilosc_wierzcholkow; ++ikoncowy) {

                if (ipoczatkowy!= ikoncowy) { //warunek uniemozliwiajacy powstawanie petli

                    int iwaga = rand() % 20 + pierwsza_losowa;
                    while (iwaga == 0) { //kazda waga krawedzi oprocz diagonali musi byc rozna od 0

                        iwaga = rand() % 20 + pierwsza_losowa;
                    }
                    dodaj_krawedz(ipoczatkowy, ikoncowy, iwaga, j++);
                }
            }
        }
    }
    else {

        int licznik_i_krawedzi = 0;//licznik
        while (licznik_i_krawedzi < ilosc_krawedzi) {//ilosc_krawedzi zostala wyliczona ze wzoru z powodu gestosci aktualnego grafu

            int poczatkowy = rand() % ilosc_wierzcholkow;//losowanie wierzcholka poczatkowego
            int koncowy = rand() % ilosc_wierzcholkow;//losowanie wierzcholka koncowego
            if (!czy_polaczony(poczatkowy, koncowy)) {

                int iwaga = rand() % 20 + pierwsza_losowa;
                while (iwaga == 0) {

                    iwaga = rand() % 20 + pierwsza_losowa;//zadna dodatkowa waga nie moze byc rowna 0 poniewaz zmienilo by to gestosc grafu
                }

                if (poczatkowy != koncowy) dodaj_krawedz(poczatkowy, koncowy, iwaga, licznik_i_krawedzi++);
                else if (czy_petle) dodaj_krawedz(poczatkowy, koncowy, iwaga, licznik_i_krawedzi++);//w zaleznosci od wyboru uzytkownika dopuszczalne sa petle
            }
        }
    }
}


void ListGraph::wypisz_graf() const {

    std::cout << std::string(30, '-') << "\n Reprezentacja: Lista sasiedztwa\n\n";
    for (int ipoczatkowy = 0; ipoczatkowy < ilosc_wierzcholkow; ++ipoczatkowy) {


        std::cout << ipoczatkowy;
        for (int ikrawedz = 0; ikrawedz < ilosc_krawedzi; ++ikrawedz) {


            if (edge[ikrawedz].source == ipoczatkowy)
                std::cout << "->" << "[" << edge[ikrawedz].dest << "|" << edge[ikrawedz].weight << "]";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}


const int ListGraph::czytaj_z_pliku() {

    std::ifstream file("Input.txt");
    if (!file.is_open()) {
        throw "Plik nie zostal otworzony poprawnie!";
        return 1;
    }

    //inicjalizacja atrybutow oraz wierzcholka startowego
    int w_startowy, source, dest, weight;
    file >> ilosc_krawedzi >> ilosc_wierzcholkow >> w_startowy;
    edge = new Edge[ilosc_krawedzi];


    for (int iilosc_krawedzi = 0; iilosc_krawedzi < ilosc_krawedzi; ++iilosc_krawedzi) {

        file >> source >> dest >> weight;
        dodaj_krawedz(source, dest, weight, iilosc_krawedzi);
    }
    file.close();
    return w_startowy;
}



void ListGraph::stworz_plik(const int w_startowy) const {

    std::ofstream file("sInput.txt");
    if (!file.is_open()) {
        throw  "Plik nie zostal otworzony poprawnie!";
        return;
    }

    file << ilosc_krawedzi << " " << ilosc_wierzcholkow << " " << w_startowy << "\n";
    for (int ikrawedz = 0; ikrawedz < ilosc_krawedzi; ++ikrawedz) {

        file << edge[ikrawedz].source << " ";
        file << edge[ikrawedz].dest << " ";
        file << edge[ikrawedz].weight << "\n";
    }
    file.close();
}
