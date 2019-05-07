#pragma once

#include "graph.h"


struct Edge {

    //wierzcholek poczatkowy, wierzcholek koncowy, waga polaczenia pomiedzy nimi
    int source, dest, weight;
};


//graf reprezentowany lista sasiedztwa
class ListGraph : public Graph {

    Edge* edge; //tablica krawedzi w grafie

public:

    void wypelnij_graf(const bool allowLoops) const override; //wypelnij graf losowymi liczbami
    void wypisz_graf() const override; //wypisuje graf na konsole
    const int czytaj_z_pliku() override; //wypelnia graf danymi z pliku
    void stworz_plik(const int w_startowy) const override; //tworzy plik z wylosowanym grafem

    const Edge* getStruct() const { return edge; }
    void dodaj_krawedz(int poczatkowy, int koncowy, int waga, int j) const; //dodaje krawedz pomiedzy wierzcholkami o odpowiedniej wadze w jotym miejscu
    bool czy_polaczony(int poczatkowy, int koncowy) const; //sprawdza czy wierzcholki posiadaja juz polaczenie

    explicit ListGraph(int s_wierzcholek, double s_gestosc)
            :Graph(s_wierzcholek, static_cast<int>(s_gestosc* s_wierzcholek* (s_wierzcholek - 1)), s_gestosc),
             edge(new Edge[static_cast<int>(s_gestosc* s_wierzcholek* (s_wierzcholek - 1))]){}//wylicza ilosc krawedzi w grafie w zaleznosci od gestosci i ilosci wierzcholkow
    ListGraph() : Graph() {};
    ~ListGraph() { delete[] edge; }
};
