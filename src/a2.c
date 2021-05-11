#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "methods.c"

/**
* Main runner function - set up in a way to easily run benchmarks of the different versions of the code through command line. 
*/
int main(int argc, char *argv[]){

double A[N][N][2];
double h[N][N];
double g[N][N];

init_room(g);
init_room(h);

int num_of_threads = atoi(argv[2]); 
char *a = argv[1];

omp_set_num_threads(num_of_threads); //set number of threads here

if(*a == '1'){
    //Sequential Calculation
    init_room(g);
    init_room(h);
    seq_heat_calc(h,g);
    printf("Printing with the Sequential Calculation: \n");
    print_matrix(h);

  }else if (*a == '2'){
    //Sequential Calculation with 3D Matrix
    init_room3D(A);
    seq_heat_calc3D(A);
    printf("Printing with the 3D matrix method: \n");
    print_matrix3D(A);

  }else if(*a == '3'){
    //Parallelised Calculation with 2D Matrix
    init_room(g);
    init_room(h);
    parallel_heat_calc(h,g);
    printf("Printing with the Parallelised Calculation: \n");
    print_matrix(h);

  }else if(*a == '4'){
   //Parallelised Calculation with 3D Matrix
    init_room3D(A);
    parallel_heat_calc3D(A);
    printf("Printing with the Parallelised 3D matrix method: \n");
    print_matrix3D(A);
 
} else {
  printf("Invalid Input. \n");
  printf("needs to be in the form of ./a2 <number from 1 to 4> <number of threads> \n");
  printf("Try 1 for sequential 2d, 2 for sequential 3d, 3 for parallelised 2d, 4 for parallelised 3d. \n");
  exit(0);
}

    return 0;
}