#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "least_sq_t.c"

int elastic_mod_trans(float ***str_cau, float ***def_fms, char des2[][10], float young[], float poisson[], float shear[], int ls_size, int nframes, int num_nodes, int testnode, int start_node, int end_node, int output_trans_eng) {

int   i,j,k,t,p = 1;
char  title[100];            /* title of text output */
float LHS_t[ls_size*3];      /* Left hand side of equation when solving for engineering constants in elastic modulus of transversely isotropic material */
float mat_t[ls_size*3][4];   /* mat is the overdetermined system solving for engineering constants of trans iso material and mat^T * mat * x =  mat^T * b */
float stiff[num_nodes][6];   /* elastic modulus of whole protein */
float comp[6];               /* components of the compliance matrix */
float det;                   /* determinant of matrix */
FILE  *fp;
FILE  *f_mod;

FILE *f_eng;
sprintf(title, "node%d_eng_const.txt",testnode+1);
fp = fopen(title, "w");
fclose(fp);
f_eng = fopen(title, "a");

if(output_trans_eng){
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      sprintf(title, "node%d_trans_elas.txt",i+1);
      fp = fopen(title, "w");
      fclose(fp);
    }
  }
}

FILE *f_comp;
sprintf(title, "node_comp_%d.txt",testnode+1);
fp = fopen(title, "w");
fclose(fp);
f_comp = fopen(title, "a");
//for(t=ls_size;t<nframes;t++){
for(t=ls_size;t<nframes;t++){
  printf("t = %d \n",t);
  for(i=0;i<num_nodes;i++){
    if(strstr(des2[i], "BAS") != NULL){
      /* Shear modulus is divided by two since gamma = 2 epsilon */
      /* G = tau / (2 * epsilon) */
      shear[0] = .5 * str_cau[i][5][t] / def_fms[i][5][t];                                                   // shear modulus G 
      shear[1] = .5 * (.5 * str_cau[i][4][t] / def_fms[i][4][t] + .5 * str_cau[i][3][t] / def_fms[i][3][t]); // Take average of the two equations to compute G'
      if(i == -testnode) {
        printf("shear[0] = %f shear[1] %f \n", shear[0], shear[1]);
        printf("str_cau[i][5][t] = %f def_fms[i][5][t] = %f \n", str_cau[i][5][t], def_fms[i][5][t]);
        printf("i = %d t = %d\n",i,t);
        getchar();
      }
      j= 0;
      for(k=t-ls_size+1;k<t+1;k++) {
        /* strain[1] = a * stress[0] / (-2 * G) + b * stress[1] / (2 * G) - c * stress[2] */
        /* a = v / (1+v)    b = 1 / (1+v)   c = v' / E' */
        /* storing coefficients of a and b */ 
        mat_t[j][0] = -.5 * str_cau[i][0][k] / shear[0];
        mat_t[j][1] =  .5 * str_cau[i][1][k] / shear[0];
        mat_t[j][2] = -str_cau[i][2][k];
        mat_t[j][3] = 0;

        /* strain[0] = a * stress[1] / (-2 * G) + b * stress[0] / (2 * G) - c * stress[2] */
        mat_t[j+ls_size][0] = 1 / (-2 * shear[0]) * str_cau[i][1][k];
        mat_t[j+ls_size][1] = 1 / ( 2 * shear[0]) * str_cau[i][0][k];
	mat_t[j+ls_size][2] = -str_cau[i][2][k];
        mat_t[j+ls_size][3] = 0;

        /* strain[2] = c * (-1) * (stress[0] + stress[1]) + d * stress[2] */
        /* d = 1 / E' */
        mat_t[j+2*ls_size][0] = 0;
        mat_t[j+2*ls_size][1] = 0;
        mat_t[j+2*ls_size][2] = -1 * (str_cau[i][0][k] + str_cau[i][1][k]); // cofficient of v'/E' is -(stress_xx + stress_yy)
        mat_t[j+2*ls_size][3] = str_cau[i][2][k];                           // coefficient of 1/E' is zz component of stress

        //if(i==testnode) printf("shear[0] = %f  k = %d\n", shear[0], k);
        j++;
      }
      j = 0;
      for(k=t-ls_size+1;k<t+1;k++) { 
        /* strain[1] */
        LHS_t[j]           = def_fms[i][1][k];
        /* strain[0] */
        LHS_t[j+ls_size]   = def_fms[i][0][k];
        /* strain[2] */
        LHS_t[j+2*ls_size] = def_fms[i][2][k];
        j++;
      }
      /* Compute E and v */
      least_sq_t(mat_t,LHS_t,young,poisson,i,testnode,t,ls_size);
      young[0] = 2 * shear[0] * (1 + poisson[0]);
      if(i == -testnode) {
        printf("shear[0] = %f poisson[0] = %f \n", shear[0], poisson[0]);
        printf("young[0] = %f \n", young[0]);
        getchar();
      }

      /* Compute the components of the compliance matrix which is the inverse of the elastic modulus matrix */
      comp[0] = 1 / young[0];            // S_11 = 1 / E
      comp[1] = - poisson[0] / young[0]; // S_12 = - v / E
      comp[2] = - poisson[1] / young[1]; // S_13 = - v' / E'
      comp[3] = 1 / young[1];            // S_33 = 1 / E'
      comp[4] = 1 / shear[1];            // S_44 = 1 / G'
      comp[5] = 1 / shear[0];            // S_66 = 1 / G
      /*
      if(i == testnode) { 
        printf("Compliance matrix of node %d \n", i+1);
        printf("%f %f %f %f %f %f \n", comp[0], comp[1], comp[2], 0.0, 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", comp[1], comp[0], comp[2], 0.0, 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", comp[2], comp[2], comp[3], 0.0, 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", 0.0, 0.0, 0.0, comp[4], 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", 0.0, 0.0, 0.0, 0.0, comp[4], 0.0);
        printf("%f %f %f %f %f %f \n", 0.0, 0.0, 0.0, 0.0, 0.0, comp[5]);
        //getchar();
      }
      */
      /* determinant of the complaince matrix, det = 1 / (S_11 + S_12 - 2 * (S_13)^2 / S_33) */
      det = 1 / (comp[0] + comp[1] - 2 * powf(comp[2],2) / comp[3]);
      stiff[i][0] = (comp[0] - powf(comp[2],2) / comp[3]) / (comp[0] - comp[1]) * det;  // C_11 = (S_11 - (S_13)^2 / S_33) * det / (S_11 - S_12)
      stiff[i][1] = -(comp[1] - powf(comp[2],2) / comp[3]) / (comp[0] - comp[1]) * det; // C_12 = -(S_12 - (S_13)^2 / S_33) * det / (S_11 - S_12)
      stiff[i][2] = -1 * comp[2] / comp[3] * det;                                       // C_13 = - S_13 * det / S_33
      stiff[i][3] = (comp[0] + comp[1]) * det / comp[3];                                // C_33 = (S_11 + S_12) * det / S_33
      stiff[i][4] = 1 / comp[4];                                                        // C_44 = 1 / S_44
      stiff[i][5] = 1 / comp[5];                                                        // C_66 = 1 / S_66
      
      if(i == -testnode) { 
        printf("Stiffness matrix of node %d \n", i+1);
        printf("%f %f %f %f %f %f \n", stiff[i][0], stiff[i][1], stiff[i][2], 0.0, 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", stiff[i][1], stiff[i][0], stiff[i][2], 0.0, 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", stiff[i][2], stiff[i][2], stiff[i][3], 0.0, 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", 0.0, 0.0, 0.0, stiff[i][4], 0.0, 0.0);
        printf("%f %f %f %f %f %f \n", 0.0, 0.0, 0.0, 0.0, stiff[i][4], 0.0);
        printf("%f %f %f %f %f %f \n", 0.0, 0.0, 0.0, 0.0, 0.0, stiff[i][5]);
        getchar();
      }
      

      /* Output engineering constants and compliance matrix for testnode */
      if(i == testnode) {
        fprintf(f_eng,  "%d %f %f %f %f %f %f\n", t, young[0], young[1], poisson[0], poisson[1], shear[0], shear[1]);
        fprintf(f_comp, "%d %f %f %f %f %f %f\n", t, comp[0], comp[1], comp[2], comp[3], comp[4], comp[5]);
      }
      if(output_trans_eng) {
        sprintf(title, "node%d_trans_elas.txt",i+1);
        f_mod = fopen(title, "a");
        fprintf(f_mod,  "%d %f %f %f %f %f %f \n", t, stiff[i][0], stiff[i][1], stiff[i][2], stiff[i][3], stiff[i][4], stiff[i][5]);
        fclose(f_mod);
      }
    }
  }
}
fclose(f_eng);
fclose(f_comp);

  return 0;
}
