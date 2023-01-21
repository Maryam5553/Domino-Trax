#include "Partie.hpp"
#include "PartieDomino.hpp"
#include "PartieTrax.hpp"

// Constructeur par défaut
Partie::Partie()
{
    joueur_actuel = 0;
}

// Destructeur
Partie::~Partie()
{
    delete grille;
    delete sac;
}

// En appelant la fonction creerPartie, on choisit si on veut une partie de domino ou de trax
// On crée et renvoie au choix : soit une PartieDomino soit une PartieTrax
// 1: domino, 2: trax
Partie *Partie::creerPartie(int parametre)
{
    if (parametre == 1)
        return new PartieDomino();
    if (parametre == 2)
        return new PartieTrax();
    // erreur
    cout << "Erreur; rentrez 1 ou 2" << endl;
    return nullptr;
}