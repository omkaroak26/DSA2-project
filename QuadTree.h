typedef struct colour_pixel
{
    unsigned char R,G,B;
}colour_pixel;

typedef struct Quad_Node
{
    unsigned char R, G ,B;

    struct Quad_Node *top_left;
    struct Quad_Node *top_right;
    struct Quad_Node *bottom_right;
    struct Quad_Node *bottom_left;
}Quad_Node;


//functions for compression
void Add_node(Quad_Node **root , colour_pixel p);
int Uniformity(colour_pixel **mat , int x ,int y , int l , colour_pixel *p);
void Compression(Quad_Node ** root , int x , int y, int L,int W, colour_pixel ** mat,int threshold , int *no_of_colour, int *no_of_nodes);
int Depth(Quad_Node* root);

//  functions for clearing memory
void del_Matrix(colour_pixel **mat, int Height); 
void del_tree(Quad_Node *root);
int powTwo(int x);

//to convert tree  to matrix
void pix_value(colour_pixel **mat,int x,int y,int l,unsigned char R, unsigned char G , unsigned char B);
void create_matrix(Quad_Node *root , colour_pixel **mat , int x , int y, int l , int *no_of_colour , int no_of_nodes);
void create_image(colour_pixel **mat , int Height,int Width, int max_no_of_colour,char *name_of_file);

//  flipping an image
void CreateQuadTree(Quad_Node ** root , int x , int y, int L, colour_pixel ** mat, int *no_of_colour, int *no_of_nodes);
//void printQuadTree(Quad_Node* root);
void Horizontal_flip(Quad_Node **root);
void Vertical_flip(Quad_Node **root);

//  filters
void red(Quad_Node *root,colour_pixel **mat,int x,int y,int L);
void green(Quad_Node *root,colour_pixel **mat,int x,int y,int L);
void blue(Quad_Node *root,colour_pixel **mat,int x,int y,int L);
void grey(Quad_Node *root,colour_pixel **mat,int x,int y,int L);
void black_white(Quad_Node *root,colour_pixel **mat,int x,int y,int L);
