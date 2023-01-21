#ifndef PARTIEDOMINO_HPP
#define PARTIEDOMINO_HPP
#include "Partie.hpp"

class PartieDomino : public Partie
{
public:
    // Hérite de Partie : le nombre de joueurs, une grille, un sac de tuile
    // Mais en plus dans Domino on tient compte d'un score
    vector<int> scores; // de taille nbJoueurs, et où score[i] contient le score actuel du joueur i

public:
    PartieDomino();                                                                   // constructeur par défaut
    void changerParametres(int &nbJoueurs, vector<int> &tailleGrille, int &nbTuiles); // fonction appelée avant de commencer une partie, pour changer nbJoueurs, taille grille, nbTuiles
    void ajoute_score(Tuile *A, int ligne, int colonne);                              // ajoute au score du joueur_actuel les points rapportés en posant la tuile A en (ligne, colonne)
    int scores_max(int nbJoueurs) const;                                              // retourne le max des points
    void gagnant() const;                                                             // décide et affiche le gagnant de la partie (dont le cas avec égalité)

    // La fonction principale qui va faire jouer une partie de Domino !
    // dedans on va retrouver la boucle principale du jeu
    virtual void jouer();

    virtual ~PartieDomino();
};

#endif