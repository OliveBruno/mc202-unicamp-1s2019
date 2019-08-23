#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//MY G FUNCTION FOR THIS JUST RETURNS 1, I HONESTLY COULDNT BE BOTHERED TO MAKE ANOTHER HASHING BUT CHANGING IT TO ANYTHING ELSE SHOULD STILL WORK. (HOPEFULLY)



typedef struct ht{//hashing table

    char str_input[251];
    int index;

}ht;

unsigned long djb2(char *str);//This function was given
unsigned long g(char *str);//Will be another hashing if I can be bothered (couldn't)
int read_command(char *command);//a scanf that returns 0 if its an 'f' and 1 otherwise
int search_table(ht *Table, char *phrase, int m, int *tracker);//searches an element, returns 1 if it finds it and and then stores the position of that element on the table on "tracker" variable
void insert_table(ht **Table, char *phrase, int m, int *index_counter);//inserts a new element on the table and updates the index_counter
void remove_from_table(ht **Table,char* phrase, int m);//removes an element from the table and puts a -2 in its index to show its been used before

int main(){
    ht* h_table;
    int m = 6949;
    char command;
    char phrase[251];
    int index_counter = 0;
    int tracker;

    h_table = malloc(m*sizeof(ht));

    for(int i = 0;i<m;i++){
        h_table[i].index = -1;//-1 means the spot has always been empty
    }

    while(read_command(&command)){
        if(command == 'i'){
            scanf("%s",phrase);

            insert_table(&h_table,phrase,m,&index_counter);

        }else if(command == 'b'){
            scanf("%s",phrase);


            if(search_table(h_table,phrase,m,&tracker)){
                printf("encontrado %d\n",h_table[tracker].index);
            }else{
                printf("nao encontrado\n");
            }

        }else if(command == 'r'){
            scanf("%s",phrase);

            remove_from_table(&(h_table),phrase,m);
        }

    }

    free(h_table);

    return 0;
}

int read_command(char *command){

    scanf("%c", command);

    if(*command == 'f')
        return 0;
    else
        return 1;

}

unsigned long djb2(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 32 + hash + c

    return hash;
}

unsigned long g(char *str){//if I am not too bored I'll change this later but for now this should work

    return 1;
}

int search_table(ht *Table, char *phrase, int m, int *tracker){

    int pos;

    pos = (djb2(phrase))%m;

    for(int i = 1; Table[pos].index != -1;i++){

        if(!strcmp(Table[pos].str_input,phrase)){
            *tracker = pos;
            return 1;
        }

        pos = (djb2(phrase)+ i*g(phrase))%m;

    }

    return 0;
}

void insert_table(ht **Table, char *phrase,int m,int *index_counter){//seems ok
    int pos;
    int i = 1;
    int dummy;

    if(search_table(*Table,phrase,m,&dummy))//if its already on the table this does nothing
        return;

    pos = (djb2(phrase))%m;

    while((*Table)[pos].index != -1 && (*Table)[pos].index != -2){
        pos = (djb2(phrase)+ i*g(phrase))%m;
        i++;
    }

    (*Table)[pos].index = *index_counter;
    strcpy((*Table)[pos].str_input,phrase);
    *index_counter = *index_counter + 1;

}

void remove_from_table(ht **Table,char* phrase, int m){

    int tracker;

    if(!search_table(*Table,phrase,m,&tracker)){//if its not on the table this does nothing
        return;
    }else{
        (*Table)[tracker].index = -2;
        strcpy((*Table)[tracker].str_input,"heloloalosl_THIS_IS_EMPTY_aodhfduhafe\0");
    }


}


