#ifndef TUILETRAX_HPP
#define TUILETRAX_HPP
#include "Tuile.hpp"

class TuileTrax : public Tuile
{
private:
    // Hérite de la classe Tuile : attribut cote (vect <vect <int> >)
    // cote contient 4 côtés de 1 entier, représentant la couleur : 1 pour rouge, 2 pour blanc

    // parametre : 1 pour recto (tuile "intersection"), 2 verso ("parallèle")
    int parametre;

public:
    // Constructeur qui prend en entrée un paramètre pour savoir si on crée un recto ou un verso
    TuileTrax(int parametre = 1);

    // Comparer le côté i de la tuile actuelle avec le côté j d'une deuxième tuile A
    virtual bool cote_egaux(int i, Tuile *A, int j) const;

    // Afficher la i-ème ligne de la tuile (on en a besoin pour afficher dans la grille)
    // Méthode virtuelle
    virtual void affiche_ligne(int i, ostream &out) const;

    // Méthode intermédiaire pour tourner, mais ne fait rien
    virtual void inverse_cote(int i);

    // Hérite de la classe Tuile : les méthodes pour tourner, afficher et le getter de cote
};

#endif
