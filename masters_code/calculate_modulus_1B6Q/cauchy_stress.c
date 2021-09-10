#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "inverse.c"


int cauchy_stress(float ***dcd, float ***str_fms, float ***str_cau, float ***def_fms, float def_grad_avg[][3], float xyz0[][4], char des2[][10], int nframes, int num_nodes, int t, int testnode, int output_cau_str) {

int   i,j,g,h,k;
int   entry;                 // which component of the stresss tensor to be taken
float sum, det;
float x0_0, y0_0, z0_0, x1_0, y1_0, z1_0, x2_0, y2_0, z2_0, x3_0, y3_0, z3_0;
float x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
float multiply1[3][3];       // = F * N
float multiply2[3][3];       // = 
float multiply3[3][3];       // = F^(T) * F
float def_grad[3][3];        // Deformation gradient, F, i is testnode, i-2, i-1, i, i+1
float def_grad2[3][3];       // Deformation gradient, F, i is testnode, i-1, i, i+1, i+2
float stress_mat[3][3];      // 1st Piola Kirchoff stress
float non_sym[3][3];         // Cauchy Stress before making numerically symmetric
float cur_vec[3][3];         // current bond lengths of three bonds
float org_vec[3][3];         // original bond lengths of three bonds
                             // F * org_vec = cur_vec
float inv_org[3][3];         // inv_cur = (cur_vec)^(-1)
char  title[100];            /* title of text output */

FILE  *fp;
FILE  *f_str;
FILE  *f_def;
FILE  *F_det;
FILE  *F_comp;

int   node_0, node_1, node_2, node_3;
if(output_cau_str) {
  for(i=6;i<num_nodes-5;i++){
    if(strstr(des2[i], "BAS") != NULL){
      sprintf(title, "node%d_stress_cau.txt",i+1);
      fp = fopen(title, "w");
      fclose(fp);
      f_str = fopen(title, "a");

      sprintf(title, "node%d_strain.txt",i+1);
      fp = fopen(title, "w");
      fclose(fp);
      f_def = fopen(title, "a");
    }
  }
}
     
sprintf(title, "node%d_strain_comp.txt",testnode+1);
fp = fopen(title, "w");
fclose(fp);
F_comp = fopen(title, "a");

sprintf(title, "node%d_F_det.txt",testnode+1);
fp = fopen(title, "w");
fclose(fp);
F_det = fopen(title, "a");


//printf("nframes = %d t = %d num_nodes = %d \n", nframes, t, num_nodes);
//getchar();

for(t=0;t<nframes;t++){
  printf("t = %d stress \n", t);
  for(i=6;i<num_nodes-5;i++){
    if(strstr(des2[i], "BAS") != NULL){
      //printf("i = %d des2[i] = %s rep2[i] = %s \n", i, des2[i], rep2[i]);

      /*
      *******************************************************************************************
      * Computation of Deformation Gradient (i-2, i-1, i, i+1) *
      *******************************************************************************************
      */
      node_2 = i; // node_2 is the testnode
      
      // Find next backbone node
      if(strstr(des2[i+1], "BAS") != NULL){
        j = i + 1;
      } else if(strstr(des2[i+2], "BAS") != NULL){
        j = i + 2;
      } else if(strstr(des2[i+3], "BAS") != NULL){
        j = i + 3;
      } else if(strstr(des2[i+4], "BAS") != NULL){
        j = i + 4;
      } else if(strstr(des2[i+5], "BAS") != NULL){
        j = i + 5;
      }
      node_3 = j; // last node in chain (after testnode)

      // Find previous backbone node
      if(strstr(des2[i-1], "BAS") != NULL){
        j = i - 1;
      } else if(strstr(des2[i-2], "BAS") != NULL){
        j = i - 2;
      } else if(strstr(des2[i-3], "BAS") != NULL){
        j = i - 3;
      } else if(strstr(des2[i-4], "BAS") != NULL){
        j = i - 4;
      } else if(strstr(des2[i-5], "BAS") != NULL){
        j = i - 5;
      }
      node_1 = j; // node before testnode

      // Find first backbone node (second backbone node prior to the testnode)
      if(strstr(des2[j-1], "BAS") != NULL){
        k = j - 1;
      } else if(strstr(des2[j-2], "BAS") != NULL){
        k = j - 2;
      } else if(strstr(des2[j-3], "BAS") != NULL){
        k = j - 3;
      } else if(strstr(des2[j-4], "BAS") != NULL){
        k = j - 4;
      } else if(strstr(des2[j-5], "BAS") != NULL){
        k = j - 5;
      }
      node_0 = k; // node before testnode


      //printf("j = %d \n", j);
      /*
      if(i == testnode) {
        //printf("testnode = %d, i = %d, rep2[i] = %s \n", testnode, i, rep2[i]);
        printf("node_0 = %d node_1 = %d node_2 = %d node_3 = %d \n", node_0, node_1, node_2, node_3);
        getchar();
      }
      */
      
      /* Compute current distance between nodes */
      /* Dcd is in angrstroms so divide by 10 to get nanometers */
      /* node_2 is the node where the stress is being computed */
      x0 = (dcd[node_2][t][0] - dcd[node_0][t][0]) / 10;
      y0 = (dcd[node_2][t][1] - dcd[node_0][t][1]) / 10;
      z0 = (dcd[node_2][t][2] - dcd[node_0][t][2]) / 10;
      cur_vec[0][0] = x0;
      cur_vec[1][0] = y0;
      cur_vec[2][0] = z0;

      x1 = (dcd[node_2][t][0] - dcd[node_1][t][0]) / 10;
      y1 = (dcd[node_2][t][1] - dcd[node_1][t][1]) / 10;
      z1 = (dcd[node_2][t][2] - dcd[node_1][t][2]) / 10;
      cur_vec[0][1] = x1;
      cur_vec[1][1] = y1;
      cur_vec[2][1] = z1;

      x2 = (dcd[node_2][t][0] - dcd[node_3][t][0]) / 10;
      y2 = (dcd[node_2][t][1] - dcd[node_3][t][1]) / 10;
      z2 = (dcd[node_2][t][2] - dcd[node_3][t][2]) / 10;
      cur_vec[0][2] = x2;
      cur_vec[1][2] = y2;
      cur_vec[2][2] = z2;

      /* Compute initial distance between nodes */
      x0_0 = xyz0[node_2][1] - xyz0[node_0][1];
      y0_0 = xyz0[node_2][2] - xyz0[node_0][2];
      z0_0 = xyz0[node_2][3] - xyz0[node_0][3];
      org_vec[0][0] = x0_0;
      org_vec[1][0] = y0_0;
      org_vec[2][0] = z0_0;

      x1_0 = xyz0[node_2][1] - xyz0[node_1][1];
      y1_0 = xyz0[node_2][2] - xyz0[node_1][2];
      z1_0 = xyz0[node_2][3] - xyz0[node_1][3];
      org_vec[0][1] = x1_0;
      org_vec[1][1] = y1_0;
      org_vec[2][1] = z1_0;

      x2_0 = xyz0[node_2][1] - xyz0[node_3][1];
      y2_0 = xyz0[node_2][2] - xyz0[node_3][2];
      z2_0 = xyz0[node_2][3] - xyz0[node_3][3];
      org_vec[0][2] = x2_0;
      org_vec[1][2] = y2_0;
      org_vec[2][2] = z2_0;


      inverse(org_vec, inv_org, i, testnode);

      //if(i == testnode){printf("i = %d, j = %d, xyz0[i][2] = %f, xyz0[j][2] = %f, y1_0 = %f \n", i,j,xyz0[i][2],xyz0[j][2], y1_0); getchar();}
      
      /* F = cur_vec * (org_vec)^(-1) = cur_vec * inv_org */
      sum = 0;
      for(k=0;k<3;k++){
        for(g=0;g<3;g++){
          for(h=0;h<3;h++){
            //printf("stress_mat[h][g] = %f \n", stress_mat[h][g]);
            sum = sum + cur_vec[k][h] * inv_org[h][g];
	    //printf("sum = %12.5e k = %d g = %d h = %d \n", sum, k , g, h);
            //printf("stress_mat[h][g] = %f \n", stress_mat[h][g]);
          }
          def_grad[k][g] = sum;
          sum = 0;
        }
      }

      /*
      if(i == testnode){
        printf(" Position of nodes at orginal timestep (equilibrium) \n");
        printf(" node_0  = %16.8e %16.8e %16.8e \n", xyz0[node_0][1], xyz0[node_0][2], xyz0[node_0][3]);
        printf(" node_1  = %16.8e %16.8e %16.8e \n", xyz0[node_1][1], xyz0[node_1][2], xyz0[node_1][3]);
        printf(" node_2  = %16.8e %16.8e %16.8e \n", xyz0[node_2][1], xyz0[node_2][2], xyz0[node_2][3]);
        printf(" node_3  = %16.8e %16.8e %16.8e \n", xyz0[node_3][1], xyz0[node_3][2], xyz0[node_3][3]);
        printf("\n");	

        printf(" Position of nodes at current timestep \n");
        printf(" node_0 = %16.8e %16.8e %16.8e \n", dcd[node_0][t][0]/10, dcd[node_0][t][1]/10, dcd[node_0][t][2]/10);
        printf(" node_1 = %16.8e %16.8e %16.8e \n", dcd[node_1][t][0]/10, dcd[node_1][t][1]/10, dcd[node_1][t][2]/10);
        printf(" node_2 = %16.8e %16.8e %16.8e \n", dcd[node_2][t][0]/10, dcd[node_2][t][1]/10, dcd[node_2][t][2]/10);
        printf(" node_3 = %16.8e %16.8e %16.8e \n", dcd[node_3][t][0]/10, dcd[node_3][t][1]/10, dcd[node_3][t][2]/10);

        printf("Current Vector: \n");
        printf("%f %f %f \n", cur_vec[0][0], cur_vec[0][1], cur_vec[0][2]);
        printf("%f %f %f \n", cur_vec[1][0], cur_vec[1][1], cur_vec[1][2]);
        printf("%f %f %f \n \n", cur_vec[2][0], cur_vec[2][1], cur_vec[2][2]);

        printf("Original Vector: \n");
        printf("%f %f %f \n", org_vec[0][0], org_vec[0][1], org_vec[0][2]);
        printf("%f %f %f \n", org_vec[1][0], org_vec[1][1], org_vec[1][2]);
        printf("%f %f %f \n \n", org_vec[2][0], org_vec[2][1], org_vec[2][2]);

        printf("Inverse of Original Vector: \n");
        printf("%f %f %f \n", inv_org[0][0], inv_org[0][1], inv_org[0][2]);
        printf("%f %f %f \n", inv_org[1][0], inv_org[1][1], inv_org[1][2]);
        printf("%f %f %f \n \n", inv_org[2][0], inv_org[2][1], inv_org[2][2]);

        printf("Deformation matrix F: \n");
        printf("%f %f %f \n", def_grad[0][0], def_grad[0][1], def_grad[0][2]);
        printf("%f %f %f \n", def_grad[1][0], def_grad[1][1], def_grad[1][2]);
        printf("%f %f %f \n \n", def_grad[2][0], def_grad[2][1], def_grad[2][2]);
        getchar();	
      }
      */

      /*
      *******************************************************************************************
      * Computation of Deformation Gradient (i-1, i, i+1, i+2) *
      *******************************************************************************************
      */
      node_1 = i; // node_1 is the testnode

      // Find previous backbone node
      if(strstr(des2[i-1], "BAS") != NULL){
        j = i - 1;
      } else if(strstr(des2[i-2], "BAS") != NULL){
        j = i - 2;
      } else if(strstr(des2[i-3], "BAS") != NULL){
        j = i - 3;
      } else if(strstr(des2[i-4], "BAS") != NULL){
        j = i - 4;
      } else if(strstr(des2[i-5], "BAS") != NULL){
        j = i - 5;
      }
      node_0 = j; // node before testnode

      // Find next backbone node
      if(strstr(des2[i+1], "BAS") != NULL){
        j = i + 1;
      } else if(strstr(des2[i+2], "BAS") != NULL){
        j = i + 2;
      } else if(strstr(des2[i+3], "BAS") != NULL){
        j = i + 3;
      } else if(strstr(des2[i+4], "BAS") != NULL){
        j = i + 4;
      } else if(strstr(des2[i+5], "BAS") != NULL){
        j = i + 5;
      }
      node_2 = j; // backbone node after testnode

      // Find last backbone node (second backbone node after to the testnode)
      if(strstr(des2[j+1], "BAS") != NULL){
        k = j + 1;
      } else if(strstr(des2[j+2], "BAS") != NULL){
        k = j + 2;
      } else if(strstr(des2[j+3], "BAS") != NULL){
        k = j + 3;
      } else if(strstr(des2[j+4], "BAS") != NULL){
        k = j + 4;
      } else if(strstr(des2[j+5], "BAS") != NULL){
        k = j + 5;
      }
      node_3 = k; // node before testnode    

      /* Compute current distance between nodes */
      /* Dcd is in angrstroms so divide by 10 to get nanometers */
      /* node_1 is the node where the stress is being computed */
      x0 = (dcd[node_1][t][0] - dcd[node_0][t][0]) / 10;
      y0 = (dcd[node_1][t][1] - dcd[node_0][t][1]) / 10;
      z0 = (dcd[node_1][t][2] - dcd[node_0][t][2]) / 10;
      cur_vec[0][0] = x0;
      cur_vec[1][0] = y0;
      cur_vec[2][0] = z0;

      x1 = (dcd[node_1][t][0] - dcd[node_2][t][0]) / 10;
      y1 = (dcd[node_1][t][1] - dcd[node_2][t][1]) / 10;
      z1 = (dcd[node_1][t][2] - dcd[node_2][t][2]) / 10;
      cur_vec[0][1] = x1;
      cur_vec[1][1] = y1;
      cur_vec[2][1] = z1;

      x2 = (dcd[node_1][t][0] - dcd[node_3][t][0]) / 10;
      y2 = (dcd[node_1][t][1] - dcd[node_3][t][1]) / 10;
      z2 = (dcd[node_1][t][2] - dcd[node_3][t][2]) / 10;
      cur_vec[0][2] = x2;
      cur_vec[1][2] = y2;
      cur_vec[2][2] = z2;

      /* Compute initial distance between nodes */
      x0_0 = xyz0[node_1][1] - xyz0[node_0][1];
      y0_0 = xyz0[node_1][2] - xyz0[node_0][2];
      z0_0 = xyz0[node_1][3] - xyz0[node_0][3];
      org_vec[0][0] = x0_0;
      org_vec[1][0] = y0_0;
      org_vec[2][0] = z0_0;

      x1_0 = xyz0[node_1][1] - xyz0[node_2][1];
      y1_0 = xyz0[node_1][2] - xyz0[node_2][2];
      z1_0 = xyz0[node_1][3] - xyz0[node_2][3];
      org_vec[0][1] = x1_0;
      org_vec[1][1] = y1_0;
      org_vec[2][1] = z1_0;

      x2_0 = xyz0[node_1][1] - xyz0[node_3][1];
      y2_0 = xyz0[node_1][2] - xyz0[node_3][2];
      z2_0 = xyz0[node_1][3] - xyz0[node_3][3];
      org_vec[0][2] = x2_0;
      org_vec[1][2] = y2_0;
      org_vec[2][2] = z2_0;

      inverse(org_vec, inv_org, i, testnode);

      //if(i == testnode){printf("i = %d, j = %d, xyz0[i][2] = %f, xyz0[j][2] = %f, y1_0 = %f \n", i,j,xyz0[i][2],xyz0[j][2], y1_0); getchar();}
      
      /* F = cur_vec * (org_vec)^(-1) = cur_vec * inv_org */
      sum = 0;
      for(k=0;k<3;k++){
        for(g=0;g<3;g++){
          for(h=0;h<3;h++){
            //printf("stress_mat[h][g] = %f \n", stress_mat[h][g]);
            sum = sum + cur_vec[k][h] * inv_org[h][g];
	    //printf("sum = %12.5e k = %d g = %d h = %d \n", sum, k , g, h);
            //printf("stress_mat[h][g] = %f \n", stress_mat[h][g]);
          }
          def_grad2[k][g] = sum;
          sum = 0;
        }
      }

      /*
      if(i == testnode){

        printf(" Position of nodes at orginal timestep (equilibrium) \n");
        printf(" node_0  = %16.8e %16.8e %16.8e \n", xyz0[node_0][1], xyz0[node_0][2], xyz0[node_0][3]);
        printf(" node_1  = %16.8e %16.8e %16.8e \n", xyz0[node_1][1], xyz0[node_1][2], xyz0[node_1][3]);
        printf(" node_2  = %16.8e %16.8e %16.8e \n", xyz0[node_2][1], xyz0[node_2][2], xyz0[node_2][3]);
        printf(" node_3  = %16.8e %16.8e %16.8e \n", xyz0[node_3][1], xyz0[node_3][2], xyz0[node_3][3]);
        printf("\n");	

        printf(" Position of nodes at current timestep \n");
        printf(" node_0 = %16.8e %16.8e %16.8e \n", dcd[node_0][t][0]/10, dcd[node_0][t][1]/10, dcd[node_0][t][2]/10);
        printf(" node_1 = %16.8e %16.8e %16.8e \n", dcd[node_1][t][0]/10, dcd[node_1][t][1]/10, dcd[node_1][t][2]/10);
        printf(" node_2 = %16.8e %16.8e %16.8e \n", dcd[node_2][t][0]/10, dcd[node_2][t][1]/10, dcd[node_2][t][2]/10);
        printf(" node_3 = %16.8e %16.8e %16.8e \n", dcd[node_3][t][0]/10, dcd[node_3][t][1]/10, dcd[node_3][t][2]/10);

        printf("Current Vector: \n");
        printf("%f %f %f \n", cur_vec[0][0], cur_vec[0][1], cur_vec[0][2]);
        printf("%f %f %f \n", cur_vec[1][0], cur_vec[1][1], cur_vec[1][2]);
        printf("%f %f %f \n \n", cur_vec[2][0], cur_vec[2][1], cur_vec[2][2]);

        printf("Original Vector: \n");
        printf("%f %f %f \n", org_vec[0][0], org_vec[0][1], org_vec[0][2]);
        printf("%f %f %f \n", org_vec[1][0], org_vec[1][1], org_vec[1][2]);
        printf("%f %f %f \n \n", org_vec[2][0], org_vec[2][1], org_vec[2][2]);

        printf("Inverse of Original Vector: \n");
        printf("%f %f %f \n", inv_org[0][0], inv_org[0][1], inv_org[0][2]);
        printf("%f %f %f \n", inv_org[1][0], inv_org[1][1], inv_org[1][2]);
        printf("%f %f %f \n \n", inv_org[2][0], inv_org[2][1], inv_org[2][2]);

        printf("2nd Deformation matrix F: \n");
        printf("%f %f %f \n", def_grad2[0][0], def_grad2[0][1], def_grad2[0][2]);
        printf("%f %f %f \n", def_grad2[1][0], def_grad2[1][1], def_grad2[1][2]);
        printf("%f %f %f \n \n", def_grad2[2][0], def_grad2[2][1], def_grad2[2][2]);
        getchar();	
      }	
      */

      /* Compute Average of the two deformation gradient matrices */
      for(k=0;k<3;k++){
        for(g=0;g<3;g++){
          def_grad_avg[k][g] = .5 * (def_grad[k][g] + def_grad2[k][g]);
        }
      }

      if(i == testnode) {
        fprintf(F_comp, "%f %f %f %f %f %f %f %f %f \n", def_grad_avg[0][0], def_grad_avg[0][1], def_grad_avg[0][2], def_grad_avg[1][0], def_grad_avg[1][1], def_grad_avg[1][2], def_grad_avg[2][0], def_grad_avg[2][1], def_grad_avg[2][2]);
      }

      /* Compute Green-Lagrangian Strain Tensor = .5 * (F^(T) * F - I) */
      // F^(T) * F
      sum = 0;
      for(k=0;k<3;k++){
        for(g=0;g<3;g++){
          for(h=0;h<3;h++){
            //printf("stress_mat[h][g] = %f \n", stress_mat[h][g]);
            sum = sum + def_grad_avg[h][k] * def_grad_avg[h][g];
          }
          multiply3[k][g] = sum;
          sum = 0;
        }
      }  

      // F^(T) * F - I
      multiply3[0][0] -= 1;
      multiply3[1][1] -= 1;
      multiply3[2][2] -= 1;

      /*
      ************************************************************************************************************
      * Store Green-Lagrangian Strain 
      ************************************************************************************************************
      */
      /* Make Cauchy Stress symmetric: tensor = 1/2 * (s + s^(T)), Since the tensor is symmetric, only need to store 6 instead of 9 components */
      def_fms[i][0][t] = multiply3[0][0] * .5; // xx
      def_fms[i][1][t] = multiply3[1][1] * .5; // yy
      def_fms[i][2][t] = multiply3[2][2] * .5; // zz
      def_fms[i][3][t] = multiply3[1][2] * .5; // yz
      def_fms[i][4][t] = multiply3[0][2] * .5; // xz
      def_fms[i][5][t] = multiply3[0][1] * .5; // xy


      if(i == -testnode){
        printf("Deformation matrix F: \n");
        printf("%f %f %f \n", def_grad_avg[0][0], def_grad_avg[0][1], def_grad_avg[0][2]);
        printf("%f %f %f \n", def_grad_avg[1][0], def_grad_avg[1][1], def_grad_avg[1][2]);
        printf("%f %f %f \n \n", def_grad_avg[2][0], def_grad_avg[2][1], def_grad_avg[2][2]);

        printf("Strain = .5 * (F^(T) * F - I): \n");
        printf("%f %f %f \n", def_fms[i][0][t],  def_fms[i][5][t], def_fms[i][4][t]);
        printf("%f %f %f \n",  def_fms[i][5][t], def_fms[i][1][t], def_fms[i][3][t]);
        printf("%f %f %f \n \n", def_fms[i][4][t], def_fms[i][3][t], def_fms[i][2][t]);
        getchar();
      }

      /* Nominal Stress in matrix form (r x F) */
      /* Matrix is of the form :
       * rx,Fx rx,Fy rx,Fz
       * ry,Fx ry,Fy ry,Fz
       * rz,Fx rz,Fy rz,Fz */
      stress_mat[0][0] = str_fms[i][0][t]; // rx,Fx
      //printf("str_fms[i][0][t] = %f i = %d \n", str_fms[i][0][t], i);
      //printf("stress_mat[0][0] = %f \n", stress_mat[0][0]);
      stress_mat[0][1] = str_fms[i][5][t]; // rx,Fy
      stress_mat[0][2] = str_fms[i][4][t]; // rx,Fz

      stress_mat[1][0] = str_fms[i][8][t]; // ry,Fx
      stress_mat[1][1] = str_fms[i][1][t]; // ry,Fy
      stress_mat[1][2] = str_fms[i][3][t]; // ry,Fz

      stress_mat[2][0] = str_fms[i][7][t]; // rz,Fx
      //printf("str_fms[i][7][t] = %f \n", str_fms[i][7][t]);
      stress_mat[2][1] = str_fms[i][6][t]; // rz,Fy
      stress_mat[2][2] = str_fms[i][2][t]; // rz,Fz

      /* Cauchy Stress = 1/det(F) * F * N */
      /* F * N = Deformation gradiant multiplied by Nominal stress */
      sum = 0;
      for(k=0;k<3;k++){
        for(g=0;g<3;g++){
          for(h=0;h<3;h++){
            //printf("stress_mat[h][g] = %f \n", stress_mat[h][g]);
            sum = sum + def_grad_avg[k][h] * stress_mat[h][g];
	    //printf("sum = %12.5e k = %d g = %d h = %d \n", sum, k , g, h);
            //printf("stress_mat[h][g] = %f \n", stress_mat[h][g]);
          }
          multiply1[k][g] = sum;
          sum = 0;
        }
      }  

      /* Determinant:
       * | a00 a01 a02 |
       * | a10 a11 a12 |
       * | a20 a21 a22 |
       * =  a00 * (a11 * a22 - a12 * a21)
       *  - a01 * (a10 * a22 - a12 * a20)
       *  + a02 * (a10 * a21 - a11 * a20) */
      det = 0;
      det =  def_grad_avg[0][0] * (def_grad_avg[1][1] * def_grad_avg[2][2] - def_grad_avg[1][2] * def_grad_avg[2][1]);
      det += def_grad_avg[0][1] * (def_grad_avg[1][0] * def_grad_avg[2][2] - def_grad_avg[1][2] * def_grad_avg[2][0]);
      det += def_grad_avg[0][2] * (def_grad_avg[1][0] * def_grad_avg[2][1] - def_grad_avg[1][1] * def_grad_avg[2][0]);
      //if(i == testnode) {printf("det = %f i = %d, t = %d \n", det, i, t); getchar();}
      
      if(i == testnode) {
        fprintf(F_det, "%f \n", det);
      }

      /* Compute 1/det(F) * F * N */
      for(j=0;j<3;j++){
        for(k=0;k<3;k++){
          non_sym[j][k] = multiply1[j][k] / det;
        }
      }

      /* Cauchy Stress. i is node, j is component of stress tensor, t is timestep */ 
//if((str_cau = (float***) malloc(num_nodes * sizeof(float**))) == NULL) {

      entry = 0;
      /* Make Cauchy Stress symmetric: tensor = 1/2 * (s + s^(T)) */
      for(j=0;j<3;j++){
        for(k=0;k<3;k++){
          str_cau[i][entry][t] = .5 * (non_sym[j][k] + non_sym[k][j]);
          //printf("entry = %d \n", entry);
          entry += 1;
        }
      }

      /*
      if(i == testnode){
        printf("Deformation matrix F: \n");
        printf("%f %f %f \n", def_grad[0][0], def_grad[0][1], def_grad[0][2]);
        printf("%f %f %f \n", def_grad[1][0], def_grad[1][1], def_grad[1][2]);
        printf("%f %f %f \n \n", def_grad[2][0], def_grad[2][1], def_grad[2][2]);

        printf("2nd Deformation matrix F: \n");
        printf("%f %f %f \n", def_grad2[0][0], def_grad2[0][1], def_grad2[0][2]);
        printf("%f %f %f \n", def_grad2[1][0], def_grad2[1][1], def_grad2[1][2]);
        printf("%f %f %f \n \n", def_grad2[2][0], def_grad2[2][1], def_grad2[2][2]);

        printf("Average of the two Deformations matrices F: \n");
        printf("%f %f %f \n", def_grad_avg[0][0], def_grad_avg[0][1], def_grad_avg[0][2]);
        printf("%f %f %f \n", def_grad_avg[1][0], def_grad_avg[1][1], def_grad_avg[1][2]);
        printf("%f %f %f \n \n", def_grad_avg[2][0], def_grad_avg[2][1], def_grad_avg[2][2]);
      
        printf("Nominal Stress matrix N: \n");
        printf("%f %f %f \n", stress_mat[0][0], stress_mat[0][1], stress_mat[0][2]);
        printf("%f %f %f \n", stress_mat[1][0], stress_mat[1][1], stress_mat[1][2]);
        printf("%f %f %f \n \n", stress_mat[2][0], stress_mat[2][1], stress_mat[2][2]);

        printf("Multiplication F * N: \n");
        printf("%f %f %f \n", multiply1[0][0], multiply1[0][1], multiply1[0][2]);
        printf("%f %f %f \n", multiply1[1][0], multiply1[1][1], multiply1[1][2]);
        printf("%f %f %f \n \n", multiply1[2][0], multiply1[2][1], multiply1[2][2]);

        printf("Non_symmetric Cauchy Stress matrix, 1/det(F) * F * N: \n");
        printf("%f %f %f \n", non_sym[0][0], non_sym[0][1], non_sym[0][2]);
        printf("%f %f %f \n", non_sym[1][0], non_sym[1][1], non_sym[1][2]);
        printf("%f %f %f \n \n", non_sym[2][0], non_sym[2][1], non_sym[2][2]);

        printf("Symmetric Cauchy Stress matrix, .5 * (s^(T) + s): \n");
        printf("%f %f %f \n", str_cau[i][0][t], str_cau[i][1][t], str_cau[i][2][t]);
        printf("%f %f %f \n", str_cau[i][3][t], str_cau[i][4][t], str_cau[i][5][t]);
        printf("%f %f %f \n \n", str_cau[i][6][t], str_cau[i][7][t], str_cau[i][8][t]);	
        getchar();
      }
      */

      /* Output Cauchy stress of testnode into text file. Units are Giga Pascals */
      if(output_cau_str) {
        if(strstr(des2[i], "BAS") != NULL){
          sprintf(title, "node%d_stress_cau.txt",i+1);
          f_str = fopen(title, "a");
          fprintf(f_str,  "%d %f %f %f %f %f %f \n", t, str_cau[i][0][t], str_cau[i][1][t], str_cau[i][2][t], 
             str_cau[i][3][t], str_cau[i][4][t], str_cau[i][5][t]);
          fclose(f_str);
        }
      }
      /* Output strain of testnode into text file. */
      if(output_cau_str) {
        if(strstr(des2[i], "BAS") != NULL){
          sprintf(title, "node%d_strain.txt",i+1);
          f_def = fopen(title, "a");
          fprintf(f_def,  "%d %f %f %f %f %f %f \n", t, def_fms[i][0][t], def_fms[i][1][t], def_fms[i][2][t], 
             def_fms[i][3][t], def_fms[i][4][t], def_fms[i][5][t]);
          fclose(f_def);
        }
      }
    }
  }
}

fclose(F_det);
fclose(F_comp);


  return 0;
}
