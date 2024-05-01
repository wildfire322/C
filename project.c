#include<stdio.h>
#include<stdlib.h>
#define inf 101
int distance[1001];
typedef struct{
    int nv;
    int ne;
    int e[1001][1001];
}*graph;
graph create(int nv,int ne){
    graph g=(graph)malloc(sizeof(graph));
    g->nv=nv;
    g->ne=ne;
    for (int i = 0; i < nv; i++)
    {
        for (int j = 0; j < nv; j++)
        {
            g->e[i][j]=inf;
        }
        
    }
    return g;
}
typedef struct{
    int data;
    int dist;
}node;
typedef struct{
    node a[1002];
    int size;
}minheap;
minheap* create(){
    minheap* h=(minheap*)malloc(sizeof(minheap));
    h->size=0;
    return h;
}
void insert(minheap* h,int data,int dist){
    h->size++;
    for(int i=h->size;i>1;i/=2){
        if(h->a[i/2].dist>dist){
            h->a[i].data=h->a[i/2].data;
            h->a[i].dist=h->a[i/2].dist;
        }else{
           break;
        }
    }
    h->a[h->size].data=data;
    h->a[h->size].dist=dist;
    return;
}
int delete(minheap* h){
    int min=h->a[1].data;
    int child,i;
    h->size--;
    int lastnum=h->a[h->size+1].data;
    int lastdist=h->a[h->size+1].dist;
    for( i=1;i*2<=h->size;i=child){
        child=i*2;
        if(child!=h->size&&h->a[child].dist>h->a[child+1].dist){
            child++;
        }
        if(lastdist>h->a[child].dist){
            h->a[i].data=h->a[child].data;
            h->a[i].dist=h->a[child].dist;
        }
        else{
            break;
        }
    }
    h->a[i].data=lastnum;
    h->a[i].dist=lastdist;
}
int main(){
    int m,n;
    scanf("%d %d",&n,&m);
    graph g=create(n,m);
    for (int i = 0; i < m; i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        g->e[a-1][b-1]=c;
    }
    int k;
    scanf("%d",&k);
    for (int i = 0; i < k; i++)
    {
        for(int j=0;j<g->nv;j++){
            distance[j]=inf;
        }
        int start,l;
        scanf("%d",&start);
        distance[start-1]=0;
        minheap* h=create();
        insert(h,start-1,0);
        while(h->size!=0){
            scanf("%d",&l);
            int u=delete(h);
            if(l!=u+1){
                printf("No\n");
                break;
            }
            for(int v=0;v<g->nv;v++){
                if(g->e[u][v]!=inf&&distance[v]>distance[u]+g->e[u][v]){
                    distance[v]=distance[u]+g->e[u][v];
                    insert(h,v,distance[v]);
                }
            }
        }
}
}