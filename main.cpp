#include "Partie.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    cout << "Bienvenue !" << endl;
    cout << "Ici vous pouvez jouer à 2 jeux : Domino et Trax" << endl;
    cout << endl;
    cout << "Choisir le jeu :" << endl;
    cout << "1- Domino, 2- Trax :  ";

    int choixJeu{0};
    cin >> choixJeu;
    Partie *partie = Partie::creerPartie(choixJeu);
    // Maintenant partie est soit une PartieDomino soit une PartieTrax

    partie->jouer();

    cout << endl;
    cout << "Merci d'avoir joué !" << endl;

    delete partie;

    return 0;
}