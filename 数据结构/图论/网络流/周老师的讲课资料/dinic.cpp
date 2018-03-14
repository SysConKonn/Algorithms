//��ս������ƾ���P216
bool bfs(int s)
{    queue<int> Q;//����һ��bfsѰ�ҷֲ�ͼʱ�Ķ���
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

int dfs(int u,int t,int dist)  //u�ǵ�ǰ�ڵ㣬dist�ǵ�ǰ����
{  if (u==t) return dist;  //���Ѿ������㣬ֱ�ӷ���  
    for (int v=1;v<=n;v++)
    {    if ((Depth[u]==Depth[v]+1)&&(cap[u][v]>0))
        {   int di=dfs(v,t,min(dist,cap[u][v]));  //��������
             if (di>0)  //������ɹ�
            {    cap[u][v]-=di;  //����߼�
                  cap[v][u].cap+=di;  //����߼�
                   return di;  //���ϴ���
            }
        }
    }
    return 0;  //����˵��û������·������0
}

int Dinic()
{
    int Ans=0;//��¼�������
    for(;;)
    {   bfs()
        if (Depth[s]<0) return Ans;
        while (int d=dfs(s,t,inf)) Ans+=d;
            
    }
    return Ans;
}

