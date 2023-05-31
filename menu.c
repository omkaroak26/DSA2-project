#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "QuadTree.h"

void MainMenu(char* input_image,char* output_image)
{
    int Height , Width , max_no_of_colour, i, j;
                                
    // Choice variable
    int choice = -1, c1=-1, c2=-1;
             
    while(choice!=6)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        
        if(choice == 1)
        {
        	int threshold = 1;
            printf("Enter Threshold: ");
            scanf("%d",&threshold);
            colour_pixel **mat;

            FILE *fp=fopen(input_image,"rb");

            char mag_id[3];             //stores the magic PPM identifier (P3 or P6)
            
            //threshold is inversely proportional to file size
            //threshold is inversely proportional to number of nodes
            
            fscanf(fp,"%2s",mag_id);
            mag_id[2]='\0';

            fscanf(fp,"%d",&Height);
            fscanf(fp,"%d",&Width);    //height = width (always for square image)
            fscanf(fp,"%d",&max_no_of_colour);
		
		
		char c;
		fscanf(fp,"%c",&c);
			
		//creating matrix of size  H x W of type colour_pixel

		mat=malloc(Height*sizeof(colour_pixel *));

		for(i=0;i<Height;i++){
		    mat[i]=malloc(Width*sizeof(colour_pixel));
		}
		
		//  blank matrix is created.......   Now we need to fill the matrix from ppm file.

		for(i=0;i<Height;i++){
		    for(j=0;j<Width;j++){
		    	//fread = pointer, sizeof 1 element, number of elements to read, read from pointer
		        fread(&mat[i][j].R , sizeof(unsigned char),1,fp);
		        fread(&mat[i][j].G , sizeof(unsigned char),1,fp);
		        fread(&mat[i][j].B , sizeof(unsigned char),1,fp);
		    }
		}
		fclose(fp);


		//converting the matrix data into  quadtree and compressing it 
		
		Quad_Node *root=NULL;
		int no_of_colour=0, no_of_nodes=0;   //no_of_colour, no_of_nodes = global variables

		Compression(&root,0,0,Width,Width,mat,threshold,&no_of_colour,&no_of_nodes);
		
		printf("no_of_colour -- %d  ----- no_of_nodes -- %d ", no_of_colour,no_of_nodes);
		// no_of_colour -- 12632904  ----- no_of_nodes -- 101672


		int x=0,y=0;

		//converting our quadtree to our matirx
		create_matrix(root,mat,x,y,Width,&no_of_colour ,no_of_nodes);
		create_image(mat,Width,Width,max_no_of_colour,output_image);
		del_Matrix(mat,Height);
		del_tree(root);

            return;
        }

        else if (choice == 2)
        {
            printf("1. Horizontal flip\n2. Vertical flip\n Enter your choice: ");
            scanf("%d",&c1);
            if(c1!=1 && c1!=2)
            {
                printf("Invalid input\n");
                return;
            }
            
            FILE *fp=fopen(input_image,"rb"); 

            colour_pixel **mat;

            char mag_id[3];   //stores the magic PPM identifier (P3 or P6)
            fscanf(fp,"%2s",mag_id);
            mag_id[2]='\0';

            fscanf(fp, "%d", &Height);
            fscanf(fp, "%d", &Width);
            fscanf(fp, "%d", &max_no_of_colour);
            char c;
            fscanf(fp,"%c",&c);  

            //creating matrix of size  H x W of type colour_pixel
            mat = malloc(Height * sizeof(colour_pixel*));
            
            for(int i = 0; i < Height; i++)
            {
                mat[i] = malloc(Width*sizeof(colour_pixel));
            }
           
            //  blank matrix is created.......   Now we need to fill the matrix from ppm file.
            for(int i = 0; i < Height; i++)
            {
                for(int j = 0; j < Width; j++)
                {
                    fread(&mat[i][j], sizeof(colour_pixel), 1, fp);
                } 
            }
            fclose(fp); 

            Quad_Node *root=NULL;
            int no_of_colour=0, no_of_nodes=0;

            CreateQuadTree(&root,0,0,Width,mat,&no_of_colour,&no_of_nodes);
            
            if(c1==1)
            {
                Horizontal_flip(&root);
            }
            if(c1==2)
            {
                Vertical_flip(&root);
            }
        
            int x = 0, y = 0;

            create_matrix(root,mat,x,y,Width,&no_of_colour ,no_of_nodes);
            create_image(mat,Height,Width,max_no_of_colour,output_image);
            del_Matrix(mat,Height);
            del_tree(root);

            return;
        }

        else if (choice == 3 || choice==4 || choice==5)
        {
            if(choice==3)
            {
                printf("1. Red\n2. Green\n3. Blue\nEnter colour choice: ");
                scanf("%d",&c2);
                if(c2!=1 && c2!=2 && c2!=3)
                {
                    printf("Invalid input\n");
                    return;
                }
            }
            Quad_Node *root=NULL;
            colour_pixel **mat;
            int Height , Width;

            FILE *fp=fopen(input_image,"rb");
            char mag_id[3];   //stores the magic PPM identifier (P3 or P6)
            fscanf(fp, "%2s", mag_id);
            mag_id[2]= '\0';

            fscanf(fp, "%d", &Height);
            fscanf(fp, "%d", &Width);
            fscanf(fp, "%d", &max_no_of_colour);
            char c;
            fscanf(fp,"%c",&c);

            //creating matrix of size  H x W of type colour_pixel
            mat = malloc(Height * sizeof(colour_pixel*));

            for(int i = 0; i < Height; i++)
            {
                mat[i] = malloc(Width * sizeof(colour_pixel));
            }


            //  blank matrix is created.......   Now we need to fill the matrix from ppm file.
            for(int i = 0; i < Height; i++)
            {
                for(int j = 0; j < Width; j++)
                {
                    fread(&mat[i][j], sizeof(colour_pixel), 1, fp);
                }
            }
            fclose(fp);

            int no_of_colour=0, no_of_nodes=0 ;
            int x=0 , y=0;


            CreateQuadTree(&root,0,0,Width,mat,&no_of_colour,&no_of_nodes);
            
            if (choice==3)
            {
                if(c2==1)
                {
                    red(root,mat,x,y,Width);
                }

                else if(c2==2)
                {
                    green(root,mat,x,y,Width);
                }

                else if(c2==3)
                {
                    blue(root,mat,x,y,Width);
                }
            }
                
            if (choice==4)
            {
                grey(root,mat,x,y,Width);
            }
                    
            if (choice==5)
            {
                black_white(root,mat,x,y,Width);
            }
                
            create_image(mat, Height, Width, max_no_of_colour, output_image);
            del_Matrix(mat, Width);
            del_tree(root);
            return;
        }
        
        else
        {
            printf("Invalid input\n");
            return;
        }
    }
}
