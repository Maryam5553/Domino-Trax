#ifndef COULEUR_HPP
#define COULEUR_HPP
#include <iostream>
using namespace std;

// Change la couleur du texte dans le terminal
// refCouleur :
// "31" : rouge
// "39" : blanc (défaut)
// "36" : cyan
// "0" : réinitialiser

// la fonction modifie un out donné en paramètre
void affiche_en_couleur(string texte, const char *refCouleur, ostream &out)
{

    printf("\033[%sm", refCouleur);
    out << texte;
    printf("\033[%sm", "0");
}
#endif