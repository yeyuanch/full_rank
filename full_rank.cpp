#include<bits/stdc++.h>
using namespace std;
int p=998244353,u,g=3,s=30,L=4,n=30,k=100;
int alpha[1005][1005];
set<int>st;
set<int>::iterator it;
int seed;
int mat[5005][5005];
int pq[1005];
int y[1005][1005]; 
int qpow(int a, int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)ans=1ll*ans*a%p;
		a=1ll*a*a%p;
		b>>=1;
	}
	return ans;
}
int main()
{
	printf("Input s, L, n, k\n");
	scanf("%d%d%d%d",&s,&L,&n,&k);
	seed=(unsigned)time(NULL);
	printf("seed: %d\n",seed);
	mt19937 rnd(seed);
	for(int i=1;i<=n;i++)
	{
		int ok;
		do
		{
			while((u=rnd()%p)==0);
			int nw=u;
			ok=1;
			for(int j=0;j<s;j++,nw=1ll*nw*g%p)if(st.count(nw)>0)ok=0;
		}while(ok==0);
		alpha[0][i]=u;
		st.insert(u);
		for(int j=1;j<s;j++)alpha[j][i]=1ll*alpha[j-1][i]*g%p,st.insert(alpha[j][i]);
	}
	int e=((s-L+1)*L*n-L*k)/((L+1)*(s-L+1));
	printf("# of errors: %d\n",e);
	int col=L*(k+e*(s-L+1))+e*(s-L+1),row=L*(s-L+1)*n;
	printf("(# of rows, # of columns): %d %d\n",row,col);
	assert(max(row,col)<5000);
	for(int i=0;i<k;i++)pq[i]=rnd()%p;
	for(int j=1;j<=n;j++)
	{
		for(int i=0;i<s;i++)
		{
			y[i][j]=0;
			if(j<=e)y[i][j]=rnd()%p;
			else
			{
				for(int v=0;v<k;v++)y[i][j]=(1ll*y[i][j]+1ll*pq[v]*qpow(alpha[i][j],v))%p;
			}
		}
	}
	for(int i=1;i<=L;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int i0=0;i0<=s-L;i0++)
			{
				int rw=(i-1)*(s-L+1)*n+(j-1)*(s-L+1)+i0+1;
				assert(rw<=row);
				for(int v=0;v<k+e*(s-L+1);v++)
				{
					int cl=(i-1)*(k+e*(s-L+1))+v+1;
					assert(cl<=col);
					mat[rw][cl]=qpow(alpha[i0][j],v);
				}
				int mm=L*(k+e*(s-L+1));
				for(int v=1;v<=e*(s-L+1);v++)
				{
					int cl=mm+v;
					assert(cl<=col);
					int bs=0;
					bs=y[i0+i-1][j];
					mat[rw][cl]=1ll*bs*qpow(alpha[i0][j],v)%p;
				}
			}
		}
	}
	int cnt=0,cur=1;
	for(int i=1;i<=col;i++)
	{
		int j;
		for(j=cur;j<=row;j++)
		{
			if(mat[j][i]!=0)
			{
				cnt++;
				break;
			}
		}
		if(j>row)continue;
		for(int v=i;v<=col;v++)swap(mat[cur][v],mat[j][v]);
		int inv=qpow(mat[cur][i],p-2);
		for(int v=cur+1;v<=row;v++)
		{
			if(mat[v][i]==0)continue;
			int coef=1ll*inv*mat[v][i]%p;
			for(int t=i;t<=col;t++)mat[v][t]=(mat[v][t]-(1ll*coef*mat[cur][t])%p+p)%p;
		}
		cur++;
	}
	printf("(# of col, rank): %d %d\n",col,cnt);
	return 0;
}
