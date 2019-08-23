#include<stdio.h>

int main(){

    int n,freq,i;
    char c;

    do{

        scanf("(%d,%d,%c)",&n,&freq,&c);

        printf("%3d |",n);

        for(i = 0;i<freq;i++){
            printf("%c",c);
        }
        printf(" %d\n",freq);

        scanf(" ");

    }while(scanf("(%d,%d,%c)",&n,&freq,&c) != EOF);


    return 0;
}
