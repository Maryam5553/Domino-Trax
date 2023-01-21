#ifndef PARTIE_HPP
#define PARTIE_HPP
#include "Grille.hpp"
#include "Sac.hpp"

// "Factory method" (méthode de fabrication) :
// - contient les éléments de base d'une partie
// - son rôle est de fabriquer : soit une partie de domino, soit une partie de trax
//   grâce à la fonction creerPartie

class Partie
{
public:
    // Une partie se compose : d'un nombre de joueurs, d'une grille, d'un sac de tuile
    int nbJoueurs;
    Grille *grille;
    Sac *sac;
    int joueur_actuel; // on stocke quel joueur est en train de jouer

public:
    Partie(); // Constructeur par défaut

    // En appelant la fonction creerPartie, on choisit si on veut une partie de domino ou de trax
    static Partie *creerPartie(int parametre); // 1: domino, 2: trax

    // La fonction principale qui va faire jouer une partie !
    // dedans on va retrouver la boucle principale du jeu, qui va être différente selon le type de jeu
    // méthode virtuelle
    virtual void jouer() = 0;

    virtual ~Partie();
};

#endif