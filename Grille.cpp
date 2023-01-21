#include "Grille.hpp"

// Constructeur
Grille::Grille(int longueur, int largeur)
{
    vector<vector<Tuile *>> x(longueur, vector<Tuile *>(largeur, nullptr)); // on prévoit long*larg nombre de cases dans notre vector
    this->cases = x;
    this->longueur = longueur;
    this->largeur = largeur;
}

// Destructeur
Grille::~Grille() {}

// Getter
int Grille::get_longueur() const { return longueur; }
int Grille::get_largeur() const { return largeur; }
vector<vector<Tuile *>> Grille::get_cases() const { return cases; }

// Opérateur d'affichage
ostream &operator<<(ostream &out, const Grille &x)
{
    for (int j{0}; j < x.largeur; j++) // la ligne horizontale du haut (autant qu'il y a de colonnes)
        out << "......";
    out << ".";
    out << endl;
    for (int i{0}; i < x.longueur; i++) // on parcoure les lignes
    {
        for (int k{0}; k < 5; k++) // le nombre de lignes *du terminal* dont on a besoin pour faire une ligne de la grille
        {
            out << ".";                        // côté gauche de la grille
            for (int j{0}; j < x.largeur; j++) // on parcoure les colonnes
            {
                if (x.cases[i][j] == nullptr) // si pas de tuile à afficher
                    out << "     .";
                else // si y'a une tuile à afficher
                {
                    x.cases[i][j]->affiche_ligne(k, out); // on affiche la tuile ligne par ligne
                    out << ".";
                }
            }
            out << endl; // on est arrivé au bord droit, on passe à la sous-ligne suivante
        }
        for (int j{0}; j < x.largeur; j++) // les lignes horizontales entre les lignes
            out << "......";
        out << ".";
        out << endl;
    }
    return out;
}

// Méthode pour poser la première tuile au milieu
void Grille::set_cases(Tuile *A, int ligne, int colonne)
{
    cases[ligne][colonne] = A;
}

// Cette fonction compare la tuile piochée avec les tuiles posées autour
// Si elle trouve des cotés qui sont similaires elle renvoie True
// Si on essaye de la poser dans une case où y a pas un contact avec une tuile,
// ou si les côtés des tuiles autour ne matchent pas, renvoie False
bool Grille::comparer(Tuile *A, int ligne, int colonne) const
{
    bool contact{0};          // vérifie s'il y a contact avec d'autres tuiles
    if (ligne < longueur - 1) // Si on est pas dans la dernière ligne
    {
        // On regarde la case (ligne+1,colonne)
        if (cases[ligne + 1][colonne] != nullptr) // Vérifier si la case est voisine de tuile *A
        {
            contact = 1;
            if (not cases[ligne + 1][colonne]->cote_egaux(0, A, 2)) // si le côté haut de case[n] = côté bas de A
            {
                cout << "Erreur; coté Bas match pas" << endl;
                return false;
            }
        }
    }

    if (ligne > 0) // Si on est pas sur la première ligne
    {
        // On regarde la case (ligne-1,colonne)
        if (cases[ligne - 1][colonne] != nullptr) // Vérifier si la case est voisine de tuile *A
        {
            contact = 1;
            if (not cases[ligne - 1][colonne]->cote_egaux(2, A, 0))
            {
                cout << "Erreur; coté Haut match pas" << endl;
                return false;
            }
        }
    }

    if (colonne < largeur - 1) // Si on est pas dans la dernière colonne
    {
        // On regarde la case (ligne,colonne+1)
        if (cases[ligne][colonne + 1] != nullptr) // Vérifier si la case n est voisin de tuile *A
        {
            contact = 1;
            if (not cases[ligne][colonne + 1]->cote_egaux(3, A, 1))
            {
                cout << "Erreur; coté droit match pas" << endl;
                return false;
            }
        }
    }
    if (colonne > 0) // Si on est pas dans la première colonne
    {
        // On regarde la case (ligne,colonne-1)
        if (cases[ligne][colonne - 1] != nullptr) // Vérifier si la case n est voisin de tuile *A
        {
            contact = 1;
            if (not cases[ligne][colonne - 1]->cote_egaux(1, A, 3))
            {
                cout << "Erreur; coté gauche match pas" << endl;
                return false;
            }
        }
    }
    if (not contact) // Si contact égale à 0
    {
        cout << "Erreur; il faut être en contact avec une tuile" << endl;
        return false;
    }

    return true;
}

// Cette méthode : ajouter une tuile dans la grille à l'emplacement (ligne,colonne)
// retourne -1 si n'a pas réussi à l'ajouter, sinon retourne les points apportés par cet ajout
bool Grille::ajoute_tuile(Tuile *A, int ligne, int colonne)
{
    // Verification des conditions
    if (0 > ligne || ligne >= longueur || 0 > colonne || colonne >= largeur) // vérif pas dépassement
    {
        cout << "ERREUR : la case (" << ligne + 1 << ", " << colonne + 1 << ") n'existe pas." << endl;
        return false;
    }
    if (cases[ligne][colonne] != nullptr) // vérif emplacement vide
    {
        cout << "ERREUR: on ne peut pas ajouter de tuile à cet endroit, il y en a déjà une." << endl;
        return false;
    }
    // On appelle la fonction comparer et on vérifie si elle ne retourne pas false
    // c'est à dire les conditions sur les tuiles voisines sont satisfaites
    if (comparer(A, ligne, colonne))
    {
        // si la comparaison a réussi, on ajoute la tuile
        cases[ligne][colonne] = A;
        return true; // Le même retour que la fonction comparer
    }
    return false;
}
