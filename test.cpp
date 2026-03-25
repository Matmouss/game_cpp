#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// pour le reset terminal
// Source - https://stackoverflow.com/a/52895729


using namespace std;

string ajouter_sucre(string texte){
    return "--------------------------------\n" + texte + "\n-------------------------------- ";
}


void afficher_jeu(string texte){
    cout<< u8"\033[2J\033[1;1H"; 
    cout << texte << endl;
}

int boucle() {
    cout<< u8"\033[2J\033[1;1H"; 


    cout << "C'est l'heure du compteur" << endl;

    for (int i = 5; i>0; i--) {
        this_thread::sleep_for(chrono::seconds(1));
        afficher_jeu(ajouter_sucre(to_string(i)));
    }  


    cout<< u8"\033[2J\033[1;1H"; 
    return 0;
}