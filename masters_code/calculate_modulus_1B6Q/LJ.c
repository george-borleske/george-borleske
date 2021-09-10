#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "QLJ.c"
#include "PLJ.c"
#include "NLJ.c"
#include "CLJ.c"
#include "check_bonds.c"

//float QLJ(float xyz[][10], char rep2[][10], int i, int j, float* sig);
//float PLJ(float xyz[][10], char rep2[][10], int i, int j);
//float NLJ(float xyz[][10], char rep2[][10], int i, int j);
//float CLJ(float xyz[][10], char rep2[][10], int i, int j, float * sig);
//int check_bonds(int i, int j, int bond_nodes[][2], int num_tot_bd);

int LJ(float En[][9], char rep2[][10], char rep3[][10], char des2[][10], int num_nodes, float xyz0[][4], float xyz[][4], int bond_nodes[][2], int num_tot_bd, int t, int testnode){

  float force_const, x1_0, y1_0, z1_0, x1, y1, z1;
  float sig;                   /* sigma, ie the finite distance at which the inter-particle potential is zero*/
  float ep;                    /* epislon, ie the depth of the potential well */
  float dist;                  /* magnitude of the vector between nodes i and j */
  int bonded;                  /* tells whether or not the two nodes are bonded togheter. if they are we will not compute the LJ potential */
  int i, j, npair;
  float LJ_eng = 0.0, LJ_this; /* total Lennard Jones potential */
  float min_dist = 0.0;
  FILE *fp;
  float rcut = 1.2;            /* cuttoff distance */
  float output = 0.0;
  char  title[100];                     /* title of text output */
  //printf("enetered LJ.c \n");
  //printf("number of bonds = %d \n", num_tot_bd);
  //getchar();

  npair = 0;
  for(i=0;i<num_nodes;i++){
    for(j=0;j<num_nodes;j++){
      //printf("i = %d, j = %d \n", i, j);	    
      if(i != j) {
	bonded = check_bonds(i,j,bond_nodes,num_tot_bd); // check to make sure nodes i and j are not bonded together.
        if(0 == bonded){ 
          //printf("bonded = %d \n", bonded);
	  //getchar();

          x1   = xyz[i][1] - xyz[j][1];                  // x-components of the distance between the two nodes
          y1   = xyz[i][2] - xyz[j][2];
          z1   = xyz[i][3] - xyz[j][3];
          dist = sqrt(powf(x1,2)+powf(y1,2)+powf(z1,2)); // magnitude of the vector between nodes i and j
          ep   = 0;
          sig  = 0;
	  dist = dist;

	  /*
	  if(rep3[i][0] == 'S' && rep3[j][0] == 'S') {
            min_dist = .43;
	  } else {
            min_dist = .47;
	  }
	  */

          //if(dist <= 1.2 && dist > min_dist){ //cutoff distance is 1.2nm
	  if(dist <= rcut){ //cutoff distance is 1.2nm

            //printf("\nat nodes %d and %d w/ dist of %f \n",i+1,j+1,dist);
            if(rep2[i][0] == 'Q'){
              ep = QLJ(rep2, i, j, &sig);
              //printf("sig is %f at nodes %d and %d \n",sig,i+1,j+1);
            } else if(rep2[i][0] == 'P'){
              ep = PLJ(rep2, i, j);
              sig = .47;
              //printf("ep is %f \n",ep);
            } else if(rep2[i][0] == 'N'){
              ep = NLJ(rep2, i, j);
              sig = .47;
              //printf("ep is %f \n",ep);
            } else if(rep2[i][0] == 'C'){
              ep = CLJ(rep2, i, j, &sig);
              //printf("ep is %f \n",ep);
            } else {
              printf("something went wrong reading parameters of LJ potential between nodes %d and %d \n",i+1,j+1);
              printf("reps are %s and %s \n", rep2[i], rep2[j]);
            }
            if(ep == 0){
              printf("ep is 0 at nodes %d and %d \n",i+1,j+1);
            } else if(sig == 0){
              printf("sig is 0 at nodes %d and %d \n",i+1,j+1);
            }

            /*
            if(i<3 && j<3){
              printf("at nodes %d and %d ep is %f and sig is %f \n",i+1,j+1,ep,sig);
              getchar();
            }
            */

	    if(sig == .62){
              printf("large sig \n");
              printf("at nodes %d (%s) and %d (%s) w/ dist of %f \n",i+1,rep2[i],j+1,rep2[j],dist);
	      printf("ep = %f sig = %f \n\n", ep, sig);
	    }

	    if(rep3[i][0] == 'S' && rep3[j][0] == 'S') {
              //printf("Ring particles \n");
              //printf("at nodes %d (%s) and %d (%s) w/ dist of %f \n",i+1,rep3[i],j+1,rep3[j],dist);
	      //printf("before: ep = %f sig = %f \n\n", ep, sig);
	      ep = .75 * ep;
	      sig = .43;
              //printf("after: ep = %f sig = %f \n\n", ep, sig);
	    }

	    /*
	    if(dist < .47) {
              printf("at nodes %d (%s) and %d (%s) w/ dist of %f \n",i+1,rep3[i],j+1,rep3[j],dist);
	      printf("ep = %f sig = %f \n\n", ep, sig);
	    }
	    */

            force_const = 24 * ep * (-2 * powf(sig,12) / powf(dist,14) + powf(sig,6) / powf(dist,8)); // * (.5);

	    /* Include s shifting 
	    LJ_this = 4 * ep * (powf(sig/dist,12) - powf(sig/dist,6)) -
		      4 * ep * (powf(sig/rcut,12) - powf(sig/rcut,12));
	    LJ_eng += 4 * ep * (powf(sig/dist,12) - powf(sig/dist,6)) -
		      4 * ep * (powf(sig/rcut,12) - powf(sig/rcut,12));
            */
            LJ_this = 4 * ep * (powf(sig/dist,12) - powf(sig/dist,6));
            LJ_eng += 4 * ep * (powf(sig/dist,12) - powf(sig/dist,6));
            output  = (powf(sig/dist,12) - powf(sig/dist,6));


            /*
	    if(i == testnode){
              sprintf(title, "LJ_%d_%d.dat", testnode+1, j+1);
              if( t == 0) {
                fp = fopen(title, "w");
              } else {
                fp = fopen(title, "a");
              }
              if (fp == NULL) {
                printf("can't open output file for Lennard Jones! \n");
              } else {
              fprintf(fp, "%d %f %f %f \n", t, force_const, LJ_this, dist);
              }
                fclose(fp);
            }
            */

            npair++;
            //printf(" force_const = %12.5e ep = %12.5e sig = %12.5e dist = %12.5e LJ = %12.4e LJ_tot = %12.4e npair = %5d j+1 = %5d, i+1 = %5d \n", force_const, ep, sig, dist, LJ_this, LJ_eng, npair, j+1, i+1);
            //if((npair%100)==0) //getchar();

            /*
            if(i == 0){
              printf("x1, y1, and z1 are %f %f %f \n",x1,y1,z1);
              printf("dist is %f, sig is %f, ep is %f \n",dist, sig, ep);
              printf("unchange for first node is %f \n \n",unchange);
            }
            */

            x1_0 = xyz0[i][1] - xyz0[j][1]; /* x-component of the initial distance between nodes */
            y1_0 = xyz0[i][2] - xyz0[j][2]; /* y-component of the initial distance between nodes */
            z1_0 = xyz0[i][3] - xyz0[j][3]; /* z-component of the initial distance between nodes */

            /*
	    if(i == testnode && dist <= .7){
              sprintf(title, "LJ_stress_%d_%d.dat", testnode+1, j+1);
              if( t == 0) {
                fp = fopen(title, "w");
              } else {
                fp = fopen(title, "a");
              }
              if (fp == NULL) {
                printf("can't open output file for Lennard Jones stress! \n");
              } else {
              fprintf(fp, "%d %f %f %f %f %f \n", t, force_const, force_const * x1 * x1_0, force_const * y1 * y1_0, force_const * z1 * z1_0, dist);
              }
                fclose(fp);
            }
            */

            if(i==-64 && j==58) {
            //if(i==64) {
               printf(" j = %5d dist = %16.8e force_constant = %16.8e x1 = %16.8e x1_0 = %16.8e F*r = %16.8e\n", j, dist, force_const, x1, x1_0, force_const * x1 * x1_0);
               //printf(" %5d  %16.8e %16.8e  %16.8e  %16.8e \n", j, ep, sig, dist, LJ_this);
               getchar();
            }

            if(strstr(des2[i], "BAS") != NULL){
              En[i][0]   += force_const * x1 * x1_0; /* Energy from F_x * r_x */
              En[i][1]   += force_const * y1 * y1_0; /* Energy from F_y * r_y */
              En[i][2]   += force_const * z1 * z1_0; /* Energy from F_z * r_z */

              En[i][3]   += force_const * z1 * y1_0; /* Energy from F_z * r_y */
              En[i][6]   += force_const * y1 * z1_0; /* Energy from F_y * r_z */

              En[i][4]   += force_const * z1 * x1_0; /* Energy from F_z * r_x */
              En[i][7]   += force_const * x1 * z1_0; /* Energy from F_x * r_z */

              En[i][5]   += force_const * y1 * x1_0; /* Energy from F_y * r_x */
              En[i][8]   += force_const * x1 * y1_0; /* Energy from F_x * r_y */
            } else if(strstr(des2[i-1], "BAS") != NULL){
              // Need to check if node i is a sidechain node. If the node is, the energy must be distributed to the backbone node.	  
              //En[i-1][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
              //En[i-1][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
              //En[i-1][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
              //En[i-1][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
              //En[i-1][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
              //En[i-1][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
            } else if(strstr(des2[i-2], "BAS") != NULL){
              //En[i-2][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
              //En[i-2][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
              //En[i-2][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
              //En[i-2][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
              //En[i-2][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
              //En[i-2][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
            } else if(strstr(des2[i-3], "BAS") != NULL){
              //En[i-3][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
              //En[i-3][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
              //En[i-3][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
              //En[i-3][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
              //En[i-3][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
              //En[i-3][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
            } else if(strstr(des2[i-4], "BAS") != NULL){
              //En[i-4][0] += force_const * x1 * x1_0; /* Energy from F_x * r_x */
              //En[i-4][1] += force_const * y1 * y1_0; /* Energy from F_y * r_y */
              //En[i-4][2] += force_const * z1 * z1_0; /* Energy from F_z * r_z */
              //En[i-4][3] += force_const * z1 * y1_0; /* Energy from F_z * r_y */
              //En[i-4][4] += force_const * z1 * x1_0; /* Energy from F_z * r_x */
              //En[i-4][5] += force_const * y1 * x1_0; /* Energy from F_y * r_x */
            } else {
              printf("something went wrong w/ LJ potential \n");
            }
          }
        }
      }
    }
  }
  //LJ_eng = LJ_eng/2;    // Overcounted by double, so need to correct
  //printf("Total Lennard Jones Potential = %12.5e \n", LJ_eng);
  //printf("Total amount of LJ interactions = %d \n", npair/2);
  //getchar();
}

