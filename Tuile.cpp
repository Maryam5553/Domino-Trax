#include "Tuile.hpp"

// Destructeur
Tuile::~Tuile() {}

// Getter
vector<vector<int>> Tuile::get_cote() const { return cote; }

// Opérateur d'affichage (utilise affiche_ligne)
ostream &operator<<(ostream &out, const Tuile &x)
{
    for (int i{0}; i < 5; i++)
    {
        x.affiche_ligne(i, out);
        out << endl;
    }
    return out;
}

// Méthode tournerDroite : dans le sens des aiguilles d'une montre
void Tuile::tournerDroite()
{
    inverse_cote(1);
    inverse_cote(3);
    // on permute juste les côtés
    vector<int> temp;
    temp = cote[0];
    cote[0] = cote[3];
    cote[3] = cote[2];
    cote[2] = cote[1];
    cote[1] = temp;
    // cout << "j'ai tourné" << endl;
}

// Méthode tournerGauche : dans le sens inverse des aiguilles d'une montre
void Tuile::tournerGauche()
{
    inverse_cote(0);
    inverse_cote(2);
    vector<int> temp;
    temp = cote[0];
    cote[0] = cote[1];
    cote[1] = cote[2];
    cote[2] = cote[3];
    cote[3] = temp;
    // cout << "j'ai tourné" << endl;
}