#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#define DEBUG

typedef struct node{

    char key;
    struct node *left;
    struct node *right;

}node;


void delete_tree(node **R_given);
node* rebuild_tree(node **R_given, char *pre_order, char *in_order, int pre_begin, int pre_end, int in_begin, int in_end);
void print_post_order_tree(node *R);


int main(){
    node *R;
    char pre_order[70], in_order[70];


    while(scanf("%s %s",pre_order,in_order) != EOF){

        R = rebuild_tree(&R,pre_order,in_order,0,strlen(pre_order)-1,0,strlen(pre_order)-1);
        print_post_order_tree(R);
        printf("\n");
        delete_tree(&R);
    }

    return 0;
}


void delete_tree(node **R_given){//not so sure
    node *R = *R_given;


    if(R->left != NULL)
        delete_tree(&(R->left));

    if(R->right != NULL)
        delete_tree(&(R->right));

    free(R);

}


node* rebuild_tree(node **R_given, char *pre_order, char *in_order, int pre_begin, int pre_end, int in_begin, int in_end){
    node *R = *R_given;
    node *left_branch = NULL;
    node *right_branch = NULL;

    int i = in_begin;
    while(in_order[i] != pre_order[pre_begin] && i <= in_end){
        i++;
    }
    #ifdef DEBUG
        printf("--\ni = %d\npre_begin = %d,pre_end = %d\nin_begin = %d,in_end = %d\n--\n",i,pre_begin,pre_end,in_begin,in_end);
    #endif // DEBUG

    if((pre_begin+1 <= pre_begin+i-in_begin) && (in_begin <= i-1)){
        #ifdef DEBUG
            printf("entrei no left_branch\n");
            printf("pre_order = ");
            for(int j = pre_begin+1;j<=pre_begin+i-in_begin;j++){
                printf("%c",pre_order[j]);
            }
            printf(" in_order = ");
            for(int j = in_begin;j<=i-1;j++){
                printf("%c",in_order[j]);
            }
            printf("\n");
        #endif // DEBUG
        left_branch = rebuild_tree(&left_branch,pre_order,in_order,pre_begin+1,pre_begin+i-in_begin,in_begin,i-1);
    }
    if((pre_begin+1+i-in_begin <= pre_end) && (i+1 <= in_end)){
        #ifdef DEBUG
            printf("entrei no right_branch\n");
            printf("pre_order = ");
            for(int j = pre_begin+1+i-in_begin;j<=pre_end;j++){
                printf("%c",pre_order[j]);
            }
            printf(" in_order = ");
            for(int j = i+1;j<=in_end;j++){
                printf("%c",in_order[j]);
            }
            printf("\n");
        #endif // DEBUG
        right_branch = rebuild_tree(&right_branch,pre_order,in_order,pre_begin+1+i-in_begin,pre_end,i+1,in_end);
    }

    R = malloc(sizeof(node));
    R->key = pre_order[pre_begin];
    #ifdef DEBUG
        printf("chave %c inserida\n",R->key);
    #endif // DEBUG
    R->right = right_branch;
    R->left = left_branch;

    return R;
}


void print_post_order_tree(node *R){//not so sure

    if(R != NULL){
        print_post_order_tree(R->left);
        print_post_order_tree(R->right);
        printf("%c",R->key);
    }

}
