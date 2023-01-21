#include "TuileTrax.hpp"
#include "Couleur.hpp" // Pour afficher en couleur dans le terminal

// Constructeur qui prend en entrée un paramètre pour savoir si on crée un recto ou un verso
TuileTrax::TuileTrax(int parametre)
{
    if (parametre == 1) // 1 : recto(intersection)
    {
        vector<vector<int>> cote{{1}, {2}, {1}, {2}};
        this->cote = cote;
    }

    if (parametre == 2) // 2 : verso(parallèle)
    {
        vector<vector<int>> cote{{1}, {1}, {2}, {2}};
        this->cote = cote;
    }
}

bool TuileTrax::cote_egaux(int i, Tuile *A, int j) const
{
    return (this->cote[i][0] == A->get_cote()[j][0]);
}

// Affiche la i-ème ligne de la tuile
// On l'utilise dans la surcharge de << de Tuile et de Grille
// Ne retourne rien mais modifie le out de Tuile ou de Grille
void TuileTrax::affiche_ligne(int i, ostream &out) const
{
    vector<const char *> coul; // 4 couleurs pour les 4 cotes

    // choix des couleurs selon les côtés
    for (int i{0}; i < 4; i++)
    {
        if (cote[i][0] == 1) // rouge : "31"
            coul.push_back("31");
        if (cote[i][0] == 2) // blanc : "39"
            coul.push_back("39");
    }
    // affiche la ligne
    if (i == 0 || i == 1)
        affiche_en_couleur("  #  ", coul[0], out);
    if (i == 2)
    {
        affiche_en_couleur("##", coul[3], out);

        if (cote[0][0] == cote[1][0] || cote[0][0] == cote[3][0]) // si on est en parallèle, on laisse un espace au milieu
            cout << " ";
        if (cote[0][0] == cote[2][0]) // si on est en intersection, on met une étoile au milieu
            affiche_en_couleur("#", coul[0], out);

        affiche_en_couleur("##", coul[1], out);
    }
    if (i == 3 || i == 4)
        affiche_en_couleur("  #  ", coul[2], out);
}

void TuileTrax::inverse_cote(int i) {}