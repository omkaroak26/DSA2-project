#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "qt.c"

int main(int argc , char *argv[])
{
      
    int Height , Width , max_no_of_colour , i ,j ,threshold;
                                
    // Choice variable
    int choice = -1, c1=-1, c2=-1;
                                
    // Menu display
    printf("\n************  IMAGE MANIPULATION  ***************\n");
    printf("\n1. Compress image\n2. Flip image\n3. Add colour filter\n4. Black and white\n5. Grayscale\n6. Exit\n");
             
while(1){
        printf("\nEnter your choice:");
        scanf("%d", &choice);
        
        
    if(choice == 1){

        printf("Enter Threshold\n");
        scanf("%d",&threshold);
        colour_pixel **mat;

        FILE *fp=fopen(argv[1],"rb");

        char mag_id[3];             //stores the magic PPM identifier (P3 or P6)
        
        //threshold is inversely proportional to file size
        //threshold is inversely proportional to number of nodes
       // threshold=atoi(argv[2]);    //   atoi converts string to  int
        
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
        create_image(mat,Width,max_no_of_colour,argv[2]);
        del_Matrix(mat,Height);
        del_tree(root);

        }
    else if (choice == 2){
            printf("Enter your choice:\n1. Horizontal flip\n2. Vertical flip\n");
            scanf("%d",&c1);
            if(c1!=1&&c1!=2){
                printf("Invalid input\n");
            }
            FILE *fp=fopen(argv[1],"rb"); 

            colour_pixel **mat;


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
            if(c1==1){
                 Horizontal_flip(&root);
            }
            if(c1==2){
                Vertical_flip(&root);

            }
          
            x = y =0;
		    l = Width; 

            create_matrix(root,mat,x,y,l,&no_of_colour ,no_of_nodes);
            create_image(mat,Width,max_no_of_colour,argv[2]);
            del_Matrix(mat,Height);
            del_tree(root);
            
        }

    else if (choice == 3 || choice==4 || choice==5){
        if(choice==3){
            printf("Enter colour choice:\n1. Red\n2. Green\n3. Blue\n");
            scanf("%d",&c2);
            if(c2!=1 && c2!=2 && c2!=3){
                printf("Invalid input\n");
            }
        }
           Quad_Node *root1=NULL;
           colour_pixel **mat1;
           int Height1 , Width1;
           // colour_pixel **mat;

           //mat=(colour_pixel**)malloc(Height*sizeof(colour_pixel*));



           FILE *fp=fopen(argv[1],"rb");
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
        if (choice==3){
          if(c2==1){
            red(root1,mat1,x,y,L);

          }

          else if(c2==2){
            green(root1,mat1,x,y,L);

          }

          else if(c2==3){
            blue(root1,mat1,x,y,L);

          }
        }
        
        if (choice==4){
            grey(root1,mat1,x,y,L);

        }
        
        if (choice==5){
            black_white(root1,mat1,x,y,L);

        }
        
        create_image(mat1, Width1, max_no_of_colour, argv[2]);
		del_Matrix(mat1, Width1);
		del_tree(root1);

        }
    
    else if(choice==6){
        return 0;
    }
    else{
        printf("Invalid input\n");
    }
     
  }
return 0;   
}
