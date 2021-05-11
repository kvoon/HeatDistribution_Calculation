#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 100
#define T 5000
#define WALL_TEMP 20
#define FIREPLACE_TEMP 100 

/**
* Default sequential heat distribution calculations provided in the spec sheet.
* @param double h[N][N] - used to represent a 2D room as a matrix 
* @param dobule g[N][N] - used to store the newly computed values of the proints from the old values.
*/
void seq_heat_calc(double h[N][N], double g[N][N]){
	
double start = omp_get_wtime(); //start time measurement

for (int iteration = 0; iteration < T; iteration++)
{

    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {
    
            g[i][j] = 0.25 * (h[i - 1][j] + h[i + 1][j]
            + h[i][j - 1] + h[i][j + 1]);

        }
    }
/* update points */
    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N-1; j++) {
            h[i][j] = g[i][j];
        }
    }
}
double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);
}


/**
* Default sequential heat distribution calculations provided in the spec sheet - modified to handle a single 3D array to avoid unnecessary points updating
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void seq_heat_calc3D(double A[N][N][2]){
	
double start = omp_get_wtime(); // start time measurement 

for (int iteration = 0; iteration < T; iteration++)
{

    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

			// Updating points using the extra dimension instead of an additional 2D matrix. 
            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}

double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);
}


/**
* Default heat distribution calculations provided in the spec sheet - parallelised using omp 
* @param double h[N][N] - used to represent a 2D room as a matrix 
* @param dobule g[N][N] - used to store the newly computed values of the proints from the old values.
*/
void parallel_heat_calc(double h[N][N], double g[N][N]){
	
double start = omp_get_wtime(); 

for (int iteration = 0; iteration < T; iteration++)
{
	
#pragma omp parallel for
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {
    
            g[i][j] = 0.25 * (h[i - 1][j] + h[i + 1][j]
            + h[i][j - 1] + h[i][j + 1]);

        }
    }
	
/* update points */
    for (int i = 1; i < N-1; i++) {
        for (int j = 1; j < N-1; j++) {
            h[i][j] = g[i][j];
        }
    }
}

double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);

}


/**
* Heat distribution calculations using a 3D Array parallelised with omp (default)
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void parallel_heat_calc3D(double A[N][N][2]){
	
double start = omp_get_wtime();  //start time measurement

for (int iteration = 0; iteration < T; iteration++)
{
	
#pragma omp parallel for 
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}

double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);

}


/**
* Heat distribution calculations using a 3D Array parallelised with omp (static scheduling, chunk-size 1)
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void parallel_heat_calc3D_static1(double A[N][N][2]){
	
double start = omp_get_wtime(); 

for (int iteration = 0; iteration < T; iteration++)
{
#pragma omp parallel for schedule(static,1)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}

double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);
}

/**
* Heat distribution calculations using a 3D Array parallelised with omp (static scheduling, chunk-size 4)
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void parallel_heat_calc3D_static4(double A[N][N][2]){
	
double start = omp_get_wtime(); 

for (int iteration = 0; iteration < T; iteration++)
{
	
#pragma omp parallel for schedule(static,4)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}

double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);

}


/**
* Heat distribution calculations using a 3D Array parallelised with omp (static scheduling, chunk-size 8)
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void parallel_heat_calc3D_static8(double A[N][N][2]){
	
double start = omp_get_wtime(); 

for (int iteration = 0; iteration < T; iteration++)
{
#pragma omp parallel for schedule(static,8)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}

double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);
}

/**
* Heat distribution calculations using a 3D Array parallelised with omp (dynamic scheduling, chunk-size 1)
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void parallel_heat_calc3D_dynamic1(double A[N][N][2]){
	
double start = omp_get_wtime(); 

for (int iteration = 0; iteration < T; iteration++)
{
#pragma omp parallel for schedule(dynamic,1)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}

double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);
}

/**
* Heat distribution calculations using a 3D Array parallelised with omp (dynamic scheduling, chunk-size 4)
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void parallel_heat_calc3D_dynamic4(double A[N][N][2]){
	
double start = omp_get_wtime(); //start time measurement

for (int iteration = 0; iteration < T; iteration++)
{
#pragma omp parallel for schedule(dynamic,4)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}
double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);
}

/**
* Heat distribution calculations using a 3D Array parallelised with omp (dynamic scheduling, chunk-size 8)
* @param double A[N][N][2] - used to represent a 2D room as a matrix, 3rd dimension is used to store the updated values
* e.g. A[N][N][1] stores the calculated points, A[N][N][0] is updated with the values from A[N][N][1]
*/
void parallel_heat_calc3D_dynamic8(double A[N][N][2]){
	
double start = omp_get_wtime(); //start time measurement

for (int iteration = 0; iteration < T; iteration++)
{
#pragma omp parallel for schedule(dynamic,8)
    for (int i = 1; i < N-1; i++) {
        for (int j = 1;j < N-1; j++) {

            if(iteration%2 == 0){

            A[i][j][1] = 0.25 * (A[i - 1][j][0] + A[i + 1][j][0]
            + A[i][j - 1][0] + A[i][j + 1][0]);

            }

            else {

            A[i][j][0] = 0.25 * (A[i - 1][j][1] + A[i + 1][j][1]
            + A[i][j - 1][1] + A[i][j + 1][1]);
    
            }

        }
    }

}
double end = omp_get_wtime(); //end time measurement

printf("Time of computation: %f seconds \n", end-start);
}


/**
* Function is used to initialise an empty room for the 3D Array 
*/
void init_room3D(double A[N][N][2]){

for (int i = 0; i < N; i++) {
     
    for (int j = 0;j < N; j++) {
		
		
			// Initialise room with default wall temperature (20 degrees)
            A[i][j][0] = WALL_TEMP;
            A[i][j][1] = WALL_TEMP;

            if(i == 0){
			
			// Initialise the top middle wall of the room with the default fireplace temperature
                if(j >= N*0.3 && j<N*0.7){

                    A[i][j][0] = FIREPLACE_TEMP;
                    A[i][j][1] = FIREPLACE_TEMP;

                }
            }
            }

        }

}

/**
* Function is used to initialise an empty room for the 2D Array 
*/
void init_room(double a[N][N]){

for (int i = 0; i < N; i++) {
     
    for (int j = 0;j < N; j++) {
           
			// Initialise room with default wall temperature (20 degrees)		   
            a[i][j] = WALL_TEMP;

            if(i == 0){

			// Initialise the top middle wall of the room with the default fireplace temperature
                if(j >= N*0.3 && j<N*0.7){

                    a[i][j] = FIREPLACE_TEMP;

                }
            }
            }

        }
}

/**
* Function used to print a scaled down 10x10 version of the 3D matrix to command line 
*/
void print_matrix3D(double A[N][N][2]){

for (int i = 0; i <10; i++) {
	
 printf("\n");
 
    for (int j = 0;j < 10; j++) { 
		
        printf("%.3f\t",A[i*10][j*10][0]);
            
    }
}
        printf("\n");

}

/**
* Function used to print a scaled down 10x10 version of the 2D matrix to command line 
*/
void print_matrix(double h[N][N]){

for (int i = 0; i <10; i++) {
	
 printf("\n");
 
    for (int j = 0; j <10; j++) { 

        printf("%.3f\t",h[i*10][j*10]);
            
    }
}
        printf("\n");

}
