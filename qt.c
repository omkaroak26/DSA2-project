#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "qt.h" 

//mat = 2D array in which each element is a color_pixel (that is each element has R G and B)

void Add_node(Quad_Node **root , colour_pixel p , int l) 
{
    Quad_Node *q=(Quad_Node *)malloc(sizeof(Quad_Node));
    q->R=p.R;
    q->G=p.G;
    q->B=p.B;
    q->A=l*l;    //l is the length of the image (in pixels)
    q->top_left=NULL;
    q->top_right=NULL;
    q->bottom_right=NULL;
    q->bottom_left=NULL;

    if(*root==NULL)
    {
        *root=q;
        return;
    }
    else   //check clockwise all children (if null, insert)
    {
        if((*root)->top_left==NULL)
            (*root)->top_left=q;

        else if((*root)->top_right==NULL)
            (*root)->top_right=q;

        else if((*root)->bottom_right==NULL)
            (*root)->bottom_right=q;

        else if((*root)->bottom_left==NULL)
            (*root)->bottom_left=q;
    }
}

//  changes (iterative)
int Uniformity(colour_pixel **mat , int x ,int y , int L , colour_pixel *RGBavg)
{
    //x(row) and y(column) is the size of mat(2D array)
    long long variance=0, average=0;
    int i , j;
    long long AvgR=0, AvgG=0 ,AvgB=0 ; 

    long long size = L;     //L = length
    
	for(i = x; i < x + L; i++)
    {
		for(j = y; j < y + L; j++)
        {	
			AvgR += mat[i][j].R;
			AvgG += mat[i][j].G;
			AvgB += mat[i][j].B;	
		}
	}

    //finding Avg of R G B of entire section
    AvgR = AvgR/(L * L);
    AvgG = AvgG/(L * L);
    AvgB = AvgB/(L * L);	

    //  storing the Avg values of RGB into  colour_pixel RGBavg
    RGBavg->R = AvgR;
    RGBavg->G = AvgG;
    RGBavg->B = AvgB;

    //printf("%d %d %d\n",AvgR,AvgG,AvgB);
    
    //  calculating var value of a node

    //  WE ARE not HERE (19-05-2023)

	for(i = x; i < x + L; i++)
    {
		for(j = y; j < y + L; j++)
        {
            //variance of average
            variance += (AvgR - mat[i][j].R)*(AvgR - mat[i][j].R);  //numerator of variance of R
            variance += (AvgB - mat[i][j].B)*(AvgB - mat[i][j].B);  //numerator of variance of B
            variance += (AvgG - mat[i][j].G)*(AvgG - mat[i][j].G);  //numerator of variance of G
        }
	}
    average=variance/(3*L*L);
    return average; //avg of variances

}

//   Compression  in a quadtree of pixels that have RGB data
void Compression(Quad_Node** root , int x , int y, int L, colour_pixel** mat,int threshold , int *no_of_colour, int *no_of_nodes)
{
    int average;    // to get the average value (to check for uniformity)
    
    colour_pixel RGBavg;   // it stores the average colour of current partition...

    average = Uniformity(mat, x, y, L, &RGBavg);
    //printf("%d ",average);

    if(L<1)
        return;

    //   count no of nodes and add the node to the root..
    (*no_of_nodes)=(*no_of_nodes)+1;

    Add_node(root,RGBavg,L);   //add the node in quadtree

    if(average>threshold)   //base case of recursion
    {

        Compression(&(*root)->top_left,     x,      y,      L/2,  mat,    threshold,  no_of_colour,no_of_nodes);
        (*no_of_colour)+=1  ;

        Compression(&(*root)->top_right,    x,      y+L/2 , L/2,  mat,    threshold, no_of_colour, no_of_nodes);
        (*no_of_colour)+=1;

        Compression(&(*root)->bottom_right, x+L/2 , y+L/2 , L/2,  mat,    threshold,  no_of_colour,no_of_nodes);
        (*no_of_colour)+=1;

        Compression(&(*root)->bottom_left,  x+L/2,  y,      L/2,  mat,    threshold,  no_of_colour,no_of_nodes);
        (*no_of_colour)+=1;

    }

}// we are here 


int Depth(Quad_Node* root){    // determining the depth of a quaternary tree
    if (root == NULL)
        return 0;
    else{       
        int t_l = Depth(root->top_left);
        int t_r = Depth(root->top_right);
        int b_r = Depth(root->bottom_right);
        int b_l = Depth(root->bottom_left); 
       
    	int max = t_l;
    	if(t_r > max)
    		max = t_r;
    	if(b_r > max)
    		max = b_r;
    	if(b_l > max)
    		max = b_l;
    	return(max+1);
    }
}




void del_Matrix(colour_pixel **mat, int Height){
    int i;
    for(i=0;i<Height;i++){
        free(mat[i]);
    }
    free(mat);
}

void del_tree(Quad_Node *root){
    if(root==NULL)
        return;
    
    del_tree(root->top_left);
    del_tree(root->top_right);
    del_tree(root->bottom_right);
    del_tree(root->bottom_left);

    free(root);
    root=NULL;
}





int powTwo(int x){       //function for obtaining a number ie a power of 2
	int a = 2;
	while(a * a != x)
		a = a * 2;
	return a;
}


void pix_value(colour_pixel **mat,int x,int y,int l,unsigned char R, unsigned char G , unsigned char B){
	int i,j;

    //  giving same rgb values to a node
	for(i = x; i < x+l; i++)
		for(j = y; j < y+l; j++){
				mat[i][j].R = R;
				mat[i][j].G = G;
				mat[i][j].B = B;
		}
}


void create_matrix(Quad_Node *root , colour_pixel **mat , int x , int y, int L , int *no_of_colour , int no_of_nodes){
    if((*no_of_colour)==0 || L==0)
        return;
    
    if (root->top_left==NULL)
    {
        pix_value(mat,x,y,L,root->R, root->G , root->B);
        *no_of_colour = (*no_of_colour) - 1;
    }
    else{
        create_matrix(root->top_left ,      mat , x     , y     , L/2 , no_of_colour , no_of_nodes);
        create_matrix(root->top_right ,     mat , x     , y+L/2 , L/2 , no_of_colour , no_of_nodes);
        create_matrix(root->bottom_right ,  mat , x+L/2 , y+L/2 ,L/2 , no_of_colour , no_of_nodes);
        create_matrix(root->bottom_left ,   mat , x+L/2 , y     , L/2 , no_of_colour , no_of_nodes);
    }
    
} //creates matrix from quadtree
//each block in the matrix holds the RGB value of the corresponding leaf node in the quadtree


void create_image(colour_pixel **mat , int Height, int max_no_of_colour,char *name_of_file){
	
    FILE *fp = fopen(name_of_file,"wb");
	fprintf(fp, "%s\n", "P6");
	fprintf(fp, "%d %d\n", Height, Height);
    fprintf(fp, "%d\n", max_no_of_colour);

    int i,j;
  
	for(i = 0; i < Height; i++){
	 	fwrite(mat[i],sizeof(colour_pixel),Height,fp);
        printf("%c ",mat[i][0]);
	}
	fclose(fp);
} //rewrite ppm file


void Horizontal_flip(Quad_Node **root){
    if((*root)==NULL)
        return;

	if((*root)->top_left != NULL){
		Quad_Node *temp = NULL;
		
		temp = (*root)->top_left; 
		(*root)->top_left = (*root)->top_right;
		(*root)->top_right = temp;
		
		temp = (*root)->bottom_left; 
		(*root)->bottom_left = (*root)->bottom_right;
		(*root)->bottom_right = temp;

		Horizontal_flip(&(*root)->top_left);
		Horizontal_flip(&(*root)->top_right);
		Horizontal_flip(&(*root)->bottom_right);
		Horizontal_flip(&(*root)->bottom_left);
	}
}

void Vertical_flip(Quad_Node **root){
    if((*root)==NULL)
        return;

	if((*root)->top_left != NULL){
		Quad_Node *temp = NULL;
		
		temp = (*root)->top_left; 
		(*root)->top_left = (*root)->bottom_left;
		(*root)->bottom_left = temp;
		
		temp = (*root)->top_right; 
		(*root)->top_right = (*root)->bottom_right;
		(*root)->bottom_right = temp;

		Vertical_flip(&(*root)->top_left);
		Vertical_flip(&(*root)->top_right);
		Vertical_flip(&(*root)->bottom_right);
		Vertical_flip(&(*root)->bottom_left);
	}
}

void complete_tree(Quad_Node **root,int l, int depth, int line){
    if(*root==NULL)
        return;

	if(line < depth && (*root)->top_left == NULL){	
		colour_pixel p;
		p.R = (*root)->R;
		p.G = (*root)->G;
		p.B = (*root)->B;

		Add_node(root,p,l);
		Add_node(root,p,l);
		Add_node(root,p,l);
		Add_node(root,p,l);
    }

    complete_tree(&(*root)->top_left,       l/2,    depth,  line+1);
    complete_tree(&(*root)->top_right,      l/2,    depth,  line+1);
    complete_tree(&(*root)->bottom_right,   l/2,    depth,  line+1);
    complete_tree(&(*root)->bottom_left,    l/2,    depth,  line+1);

}

/*
void Overlap_imgs(Quad_Node *root1 , Quad_Node *root2, colour_pixel **mat , int x,int y, int L){
    if(L==0)
        return;
    if(root1->top_left==NULL){
        pix_value(mat , x, y, L, (int)(root1->R + root2->R)/2 , (int)(root1->G + root2->G)/2, (int)(root1->B + root2->B)/2) ;
    }
    else{
        Overlap_imgs(root1->top_left     , root2->top_left     , mat , x     , y     , L/2);
        Overlap_imgs(root1->top_right    , root2->top_right    , mat , x     , y+L/2 , L/2);
        Overlap_imgs(root1->bottom_left , root2->bottom_right , mat , x+L/2 , y     , L/2);
        Overlap_imgs(root1->bottom_right  , root2->bottom_left  , mat , x+L/2 , y+L/2 , L/2);
    }
}*/

void red(Quad_Node *root,colour_pixel **mat,int x,int y,int L){
    if(L==0)
        return;
    if(root->top_left==NULL)
        pix_value(mat,x,y,L,root->R,0,0);
    
    else{
        red(root->top_left      ,mat, x      ,y      ,L/2);
        red(root->top_right     ,mat, x      ,y+L/2  ,L/2);
        red(root->bottom_left   ,mat, x+L/2  ,y      ,L/2);
        red(root->bottom_right  ,mat, x+L/2  ,y+L/2  ,L/2);
    }
}

void green(Quad_Node *root,colour_pixel **mat,int x,int y,int L){
    if(L==0)
        return;
    if(root->top_left==NULL)
        pix_value(mat,x,y,L,0,root->G,0);
    
    else{
        green(root->top_left      ,mat, x      ,y      ,L/2);
        green(root->top_right     ,mat, x      ,y+L/2  ,L/2);
        green(root->bottom_left   ,mat, x+L/2  ,y      ,L/2);
        green(root->bottom_right  ,mat, x+L/2  ,y+L/2  ,L/2);
    }
}

void blue(Quad_Node *root,colour_pixel **mat,int x,int y,int L){
    if(L==0)
        return;
    if(root->top_left==NULL)
        pix_value(mat,x,y,L,0,0,root->B);
    
    else{
        blue(root->top_left      ,mat, x      ,y      ,L/2);
        blue(root->top_right     ,mat, x      ,y+L/2  ,L/2);
        blue(root->bottom_left   ,mat, x+L/2  ,y      ,L/2);
        blue(root->bottom_right  ,mat, x+L/2  ,y+L/2  ,L/2);
    }
}


//   greyscale is obtained by multiplying  R * 0.299 , G * 0.578 , B* 0.114
void grey(Quad_Node *root,colour_pixel **mat,int x,int y,int L){
    if(L==0)
        return;

    if(root->top_left==NULL){
        int c=(root->R)*0.299 + (root->G)*0.587 + (root->B)*0.114;
        pix_value(mat,x,y,L,c,c,c);
    }
    else{
        grey(root->top_left      ,mat, x      ,y      ,L/2);
        grey(root->top_right     ,mat, x      ,y+L/2  ,L/2);
        grey(root->bottom_left   ,mat, x+L/2  ,y      ,L/2);
        grey(root->bottom_right  ,mat, x+L/2  ,y+L/2  ,L/2);
    }
}

void black_white(Quad_Node *root,colour_pixel **mat,int x,int y,int L){
    if(L==0)
        return;    
    if(root->top_left == NULL){	 
		int c = (root->R + root->G + root->B)/3 ;
		if(c > 200){
	 		pix_value(mat, x, y, L, 0, 0, 0); 
        }
		else
			pix_value(mat, x, y, L, 255, 255, 255);
    }
    else{
        black_white(root->top_left      ,mat, x      ,y      ,L/2);
        black_white(root->top_right     ,mat, x      ,y+L/2  ,L/2);
        black_white(root->bottom_left   ,mat, x+L/2  ,y      ,L/2);
        black_white(root->bottom_right  ,mat, x+L/2  ,y+L/2  ,L/2);
    }
}

