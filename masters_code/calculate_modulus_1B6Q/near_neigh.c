#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int near_neigh(float xyz[][10], int near_n[][2], int num_nodes) {

  printf("entered near_neigh program \n");
  getchar();

  int i=0,j=0;
  float x,y,z,dist;
  float nn_dist [num_nodes][3];    /* distance between the nearest neighbors
                                      first component is node i
			              second component is node j
				      third component is the distance between these nearest neighbors
				   */

  for(i=0;i<num_nodes;i++){
    nn_dist[i][2] = 100;           /* set the initial 'smallest distance' to something large */
    nn_dist[i][0] = i + 1;         /* increase index by since nodes start at 1 not zero */
    for(j=0;j<num_nodes;j++){
      if(i != j) {
        x = xyz[i][4] - xyz[j][4];                         /* x-component of the vector between nodes i and j */
	y = xyz[i][5] - xyz[j][5];                         /* y-component of the vector between nodes i and j */
	z = xyz[i][6] - xyz[j][6];                         /* z-component of the vector between nodes i and j */
	dist = sqrtf(powf(x,2) + powf(y,2) + powf(z,2));   /* magnitute of the vector between nodes i and j */
	printf("x = %12.5e y = %12.5e z = %12.5e dist = %12.5e \n", x, y, z, dist);
	if(dist < nn_dist[i][2]) {                         /* check to see if the current distance is less than the current smallest distance */
          nn_dist[i][1] = j + 1;                           /* update the node that is i's nearest neighbor */
	  nn_dist[i][2] = dist;                            /* update the distance between these current nearest neighbors */
	  printf("i = %d j = %d nn_dist = %12.5e dist = %12.5e \n", i, j, nn_dist[i][2], dist);
	  
	}
      }
    }
    printf("i = %d \n", i);
    printf("nearest neighbor for node i = %f, is j = %f, w/ dist = %12.5e \n", nn_dist[i][0], nn_dist[i][1], nn_dist[i][2]);
    getchar();
  }
  getchar();

  return 0;
}
