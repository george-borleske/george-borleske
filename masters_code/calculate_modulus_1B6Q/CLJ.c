#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <math.h>
//#include "dcdfile.h"

float CLJ(char rep2[][10], int i, int j, float* sig){
  //printf("entered CLJ \n");
  float ep=0;

if(rep2[i][0] == 'C'){
          //printf("node 1 is C type \n");
          if(rep2[i][1] == '5'){
            *sig=.47;
            //printf("node 1 is C5 type \n");
            if(rep2[j][0] == 'Q'){
              //printf("node 2 is type Q \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type QDA \n");
                  ep=3.1;
                } else {
                  //printf("node 2 is type QD \n");
                  ep=3.1;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type QA \n");
                ep=3.1;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type Q0 \n");
                ep=3.1;
              } else {
                printf("something when wrong, node 2 is Q something type \n");
              }
            } else if(rep2[j][0] == 'P'){
              if(rep2[j][1]=='5'){
                //printf("node 2 is type P5 \n");
                ep=3.1;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type P4 \n");
                ep=3.1;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type P3 \n");
                ep=3.5;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type P2 \n");
                ep=3.5;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type P1 \n");
                ep=3.5;
              } else{
                printf("something when wrong, node 2 is P something type \n");
              }
            } else if(rep2[j][0] == 'N'){
              //printf("node 2 is type N \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type NDA \n");
                  ep=3.5;
                } else {
                  //printf("node 2 is type ND \n");
                  ep=3.5;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type NA \n");
                ep=3.5;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type N0 \n");
                ep=3.5;
              } else {
                printf("something when wrong, node 2 is N something type \n");
              }
            } else if(rep2[j][0] == 'C'){
              if(rep2[j][1]=='5'){
                //printf("node 2 is type C5 \n");
                ep=3.5;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type C4 \n");
                ep=3.5;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type C3 \n");
                ep=3.5;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type C2 \n");
                ep=3.1;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type C1 \n");
                ep=3.1;
              } else{
                printf("something when wrong, node 2 is C something type \n");
              }
            }
/*@@@@*/
          } else if(rep2[i][1] == '4'){
            *sig=.47;
            //printf("node 1 is C4 type \n");
            if(rep2[j][0] == 'Q'){
              //printf("node 2 is type Q \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type QDA \n");
                  ep=2.7;
                } else {
                  //printf("node 2 is type QD \n");
                  ep=2.7;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type QA \n");
                ep=2.7;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type Q0 \n");
                ep=2.7;
              } else {
                printf("something when wrong, node 2 is Q something type \n");
              }
            } else if(rep2[j][0] == 'P'){
              if(rep2[j][1]=='5'){
                //printf("node 2 is type P5 \n");
                ep=2.7;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type P4 \n");
                ep=2.7;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type P3 \n");
                ep=3.1;
              } else if(rep2[j][1]=='2'){
               // printf("node 2 is type P2 \n");
                ep=3.5;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type P1 \n");
                ep=3.5;
              } else{
                printf("something when wrong, node 2 is P something type \n");
              }
            } else if(rep2[j][0] == 'N'){
              //printf("node 2 is type N \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type NDA \n");
                  ep=3.1;
                } else {
                 // printf("node 2 is type ND \n");
                  ep=3.1;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type NA \n");
                ep=3.1;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type N0 \n");
                ep=3.5;
              } else {
                printf("something when wrong, node 2 is N something type \n");
              }
            } else if(rep2[j][0] == 'C'){
              if(rep2[j][1]=='5'){
                //printf("node 2 is type C5 \n");
                ep=3.5;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type C4 \n");
                ep=3.5;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type C3 \n");
                ep=3.5;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type C2 \n");
                ep=3.1;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type C1 \n");
                ep=3.1;
              } else{
                printf("something when wrong, node 2 is C something type \n");
              }
            }
/*@@@@*/
          } else if(rep2[i][1] == '3'){
            *sig=.47;
            //printf("node 1 is C3 type \n");
            if(rep2[j][0] == 'Q'){
              //printf("node 2 is type Q \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type QDA \n");
                  ep=2.3;
                } else {
                  //printf("node 2 is type QD \n");
                  ep=2.3;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type QA \n");
                ep=2.3;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type Q0 \n");
                ep=2.3;
              } else {
                printf("something when wrong, node 2 is Q something type \n");
              }
            } else if(rep2[j][0] == 'P'){
              if(rep2[j][1]=='5'){
                //printf("node 2 is type P5 \n");
                ep=2.7;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type P4 \n");
                ep=2.7;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type P3 \n");
                ep=3.1;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type P2 \n");
                ep=3.1;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type P1 \n");
                ep=3.5;
              } else{
                printf("something when wrong, node 2 is P something type \n");
              }
            } else if(rep2[j][0] == 'N'){
              //printf("node 2 is type N \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type NDA \n");
                  ep=2.7;
                } else {
                  //printf("node 2 is type ND \n");
                  ep=2.7;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type NA \n");
                ep=2.7;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type N0 \n");
                ep=3.5;
              } else {
                printf("something when wrong, node 2 is N something type \n");
              }
            } else if(rep2[j][0] == 'C'){
              if(rep2[j][1]=='5'){
                //printf("node 2 is type C5 \n");
                ep=3.5;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type C4 \n");
                ep=3.5;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type C3 \n");
                ep=3.5;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type C2 \n");
                ep=3.5;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type C1 \n");
                ep=3.5;
              } else{
                printf("something when wrong, node 2 is C something type \n");
              }
            }
/*@@@@*/
          } else if(rep2[i][1] == '2'){
           // printf("node 1 is C2 type \n");
            if(rep2[j][0] == 'Q'){
              *sig=.62; 
              //printf("node 2 is type Q \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type QDA \n");
                  ep=2.0;
                } else {
                  //printf("node 2 is type QD \n");
                  ep=2.0;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type QA \n");
                ep=2.0;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type Q0 \n");
                ep=2.0;
              } else {
                printf("something when wrong, node 2 is Q something type \n");
              }
            } else if(rep2[j][0] == 'P'){
              *sig=.47;
              if(rep2[j][1]=='5'){
                //printf("node 2 is type P5 \n");
                ep=2.3;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type P4 \n");
                ep=2.3;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type P3 \n");
                ep=2.7;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type P2 \n");
                ep=2.7;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type P1 \n");
                ep=3.1;
              } else{
                printf("something when wrong, node 2 is P something type \n");
              }
            } else if(rep2[j][0] == 'N'){
              *sig=.47;
              //printf("node 2 is type N \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type NDA \n");
                  ep=2.7;
                } else {
                  //printf("node 2 is type ND \n");
                  ep=2.7;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type NA \n");
                ep=2.7;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type N0 \n");
                ep=3.1;
              } else {
                printf("something when wrong, node 2 is N something type \n");
              }
            } else if(rep2[j][0] == 'C'){
              *sig=.47;
              if(rep2[j][1]=='5'){
                //printf("node 2 is type C5 \n");
                ep=3.1;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type C4 \n");
                ep=3.1;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type C3 \n");
                ep=3.5;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type C2 \n");
                ep=3.5;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type C1 \n");
                ep=3.5;
              } else{
                printf("something when wrong, node 2 is C something type \n");
              }
            }
/*@@@@*/
          } else if(rep2[i][1] == '1'){
            //printf("node 1 is C1 type \n");
            if(rep2[j][0] == 'Q'){
              *sig=.62;
              //printf("node 2 is type Q \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type QDA \n");
                  ep=2.0;
                } else {
                  //printf("node 2 is type QD \n");
                  ep=2.0;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type QA \n");
                ep=2.0;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type Q0 \n");
                ep=2.0;
              } else {
                printf("something when wrong, node 2 is Q something type \n");
              }
            } else if(rep2[j][0] == 'P'){
              *sig=.47;
              if(rep2[j][1]=='5'){
                //printf("node 2 is type P5 \n");
                ep=2.0;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type P4 \n");
                ep=2.0;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type P3 \n");
                ep=2.3;
              } else if(rep2[j][1]=='2'){
                //printf("node 2 is type P2 \n");
                ep=2.3;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type P1 \n");
                ep=2.7;
              } else{
                printf("something when wrong, node 2 is P something type \n");
              }
            } else if(rep2[j][0] == 'N'){
              *sig=.47;
              //printf("node 2 is type N \n");
              if(rep2[j][1] == 'D'){
                if(rep2[i][2] == 'A'){
                  //printf("node 2 is type NDA \n");
                  ep=2.7;
                } else {
                  //printf("node 2 is type ND \n");
                  ep=2.7;
                }
              } else if(rep2[j][1] == 'A'){
                //printf("node 2 is type NA \n");
                ep=2.7;
              } else if(rep2[j][1] == '0'){
                //printf("node 2 is type N0 \n");
                ep=2.7;
              } else {
                printf("something when wrong, node 2 is N something type \n");
              }
            } else if(rep2[j][0] == 'C'){
              *sig=.47;
              if(rep2[j][1]=='5'){
                //printf("node 2 is type C5 \n");
                ep=3.1;
              } else if(rep2[j][1]=='4'){
                //printf("node 2 is type C4 \n");
                ep=3.1;
              } else if(rep2[j][1]=='3'){
                //printf("node 2 is type C3 \n");
                ep=3.5;
              } else if(rep2[j][1]=='2'){
               // printf("node 2 is type C2 \n");
                ep=3.5;
              } else if(rep2[j][1]=='1'){
                //printf("node 2 is type C1 \n");
                ep=3.5;
              } else{
                printf("something when wrong, node 2 is C something type \n");
              }
            }
          }//subscript (first letter)
/*@@@@*/
        }

//printf("end of clj \n");
  return ep;
}
