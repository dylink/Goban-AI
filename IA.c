#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <assert.h>

//Fonction permettant de parcourir une chaîne, inspirée de l'agorithme de remplissage par diffusion
void chaine(plateau grille, int j, int i, int joueur, int tab[], int *t[]) {
  int gauche, droite, e;
  int in_line = 1;
  gauche = droite = j;
    while( in_line){
      if (!appartient(tab, i * L + gauche)){
        tab[i * L + gauche] = i * L + gauche;
      }
      gauche--;
      in_line = (gauche < 0) ? 0 : (grille[i][gauche] == joueur);
    }
    gauche++;
    in_line = 1;
    while( in_line){
      if (!appartient(tab, i * L + droite)){
        tab[i * L + droite] = i * L + droite;
      }
      droite++;
      in_line = (droite > C-1) ? 0 : (grille[i][droite] == joueur);
    }
    droite--;
    for(e = gauche; e <= droite; e++){
      if( i >= 0 && grille[i - 1][e] == joueur && !appartient(tab, (i - 1) * L + e)){
        chaine(grille, e, i - 1, joueur, tab, t);
      }
      if( i < L-1 && grille[i + 1][e] == joueur && !appartient(tab, (i + 1) * L + e)){
        chaine(grille, e, i + 1, joueur, tab, t);
      }
    }
}

//Fonction permettant d'afficher une chaîne
void afficheChaine(plateau grille, pierre p){
  int tab[36];
  int *t[36];
  for (int e = 36; e < 72; e++){
    tab[e-36] = e;
  }
  if (estChaine(grille, p)){
    int i = p.i;
    int j = p.j;
    chaine(grille, j, i, p.joueur, tab, t);
    for (int f = 0; f < 36; f++){
      if(appartient(tab, f)){
        pierre s;
        s.i = fonctMathi(f);
        s.j = fonctMathj(f);
        printf("p(%d, %d)\n", s.i, s.j);
      }
    }
  }
}

//Fonction permettant de retirer une chaîne sur le plateau si besoin est
void enleveChaine(plateau grille, pierre p){
  int tab[36];
  int *t[36];
  for (int e = 36; e < 72; e++){
    tab[e-36] = e;
  }
  int i = p.i;
  int j = p.j;
  chaine(grille, j, i, p.joueur, tab, t);
  pierre s;
  if (liberteChaine(grille, p) == 0){
    for (int e = 0; e < 36; e++){
      if(appartient(tab, e)){
        s.i = fonctMathi(e);
        s.j = fonctMathj(e);
        grille[s.i][s.j] = 1;
      }
    }
  }
  printf("\n");
}

//Teste si une chaîne est en position d'Atari (pas abouti)
int atariChaine(plateau grille, pierre p){
  int tab[36];
  int *t[36];
  for (int e = 36; e < 72; e++){
    tab[e-36] = e;
  }
  if (estChaine(grille, p)){
    int i = p.i;
    int j = p.j;
    chaine(grille, j, i, p.joueur, tab, t);
    pierre s;
    for (int e = 0; e < 36; e++){
      if(appartient(tab, e)){
        s.i = fonctMathi(e);
        s.j = fonctMathj(e);
        if(liberte(grille, s) == 1 && liberteChaine(grille, p) == 1){
          return 1;
        }
      }
    }
  }
  return 0;
}

//Retourne le nombre de liberté d'une chaîne (pas abouti)
int liberteChaine(plateau grille, pierre p){
  int tab[36];
  int *t[36];
  int l = 0;
  for (int e = 36; e < 72; e++){
    tab[e-36] = e;
  }
  if (estChaine(grille, p)){
    int i = p.i;
    int j = p.j;
    chaine(grille, j, i, p.joueur, tab, t);
    for (int e = 0; e < 36; e++){
      if(appartient(tab, e)){
        pierre s;
        s.i = fonctMathi(e);
        s.j = fonctMathj(e);
        l += liberte(grille, s);
        if ((j != s.j) ^ (i != s.i)){
          l -= 1;
        }
      }
    }
    return l;
  }
  return 0;
}

//Teste si une pierre donnée appartient à une chaîne
int estChaine(plateau grille, pierre p){
  p.joueur = grille[p.i][p.j];
  if (p.joueur > 1){
    if (grille[p.i+1][p.j] == p.joueur || grille[p.i-1][p.j] == p.joueur || grille[p.i][p.j+1] == p.joueur || grille[p.i][p.j-1] == p.joueur){
      return 1;
    }
  }
  return 0;
}

//Met une pierre en position d'Atari
void faitAtari (plateau grille){
  pierre p;
  int joueur;
  for(int i=0;  i<L;  i++){
    p.i = i;
    for(int j=0;  j<C ;  j++){
      p.j = j;
      if (grille[p.i][p.j] > 1){
        //printf("p(%d, %d) == %d\n", p.i, p.j, liberte(grille, p));
        if (pAtari(grille, p)){
          joueur = (grille[p.i][p.j] == J1)? IA : J1;
          if (grille[p.i+1][p.j] < 3){
            grille[p.i+1][p.j]=joueur;
            return;
          }
          else if (grille[p.i-1][p.j] < 3){
            grille[p.i-1][p.j]=joueur;
            return;
          }
          else if (grille[p.i][p.j-1] < 3){
            grille[p.i][p.j-1]=joueur;
            return;
          }
          else if (grille[p.i][p.j+1] < 3){
            grille[p.i][p.j+1]=joueur;
            return;
          }
        }
      }
    }
  }
  printf("\nPas d'atari possible.\n\n");
  return;
}

//Teste si une pierre peut-être mise en position d'Atari
int pAtari (plateau grille, pierre p){
  int l = 0;
  if (liberte(grille, p) == 2){
    if (grille[p.i+1][p.j] != (p.joueur ^ 0)
    && grille[p.i][p.j-1]!= (p.joueur ^ 0)
    && grille[p.i-1][p.j] != (p.joueur ^ 0)
    && grille[p.i][p.j+1] != (p.joueur ^ 0)){
      l = 1;
    }
    else {
      l = 0;
    }
  }
  else {
    l = 0;
  }
  return l;
}

//Teste si une pierre est en atari
int atari (plateau grille, pierre p){
  int l = 0;
  p.joueur = grille[p.i][p.j];
  if (liberte(grille, p) == 1){
    //printf("%d\n", p.joueur);
    if (grille[p.i+1][p.j] != (p.joueur ^ 0)
    && grille[p.i][p.j-1]!= (p.joueur ^ 0)
    && grille[p.i-1][p.j] != (p.joueur ^ 0)
    && grille[p.i][p.j+1] != (p.joueur ^ 0)){
      l = 1;
    }
    else {
      l = 0;
    }
  }
  else {
    l = 0;
  }
  return l;
}

//Enlève une pierre du plateau si besoin est
void enlever(plateau grille, pierre p){
  p.joueur = grille[p.i][p.j];
  if(p.joueur >2 ){
    if(!(liberte(grille, p)) && (grille[p.i+1][p.j] != (p.joueur ^ 0) && grille[p.i-1][p.j] != (p.joueur ^ 0) && grille[p.i][p.j+1] != (p.joueur ^ 0) && grille[p.i][p.j-1] != (p.joueur ^ 0) )){
      grille[p.i][p.j] = 1;
    }
  }
}

//Détermine si une case est un oeil
int oeil(plateau grille, pierre p){
  p.joueur = grille[p.i][p.j];
  if(grille[p.i+1][p.j] > 1 && grille[p.i-1][p.j] > 1 && grille[p.i][p.j+1] > 1 && grille[p.i][p.j-1] > 1) {
    grille[p.i][p.j] = 1;
    return 1;
  }
  return 0;
}

/*int estCapture(plateau grille, int joueur){
  pierre p;
  for(int i=0;  i<L;  i++){
    p.i = i;
    for(int j=0;  j<C ;  j++){
      p.j = j;
      if (grille[p.i][p.j] > 1 && grille[p.i][p.j] != joueur){
        if(atariChaine(grille, p) ^ atari(grille,p) ^ pAtari(grille, p)) {
          return 1;
        }
      }
    }
  }
  return 0;
}

int estDefense(plateau grille, int joueur){
  pierre p;
  for(int i=0;  i<L;  i++){
    p.i = i;
    for(int j=0;  j<C ;  j++){
      p.j = j;
      if (grille[p.i][p.j] > 1 && grille[p.i][p.j] == joueur){
        if(atariChaine(grille, p) ^ atari(grille,p) ^ pAtari(grille, p)) {
          return 1;
        }
      }
    }
  }
  return 0;
}*/

//Programme de résolution de problèmes (pas abouti)
void resolution(plateau grille){
  int joueur = probleme(grille);
  pierre p;
  int joueur2;
  joueur2 = (joueur == IA) ? J1 : IA;
  for(int i=0;  i<L;  i++){
    p.i = i;
    for(int j=0;  j<C ;  j++){
      p.j = j;
      if (grille[p.i][p.j] > 1 && grille[p.i][p.j] != joueur){
        if(atariChaine(grille, p)){
          if (grille[p.i+1][p.j] == 0){
            grille[p.i+1][p.j]=joueur;
            enleveChaine(grille, p);
            raffraichir(grille, joueur2);
            return;
          }
          else if (grille[p.i-1][p.j] == 0){
            grille[p.i-1][p.j]=joueur;
            enleveChaine(grille, p);
            raffraichir(grille, joueur2);
            return;
          }
          else if (grille[p.i][p.j-1] == 0 && p.j != 0){
            grille[p.i][p.j-1]=joueur;
            enleveChaine(grille, p);
            raffraichir(grille, joueur2);
            return;
          }
          else if (grille[p.i][p.j+1] == 0 && p.i != 0){
            grille[p.i][p.j+1]=joueur;
            enleveChaine(grille, p);
            raffraichir(grille, joueur);
            return;
          }
        }
      }
      else if (grille[p.i][p.j] > 1 && grille[p.i][p.j] == joueur){
        if(atariChaine(grille, p)){
          if (grille[p.i+1][p.j] == 0){
            grille[p.i+1][p.j]=joueur;
            //enleveChaine(grille, p);
            raffraichir(grille, 0);
            return;
          }
          else if (grille[p.i-1][p.j] == 0){
            grille[p.i-1][p.j]=joueur;
            //enleveChaine(grille, p);
            raffraichir(grille, 0);
            return;
          }
          else if (grille[p.i][p.j-1] == 0 && p.j != 0){
            grille[p.i][p.j-1]=joueur;
            //enleveChaine(grille, p);
            raffraichir(grille, 0);
            return;
          }
          else if (grille[p.i][p.j+1] == 0 && p.i != 0){
            grille[p.i][p.j+1]=joueur;
            //enleveChaine(grille, p);
            raffraichir(grille, 0);
            return;
          }
        }
      }
    }
  }
  for(int i=0;  i<L;  i++){
    p.i = i;
    for(int j=0;  j<C ;  j++){
      p.j = j;
      if (grille[p.i][p.j] > 1 && grille[p.i][p.j] != joueur){
        if (atari(grille, p)){
          if (grille[p.i+1][p.j] == 0){
            grille[p.i+1][p.j]=joueur;
            enlever(grille, p);
            raffraichir(grille, joueur2);
            return;
          }
          else if (grille[p.i-1][p.j] == 0){
            grille[p.i-1][p.j]=joueur;
            enlever(grille, p);
            raffraichir(grille, joueur2);
            return;
          }
          else if (grille[p.i][p.j-1] == 0 && p.j != 0){
            grille[p.i][p.j-1]=joueur;
            enlever(grille, p);
            raffraichir(grille, joueur2);
            return;
          }
          else if (grille[p.i][p.j+1] == 0 && p.i != 0){
            grille[p.i][p.j+1]=joueur;
            enlever(grille, p);
            raffraichir(grille, joueur2);
            return;
          }
        }
      }
      else if (grille[p.i][p.j] > 1 && grille[p.i][p.j] == joueur){
        if (atari(grille, p)){
          if (grille[p.i+1][p.j] == 0){
            grille[p.i+1][p.j]=joueur;
            //enlever(grille, p);
            raffraichir(grille, 0);
            return;
          }
          else if (grille[p.i-1][p.j] == 0){
            grille[p.i-1][p.j]=joueur;
            //enlever(grille, p);
            raffraichir(grille, 0);
            return;
          }
          else if (grille[p.i][p.j-1] == 0 && p.j != 0){
            grille[p.i][p.j-1]=joueur;
            //enlever(grille, p);
            raffraichir(grille, 0);
            return;
          }
          else if (grille[p.i][p.j+1] == 0 && p.i != 0){
            grille[p.i][p.j+1]=joueur;
            //enlever(grille, p);
            raffraichir(grille, 0);
            return;
          }
        }
      }
    }
  }
  printf("\nPas de capture possible.\n\n");
  return;
}
