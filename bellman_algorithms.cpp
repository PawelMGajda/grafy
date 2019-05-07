#include "bellman_algorithms.h"

static int  nieskonczonosc = 1000000; //waga polaczenia pomiedzy wierzcholkami na poczatku dzialania algorytmu
static int  m_nieskonczonosc = -1000000; //w przypadku ujemnej petli

//wypisuje wyniki na konsole oraz do pliku Output.txt
void wypisz_wyniki(std::string w_sciezki[], int d_sciezki[], int ilosc_wierzcholkow, int w_startowy) {

    std::ofstream file("Output.txt");

    std::cout << std::string(20, '-') << "\n   Wyniki:\n\n";
    std::cout << "Wierzcholek startowy -> " << w_startowy << "\n\n";

    file << std::string(20, '-') << "\n   Wyniki:\n\n";
    file << "Wierzcholek startowy -> " << w_startowy << "\n\n";

    for (int i = 0; i < ilosc_wierzcholkow; ++i) {
        //wypisuje najkrotsza sciezke
        if (d_sciezki[i] == m_nieskonczonosc) {
            std::cout << i << "->" << "-inf\n";
            file << i << "->" << "-inf\n";
            continue;
        }
        else if (d_sciezki[i] == nieskonczonosc) {
            std::cout << i << "->" << "inf\n";
            file << i << "->" << "inf\n";
            continue;
        }

        else {
            std::cout << i << "->" << d_sciezki[i];
            file << i << "->" << d_sciezki[i];
        }



        //petle zapewniaja rowne ulozenie wynikow
        if (i < 10) {
            std::cout << "   ";
            file << "   ";
        }
        else if (i < 100) {
            std::cout << "  ";
            file << "  ";
        }
        else {
            std::cout << " ";
            file << " ";
        }

        
        if ((d_sciezki[i] >= 100 && d_sciezki[i] < 1000) || (-100 > d_sciezki[i]  && d_sciezki[i] <= -10)) {

            std::cout << " Najkrotsza sciezka: " << w_sciezki[i] << i;
            file << " Najkrotsza sciezka: " << w_sciezki[i] << i;
        }
        else if (0 <= d_sciezki[i] && d_sciezki[i] < 10) {

            std::cout << "   Najkrotsza sciezka: " << w_sciezki[i] << i;
            file << "   Najkrotsza sciezka: " << w_sciezki[i] << i;
        }
        else if ((d_sciezki[i] >= 10 && d_sciezki[i] < 100) || (-10 < d_sciezki[i] && d_sciezki[i] < 0)) {

            std::cout << "  Najkrotsza sciezka: " << w_sciezki[i] << i;
            file << "  Najkrotsza sciezka: " << w_sciezki[i] << i;
        }
        else { // (-1000,-100] && [1000,10000)

            std::cout << "Najkrotsza sciezka: " << w_sciezki[i] << i;
            file << "Najkrotsza sciezka: " << w_sciezki[i] << i;
        }
        std::cout << std::endl;
        file << std::endl;
    }
    std::cout << std::endl;
    file.close();
}


//bellmanFord lista sasiedztwa
double bellmanFord(std::shared_ptr<ListGraph> t_graph, int w_startowy, bool czy_wypisz) {

    std::string* sciezka = new std::string[t_graph->getW()]; //sciezka najkrotszej drogi

    auto t_start = std::chrono::high_resolution_clock::now(); //start clock

    int* d_sciezki = new int[t_graph->getW()]; //najkrotsza droga 

    for (int i = 0; i < t_graph->getW(); ++i) {

        d_sciezki[i] = nieskonczonosc; //ustawia odleglosc poczatkowa na nieskonczonosc-ustalona na poczatku pliku bellman_algorithms.cpp
    }

    d_sciezki[w_startowy] = 0; //odlegosc od wierzcholka startowego do niego samego ustawia na 0

    for (int i = 1; i < t_graph->getW(); ++i) { //dla ilosc wierzcholkow -1
        for (int j = 0; j < t_graph->getK(); ++j) { //dla wszystkich krawedzi

            int u = t_graph->getStruct()[j].source;
            int v = t_graph->getStruct()[j].dest;
            int waga = t_graph->getStruct()[j].weight;

            if (d_sciezki[u] + waga < d_sciezki[v]) { //porownanie starej drogi do nowej
                d_sciezki[v] = d_sciezki[u] + waga; //jesli nowa droga jest krotsza zamienia

                if (czy_wypisz) { //wypisze sciezke w zaleznosci od wyboru rodzaju testu

                    sciezka[v].clear();
                    sciezka[v].append(sciezka[u] + std::to_string(u) + "->");
                }
            }
        }
    }

    //sprawdzanie czy istnieja negatywne cykle, ktore sa zabronione
    for (int i = 1; i < t_graph->getW(); ++i) {
        for (int j = 0; j < t_graph->getK(); ++j) {

            int u = t_graph->getStruct()[j].source;
            int v = t_graph->getStruct()[j].dest;
            int waga = t_graph->getStruct()[j].weight;
            if (d_sciezki[u] + waga < d_sciezki[v]) {

                if (d_sciezki[u] > nieskonczonosc/2) d_sciezki[u] = nieskonczonosc;
                else d_sciezki[v] = m_nieskonczonosc;
            }
            else if (d_sciezki[u] > nieskonczonosc/2) d_sciezki[u] = nieskonczonosc;
        }
    }
    auto t_end = std::chrono::high_resolution_clock::now(); //stop clock

    //prinitng solution if user wanted to
    if (czy_wypisz) wypisz_wyniki(std::move(sciezka), std::move(d_sciezki), t_graph->getW(), w_startowy);
    delete[] d_sciezki;
    return std::chrono::duration<double, std::milli>(t_end - t_start).count(); //zwraca czas wykonania algorytmu
}


//bellmanFord macierz sasiedztwa
//algorytm dziala analogicznie jak dla listy sasiedztwa
double bellmanFord(std::shared_ptr<MatrixGraph> t_graph, int w_startowy, bool czy_wypisz) {

    std::string* sciezka = new std::string[t_graph->getW()];

    auto t_start = std::chrono::high_resolution_clock::now();

    int* d_sciezki = new int[t_graph->getW()];

    for (int i = 0; i < t_graph->getW(); ++i) {

        d_sciezki[i] = nieskonczonosc;
    }

    d_sciezki[w_startowy] = 0;

    for (int i = 1; i < t_graph->getW(); ++i) {
        for (int j = 0; j < t_graph->getW(); ++j) {
            for (int w = 0; w < t_graph->getW(); ++w) {

                int u = j;
                int v = w;
                int waga = t_graph->getWeight(j, w);
                if (d_sciezki[u] + waga < d_sciezki[v]) {

                    d_sciezki[v] = d_sciezki[u] + waga;
                    if (czy_wypisz) {

                        sciezka[v].clear();
                        sciezka[v].append(sciezka[u] + std::to_string(u) + "->");
                    }
                }
            }
        }
    }
    for (int i = 1; i < t_graph->getW(); ++i) {
        for (int j = 0; j < t_graph->getW(); ++j) {
            for (int w = 0; w < t_graph->getW(); ++w) {

                int u = j;
                int v = w;
                int waga = t_graph->getWeight(j, w);
                if (d_sciezki[u] + waga < d_sciezki[v]) {

                    if (d_sciezki[u] > nieskonczonosc / 2) d_sciezki[u] = nieskonczonosc;
                    else if (waga == nieskonczonosc) continue;
                    else d_sciezki[v] = m_nieskonczonosc;
                }
                else if (d_sciezki[u] > nieskonczonosc/2) d_sciezki[u] = nieskonczonosc;
            }
        }
    }
    auto t_end = std::chrono::high_resolution_clock::now();

    if (czy_wypisz) wypisz_wyniki(std::move(sciezka), std::move(d_sciezki), t_graph->getW(), w_startowy);
    delete[] d_sciezki;
    return std::chrono::duration<double, std::milli>(t_end - t_start).count();
}
