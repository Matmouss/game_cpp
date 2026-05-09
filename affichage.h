#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <string>
#include <map>
#include <vector>
#include <ncurses.h>

class Personnage;

struct GameWindow {
    WINDOW* jeu;
    int hauteur;
    int largeur;
};

WINDOW* creer_boite_jeu(int hauteur, int largeur);
void dessiner_boite_jeu(WINDOW* win, const std::vector<std::string>& state, const std::map<std::string, std::string>& data);
GameWindow init_ncurses();
void end_ncurses(WINDOW* jeu);
WINDOW* displayState(WINDOW* jeu, int hauteur, int largeur, const std::vector<std::string>& state, const std::map<std::string, std::string>& infos);
GameWindow resize_window(WINDOW* jeu, const std::vector<std::string>& state, const std::map<std::string, std::string>& infos);
std::string getInput(const std::map<int, std::string>& keymap);

void initInterface();
void fermerInterface();
void initBinds();

std::string joinLines(const std::vector<std::string>& lines);
std::string stripDescription(const std::string& option);
std::string extractDescription(const std::string& option);

void setUIMode(const std::string& mode, const std::string& title);
void setSidebarMenu(const std::string& title, const std::vector<std::string>& options, int selected);
void clearSidebarMenu();
void setCombatInventory(Personnage& personnage);
void updateInfos(Personnage& personnage);
void setCombatInfos(const std::string& header, const std::string& message, const std::string& hint);
void setCombatMessage(const std::string& message);
std::vector<std::string> creerDisplayCombat(const std::string& header, const std::string& message);

void afficher(const std::vector<std::string>& display);
void waitEnterOrQuit(const std::vector<std::string>& display);
void afficherEtAttendre(const std::vector<std::string>& display);
void afficherMessageCombat(const std::string& titre, const std::string& texte, const std::string& hint = "TARGET LOCKED");
std::string Menu(std::vector<std::string> options, std::string title);

#endif
