#include<stdio.h>
#include<unordered_map>
using namespace std;
unordered_map<int,int> trace;

void buildHeap(int arr[],int i,int n){//This function is used to create the initial max heap for the given array of elements.
    int l=(i*2)+1;
    int r=(i*2)+2;
    int highest=i;
    if(l<n && arr[l]>arr[i]) highest=l;
    if(r<n && arr[highest]<arr[r]) highest=r;
    if(highest!=i){
        swap(arr[i],arr[highest]);
        buildHeap(arr,highest,n);
}
}
void heapify(int arr[],int cnt,int i,int n){//This function finds the path from root node to leaf node that the root may exist in.  
    int highest;
    int l=(i*2)+1;
    int r=(i*2)+2;
    if(l<n && r<n){//If left and right children are available to the parent then we simply pick the largest among them and store the index in a hash map.
        if(arr[l]>arr[r]){//This takes 1 comparison.
        highest=l;
        trace.insert({cnt,l});}          
        else{ highest=r;
        trace.insert({cnt,r});
        }
    }
    else if(l<n && r>=n){//If only left child is available we simply insert the left child's index into the hash map.This takes one comparison only.
        highest=l;
        trace.insert({cnt,highest});
    }
    cnt++;
    if(l>=n&&r>=n){//If the parent has no child we simply halt the operation.
        return;
    }
    if((highest<n)){
    heapify(arr,cnt,highest,n);//We continue to find the entire path by picking the greatest element node as the parent.This takes logn iterations in total.
}
}
int binarySearch(int arr[],unordered_map<int,int> trace,int l,int r,int root){//This function is used to find the position of the root in the path traced using binary search. 
       int mid=(l+r)/2;
       if(l>=r){
        if(trace.size()==1) return l;
        if(arr[trace.at(l)]>root) return l;
        else return l-1;
       }
       if(root>arr[trace.at(mid)]) r=mid-1;
       if(root<arr[trace.at(mid)]) l=mid+1;
       return binarySearch(arr,trace,l,r,root);

}
int heapifyDownward(int arr[],int i,int n){//heapifyDownward traces the path in the tree where the root might exist and swaps the root with the element that the root belongs at.
    swap(arr[0],arr[n-1-i]);//The last leaf node element and root element are swapped.
        int root=arr[0];
    heapify(arr,0,0,n-i-1);//The path in the tree for the root is traced.This takes logn iterations and at each iteration one data/key item comparison is performed.
        if(trace.size()==0){
            if(arr[0]>arr[1]) swap(arr[0],arr[1]);
            printf("\nThe sorted array is as follows: ");
    for(int i=0;i<n;i++){
            printf("%d ",arr[i]);
        }   
        return 1;
        }
        
        int ind=binarySearch(arr,trace,0,trace.size()-1,root);//a form of binary search is performed to find the root node's position.
        if(trace.size()>0){
        for(int i=0;i<=ind;i++){//We shift the elements on the path upto the root's position to their parents.
            int x;
            if((trace.at(i)%2)==0) x=(trace.at(i)-1)/2;
            else{
                x=(trace.at(i))/2;
            }
            int x1=trace.at(i);
            arr[x]=arr[x1];
        }
        }
        int temp=arr[trace.at(ind)];
        arr[trace.at(ind)]=root;//The root is placed at it's position.
        if(trace.size()<=1){arr[0]=temp;}
        trace.clear();
        return 0;
}

int main(){
    int n;
    printf("Please enter the number of elements in the array:");//Enter the number of elements.
    scanf("%d",&n);
    if(n==0) return 0;// If array size is 0 we have nothing to sort.
    int arr[n];
    printf("Enter the elements:");//Enter the elements.
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    for(int i=(n/2)-1;i>=0;i--){
        buildHeap(arr,i,n);//For each parent we perform a form of heapifyDownward with 2 comparisons to build the heap.
    }
    printf("The heap is as follows:");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    for(int i=0;i<n;i++){
        int x=heapifyDownward(arr,i,n);
        int root=arr[0];
        if(x==1) return 0;           
    }
     
    return 0;
}