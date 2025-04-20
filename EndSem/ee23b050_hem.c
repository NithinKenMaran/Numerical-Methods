//****************************************//
/* Developer: Nithin Ken Maran            */
/* Version: 1.0                           */
/* input: One integer M.                  */
/* Output: M'th term from fibonacci series*/
//****************************************//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int hem(int);



int main(int argc, char* argv[]){
    int M = atoi(argv[1]);
    printf("%d", hem(M));

return 0;
}


int hem(int M){

    int i = M;
    while (i>2){
        return (hem(i-1)+hem(i-2));
        //hem(M) calls hem(M-1), which calls hem(M-2) and so on, till it reaches hem(2) and hem(1), which are predefined as 1 and 0.
        //It then goes back up the queue and substitutes for hem(3), hem(4), ... till hem(M)
    }

    if (i == 1){
        return 0;
    }

    if (i == 2){
        return 1;
    }

return 0;
}