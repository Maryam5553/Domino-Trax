#ifndef TUILE_HPP
#define TUILE_HPP
#include <iostream>
#include <vector>
using namespace std;

class Tuile
{
protected:
    // Vector de taille 4 qui va contenir les 4 côtés, eux-même des vectors d'int
    vector<vector<int>> cote;

public:
    // Constructeur spécifique à chacune des tuiles

    // Destructeur
    virtual ~Tuile();
    // Getter
    vector<vector<int>> get_cote() const;
    // Opérateur d'affichage (fait appel à affiche_ligne)
    friend ostream &operator<<(ostream &out, const Tuile &x);

    // Comparer le côté i de la tuile actuelle avec le côté j d'une deuxième tuile A
    virtual bool cote_egaux(int i, Tuile *A, int j) const = 0;

    // Afficher la i-ème ligne de la tuile (on en a besoin pour afficher dans la grille)
    // Méthode virtuelle ("virtual" + "= 0") car elle est définie différemment selon Domino/Trax
    virtual void affiche_ligne(int i, ostream &out) const = 0;

    // Méthode intermédiaire pour tourner
    virtual void inverse_cote(int i) = 0;

    // Méthodes tourner
    void tournerDroite();
    void tournerGauche();
};

#endif