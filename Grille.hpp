#ifndef GRILLE_HPP
#define GRILLE_HPP
#include "Tuile.hpp"

class Grille
{
private:
    vector<vector<Tuile *>> cases; // la grille est un vecteur de pointeurs sur des tuiles
    int longueur;
    int largeur;

public:
    // Constructeur
    Grille(int longueur, int largeur);

    // Getter
    vector<vector<Tuile *>> get_cases() const;
    int get_longueur() const;
    int get_largeur() const;

    // Méthodes pour poser des tuiles dans la grille
    void set_cases(Tuile *A, int ligne, int colonne);
    bool comparer(Tuile *A, int ligne, int colonne) const; // retourne True si on peut poser la tuile A à l'enplacement (ligne,colonne), sinon False
    bool ajoute_tuile(Tuile *A, int ligne, int colonne);   // Ajoute une tuile à l'emplacement (i,j) dans la grille
                                                           // retourne True si a réussi à l'ajouter, False sinon
    // Opérateur d'affichage
    friend ostream &operator<<(ostream &out, const Grille &x);

    // Destructeur
    virtual ~Grille();
};

#endif