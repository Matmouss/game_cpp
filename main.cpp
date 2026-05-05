#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "affichage.h"
#include "monstre.h"
#include "partie.h"
#include "personnage.h"
#include "csv.h"
#include "act.h"
#include "entite.h"
#include "item.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;

struct ResultatTourJoueur {
    bool pass;
    bool bypass;
    bool actionEffectuee;
    string message;
};

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

vector<string> getOptionsRemplacementAct(Personnage& personnage, Act* nouvelleAction) {
    vector<string> options;

    for (int i = 0; i < personnage.getNbActions(); i++) {
        Act* action = personnage.getActions(i);

        if (action == nullptr) {
            options.push_back("Emplacement vide : prendre " + nouvelleAction->identifiant);
        } else {
            options.push_back(action->identifiant + " : remplacer par " + nouvelleAction->identifiant);
        }
    }

    options.push_back("Refuser : ne pas prendre " + nouvelleAction->identifiant);
    return options;
}

vector<string> getOptionsRemplacementItem(Personnage& personnage, Item* nouvelItem) {
    vector<string> options;

    for (int i = 0; i < personnage.getTailleInventaire(); i++) {
        Item* item = personnage.getInventaireItems(i);

        if (item == nullptr) {
            options.push_back("Emplacement vide : prendre " + nouvelItem->getNom());
        } else {
            options.push_back(item->getNom() + " : remplacer par " + nouvelItem->getNom());
        }
    }

    options.push_back("Refuser : ne pas prendre " + nouvelItem->getNom());
    return options;
}

Monstre* getMonstreCombat(Partie& partie_en_cours) {
    if (partie_en_cours.tailleBestiaire == 4 || partie_en_cours.tailleBestiaire == 8) return partie_en_cours.randomMonstre("mini");
    if (partie_en_cours.tailleBestiaire == 9) return partie_en_cours.randomMonstre("boss");
    return partie_en_cours.randomMonstre("lambda");
}

bool VictoireCondition(Personnage& personnage) {
    if (personnage.getHp() <= 0 || personnage.getMercy() >= personnage.getMercyGoal()) return false;
    return true;
}

bool combatEnCours(Monstre& monstre, Personnage& personnage) {
    if (monstre.getHp() <= 0 || monstre.getMercy() >= monstre.getMercyGoal() || personnage.getHp() <= 0 || personnage.getMercy() >= personnage.getMercyGoal()) return false;
    return true;
}

int getIndexActionChoisie(Personnage& personnage, const vector<string>& options, const string& choix) {
    for (int i = 0; i < personnage.getNbActions(); i++) {
        if (i < static_cast<int>(options.size()) && options[i] == choix && choix != "") return i;
    }

    return -1;
}

int getIndexItemChoisi(Personnage& personnage, const vector<string>& options, const string& choix) {
    for (int i = 0; i < personnage.getTailleInventaire(); i++) {
        if (i < static_cast<int>(options.size()) && options[i] == choix) return i;
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

ResultatTourJoueur executerActJoueur(Monstre& monstre, Personnage& personnage, const vector<string>& options, const string& choix) {
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

ResultatTourJoueur executerItemJoueur(Personnage& personnage, const vector<string>& options, const string& choix) {
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

bool placerActionLibre(Personnage& personnage, Act* nouvelleAction) {
    for (int i = 0; i < personnage.getNbActions(); i++) {
        if (personnage.getActions(i) == nullptr) {
            personnage.setAction(nouvelleAction, i);
            return true;
        }
    }

    return false;
}

bool placerItemLibre(Personnage& personnage, Item* nouvelItem) {
    for (int i = 0; i < personnage.getTailleInventaire(); i++) {
        if (personnage.getInventaireItems(i) == nullptr) {
            personnage.setInventaireItems(nouvelItem, i);
            return true;
        }
    }

    return false;
}

void donnerAction(Personnage& personnage, Act* nouvelleAction) {
    if (nouvelleAction == nullptr) return;

    afficherMessageCombat("RECOMPENSE", "Vous avez gagne la competence : " + nouvelleAction->identifiant);

    if (placerActionLibre(personnage, nouvelleAction)) {
        afficherMessageCombat("RECOMPENSE", nouvelleAction->identifiant + " ajoutee aux competences");
        return;
    }

    setCombatInfos("NOUVELLE COMPETENCE", "Choisissez une competence a remplacer", "TARGET LOCKED");

    vector<string> options = getOptionsRemplacementAct(personnage, nouvelleAction);
    string choix = Menu(options, "NOUVELLE COMPETENCE");

    if (choix != "quit" && stripDescription(choix) != "Refuser") {
        for (int i = 0; i < personnage.getNbActions(); i++) {
            if (options[i] == choix) {
                personnage.setAction(nouvelleAction, i);
                afficherMessageCombat("RECOMPENSE", nouvelleAction->identifiant + " equipee");
                return;
            }
        }
    }

    afficherMessageCombat("RECOMPENSE", nouvelleAction->identifiant + " refusee");
}

void donnerItem(Personnage& personnage, Item* nouvelItem) {
    if (nouvelItem == nullptr) return;

    afficherMessageCombat("RECOMPENSE", "Vous avez gagne l'objet : " + nouvelItem->getNom());

    if (placerItemLibre(personnage, nouvelItem)) {
        afficherMessageCombat("RECOMPENSE", nouvelItem->getNom() + " ajoute a l'inventaire");
        return;
    }

    setCombatInfos("NOUVEL OBJET", "Choisissez un objet a remplacer", "TARGET LOCKED");

    vector<string> options = getOptionsRemplacementItem(personnage, nouvelItem);
    string choix = Menu(options, "NOUVEL OBJET");

    if (choix != "quit" && stripDescription(choix) != "Refuser") {
        for (int i = 0; i < personnage.getTailleInventaire(); i++) {
            if (options[i] == choix) {
                personnage.setInventaireItems(nouvelItem, i);
                afficherMessageCombat("RECOMPENSE", nouvelItem->getNom() + " equipe");
                return;
            }
        }
    }

    afficherMessageCombat("RECOMPENSE", nouvelItem->getNom() + " refuse");
}

void donnerRecompenses(Personnage& personnage, Act* nouvelleAction, Item* nouvelItem) {
    donnerAction(personnage, nouvelleAction);
    donnerItem(personnage, nouvelItem);
    updateInfos(personnage);
}

void appliquerVictoireCombat(Partie& partie_en_cours, Monstre* monstre) {
    partie_en_cours.ajouterBestiaire(monstre);
    partie_en_cours.personnage->destructionStats();
    partie_en_cours.personnage->setNbTue();
    partie_en_cours.personnage->setAllStatsUp(5);
}

string choisirCommandeJoueur() {
    return Menu(getActionMenu(), "COMMANDS");
}

string choisirActJoueur(Personnage& personnage, vector<string>& options) {
    options = getActionsOptions(personnage);
    setCombatMessage("Selectionnez une competence.");
    return Menu(options, "SKILLS");
}

string choisirItemJoueur(Personnage& personnage, vector<string>& options) {
    options = getItemsOptions(personnage);
    setCombatMessage("Selectionnez un objet.");
    return Menu(options, "ITEMS");
}

void afficherDebutCombat(Monstre& monstre) {
    vector<string> display = creerDisplayCombat(getCombatHeader(monstre), monstre.getDialogues(0));
    setCombatInfos(display[0], display[1], "SCAN TARGET");
    afficherEtAttendre(display);
}

void afficherDialogueCombat(Monstre& monstre, vector<string>& display) {
    display[0] = getCombatHeader(monstre);
    display[1] = monstre.getDialogues(rand() % (monstre.getTailleDialogues() - 1));
    display[2] = "Appuyer sur entree pour continuer";

    setCombatInfos(display[0], display[1], "TARGET RESPONSE");
    setSidebarMenu("COMMANDS", getCombatSidebarMenu(), 0);
    afficherEtAttendre(display);
}

void afficherFinCombat(Monstre& monstre, Personnage& personnage, bool victoire, vector<string>& display) {
    display[0] = getCombatHeader(monstre);
    display[1] = monstre.getDialogues(monstre.getTailleDialogues() - 1);
    display[2] = "Appuyer sur entree pour continuer";

    setCombatInfos(display[0], display[1], victoire ? "TARGET NEUTRALIZED" : "PLAYER OFFLINE");
    afficherEtAttendre(display);

    display = {
        "FIN COMBAT",
        monstre.getNom() + " | HP " + to_string(monstre.getHp()) + " | MERCY " + to_string(monstre.getMercy())
    };

    if (victoire) {
        if (monstre.getHp() <= 0) {
            display.push_back("Vous rangez le cadavre de monstre dans votre sac et poursuivez votre chemin...");
        } else {
            display.push_back("Le monstre vous donne son numéro de téléphone et s'en va en souriant.");
        }

        display.push_back("Vous sentez une force se reveiller en vous! HP,ATK,DEF + 5");
        display.push_back("Appuyer sur entree pour continuer");
    }

    updateInfos(personnage);
    setCombatInfos(display[0], display[1], victoire ? "TARGET NEUTRALIZED" : "PLAYER OFFLINE");
    afficherEtAttendre(display);
}

bool FightJoueur(Monstre& monstre, Personnage& personnage) {
    vector<string> display;
    vector<string> options;
    ResultatTourJoueur resultat = nouveauResultatTourJoueur();

    setCombatInfos(getCombatHeader(monstre), "Selectionnez une commande dans la console gauche.", "TARGET LOCKED");

    string choix = choisirCommandeJoueur();

    if (choix == "quit") return false;

    string choixCourt = stripDescription(choix);
    string headerAvantAction = getCombatHeader(monstre);

    if (choixCourt == "Act") {
        choix = choisirActJoueur(personnage, options);
        resultat = executerActJoueur(monstre, personnage, options, choix);
    } else if (choixCourt == "Item") {
        choix = choisirItemJoueur(personnage, options);
        resultat = executerItemJoueur(personnage, options, choix);
    } else if (choixCourt == "Pass") {
        resultat = executerPassJoueur();
    }

    updateInfos(personnage);
    setCombatInventory(personnage);
    setSidebarMenu("COMMANDS", getActionMenu(), -1);

    if (resultat.actionEffectuee) {
        display = creerDisplayCombat(headerAvantAction, resultat.message);
        setCombatInfos(display[0], display[1], "TARGET LOCKED");
        afficher(display);
    }

    if (!resultat.bypass && !display.empty()) waitEnterOrQuit(display);

    clearSidebarMenu();
    return resultat.pass;
}

void FightMonstre(Monstre& monstre, Personnage& personnage) {
    vector<string> display = {""};

    int index_action = rand() % monstre.getNbActions();

    display.push_back(monstre.utiliserAct(index_action, personnage));
    display[0] = getCombatHeaderAct(monstre);
    display.push_back("Appuyer sur entree pour continuer");

    setCombatInfos(display[0], display[1], "HOSTILE PROCESS RUNNING");
    setSidebarMenu("COMMANDS", getCombatSidebarMenu(), -1);
    updateInfos(personnage);
    afficherEtAttendre(display);
}

bool Fight(Partie& partie_en_cours, Monstre& monstre, Personnage& personnage) {
    bool combatEnCours_b = true;
    bool victoire = false;

    setCombatInfos(getCombatHeader(monstre), "", "SCAN TARGET");
    setCombatInventory(personnage);
    setSidebarMenu("COMMANDS", getCombatSidebarMenu(), 0);

    afficherDebutCombat(monstre);

    vector<string> display = {
        getCombatHeader(monstre),
        monstre.getDialogues(0),
        "Appuyer sur entree pour continuer"
    };

    while (combatEnCours_b) {
        while (!FightJoueur(monstre, personnage) && combatEnCours(monstre, personnage) && personnage.getAct() > 0) {}

        combatEnCours_b = combatEnCours(monstre, personnage);
        personnage.EndTurn();

        if (combatEnCours_b) afficherDialogueCombat(monstre, display);

        while (combatEnCours_b && monstre.getAct() > 0) FightMonstre(monstre, personnage);

        combatEnCours_b = combatEnCours(monstre, personnage);
        monstre.EndTurn();
    }

    victoire = VictoireCondition(personnage);

    afficherFinCombat(monstre, personnage, victoire, display);
    donnerRecompenses(personnage, partie_en_cours.randomACT(), partie_en_cours.randomItem());

    setUIMode("menu", "MENU");
    clearSidebarMenu();

    return victoire;
}

bool ouvrirBestiaire(Partie& partie_en_cours) {
    setUIMode("menu", "BESTIAIRE");

    string choix = Menu(getBestiaireOptions(partie_en_cours), "BESTIAIRE");

    if (choix == "quit") return false;
    return true;
}

bool ouvrirInventaire(Partie& partie_en_cours) {
    setUIMode("menu", "INVENTAIRE");

    string choix = Menu(getInventaireOptions(*partie_en_cours.personnage), "INVENTAIRE");

    if (choix == "quit") return false;
    return true;
}

void afficherGameOver() {
    clearSidebarMenu();
    afficherMessageCombat("GAME OVER", "Vous etes un nul", "PLAYER OFFLINE");
    setUIMode("menu", "MENU");
    clearSidebarMenu();
}

void afficherVictoireJeu() {
    clearSidebarMenu();
    setCombatInfos("VICTOIRE", "yay tu as tabassé le boss", "SYSTEM CLEARED");

    vector<string> display = {
        "VICTOIRE",
        "Vous avez gagne ALTERDUNE",
        "Appuyer sur entree pour continuer"
    };

    afficherEtAttendre(display);

    setUIMode("menu", "MENU");
    clearSidebarMenu();
}

bool lancerCombat(Partie& partie_en_cours) {
    Monstre* monstre = getMonstreCombat(partie_en_cours);

    if (Fight(partie_en_cours, *monstre, *partie_en_cours.personnage)) {
        appliquerVictoireCombat(partie_en_cours, monstre);
        updateInfos(*partie_en_cours.personnage);

        if (partie_en_cours.personnage->getNbTue() >= 10) {
            afficherVictoireJeu();
            return false;
        }

        return true;
    }

    afficherGameOver();
    return false;
}

bool menuAccueil() {
    setUIMode("menu", "ALTERDUNE");

    vector<string> options = {
        "Commencer une partie : lancer une nouvelle partie",
        "Quitter : quitter le jeu"
    };

    string choix = Menu(options, "ALTERDUNE");
    string choixCourt = stripDescription(choix);

    if (choix == "quit" || choixCourt == "Quitter") return false;
    return true;
}

void game() {
    Partie partie_en_cours = Partie();

    updateInfos(*partie_en_cours.personnage);

    bool running = true;

    while (running) {
        setUIMode("menu", "MAIN MENU");

        string choix = Menu(getMenuPrincipalOptions(), "MAIN MENU");
        string choixCourt = stripDescription(choix);

        if (choix == "quit" || choixCourt == "Quit") {
            running = false;
        } else if (choixCourt == "Bestiaire") {
            running = ouvrirBestiaire(partie_en_cours);
        } else if (choixCourt == "Fight") {
            running = lancerCombat(partie_en_cours);
        } else if (choixCourt == "Inventaire") {
            running = ouvrirInventaire(partie_en_cours);
        }
    }
}

int main() {
    initInterface();
    initBinds();

    if (menuAccueil()) game();

    fermerInterface();

    cout << "c'etait bien non ?" << endl;
}
