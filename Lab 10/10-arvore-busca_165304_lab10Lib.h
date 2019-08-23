#ifndef lab10

typedef struct node{

    int key;
    struct node *left;
    struct node *right;

}node;

typedef struct queue{
    node *entry;
    struct queue *next;
}queue;

int read_input(char *command);
void print_post_order_tree(node *R);
void print_in_order_tree(node *R);
void print_pre_order_tree(node *R);
queue* Enqueue(node *R, queue **Q_given);
void print_breadth_tree(node *R);
void delete_tree(node **R_given);
void min(node *R);
void max(node *R);
int search(node *R,int x);
node* insert(node **R_given);
node* exclude(node **R_given);

#endif