#include<stdio.h>
#include<stdlib.h>

typedef struct grafo_info{//auxiliary matrix for BFS

    int me;
    int distance;
    int mark;

}grafo_info;

typedef struct queue{

    grafo_info *entry;
    struct queue *next;

}queue;

void print_matrix(int **matrix,int n_lines,int n_columns);//for debugging
void Enqueue(queue **Q, grafo_info* R);//Enqueue
void print_breadth_grafo(int **matrix,int n,int origin);//imprime um grafo (implementado como matriz de adjascencias) em largura
void build_grafo_matrix(int ***matrix, int n);
void delete_matrix(int ***matrix, int n);

int main(){

    int **matrix;
    int n_vertex;
    int origin;

    scanf("%d",&n_vertex);
    build_grafo_matrix(&matrix,n_vertex);

    scanf("%d",&origin);

    printf("Origem da busca: %d\n",origin);
    printf("Vertices alcancados e distancias:\n");

    print_breadth_grafo(matrix,n_vertex,origin-1);

    delete_matrix(&matrix,n_vertex);

    return 0;
}

void build_grafo_matrix(int ***matrix, int n){

    int i,j;

    (*matrix) = malloc(n*sizeof(int*));

    for(int k = 0;k<n;k++){
        (*matrix)[k] = calloc(n,sizeof(int));
    }

    scanf("%d",&i);
    getchar();
    scanf("%d",&j);

    if(i != 0){
        i--;
        j--;
    }

    while(i != j || i != 0){

        (*matrix)[i][j] = 1;
        (*matrix)[j][i] = 1;

        scanf("%d",&i);
        getchar();
        scanf("%d",&j);

        if(i != 0){
            i--;
            j--;
        }
    }

}

void delete_matrix(int ***matrix, int n){

    for(int k = 0;k<n;k++){
        free((*matrix)[k]);
    }
    free(*matrix);

    *matrix = NULL;
}

void print_matrix(int **matrix,int n_lines,int n_columns){

    printf("   ");

    for(int j = 0;j<n_columns;j++){
        printf("%d ",j+1);
    }

    printf("\n");

    for(int j = 0;j<n_columns+1;j++){
        printf("--");
    }

    printf("\n");

    for(int i = 0;i<n_lines;i++){

        printf("%d| ",i+1);

        for(int j = 0;j<n_columns;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void print_breadth_grafo(int **matrix,int n,int origin){//assumes nxn matrix

    queue *Q = NULL;
    queue *dequeuer;
    grafo_info *aux;
    grafo_info *u;

    aux = malloc(n*sizeof(grafo_info));

    for(int i = 0;i<n;i++){
        aux[i].distance = -1;
        aux[i].mark = 0;
    }

    aux[origin].me = origin;
    aux[origin].distance = 0;
    aux[origin].mark = 1;

    Enqueue(&Q,&(aux[origin]));//Enqueue

    while(Q != NULL){

        u = Q->entry;//Dequeue
        dequeuer = Q;
        Q = Q->next;
        free(dequeuer);

        printf("%d %d\n",u->me + 1,u->distance);

        for(int v = 0;v<n;v++){
            if((aux[v].mark == 0) && (matrix[u->me][v] == 1)){
                aux[v].distance = u->distance + 1;
                aux[v].me = v;
                Enqueue(&Q,&(aux[v]));
                aux[v].mark = 1;
            }
        }

    }

    free(aux);

}

void Enqueue(queue **Q, grafo_info* R){//seems ok
    queue *q;
    queue* end;

    q = malloc(sizeof(queue));
    q->entry = R;
    q->next = NULL;

    end = *Q;

    if(end != NULL){

        while(end->next != NULL)
            end = end->next;

        end->next = q;
    }else{

        *Q = q;

    }
}

