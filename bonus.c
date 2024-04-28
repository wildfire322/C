#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 20001
int a[MAX_SIZE];
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;
typedef struct LRUCache {
    Node* cache[MAX_SIZE]; 
    Node* head;
    Node* tail;
    int size;
} LRUCache;
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}
LRUCache* createLRUCache() {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        cache->cache[i] = NULL;
    }
    return cache;
}
void removeNode(LRUCache* cache, Node* node) {
    cache->size--;
    cache->cache[node->data] = NULL;
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        Node* temp = node->next;
        if(temp!=NULL)
            temp->prev = NULL;
        free(node);
        node=NULL;
        cache->head = temp;
        return;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        Node* temp = node->prev;
        if(temp!=NULL)
            temp->next = NULL;
        free(node);
        node=NULL;
        cache->tail = temp;
        return;
    }
    free(node);
    node=NULL;
}
void insert(LRUCache* cache, int data) {
    Node* temp = newNode(data);
    cache->size++;
    if (cache->head == NULL) {
        cache->head = temp;
        cache->tail = temp;
    } else {
        cache->tail->next = temp;
        temp->prev = cache->tail;
        cache->tail = temp;
    }
    cache->cache[data] = temp;
}
int main(){
    int k,n,m,s;
    scanf("%d %d %d",&k,&n,&m);
    LRUCache* History = createLRUCache();
    LRUCache* Cache = createLRUCache();
    while(m--){
        scanf("%d",&s);
        if(Cache->cache[s]!=NULL){
            removeNode(Cache,Cache->cache[s]);
            insert(Cache,s);
        }
        else if(History->cache[s]!=NULL){
            removeNode(History,History->cache[s]);
            a[s]++;
            if(a[s]==k){
                if(Cache->size==n) 
                    removeNode(Cache,Cache->head);
                insert(Cache,s);
                a[s]=0;
            }
            else{
                if(History->size==n){
                    a[History->head->data]=0;
                    removeNode(History,History->head);
                }
                insert(History,s);}
        }
        else{
            a[s]++;
            if(History->size==n){
                a[History->head->data]=0;
                removeNode(History,History->head);
            }
            insert(History,s);
        }
    }
    
    if(History->size==0) printf("-\n");
    else{
        Node* temp = History->head;
        while(temp!=NULL){
            printf("%d",temp->data);
            if(temp->next!=NULL) printf(" ");
            temp=temp->next;
        }
        printf("\n");
    }
    if(Cache->size==0) printf("-\n");
    else{
        Node* temp = Cache->head;
        while(temp!=NULL){
            printf("%d",temp->data);
            if(temp->next!=NULL) printf(" ");
            temp=temp->next;
        }
        printf("\n");
    }
    return 0;

    
}