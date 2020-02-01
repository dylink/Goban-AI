#define L 6 //Nombre de colonnes
#define C 6 //Nombre de lignes
#define J1 3 //Joueur 1
#define IA 4 //Joueur 2



typedef struct pierre{ //Création d'une structure "pierre"
	int i;
	int j;
	int joueur;
} pierre;


typedef int plateau[C][L]; //Création d'un type "plateau" de taille C*L



/*																			Fonctions de plateau																		*/

void initPlateau(plateau grille);
void affichePlateau(plateau grille);
void raffraichir(plateau grille, int joueur);

/*																			Fonctions de pierres																		*/


int liberte(plateau grille, pierre p);
int libertePaire(plateau grille, pierre p, pierre q);
int liberteTriplet(plateau grille, pierre p, pierre q, pierre r);
int liberteChaine(plateau grille, pierre p);
int isolee(plateau grille, pierre p);
int adjacent(plateau grille, pierre p, pierre q);
void afficheChaine(plateau grille, pierre p);
void chaine(plateau grille, int j, int i, int joueur, int tab[], int *t[]);


/*																			Fonctions de jeu																		*/

int finPartie(plateau grille);
void game(plateau grille);
int probleme(plateau grille);


/*																			Fonctions de règles																		*/

int atari (plateau grille, pierre p);
int pAtari (plateau grille, pierre p);
void enlever(plateau grille, pierre p);
void enleveChaine(plateau grille, pierre p);
int oeil(plateau grille, pierre p);

/*																			Fonctions utilitaires																		*/

int fonctMathi(int nombre);
int fonctMathj(int nombre);
int appartient(int tab[], int e);
void explore(plateau grille, pierre p);


/*																			Fonctions "IA"																		*/

void resolution(plateau grille);
void faitAtari (plateau grille);
int estChaine(plateau grille, pierre p);
int atariChaine(plateau grille, pierre p);
