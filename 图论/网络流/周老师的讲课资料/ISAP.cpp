
const int MAXN=1100; 
int cap[MAXN][MAXN]; 
int gap[MAXN],dis[MAXN],pre[MAXN],cur[MAXN]; 
int isap(int s,int t) 
{   int flow=0;
   
    memset(cur,0,sizeof(cur)); //用于回溯 
    memset(dis,0,sizeof(dis)); //到汇的的距离 
    memset(gap,0,sizeof(gap));  //gap[i]高度为i的点的个数 
    BFS();
    for(int i=1;i<=n;i++) gap[dis[i]]++;
    int u=s;
    while(dis[s]<=n) 
    {  if(u==t){
            int d=INF;
	    	for(int i=t;i!=s;i=pre[i])
	    		 d=min(a,cap[pre[i]][i]);
	    	for(int i=t;i!=s;i=pre[i]){
	    		cap[pre[i]][i]-=d;
	    		cap[i][pre[i]]+=d;
        	}
        	flow+=d;
        	u=s;
        }
        int ok=0;
        for(int v=cur[u];v<=n;v++) 
            if(cap[u][v] && dis[u]==dis[v]+1) 
            {   ok=1;
                pre[v]=u; 
                u=cur[u]=v; 
                break;
            }
        if(!ok) {
            int mindis=n; 
            for(int v=1;v<=n;v++) 
               if(cap[u][v])   mindis=(mindis,dis[v]); 
            
            if((--gap[dis[u]])==0) break; 
            gap[dis[u]=mindis+1]++; 
            cur[u]=1;
            u=pre[u]; 
    } 
    return maxflow; 
}
