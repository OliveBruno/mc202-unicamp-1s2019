#include<stdio.h>
#include<stdlib.h>

//#define DEBUGMAIN
//#define DEBUGINSERT
//#define DEBUGTRANSPOSE
//#define DEBUGREVERSE

struct node{

    int d;
    char s[129];
    float f;
    char c;

    char type;
    struct node *next;

};

typedef struct node node;

node* insert_on_list(node **L_given,char command);//takes in a command, creates a new node and stores the "value" according to the command.
node* reverse_list(node **L_given, int a, int b);//takes in a List and an interval range and reverses the nodes on that interval.
node* transpose_list(node **L_given, int a, int b, int c);//takes in a List and an interval range and a position and places the "block" to the right of the given position.
void print_list(node **L_given);//takes in a List and prints the information in it in a single line.
void print_node(node **L_given);//takes in a pointer and prints the value stored on that node.
node* delete_list(node **L_given);//frees a given List.

int main(){//seems ok

    node* L = NULL;
    int N,R;
    char command;
    int a,b,c;

    scanf("%d",&N);

    for(int i = 0;i<N;i++){
        scanf(" %c",&command);
        L = insert_on_list(&L,command);
    }

    print_list(&L);


    scanf("%d",&R);

    for(int i = 0;i<R;i++){

        scanf(" %c",&command);

        if(command == 'r'){

            scanf("%d %d",&a,&b);
            L = reverse_list(&L,a,b);
            print_list(&L);

        }else if(command == 't'){

            scanf("%d %d %d",&a,&b,&c);
            L = transpose_list(&L,a,b,c);
            print_list(&L);

        }
    }

    L = delete_list(&L);

    return 0;
}

node* insert_on_list(node **L_given,char command){//seems ok

    node *L = *L_given;
    node *p = L;

    if(L == NULL){
        L = malloc(sizeof(node));
        L->next = NULL;

        L->type = command;

        //printf("Head.type is %c\n",L->type);

        if(command == 'd'){
            scanf(" %d",&(L->d));
            #ifdef DEBUGMAIN
                printf("inserido = %d\n",(L->d));
            #endif // DEBUGMAIN
        }else if(command == 'f'){
            scanf(" %f",&(L->f));
            #ifdef DEBUGMAIN
                printf("inserido = %.4f\n",(L->f));
            #endif // DEBUGMAIN
        }else if(command == 'c'){
            scanf(" %c",&(L->c));
            #ifdef DEBUGMAIN
                printf("inserido = %c\n",(L->c));
            #endif // DEBUGMAIN
        }else if(command == 's'){
            scanf(" %[^\n]",(L->s));
            #ifdef DEBUGMAIN
                printf("inserido = %s\n",(L->s));
            #endif // DEBUGMAIN
        }

    }else{

        p = L;
        #ifdef DEBUGMAIN
            printf("inserting new element: ");
            print_node(&p);
        #endif // DEBUGMAIN
        while(p->next != NULL){
            p = p->next;
            #ifdef DEBUGMAIN
                printf("inserting new element: ");
                print_node(&p);
            #endif // DEBUGMAIN
        }
        #ifdef DEBUGMAIN
            printf("previous element was: ");
            print_node(&p);
        #endif // DEBUGMAIN

        p->next = malloc(sizeof(node));

        p = p->next;
        p->next = NULL;
        p->type = command;

        #ifdef DEBUGMAIN
            printf("list before insertion: ");
            print_list(&L);
            printf("this last element was garbage\n");
        #endif // DEBUGMAIN

        if(command == 'd'){
            scanf(" %d",&(p->d));
            #ifdef DEBUGMAIN
                printf("inserido = %d\n",(p->d));
            #endif // DEBUGMAIN
        }else if(command == 'f'){
            scanf(" %f",&(p->f));
            #ifdef DEBUGMAIN
                printf("inserido = %.4f\n",(p->f));
            #endif // DEBUGMAIN
        }else if(command == 'c'){
            scanf(" %c",&(p->c));
            #ifdef DEBUGMAIN
                printf("inserido = %c\n",(p->c));
            #endif // DEBUGMAIN
        }else if(command == 's'){
            scanf(" %[^\n]",(p->s));
            #ifdef DEBUGMAIN
                printf("inserido = %s\n",(p->s));
            #endif // DEBUGMAIN
        }
    }


    return L;
}

void print_list(node **L_given){//seems ok

    node *L = *L_given;
    node *p = L;


    while(p!=NULL){
        if(p->type == 'd'){
            printf("%d ",(p->d));
        }else if(p->type == 'f'){
            printf("%.4f ",(p->f));
        }else if(p->type == 'c'){
            printf("%c ",(p->c));
        }else if(p->type == 's'){
            printf("%s ",(p->s));
        }
        p = p->next;
    }
    printf("\n");

}

void print_node(node **L_given){//seems ok

    node *p = *L_given;


    if(p->type == 'd'){
        printf("this node has the int d = %d ",(p->d));
    }else if(p->type == 'f'){
        printf("this node has the float f =  %.4f ",(p->f));
    }else if(p->type == 'c'){
        printf("this node has the char c = %c ",(p->c));
    }else if(p->type == 's'){
        printf("this node has the string s = %s ",(p->s));
    }
    printf("\n");

}

node* transpose_list(node **L_given, int a, int b, int c){//seems ok

    node *L = *L_given;
    node *p = L;
    node *q;
    node *r;
    node *aux;

    if((a == 0) && (c == -1)){//this case does nothing

        return L;
    }

    if(a == b){//this case was being annoying so I treated it separately
        if(a == 0){
            r = L;
            for(int i =0;i<c;i++){
                r=r->next;
            }

            aux = L;
            L = L->next;
            aux->next = r->next;
            r->next = aux;

        }else{

            p = L;
            for(int i = 0;i<a-1;i++){
                p = p->next;
            }

            if(c == -1){
                aux = p->next;
                p->next = aux->next;
                aux->next = L;
                L = aux;
            }else{
                r = L;
                for(int i = 0;i<c;i++){
                    r = r->next;
                }

                aux = p->next;
                p->next = aux->next;
                aux->next = r->next;
                r->next = aux;
            }
        }
        return L;
    }

    if(a == 0){//this is where the code begins for real

        p = L;
        q = L;

        for(int i=0;i<b-1;i++){
            q=q->next;
        }

        #ifdef DEBUGTRANSPOSE
            print_node(&(q->next));
        #endif // DEBUGTRANSPOSE

    }else{

        int i;
        for(i=0;i<a-1;i++){
            p=p->next;
        }
        #ifdef DEBUGTRANSPOSE
            print_node(&(p->next));
        #endif // DEBUGTRANSPOSE

        q = p;

        for(i=0;i<(b-a);i++){
            q=q->next;
        }
        #ifdef DEBUGTRANSPOSE
            print_node(&(q->next));
        #endif // DEBUGTRANSPOSE

    }//when this is done, p points to the node prior to "a" (or p == L) and q points to the node prior to "b".


    if(c == -1){//places a block on the beggining of the list.

        aux = p->next;
        p->next = (q->next)->next;
        (q->next)->next = L;
        L = aux;

    }else{//places the "block" after where r points to

        r = L;
        for(int i = 0;i<c;i++){
            r = r->next;
        }

        if(a == 0 && b == 0){//caso 1

            aux = L;
            L = aux->next;
            aux->next = r->next;
            r->next = aux;

        }else if(a == 0){//caso 2

            aux = L;
            if(b != 1){
                L = q->next;
                q->next = r->next;
            }else{
                L = L->next->next;
                aux->next->next = r->next;
            }
            r->next = aux;


        }else{//caso 3

            aux = p->next;
            p->next = q->next;
            q->next = r->next;
            r->next = aux;
        }
    }
    return L;
}

node* reverse_list(node **L_given, int a, int b){//seems ok

    node *L = *L_given;
    node *p;
    node *q;
    node *aux;
    node *save;
    node *save_next;

    if(a == b)
        return L;

    if(a == 0){//first case.

        if(b == 1){//taking care of the annoying case with the head of my list.
            aux = L;
            L = aux->next;
            aux->next = L->next;
            L->next = aux;
            return L;
        }

        q = L;

        for(int i=0;i<(b-1);i++){//q stops before reaching the end of the interval we want to reverse.
            q = q->next;
        }

        p = L;
        L = (q->next);//start the list at the end of my interval.

        save = p->next;//I will need this later.
        save_next = save->next;

        p->next = (q->next)->next;//makes the previous beginning point to the rest of the list (after the new first).


        for(int j=0;j<(b-a);j++){
            save->next = p;
            p = save;
            save = save_next;
            if(save->next != NULL)
                save_next = save->next;
        }


    }else if(b-a == 1){//second case

        p = L;

        for(int i=0;i<(a-1);i++){//p stops before reaching the start of the interval we want to reverse.
            p = p->next;
        }

        aux = p->next;
        q = aux->next;
        aux->next = q->next;
        q->next = aux;
        p->next = q;

    }else{

        p = L;

        for(int i=0;i<(a-1);i++){//p stops before reaching the start of the interval we want to reverse.
            p = p->next;
        }

        q = L;

        for(int i=0;i<(b-1);i++){//q stops before reaching the end of the interval we want to reverse.
            q = q->next;
        }

        p->next = (q->next);

        save = p->next;//I will need this later.
        save_next = save->next;

        p->next = (q->next)->next;//makes the previous beginning point to the rest of the list (after the new first).

        for(int j=0;j<(b-a);j++){
            save->next = p;
            p = save;
            save = save_next;
            if(save->next != NULL)
                save_next = save->next;
        }

    }

    return L;
}

node* delete_list(node **L_given){//seems ok
    node *L = *L_given;
    node *aux;

    while(L != NULL){
        aux = L->next;
        free(L);
        L = aux;
    }
    return L;
}
