#include <iostream>
#define N 10
using namespace std;

void adjust_down(int array[],int k,int max);
void build_heap(int array[],int max);
void swap(int &a,int &b);
int main()
{
    int array[N] = {1,2,3,4,5,6,7,8,9,10};
    build_heap(array,N);
    for(int i=0;i<N;i++) cout << array[i] << " ";
    cout << endl;
    for(int i = 0; i < N-1;i++){
        swap(array[0],array[N-1-i]);
        adjust_down(array,0,N-i-1);
    }
    for(int i=0;i<N;i++) cout << array[i] << " ";
    cout << endl;
    return 0;
}

void adjust_down(int data[],int k,int max)
{
    int item = data[k];
    for(int i = 2*k +1;i< max;i = i*2+1){
        if(i+1<max&&data[i]<data[i+1]) i++;
        if(item > data[i]) break;
        else{
            data[k] = data[i];
            k = i;
        }
    }
    data[k] = item;
}

void build_heap(int data[],int max){
    for(int i = max/2;i>=0;i--)
        adjust_down(data,i,max);
}
void swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
