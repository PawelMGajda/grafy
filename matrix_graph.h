#pragma once

#include "graph.h"


class MatrixGraph : public Graph {

    std::unique_ptr<std::unique_ptr<int[]>[]> matrix; //macierz dynamiczna

    
public:
    
    void wypelnij_graf(const bool allowLoops) const override; //wypelnij graf losowymi liczbami
    void wypisz_graf() const override; //wypisuje graf na konsole
    const int czytaj_z_pliku() override; //wypelnia graf danymi z pliku
    void stworz_plik(const int w_startowy) const override; //tworzy plik z wylosowanym grafem

    //zwraca wartosc wagi konkretnej komorki 
    const int& getWeight(int wiersz, int kolumna) const { return matrix[wiersz][kolumna]; }

    explicit MatrixGraph(int t_V, double gestosc);
    MatrixGraph() : Graph() {};
};