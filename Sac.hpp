#ifndef SAC_HPP
#define SAC_HPP
#include "TuileDomino.hpp"
#include "TuileTrax.hpp"

class Sac
{
private:
    // Le nombre de tuile dans le sac
    const int nbTuiles;
    // Pointeur vers la tuile
    vector<Tuile *> const tuile;
    // La tuile qu'on est en train de jouer (compteur)
    int tuile_courante;

public:
    // Constructeur de Sac
    Sac(const int nbTuiles, string typeTuile);                                  // on demande avec quel type de Tuile on doit remplir le sac
    vector<Tuile *> const initialiserSac(const int nbTuiles, string typeTuile); // fonction intermédiaire pour initialiser le sac

    // Getter
    vector<Tuile *> get_tuile() const;
    const int get_nbTuiles() const;
    int get_tuileCourante() const;

    // Piocher une tuile : c'est juste get_tuile mais qui incrémente le compteur tuile_courante
    Tuile *pioche_tuile();
    // Renvoie si le sac est vide
    bool estVide() const;

    // Destructeur
    virtual ~Sac();
};

#endif