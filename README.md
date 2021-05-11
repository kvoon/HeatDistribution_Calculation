# Assignment Description
As per assignment spec:

The objective is to write a program that will model the static heat distribution of a room with a
fireplace using a stencil pattern. Although a room is 3 dimensional, we will be simulating the room
with 2 dimensions. The room is 10 feet wide and 10 feet long with a fireplace along one wall as
depicted in Figure 1. The fireplace is 4 feet wide and is centered along one wall (it takes up 40% of
the wall, with 30% of the walls on either side). The fireplace emits 100◦C of heat (although in reality
a fire is much hotter). The walls are considered to be 20◦C. The boundary values (the fireplace and
the walls) are considered to be fixed temperatures. The room temperature is initialized to 20◦C.

## Running Instructions 
A Makefile is provided, simply type `make a2` to compile the code and `rm a2` to delete the executable object.

To run the code, simply type `./a2 <number from 1 to 4> <number of threads>`.

The numbers represents which version of the code to execute. 
 * 1 : Sequential 2D Calculation (Alternatively use: `make seq2D`)
 * 2 : Sequential 3D Calculation (Alternatively use: `make seq3D`)
 * 3 : Parallel 2D Calculation (Alternatively use: `make par2D`) *runs with 1,2,4,8 threads*
 * 4 : Parallel 3D Calculation (Alternatively use: `make par3D`) *runs with 1,2,4,8 threads*

Note: Different functions for each scheduling method were included in the `methods.c` file, but weren't actually used in the main method in `a2.c`. As I simply just rewrote the original function with the different schedulers and recompiled the code, and ran it manually for each test. They are there mostly to show how I rewrote the code to perfrom these tests. 

