#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "plateau.h"

//Fonction vider buffer
void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
      c = getchar();
    }
}

//Fonction permettant de saisir un problème
int probleme(plateau grille){
  int i = 1;
  int joueur;
  int e;
  int a, d, j=20;
  char c[2];
  while(i) {
    printf("\nVoulez-vous saisir un problème? O ou N.\n\n");
    scanf("%s", c);
    if (c[0] == 'N'){
      i = 0;
    }
    else if (c[0] == 'O'){
      printf("Veuillez placer vos pions : \n\n");
      while(i){
        affichePlateau(grille);
        printf("\nQuel joueur voulez-vous placer ?");
        printf("\n1 : Joueur 1.\t\t2 : Joueur 2.\t\t3 : Effacer pion.\t0 : Quitter.\n\n");
        scanf("%d", &j);
        if(j > 0 && j < 4){
          switch (j){
            case 1 : joueur = J1; break;
            case 2 : joueur = IA; break;
            case 3 : joueur = 0; break;
          }
          printf("\nEntrez une coordonnée : \n");
          if (c[0] == 'Q'){
            i = 0;
          }
          scanf("%s", c);
          a = c[0]-65;
          d = c[1]-49;
          if ((a<0 || a>5) ^ (d<0 || d>5)){
            printf("\nCes coordonnées n'existent pas.\n\n");
          }
          if (grille[d][a] != 0 && (a > -1 && a < 6) && (d > -1 && d > 6)){
            printf("\nCette intersection n'est pas disponible.\n\n");
          }
          else{
            grille[d][a] = joueur;
          }
        }
        else if (j == 0){
          printf("Qui doit jouer?\n");
          scanf("%d", &e);
          if(e > 0 && e < 3){
            switch(e){
              case 1 : joueur = J1; break;
              case 2 : joueur = IA; break;
            }
          }
          else {
            printf("Ce joueur n'existe pas.\n");
          }
          i = 0;
        }
        else{
          printf("\nSaisie incorrecte.\n\n");
        }
      }
    }
    i = 0;
  }
  printf("\nFin de la saisie du problème.\n");
  return joueur;
}

//Fonction permettant de lancer une partie (pas abouti)
void game (plateau grille){
  int joueur = J1;
  int a, d;
  char c[2];
  while(finPartie(grille)) {
    if(joueur == J1){
      printf("Autour du joueur 1 : \n");
      printf("\nEntrez une coordonnée : ");
      scanf("%s", c);
      a = c[0]-65;
      d = c[1]-49;
      grille[d][a] = joueur;
      viderBuffer();
      joueur = (joueur == J1)? IA : J1;
      affichePlateau(grille);
    }
    if(joueur == IA){
      printf("Autour du joueur 2 : \n");
      printf("\nEntrez une coordonnée : ");
      scanf("%s", c);
      a = c[0]-65;
      d = c[1]-49;
      grille[d][a] = joueur;
      viderBuffer();
      joueur = (joueur == J1)? IA : J1;
      affichePlateau(grille);
    }
  }
  printf("\nLa partie est terminée!\n");
}
