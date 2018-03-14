int dfs(int v,int t){
       if(v==t) return f;
      for(int i=1;i<=n;i++) {
       	 if(!p[i]&&cap[v][i]>0) {
                             p[i]=min(p[v],cap[v][i]));
       	  	int d=dfs(i,t);
       	  	if(d>0){ 	  cap[v][i]-=d;  cap[i][v]+=d;  return d;   	}
       	  }
       }
       return 0;
}
int ford_fulkerson(int s,int t){
             int f,flow=0;
             for( ; ; ){    memset(p,0,sizeof(p));  p[s]=INF;
		if(f=dfs(s,t,INF)) flow+=f;
		 else return  flow;
	}	
}

