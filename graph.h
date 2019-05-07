#pragma once

#include <stdlib.h>
#include <memory>
#include <iostream>
#include <fstream>



class Graph {

protected:
    int ilosc_wierzcholkow, ilosc_krawedzi;
    double gestosc; //gestosc grafu

public:
    const int& getW() const { return ilosc_wierzcholkow; }
    const int& getK() const { return ilosc_krawedzi; }

    virtual void wypelnij_graf(const bool allowLoops) const = 0; //wypelnij graf losowymi liczbami
    virtual void wypisz_graf() const =  0; //wypisuje graf na konsole
    virtual const int czytaj_z_pliku() = 0; //wypelnia graf danymi z pliku
    virtual void stworz_plik(const int w_startowy) const = 0; //tworzy plik z wylosowanym grafem
    virtual ~Graph() {};
    explicit Graph(int s_wierzcholek, int s_krawedz, double s_gestosc) : ilosc_wierzcholkow(s_wierzcholek), ilosc_krawedzi(s_krawedz), gestosc(s_gestosc) {}
    Graph() {};// uzywany gdy graf wczytywany jest z pliku, nie sa znane rozmiary podczas tworzenia grafu

};