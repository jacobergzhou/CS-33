#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* thread (void* vargp);
static int thread_cnt;

struct node {//create a node that is that is used to implement the tree
    int node;
    int label;
} ;


int main (int argc, char* argv[]){
    struct node root;
    if (argc != 2) {
        printf("Wrong # of args, quiting\n");
        exit(1);
    }
    
    thread_cnt = atoi(argv[1]);
    if (thread_cnt <= 0){
        printf("Wrong # of order of Leonardo Number, quiting\n");
        exit(2);
    }//check for the wrong condition
    
    if (thread_cnt == 1){
        printf("[0]\n");
        exit(0);
    }
    
    root.node = 0;
    root.label = thread_cnt;
    
    
    pthread_t tid;
    thread_cnt = 0;
    
    void* tomb = malloc(sizeof(int));
    tomb = NULL;
    printf("(0\n");
    pthread_create(&tid, NULL, thread, (void*)&root);
    pthread_join(tid, tomb);
    printf("0)\n");
    free(tomb);
    
    return 0;
}




void* thread(void* vargp) {
    struct node* parent_node  = (struct node*)(vargp);
    int* l = malloc(sizeof(int));
    *l = 0;
    if (parent_node -> label <= 1){//when it is the end node
        *l = 1;
        printf ("[%d]\n", parent_node->node);
        pthread_exit(l);
    }
    if (parent_node -> label > 1){//there exists more node on the left side
        struct node* left_node = malloc(sizeof(struct node));
        pthread_t tid;
        void* p_l = NULL;
        left_node->label = parent_node->label - 1;
        left_node->node = parent_node->node +1;
        if (left_node->label > 1){
            printf("(%d\n", left_node->node);
        }
        
        thread_cnt++;
        pthread_create(&tid, NULL, thread, left_node);
        pthread_join(tid, (void**)&p_l);
        if (left_node->label > 1){
            printf("%d)\n", left_node->node);
        }
        (*(int*)l) += (*(int*)p_l + 1);
        free(p_l);
        free(left_node);
    }
    if (parent_node->label - 2 >= 0){//there exists more node on the right side
        struct node* right_node = malloc(sizeof(struct node));
        pthread_t tid;
        void* p_l = NULL;
        right_node->label = parent_node->label - 2;
        right_node->node = parent_node->node + 1 + (*(int*)l-1);
        if (right_node->label > 1){
            printf("(%d\n", right_node->node);
        }
        
        
        thread_cnt++;
        pthread_create(&tid, NULL, thread, right_node);
        pthread_join(tid, (void**)&p_l);
        if (right_node->label > 1){
            printf("%d)\n", right_node->node);
        }
        
        (*(int*)l) += *(int*)p_l;
        free(p_l);
        free(right_node);
    }
    
    pthread_exit(l);
    
    
    return  NULL;
    
}
