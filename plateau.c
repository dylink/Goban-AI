#include <stdio.h>
#include "plateau.h"

//Initialise le plateau
void initPlateau(plateau grille){
  for (int i = 0; i<L ;i++){
    for (int j = 0; j<C; j++){
      grille[i][j] = 0;
    }
  }
}

//Affiche le plateau
void affichePlateau(plateau grille){
  char c = 65;
  int d;
  for (int e = 0; e < L; e++){
    printf("  %c ", c);
    c++;
  }
  printf("\n");
  for (int i = 0; i<L; i++){
    d = i+1;
    printf("%d ", d);
    for (int j = 0; j<C; j++){
      if(j==5){
        switch(grille[i][j]){
          case 0 : printf("+"); break;
          case 1 : printf("+"); break;
          case J1 : printf("O"); break;
          case IA : printf("X"); break;
        }
      }
      else{
        switch(grille[i][j]){
          case 0 : printf("+ - "); break;
          case 1 : printf("+ - "); break;
          case J1 : printf("O - "); break;
          case IA : printf("X - "); break;
        }
      }
    }
    printf(" %d ", d);
    if (i!=5){
      printf("\n");
      printf("  |   |   |   |   |   |");
      printf("\n");
    }
  }
  c = 65;
  printf("\n");
  for (int e = 0; e < L; e++){
    printf("  %c ", c);
    c++;
  }
  printf("\n");
}

//Raffraîchit le plateau si besoin est
void raffraichir(plateau grille, int joueur){
  pierre p;
  int i;
  int j;
  for(i = 0; i<L; i++){
    p.i = i;
    for (j=0; j<C; j++){
      p.j = j;
      p.joueur = grille[p.i][p.j];
      if(p.joueur == joueur){
        enleveChaine(grille, p);
        enlever(grille, p);
      }
      if(p.joueur == 0){
        oeil(grille, p);
      }
    }
  }
  affichePlateau(grille);
}
