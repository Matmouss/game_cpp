#include <iostream>
#include "affichage.h"
#include "csv.h"

using namespace std;

int main() {
    //test();


    auto data = readCSV("data/monstres.csv");
    
    for (const auto& row : data) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    return 0;

    
}
