//MIN HEAP

#include <iostream>
#include <fstream>
using namespace std;

#define SIZE 10

/*
Insert 10 values into a min-heap from a file.
Display the data, level by level.
Then delete 5 items.
After each delete, display the heap, level by level.
*/

ifstream in("input.txt");

///Heaps
//for min heaps, the parent is always smaller than the children
//for max heaps, the parent is always larger than the children

struct heap
{
    int arr[SIZE];
    int heapsize;
};

void printlevelheap(heap *&h)
{
    for (int i = 0, x = 1; i < h->heapsize; x*=2)
    {
        for(int j = 0; j < x && i < h->heapsize; j++)
            cout << h->arr[i++] << " ";
        cout << endl;
    }

}

void siftUp(heap *&h, int index)
{
    int parent = (index - 1)/2;
    if (h->arr[parent] > h->arr[index])
    {
        swap(h->arr[parent], h->arr[index]);
        siftUp(h, parent);
    }
}

void siftDown(heap *&h, int index)
{
    int leftchild = 2*index + 1;
    int rightchild = 2*index + 2;
    int temp = index;

    if(leftchild >= h->heapsize)
        return;
    if(h->arr[index] > h->arr[leftchild])
        temp = leftchild;
    if((rightchild < h->heapsize) && (h->arr[temp] > h->arr[rightchild]))
        temp = rightchild;
    if(temp != index)
    {
        swap(h->arr[index], h->arr[temp]);
        siftDown(h, temp);
    }
}

void heapinsert(heap *&h, int value)
{
    if(h->heapsize == 0)
    {
        h->arr[0] = value;
        h->heapsize++;
    }
    else
    {
        h->arr[h->heapsize] = value;
        siftUp(h, h->heapsize);
        h->heapsize++;
    }
}

void heapremove(heap *&h)
{
    if(h->heapsize)
    {
        swap(h->arr[0], h->arr[h->heapsize---1]);
        siftDown(h, 0);
        printlevelheap(h);
        cout << endl;
    }
}

int main()
{
    heap *h = new heap;
    h->heapsize = 0;
    int temp = 0;

    cout << "Inserting to heap:\n";
    while(in.good())
    {
        in >> temp;
        heapinsert(h, temp);
        printlevelheap(h);
        cout << endl;
    }

    cout << "Removing from heap:\n";
    for(int i = 0; i < 5 && h->heapsize; i++)
    {
        heapremove(h);
    }
}
