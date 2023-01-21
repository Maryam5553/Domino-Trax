#ifndef TUILE_DOMINO_HPP
#define TUILE_DOMINO_HPP
#include "Tuile.hpp"

class TuileDomino : public Tuile
{
    // Hérite de la classe Tuile : attribut cote (vect <vect <int> >)
    // cote contient 4 côtés de 3 entiers
public:
    // Constructeur qui génère aléatoirement les côtés de 3 chiffres
    TuileDomino();

    // Comparer le côté i de la tuile actuelle avec le côté j d'une deuxième tuile A
    virtual bool cote_egaux(int i, Tuile *A, int j) const;

    // Afficher la i-ème ligne de la tuile (on en a besoin pour afficher dans la grille)
    void affiche_ligne(int i, ostream &out) const;

    // Méthode intermédiaire pour tourner
    void inverse_cote(int i);

    // Hérite de la classe Tuile : afficher et le getter de cote
};

#endif