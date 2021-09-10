#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "ang_struct.h"


int anglevalue(int angle_nodes[][3], double angle_para[][2], char rep2[][10], char des2[][10], char amino2[][10], int num_nodes) {

  int   i, j, temp;
  int   loop1     = 1;
  int   loop2     = 1;
  int   count     = 0;           // tracks how many node combinations there are
  int   ang_count = 0;        // number of angle bonds
  char  str[100];              // place to store a line read in from the parameter file
  float k_a;                   // force constant of the angle bond
  float eq_ang;                // equillibrium angle, in degrees
  char *str1;                  // representation of the first of the three nodes bonded together
  str1 = (char *) malloc(10);
  char *str2;
  str2 = (char *) malloc(10);
  char *str3;
  str3 = (char *) malloc(10);
  char *trig;
  trig = (char *) malloc(10);

  //printf("entered anglevalue.c\n");

  ang_struct ang_info;
  if ((ang_info.rep_h = (char***) malloc(60000 * sizeof(float**))) == NULL){
    printf("Error: malloc fails at first part of rep_h \n"); 
    printf("Program is being paused: ");
    getchar();
  }
  for (i=0;i<60000;i++){
    if ((ang_info.rep_h[i] = (char**) malloc(3 * sizeof(float*))) == NULL){
      printf("Error: malloc fails at second part of rep_h \n");
      printf("Program is being paused: ");
      getchar();
    }
  }
  for (i=0;i<60000;i++){
    for (j=0;j<3;j++){
      if ((ang_info.rep_h[i][j] = (char*) malloc(10 * sizeof(float))) == NULL){
        printf("Error: malloc fails at second part of rep_h \n");
        printf("Program is being paused: ");
        getchar();
      }
    }
  }

  if ((ang_info.k_a = (float*) malloc(60000 * sizeof(float))) == NULL){
    printf("Error: malloc fails at k_a \n"); 
    printf("Program is being paused: ");
    getchar();
  }

  if ((ang_info.eq_ang = (float*) malloc(60000 * sizeof(float))) == NULL){
    printf("Error: malloc fails at eq_ang \n"); 
    printf("Program is being paused: ");
    getchar();
  }

  if ((ang_info.trig = (float*) malloc(60000 * sizeof(float))) == NULL){
    printf("Error: malloc fails at k_a \n"); 
    printf("Program is being paused: ");
    getchar();
  }
  char ang_name[100];
  sprintf(ang_name, "martini-protein-angles-cos-u.par");

  /*
  ************************************************************************************************************
  * Open angle parameter file
  ************************************************************************************************************
  */
  FILE *fp;
  fp = fopen(ang_name, "r");
  if (fp == NULL) {
    printf("Can't open angle parameter file!\n");
    printf("file name is %s \n", ang_name);
    exit(1);
  }

  //printf("opened angle parameter file \n");
  //getchar();

  // Ignore first few lines before angle parameter data
  for (i=0;i<9;i++) {
    fgets(str, 100, fp);
    //printf("%s", str);
    //getchar();
  }

  while (loop1 == 1) {
    temp = fscanf(fp, "%s %s %s %f %f %s", str1, str2, str3, &k_a, &eq_ang, trig);
    /*
    printf("temp = %d \n", temp);
    printf("%s | %s | %s | %f | %f | %s |", str1, str2, str3, k_a, ang, trig);
    getchar(); 
    */
    if (temp != 6) {
      loop1 = 0;
      //printf("%s | %s | %s | %f | %f | %s |", str1, str2, str3, k_a, eq_ang, trig);
      //getchar();
    } else {
      strncpy(ang_info.rep_h[count][0], str1, 5);
      strncpy(ang_info.rep_h[count][1], str2, 5);
      strncpy(ang_info.rep_h[count][2], str3, 5);
      ang_info.k_a[count] = k_a * 4.184 * 2;      // convert units from kilocalories to kilojoules. The database halves the value of the parameter for the simulation.
      ang_info.eq_ang[count] = eq_ang;            // units in degrees
      /*
      if(count % 1000 == 0) {
        printf("%d %s %s %s %f %f \n", count, ang_info.rep_h[count][0], ang_info.rep_h[count][1], ang_info.rep_h[count][2], ang_info.k_a[count], ang_info.eq_ang[count]);
        //getchar();
      }
      */
      count++;
    }

    //printf("count = %d \n", count);
  }

  fclose(fp);
  //printf("finished loop, count = %d \n", count);
  count = count - 1;
  //printf("last line is: \n");
  /*
  for(i=count;i>count-5;i--){
    printf("%d %s %s %s %f %f \n", i, ang_info.rep_h[i][0], ang_info.rep_h[i][1], ang_info.rep_h[i][2], ang_info.k_a[i], ang_info.eq_ang[i]);
  }
  printf("\n %d %s %s %s %f %f \n", count, ang_info.rep_h[count][0], ang_info.rep_h[count][1], ang_info.rep_h[count][2], ang_info.k_a[count], ang_info.eq_ang[count]);
  getchar();
  */



  while (loop2 == 1) {
    //printf("entered while loop\n");
    if (angle_nodes[ang_count][0] > num_nodes || angle_nodes[ang_count][1] > num_nodes || angle_nodes[ang_count][2] > num_nodes || angle_nodes[ang_count][0] == '\0') {
      loop2     = 0;
      ang_count = ang_count - 1;
      //printf("ended while loop, ang_count = %d \n", ang_count);
      //printf("%s %d \n", rep2[angle_nodes[ang_count][0]-1], angle_nodes[ang_count][0]);
      //printf("last read parameters were between nodes %s ( %d ), %s ( %d ), %s ( %d )\n", rep2[angle_nodes[ang_count][0]-1], angle_nodes[ang_count][0], rep2[angle_nodes[ang_count][1]-1], angle_nodes[ang_count][1], rep2[angle_nodes[ang_count][2]-1], angle_nodes[ang_count][2]);
      //printf("with a angle value of %d and k value of %f at angle number %f \n", ang_count+1, angle_para[ang_count][1], angle_para[ang_count][0]);
      
      //printf("\n\n");
      //printf("second to last read parameters were between nodes %s ( %d ), %s ( %d ), %s ( %d )\n", rep2[angle_nodes[ang_count-1][0]-1], angle_nodes[ang_count-1][0], rep2[angle_nodes[ang_count-1][1]-1], angle_nodes[ang_count-1][1], rep2[angle_nodes[ang_count-1][2]-1], angle_nodes[ang_count-1][2]);
      //printf("with a angle value of %d and k value of %f at angle number %f \n", ang_count, angle_para[ang_count-1][1], angle_para[ang_count-1][0]);
      //getchar();
    } else {

      /* angle between 3 backbone nodes */
      /* reads parameters directly from .par file since they are different from the paper */
      if(strstr(des2[angle_nodes[ang_count][0]-1], "BAS") != NULL && strstr(des2[angle_nodes[ang_count][1]-1], "BAS") != NULL && strstr(des2[angle_nodes[ang_count][2]-1], "BAS") != NULL){
        //printf("entered backbone only if statement \n");
        //getchar();
        for(i=0;i<count+1;i++) {
          if(strcmp(rep2[angle_nodes[ang_count][0]-1], ang_info.rep_h[i][0]) == 0) {
            if(strcmp(rep2[angle_nodes[ang_count][1]-1], ang_info.rep_h[i][1]) == 0) {
              //printf("i = %d \n", i);
              if(strcmp(rep2[angle_nodes[ang_count][0]-1], ang_info.rep_h[i][2]) == 0) {
                angle_para[ang_count][0] = ang_info.eq_ang[i];
                angle_para[ang_count][1] = ang_info.k_a[i];
                if(ang_count > 700) {
                  printf(" i = %d \n", i);
                  printf("angle_nodes[ang_count][0] = %d \n", angle_nodes[ang_count][0]);
		  //getchar();

                  printf(" i = %d \n", i);
                  printf("%s %s %s \n", ang_info.rep_h[i][0], ang_info.rep_h[i][1], ang_info.rep_h[i][2]);
                  printf("ang_count = %d, '%s', '%s', '%s' \n", ang_count, rep2[angle_nodes[ang_count][0]-1], rep2[angle_nodes[ang_count][1]-1], rep2[angle_nodes[ang_count][2]-1]);
                  j = i;
                  i = count + 2;
                }
              }
            }
          }
        }

        if(ang_count > 700) {
          printf("\n\n ang_count = %d, '%s', '%s', '%s' \n", ang_count, rep2[angle_nodes[ang_count][0]-1], rep2[angle_nodes[ang_count][1]-1], rep2[angle_nodes[ang_count][2]-1]);
          printf("j = %d, ang_para[][0] = %lf ang_para[][1] = %lf \n", j, angle_para[ang_count][0], angle_para[ang_count][1]);
          getchar();
        }

      /* angle between 2 backbone nodes and 1 sidechain node */
      } else if(strstr(des2[angle_nodes[ang_count][0]-1], "BAS") != NULL && strstr(des2[angle_nodes[ang_count][1]-1], "BAS") != NULL && strstr(des2[angle_nodes[ang_count][2]-1], "SI") != NULL){
        angle_para[ang_count][0]=100;
        angle_para[ang_count][1]=25;
      } else if(strstr(des2[angle_nodes[ang_count][0]-1], "BAS") != NULL && strstr(des2[angle_nodes[ang_count][1]-1], "SI") != NULL && strstr(des2[angle_nodes[ang_count][2]-1], "SI") != NULL){
        if (strstr(amino2[angle_nodes[ang_count][0]-1], "LYS")){
          angle_para[ang_count][0]=180;
          angle_para[ang_count][1]=25;
        } else if (strstr(amino2[angle_nodes[ang_count][0]-1], "ARG")){
          angle_para[ang_count][0]=180;
          angle_para[ang_count][1]=25;
        } else if (strstr(amino2[angle_nodes[ang_count][0]-1], "HIS")){
          angle_para[ang_count][0]=150;
          angle_para[ang_count][1]=50;
//@@@@@@@@@@@@ not sure if HSD should be considered HIS
        } else if (strstr(amino2[angle_nodes[ang_count][0]-1], "HSD")){
          angle_para[ang_count][0]=150;
          angle_para[ang_count][1]=50;
        } else if (strstr(amino2[angle_nodes[ang_count][0]-1], "TYR")){
          angle_para[ang_count][0]=150;
          angle_para[ang_count][1]=50;
        } else if (strstr(amino2[angle_nodes[ang_count][0]-1], "PHE")){
          angle_para[ang_count][0]=150;
          angle_para[ang_count][1]=50;
        } else if (strstr(amino2[angle_nodes[ang_count][0]-1], "TRP")){
          angle_para[ang_count][0]=90;
          angle_para[ang_count][1]=50;
        }
      } else {
        printf("problem occurred between nodes %d, %d, and %d \n",angle_nodes[ang_count][0],angle_nodes[ang_count][1], angle_nodes[ang_count][2]);
        printf("ang_count is: %d \n", ang_count);
        getchar();
      }
    }
    ang_count = ang_count + 1;
  }
  return 0;
}
