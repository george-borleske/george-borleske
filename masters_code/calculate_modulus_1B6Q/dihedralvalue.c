#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <stdlib.h>
#include <math.h>
////Helix, Extenstion and Coil are taken from the database
int dihedralvalue(int dihedral_nodes[][4],double dihedral_para[][2],char rep2[][10],char des2[][10],char amino2[][10], int num_nodes) {

  int loop = 1;
  int i    = 0;
  while (loop == 1) {
    if (dihedral_nodes[i][0] > num_nodes || dihedral_nodes[i][1] > num_nodes || dihedral_nodes[i][2] > num_nodes || dihedral_nodes[i][3] > num_nodes || dihedral_nodes[i][0] == '\0') {
      loop = 0;
      i    = i-1;
      //printf("last read parameters were between nodes \n %s ( %d ), %s ( %d ), %s ( %d ), %s ( %d ) \n", rep2[dihedral[i][0]-1], dihedral[i][0], rep2[dihedral[i][1]-1],
        //dihedral[i][1], rep2[dihedral[i][2]-1], dihedral[i][2], rep2[dihedral[i][3]-1], dihedral[i][3]);
      //printf("with an angle value of %d and k value of %d at dihedral number %d \n", dihedral[i][4], dihedral[i][5], i+1);
    } else {

      /* between 4 backbone nodes (this will always be the case) */
      if(strstr(des2[dihedral_nodes[i][0]-1], "BAS") != NULL && strstr(des2[dihedral_nodes[i][1]-1], "BAS") != NULL
        && strstr(des2[dihedral_nodes[i][2]-1], "BAS") != NULL && strstr(des2[dihedral_nodes[i][3]-1], "BAS") != NULL){

        /* secondary structure is needed to determine the constants */
        if(strchr(rep2[dihedral_nodes[i][0]-1], 'E') != NULL && strchr(rep2[dihedral_nodes[i][1]-1], 'E') != NULL
          && strchr(rep2[dihedral_nodes[i][2]-1], 'E') != NULL && strchr(rep2[dihedral_nodes[i][3]-1], 'E') != NULL){
          dihedral_para[i][0]=0; //angle
          dihedral_para[i][1]=10; //k value

        } else if(strchr(rep2[dihedral_nodes[i][0]-1], 'C') != NULL && strchr(rep2[dihedral_nodes[i][1]-1], 'C') != NULL
          && strchr(rep2[dihedral_nodes[i][2]-1], 'C') != NULL && strchr(rep2[dihedral_nodes[i][3]-1], 'C') != NULL){
          dihedral_para[i][0]=0; //angle
          //dihedral_para[i][1]=10; //k value
	  dihedral_para[i][1] = 0;
	  printf("coil dihedral angle \n");
          printf("Nodes are: %d %d %d %d\n",dihedral_nodes[i][0],dihedral_nodes[i][1], dihedral_nodes[i][2], dihedral_nodes[i][3]);
          printf("Reps are: %s %s %s %s \n",rep2[dihedral_nodes[i][0]-1],rep2[dihedral_nodes[i][1]-1],rep2[dihedral_nodes[i][2]-1],rep2[dihedral_nodes[i][3]-1]);

	} else if(strchr(rep2[dihedral_nodes[i][0]-1], 'H') != NULL && strchr(rep2[dihedral_nodes[i][1]-1], 'H') != NULL
          && strchr(rep2[dihedral_nodes[i][2]-1], 'H') != NULL && strchr(rep2[dihedral_nodes[i][3]-1], 'H') != NULL){
          dihedral_para[i][0]=-120; //angle
	  //dihedral_para[i][0]=60; //angle
          dihedral_para[i][1]=400; //k value
        } else {
          /*
          printf("something went wrong reading in dihedral parameters between backbone nodes \n");
          printf("i is: %d \n", i);
          printf("Nodes are: %d %d %d %d\n",dihedral_nodes[i][0],dihedral_nodes[i][1], dihedral_nodes[i][2], dihedral_nodes[i][3]);
          printf("Reps are: %s %s %s %s \n",rep2[dihedral_nodes[i][0]-1],rep2[dihedral_nodes[i][1]-1],rep2[dihedral_nodes[i][2]-1],rep2[dihedral_nodes[i][3]-1]);
          if(strchr(rep2[dihedral_nodes[i][0]-1], 'H') != NULL){
            printf("pointer is %d", strchr(rep2[dihedral_nodes[i][0]-1], 'H'));
          }
	  */
          dihedral_para[i][0] = 0;
	  dihedral_para[i][1] = 0;
        }
      } else {
        printf("problem occurred between nodes %d, %d, %d, and %d \n",dihedral_nodes[i][0],dihedral_nodes[i][1], dihedral_nodes[i][2], dihedral_nodes[i][3]);
        printf("i is: %d \n", i);
      }
    }
    i=i+1;
  }

  return 0;
}
