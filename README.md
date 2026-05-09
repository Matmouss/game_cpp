# game_cpp
Bienvenue sur ce jeu Cpp basé sur une architecture POO fais exclusivement a l'aide gestion de memoire dynamique (autrement dit des pointeurs et pas de array ou vectors)

HOW TO RUN:

Sur Linux, lancer la commande "./test" et vous etes dedans! (car nous avons déja précompilé le projet)

HOW TO BUILD:

Alors ici il y a des depencies à installer avant de pouvoir run notre makefile,
on a donc besoin de gcc, make et ncurses (pour l'affichage joli)

ainsi il faudra sur linux installer quelques element pour assurer toute dependency

"
RUN apt update && apt install -y \
    gcc \
    g++ \
    make\
    libncurses5-dev
"

et finalement vous pourrez run la commande "make -B" pour recompiler tous les fichiers! 