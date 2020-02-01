#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include <assert.h>

int main(){
  plateau grille;
  initPlateau(grille);
  affichePlateau(grille);
  resolution(grille);

	return 0;
}
