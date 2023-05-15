#include <stdio.h>
#include <stdlib.h>

typedef struct colour_pixel
{
    unsigned char R,G,B;    //values of RGB are 255*255*255
}colour_pixel;

typedef  struct Quad_Node
{
    unsigned char R, G ,B;
    unsigned int A;   //area

    struct Quad_Node *top_left;
    struct Quad_Node *top_right;
    struct Quad_Node *bottom_right;
    struct Quad_Node *bottom_left;
}Quad_Node;

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

/*void Inorder(Quad_Node root)
{
    if(root==NULL)
}*/

void print(Quad_Node* root)
{
    printf("%d ",root->R);
    printf("%d ",root->G);
    printf("%d ",root->B);
    printf("%d ",root->top_left->R);
    printf("%d ",root->top_right->B);
    if(root->bottom_left==NULL!=1)
        printf("%d ",root->bottom_left->R);
    else
        printf("rukmini");
}

int main()
{
    Quad_Node* root;
    colour_pixel p;
    p.B = 100;
    p.R = 120;
    p.G = 100;
    int l=10;
    Add_node(&root,p,l);
    colour_pixel p2;
    p2.B = 110;
    p2.R = 120;
    p2.G = 130;

    colour_pixel p3;
    p3.B = 10;
    p3.R = 20;
    p3.G = 30;
    Add_node(&root,p2,l);
    Add_node(&root,p3,l);
    //Add_node(&root,p,l);
    print(root);


    return 0;
}