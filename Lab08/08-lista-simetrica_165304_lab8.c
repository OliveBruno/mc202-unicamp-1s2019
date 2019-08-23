#include<stdio.h>
#include<stdlib.h>

//#define DEBUGINSERT
//#define DEBUGREV

//IMPORTANT!!!
//FOR THIS PROGRAM I USED A LIST WITH TWO DUMMY NODES, ONE ON THE HEAD AND THE OTHER ON THE TAIL.


typedef struct node{

    double myvalue;
    struct node *a;
    struct node *b;

}node;


int list_size = 0;//the size of the list is a global variable.

int read_command(char *command);//basically a scanf that outputs 0 if its a 't' and 1 otherwise.
node* insert_on_list(node **L_given);//this function takes a list and reads 2 values, a position and a value, and inserts a node with that value on the given position
void print_list(node **L_given);//prints all the elements on a list
node* reverse_list(node **L_given);//takes in a list and then reads an interval, it then reverses the elements in that inteval
node* delete_list(node **L_given);//frees a list

int main(){//seems ok

    node *L;
    L = malloc(sizeof(node));
    L->a = NULL;
    L->b = malloc(sizeof(node));
    (L->b)->a = L;
    (L->b)->b = NULL;

    char command;

    while(read_command(&command)){

        if(command == 'i'){
            L = insert_on_list(&L);
        }else if(command == 'p'){
            print_list(&L);
        }else if(command == 'v'){
            L = reverse_list(&L);
        }

    }

    L = delete_list(&L);

    return 0;
}

int read_command(char *command){//seems ok

    scanf(" %c",command);

    if(*command == 't')
        return 0;
    else
        return 1;
}

node* insert_on_list(node **L_given){//seems ok

    node *L = *L_given;
    node *curr_node;
    node *prev_node;
    node *aux;
    int pos;
    double value;

    scanf(" %d %lf",&pos,&value);

    #ifdef DEBUGINSERT
        printf("pos = %d, value = %.4f\n",pos,value);
    #endif // DEBUGINSERT

    if(pos>list_size)
        pos = list_size;

    if(pos == 0){
        aux = malloc(sizeof(node));
        aux->myvalue = value;
        aux->b = L->b;
        aux->a = L;
        if((L->b)->a == L){
            (L->b)->a = aux;
        }else if((L->b)->b == L){
            (L->b)->b = aux;
        }
        L->b = aux;
        list_size++;
    }else{
        curr_node = L->b;
        prev_node = L;

        for(int i = 0;i < pos-1;i++){
            if(curr_node->b != prev_node){
                prev_node = curr_node;
                curr_node = curr_node->b;
            }else if(curr_node->a != prev_node){
                prev_node = curr_node;
                curr_node = curr_node->a;
            }
        }

        aux = malloc(sizeof(node));
        aux->myvalue = value;
        list_size++;

        if(curr_node->b != prev_node){
            aux->b = curr_node->b;
            aux->a = curr_node;

            if((curr_node->b)->b == curr_node){
                (curr_node->b)->b = aux;
            }else if((curr_node->b)->a == curr_node){
                (curr_node->b)->a = aux;
            }

            curr_node->b = aux;

        }else if(curr_node->a != prev_node){
            aux->b = curr_node->a;
            aux->a = curr_node;

            if((curr_node->a)->b == curr_node){
                (curr_node->a)->b = aux;
            }else if((curr_node->a)->a == curr_node){
                (curr_node->a)->a = aux;
            }

            curr_node->a = aux;
        }

    }

    return L;
}

void print_list(node **L_given){//seems ok

    if(list_size > 0){

        node *L = *L_given;
        node *prev_node = L;
        node *curr_node = L->b;

        for(int i = 0; i < list_size ; i++){

            printf("%.4f ",curr_node->myvalue);

            if(curr_node->b != prev_node){
                prev_node = curr_node;
                curr_node = curr_node->b;
            }else if(curr_node->a != prev_node){
                prev_node = curr_node;
                curr_node = curr_node->a;
            }
        }

    }

    printf("\n");

}

node* reverse_list(node **L_given){////seems ok

    node *L = *L_given;
    node *prev_node_start = L;
    node *curr_node_start = L->b;
    node *prev_node_end = L;
    node *curr_node_end = L->b;
    node* aux = NULL;
    int start,end;

    scanf(" %d %d",&start,&end);

    #ifdef DEBUGREV
        printf("start = %d, end = %d\n",start,end);
    #endif // DEBUGREV

    if(start == end || list_size == 0)
        return L;

    for(int i = 0;i<start;i++){

        if(curr_node_start->b != prev_node_start){
            prev_node_start = curr_node_start;
            curr_node_start = curr_node_start->b;
        }else if(curr_node_start->a != prev_node_start){
            prev_node_start = curr_node_start;
            curr_node_start = curr_node_start->a;
        }
    }

    #ifdef DEBUGREV
        printf("valor do primeiro elemento da lista antes da inversao = %.4f\n",curr_node_start->myvalue);
    #endif // DEBUGREV

    for(int i = 0;i<end;i++){

        if(curr_node_end->b != prev_node_end){
            prev_node_end = curr_node_end;
            curr_node_end = curr_node_end->b;
        }else if(curr_node_end->a != prev_node_end){
            prev_node_end = curr_node_end;
            curr_node_end = curr_node_end->a;
        }
    }//now I have the start, end, the node before the start and the node before the end of my list


    #ifdef DEBUGREV
        printf("valor do ultimo elemento da lista antes da inversao = %.4f\n",curr_node_end->myvalue);
    #endif // DEBUGREV


    if(prev_node_start->b == curr_node_start){
        prev_node_start->b = curr_node_end;//pointer to previous start now points to the end
    }else if(prev_node_start->a == curr_node_start){
        prev_node_start->a = curr_node_end;//pointer to previous start now points to the end
    }

    if(curr_node_end->b != prev_node_end){//pointer from end of the interval to the rest of the list now points to pointer changed above.
        aux = curr_node_end->b;//aux now carries the rest of the list
        curr_node_end->b = prev_node_start;
    }else if(curr_node_end->a != prev_node_end){
        aux = curr_node_end->a;
        curr_node_end->a = prev_node_start;
    }

    if(curr_node_start->a == prev_node_start){//old start now points to the rest of the list
        curr_node_start->a = aux;
    }else if(curr_node_start->b == prev_node_start){
        curr_node_start->b = aux;
    }

    if(aux->a == curr_node_end){//rest of list points to the old start.
        aux->a = curr_node_start;
    }else if(aux->b == curr_node_end){
        aux->b = curr_node_start;
    }

    return L;
}

node* delete_list(node **L_given){//seems ok

    node *L = *L_given;
    node *freed_node = L;// I am going to free this one.
    node *prev_node = L->b;
    node *curr_node = NULL;

    if(list_size == 0){
        free(freed_node);
        free(prev_node);
        return L;
    }

    if(prev_node->a != freed_node){
        curr_node = prev_node->a;
    }else if(prev_node->b != freed_node){
        curr_node = prev_node->b;
    }


    for(int i = 0; i < list_size-1; i++){
        free(freed_node);

        freed_node = prev_node;

        if(curr_node->a != prev_node){
            prev_node = curr_node;
            curr_node = curr_node->a;
        }else if(curr_node->b != prev_node){
            prev_node =  curr_node;
            curr_node = curr_node->b;
        }
    }

    free(freed_node);
    free(prev_node);
    free(curr_node);

    return L;

}
