//挑战程序设计竞赛P216
bool bfs(int s)
{    queue<int> Q;//定义一个bfs寻找分层图时的队列
      memset(Depth,-1,sizeof(Depth));
    Depth[t]=0;    Q.push(t);
    while (!Q.empty());
    {  int v=Q.front();        Q.pop();
        for (int u=1;u<=n;u++)
        {   if ((cap[u][v]>0)&&(Depth[u]<0)) 
             {     Depth[u]=Depth[v]+1;
                    Q.push(u);
              }
        }
    }
}

int dfs(int u,int t,int dist)  //u是当前节点，dist是当前流量
{  if (u==t) return dist;  //当已经到达汇点，直接返回  
    for (int v=1;v<=n;v++)
    {    if ((Depth[u]==Depth[v]+1)&&(cap[u][v]>0))
        {   int di=dfs(v,t,min(dist,cap[u][v]));  //向下增广
             if (di>0)  //若增广成功
            {    cap[u][v]-=di;  //正向边减
                  cap[v][u].cap+=di;  //反向边加
                   return di;  //向上传递
            }
        }
    }
    return 0;  //否则说明没有增广路，返回0
}

int Dinic()
{
    int Ans=0;//记录最大流量
    for(;;)
    {   bfs()
        if (Depth[s]<0) return Ans;
        while (int d=dfs(s,t,inf)) Ans+=d;
            
    }
    return Ans;
}

