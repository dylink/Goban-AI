#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "plateau.h"

//Teste si un élément donné appartient à une liste
int appartient(int tab[], int e){
  int i;
  //size_t n = sizeof(*tab) / sizeof(e);
  for (i=0; i<36; i++){
    if (tab[i] == e){
      return 1;
    }
  }
  return 0;
}

//Retourne un i par rapport à un numéro de case donné
int fonctMathi(int nombre){
  int i;
  int j;
  for(i=0; i<6;i++){
    for(j=0; j<6 ; j++){
      if((i*6 + j) == nombre){
        return i;
      }
    }
  }
  return 0;
}

//Retourne un j par rapport à un numéro de case donné
int fonctMathj(int nombre){
  int i;
  int j;
  for(i=0; i<6;i++){
    for(j=0; j<6 ; j++){
      if((i*6 + j) == nombre){
        return j;
      }
    }
  }
  return 0;
}

//Retourne le nombre de liberté d'une pierre
int liberte(plateau grille, pierre p){
  int l = 0;
  if (grille[p.i+1][p.j] == 0 && p.i != 5){
    l += 1;
    //grille[p.i+1][p.j] = 1;
  }
  if (grille[p.i][p.j-1] == 0 && p.j != 0){
    l += 1;
    //grille[p.i][p.j-1] = 1;
  }
  if (grille[p.i-1][p.j] == 0 && p.i != 0) {
    l += 1;
    //grille[p.i-1][p.j] = 1;
  }
  if (grille[p.i][p.j+1] == 0 && p.j != 5){
    l += 1;
    //grille[p.i][p.j+1] = 1;
  }
  return l;
}

//Retourne le nombre de liberté d'un paire
int libertePaire(plateau grille, pierre p, pierre q){
  int l = 0;
  if (adjacent(grille, p, q)){
    l += liberte(grille, p) + liberte(grille, q);
  }
  return l;
}

//Retourne le nombre de liberté d'un triplet
int liberteTriplet(plateau grille, pierre p, pierre q, pierre r){
  int l = 0;
  if ((adjacent(grille, p, q) && adjacent(grille, p, r)) ^ (adjacent(grille, p, r) && adjacent(grille, r, q)) ^ (adjacent(grille, q, r) && adjacent(grille, p, q))) {
    l += liberte(grille, p) + liberte(grille, q) + liberte(grille, r);
    if ((p.i == q.i && p.i == r.i) ^ (p.j == q.j && p.j == r.j)) {
      l += 1;
    }
  }
  return l-1;
}

//Détermine si une pierre est isolée
int isolee(plateau grille, pierre p){
  if ((grille[p.i+1][p.j]  > 1 && p.i != 5) ^ (grille[p.i-1][p.j] > 1 && p.i != 0) ^ (grille[p.i][p.j+1] > 1 && p.j != 5) ^ (grille[p.i][p.j-1] > 1 && p.j != 0)) {
    return 0;
  }
  return 1;
}

//Détermine si deux pierres sont adjacentes
int adjacent(plateau grille, pierre p, pierre q){
  int l = 0;
  if (q.j != 5 || q.j != 0 || p.j != 0 || p.j != 5){
    if (((q.i == p.i-1) && (q.j == p.j)) || ((q.i == p.i+1) && (q.j == p.j)) || ((q.i == p.i) && (q.j == p.j-1)) || ((q.i == p.i) && (q.j == p.j+1))) {
      if (p.joueur == q.joueur){
        l = 1;
      }
      else {
        printf("La pierre (%d, %d) et la pierre (%d, %d) ne sont pas adjacentes.\n", p.j+1, p.i+1, q.j+1, q.i+1);
        l = 0;
      }
    }
    else {
      printf("La pierre (%d, %d) et la pierre (%d, %d) ne sont pas adjacentes.\n", p.j+1, p.i+1, q.j+1, q.i+1);
      l = 0;
    }
  }
  return l;
}

//La partie est finie si le tableau est plein (non utilisée)
int finPartie(plateau grille){
  int i, j, l;
  l=36;
  for (i = 0; i<L ;i++){
    for (j = 0; j<C; j++){
      if(grille[i][j] != 0)
        l--;
      }
    }
  return l;
}
