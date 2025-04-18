#include <iostream>
#include <chrono>
#include "BrtkvE18.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now(); // Początek pomiaru czasu
    BrtkvE18 SIG("1101371683409170059");

    BrtkvE18 SIGMA("1237687123768789785543432132113234213");
    BrtkvE18 SOGMA("1123768789785543490");

    std::cout << SIGMA/SOGMA << "\n";


    SIGMA /=SOGMA;


    std::cout << SIGMA << "\n";
    std::cout << SIG << "\n";



    auto end = std::chrono::high_resolution_clock::now(); // Koniec pomiaru czasu
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Czas wykonania: " << elapsed.count() << " sekund\n";

    return 0;
}
