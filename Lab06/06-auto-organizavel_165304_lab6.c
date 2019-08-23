#include <stdio.h>
#include <stdlib.h>

//#define DEBUGMAIN
//#define DEBUGMTF
//#define DEBUGTR
//#define DEBUGCOUNT

struct list{

    int myvalue;
    struct list *next;

};

typedef struct list list;

int N,R;//dados do problema.
int *keys;//as chaves de requisição serao salvas em um vetor pois serao usadas 3 vezes, uma para cada metodo.

void read_input();//le o input e salva os R's em um vetor (keys) para serem usados depois.
int MTF(list **L_given,int *ref_keys);//calcula o custo do MTF.
int TR(list **L_given,int *ref_keys);//calcula o custo do TR.
int Count(list **L_given,int *ref_keys);//calcula o custo do C.
list* new_node_end(list **L_given,int value);//cria um node no final da lista e insere um valor neste node, se a lista estiver vazia, inicia uma lista.
list* delete_list(list **L_given);//da um free em uma lista inteira.
list* create_list(list **L_given,int SIZE);//cria uma lista de tamanho SIZE, com chaves de referencia de 1 ate SIZE.
list* reset_list(list **L_given, int SIZE);//apaga uma lista e cria uma nova para ser usada na prox fucao.
void print_list(list **L_given);//imprime uma lista.

int main(){//seems ok

    int cost_MTF = 0,cost_TR = 0,cost_Count = 0;
    list *L = NULL;

    read_input();

    L = create_list(&L,N);

    #ifdef DEBUGMAIN
        print_list(&L);
    #endif // DEBUGMAIN

    cost_MTF = MTF(&L,keys);

    L = reset_list(&L,N);

    #ifdef DEBUGMAIN
        print_list(&L);
    #endif // DEBUGMAIN

    cost_TR = TR(&L,keys);

    L = reset_list(&L,N);
    cost_Count = Count(&L,keys);

    printf("%d %d %d\n",cost_MTF,cost_TR,cost_Count);

    L = delete_list(&L);
    free(keys);

    return 0;
}

void read_input(){//seems ok

    scanf("%d %d ",&N,&R);

    #ifdef DEBUG
        printf("in read_input : N = %d e R = %d\n",N,R);
    #endif // DEBUG

    keys = malloc(R*sizeof(int));

    for(int i=0;i<R;i++){
        scanf(" %d",&keys[i]);
    }

    #ifdef DEBUG
        for(int i=0;i<R;i++)
            printf("%d ",keys[i]);
        printf("\n");
    #endif // DEBUG

}

list* new_node_end(list **L_given,int value){//seems ok

    list *L;//fica menos confuso assim do que colocando *L_given
    L = *L_given;
    list *p = L;


    #ifdef DEBUG
        printf("entrei!\n");
        printf("in new_node_end:\nL_given = %d e L = %d\n",*L_given,L);
    #endif // DEBUG

    if(L == NULL){
        L = malloc(sizeof(list));
        L->myvalue = value;
        L->next = NULL;

        #ifdef DEBUG
            printf("in new_node_end:\ncabeca = %d, L = %d\n",L->myvalue,L);
        #endif // DEBUG

    }else{
        while(p->next != NULL){
            p = p->next;
        }
        p->next = malloc(sizeof(list));
        p = p->next;
        p->myvalue = value;
        p->next = NULL;

        #ifdef DEBUG
            printf("in new_node_end:\n %d inserido\n",p->myvalue);
        #endif // DEBUG

    }
    return L;
}

list* create_list(list **L_given,int SIZE){//seems ok

    list *L = *L_given;

    for(int i=0;i<SIZE;i++){//crio a minha lista
        L = new_node_end(&L,i+1);
    }
    return L;
}

int MTF(list **L_given,int *ref_keys){//seems ok

    list *L = *L_given;
    list *p;
    list *aux;
    int cost=0;

    if(L == NULL)
        return 0;

    #ifdef DEBUGMTF
        print_list(&L);
        printf("In MTF: cost = %d\n",cost);
    #endif // DEBUGMTF

    for(int i = 0;i<R;i++){

        p = L;

        #ifdef DEBUGMTF
            printf("checking for: %d\n",ref_keys[i]);
        #endif // DEBUGMTF

        if(L->myvalue == ref_keys[i]){//checo o primeiro elemento
            cost++;
            #ifdef DEBUGMTF
                print_list(&L);
                printf("In MTF: cost = %d\n",cost);
            #endif // DEBUGMTF
        }else{
            cost++;
            while(p->next->myvalue != ref_keys[i]){//checo do segundo para frente
                p = p->next;
                cost++;
            }
            cost++;
            aux = p->next;
            p->next = aux->next;
            aux->next = L;
            L = aux;
            #ifdef DEBUGMTF
                print_list(&L);
                printf("In MTF: cost = %d\n",cost);
            #endif // DEBUGMTF

        }
    }
    return cost;
}

int TR(list **L_given,int *ref_keys){//seems ok

    list *L = *L_given;
    list *p = L;
    list *q = p;
    list *aux;
    int cost=0;

    if(L == NULL)
        return 0;

    #ifdef DEBUGTR
        print_list(&L);
        printf("In TR: cost = %d\n",cost);
    #endif // DEBUGTR


    for(int i = 0;i<R;i++){

        p = L;
        q = p;

        if(L->myvalue == ref_keys[i]){//checo o primeiro elemento
            cost++;
            #ifdef DEBUGTR
                print_list(&L);
                printf("In TR: cost = %d\n",cost);
            #endif // DEBUGTR
        }else{
            cost++;
            while(p->next->myvalue != ref_keys[i]){//checo do segundo para frente
                q = p;
                p = p->next;
                cost++;
            }

            cost++;
            aux = p->next;
            p->next = aux->next;
            aux->next = p;
            if(q != p)
                q->next = aux;
            else
                L = aux;

            #ifdef DEBUGTR
                print_list(&L);
                printf("In TR: cost = %d\n",cost);
            #endif // DEBUGTR

        }
    }
    return cost;
}

int Count(list **L_given,int *ref_keys){

    list *L = *L_given;
    list *p = L;
    list *q = p;
    list *aux;
    int *counter;
    int cost = 0;
    int swap;

    if(L == NULL)
        return 0;

    #ifdef DEBUGCOUNT
        print_list(&L);
        printf("IN COUNT: cost = %d\n",cost);
    #endif // DEBUGCOUNT

    counter = calloc(N,sizeof(int));

    for(int i = 0;i<R;i++){

        p = L;

        #ifdef DEBUGCOUNT
            printf("  checking for: %d\n",ref_keys[i]);
        #endif // DEBUGCOUNT

        if(L->myvalue == ref_keys[i]){//checo o primeiro elemento
            cost++;
            counter[0]++;
            #ifdef DEBUGCOUNT
                print_list(&L);
                printf("\tcounter:   ");
                for(int var = 0;var<N-1;var++)
                    printf("%d ",counter[var]);
                printf("%d\n",counter[N-1]);
                printf("IN COUNT: cost = %d\n",cost);
            #endif // DEBUGCOUNT
        }else{
            cost++;
            int j = 1;
            while(p->next->myvalue != ref_keys[i]){//checo do segundo para frente
                p = p->next;
                cost++;
                j++;
            }
            cost++;
            counter[j]++;


            int k = j-1;
            while(counter[j]>=counter[k] && k>=0){
                swap = counter[j];
                counter[j] = counter[k];
                counter[k] = swap;
                #ifdef DEBUGCOUNT
                    printf("\tcounter:   ");
                    for(int var = 0;var<N-1;var++)
                        printf("%d ",counter[var]);
                    printf("%d\n",counter[N-1]);
                    printf("In COUNT: cost = %d\n",cost);
                    printf("k = %d, j = %d\n",k,j);
                #endif // DEBUGCOUNT
                k--;
                j--;
            }


            #ifdef DEBUGCOUNT
                printf("j = %d----\n",j);
            #endif // DEBUGCOUNT
            q = L;
            while(j>1){
                q = q->next;
                j--;
            }

            aux = p->next;
            p->next = aux->next;


            if(q != L || j == 1){
                aux->next = q->next;
                q->next = aux;
            }else{
                aux->next = L;
                L = aux;
            }

            #ifdef DEBUGCOUNT
                print_list(&L);
                printf("\tcounter:   ");
                for(int var = 0;var<N-1;var++)
                    printf("%d ",counter[var]);
                printf("%d\n",counter[N-1]);
                printf("In COUNT: cost = %d\n",cost);
            #endif // DEBUGCOUNT

        }
    }
    free(counter);

    return cost;
}

list* delete_list(list **L_given){//seems ok

    list *L = *L_given;
    list *aux;

    if(L != NULL){
        while(L->next != NULL){

            aux = L->next;
            free(L);
            L = aux;

        }
        free(L);
    }
    L = NULL;
    return L;
}

list* reset_list(list **L_given, int SIZE){//seems ok

    list *L = *L_given;

    L = delete_list(&L);
    L = create_list(&L,SIZE);

    return L;
}

void print_list(list **L_given){//seems ok

    list *L = *L_given;
    list *p = L;

    printf("\tYour list: ");

    while(p!=NULL){
        printf("%d ",p->myvalue);
        p=p->next;
    }
    printf("\n");

}
