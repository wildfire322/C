#include<stdio.h>
#include<stdlib.h>
#define inf 101
int distance[1001];
int test[1001];
int visited[1001];
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
int findmin(graph g){
    int min=inf;
    int minindex=0;
    for (int i = 0; i < g->nv; i++)
    {
        if (!visited[i]&&distance[i]<min)
        {
            min=distance[i];
            minindex=i;
        }
        
    }
    return minindex;
}
int dijkstra(graph g){
    int kk,z;
    for(int i=0;i<g->nv;i++){
        scanf("%d",&kk);
        distance[i]=inf;
        visited[i]=0;
        test[i]=kk-1;
    }
    distance[test[0]]=0;
    visited[test[0]]=1;
    for (int i = 0; i < g->nv; i++)
    {
        if (i!=test[0]&&g->e[test[0]][i]!=inf)
        {
            distance[i]=g->e[test[0]][i];
        }
        
    }
    for (int i = 1; i < g->nv; i++)
    {
        z=findmin(g);
        if(distance[z]!=distance[test[i]]){
            return 0;
        }
        visited[test[i]]=1;
        for (int j = 0; j < g->nv; j++)
        {
            if (!visited[j]&&g->e[test[i]][j]!=inf&&distance[test[i]]+g->e[test[i]][j]<distance[j])
            {
                distance[j]=distance[test[i]]+g->e[test[i]][j];
            }
    }
    }
    return 1;
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
        g->e[b-1][a-1]=c;
    }
    int k,u;
    scanf("%d",&k);
    for(int i=0;i<k;i++){
        u=dijkstra(g);
        if(u==1){
            printf("Yes\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}