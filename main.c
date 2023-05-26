/********************************
IMAGE MANIPULATION USING QUADTREE
BY: OMKAR OAK       (112103099)
    RUKMINI NAZRE   (112103098)
    VARDHAN MUNDADA (112103091)

FUNCTIONALITY: 
1.) IMAGE COMPRESSION
2.) FLIPPING OF IMAGE
3.) RED FILTER
4.) GREEN FILTER
5.) BLUE FILTER
6.) BLACK & WHITE FILTER
7.) GRAYSCALE FILTER
*********************************/
#include<stdio.h>
#include<stdlib.h>
#include "QuadTree.h"
#include "menu.h"

//COMMAND LINE ARGUEMENT:  ./main <input.ppm> <output.ppm>

int main(int argc , char *argv[])
{
    char* input_image = argv[1];
    char* output_image = argv[2];

    // Menu display
    printf("\n************  IMAGE MANIPULATION  ***************\n");
    printf("\n1. Compress image\n2. Flip image\n3. Add colour filter\n4. Black and white\n5. Grayscale\n6. Exit\n");

    MainMenu(input_image,output_image);

    printf("\n***************  COMPLETED!  ******************\n\n");

    return 0;   
}