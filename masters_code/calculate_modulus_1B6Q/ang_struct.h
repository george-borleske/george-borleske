

typedef struct ang_struct{

  char  ***rep_h;
  float *k_a;
  float *eq_ang;
  float *trig;

  /* Representations of the three bonded backbone nodes */
  /*
  if ((rep_h = (float**) malloc(3 * sizeof(float*))) == NULL){
    printf("Error: malloc fails at first part of rep_h \n"); 
    printf("Program is being paused: ");
    getchar();
  }
  for (i=0;i<3;i++){
    if ((rep_h[i] = (float*) malloc(10000 * sizeof(float))) == NULL){
      printf("Error: malloc fails at second part of rep_h \n");
      printf("Program is being paused: ");
      getchar();
    }
  }

  if ((k_a = (float*) malloc(10000 * sizeof(float))) == NULL){
    printf("Error: malloc fails at k_a \n"); 
    printf("Program is being paused: ");
    getchar();
  }

  if ((trig = (float*) malloc(10000 * sizeof(float))) == NULL){
    printf("Error: malloc fails at k_a \n"); 
    printf("Program is being paused: ");
    getchar();
  }
  */

}  ang_struct;





