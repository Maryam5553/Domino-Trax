#include "Sac.hpp"

// Constructeur
Sac::Sac(const int nbTuiles, string typeTuile) : nbTuiles{nbTuiles}, tuile{initialiserSac(nbTuiles, typeTuile)}
{
    this->tuile_courante = 0; // quand on pioche la première tuile on pioche la tuile 0
}

// Fonction séparée pour initialiser le sac
// le but est de retourner une valeur CONSTANTE après initialisation

// on a définit un vecteur de pointeur de Tuile
// Ensuite on génère nbTuiles Tuiles avec des new
// le paramètre permet de choisir quel type de tuile on met dans le sac :
// Domino ou Trax
vector<Tuile *> const Sac::initialiserSac(const int nbTuiles, string typeTuile)
{

    vector<Tuile *> sac;
    if (typeTuile == "domino")
    {
        for (int i{0}; i < nbTuiles; i++)
        {
            TuileDomino *B = new TuileDomino();
            sac.push_back(B);
        }
    }
    if (typeTuile == "trax")
    {
        for (int i{0}; i < nbTuiles; i++)
        {
            TuileTrax *B = new TuileTrax();
            sac.push_back(B);
        }
    }
    return sac;
}

// Getter
vector<Tuile *> Sac::get_tuile() const { return tuile; }
const int Sac::get_nbTuiles() const { return nbTuiles; }
int Sac::get_tuileCourante() const { return tuile_courante; }

// Piocher une tuile : c'est juste get_tuile mais qui incrémente le compteur tuile_courante

Tuile *Sac::pioche_tuile()
{
    tuile_courante++;
    return tuile[tuile_courante - 1];
}

// Retourne si le sac est vide
bool Sac::estVide() const
{
    return (nbTuiles <= tuile_courante);
}

// Destructeur : nous avons détruit les tuiles que nous avons mis dans le sac
Sac::~Sac()
{
    for (int i{0}; i < nbTuiles; i++)
    {
        delete tuile[i];
    }
}
