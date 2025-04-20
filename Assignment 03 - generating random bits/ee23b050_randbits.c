#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <math.h>



int N;
int seed;
int hamdist=0;
char* file1;
char* file2;
time_t t;


int main(int argc, char **argv) {

    char bitstream[100];
    FILE *fout;
    
    int option;

    while ((option = getopt(argc, argv, "n:s:th")) != -1) {

    //"n:s:th" cuz n and s need arguments, but t and h don't. 

    //actually h does need arguments, but im not using optarg for case 'h'.
    //instead of optarg im using optind++ to get argv arguments after the -h flag


        switch (option) { 
            case 'n':
                N = atoi(optarg);

                break;
        
            case 's':
                seed = atoi(optarg);

                

                srand((unsigned)seed); //giving the input seed for rand()


                for (int i=0; i<N; i++) {
                    if (rand()%2==0){
                        char digit = '1';
                       bitstream[i]=digit;

                       
                    }

                    else {
                        char digit = '0';
                      bitstream[i]=digit;
                    }
                }

                fout = fopen("randbits.txt", "w"); 
                
                fprintf(fout,"%s", bitstream);

                fclose(fout);
                break;
        
            case 't':
                seed = time(&t);

                srand((unsigned)seed);

                for (int i=0; i<N; i++) {
                    if (rand()%2==0){
                        char digit = '1';
                       bitstream[i]=digit;
                    }

                    else {
                        char digit = '0';
                      bitstream[i]=digit;
                    }
                }

                fout = fopen("randbits.txt", "w"); 
                
                fprintf(fout,"%s", bitstream);

                fclose(fout);


                
                break;
        
            case 'h':
                file1 = argv[optind]; //first argument after '-h'
                file2 = argv[optind + 1]; //second argument after '-h'

                char bitstream1[1000];  //initializing all variables
                char bitstream2[1000];
                int len1;
                int len2;

                FILE* fin1;
                FILE* fin2;

                fin1 = fopen(file1, "r");
                fin2 = fopen(file2, "r");

                fscanf(fin1, "%s", bitstream1); //reading bitstream from file1
                fscanf(fin2, "%s", bitstream2); //reading bitstream from file2
            

                len1 = strlen(bitstream1);
                len2 = strlen(bitstream2);



                if (len1<=len2){ 
                    for (int i=1; i<=len1; i++) {
                        if (bitstream1[i]!=bitstream2[i]) { 
                //cuz hamming distance = number of DIFFERENT bits
                            hamdist+=1;
                        }
                    }
                }

                else {

                    for (int i=1; i<=len2; i++) {
                        if (bitstream1[i]!=bitstream2[i]){
                            hamdist += 1;
                        }   
                    }

                }
                printf("hamming distance is %d", hamdist);

                break;
          
        }
    }
    return 0;
}
