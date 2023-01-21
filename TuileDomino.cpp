#include "TuileDomino.hpp"
#include <cstdlib> // pour rand()
#include <time.h>  // pour initialiser rand()

// Constructeur qui génère aléatoirement les côtés de 3 chiffres
TuileDomino::TuileDomino()
{
    // génération random des cotés
    for (int j{0}; j < 4; j++)
    {
        vector<int> cote_i;
        for (int i{0}; i < 4; i++)
        {
            cote_i.push_back(rand() % 3); // on push un chiffre aléatoire entre 0 et 2
        }
        cote.push_back(cote_i); // on ajoute le côté créé à l'attribut "cote"
    }
}

// Comparer le côté i de la tuile actuelle avec le côté j d'une deuxième tuile A
bool TuileDomino::cote_egaux(int i, Tuile *A, int j) const
{
    return (this->cote[i][0] == A->get_cote()[j][0] && this->cote[i][1] == A->get_cote()[j][1] && this->cote[i][2] == A->get_cote()[j][2]);
}

// Affiche la i-ème ligne de la tuile
// On l'utilise dans la surcharge de << de Tuile et de Grille
// Ne retourne rien mais modifie le out de Tuile ou de Grille
void TuileDomino::affiche_ligne(int i, ostream &out) const
{
    if (i == 0) // première ligne
    {
        // on affiche le côté du haut
        out << " ";
        for (int j{0}; j < 3; j++)
        {
            out << cote[0][j];
        }
        out << " ";
    }
    if (i == 1 || i == 2 || i == 3) // lignes du milieu
    {
        // on affiche verticalement les côtés droit et gauche
        out << cote[3][i - 1]; // i-1 car on affiche le 1er caractère sur la 2-ème ligne
        out << "   ";
        out << cote[1][i - 1];
    }
    if (i == 4) // dernière ligne
    {
        // on affiche le côté du bas
        out << " ";
        for (int j{0}; j < 3; j++)
        {
            out << cote[2][j];
        }
        out << " ";
    }
}

// Méthode inverse : qui permute la valeur de la position 0 et la position 2
// chose qui est importante lors d'utiliser la fonction inverseDroite et inverseGauche
void TuileDomino::inverse_cote(int i)
{
    int tmp;
    tmp = cote[i][0];
    cote[i][0] = cote[i][2];
    cote[i][2] = tmp;
}