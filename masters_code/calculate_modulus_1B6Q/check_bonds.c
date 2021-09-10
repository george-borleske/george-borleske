#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int check_bonds(int i, int j, int bond_nodes[][2], int num_tot_bd) {

  int k;
  int bonded = 0;

  for(k=0;k<num_tot_bd;k++){
    if(bond_nodes[k][0] == i + 1 && bond_nodes[k][1] == j + 1){
      bonded = 1;
    } else if(bond_nodes[k][0] == j + 1  && bond_nodes[k][1] == i + 1) {
      bonded = 1;
    }
  }


  return bonded;
}
