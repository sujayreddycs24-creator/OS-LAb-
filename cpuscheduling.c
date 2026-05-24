#include<stdio.h>
#include<time.h>
int a[10000];
int b[10000];
void merge(int a[],int low,int mid,int high){
    int i= low;
    int j= mid+1;
    int k = low;
    while(i<=mid&&j<=high){
            if(a[i]<a[j]){
                b[k]=a[i];
                i++;
            }
            else{
                b[k]=a[i];
                j++;
            }
            k++;
        }
while(i<=mid){
     b[k]=a[i];
    j++;
    k++;
}
while(j<=high){
     b[k]=a[j];
    j++;
    k++;

}for (int x=low; x<=high;x++){
a[x]=b[x];
}
}
void mergesort(int a[],int low, int high){
if(low<high){
    int mid= (low+high)/2;
    mergesort(a,low,mid);
    mergesort(a,mid+1,high);
    merge(a,low,mid,high);
}
}
int main(){
int n;
clock_t start, end;
printf("enter the number of elements");
scan("%d",&n);
printf("enter the elements");
for (int z=0;z<n;z++)
{
    a[z]=rand()%10000;

}
printf("\n");
start = clock();
mergesort(a,0,n-1);
end = clock();
double time=((double)(end - start))*1000.0/ CLOCKS_PER_SEC;
printf("\nTime Taken: %f seconds\n", time);
for(int z =0;z<n;z++){
    printf("%d",a[z]);
}
return 0;
}
