#include<stdio.h>
#include<math.h>
int zero(double op[],int n){
    for (int i = 0; i < n; i++)
    {
        if(op[i]>=1e-6||op[i]<=-(1e-6)){
           return 0;
        }
    }
    return 1;
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    double a[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int k = 0; k < n; k++)
        {
            scanf("%lf",&a[i][k]);
        }
        
    }
    double q[m][n];//全部的q
    double qq[n];//q弯弯
    for (int i = 0; i < n; i++)
    {
        qq[i]=a[0][i];
        q[0][i]=a[0][i];
    }
    if(zero(qq,n)){
        printf("YES 1");
        return 0;
    }
    double oier=0;
    for (int nm = 0; nm < n; nm++)
            {
                oier+=qq[nm]*qq[nm];
            }
        oier=sqrt(oier);
    for(int fuck=0;fuck<n;fuck++){
        q[0][fuck]/=oier;
    }
    for (int i = 1; i < m; i++)
    {
        for (int pl = 0; pl < n; pl++)
        {
           qq[pl]=a[i][pl];//先把q弯弯赋成ai
        }
        
        for (int k = 0; k < i; k++)//一共需要减去i次,这里的i和题目的i不一样，比题目里的i少一
        {
            double sum=0;
            for (int nm = 0; nm < n; nm++)
            {
                sum+=q[k][nm]*a[i][nm];//计算qk transfer与ai的点积
            }
            
            for (int u = 0; u < n; u++)//对向量的每一位做操作
            {
                qq[u]-=sum*q[k][u];
            }
            
        }
        if(zero(qq,n)){
            printf("YES %d",i+1);
            return 0;
        }
        double pow=0;
        for (int nmsl = 0; nmsl < n; nmsl++)
        {
            pow+=qq[nmsl]*qq[nmsl];
        }
        pow=sqrt(pow);
        for (int cs = 0; cs < n; cs++)
        {
            q[i][cs]=qq[cs]/pow;
        }
        
    }
printf("NO\n");
printf("%.2lf",q[m-1][0]);
for (int i = 1; i < n; i++)
{
    printf(" %.2lf",q[m-1][i]);
}
return 0;

    
}