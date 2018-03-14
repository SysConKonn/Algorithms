struct Treap 
{ int tot,root;//  �ڵ����������ڵ㡣 
  int ls[N];//  ����� 
  int rs[N];  //  �Ҷ��� 
  int aux[N];//  ����� 
  int key[N];//  �ڵ�ֵ 
  int size[N];//  ������С 

  void l_rot(int &k) 
  { int y=rs[k]; 
    //PushDown(k);PushDown(y);�����˱�ǣ�����Ҫ���ơ� 
    //Move k��s To y��s   ����һ���ǰ�����k�ı�Ǵ���y�� 
    rs[k]=ls[y]; 
    ls[y]=k; 
    //Update(k);����k�ı�ǡ� 
    k=y; 
  } 
  void r_rot(int &k) 
  { int y=ls[k]; 
    //PushDown(k);PushDown(y);������� 
    //Move k��s To y��s ����� 
    ls[k]=rs[y]; 
    rs[y]=k; 
    //Update(k);���±�� 
    k=y; 
  } 
  void Insert(int &k,int x)//���������е��øú���Ҫ����дInsert(root,x); 
  { if(!k) 
    { k=++tot;//�����½ڵ㡣 
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
  void Delete(int &k,int x) //���������е��øú���Ҫ����дDelete(root,x); 
  //ɾ������һ��ȽϷ�����������Ĵ���ȴ����Ļر�����һ�㡣 
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
    //PushDown(k);PushDown(y);�����˱�ǣ�����Ҫ���ơ� 
    //Move k��s To y��s   ����һ���ǰ�����k�ı�Ǵ���y�� 
    rs[k]=ls[y]; 
    ls[y]=k; 
    //Update(k);����k�ı�ǡ� 
    k=y; 
  } 
