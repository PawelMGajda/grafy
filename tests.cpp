#include <time.h>

#include "bellman_algorithms.h"


//funkcja wykonujaca testy
//ilosc_petli - ile razy wykona sie caly cykl dla odpowiedniej ilosci wierzcholko i gestosci grafu
//tab_ilosc_wierzcholkow,tab_gestosc - tabele zawierajace odpowiednio ilosc wierzcholkow oraz wartosci gestosci grafu
template<typename T>
std::ostream& tests(std::ostream& file, int (&tab_ilosc_wierzcholkow)[5], double (&tab_gestosc)[4], int ilosc_petli) {

    for (double gestosc : tab_gestosc) {
        for (int ilosc_wierzcholkow : tab_ilosc_wierzcholkow) {
            double sum = 0;
            for (int ipetla = 0; ipetla < ilosc_petli; ++ipetla) {

                std::shared_ptr<T> graph = std::make_shared<T>(ilosc_wierzcholkow, gestosc); //tworzy obiekt odpowiedniego typu
                int w_startowy = rand() % ilosc_wierzcholkow; //wierzcholek startowy wybierany w sposob losowy z powstalych

                graph->wypelnij_graf(false); //fill graph with ilosc_petli possibility

                sum += bellmanFord(std::move(graph), w_startowy, false); //zwraca czas poszczegolnego wykonania i dodaje go do sumy ogolnej
                std::cout << (ipetla * 100 / ilosc_petli) + 1 << "%" << "\r" << std::flush; //ile % zostalo juz zrobione
        }
            file << sum / ilosc_petli << " "; //zapisuje srednia pomiarow do pliku
            std::cout << ilosc_wierzcholkow << " wierzcholkow gotowych!" << std::endl;
        }
        std::cout << "\n"<<"Gestosc " << gestosc << " gotowa!\n" << std::endl;
    }
    file << "\n";
    return file;
}


int main() {

    srand(static_cast<unsigned int>(time(NULL)));

    bool test_spr = false; // WYBIERZ czy ma wykonac sie test do sprawozdania czy mniejsze testy do sprawdzania dzialania programu
                            //true- sprawozdanie, false- testy dzialanosci


    // TEST do sprawozdania //

    //wykonuje test potrzebny do sprawozdania
    // 5 roznych ilosci wierzcholkow
    // 4 rozna gestosci grafu
    // 100 powtorzen

    if (test_spr) {

        /////////////////////////

        int tab_ilosc_wierzcholkow[5] = {20, 40, 60, 80, 100}; //ilosc wierzcholkow grafu
        double tab_gestosc[4] = {0.25, 0.5, 0.75, 1}; //gestosc grafu
        int ilosc_petli = 100;		// ilosc powtorzen
        /////////////////////////

        std::ofstream file("OutputTimes.txt");
        if (!file.is_open()) {

            std::cerr << "Plik nie zostal otworzony poprawnie!" << std::flush;
            return 1;
        }

        tests<ListGraph>(file, tab_ilosc_wierzcholkow, tab_gestosc, ilosc_petli); //wykonanie testu dla listy sasiedztwa
        std::cout << "Lista gotowa\n" << std::endl;
        tests<MatrixGraph>(file, tab_ilosc_wierzcholkow, tab_gestosc, ilosc_petli);	// wykonanie testu dla macierzy sasiedztwa
        std::cout << "Macierz gotowa" << std::endl;

        file.close();
        std::cin.get();
        return 0;
    }


    // Testy//

    //czytanie z pliku
    //mozliwosc wprowadzenia petli
    //ustawianie parametrow grafu recznie
    //wybor reprezentacji grafu: macierza lub lista sasiedztwa
    /////////////////////////
    typedef	MatrixGraph AktualnaReprezentacja;   // reprezentacja macierzy sasiedztwa
   // typedef	ListGraph AktualnaReprezentacja; // reprezentacja lsty sasiedztwa
    bool czy_z_pliku = false;	       //mozliwosc wyboru czy wczytac graf z pliku czy wylosowac (Input.txt)
    bool czy_petle = true;	           //umozliwia dodanie petli
    int ilosc_wierzcholkow = 9;		   //ilosc wierzcholkow
    double gestosc = 0.75;	               //gestosc grafu
    int w_startowy = 1;		           //wybor wierzcholka startowego
    /////////////////////////

    std::shared_ptr<AktualnaReprezentacja> graf;

    if (czy_z_pliku) { //jesli wybrano wczytywanie grafu z pliku
        std::shared_ptr<AktualnaReprezentacja> tmp = std::make_shared<AktualnaReprezentacja>();
        graf = tmp;
        try {
            w_startowy = tmp->czytaj_z_pliku();
        }
        catch (const char* msg) {
            std::cerr << msg << std::flush;
            return 1;
        }
    }
    else { //jesli wybrano opcje wypelnienia grafu losowo
        std::shared_ptr<AktualnaReprezentacja> tmp = std::make_shared<AktualnaReprezentacja>(ilosc_wierzcholkow, gestosc);
        graf = tmp;
        tmp->wypelnij_graf(czy_petle);
    }

    graf->wypisz_graf();
    //sprawdza czy otwarto poprawnie
    try {
        if (!czy_z_pliku) graf->stworz_plik(w_startowy);
    }
    catch(const char* msg) {
        std::cerr << msg << std::flush;
        return 1;
    }
    bellmanFord(std::move(graf), w_startowy, true);
std::cin.get();
    return 0;
}