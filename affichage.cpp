#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ncurses.h>

// pour le reset terminal
// Source - https://stackoverflow.com/a/52895729


using namespace std;

string ajouter_sucre(string texte){
    return "--------------------------------\n" + texte + "\n-------------------------------- ";
}


void afficher_jeu(string texte){
    texte = ajouter_sucre(texte);
    cout<< u8"\033[2J\033[1;1H"; 
    cout << texte << endl;
}

void verifier_input(){
    int ch;

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    ch = getch();
    cout << ch << '\n';
    ch = getch();
    cout << ch << '\n';
    ch = getch();
    cout << ch << '\n';


    refresh();
    getch();
    endwin();
}


int boucle() {
    cout<< u8"\033[2J\033[1;1H"; 


    cout << "C'est l'heure du compteur" << endl;

    for (int i = 5; i>0; i--) {
        this_thread::sleep_for(chrono::seconds(1));
        afficher_jeu(to_string(i));
    }  


    cout<< u8"\033[2J\033[1;1H"; 
    return 0;
}

int test(){
    //boucle();
    verifier_input();
    return 0;
}