#include "PartieTrax.hpp"

// Constructeur
PartieTrax::PartieTrax() : Partie()
{
    cout << "Bienvenue dans une partie de Trax !" << endl;
    cout << endl;
    nbJoueurs = 2;
    this->grille = new Grille{8, 8};
    this->sac = new Sac{64, "trax"}; // on demande à remplir le sac de 64 tuiles de trax
}

// Destructeur
PartieTrax::~PartieTrax() {}

// La fonction principale qui va faire jouer une partie de Trax !
// dedans on va retrouver la boucle principale du jeu
void PartieTrax::TEST()
{
    // on pose une tuile au milieu
    Tuile *A;
    A = sac->pioche_tuile();
    grille->set_cases(A, grille->get_longueur() / 2, grille->get_largeur() / 2);

    bool gagner = false;
    while ((not sac->estVide()) && (not gagner))
    {
        // on propose de poser une tuile
        Tuile *tuile;
        tuile = sac->pioche_tuile(); // on pioche une tuile

        cout << *grille;
        int parametre = 0;
        while (parametre != 4)
        {
            cout << *(tuile);
            cout << "1-la tourner à droite 2- la tourner à gauche 3-la poser 4-la jeter :  ";
            cin >> parametre;
            if (parametre != 1 && parametre != 2 && parametre != 3 && parametre != 4) // erreur
            {
                cout << "Valeur erronée, veuillez réessayer" << endl;
            }
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
                ligne -= 1;
                cout << "colonne : ";
                cin >> colonne;
                colonne -= 1;

                int resultat;
                resultat = grille->ajoute_tuile(tuile, ligne, colonne);
                if (resultat != -1)
                {
                    parametre = 4;
                }
            }
        }
        cout << *grille;

        // cout << B;
        // grille.ajoute_tuile(&B, 3, 2);
        // cout << grille;
    }
}
// Retourne le(s) côté(s) qui a matché en posant la tuile A en (ligne, colonne)
vector<int> PartieTrax::coteContact(Tuile *A, int ligne, int colonne) const
{
    vector<int> listeCoteContact; // on peut avoir matché plusieurs côtés en même temps
    int longueur = grille->get_longueur();
    int largeur = grille->get_largeur();

    // Même principe que la fonction comparer : on regarde ce qu'il y a autour
    if (ligne < longueur - 1) // Si on est pas dans la dernière ligne
    {
        if (grille->get_cases()[ligne + 1][colonne] != nullptr)
            listeCoteContact.push_back(2);
    }
    if (ligne > 0) // Si on est pas sur la première ligne
    {
        if (grille->get_cases()[ligne - 1][colonne] != nullptr)
            listeCoteContact.push_back(0);
    }
    if (colonne < largeur - 1) // Si on est pas dans la dernière colonne
    {
        if (grille->get_cases()[ligne][colonne + 1] != nullptr)
            listeCoteContact.push_back(1);
    }
    if (colonne > 0) // Si on est pas dans la première colonne
    {
        if (grille->get_cases()[ligne][colonne - 1] != nullptr)
            listeCoteContact.push_back(3);
    }
    return listeCoteContact;
}

// Retourne le côté opposé d'où on vient (ex: cote_opposé(gauche) = droite)
int PartieTrax::cote_oppose(int cote) const
{
    return ((cote + 2) % 4); // ({0,1,2,3}) :  0<->2 / 1<->3  sont opposés
}

// Retourne la prochaine case, et change la ligne/colonne pour se positionner sur cette case
Tuile *PartieTrax::prochaine_case(int direction, int &ligne, int &colonne, int &ligne_min, int &ligne_max, int &colonne_min, int &colonne_max) const
{
    if (direction == 0) // Haut
    {
        ligne--; // on recule d'une ligne
        if (ligne < ligne_min)
            ligne_min = ligne;
    }
    if (direction == 1) // Droite
    {
        colonne++; // on avance d'une colonne
        if (colonne > colonne_max)
            colonne_max = colonne;
    }
    if (direction == 2) // Bas
    {
        ligne++; // on avance d'une ligne
        if (ligne > ligne_max)
            ligne_max = ligne;
    }
    if (direction == 3) // Gauche
    {
        colonne--; // on recule d'une colonne
        if (colonne < colonne_min)
            colonne_min = colonne;
    }
    // cout << *grille->get_cases()[ligne][colonne];
    return grille->get_cases()[ligne][colonne];
}

// Retourne quel autre côté (que l'origine) de la tuile est de la couleur voulue
int PartieTrax::prochaine_direction(Tuile *A, int origine, int couleur) const
{
    for (int i{0}; i < 4; i++)
    {
        if (i != origine && A->get_cote()[i][0] == couleur) // si on est de la même couleur mais qu'on n'est pas l'origine
            return i;
    }
    cout << "Erreur; on ne trouve pas le côté de la même couleur ?" << endl;
    return -1;
}

bool PartieTrax::parcours(Tuile *A, int ligne, int colonne, int couleur) const
{
    // On regarde quelle couleur on a reliée en posant notre tuile
    vector<int> listeCote = coteContact(A, ligne, colonne);
    int coteContact{-1}; // côté qui a matché
    for (unsigned int i{0}; i < listeCote.size(); i++)
    {
        if (A->get_cote()[listeCote[i]][0] == couleur) // si un des côtés qui a matché a la couleur voulue
            coteContact = A->get_cote()[i][0];
    }
    if (coteContact == -1) // on a matché aucun côté de la couleur voulue
        return false;      // on n'a pas pu fermer de chemin dans cette couleur

    // On stocke ligne et colonne de A, pour faire un 2e parcours
    int LIGNE = ligne;
    int COLONNE = colonne;
    // retient les plus hautes et plus basses lignes/colonnes rencontrées
    int ligne_min = ligne; // pour le moment on n'est pas allé plus loin que les coord de la tuile A
    int ligne_max = ligne;
    int colonne_min = colonne;
    int colonne_max = colonne;

    // PARCOURS de la couleur voulue pour la recherche de boucle
    int prochaineDirection = coteContact;          // on va du côté qu'on a relié
    int origine = cote_oppose(prochaineDirection); // on retient d'où on est venu (pour ne pas y retourner)

    Tuile *prochaineCase = prochaine_case(prochaineDirection, ligne, colonne, ligne_min, ligne_max, colonne_min, colonne_max); // cette fonction modifie ligne et colonne

    // on suit le chemin jusqu'à retomber sur la tuile d'origine
    // ou jusqu'à ce qu'il n'y ait plus rien
    while (prochaineCase != nullptr && prochaineCase != A) // on s'arête quand on n'a plus de voisin ou qu'on est revenu sur A
    {
        prochaineDirection = prochaine_direction(prochaineCase, origine, couleur);
        origine = cote_oppose(prochaineDirection);
        prochaineCase = prochaine_case(prochaineDirection, ligne, colonne, ligne_min, ligne_max, colonne_min, colonne_max);
    }

    // Si on est revenu à la première case, il y a eu une boucle
    if (prochaineCase == A)
    {
        cout << "Il y a une boucle !" << endl;
        return true;
    }

    // Si pas de boucle, on part de l'autre côté depuis A
    prochaineCase = A;
    ligne = LIGNE; // on réinitialise ligne et colonne pour être en A
    colonne = COLONNE;
    origine = coteContact; // avant le cote en contact était la prochaine direction, maintenant c'est l'origine

    while (prochaineCase != nullptr && ligne >= 0 && colonne >= 0) // on s'arête quand on n'a plus de voisin (on n'est pas dans une boucle)
    {
        prochaineDirection = prochaine_direction(prochaineCase, origine, couleur);
        origine = cote_oppose(prochaineDirection);
        prochaineCase = prochaine_case(prochaineDirection, ligne, colonne, ligne_min, ligne_max, colonne_min, colonne_max);
    }

    // Regardons s'il y a eu une ligne
    int LONGUEUR_TEST = 8;
    if (ligne_max - ligne_min + 1 >= LONGUEUR_TEST || colonne_max - colonne_min + 1 >= LONGUEUR_TEST)
    {
        cout << "Il y a eu une ligne !" << endl;
        return true;
    }

    return false;
}

void PartieTrax::jouer()
{
    cout << "Malheureusement il y a un bug dans notre partie..." << endl;
    cout << "Mais on peut vous présenter les fonctionnalités de Trax" << endl;
    cout << "Voulez-vous tester une ligne ou une boucle ?  1- boucle  2- ligne" << endl;
    int param{0};
    cin >> param;
    if (param == 1) // TESTER UNE BOUCLE
    {

        Tuile *A = new TuileTrax(2);
        A->tournerDroite();
        Tuile *B = new TuileTrax(2);
        B->tournerDroite();
        B->tournerDroite();
        Tuile *C = new TuileTrax(2);
        Tuile *D = new TuileTrax(2);
        D->tournerGauche();
        grille->set_cases(A, 0, 0);
        grille->set_cases(B, 0, 1);
        grille->set_cases(C, 1, 0);
        grille->set_cases(D, 1, 1);
        cout << *grille;

        cout << parcours(A, 0, 0, 1) << endl;

        delete A;
        delete B;
        delete C;
        delete D;
    }
    if (param == 2) // TESTER UNE LIGNE
    {
        Tuile *A = new TuileTrax(2);
        // A->tournerGauche();
        Tuile *B = new TuileTrax(1);
        B->tournerDroite();
        Tuile *C = new TuileTrax(2);
        C->tournerGauche();
        C->tournerGauche();
        Tuile *D = new TuileTrax(2);
        D->tournerDroite();
        Tuile *E = new TuileTrax(2);
        E->tournerGauche();
        Tuile *F = new TuileTrax(1);
        Tuile *G = new TuileTrax(2);
        Tuile *H = new TuileTrax(2);
        H->tournerDroite();
        Tuile *I = new TuileTrax(2);
        I->tournerGauche();

        Tuile *J = new TuileTrax(2);
        J->tournerGauche();
        J->tournerGauche();
        Tuile *K = new TuileTrax(1);
        Tuile *L = new TuileTrax(2);
        L->tournerDroite();
        Tuile *M = new TuileTrax(2);
        M->tournerGauche();
        Tuile *N = new TuileTrax(1);
        Tuile *O = new TuileTrax(2);
        Tuile *P = new TuileTrax(2);
        P->tournerDroite();
        Tuile *Q = new TuileTrax(2);
        Q->tournerGauche();
        Tuile *R = new TuileTrax(2);
        R->tournerDroite();
        Tuile *S = new TuileTrax(2);
        S->tournerGauche();
        Tuile *T = new TuileTrax(2);
        T->tournerGauche();
        T->tournerGauche();
        Tuile *U = new TuileTrax(1);
        Tuile *V = new TuileTrax(2);
        V->tournerDroite();
        Tuile *W = new TuileTrax(2);
        W->tournerGauche();
        Tuile *X = new TuileTrax(2);
        X->tournerDroite();
        Tuile *Y = new TuileTrax(2);
        Y->tournerGauche();

        grille->set_cases(A, 0, 0);
        grille->set_cases(B, 1, 0);
        grille->set_cases(C, 2, 0);
        grille->set_cases(D, 2, 1);
        grille->set_cases(E, 1, 1);
        grille->set_cases(F, 1, 2);
        grille->set_cases(G, 1, 3);
        grille->set_cases(H, 2, 3);
        grille->set_cases(I, 2, 2);
        grille->set_cases(J, 3, 2);
        grille->set_cases(K, 3, 3);
        grille->set_cases(L, 3, 4);
        grille->set_cases(M, 2, 4);
        grille->set_cases(N, 2, 5);
        grille->set_cases(O, 2, 6);
        grille->set_cases(P, 3, 6);
        grille->set_cases(Q, 3, 5);
        grille->set_cases(R, 4, 5);
        grille->set_cases(S, 4, 4);
        grille->set_cases(T, 5, 4);
        grille->set_cases(U, 5, 5);
        grille->set_cases(V, 5, 6);
        grille->set_cases(W, 4, 6);
        grille->set_cases(X, 4, 7);
        grille->set_cases(Y, 3, 7);

        cout << *grille << endl;

        cout << parcours(K, 3, 3, 2) << endl;

        delete A;
        delete B;
        delete C;
        delete D;
        delete E;
        delete F;
        delete G;
        delete H;
        delete I;
        delete J;
        delete K;
        delete L;
        delete M;
        delete N;
        delete O;
        delete P;
        delete Q;
        delete R;
        delete S;
        delete T;
        delete U;
        delete V;
        delete W;
        delete X;
        delete Y;
    }
}

// TANT QUE SAC PAS VIDE
//
// B = {B,N,B,N} (tuile déjà dans grille)
// joueur noir
// pioche A = {N,B,B,N} (la tourner ou pas)
// ajoute_tuile A à droite de tuile B

// jouer_coups_forcés()

//
// REGARDER SI Y'A UNE BOUCLES/LIGNES