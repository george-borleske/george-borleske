#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <math.h>
//#include "dcdfile.h"


// change HS for back-side from .28 which was side chain to side chain to .32nm


int bondvalue(int bond[][2],double bond_para[][2],char rep2[][10],char des2[][10],char amino2[][10], int num_nodes) {
  int loop = 1;
  int i    = 0;
  int j;
  while (loop == 1) {
    if (bond[i][0] > num_nodes || bond[i][1] > num_nodes || bond[i][0] == '\0') {
      loop = 0;
      i    = i-1;
      //printf("last read parameters were between nodes %s ( %d ) and %s  ( %d )\n", rep2[bond[i][0]-1], bond[i][0],rep2[bond[i][1]-1], bond[i][1]);
      //printf("with a bond value of %d at bond number %d \n", bond[i][2], i+1);
    } else {
      
      /* bonds between backbone nodes */
      if(strstr(des2[bond[i][0]-1], "BAS") != NULL && strstr(des2[bond[i][1]-1], "BAS") != NULL){
        
        /* equilbruim distance of .35 nm for all backbone - backbone bonds */
        //bond[i][3]=35;
	bond_para[i][1] = .35;

        /*
        ************************************************************************************************************
        * find k_b based on the secondary structure
        ************************************************************************************************************
        */     

        /* secondary structure is the same for both nodes */
        if(strchr(rep2[bond[i][0]-1], 'H') != NULL && strchr(rep2[bond[i][1]-1], 'H') != NULL){
          bond_para[i][0]=1250;
        } else if(strchr(rep2[bond[i][0]-1], 'C') != NULL && strchr(rep2[bond[i][1]-1], 'C') != NULL){
          bond_para[i][0]=400;
        } else if(strchr(rep2[bond[i][0]-1], 'E') != NULL && strchr(rep2[bond[i][1]-1], 'E') != NULL){
          bond_para[i][0]=1250;
        } else if(strchr(rep2[bond[i][0]-1], 'T') != NULL && strchr(rep2[bond[i][1]-1], 'T') != NULL){
          bond_para[i][0]=500;
        } else if(strchr(rep2[bond[i][0]-1], 'B') != NULL && strchr(rep2[bond[i][1]-1], 'B') != NULL){
          bond_para[i][0]=400;

        /* secondary structure is different for each node */
        } else if(strchr(rep2[bond[i][0]-1], 'C') != NULL || strchr(rep2[bond[i][1]-1], 'C') != NULL) {
          bond_para[i][0]=400;
        } else if(strchr(rep2[bond[i][0]-1], 'B') != NULL || strchr(rep2[bond[i][1]-1], 'B') != NULL) {
          bond_para[i][0]=400;
        } else if(strchr(rep2[bond[i][0]-1], 'T') != NULL || strchr(rep2[bond[i][1]-1], 'T') != NULL) {
          bond_para[i][0]=500;
        } else if(strchr(rep2[bond[i][0]-1], 'H') != NULL || strchr(rep2[bond[i][1]-1], 'H') != NULL) {
          bond_para[i][0]=1250;
        } else if(strchr(rep2[bond[i][0]-1], 'E') != NULL || strchr(rep2[bond[i][1]-1], 'E') != NULL) {
          bond_para[i][0]=1250;
        }else {
          printf("something went wrong reading in bond parameters between backbone nodes \n");
          printf("i is: %d \n", i);
        }

      /* bonds between a sidechain node and its corresponding backbone node */
      } else if(strstr(des2[bond[i][0]-1], "BAS") != NULL && strstr(des2[bond[i][1]-1], "SI") != NULL){
        if(strstr(amino2[bond[i][0]-1], "ARG") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.33;
        } else if(strstr(amino2[bond[i][0]-1], "ASN") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.32;
        } else if(strstr(amino2[bond[i][0]-1], "ASP") != NULL){
          bond_para[i][0]=7500;
          bond_para[i][1]=.32;
        } else if(strstr(amino2[bond[i][0]-1], "CYS") != NULL){
          bond_para[i][0]=7500;
          bond_para[i][1]=.31;
        } else if(strstr(amino2[bond[i][0]-1], "GLN") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.40;
        } else if(strstr(amino2[bond[i][0]-1], "GLU") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.40;
        } else if(strstr(amino2[bond[i][0]-1], "HS") != NULL){
          bond_para[i][0]=7500;
          bond_para[i][1]=.32;
          //HIS?
        } else if(strstr(amino2[bond[i][0]-1], "LEU") != NULL){
          bond_para[i][0]=7500;
          bond_para[i][1]=.33;
        } else if(strstr(amino2[bond[i][0]-1], "LYS") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.33;
        } else if(strstr(amino2[bond[i][1]-1], "MET") != NULL){
          bond_para[i][0]=2500;
          bond_para[i][1]=.40;
        } else if(strstr(amino2[bond[i][0]-1], "PHE") != NULL){
          bond_para[i][0]=7500;
          bond_para[i][1]=.31;
        } else if(strstr(amino2[bond[i][0]-1], "PRO") != NULL){
          bond_para[i][0]=7500;
          bond_para[i][1]=.30;
        } else if(strstr(amino2[bond[i][0]-1], "SER") != NULL){
          bond_para[i][0]=7500;
          bond_para[i][1]=.25;
        } else if(strstr(amino2[bond[i][0]-1], "THR") != NULL){
          bond_para[i][0]=0; // constrained
          bond_para[i][1]=.26;
        } else if(strstr(amino2[bond[i][0]-1], "TRP") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.30;
        } else if(strstr(amino2[bond[i][0]-1], "TYR") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.32;
        } else if(strstr(amino2[bond[i][0]-1], "VAL") != NULL){
          bond_para[i][0]=0; //constrained
          bond_para[i][1]=.27;
        } else if(strstr(amino2[bond[i][0]-1], "ILE") != NULL){
          bond_para[i][0]=0; //constrained
          bond_para[i][1]=.31;
        } else {
          printf("problem occurred between backbone %d sidechain %d \n",bond[i][0],bond[i][1]);
          printf("i is: %d \n", i);
        }
      /*@@@@@@@@@ need to go back and look at exceptions for bas to si @@@@@@@@@@@@*/

      /* bonds between two sidechain nodes */
      } else if(strstr(des2[bond[i][0]-1], "SI") != NULL && strstr(des2[bond[i][1]-1], "SI") != NULL){
        if(strstr(amino2[bond[i][0]-1], "PHE") != NULL){
          bond_para[i][0]=0; // constrained
          bond_para[i][1]=.27;
        } else if(strstr(amino2[bond[i][0]-1], "ARG") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.34;
        } else if(strstr(amino2[bond[i][0]-1], "LYS") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.28;
        } else if(strstr(amino2[bond[i][0]-1], "HIS") != NULL){
          bond_para[i][0]=0; // constrained
          bond_para[i][1]=.27;
        /*@@@@@@@@@@@@@@@@ Not sure about HSD @@@@@@@@@@@@@@@@@@@@@@@@@*/
        } else if(strstr(amino2[bond[i][0]-1], "HSD") != NULL){
          bond_para[i][0]=0; // constrained
          bond_para[i][1]=.27;
        } else if(strstr(amino2[bond[i][0]-1], "TYR") != NULL){
          bond_para[i][0]=0; // constrained
          bond_para[i][1]=.27;
        } else if(strstr(amino2[bond[i][0]-1], "TRP") != NULL){
          bond_para[i][0]=0; // constrained
          bond_para[i][1]=.27;
        } else if(strstr(amino2[bond[i][0]-1], "CYS") != NULL){
          bond_para[i][0]=5000;
          bond_para[i][1]=.39;
          //This is different between the paper and parameter files used in the simulation. These parameters are from the simulation
        }
      } else {
        printf("problem occurred between nodes %d and %d \n",bond[i][0],bond[i][1]);
        printf("i is: %d \n", i);
        printf("the amino acid is : %s\n",amino2[bond[i][0]-1]);
        printf("des are %s and %s \n",des2[bond[i][0]-1],des2[bond[i][1]-1]);
      }
    }
    i=i+1;
  }

  return 0;
}

