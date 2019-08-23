#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define DEBUG
#define WHEN_DONE

int inserted_value=0,seq_size=0,begining=0,ending=1,vet_size=0;

int readinput(char *command);
int* add_first(int *list);
int* remove_first(int *list);
int* remove_last(int *list);
int* add_last(int *list);
int* adaptsize(int *list);
int* double_size(int *list);
int* halve_size(int *list);

int main(){

    int *list;
    char command[20];

    list = malloc(2*sizeof(int));
    vet_size = 2;

    list[0] = -1000;//inicializo assim just because
    list[1] = -1000;


    while(readinput(command)){

        #ifdef DEBUG

            printf("command = %s\n",command);

        #endif // DEBUG

        if(strcmp(command,"insert-first\0") == 0){

            #ifdef DEBUG
                printf("inserted_value = %d\n",inserted_value);
            #endif // DEBUG

            list=add_first(list);

        }else if(strcmp(command,"remove-first\0") == 0){
            if(seq_size>0)
                list=remove_first(list);
        }else if(strcmp(command,"print-first\0") == 0){
            #ifdef DEBUG
                printf("begining = %d\n",begining);
            #endif // DEBUG
            if(seq_size>0)
                printf("%d\n",list[begining]);
        }else if(strcmp(command,"insert-last\0") == 0){

            #ifdef DEBUG
                printf("inserted_value = %d\n",inserted_value);
            #endif // DEBUG

            list = add_last(list);

        }else if(strcmp(command,"remove-last\0") == 0){
            if(seq_size>0)
                list=remove_last(list);
        }else if(strcmp(command,"print-last\0") == 0){
            #ifdef DEBUG
                printf("ending = %d\n",ending);
            #endif // DEBUG
            if(seq_size>0)
                printf("%d\n",list[ending]);
        }else if(strcmp(command,"is-empty\0") == 0){
            if(seq_size==0)
                printf("yes\n");
            else
                printf("no\n");

        }

    #ifdef DEBUG
    for(int i=0;i<vet_size;i++){
        printf("list[%d] = %d\n",i,list[i]);
    }
    #endif // DEBUG

    }// end of while

    free(list);

    return 0;
}



int readinput(char *command){//le o comando e retorna 0 se for exit, retorna 1 cc

    #ifdef DEBUG
        printf("\nTo Lendo#######################\n");
        printf("in readinput: seq_size = %d\n",seq_size);
    #endif // DEBUG

    scanf("%s",command);

    if((strcmp(command,"exit\0"))==0){
        return 0;
    }else if((strcmp(command,"insert-first\0")==0)||(strcmp(command,"insert-last\0")==0)){
        scanf(" %d",&inserted_value);
        return 1;
    }else
        return 1;

}
int* adaptsize(int *list){//define os criterios para aumentar ou diminuir o tamanho do vetor quando necessario

    if(vet_size == (seq_size)){

        #ifdef DEBUG
            printf("in adaptsize: vet_size = %d, (seq_size) = %d\n",vet_size,(seq_size));
            printf("dobrou!!\n");
        #endif // DEBUG

        list=double_size(list);

    }else if(((float)vet_size/4 >= (seq_size)) && (vet_size > 2)){

        #ifdef DEBUG
            printf("in adaptsize: seq_size = %d\n",seq_size);
            printf("in adaptsize: (float)vet_size/4 = %.2f, (seq_size) = %d\n",(float)vet_size/4,(seq_size));
            printf("dividiu!!\n");
        #endif // DEBUG

        list=halve_size(list);
    }


    #ifdef DEBUG
        for(int i=0;i<vet_size;i++)
            printf("in adaptsize: list[%d] = %d\n",i,list[i]);
    #endif // DEBUG

    return list;
}
int* add_first(int *list){
    list=adaptsize(list);


    #ifdef DEBUG
        for(int i=0;i<vet_size;i++)
            printf("in add_first: list[%d] = %d\n",i,list[i]);
    #endif // DEBUG

    if((seq_size)==0){
        begining = 0;
        ending = 0;
        list[0] = inserted_value;
        seq_size++;

        #ifdef DEBUG
            printf("in add_first: list[begining] = %d, vet_size = %d,list_size = %d\n",list[begining],vet_size,seq_size);
        #endif // DEBUG

    }else if(begining == 0){
        begining = (vet_size-1);

        list[begining] = inserted_value;
        seq_size++;

        #ifdef DEBUG
            printf("in add_first: list[begining] = %d, vet_size = %d,list_size = %d\n",list[begining],vet_size,seq_size);
        #endif // DEBUG

    }else{
        begining--;
        list[begining] = inserted_value;
        seq_size++;
        #ifdef DEBUG
            printf("in add_first: list[begining] = %d, vet_size = %d,list_size = %d\n",list[begining],vet_size,seq_size);
        #endif // DEBUG
    }

    #ifdef DEBUG
        printf("in add_first: begining = %d, ending = %d, tam_list = %d\n",begining,ending,vet_size);
    #endif // DEBUG

    return list;
}
int* remove_first(int *list){

    if(seq_size!=0){
        if(begining == vet_size-1){
            list[begining]=-999;
            begining = 0;
            seq_size--;
        }else{
            list[begining]=-999;
            begining++;
            seq_size--;
        }

        list=adaptsize(list);
    }
    return list;
}
int* remove_last(int *list){
    if(seq_size!=0){
        if(ending == 0){
            list[ending]=-999;
            ending = vet_size-1;
            seq_size--;
        }else{
            list[ending]=-999;
            ending--;
            seq_size--;
        }
        list=adaptsize(list);
    }
    return list;
}
int* add_last(int *list){
    list=adaptsize(list);

    #ifdef DEBUG
        for(int i=0;i<vet_size;i++)
            printf("in add_last: list[%d] = %d\n",i,list[i]);
    #endif // DEBUG

    if((seq_size)==0){
        begining = 0;
        ending = 0;
        list[ending] = inserted_value;
        seq_size++;

        #ifdef DEBUG
            printf("in add_last: list[ending] = %d, vet_size = %d,list_size = %d\n",list[ending],vet_size,seq_size);
        #endif // DEBUG

    }else if(ending == (vet_size-1)){
        ending = 0;

        list[ending] = inserted_value;
        seq_size++;

        #ifdef DEBUG
            printf("in add_last: list[ending] = %d, vet_size = %d,list_size = %d\n",list[ending],vet_size,seq_size);
        #endif // DEBUG

    }else{
        ending++;
        list[ending] = inserted_value;
        seq_size++;
        #ifdef DEBUG
            printf("in add_last: list[ending] = %d, vet_size = %d,list_size = %d\n",list[ending],vet_size,seq_size);
        #endif // DEBUG
    }

    #ifdef DEBUG
        printf("in add_last: begining = %d, ending = %d, tam_list = %d\n",begining,ending,vet_size);
    #endif // DEBUG

    return list;
}
int* double_size(int *list){

    int *new_vet;
    new_vet = malloc(2*vet_size*sizeof(int));

    int j=0;
    for(int i = begining;i < vet_size;i++){
        new_vet[j] = list[i];
        #ifdef DEBUG
            printf("new_vet[%d] = %d\n",j,new_vet[j]);
        #endif // DEBUG
        j++;
    }

    for(int i = 0;(i <= ending) && (j < vet_size);i++){
        new_vet[j] = list[i];
        #ifdef DEBUG
            printf("new_vet[%d] = %d\n",j,new_vet[j]);
        #endif // DEBUG
        j++;
    }

    begining = 0;
    ending = vet_size-1;

    #ifdef DEBUG
        printf("after doubling: begining = %d, ending = %d\n",begining,ending);
    #endif // DEBUG

    vet_size *= 2;

    #ifdef DEBUG
    printf("after doubling: vet_size = %d\n",vet_size);
    #endif // DEBUG

    free(list);

    #ifdef DEBUG
        for(int i=0;i<vet_size;i++)
            printf("in double_size: vet[%d] = %d\n",i,new_vet[i]);
    #endif // DEBUG

    return new_vet;

}
int* halve_size(int *list){

    int *new_vet;
    new_vet = malloc(0.5*vet_size*sizeof(int));

    if(ending>begining){
        int j=0;
        for(int i = begining;i <= ending;i++){
            new_vet[j] = list[i];
            #ifdef DEBUG
                printf("new_vet[%d] = %d\n",j,new_vet[j]);
            #endif // DEBUG
            j++;

        }
    }else{

        int j=0;
        for(int i = begining;i < vet_size;i++){
            new_vet[j] = list[i];
            #ifdef DEBUG
                printf("new_vet[%d] = %d\n",j,new_vet[j]);
            #endif // DEBUG
            j++;
        }


        for(int i = 0;(i <= ending) && (j < seq_size);i++){
            new_vet[j] = list[i];
            #ifdef DEBUG
                printf("new_vet[%d] = %d\n",j,new_vet[j]);
            #endif // DEBUG
            j++;
        }
    }

    begining = 0;
    ending = seq_size-1;

    #ifdef DEBUG
        printf("after halving: begining = %d, ending = %d\n",begining,ending);
    #endif // DEBUG

    vet_size *= 0.5;

    #ifdef DEBUG
    printf("after halving: vet_size = %d\n",vet_size);
    #endif // DEBUG

    free(list);

    #ifdef DEBUG
        for(int i=0;i<vet_size;i++)
            printf("in halve_size: new_vet[%d] = %d\n",i,new_vet[i]);
    #endif // DEBUG

    return new_vet;
}
