#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lab10Lib.h"

int read_input(char *command){//seems ok

    scanf("%s",command);

    if(!strcmp(command,"terminar"))
        return 0;
    else
        return 1;

}

void print_pre_order_tree(node *R){//seems ok

    if(R != NULL){
        printf("%d ",R->key);
        print_pre_order_tree(R->left);
        print_pre_order_tree(R->right);
    }

}

void print_in_order_tree(node *R){//seems ok

    if(R != NULL){
        print_in_order_tree(R->left);
        printf("%d ",R->key);
        print_in_order_tree(R->right);
    }

}

void print_post_order_tree(node *R){//seems ok

    if(R != NULL){
        print_post_order_tree(R->left);
        print_post_order_tree(R->right);
        printf("%d ",R->key);
    }

}

queue* Enqueue(node *R, queue **Q_given){//seems ok
    queue *Q = *Q_given;
    queue *q;
    queue* end;

    q = malloc(sizeof(queue));
    q->entry = R;
    q->next = NULL;

    end = Q;

    if(end != NULL){

        while(end->next != NULL)
            end = end->next;

        end->next = q;
    }else{

        Q = q;

    }

    return Q;
}

void print_breadth_tree(node *R){//seems ok
    queue *Q = NULL;
    queue* aux;
    node* p;


    Q = Enqueue(R,&Q);//Enqueue


    while(Q != NULL){

            p = Q->entry;//Dequeue
            aux = Q;
            Q = Q->next;
            free(aux);

            printf("%d ",p->key);//visit

        if(p->left != NULL){
            Q = Enqueue(p->left,&Q);
        }
        if(p->right != NULL){
            Q = Enqueue(p->right,&Q);
        }
    }

}

void delete_tree(node **R_given){//seems ok
    node *R = *R_given;
	
    if(!R)
	return;

    if(R->left != NULL)
        delete_tree(&(R->left));

    if(R->right != NULL)
        delete_tree(&(R->right));

    free(R);

}

void min(node *R){//seems ok
    node *aux = R;

    if(!R){
        printf("vazia\n");
        return;
    }

    while(aux->left != NULL)
        aux = aux->left;

    printf("%d\n",aux->key);
}

void max(node *R){//seems ok
    node *aux = R;

    if(!R){
        printf("vazia\n");
        return;
    }

    while(aux->right != NULL)
        aux = aux->right;

    printf("%d\n",aux->key);
}

int search(node *R,int x){//seems ok
    node *aux = R;

    while(aux != NULL){
        if(x < aux->key){
            aux = aux->left;
        }else if(x > aux->key){
            aux = aux->right;
        }else{
            return 1;
        }
    }

    return 0;

}

node* insert(node** R_given) {//seems ok

    node *R = *R_given;
    int x;
    node* z = malloc(sizeof(node));
    if(!z){
        printf("memoria insuficiente\n");
        return R;
    }

    scanf(" %d",&x);

    if(search(R,x))
        return R;

    z->right = z->left = NULL;
    z->key = x;

    node* u = R;
    node* p = NULL;


    while (u) {

        p = u;

        if (x < u->key)
            u = u->left;
        else
            u = u->right;
    }


    if (p == NULL){
        R = z;
    }else {

        if (x < p->key){
            p->left = z;
        }else{
            p->right = z;
        }
    }

    return R;
}

node* exclude(node **R_given){//seems ok
    node *R = *R_given;
    node *aux = R;
    node *p = NULL;
    int x;

    scanf(" %d",&x);

    if(!search(R,x))
        return R;

    while(aux != NULL){

        if(x < aux->key){
            p = aux;
            aux = aux->left;
        }else if(x > aux->key){
            p = aux;
            aux = aux->right;
        }else{
            break;
        }
    }//aqui, aux tem a chave que a gente quer excluir e p eh o pai dele ou p e aux sao a raiz


    if(!p){//quero excluir a raiz


        if(!(aux->left) && !(aux->right)){//so tenho a raiz
            R = NULL;
            free(aux);
        }else if(!(aux->right)){//nao tenho sub arvore a direita
            R = aux->left;
            free(aux);
        }else if(!(aux->left)){//nao tenho sub arvore a esquerda
            R = aux->right;
            free(aux);
        }else{//tenho dois filhos

            node *q = aux;// sera o pai do minimo da sub arvore a direita
            node *aux2 = aux->right;//sera o minimo da sub arvore a direita

            while(aux2->left != NULL){//procuro o minimo da sub arvore a direita
                q = aux2;
                aux2 = aux2->left;
            }//pay attention here

            if(q->right != aux2)
                q->left = aux2->right;//faco o pai do minimo apontar pro que tiver a direita do minimo

            //faco a substituicao
            R = aux2;
            aux2->left = aux->left;
            if(aux->right != aux2)
                aux2->right = aux->right;
            free(aux);

        }
    }else if(!(aux->left) && !(aux->right)){//checo se eh folha
        if(p->right == aux){
            p->right = NULL;
            free(aux);
        }else if(p->left == aux){
            p->left = NULL;
            free(aux);
        }
    }else if(!(aux->right)){//checo se tem sub arvore a direita, caso nao tenha trato aqui

        if(p->left == aux){
            p->left = aux->left;
            free(aux);
        }else{
            p->right = aux->left;
            free(aux);
        }

    }else if(!(aux->left)){//checo se tem sub arvore a esquerda, caso nao tenha trato aqui

        if(p->left == aux){
            p->left = aux->right;
            free(aux);
        }else{
            p->right = aux->right;
            free(aux);
        }

    }else{//tem dois filhos

        node *q = aux;// sera o pai do minimo da sub arvore a direita
        node *aux2 = aux->right;//sera o minimo da sub arvore a direita

        while(aux2->left != NULL){//procuro o minimo da sub arvore a direita
            q = aux2;
            aux2 = aux2->left;
        }//pay attention here

        if(q->right != aux2)
            q->left = aux2->right;//faco o pai do minimo apontar pro que tiver a direita do minimo

        if(p->left == aux){//faco a substituicao
            p->left = aux2;
            aux2->left = aux->left;
            if(aux->right != aux2)
                aux2->right = aux->right;
            free(aux);
        }else{
            p->right = aux2;
            aux2->left = aux->left;
            if(aux->right != aux2)
                aux2->right = aux->right;
            free(aux);
        }
    }


    return R;
}
