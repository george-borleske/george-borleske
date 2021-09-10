#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "least_sq_i.c"

int elastic_mod_iso(float ***str_cau, float ***def_fms, char des2[][10], float young[], float poisson[], float shear[], int ls_size, int nframes, int num_nodes, int testnode, int output_iso_eng) {

int   i,j,k,t;
char  title[100];            /* title of text output */
float LHS_i[ls_size*3];      /* Left hand side of equation when solving for engineering constants in elastic modulus of isotropic material */
float mat_i[ls_size*3][2];   /* mat is the overdetermined system solving for engineering constants of isotropic material and mat^T * mat * x =  mat^T * b */

printf("Entered elastic_mod_iso.c \n");

FILE  *fp;
if(output_iso_eng) {
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      sprintf(title, "node%d_eng_const_iso.txt",i+1);
      fp = fopen(title, "w");
      fclose(fp);
    }
  }
}

FILE *f_eng;
//f_eng = fopen(title, "a");
for(t=ls_size;t<nframes;t++){
//for(t=ls_size;t<0;t++){
  printf("t = %d \n",t);
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      //printf("i = %d t = %d \n",i,t);
      /* Shear modulus, G, is divided by two since gamma = 2 epsilon */
      /* G = tau / (2 * epsilon) */
      // Take average of the three equations to compute G'
      shear[0] = (.5 * str_cau[i][5][t] / def_fms[i][5][t] + .5 * str_cau[i][4][t] / def_fms[i][4][t] + .5 * str_cau[i][3][t] / def_fms[i][3][t]) / 3;
      if(i== -testnode) {
        printf("shear = %f \n", shear[0]);
        printf("str_fms[i][3][t] = %f def_fms[i][3][t] = %f \n", str_cau[i][3][t], def_fms[i][3][t]);
        printf("str_fms[i][4][t] = %f def_fms[i][4][t] = %f \n", str_cau[i][5][t], def_fms[i][4][t]);
        printf("str_fms[i][5][t] = %f def_fms[i][5][t] = %f \n", str_cau[i][5][t], def_fms[i][5][t]);
        printf("i = %d t = %d\n",i,t);
        getchar();
      }
      j= 0;
      for(k=t-ls_size+1;k<t+1;k++) {
        /* strain[0] = a * stress[0] + b * (-stress[1] - stress[2]) */
        /* a = 1 / E    b = v / E */
        /* storing coefficients of a and b */ 
        mat_i[j][0] =  str_cau[i][0][k];
        mat_i[j][1] = -str_cau[i][1][k] - str_cau[i][2][k];

        /* strain[1] = a * stress[1] + b * (-stress[0] - stress[2]) */
        //mat_i[j+ls_size][0] =  str_cau[i][1][k];
        //mat_i[j+ls_size][1] = -str_cau[i][0][k] - str_cau[i][2][k];
        mat_i[j+ls_size][0] = 0;
        mat_i[j+ls_size][1] = 0;

        /* strain[2] = a * stress[2] + b * (-stress[0] - stress[1]) */
        //mat_i[j+2*ls_size][0] =  str_cau[i][2][k];
        //mat_i[j+2*ls_size][1] = -str_cau[i][0][k] - str_cau[i][1][k];
        mat_i[j+2*ls_size][0] = 0;
        mat_i[j+2*ls_size][1] = 0;
        //if(i==testnode) printf("shear[0] = %f  k = %d\n", shear[0], k);
        j++;
      }
      j = 0;
      for(k=t-ls_size+1;k<t+1;k++) { 
        /* strain[0] */
        LHS_i[j]           = def_fms[i][0][k];
        /* strain[1] */
        //LHS_i[j+ls_size]   = def_fms[i][1][k];
        LHS_i[j+ls_size]   = 0;
        /* strain[2] */
        //LHS_i[j+2*ls_size] = def_fms[i][2][k];
        LHS_i[j+2*ls_size] = 0;
        j++;
      }
      /* Compute E and v */
      least_sq_i(mat_i,LHS_i,young,poisson,i,testnode,t,ls_size);
      if(i == -testnode) {
        printf("shear[0] = %f poisson[0] = %f young[0] = %f \n", shear[0], poisson[0], young[0]);
        getchar();
      }
      
      /* Output engineering constants of every node */
      if(output_iso_eng) {
        sprintf(title, "node%d_eng_const_iso.txt",i+1);
        f_eng = fopen(title, "a");
        fprintf(f_eng,  "%d %f %f %f %f \n", t, young[0], poisson[0], shear[0], young[0]/(2+2*poisson[0]));
        fclose(f_eng);
      }
      /*
      if(i == testnode) {
        fprintf(f_eng,  "%d %f %f %f %f \n", t, young[0], poisson[0], shear[0], young[0]/(2+2*poisson[0]));
      }
      */
    }
  }
}

  return 0;
}
