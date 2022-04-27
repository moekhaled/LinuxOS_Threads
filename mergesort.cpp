#include <iostream>
#include<pthread.h>
#include<bits/stdc++.h>
using namespace std;
int arr[(int)1e5+7];
std::mutex mtx;

void merge(int low,int mid ,int high){
    int sizeleft=1+mid-low;
    int sizeright=high-mid;

    int *left = (int*)malloc(sizeleft*sizeof(int));
    int *right = (int*)malloc(sizeright*sizeof(int));

    for(int i=0;i<sizeleft;++i)
    left[i]=arr[i+low];
    for(int i=0;i<sizeright;++i)
    right[i]=arr[mid+1+i];
    int cnt=low,i=0,j=0;
    while(i<sizeleft&&j<sizeright)
        if(left[i]<right[j])arr[cnt++]=left[i++];
        else arr[cnt++]=right[j++];
    while(i<sizeleft)arr[cnt++]=left[i++];
    while(j<sizeright)arr[cnt++]=right[j++];
}
void* mergesort(void *arg){
    pair<int,int> lr = *(pair<int,int>*)arg;
    int mid=(lr.first+lr.second)>>1;
    pthread_t p1,p2;
    pair<int,int> pair1={lr.first,mid},pair2={mid+1,lr.second};
    if(lr.first<lr.second){
        pthread_create(&p1,NULL,&mergesort,&pair1);
        pthread_create(&p2,NULL,&mergesort,&pair2);
        pthread_join(p1,NULL);
        pthread_join(p2,NULL);
        merge(lr.first,mid,lr.second);
    }

}

int main()
{
    memset(arr,inf,sizeof(arr));
    freopen("mergesortinput.txt","r",stdin);
    freopen("mergesortoutput.txt","w",stdout);
    int n;
    //read array size
    cin>>n;
   //read array element
   for(int i=0;i<n;++i)cin>>arr[i];


    //start clock
    clock_t st=clock();
    pthread_t p1,p2;
    pair<int,int> pair1={0,n/2},pair2{n/2+1,n};
    pthread_create(&p1,NULL,&mergesort,&pair1);
    pthread_create(&p2,NULL,&mergesort,&pair2);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    merge(0,n/2,n);
    clock_t en=clock();
    for(int i=0;i<n;++i)cout<<arr[i]<<" ";
    cout<<"\nTime = "<<(double)(en-st)/CLOCKS_PER_SEC<<"S.\n";
}
