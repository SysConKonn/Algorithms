 int bfs(int s,int t){    //p[i]表示i点的流量,    pre[i]表示i点的流量从哪里来
       queue<int> q;       memset(p,0,sizeof(p));       p[s]=inf;      q.push(s);          
        while(!q.empty()){    
                int ans=q.front();              q.pop();              
                for(i=1;i<=n;i++){                  
                       if(!p[i]&&cap[ans][i]){                     
                            p[i]=min(p[ans],cap[ans][i]);                     
                            pre[i]=ans;  q.push(i);
                            if(i==t)   return (p[i]);        
                      }   
                 }     
          }         
 int Edmonds-Karp (int s,int t){
          while(mi=bfs(s,t){
                 sum+=mi;          int tmp=t;          
                 for(int i=t;i!=s;i=pre[i]){      cap[pre[i][i]-=mi;    cap[i][pre[i]]+=mi;     }
          }    
 }  

