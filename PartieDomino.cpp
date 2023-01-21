#include "PartieDomino.hpp"

// Constructeur
PartieDomino::PartieDomino() : Partie() // commence par initialiser une partie par défaut
{
    srand(time(0)); // initialisation de rand()
    cout << "Bienvenue dans une partie de Domino !" << endl;
    cout << endl;

    // Paramètres par défaut pour initialiser nbJoueurs, sac et grille
    int nbJoueurs = 2;
    vector<int> tailleGrille = {5, 5};
    int nbTuiles = 10;

    // Possibilité de changer les paramètres
    changerParametres(nbJoueurs, tailleGrille, nbTuiles);

    // Construction d'une PartieDomino
    this->nbJoueurs = nbJoueurs;
    this->grille = new Grille{tailleGrille[0], tailleGrille[1]};
    this->sac = new Sac{nbTuiles + 1, "domino"}; // sac de taille nbTuiles + 1 (+1 pour la première tuile posée dans la grille)
                                                 // on demande à le remplir de tuiles de Domino
    vector<int> scores(nbJoueurs, 0);            // initialise un vecteur de taille nbJoueurs rempli de 0
    this->scores = scores;
}

// Destructeur
PartieDomino::~PartieDomino() {}

// Changement des paramètres pour initialiser une partie
void PartieDomino::changerParametres(int &nbJoueurs, vector<int> &tailleGrille, int &nbTuiles)
{
    int parametre{1}; // on initialise à "je veux changer les paramètres" pour rentrer dans la boucle
    while (parametre != 2)
    {
        cout << "***PARAMETRES :" << endl; // on affiche les paramètres actuels
        cout << "-nombre de joueurs : " << nbJoueurs << endl;
        cout << "-taille de la grille : " << tailleGrille[0] << "x" << tailleGrille[1] << endl;
        cout << "-nombre de tuiles dans le sac de départ : " << nbTuiles << endl;
        cout << endl
             << "Voulez-vous changer les paramètres de jeu ?" << endl
             << "1-changer les paramètres 2-commencer une partie :  ";
        cin >> parametre;
        // si on rentre un 2, on sort de la boucle
        if (parametre != 1 && parametre != 2) // erreur
        {
            cout << "Valeur erronée, veuillez réessayer" << endl;
        }
        if (parametre == 1) // si on veut changer les paramètres
        {
            cout << endl
                 << "nombre de joueurs : ";
            cin >> nbJoueurs;
            // Gestion d'erreur : on va demander un string pour vérifier s'il rentre pas quelque chose comme "2x2"
            string long_temp;
            cout << "longueur de la grille : ";
            cin >> long_temp;
            while (long_temp.length() > 2) // cas de figure "2x2" (on peut supposer qu'on ne demande jamais de grille de taille 100)
            {
                cout << endl;
                cout << "Erreur : on demande juste la longeur de la grille" << endl;
                cout << "longueur de la grille : ";
                cin >> long_temp;
            }
            tailleGrille[0] = stoi(long_temp); // conversion en int
            cout << "largeur de la grille : ";
            cin >> tailleGrille[1];
            cout << "nombre de tuiles dans le sac de départ : ";
            cin >> nbTuiles;
            cout << endl;
        }
    }
}

// Ajoute au score du joueur_actuel les points rapportés en posant la tuile A en (ligne, colonne)
void PartieDomino::ajoute_score(Tuile *A, int ligne, int colonne)
{
    int score = 0;
    int longueur = grille->get_longueur();
    int largeur = grille->get_largeur();

    // Même principe que la fonction comparer : on regarde ce qu'il y a autour
    if (ligne < longueur - 1) // Si on est pas dans la dernière ligne
    {
        if (grille->get_cases()[ligne + 1][colonne] != nullptr) // Vérifier si la case (i+1,j) est voisine de tuile *A
        {
            score += A->get_cote()[2][0] + A->get_cote()[2][2] + A->get_cote()[2][1];
        }
    }
    if (ligne > 0) // Si on est pas sur la première ligne
    {
        // On regarde la case (ligne-1,colonne)
        if (grille->get_cases()[ligne - 1][colonne] != nullptr) // Vérifier si la case (i-1,j) est voisine de tuile *A
        {
            score += A->get_cote()[0][0] + A->get_cote()[0][2] + A->get_cote()[0][1];
        }
    }
    if (colonne < largeur - 1) // Si on est pas dans la dernière colonne
    {
        // On regarde la case (ligne,colonne+1)
        if (grille->get_cases()[ligne][colonne + 1] != nullptr) // Vérifier si la case (i,j+1) est voisine de tuile *A
        {
            score += A->get_cote()[1][0] + A->get_cote()[1][2] + A->get_cote()[1][1];
        }
    }
    if (colonne > 0) // Si on est pas dans la première colonne
    {
        // On regarde la case (ligne,colonne-1)
        if (grille->get_cases()[ligne][colonne - 1] != nullptr) // Vérifier si la case (i,j-1) est voisine de tuile *A
        {
            score += A->get_cote()[3][0] + A->get_cote()[3][2] + A->get_cote()[3][1];
        }
    }

    scores[joueur_actuel] += score;
}

// Trouve le max des scores
int PartieDomino::scores_max(int nbJoueurs) const
{
    int score_max{0};
    for (int i{0}; i < nbJoueurs; i++)
    {
        if (scores[i] > score_max)
            score_max = scores[i];
    }
    return score_max;
}

// Décide du gagnant
void PartieDomino::gagnant() const
{
    vector<int> liste_gagnant;
    int score_max = scores_max(nbJoueurs);
    for (int i{0}; i < nbJoueurs; i++)
    {
        if (scores[i] == score_max)
            liste_gagnant.push_back(i); // trouver tous les joueurs qui ont atteint ce score
    }

    if (liste_gagnant.size() == 1)
    {
        cout << "le gagnant est le joueur " << liste_gagnant[0] + 1 << " avec " << score_max << " points" << endl;
    }
    else
    {
        cout << "égalité entre les joueurs ";
        for (long unsigned int i{0}; i < liste_gagnant.size() - 1; i++)
        {
            cout << liste_gagnant[i] + 1 << ",";
        }
        cout << " et " << liste_gagnant[liste_gagnant.size() - 1] + 1;
        cout << " avec " << score_max << " points" << endl;
    }
    cout << "Le score final de la partie est : ";
    for (int i{0}; i < nbJoueurs - 1; i++)
    {
        cout << "joueur " << i + 1 << " : " << scores[i] << " ; ";
    }
    cout << "joueur " << nbJoueurs << " : " << scores[nbJoueurs - 1] << endl;
}

// Joue une partie
void PartieDomino::jouer()
{
    // Générer la première tuile au centre de la grille
    Tuile *A;
    A = sac->pioche_tuile();
    grille->set_cases(A, grille->get_longueur() / 2, grille->get_largeur() / 2);

    while (not sac->estVide()) // la condition d'arrêt du jeu est quand on a fini de parcourir le sac
    {
        Tuile *tuile;
        tuile = sac->pioche_tuile(); // on pioche une tuile
        cout << *grille;
        int parametre = 0;
        cout << "nombre de tuiles restant : " << sac->get_nbTuiles() - sac->get_tuileCourante() << endl;
        cout << "scores actuels : ";
        for (int i{0}; i < nbJoueurs - 1; i++)
        {
            cout << "joueur " << i + 1 << " : " << scores[i] << " ; ";
        }
        cout << "joueur " << nbJoueurs << " : " << scores[nbJoueurs - 1] << endl;
        cout << "C'est le tour du joueur " << joueur_actuel + 1 << endl;
        cout << "Voici votre tuile :" << endl;
        while (parametre != 4) // 4 veut dire "la jeter" mais on va aussi mettre 4 si on arrive à la poser
        {
            cout << *tuile;
            cout << "1-la tourner à droite 2- la tourner à gauche 3-la poser 4-la jeter :  ";
            cin >> parametre;
            if (parametre != 1 && parametre != 2 && parametre != 3 && parametre != 4) // erreur
                cout << "Valeur erronée, veuillez réessayer" << endl;
            if (parametre == 1)
                tuile->tournerDroite();
            if (parametre == 2)
                tuile->tournerGauche();
            if (parametre == 3)
            {
                int ligne;
                int colonne;
                cout << "où voulez-vous la poser ?" << endl;
                cout << "ligne : ";
                cin >> ligne;
                ligne -= 1; // On a soustrait -1 pour que ça paraît plus naturel au joueur de commencer à 1 au lieu de 0
                cout << "colonne : ";
                cin >> colonne;
                colonne -= 1;

                if (grille->ajoute_tuile(tuile, ligne, colonne))
                {
                    ajoute_score(tuile, ligne, colonne);
                    parametre = 4; // on sort de la boucle
                }
            }
        }
        joueur_actuel = (joueur_actuel + 1) % nbJoueurs; // on passe au joueur suivant (modulo nb de joueurs)
    }
    cout << *grille;
    // La partie est finie
    cout << "La partie est finie" << endl;
    cout << "Vous n'avez plus de tuile dans le sac" << endl;

    // Calcul du gagnant
    scores_max(nbJoueurs);
    gagnant();
}