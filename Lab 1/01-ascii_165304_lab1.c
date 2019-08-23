#include<stdio.h>

int main(){
    int i,j;

    printf("      +0 +1 +2 +3 +4 +5 +6 +7 \n");//cabecalho
    printf("    +------------------------ \n");


    for(i = 32;i<=127;i++){

        printf("%3d |",i);

        for(j = 0;j<=7;j++){

            if((i+j) == 127)
                printf("   ");
            else
                printf("%3c",i+j);

        }

        i += j- 1;

        printf(" \n");

    }


    return 0;
}
