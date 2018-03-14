struct Treap 
{ int tot,root;//  节点总数，根节点。 
  int ls[N];//  左儿子 
  int rs[N];  //  右儿子 
  int aux[N];//  随机数 
  int key[N];//  节点值 
  int size[N];//  子树大小 

  void l_rot(int &k) 
  { int y=rs[k]; 
    //PushDown(k);PushDown(y);若打了标记，这里要下移。 
    //Move k’s To y’s   这里一般是把所有k的标记传给y。 
    rs[k]=ls[y]; 
    ls[y]=k; 
    //Update(k);更新k的标记。 
    k=y; 
  } 
  void r_rot(int &k) 
  { int y=ls[k]; 
    //PushDown(k);PushDown(y);标记下移 
    //Move k’s To y’s 传标记 
    ls[k]=rs[y]; 
    rs[y]=k; 
    //Update(k);更新标记 
    k=y; 
  } 
  void Insert(int &k,int x)//在主程序中调用该函数要这样写Insert(root,x); 
  { if(!k) 
    { k=++tot;//创立新节点。 
      key[k]=x;
      ls[k]=rs[k]=0; 
      aux[k]=rand(); 
      size[k]=1; 
      return; 
    } 
    if(x<key[k]) 
    { ins(ls[k],x); 
      if(aux[k]>aux[ls[k]])r_rot(k);//rot(k,1) 
    }else 
    { ins(rs[k],x); 
      if(aux[k]>aux[rs[k]])l_rot(k); //rot(k,1) 
    } 
    //Update(k); 
  }  
  void Delete(int &k,int x) //在主程序中调用该函数要这样写Delete(root,x); 
  //删除操作一般比较繁琐，但下面的代码却巧妙的回避了这一点。 
  { int ret; 
    //PushDown(k);  
    if(key[k]==x||x<key[k]&&!ls[k]||x>key[k]&&!rs[k]) 
    { if(!ls[k]||!rs[k]) 
      { ret=key[k]; 
        k=ls[k]+rs[k];  
      }else 
	    ret=key[k]=Delete(ls[k],x+1);   
    }else 
	   ret=( key[k]<x?Delete(rs[k],x);Delete(ls[k],x) ); 
     //Update(k); 
    return ret; 
  } 
  int Findpre(int x) 
  {  int now=root,ret=0; 
     while(Pushdown(now),now)  
      if(key[now]<x) 
      { ret=max(ret,key[now]); 
        now=rs[now];   
      }else now=ls[now];  
    return ret; 
  } 
  int Findsuc(int x) 
  { int now=root,ret=inf; 
    while(PushDown(now),now)    
      if(key[now]>x) 
      { ret=min(ret,key[now]); 
        now=ls[now]; 
      }else now=rs[now];   
    return ret; 
  } 
  int Findkth(int k) 
  { int now=root,tmp; 
    for(;;) 
    { //PushDown(now); 
      tmp=size[ls[k]]; 
      if(tmp+1==k)return key[k]; 
      if(tmp>k)now=ls[now];else 
      now=rs[now],k-=tmp+1; 
    } 
  } 
} 

 void l_rot(int &k,) 
  { int y=rs[k]; 
    //PushDown(k);PushDown(y);若打了标记，这里要下移。 
    //Move k’s To y’s   这里一般是把所有k的标记传给y。 
    rs[k]=ls[y]; 
    ls[y]=k; 
    //Update(k);更新k的标记。 
    k=y; 
  } 
