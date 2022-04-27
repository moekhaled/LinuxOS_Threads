#include <iostream>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;
int a[50][50],b[50][50],mul[50][50],mul2[50][50],m,n,k;
int arr[50*50];
unordered_map<int,pair<int,int>> thread_id;

void* multplication(void *arg){
            int index=*(int*)arg;
            auto x=thread_id[index];
            for(int i=0;i<m;++i)
            mul[x.first][x.second]+=a[x.first][i]*b[i][x.second];
}

void* multplication2(void *arg){
            int index=*(int*)arg;
            for(int i=0;i<k;++i)
            for(int j=0;j<m;++j)
            mul2[index][i]+=a[index][j]*b[j][i];
}
void init(){
    for(int i=0;i<50*50;++i)arr[i]=i;
    }
int main()
{
    init();
    freopen("matrixinput.txt","r",stdin);
    freopen("matrixoutput.txt","w",stdout);
    cin>>n>>m;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            cin>>a[i][j];
    cin>>m>>k;
    for(int i=0;i<m;++i)
        for(int j=0;j<k;++j)
            cin>>b[i][j];
    clock_t st=clock();
    pthread_t p[n][k];
    int cnt=0;
    //create thread call multplication 1 every element in matrix has one thread
    for(int i=0;i<n;++i)
    for(int j=0;j<k;++j){
        thread_id[cnt++]={i,j};
        pthread_create(&p[i][j],NULL,&multplication,&arr[cnt]);
    }
    // join threads after create
	for(int i = 0 ;i < n; i++){
		for(int j= 0 ; j < k ; j++){
			pthread_join(p[i][j], NULL);
		}
	}
  //print final matrix after multplication
    for(int i=0;i<n;++i){
        for(int j=0;j<k;++j)
            cout<<mul[i][j]<<" ";
            puts("");
    }
    clock_t en=clock();
    cout<<"END1\t"<<(double)(en-st)/CLOCKS_PER_SEC<<"s\n";
    // case 2 every row has one thraed
    st=clock();
    pthread_t p2[100];
    cnt=0;

    //create thraed with for every row
    for(int i=0;i<n;++i)
    pthread_create(&p2[i],NULL,&multplication2,&arr[i]);

    //join thread
    for(int i =0 ; i < n ; i++)
    pthread_join(p2[i],NULL);
    //print final matrix after multplication
    for(int i=0;i<n;++i){
        for(int j=0;j<k;++j)
            cout<<mul2[i][j]<<" ";
            puts("");
    }
    en=clock();
    cout<<"END2\t"<<(double)(en-st)/CLOCKS_PER_SEC<<"s\n";
}
