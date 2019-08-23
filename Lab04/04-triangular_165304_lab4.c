#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//#define DEBUG

int main(){

    int n;
    double sum=0,average,deviation,total=0,**input;

    scanf("%d ",&n);//coleta o n

    #ifdef DEBUG
        printf("%d\n",n);
    #endif

    input = malloc(n*sizeof(double*));

    for(int i=0;i<n;i++){//cria a matriz

        input[i] = malloc((i+1)*sizeof(double));

    }


    for(int i=0;i<n;i++){//pega os valores, guarda na matriz e ja vai somando todos os valores para depois tirar a media
        for(int j=0;j<=i;j++){
            scanf("%lf ",&input[i][j]);
            sum += input[i][j];
            #ifdef DEBUG
                printf("input[%d][%d] = %f, e sum = %f\n",i,j,input[i][j],sum);
            #endif
        }

    }


    //calculando a media

    total = (n*(n+1)/2);
    average = sum/total;

    #ifdef DEBUG
        printf("average = %f\n",average);
    #endif

    //calculando o desvio padrao
    sum = 0;

    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            sum += pow((input[i][j]-average),2);

            #ifdef DEBUG
                 printf("sum(for deviation) = %f\n",sum);
            #endif
        }

    }

    deviation = sqrt(sum/total);

    #ifdef DEBUG
        printf("deviation = %f\n",deviation);
    #endif

    for(int i=0;i<n;i++){//calcula a matrix de output
        for(int j=0;j<=i;j++){

            input[i][j] = (input[i][j]-average)/deviation;

            #ifdef DEBUG
                printf("input[%d][%d] = %f, e sum = %f\n",i,j,input[i][j],sum);
            #endif
        }

    }

    for(int i=0;i<n;i++){//imprime a matrix de output
        for(int j=0;j<=i;j++){

            printf("%.12lf ",input[i][j]);

            #ifdef DEBUG
                printf("input[%d][%d] = %f, e sum = %f\n",i,j,input[i][j],sum);
            #endif
        }
        //printf("%12f",input[i][j]);

        printf("\n");

    }

    printf("\n");
    printf("%.12lf %.12lf \n",average,deviation);

    for(int i=1;i<n;i++){//libera a memoria

        free(input[i]);

    }

    free(input);


    return 0;
}
