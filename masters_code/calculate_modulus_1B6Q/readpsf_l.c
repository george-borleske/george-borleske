#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int readpsf_l(char rep2[][10], char des2[][10], char amino2[][10], float mass2[], float charge2[], int bond_nodes[][2], int angle_nodes[][3], int dihedral_nodes[][4]) {

  int loop1 = 1;
  int loop2 = 1;
  int i     = 0;
  int j;
  int k;
  int temp;
  int temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9;
  int num1, num2, num3;
  int numnodes;
  double charge, mass;

  //char str1[10], amino[10], des[10], rep[10];
  char *str1;
  str1 = (char *) malloc(10);
  char *amino;
  amino = (char *) malloc(10);
  char *des;
  des = (char *) malloc(10);
  char *rep;
  rep = (char *) malloc(10);

  char str[100];
  int w;
  int r=0;
  int q=0;
  //int ch;
  //int p;
  
  /*
  ************************************************************************************************************
  * Open psf file
  ************************************************************************************************************
  */
  FILE *fp;
  fp = fopen("CG-fix-1B6Q-l.psf", "r");
  if (fp == NULL) {
    printf("Can't open input file psf file!\n");
    exit(1);
  }

  /*
  ************************************************************************************************************
  * Read in parameters of each node, including representation, description, name of amino acid, mass, and charge
  ************************************************************************************************************
  */
  while (loop1==1) {
    if(fgets(str, 100, fp) != NULL) {
      if (strstr(str, "natom")){
        //printf("found it\n");
	//printf("loop2 = %d \n", loop2);
	//getchar();
        loop1=0;
        while (loop2==1){
          temp = fscanf(fp, "%d %s %d %s %s %s %lf %lf %d", &num1, str1, &num2, amino, des, rep, &charge, &mass, &num3);
	  //printf("temp = %d \n",temp);
          if (9 == temp && strcmp(str1, "p1") == 0){
            /*
            strcpy(rep2[i], rep);
            strcpy(des2[i], des);
            strcpy(amino2[i], amino);
            */
            strncpy(rep2[i], rep, 5);
            strncpy(des2[i], des, 4);
            strncpy(amino2[i], amino, 4);  
            mass2[i]=mass;
            charge2[i]=charge;
            
	    /*
            printf("%d %s %s %s %lf %lf \n",i+1,amino2[i],des2[i],rep2[i],charge2[i],mass2[i]);
	    getchar();
            if(mass2[0] != 72){
              int random;
              printf("i is %d \n",i);
              printf("Program is being paused: ");
              scanf("%d", &random);
            }
            */
            i=i+1;
          } else if (9 == temp && strcmp(str1, "p2") == 0){
            /*
            strcpy(rep2[i], rep);
            strcpy(des2[i], des);
            strcpy(amino2[i], amino);
            */
            strncpy(rep2[i], rep, 5);
            strncpy(des2[i], des, 4);
            strncpy(amino2[i], amino, 4);  
            mass2[i]=mass;
            charge2[i]=charge;
            //printf("%d %s %s %s %lf %lf \n",i+1,amino2[i],des2[i],rep2[i],charge2[i],mass2[i]);
            //printf("%d %s %s %s %lf %lf \n",i+1,amino,des,rep,charge,mass);
            //printf("%d %s %s %s %lf %lf \n \n",i,amino2[i-1],des2[i-1],rep2[i-1],charge2[i-1],mass2[i-1]);
            i=i+1;
          } else {            
            loop2=0;
            i=i-1;
            /*
            printf("%s\n",rep2[i]);
            printf("%d\n", i);
            printf("%d\n", temp);
            printf("mass is %f \n",mass2[i]);
            printf("charge is %f \n",charge2[i]);
            printf("%s\n",rep2[i-1]);
            */
          }
	}
      }
    } else {
      printf("couldn't find nodes in psf file \n");
      exit(1);
    }
  }

/*
  printf("in readpsf \n");
  for(i=0;i<10;i++){
    printf("%d %s %s %s %lf %lf \n",i+1,amino2[i],des2[i],rep2[i],charge2[i],mass2[i]);
  } 
  int random;
  printf("Program is being paused: ");
  scanf("%d", &random);
*/

  numnodes = i+1;
  //printf("numnodes is %d \n", numnodes);
  //printf("i is %d \n", i);

  /*
  ************************************************************************************************************
  * Read which nodes are bonded
  ************************************************************************************************************
  */
  //printf("%s\n", str);
  rewind(fp);
  i     = -1;
  loop1 = 1;
  loop2 = 0;
  temp  = 8;
  while (loop1 == 1) {
    if(fgets(str, 100, fp) == NULL) {
      loop1 = 0;
      if(loop2 == 0) {
        printf("couldn't find bonds \n");
      }
    } else {
      //printf("fgets returns: %s \n",str);
      if (strstr(str, "nbond")) {
        loop2 = 1;
        //printf("%s\n", "found the angles");
        while (temp == 8){
          temp = fscanf(fp, "%d %d %d %d %d %d %d %d", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &temp7, &temp8);
          if (temp == 8){
            i = i + 1;
            bond_nodes[i][0] = temp1;
            bond_nodes[i][1] = temp2;
            i = i + 1;
            bond_nodes[i][0] = temp3;
            bond_nodes[i][1] = temp4;
            i = i + 1;
            bond_nodes[i][0] = temp5;
            bond_nodes[i][1] = temp6;
            i = i + 1;
            bond_nodes[i][0] = temp7;
            bond_nodes[i][1] = temp8;
          } else {
            i = i +1;
            loop1 = 0;
            switch (temp - 1) {
              case 0:
                i = i - 1;
                break;
              case 2:
                bond_nodes[i][0] = temp1;
                bond_nodes[i][1] = temp2;
                //printf("%d %d\n", temp1, temp2);
                break;
              case 4:
                bond_nodes[i][0] = temp1;
                bond_nodes[i][1] = temp2;
                i = i + 1;
                bond_nodes[i][0] = temp3;
                bond_nodes[i][1] = temp4;
                //printf("%d %d %d %d\n", temp1, temp2, temp3, temp4);
                break;
              case 6:
                bond_nodes[i][0] = temp1;
                bond_nodes[i][1] = temp2;
                i = i + 1;
                bond_nodes[i][0] = temp3;
                bond_nodes[i][1] = temp4;
                i = i + 1;
                bond_nodes[i][0] = temp5;
                bond_nodes[i][1] = temp6;
                //printf("%d %d %d %d %d %d\n", temp1, temp2, temp3, temp4, temp5, temp6);
                break;
              case 8:
                bond_nodes[i][0] = temp1;
                bond_nodes[i][1] = temp2;
                i = i + 1;
                bond_nodes[i][0] = temp3;
                bond_nodes[i][1] = temp4;
                i = i + 1;
                bond_nodes[i][0] = temp5;
                bond_nodes[i][1] = temp6;
                i = i + 1;
                bond_nodes[i][0] = temp7;
                bond_nodes[i][1] = temp8;
                //printf("%d %d %d %d %d %d %d %d\n", temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8);
                break;
            }
          }
        }
      } 
    }
  }


/*
  for(i=0;i<75;i++){
    printf("bonds are: %d %d \n",bond[i][0], bond[i][1]);
  }
*/
/*
  printf("%d\n", temp);
  printf("%d %d %d %d %d %d %d %d\n", temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8);
  printf("Number of bonds: %d\n\n", i+1);
*/

  /*
  ************************************************************************************************************
  * Read which nodes form angles
  ************************************************************************************************************
  */
  rewind(fp);
  i     = -1;
  loop1 = 1;
  temp  = 9;
  loop2 = 0;
  while (loop1 == 1) {
    if(fgets(str, 100, fp) == NULL) {
      loop1 = 0;
      if(loop2 == 0) {
        printf("couldn't find angles \n");
      }
    } else {
      //printf("fgets returns: %s \n",str);
      if (strstr(str, "ntheta")) {
        loop2 = 1;
        //printf("%s\n", "found the angles");
        while (temp == 9){
          temp = fscanf(fp, "%d %d %d %d %d %d %d %d %d", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &temp7, &temp8, &temp9);
          if (temp == 9){
            i = i + 1;
            angle_nodes[i][0] = temp1;
            angle_nodes[i][1] = temp2;
            angle_nodes[i][2] = temp3;
            i = i + 1;
            angle_nodes[i][0] = temp4;
            angle_nodes[i][1] = temp5;
            angle_nodes[i][2] = temp6;
            i = i + 1;
            angle_nodes[i][0] = temp7;
            angle_nodes[i][1] = temp8;
            angle_nodes[i][2] = temp9;
          } else {
            i = i +1;
            loop1 = 0;
            switch (temp - 1) {
              case 0:
                i = i - 1;
                break;
              case 3:
                angle_nodes[i][0] = temp1;
                angle_nodes[i][1] = temp2;
                angle_nodes[i][2] = temp3;
                //printf("%d %d %d\n", temp1, temp2, temp3);
                break;
              case 6:
                angle_nodes[i][0] = temp1;
                angle_nodes[i][1] = temp2;
                angle_nodes[i][2] = temp3;
                i = i + 1;
                angle_nodes[i][0] = temp4;
                angle_nodes[i][1] = temp5;
                angle_nodes[i][2] = temp6;
                //printf("%d %d %d %d %d %d\n", temp1, temp2, temp3, temp4, temp5, temp6);
                break;
            }
          }
        }
      }
    }
  }

/*
  for(i=0;i<75;i++){
    printf("angles are: %d %d %d \n",angle[i][0], angle[i][1], angle[i][2]);
  }
*/


/*
  printf("%d\n", temp);
  printf("%d %d %d %d %d %d %d %d %d\n", temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9);
  printf("Number of angles: %d\n\n", i+1);
*/

  /*
  ************************************************************************************************************
  * Read which nodes form dihedral angles
  ************************************************************************************************************
  */
  rewind(fp);
  i     = -1;
  loop1 = 1;
  loop2 = 0;
  temp  = 8;
  while (loop1 == 1) {
    if(fgets(str, 100, fp) == NULL) {
      loop1 = 0;
      if(loop2 == 0) {
        printf("couldn't find dehedrals \n");
      }
    } else {
      //printf("fgets returns: %s \n",str);
      if (strstr(str, "nphi")) {
        loop2 = 1;
        //printf("%s\n", "found the dihedrals");
        while (temp == 8){
          temp = fscanf(fp, "%d %d %d %d %d %d %d %d", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6, &temp7, &temp8);
          if (temp == 8){
            i = i + 1;
            dihedral_nodes[i][0] = temp1;
            dihedral_nodes[i][1] = temp2;
            dihedral_nodes[i][2] = temp3;
            dihedral_nodes[i][3] = temp4;
            i = i + 1;
            dihedral_nodes[i][0] = temp5;
            dihedral_nodes[i][1] = temp6;
            dihedral_nodes[i][2] = temp7;
            dihedral_nodes[i][3] = temp8;
          } else {
            i = i +1;
            loop1 = 0;
            switch (temp - 1) {
              case 0:
                i = i - 1;
                break;
              case 4:
                dihedral_nodes[i][0] = temp1;
                dihedral_nodes[i][1] = temp2;
                dihedral_nodes[i][2] = temp3;
                dihedral_nodes[i][3] = temp4;
               // printf("%d %d %d %d\n", temp1, temp2, temp3, temp4);
                break;
              case 8:
                dihedral_nodes[i][0] = temp1;
                dihedral_nodes[i][1] = temp2;
                dihedral_nodes[i][2] = temp3;
                dihedral_nodes[i][3] = temp4;
                i = i + 1;
                dihedral_nodes[i][0] = temp5;
                dihedral_nodes[i][1] = temp6;
                dihedral_nodes[i][2] = temp7;
                dihedral_nodes[i][3] = temp8;
                //printf("%d %d %d %d %d %d %d %d\n", temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8);
                break;
            }
          }
        }
      }
    }
  }


/*
  for(i=0;i<75;i++){
    printf("dihedrals are: %d %d %d %d \n",dihedral[i][0], dihedral[i][1], dihedral[i][2], dihedral[i][3]);
  }
*/

  
/*
  printf("%d\n", temp);
  printf("%d %d %d %d %d %d %d %d\n", temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8);
  printf("Number of dihedrals: %d\n\n", i+1);
*/

  fclose(fp);
  free(str1);
  free(des);
  free(amino);
  free(rep);

  return 0;
}
