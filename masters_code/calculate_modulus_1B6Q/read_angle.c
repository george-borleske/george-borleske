#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int read_angle(int angle_nodes[][3],double angle_para2[][2],char rep2[][10],char des2[][10],char amino2[][10], int num_nodes) {

  int loop1 = 1;
  int loop2 = 1;
  int i     = 0; 
  int j     = 0;
  int len;       // length of the string read in from parameter file
  int cmp;       // results of string compare
  FILE *fp;
  char title[100];
  char str[100];
  char combine_str[100];
  char space[100] = " ";
  char space3[100] = "   ";
  double num1, num2;
  double cons83 = 83.652008;
  double cons5  = 5.9751434;
  double cons2  = 2.9875717;
  char *str1;
  char *str2;
  char *str3;
  char *str4;
  str1 = (char *) malloc(10);
  str2 = (char *) malloc(10);
  str3 = (char *) malloc(10);
  str4 = (char *) malloc(10);

  //printf("entered read_angle \n");

  /*
  ************************************************************************************************************
  * Open martini parameter file
  ************************************************************************************************************
  */
  sprintf(title, "martini-protein-angles-cos-l.par");
  fp = fopen(title, "r");
  if(fp == NULL) {
    printf("can't open martini angle parameter file! \n");
    exit(1);
  }

  
  //getchar();

  i = 0;
  strcpy(combine_str, rep2[i]);
  strcat(combine_str, space);
  strcat(combine_str, rep2[i+1]);
  //printf("rep2[i] = %s, rep2[i+1]= %s, combine_str = %s \n", rep2[i], rep2[i+1], combine_str);
  //printf("new combine_str = %s \n", strcpy(combine_str, "hi"));
  //printf("lower case of combine_str = %s \n", strlwr(combine_str));
  //printf("comparison of str and StR using strcasecmp yields %d \n", strcasecmp("str", "StR"));
  //printf("comparison of asf and qtr using strcasecmp yields %d \n", strcasecmp("asf", "qtr"));
  //printf("comparison of aqrtz and qtr using strcasecmp yields %d \n", strcasecmp("aqrtz", "qtr"));
  //getchar();



  /*
  ************************************************************************************************************
  * Read in k values and cos(equilibrium angles)
  ************************************************************************************************************
  */
  while (loop1 == 1) {
    if (angle_nodes[i][0] > num_nodes || angle_nodes[i][1] > num_nodes || angle_nodes[i][2] > num_nodes || angle_nodes[i][0] == '\0') {
      loop1 = 0;
      i    = i-1;
      //printf("last read parameters between nodes %d %d and %d \n", angle_nodes[i][0], angle_nodes[i][1], angle_nodes[i][2]);
      //printf("k value = %f, equilibrium angle = %f \n", angle_para2[i][0], angle_para2[i][1]);
      //getchar();
    } else {   
      loop2 = 1;  
      while(loop2 == 1) {
        strcpy(combine_str, rep2[angle_nodes[i][0]-1]);
        strcat(combine_str, space);
        strcat(combine_str, rep2[angle_nodes[i][1]-1]);
        strcat(combine_str, space);
        strcat(combine_str, rep2[angle_nodes[i][2]-1]);
        strcat(combine_str, space);                      // add last space to compare w/ str properly if last node is something like N0H vs N0Hp  
        if(fgets(str, 100, fp) != NULL){
          if(strstr(str, combine_str)) {
	    len = strlen(str);
            /*
	    printf("i = %d \n", i);
	    printf("nodes are %d, %d, %d \n", angle_nodes[i][0], angle_nodes[i][1], angle_nodes[i][2]);
            printf("str on line read is = %s", str);
	    printf("combine_str = %s \n", combine_str);
	    */
	    cmp = strcmp(combine_str, space3);
	    //printf("cmp = %d \n", cmp);

	    fseek(fp, -len-1, SEEK_CUR);	    
	    fscanf(fp, "%s %s %s %lf %lf %s", str1, str2, str3, &num1, &num2, str4);
	    //printf("str1 = %s num1 = %f \n", str1, num1);
	    //printf("num2 = %f \n", num2);
	    //if(i == 50) getchar();

	    if(num1 == cons2) {
	      angle_para2[i][1] = 25; // 2 * 2.9875717 kcal/mol = 25 kJ. Do this way to avoid numerical error
	    } else if(num1 == cons5) {
	      angle_para2[i][1] = 50;
	    } else if(num1 == cons83) {
              angle_para2[i][1] = 700;
	    } else {
      	      printf("something went wrong converting units from kcal to kJ \n");
	    }
	    angle_para2[i][0] = num2;

	    //printf("k-val = %f, equilbirum angle = %f \n", angle_para2[i][0], angle_para2[i][1]);
	    //getchar();

	    loop2 = 0;
	    i += 1;
	    fseek(fp, 0, SEEK_SET);
          }
  	} else{
	  loop2 = 0;
	  printf("couldn't find '%s' in parameter file \n", combine_str);
	  printf("i is %d \n", i);
	  i += 1;
	  //getchar();
	}
      }           
    
    }
  }

  //getchar();

  fclose(fp);
  return 0;
}
