#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <locale.h>
#include <ncurses.h>
#include "affichage.h"
#include "personnage.h"
#include "item.h"

using std::map;
using std::string;
using std::to_string;
using std::vector;

namespace {
    constexpr int PAIR_FRAME = 1;
    constexpr int PAIR_TEXT = 2;
    constexpr int PAIR_HIGHLIGHT = 3;
    constexpr int PAIR_TITLE = 4;
    constexpr int PAIR_DIM = 5;
    constexpr int PAIR_ALERT = 6;
    constexpr int PAIR_GHOST = 7;

    GameWindow gw = {nullptr, 0, 0};
    map<int, string> keymap;
    map<string, string> infos;

    string getValue(const map<string, string>& data, const string& key, const string& fallback = "") {
        auto it = data.find(key);
        return it != data.end() ? it->second : fallback;
    }

    int getIntValue(const map<string, string>& data, const string& key, int fallback = -1) {
        auto it = data.find(key);
        if (it == data.end() || it->second.empty()) return fallback;

        try {
            return std::stoi(it->second);
        } catch (...) {
            return fallback;
        }
    }

    vector<string> splitLines(const string& source) {
        vector<string> lines;
        string current;

        for (char c : source) {
            if (c == '\n') {
                lines.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }

        lines.push_back(current);

        if (lines.size() == 1 && lines[0].empty()) lines.clear();
        return lines;
    }

    string trimText(const string& text, int maxWidth) {
        if (maxWidth <= 0) return "";
        if (static_cast<int>(text.size()) <= maxWidth) return text;
        if (maxWidth <= 3) return text.substr(0, maxWidth);
        return text.substr(0, maxWidth - 3) + "...";
    }

    void printClipped(WINDOW* win, int y, int x, int width, const string& text, int attrs = 0, int pair = PAIR_TEXT) {
        if (width <= 0) return;

        string clipped = trimText(text, width);
        wattron(win, COLOR_PAIR(pair) | attrs);
        mvwprintw(win, y, x, "%s", clipped.c_str());
        wattroff(win, COLOR_PAIR(pair) | attrs);
    }

    void drawHackerBorder(WINDOW* win, int y, int x, int h, int w, const string& title, bool active = false) {
        if (h < 3 || w < 4) return;

        int borderPair = active ? PAIR_HIGHLIGHT : PAIR_FRAME;
        int titlePair = active ? PAIR_HIGHLIGHT : PAIR_TITLE;
        int attrs = active ? A_BOLD : 0;

        wattron(win, COLOR_PAIR(borderPair) | attrs);
        mvwaddch(win, y, x, ACS_ULCORNER);
        mvwaddch(win, y, x + w - 1, ACS_URCORNER);
        mvwaddch(win, y + h - 1, x, ACS_LLCORNER);
        mvwaddch(win, y + h - 1, x + w - 1, ACS_LRCORNER);

        mvwhline(win, y, x + 1, ACS_HLINE, w - 2);
        mvwhline(win, y + h - 1, x + 1, ACS_HLINE, w - 2);
        mvwvline(win, y + 1, x, ACS_VLINE, h - 2);
        mvwvline(win, y + 1, x + w - 1, ACS_VLINE, h - 2);

        mvwaddch(win, y, x + 1, '>');
        mvwaddch(win, y + h - 1, x + w - 2, '<');
        wattroff(win, COLOR_PAIR(borderPair) | attrs);

        if (!title.empty() && w > 8) {
            string label = " " + title + " ";
            printClipped(win, y, x + 3, w - 6, label, A_BOLD, titlePair);
        }
    }

    void drawScanlines(WINDOW* win, int y, int x, int h, int w) {
        wattron(win, COLOR_PAIR(PAIR_GHOST));
        for (int row = y + 1; row < y + h - 1; row += 2) {
            for (int col = x + 1; col < x + w - 1; col += 4) {
                mvwaddch(win, row, col, '.');
            }
        }
        wattroff(win, COLOR_PAIR(PAIR_GHOST));
    }

    vector<string> menuItems(const map<string, string>& data) {
        return splitLines(getValue(data, "__sidebar_menu_items", ""));
    }

    void drawTextList(WINDOW* win, int y, int x, int h, int w, const vector<string>& lines, int pair = PAIR_TEXT) {
        int maxLines = std::min(h, static_cast<int>(lines.size()));

        for (int i = 0; i < maxLines; ++i) {
            printClipped(win, y + i, x, w, lines[i], 0, pair);
        }
    }

    void drawProgress(WINDOW* win, int y, int x, int w, int value, int maxValue, const string& label) {
        if (w < 8) return;

        int labelW = std::min(6, w / 3);
        printClipped(win, y, x, labelW, label, A_BOLD, PAIR_TITLE);

        int barX = x + labelW + 1;
        int barW = w - labelW - 1;

        int filled = 0;
        if (maxValue > 0) {
            filled = (value * barW) / maxValue;
            if (filled < 0) filled = 0;
            if (filled > barW) filled = barW;
        }

        wattron(win, COLOR_PAIR(PAIR_DIM));
        for (int i = 0; i < barW; ++i) mvwaddch(win, y, barX + i, ACS_CKBOARD);
        wattroff(win, COLOR_PAIR(PAIR_DIM));

        wattron(win, COLOR_PAIR(PAIR_HIGHLIGHT) | A_BOLD);
        for (int i = 0; i < filled; ++i) mvwaddch(win, y, barX + i, ' ' | A_REVERSE);
        wattroff(win, COLOR_PAIR(PAIR_HIGHLIGHT) | A_BOLD);
    }

    vector<string> monsterPlaceholder() {
        return {
            "        _____       ",
            "       |     |      ",
            "       |_____|      ",
            "          |         ",
            "       ___|___      ",
            "      /   |    \\    ",
            "     /    |     \\   ",
            "         / \\        "
        };
    }

    void drawBootNoise(WINDOW* win, int maxY, int maxX) {
        wattron(win, COLOR_PAIR(PAIR_GHOST));
        for (int y = 1; y < maxY - 1; y += 4) {
            string line = "";
            mvwprintw(win, y, 2, "%s", trimText(line, maxX - 4).c_str());
        }
        wattroff(win, COLOR_PAIR(PAIR_GHOST));
    }

    void drawCenteredMainMenu(WINDOW* win, const vector<string>& state, const map<string, string>& data, int maxY, int maxX) {
        (void)state;
        drawBootNoise(win, maxY, maxX);

        string title = getValue(data, "__title", "MENU");
        vector<string> items = menuItems(data);
        int selected = getIntValue(data, "__sidebar_menu_selected", -1);
        string detail = getValue(data, "__selection_detail", "");

        int boxW = std::max(38, maxX / 3);
        if (boxW > maxX - 8) boxW = maxX - 8;

        int boxH = std::max(12, static_cast<int>(items.size()) + 8);
        if (boxH > maxY - 4) boxH = maxY - 4;

        int boxY = (maxY - boxH) / 2;
        int boxX = (maxX - boxW) / 2;

        drawHackerBorder(win, boxY, boxX, boxH, boxW, title, true);
        drawScanlines(win, boxY, boxX, boxH, boxW);

        printClipped(win, boxY + 2, boxX + 3, boxW - 6, "ROOT@RPG:~$ ./menu", A_BOLD, PAIR_TITLE);
        printClipped(win, boxY + 3, boxX + 3, boxW - 6, "--------------------------------", 0, PAIR_DIM);

        int startY = boxY + 5;
        for (int i = 0; i < static_cast<int>(items.size()) && startY + i < boxY + boxH - 4; ++i) {
            string line = (i == selected ? "> " : "  ") + items[i];

            if (i == selected) {
                wattron(win, COLOR_PAIR(PAIR_HIGHLIGHT) | A_BOLD);
                mvwhline(win, startY + i, boxX + 2, ' ', boxW - 4);
                mvwprintw(win, startY + i, boxX + 3, "%s", trimText(line, boxW - 6).c_str());
                wattroff(win, COLOR_PAIR(PAIR_HIGHLIGHT) | A_BOLD);
            } else {
                printClipped(win, startY + i, boxX + 3, boxW - 6, line, 0, PAIR_TEXT);
            }
        }

        int hintY = boxY + boxH - 3;
        printClipped(win, hintY, boxX + 3, boxW - 6, "FLECHES naviguer  ENTER executer  ESC/q quitter", 0, PAIR_DIM);

        if (!detail.empty()) {
            int infoW = boxW;
            int infoH = 5;
            int infoY = boxY + boxH + 1;
            int infoX = boxX;

            if (infoY + infoH < maxY - 1) {
                drawHackerBorder(win, infoY, infoX, infoH, infoW, "INFO", false);
                printClipped(win, infoY + 2, infoX + 3, infoW - 6, detail, 0, PAIR_TEXT);
            }
        }
    }

    void drawCombatActions(WINDOW* win, int y, int x, int h, int w, const map<string, string>& data) {
        drawHackerBorder(win, y, x, h, w, getValue(data, "__sidebar_menu_title", "ACTIONS"), true);

        vector<string> items = menuItems(data);
        int selected = getIntValue(data, "__sidebar_menu_selected", -1);

        if (items.empty()) items.push_back("Aucune action");

        int maxVisible = h - 4;
        int first = 0;
        if (selected >= maxVisible) first = selected - maxVisible + 1;

        for (int i = first, line = 0; i < static_cast<int>(items.size()) && line < maxVisible; ++i, ++line) {
            int yy = y + 2 + line;
            string label = (i == selected ? "> " : "  ") + items[i];

            if (i == selected) {
                wattron(win, COLOR_PAIR(PAIR_HIGHLIGHT) | A_BOLD);
                mvwhline(win, yy, x + 2, ' ', w - 4);
                mvwprintw(win, yy, x + 3, "%s", trimText(label, w - 6).c_str());
                wattroff(win, COLOR_PAIR(PAIR_HIGHLIGHT) | A_BOLD);
            } else {
                printClipped(win, yy, x + 3, w - 6, label, 0, PAIR_TEXT);
            }
        }

        printClipped(win, y + h - 2, x + 2, w - 4, "ENTER exec | q retour/quit", 0, PAIR_DIM);
    }

    void drawCombatStats(WINDOW* win, int y, int x, int h, int w, const map<string, string>& data) {
        drawHackerBorder(win, y, x, h, w, "PLAYER", false);

        string nom = getValue(data, "Nom", "Personnage");
        string hp = getValue(data, "Hp", "0");
        string atk = getValue(data, "Atk", "0");
        string def = getValue(data, "Def", "0");
        string mercy = getValue(data, "Mercy", "0");
        string actPts = getValue(data, "ActPts", "0");
        string kills = getValue(data, "Monstres tués", "0");

        printClipped(win, y + 2, x + 2, w - 4, "ID     " + nom, A_BOLD, PAIR_TITLE);
        printClipped(win, y + 4, x + 2, w - 4, "ATK    " + atk, 0, PAIR_TEXT);
        printClipped(win, y + 5, x + 2, w - 4, "DEF    " + def, 0, PAIR_TEXT);
        printClipped(win, y + 6, x + 2, w - 4, "MERCY  " + mercy, 0, PAIR_TEXT);
        printClipped(win, y + 7, x + 2, w - 4, "KILLS  " + kills, 0, PAIR_TEXT);

        int hpInt = getIntValue(data, "Hp", 0);
        int actInt = getIntValue(data, "ActPts", 0);

        drawProgress(win, y + h - 4, x + 2, w - 4, hpInt, 100, "PV");
        drawProgress(win, y + h - 3, x + 2, w - 4, actInt, 10, "ACT");
    }

    void drawCombatInventory(WINDOW* win, int y, int x, int h, int w, const map<string, string>& data) {
        drawHackerBorder(win, y, x, h, w, "INVENTORY / STATS", false);

        vector<string> items = splitLines(getValue(data, "__inventory_items", ""));
        if (items.empty()) items.push_back("Inventaire vide");

        drawTextList(win, y + 2, x + 2, h - 3, w - 4, items, PAIR_TEXT);
    }

    void drawMonsterSmall(WINDOW* win, int y, int x, int h, int w, const vector<string>& state, const map<string, string>& data) {
        drawHackerBorder(win, y, x, h, w, "TARGET", false);
        drawScanlines(win, y, x, h, w);

        string header = state.empty() ? "UNKNOWN TARGET" : state[0];
        printClipped(win, y + 1, x + 2, w - 4, header, A_BOLD, PAIR_ALERT);

        vector<string> sprite = splitLines(getValue(data, "__monster_sprite", ""));
        if (sprite.empty()) sprite = monsterPlaceholder();

        int spriteH = static_cast<int>(sprite.size());
        int spriteW = 0;

        for (const string& line : sprite) {
            spriteW = std::max(spriteW, static_cast<int>(line.size()));
        }

        int sy = y + 3 + std::max(0, (h - 5 - spriteH) / 2);
        int sx = x + 2 + std::max(0, (w - 4 - spriteW) / 2);

        for (int i = 0; i < spriteH && sy + i < y + h - 2; ++i) {
            printClipped(win, sy + i, sx, w - 4, sprite[i], A_BOLD, PAIR_TEXT);
        }

        printClipped(win, y + h - 2, x + 2, w - 4, getValue(data, "__monster_hint", "scan actif"), A_BLINK, PAIR_DIM);
    }

    void drawCombatLog(WINDOW* win, int y, int x, int h, int w, const vector<string>& state, const map<string, string>& data) {
        drawHackerBorder(win, y, x, h, w, "OUTPUT", true);

        vector<string> logs;
        if (state.size() > 1) {
            for (size_t i = 1; i < state.size(); ++i) logs.push_back("$ " + state[i]);
        }

        string detail = getValue(data, "__selection_detail", "");
        if (!detail.empty()) {
            logs.push_back("");
            logs.push_back("> " + detail);
        }

        if (logs.empty()) logs.push_back("$ attente d'instruction...");

        drawTextList(win, y + 2, x + 2, h - 4, w - 4, logs, PAIR_TEXT);

        printClipped(win, y + h - 2, x + 2, w - 4, "signal stable // interface combat", 0, PAIR_DIM);
    }

    void drawCombatLayout(WINDOW* win, const vector<string>& state, const map<string, string>& data, int maxY, int maxX) {
        drawBootNoise(win, maxY, maxX);

        int leftW = std::max(28, maxX / 4);
        if (leftW > 38) leftW = 38;

        int gap = 1;
        int leftX = 1;
        int rightX = leftX + leftW + gap;
        int rightW = maxX - rightX - 1;
        int topY = 1;
        int totalH = maxY - 2;

        int actionsH = std::max(8, totalH / 3);
        int statsH = std::max(11, totalH / 3);
        int inventoryH = totalH - actionsH - statsH - 2;
        if (inventoryH < 6) {
            inventoryH = 6;
            statsH = totalH - actionsH - inventoryH - 2;
        }

        drawCombatActions(win, topY, leftX, actionsH, leftW, data);
        drawCombatStats(win, topY + actionsH + 1, leftX, statsH, leftW, data);
        drawCombatInventory(win, topY + actionsH + statsH + 2, leftX, inventoryH, leftW, data);

        int targetH = std::max(11, totalH / 3);
        if (targetH > 15) targetH = 15;

        drawMonsterSmall(win, topY, rightX, targetH, rightW, state, data);
        drawCombatLog(win, topY + targetH + 1, rightX, totalH - targetH - 1, rightW, state, data);
    }
}

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
    if (pos == string::npos) return "";
    return option.substr(pos + 3);
}

WINDOW* creer_boite_jeu(int hauteur, int largeur) {
    int starty = (LINES - hauteur) / 2;
    int startx = (COLS - largeur) / 2;

    WINDOW* win = newwin(hauteur, largeur, starty, startx);
    keypad(win, TRUE);
    return win;
}

void dessiner_boite_jeu(WINDOW* win, const vector<string>& state, const map<string, string>& data) {
    if (win == nullptr) return;

    werase(win);
    wbkgd(win, COLOR_PAIR(PAIR_TEXT));

    int maxY = 0;
    int maxX = 0;
    getmaxyx(win, maxY, maxX);

    wattron(win, COLOR_PAIR(PAIR_FRAME) | A_BOLD);
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(PAIR_FRAME) | A_BOLD);

    string mode = getValue(data, "__mode", "menu");
    string title = getValue(data, "__title", mode == "combat" ? "COMBAT" : "MENU");

    printClipped(win, 0, 2, maxX - 4, "== " + title + " ==", A_BOLD, PAIR_TITLE);

    if (maxY < 18 || maxX < 70) {
        vector<string> warning = {
            "TERMINAL TROP PETIT",
            "Taille minimale conseillee : 70x18"
        };
        int y = std::max(2, maxY / 2 - 1);
        drawTextList(win, y, 3, maxY - 4, maxX - 6, warning, PAIR_ALERT);
        wrefresh(win);
        return;
    }

    if (mode == "combat") {
        drawCombatLayout(win, state, data, maxY, maxX);
    } else {
        drawCenteredMainMenu(win, state, data, maxY, maxX);
    }

    wrefresh(win);
}

GameWindow init_ncurses() {
    setlocale(LC_ALL, "");
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    if (has_colors()) {
        start_color();
        use_default_colors();
        init_pair(PAIR_FRAME, COLOR_GREEN, -1);
        init_pair(PAIR_TEXT, COLOR_GREEN, -1);
        init_pair(PAIR_HIGHLIGHT, COLOR_BLACK, COLOR_GREEN);
        init_pair(PAIR_TITLE, COLOR_GREEN, -1);
        init_pair(PAIR_DIM, COLOR_GREEN, -1);
        init_pair(PAIR_ALERT, COLOR_YELLOW, -1);
        init_pair(PAIR_GHOST, COLOR_GREEN, -1);
    }

    int hauteur = LINES - 2;
    int largeur = COLS - 4;

    if (hauteur < 18) hauteur = 18;
    if (largeur < 70) largeur = 70;
    if (hauteur > LINES) hauteur = LINES;
    if (largeur > COLS) largeur = COLS;

    WINDOW* jeu = creer_boite_jeu(hauteur, largeur);

    vector<string> state_vide;
    map<string, string> infos_vides;
    dessiner_boite_jeu(jeu, state_vide, infos_vides);

    return {jeu, hauteur, largeur};
}

void end_ncurses(WINDOW* jeu) {
    if (jeu != nullptr) delwin(jeu);
    endwin();
}

WINDOW* displayState(WINDOW* jeu, int hauteur, int largeur, const vector<string>& state, const map<string, string>& infos) {
    if (jeu != nullptr) delwin(jeu);

    jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu, state, infos);

    return jeu;
}

GameWindow resize_window(WINDOW* jeu, const vector<string>& state, const map<string, string>& infos) {
    if (jeu != nullptr) delwin(jeu);

    clear();
    refresh();

    int hauteur = LINES - 2;
    int largeur = COLS - 4;

    if (hauteur < 18) hauteur = 18;
    if (largeur < 70) largeur = 70;
    if (hauteur > LINES) hauteur = LINES;
    if (largeur > COLS) largeur = COLS;

    jeu = creer_boite_jeu(hauteur, largeur);
    dessiner_boite_jeu(jeu, state, infos);

    return {jeu, hauteur, largeur};
}

string getInput(const map<int, string>& keymap) {
    int ch = getch();

    if (ch == KEY_RESIZE) return "resize";

    auto it = keymap.find(ch);
    if (it != keymap.end()) return it->second;

    return std::to_string(ch);
}

void initInterface() {
    gw = init_ncurses();
}

void fermerInterface() {
    end_ncurses(gw.jeu);
    gw = {nullptr, 0, 0};
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
        {"Force", "0"},
        {"Vulnerabilite", "0"},
        {"__mode", "menu"},
        {"__title", "MENU"},
        {"__sidebar_menu_title", ""},
        {"__sidebar_menu_items", ""},
        {"__sidebar_menu_selected", "-1"},
        {"__inventory_items", ""},
        {"__combat_header", ""},
        {"__combat_message", ""},
        {"__selection_detail", ""},
        {"__monster_hint", "SCAN TARGET"},
        {"__monster_sprite", ""}
    };
}

void setUIMode(const string& mode, const string& title) {
    infos["__mode"] = mode;
    infos["__title"] = title;
}

void setSidebarMenu(const string& title, const vector<string>& options, int selected) {
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

void clearSidebarMenu() {
    infos["__sidebar_menu_title"] = "";
    infos["__sidebar_menu_items"] = "";
    infos["__sidebar_menu_selected"] = "-1";
    infos["__selection_detail"] = "";
}

void setCombatInventory(Personnage& personnage) {
    vector<string> lignes;

    lignes.push_back("[STATS]");
    for (int i = 0; i < personnage.getNbStats(); i++) {
        string nom = personnage.getStats(i)->getNom();
        lignes.push_back("- " + nom + ": " + to_string(personnage.getStatValue(nom)));
    }
    lignes.push_back("");
    lignes.push_back("[ITEMS]");

    for (int i = 0; i < personnage.getTailleInventaire(); ++i) {
        Item* item = personnage.getInventaireItems(i);

        if (item == nullptr) {
            lignes.push_back("- vide");
        } else {
            lignes.push_back("- " + item->getNom());
        }
    }

    infos["__inventory_items"] = joinLines(lignes);
}

void updateInfos(Personnage& personnage) {
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

    setCombatInventory(personnage);
}

void setCombatInfos(const string& header, const string& message, const string& hint) {
    infos["__mode"] = "combat";
    infos["__title"] = "COMBAT MODE";
    infos["__combat_header"] = header;
    infos["__combat_message"] = message;
    infos["__monster_hint"] = hint;
}

void setCombatMessage(const string& message) {
    infos["__combat_message"] = message;
}

vector<string> creerDisplayCombat(const string& header, const string& message) {
    return {
        header,
        message,
        "Appuyer sur entree pour continuer"
    };
}

void afficher(const vector<string>& display) {
    gw.jeu = displayState(gw.jeu, gw.hauteur, gw.largeur, display, infos);
}

void waitEnterOrQuit(const vector<string>& display) {
    string input = getInput(keymap);

    while (input != "enter" && input != "quit") {
        if (input == "resize") {
            gw = resize_window(gw.jeu, display, infos);
        }

        input = getInput(keymap);
    }
}

void afficherEtAttendre(const vector<string>& display) {
    afficher(display);
    waitEnterOrQuit(display);
}

void afficherMessageCombat(const string& titre, const string& texte, const string& hint) {
    setCombatInfos(titre, texte, hint);
    afficherEtAttendre(creerDisplayCombat(titre, texte));
}

string Menu(vector<string> options, string title) {
    if (options.empty()) return "";

    bool choisi = false;
    int choix = 0;
    vector<string> display;
    bool combatContext = (infos["__mode"] == "combat");

    if (!combatContext) {
        setUIMode("menu", title);
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

        setSidebarMenu(title, options, choix);
        afficher(display);

        string input = getInput(keymap);

        if (input == "quit") {
            clearSidebarMenu();
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
    clearSidebarMenu();

    return selected;
}
