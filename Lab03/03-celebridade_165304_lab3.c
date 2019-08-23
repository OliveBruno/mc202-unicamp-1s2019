#include<stdio.h>
#include<string.h>


//#define DEBUG2

int checkend(char *phrase,int *read){//basicamente um printf mas que muda uma variavel de contagem, neste caso "read".
    int st;

    st = scanf("%[^\n]",phrase);
    *(read) = 0;

    return st;
}

typedef struct ppl{
    char name[51];
    int nknow;
    int nknown;// ppl they know and ppl that know them
}ppl;

int main(){

    int counter1,counter2,initia, read = 1;

    ppl allppl[1000];
    char phrase[110], name1[51], name2[51], *aux;


    for(int i = 0;i < 1000;i++){//zera todos os contadores
        allppl[i].nknow = 0;
        allppl[i].nknown = 0;
    }

    int list = 0;

    do{//programa principal acontece aqui

        for(initia=0;initia < strlen(name1);aux++){//zera os nomes a cada iteracao
            name1[initia] = 0;
            name2[initia] = 0;
        }

        #ifdef DEBUG2
        printf("here we go!!\n");
        #endif

        if(read)
            scanf("%[^\n]",phrase);
        aux = strstr(phrase, " conhece");
        getchar();

        #ifdef DEBUG
        printf("%s\n",phrase);
        #endif

        int i = 0;
        while(&phrase[i] != aux){//pega o primeiro nome na frase

            name1[i] = phrase[i];

            i++;
        }

        name1[i] = 0;

        #ifdef DEBUG
        printf("%s size name1 is %d\n",name1,strlen(name1));
        #endif

        i += 9;//aproveito os contadores para pegar o segundo nome
        int j = 0;

        while(i <= strlen(phrase)){//pega o segundo nome na frase

            name2[j] = phrase[i];

            i++;
            j++;
        }

        name2[j] = 0;

        #ifdef DEBUG
        printf("%s size name2 is %d\n",name2,strlen(name2));
        #endif

        //aqui ja tenho os nomes

        counter1=0;
        counter2=0;

        for(int i=0;i < list;i++){//crio a database

            if(strcmp(name1,allppl[i].name) == 0){//compara os nomes com os nomes na lista,
                counter1++;                         //se o nome nao apareceu o counter do nome é 0
                                                    //e este sera adicionado a lista mais a frente
            }

            if(strcmp(name2,allppl[i].name) == 0){
                counter2++;
            }

        }

        if(counter1 == 0){//adiciona os nomes que nao apareceram nos counters a database
            strcpy(allppl[list].name,name1);

            #ifdef DEBUG2
                printf("%s adicionado na posicao %d\n",name1,list);
            #endif
            list++;
        }
        if(counter2 == 0){
            strcpy(allppl[list].name,name2);
            #ifdef DEBUG2
                printf("%s adicionado na posicao %d\n",name2,list);
            #endif
            list++;
        }



        for(int i=0;i < list;i++){//somo 1 nos counters de pessoas conhecidas e pessoas que conhecem

            if(strcmp(name1,allppl[i].name) == 0){
                allppl[i].nknow++;
                #ifdef DEBUG2
                printf("%s conhece %d negos\n",allppl[i].name,allppl[i].nknow);
                #endif

            }

            if(strcmp(name2,allppl[i].name) == 0){
                allppl[i].nknown++;
                #ifdef DEBUG2
                printf("%s eh conhecido por %d negos\n",allppl[i].name,allppl[i].nknown);
                #endif
            }

        }
    }while(checkend(phrase,&read) != EOF);

    #ifdef DEBUG
    printf("%d\n", list);
    #endif

    #ifdef DEBUG2
    printf("loop ended\n");
    #endif

    for(int i=0;i<list;i++){//checa a condicao para ser celebridades

        #ifdef DEBUG
        printf("%s nknow = %d, nknown = %d\n",allppl[i].name,allppl[i].nknow,allppl[i].nknown);
        #endif

        if(allppl[i].nknow==0 && allppl[i].nknown==(list-1)){
            printf("%s e' celebridade.\n",allppl[i].name);
            return 0;
        }
    }

    printf("Nao ha' celebridade.\n");

    return 0;
}
