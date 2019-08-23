#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "lab10Lib.h"

int main(){//seems done

    int x;
    char command[50];
    node *R = NULL;

    while(read_input(command)){

        if(!strcmp(command,"inserir")){//done
            R = insert(&R);
        }else if(!strcmp(command,"excluir")){//done
            R = exclude(&R);
        }else if(!strcmp(command,"buscar")){//done

            scanf(" %d",&x);

            if(search(R,x))
                printf("pertence\n");
            else
                printf("nao pertence\n");

        }else if(!strcmp(command,"minimo")){//done
            min(R);
        }else if(!strcmp(command,"maximo")){//done
            max(R);
        }else if(!strcmp(command,"pos-ordem")){//done
            if(!R)
                printf("vazia");
            else
                print_post_order_tree(R);
            printf("\n");
        }else if(!strcmp(command,"em-ordem")){//done
            if(!R)
                printf("vazia");
            else
                print_in_order_tree(R);
            printf("\n");
        }else if(!strcmp(command,"pre-ordem")){//done
            if(!R)
                printf("vazia");
            else
                print_pre_order_tree(R);
            printf("\n");
        }else if(!strcmp(command,"largura")){
            if(!R)
                printf("vazia");
            else
                print_breadth_tree(R);
            printf("\n");
        }

    }

    delete_tree(&R);

    return 0;
}