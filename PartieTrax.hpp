#ifndef PARTIETRAX_HPP
#define PARTIETRAX_HPP
#include "Partie.hpp"

class PartieTrax : public Partie
{
public:
    // Hérite de Partie : le nombre de joueurs, une grille, un sac de tuile

public:
    // Constructeur
    PartieTrax();

    // void coupsForcés(); // joue les coups forcés

    // Fonctions intermédiaires pour boucle et ligne

    vector<int> coteContact(Tuile *A, int ligne, int colonne) const;                                                                          // Retourne le(s) côté(s) qui a matché après avoir posé une tuile
    int cote_oppose(int cote) const;                                                                                                          // Retourne le côté opposé d'où on vient (ex: cote_opposé(gauche) = droite)
    Tuile *prochaine_case(int direction, int &ligne, int &colonne, int &ligne_min, int &ligne_max, int &colonne_min, int &colonne_max) const; // Retourne les coordonées de la prochaine case
    int prochaine_direction(Tuile *A, int origine, int couleur) const;                                                                        // Retourne quel autre côté (que l'origine) de la tuile est de la couleur voulue

    // Regarde si, après avoir posé la tuile A en (ligne, colonne),
    // s'il y a une boucle ou une ligne de la couleur voulue
    bool parcours(Tuile *A, int ligne, int colonne, int couleur) const;
    // bool ligne(int couleur) const;

    // La fonction principale qui va faire jouer une partie de Trax !
    // dedans on va retrouver la boucle principale du jeu
    virtual void jouer();

    void TEST();
    // Destructeur
    virtual ~PartieTrax();
};

#endif