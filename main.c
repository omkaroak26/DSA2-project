#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "qt.h"

int main(int argc , char *argv[])
{

    int Height , Width , max_no_of_colour , i ,j ,threshold ;
    
    //   for compression  use  ---- ./quadtree -c threshold < file_name .ppm format > < file output .out format >
    
    if(strcmp(argv[1],"-c")==0)
    {
        colour_pixel **mat;

        FILE *fp=fopen(argv[3],"rb");

        char mag_id[3];             //stores the magic PPM identifier (P3 or P6)
        
        //threshold is inversely proportional to file size
        //threshold is inversely proportional to number of nodes
        threshold=atoi(argv[2]);    //   atoi converts string to  int
        
        fscanf(fp,"%2s",mag_id);
        mag_id[2]='\0';

        fscanf(fp,"%d",&Height);
        fscanf(fp,"%d",&Width);    //height = width (always for sqaure image)
        fscanf(fp,"%d",&max_no_of_colour);

        //creating matrix of size  H x W of type colour_pixel

        mat=(colour_pixel**)malloc(Height*sizeof(colour_pixel*));

        for(i=0;i<Height;i++)
        {
            mat[i]=(colour_pixel*)malloc(Width*sizeof(colour_pixel));
        }
        
        //  blank matrix is created.......   Now we need to fill the matrix from ppm file.

        for(i=0;i<Height;i++)
        {
            for(j=0;j<Width;j++)
            {
                //fread = pointer, sizeof 1 element, number of elements to read, read from pointer
                fread(&mat[i][j].R , sizeof(unsigned char),1,fp);
                fread(&mat[i][j].G , sizeof(unsigned char),1,fp);
                fread(&mat[i][j].B , sizeof(unsigned char),1,fp);
            }
        }
        fclose(fp);

        //converting the matrix data into  quadtree and compressing it 
        
        Quad_Node *root=NULL;
        int no_of_colour=0, no_of_nodes=0 ;   //no_of_colour, no_of_nodes = global variables

       // printf("%d %d %d ",mat[55][10].R,mat[55][10].G,mat[55][10].B);
        Compression(&root,0,0,Width,mat,threshold,&no_of_colour,&no_of_nodes);
        
        //printf("no_of_colour -- %d  ----- no_of_nodes -- %d ", no_of_colour,no_of_nodes);

        int x,y,l;
 		x = y =0;
		l = Width;

        //  converting our quadtree to our matirx

        create_matrix(root,mat,x,y,l,&no_of_colour ,no_of_nodes);
        create_image(mat,Width,max_no_of_colour,argv[4]);
        del_Matrix(mat,Height);
        del_tree(root);
    }
    
    if(strcmp(argv[1],"-m") == 0){
        colour_pixel **mat;
        int mirror;
        if(strcmp(argv[2],"h")==0)
            mirror=1;
        else if(strcmp(argv[2],"v")==0)
            mirror=2;
        else
            mirror=0;
        
        threshold=atoi(argv[3]);

        FILE *fp=fopen(argv[4],"rb"); 

        char mag_id[3];
		fscanf(fp,"%2s",mag_id);
		mag_id[2]='\0';
		fscanf(fp, "%d", &Height);
    	fscanf(fp, "%d", &Width);
    	fscanf(fp, "%d", &max_no_of_colour);
    	char c;
    	fscanf(fp,"%c",&c);  

    	mat = malloc(Height * sizeof(colour_pixel*));
		for(i = 0; i < Height; i++)
			mat[i] = malloc(Width*sizeof(colour_pixel));

		for(i = 0; i < Height; i++){
			for(j = 0; j < Width; j++)
				fread(&mat[i][j], sizeof(colour_pixel), 1, fp);
		}
		fclose(fp); 

        Quad_Node *root=NULL;
        int no_of_colour=0, no_of_nodes=0;
		int x,y,l;

        CreateQuadTree(&root,0,0,Width,mat,&no_of_colour,&no_of_nodes);

        if (mirror==1)
        {
            Horizontal_flip(&root);
        }
        else if (mirror==2)
        {
            Vertical_flip(&root);
        }


		x = y =0;
		l = Width; 

        create_matrix(root,mat,x,y,l,&no_of_colour ,no_of_nodes);
        create_image(mat,Width,max_no_of_colour,argv[5]);
        del_Matrix(mat,Height);
        del_tree(root);
        
    }

    if(strcmp(argv[1],"-a") == 0){
		
		int colour;

		if(strcmp(argv[2],"red") == 0)
			colour = 1; 

		else if(strcmp(argv[2],"green") == 0)
			colour = 2; 

		else if(strcmp(argv[2],"blue")==0)
			colour = 3;  

		else if(strcmp(argv[2],"grey")==0)
			colour = 4;  

		else if(strcmp(argv[2],"black_white")==0)
			colour = 5;  

		else
			colour = 0;	

        Quad_Node *root1=NULL;
        colour_pixel **mat1;
        int Height1 , Width1;
        threshold=atoi(argv[3]);

        FILE *fp=fopen(argv[4],"rb");
        char mag_id[3];
        fscanf(fp, "%2s", mag_id);
		mag_id[2]= '\0';
		fscanf(fp, "%d", &Height1);
		fscanf(fp, "%d", &Width1);
		fscanf(fp, "%d", &max_no_of_colour);
		char c;
		fscanf(fp,"%c",&c);

		mat1 = malloc(Height1 * sizeof(colour_pixel*));
		for(i = 0; i < Height1; i++)
		{
            mat1[i] = malloc(Width1 * sizeof(colour_pixel));
        }

		for(i = 0; i < Height1; i++)
        {
			for(j = 0; j < Width1; j++)
            {
                fread(&mat1[i][j], sizeof(colour_pixel), 1, fp);
            }
		}
        fclose(fp);

        int no_of_colour=0, no_of_nodes=0 ;
        int x=0 , y=0 , L;
        L=Width1;

        CreateQuadTree(&root1,0,0,Width1,mat1,&no_of_colour,&no_of_nodes);
        
        if(colour==1){
            red(root1,mat1,x,y,L);
        }

        else if(colour==2){
            green(root1,mat1,x,y,L);
        }

        else if(colour==3){
            blue(root1,mat1,x,y,L);
        }

        else if(colour==4){
            grey(root1,mat1,x,y,L);
        }

        else if(colour==5){
            black_white(root1,mat1,x,y,L);
        }
        else{
            printf("Your selected choice is wrong");
            return 0;
        }

		create_image(mat1, Width1, max_no_of_colour, argv[5]);
		del_Matrix(mat1, Width1);
		del_tree(root1);
    }

    return 0;    
}
