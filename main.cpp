#include <string>
#include <map>
#include <vector>
#include <utility>
#include <ncurses.h>
#include "affichage.h"
#include "monstre.h"
#include "partie.h"
#include "personnage.h"
#include "csv.h"
#include "act.h"
#include "entite.h"
#include "item.h"
#include <iostream>
#include <cstdlib>

using std::endl;
using std::cout;
using std::map;
using std::string;
using std::to_string;
using std::vector;

map<int, string> keymap;
map<string, string> infos;

struct ResultatTourJoueur {
    bool pass;
    bool bypass;
    bool actionEffectuee;
    string message;
};

// ====================
// OUTILS TEXTE
// ====================

string joinLines(const vector<string>& lines) {
    string result;

    for (size_t i = 0; i < lines.size(); ++i) {
        result += lines[i];
        if (i + 1 < lines.size()) result += "\n";
    }

    return result;
}

string stripDescription(const string& option) {
    size_t pos = option.find(" : ");
    if (pos == string::npos) pos = option.find(" | ");
    if (pos == string::npos) return option;

    return option.substr(0, pos);
}

string extractDescription(const string& option) {
    size_t pos = option.find(" : ");
    if (pos == string::npos) pos = option.find(" | ");
    if (pos == string::npos) return option;

    return option.substr(pos + 3);
}

// ====================
// LOGIQUE DE DONNEES
// ====================

string getCombatHeader(Monstre& monstre) {
    return monstre.getNom() + " | HP " + to_string(monstre.getHp()) + " | MERCY " + to_string(monstre.getMercy()) + "%";
}

string getCombatHeaderAct(Monstre& monstre) {
    return getCombatHeader(monstre) + " | ACT " + to_string(monstre.getAct());
}

vector<string> getActionMenu() {
    return {
        "Act : executer une competence",
        "Item : ouvrir les objets utilisables",
        "Pass : terminer le tour"
    };
}

vector<string> getCombatSidebarMenu() {
    return {
        "Act",
        "Item",
        "Pass"
    };
}

vector<string> getMenuPrincipalOptions() {
    return {
        "Fight : lancer un combat",
        "Bestiaire : consulter les monstres vaincus",
        "Inventaire : consulter les objets",
        "Quit : quitter le jeu"
    };
}

vector<string> getActionsOptions(Personnage& personnage) {
    vector<string> options;

    for (int i = 0; i < personnage.getNbActions(); i++) {
        if (personnage.getActions(i) != nullptr) {
            options.push_back(personnage.getActions(i)->identifiant + " : " + personnage.getActions(i)->texte);
        } else {
            options.push_back("nullAction");
        }
    }

    options.push_back("Retour : revenir aux commandes");
    return options;
}

vector<string> getItemsOptions(Personnage& personnage) {
    vector<string> options;

    for (int i = 0; i < personnage.getTailleInventaire(); i++) {
        if (personnage.getInventaireItems(i) == nullptr) {
            options.push_back("emplacment vide");
        } else {
            options.push_back(personnage.getInventaireItems(i)->getNom() + " : " + personnage.getInventaireItems(i)->getTexte());
        }
    }

    options.push_back("Retour : revenir aux commandes");
    return options;
}

vector<string> getBestiaireOptions(Partie& partie_en_cours) {
    vector<string> options;

    if (partie_en_cours.tailleBestiaire == 0) {
        options.push_back("Aucun monstre : aucun monstre vaincu pour le moment");
    } else {
        for (int i = 0; i < partie_en_cours.tailleBestiaire; i++) {
            options.push_back(
                partie_en_cours.bestiaire[i]->getNom() +
                " : ATK " + to_string(partie_en_cours.bestiaire[i]->getAtk()) +
                " | DEF " + to_string(partie_en_cours.bestiaire[i]->getDef()) +
                " | HP " + to_string(partie_en_cours.bestiaire[i]->getHpMax()) +
                " | Mercy Goal " + to_string(partie_en_cours.bestiaire[i]->getMercyGoal()) +
                " | " + partie_en_cours.bestiaire[i]->getDescription()
            );
        }
    }

    options.push_back("Retour : revenir au menu principal");
    return options;
}

vector<string> getInventaireOptions(Personnage& personnage) {
    vector<string> options;

    if (personnage.getTailleInventaire() == 0) {
        options.push_back("Vide : aucun objet disponible");
    } else {
        for (int i = 0; i < personnage.getTailleInventaire(); i++) {
            Item* item = personnage.getInventaireItems(i);

            if (item == nullptr) {
                options.push_back("emplacement vide");
            } else {
                options.push_back(item->getNom() + " : " + item->getTexte());
            }
        }
    }

    options.push_back("Retour : revenir au menu principal");
    return options;
}

Monstre* getMonstreCombat(Partie& partie_en_cours) {
    if (partie_en_cours.tailleBestiaire == 5) {
        return partie_en_cours.randomMonstre("mini");
    }

    if (partie_en_cours.tailleBestiaire == 10) {
        return partie_en_cours.randomMonstre("boss");
    }

    return partie_en_cours.randomMonstre("lambda");
}

bool VictoireCondition(Personnage& personnage) {
    if (personnage.getHp() <= 0) return false;
    return true;
}

bool combatEnCours(Monstre& monstre, Personnage& personnage) {
    if (monstre.getHp() <= 0 || monstre.getMercy() >= monstre.getMercyGoal() || personnage.getHp() <= 0) {
        return false;
    }

    return true;
}

int getIndexActionChoisie(Personnage& personnage, const vector<string>& options, const string& choix) {
    for (int i = 0; i < personnage.getNbActions(); i++) {
        if (i < static_cast<int>(options.size()) && options[i] == choix && choix != "") {
            return i;
        }
    }

    return -1;
}

int getIndexItemChoisi(Personnage& personnage, const vector<string>& options, const string& choix) {
    for (int i = 0; i < personnage.getTailleInventaire(); i++) {
        if (i < static_cast<int>(options.size()) && options[i] == choix) {
            return i;
        }
    }

    return -1;
}

ResultatTourJoueur nouveauResultatTourJoueur() {
    ResultatTourJoueur resultat;

    resultat.pass = false;
    resultat.bypass = false;
    resultat.actionEffectuee = false;
    resultat.message = "";

    return resultat;
}

// ====================
// LOGIQUE DE JEU
// ====================

ResultatTourJoueur executerActJoueur(
    Monstre& monstre,
    Personnage& personnage,
    const vector<string>& options,
    const string& choix
) {
    ResultatTourJoueur resultat = nouveauResultatTourJoueur();

    if (choix == "quit" || stripDescription(choix) == "Retour") {
        resultat.bypass = true;
        return resultat;
    }

    int index = getIndexActionChoisie(personnage, options, choix);

    if (index != -1) {
        resultat.message = personnage.utiliserAct(index, monstre);
        resultat.actionEffectuee = true;
    }

    return resultat;
}

ResultatTourJoueur executerItemJoueur(
    Personnage& personnage,
    const vector<string>& options,
    const string& choix
) {
    ResultatTourJoueur resultat = nouveauResultatTourJoueur();

    if (choix == "quit" || stripDescription(choix) == "Retour" || choix == "emplacment vide") {
        resultat.bypass = true;
        return resultat;
    }

    int index = getIndexItemChoisi(personnage, options, choix);

    if (index != -1) {
        resultat.message = personnage.utiliserItem(index);
        resultat.actionEffectuee = true;
    }

    return resultat;
}

ResultatTourJoueur executerPassJoueur() {
    ResultatTourJoueur resultat = nouveauResultatTourJoueur();

    resultat.pass = true;
    resultat.actionEffectuee = true;
    resultat.message = "Vous passez votre tour";

    return resultat;
}

void appliquerVictoireCombat(Partie& partie_en_cours, Monstre* monstre) {
    partie_en_cours.ajouterBestiaire(monstre);
    partie_en_cours.personnage->destructionStats();
    partie_en_cours.personnage->setNbTue();
}

// ====================
// ETAT AFFICHAGE
// ====================

void setUIMode(map<string, string>& infos, const string& mode, const string& title) {
    infos["__mode"] = mode;
    infos["__title"] = title;
}

void setSidebarMenu(map<string, string>& infos, const string& title, const vector<string>& options, int selected) {
    vector<string> labels;

    for (const string& option : options) {
        labels.push_back(stripDescription(option));
    }

    infos["__sidebar_menu_title"] = title;
    infos["__sidebar_menu_items"] = joinLines(labels);
    infos["__sidebar_menu_selected"] = to_string(selected);

    if (selected >= 0 && selected < static_cast<int>(options.size())) {
        infos["__selection_detail"] = extractDescription(options[selected]);
    } else {
        infos["__selection_detail"] = "";
    }
}

void clearSidebarMenu(map<string, string>& infos) {
    infos["__sidebar_menu_title"] = "";
    infos["__sidebar_menu_items"] = "";
    infos["__sidebar_menu_selected"] = "-1";
    infos["__selection_detail"] = "";
}

void setCombatInventory(Personnage& personnage, map<string, string>& infos) {
    vector<string> lignes;

    for (int i = 0; i < personnage.getTailleInventaire(); ++i) {
        Item* item = personnage.getInventaireItems(i);

        if (item == nullptr) {
            lignes.push_back("- vide");
        } else {
            lignes.push_back("- " + item->getNom());
        }
    }

    if (lignes.empty()) lignes.push_back("Inventaire vide");

    infos["__inventory_items"] = joinLines(lignes);
}

void updateInfos(Personnage& personnage, map<string, string>& infos) {
    infos["Nom"] = personnage.getNom();
    infos["Monstres tués"] = to_string(personnage.getNbTue());
    infos["Hp"] = to_string(personnage.getHp());
    infos["Atk"] = to_string(personnage.getAtk());
    infos["Def"] = to_string(personnage.getDef());
    infos["Mercy"] = to_string(personnage.getMercy());
    infos["ActPts"] = to_string(personnage.getAct());

    vector<string> statsLines;

    for (int i = 0; i < personnage.getNbStats(); i++) {
        string nom = personnage.getStats(i)->getNom();
        statsLines.push_back(nom + ": " + to_string(personnage.getStatValue(nom)));
    }

    infos["Stats"] = statsLines.empty() ? "-" : joinLines(statsLines);

    setCombatInventory(personnage, infos);
}

void setCombatInfos(map<string, string>& infos, const string& header, const string& message, const string& hint) {
    infos["__mode"] = "combat";
    infos["__title"] = "COMBAT MODE";
    infos["__combat_header"] = header;
    infos["__combat_message"] = message;
    infos["__monster_hint"] = hint;
}

void setCombatInfosDepuisMonstre(Monstre& monstre, map<string, string>& infos, const string& message, const string& hint) {
    setCombatInfos(infos, getCombatHeader(monstre), message, hint);
}

vector<string> creerDisplayCombat(const string& header, const string& message) {
    return {
        header,
        message,
        "Appuyer sur entree pour continuer"
    };
}


void afficher(GameWindow& gw, map<string, string>& infos, const vector<string>& display) {
    gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);
}

void waitEnterOrQuit(GameWindow& gw, map<int, string>& keymap, map<string, string>& infos, const vector<string>& display) {
    string input = getInput(keymap);

    while (input != "enter" && input != "quit") {
        if (input == "resize") {
            gw = resize_window(gw.jeu, display, infos);
        }

        input = getInput(keymap);
    }
}

void afficherEtAttendre(GameWindow& gw, map<int, string>& keymap, map<string, string>& infos, const vector<string>& display) {
    afficher(gw, infos, display);
    waitEnterOrQuit(gw, keymap, infos, display);
}

string Menu(
    GameWindow& gw,
    map<int, string>& keymap,
    map<string, string>& infos,
    vector<string>& options,
    string& title
) {
    if (options.empty()) return "";

    bool choisi = false;
    int choix = 0;
    vector<string> display;
    bool combatContext = (infos["__mode"] == "combat");

    if (!combatContext) {
        setUIMode(infos, "menu", title);
    } else {
        infos["__title"] = "COMBAT MODE";
    }

    while (!choisi) {
        display.clear();

        if (combatContext) {
            display.push_back(infos.count("__combat_header") ? infos["__combat_header"] : "TARGET UNKNOWN");
            display.push_back(infos.count("__combat_message") ? infos["__combat_message"] : "Choisissez une commande.");
        } else {
            display.push_back("ROOT@RPG:~$ " + title);
        }

        setSidebarMenu(infos, title, options, choix);
        afficher(gw, infos, display);

        string input = getInput(keymap);

        if (input == "quit") {
            clearSidebarMenu(infos);
            return "quit";
        } else if (input == "resize") {
            gw = resize_window(gw.jeu, display, infos);
        } else if (input == "up" || input == "left") {
            choix = (choix - 1 + static_cast<int>(options.size())) % static_cast<int>(options.size());
        } else if (input == "down" || input == "right") {
            choix = (choix + 1) % static_cast<int>(options.size());
        } else if (input == "enter") {
            choisi = true;
        }
    }

    string selected = options[choix];
    clearSidebarMenu(infos);

    return selected;
}

string choisirCommandeJoueur(GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    vector<string> actionMenu = getActionMenu();
    string title = "COMMANDS";

    return Menu(gw, keymap, infos, actionMenu, title);
}

string choisirActJoueur(
    Personnage& personnage,
    GameWindow& gw,
    map<int, string>& keymap,
    map<string, string>& infos,
    vector<string>& options
) {
    options = getActionsOptions(personnage);

    infos["__combat_message"] = "Selectionnez une competence.";

    string title = "SKILLS";
    return Menu(gw, keymap, infos, options, title);
}

string choisirItemJoueur(
    Personnage& personnage,
    GameWindow& gw,
    map<int, string>& keymap,
    map<string, string>& infos,
    vector<string>& options
) {
    options = getItemsOptions(personnage);

    infos["__combat_message"] = "Selectionnez un objet.";

    string title = "ITEMS";
    return Menu(gw, keymap, infos, options, title);
}

void afficherDebutCombat(Monstre& monstre, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    vector<string> display = creerDisplayCombat(getCombatHeader(monstre), monstre.getDialogues(0));

    infos["__combat_header"] = display[0];
    infos["__combat_message"] = display[1];

    afficherEtAttendre(gw, keymap, infos, display);
}

void afficherDialogueCombat(Monstre& monstre, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos, vector<string>& display) {
    display[0] = getCombatHeader(monstre);
    display[1] = monstre.getDialogues(rand() % (monstre.getTailleDialogues() - 1));
    display[2] = "Appuyer sur entree pour continuer";

    infos["__combat_header"] = display[0];
    infos["__combat_message"] = display[1];
    infos["__monster_hint"] = "TARGET RESPONSE";

    setSidebarMenu(infos, "COMMANDS", getCombatSidebarMenu(), 0);
    afficherEtAttendre(gw, keymap, infos, display);
}

void afficherFinCombat(
    Monstre& monstre,
    Personnage& personnage,
    bool victoire,
    GameWindow& gw,
    map<int, string>& keymap,
    map<string, string>& infos,
    vector<string>& display
) {
    display[0] = getCombatHeader(monstre);
    display[1] = monstre.getDialogues(monstre.getTailleDialogues() - 1);
    display[2] = "Appuyer sur entree pour continuer";

    infos["__combat_header"] = display[0];
    infos["__combat_message"] = display[1];
    infos["__monster_hint"] = victoire ? "TARGET NEUTRALIZED" : "PLAYER OFFLINE";

    afficherEtAttendre(gw, keymap, infos, display);

    display = {
        "FIN COMBAT",
        monstre.getNom() + " | HP " + to_string(monstre.getHp()) + " | MERCY " + to_string(monstre.getMercy()),
        "Appuyer sur entree pour continuer"
    };

    infos["__combat_header"] = display[0];
    infos["__combat_message"] = display[1];

    updateInfos(personnage, infos);
    afficherEtAttendre(gw, keymap, infos, display);
}


bool FightJoueur(Monstre& monstre, Personnage& personnage, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    vector<string> display;
    vector<string> options;
    ResultatTourJoueur resultat = nouveauResultatTourJoueur();

    setCombatInfosDepuisMonstre(monstre, infos, "Selectionnez une commande dans la console gauche.", "TARGET LOCKED");

    string choix = choisirCommandeJoueur(gw, keymap, infos);

    if (choix == "quit") return false;

    string choixCourt = stripDescription(choix);
    string headerAvantAction = getCombatHeader(monstre);

    if (choixCourt == "Act") {
        choix = choisirActJoueur(personnage, gw, keymap, infos, options);
        resultat = executerActJoueur(monstre, personnage, options, choix);
    } else if (choixCourt == "Item") {
        choix = choisirItemJoueur(personnage, gw, keymap, infos, options);
        resultat = executerItemJoueur(personnage, options, choix);
    } else if (choixCourt == "Pass") {
        resultat = executerPassJoueur();
    }

    updateInfos(personnage, infos);
    setCombatInventory(personnage, infos);
    setSidebarMenu(infos, "COMMANDS", getActionMenu(), -1);

    if (resultat.actionEffectuee) {
        display = creerDisplayCombat(headerAvantAction, resultat.message);
        setCombatInfos(infos, display[0], display[1], "TARGET LOCKED");
        afficher(gw, infos, display);
    }

    if (!resultat.bypass && !display.empty()) {
        waitEnterOrQuit(gw, keymap, infos, display);
    }

    clearSidebarMenu(infos);

    return resultat.pass;
}

void FightMonstre(Monstre& monstre, Personnage& personnage, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    vector<string> display = {""};

    int index_action = rand() % monstre.getNbActions();

    display.push_back(monstre.utiliserAct(index_action, personnage));
    display[0] = getCombatHeaderAct(monstre);
    display.push_back("Appuyer sur entree pour continuer");

    infos["__mode"] = "combat";
    infos["__title"] = "COMBAT MODE";
    infos["__combat_header"] = display[0];
    infos["__combat_message"] = display[1];
    infos["__monster_hint"] = "HOSTILE PROCESS RUNNING";

    setSidebarMenu(infos, "COMMANDS", getCombatSidebarMenu(), -1);
    updateInfos(personnage, infos);

    afficherEtAttendre(gw, keymap, infos, display);
}

bool Fight(Monstre monstre, Personnage& personnage, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    bool combatEnCours_b = true;
    bool victoire = false;

    infos["__mode"] = "combat";
    infos["__title"] = "COMBAT MODE";
    infos["__monster_hint"] = "SCAN TARGET";
    //infos["__monster_sprite"] = "aaaaaaaaaa";

    setCombatInventory(personnage, infos);
    setSidebarMenu(infos, "COMMANDS", getCombatSidebarMenu(), 0);

    afficherDebutCombat(monstre, gw, keymap, infos);

    vector<string> display = {
        getCombatHeader(monstre),
        monstre.getDialogues(0),
        "Appuyer sur entree pour continuer"
    };

    while (combatEnCours_b) {
        while (!FightJoueur(monstre, personnage, gw, keymap, infos) && combatEnCours(monstre, personnage) && personnage.getAct() > 0) {}

        combatEnCours_b = combatEnCours(monstre, personnage);
        personnage.EndTurn();

        if (combatEnCours_b) {
            afficherDialogueCombat(monstre, gw, keymap, infos, display);
        }

        while (combatEnCours_b && monstre.getAct() > 0) {
            FightMonstre(monstre, personnage, gw, keymap, infos);
        }

        combatEnCours_b = combatEnCours(monstre, personnage);
        monstre.EndTurn();
    }

    victoire = VictoireCondition(personnage);

    afficherFinCombat(monstre, personnage, victoire, gw, keymap, infos, display);

    infos["__mode"] = "menu";
    infos["__title"] = "MENU";
    clearSidebarMenu(infos);

    return victoire;
}


void initBinds() {
    keymap = {
        {KEY_UP, "up"},
        {KEY_DOWN, "down"},
        {KEY_LEFT, "left"},
        {KEY_RIGHT, "right"},
        {'z', "up"},
        {'Z', "up"},
        {'w', "up"},
        {'W', "up"},
        {'s', "down"},
        {'S', "down"},
        {'q', "quit"},
        {'Q', "quit"},
        {27, "quit"},
        {10, "enter"},
        {KEY_ENTER, "enter"}
    };

    infos = {
        {"Nom", "Personnage"},
        {"Monstres tués", "0"},
        {"Hp", "0"},
        {"Atk", "0"},
        {"Def", "0"},
        {"Mercy", "0"},
        {"ActPts", "0"},
        {"Stats", "0"},
        {"__mode", "menu"},
        {"__title", "MENU"},
        {"__sidebar_menu_title", ""},
        {"__sidebar_menu_items", ""},
        {"__sidebar_menu_selected", "-1"},
        {"__inventory_items", ""},
        {"__combat_header", ""},
        {"__combat_message", ""},
        {"__selection_detail", ""},
        {"__monster_hint", "SCAN TARGET"}
    };
}


bool ouvrirBestiaire(Partie& partie_en_cours, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    string state = "BESTIAIRE";

    setUIMode(infos, "menu", "BESTIAIRE");

    vector<string> options = getBestiaireOptions(partie_en_cours);
    string choix = Menu(gw, keymap, infos, options, state);

    if (choix == "quit") return false;
    return true;
}

bool ouvrirInventaire(Partie& partie_en_cours, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    string state = "INVENTAIRE";

    setUIMode(infos, "menu", "INVENTAIRE");

    vector<string> options = getInventaireOptions(*partie_en_cours.personnage);
    string choix = Menu(gw, keymap, infos, options, state);

    if (choix == "quit") return false;
    return true;
}

bool lancerCombat(Partie& partie_en_cours, GameWindow& gw, map<int, string>& keymap, map<string, string>& infos) {
    Monstre* monstre = getMonstreCombat(partie_en_cours);

    if (Fight(*monstre, *partie_en_cours.personnage, gw, keymap, infos)) {
        appliquerVictoireCombat(partie_en_cours, monstre);
        updateInfos(*partie_en_cours.personnage, infos);
    } else {
        
        vector<string> display = {"Vous etes un nul","Appuyer sur Enter pour Continuer"};
        afficherEtAttendre(gw, keymap, infos, display);
        return false;
    }
    return true;
}


void game() {
    string state = "menu";

    GameWindow gw = init_ncurses();

    initBinds();

    Partie partie_en_cours = Partie();

    updateInfos((*partie_en_cours.personnage), infos);

    bool running = true;

    while (running) {
        state = "MAIN MENU";

        setUIMode(infos, "menu", "MAIN MENU");

        vector<string> options = getMenuPrincipalOptions();
        string choix = Menu(gw, keymap, infos, options, state);
        string choixCourt = stripDescription(choix);

        if (choix == "quit" || choixCourt == "Quit") {
            running = false;
        } else if (choixCourt == "Bestiaire") {
            running = ouvrirBestiaire(partie_en_cours, gw, keymap, infos);
        } else if (choixCourt == "Fight") {
            state = "Fight";
            running = lancerCombat(partie_en_cours, gw, keymap, infos);
        } else if (choixCourt == "Inventaire") {
            running = ouvrirInventaire(partie_en_cours, gw, keymap, infos);
        }
    }

    end_ncurses(gw.jeu);
}

int main() {
    
    game();
    cout << "c'etait bien non ?" << endl;
}