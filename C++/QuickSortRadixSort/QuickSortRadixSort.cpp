///Quick Sort & Radix Sort
/*
Jeremiah Alindogan
CISP 440
Iraj Sabzevary
03/15/2018
*/

/****************
Objective:
1. Modify quick sort algorithm
    -pivot is the last item
    -descending order
Note: Do not move the last element into the first element of
      element of the array. You must treat the algorithm as if
      the pivot is actually sitting in the last location of the array.

2. Add additional 5's to each number such that they have the same
   number of digits as the largest element.

3. Then sort using radix sort in descending order.

Note: Read the original data elements from a file.
      Number of elements must not exceed 10.
****************/
#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");

#define SIZE 10

struct node
{
    int data;
    node *next;
};

struct nodeQ
{
    node *front;
    node *rear;
};

void traverse(node  *mylist) //traverse through nodes and displays their data
{
    node* curr = mylist;
    while(curr)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

void enqueue(int item, struct node *&front, struct node*&rear)//inputs item into the rear
{
    struct node *newNode=new node;
    newNode->data=item;
    newNode->next=NULL;
    if (rear)
    {
        rear ->next=newNode;
        rear =newNode;
    }else
        front = rear =newNode;
}

int dequeue(struct node *& front, struct node *& rear) //takes off item from the front
{
    struct node *temp;
    int store;

    if(front)
    {
        temp= front;
        front = front->next;
        store = temp->data;
        delete temp;
        if (!front)
            rear=NULL;
        return store;
    }
}

int clean()
{
      string comments;  //store the comments in this variable
       while (in.peek()=='\n' || in.peek()=='/' || in.peek()==' ' || in.peek()=='\t'){
           if (in.peek()=='/' )
              getline(in, comments);  //read the entire line because it is a comment
           else
              in.get();    //eat the newline, space and tab characters
      }
      return 1;
}

int readFile(int arr[]) //reads file and creates array from data
{
    int i = 0;
    while(clean() && in.good())
    {
        in >> arr[i];
        i++;
    }
    return i;
}

void display(int origin[], int count) //Displays Array
{
    cout << "[ ";
    for(int i=0; i < count; i++)
    {
        cout << origin[i] << " ";
    }
    cout << "]";
}

int digitlength(int num)
{
    int length = 1;
    while(num /= 10)
        length++;
    return length;
}

int addfives(int arr[], int count)
{
    int digits = 0, maxdig = digitlength(arr[0]);
    for (int i = 0; i < count; i++)
    {
        digits = digitlength(arr[i]);
        while(digits < maxdig) //first element will be biggest
        {
            arr[i] = arr[i]*10 + 5; //adds a zero to the end, and replaces zero with 5
            digits++;
        }
    }
}

int partition(int a[], int first, int last)
{
	int pivot = last; //pivot starting at last
    int lower = first, upper = last - 1;

	while (lower <= upper) //not crossing
	{
	  while (a[lower] >= a[pivot] && lower <= upper) //compare pivot to lower
			lower++;
		if (lower > upper)
			break;
		swap(a[lower], a[pivot]);
		pivot = lower;
		lower++;

		while (a[upper] <= a[pivot] && upper >= lower)
			upper--;
		if (upper < lower)
			break;
		swap(a[upper], a[pivot]);
		pivot = upper;
		upper--;
	}
	return pivot;
}

void quickSort(int a[], int start, int end)
{
    int pIndex = 0;
    if(start >= end) //base
        return;

    pIndex = partition(a, start, end);
    quickSort(a, start, pIndex-1);
    quickSort(a, pIndex+1, end);
}

void radixsort(int origin[])
{
    nodeQ que[10]; //for places
    int MAX = 0, M = 10, N = 1;

    for(int i = 0; i < SIZE; i++) //find largest element for number of passes
    {
        if(MAX < origin[i])
            MAX = origin[i];
        //initialize queues
        que[i].front = que[i].rear = 0;
    }

    while(N <= MAX) //until every digit in every number has been evaluated
    {
        for(int i = 10, k = 0; i >= 0; i--) //0 through 9
        {
            for(int k = 0; k < SIZE; k++) //for array
            {
                if(i == (origin[k]%M)/N)
                    enqueue(origin[k], que[i].front, que[i].rear);
            }
        }

        //dequeue all queues and repopulate array
        for(int i = 10, k = 0; i >= 0; i--) //0 through 9
        {
            while(que[i].front)
            {
                origin[k] = dequeue(que[i].front, que[i].rear);
                k++;
            }
        }

        M *= 10;
        N *= 10;
    }
}

//need to create dynamically accounting for less elements than SIZE

int main()
{
    int original[SIZE] = {}; ///has zeros
    int count = readFile(original);
    cout << "Original Array: ";
    display(original, count); //sending count to only display how many items there are

    quickSort(original, 0, count);
    cout << "\n\nQuick Sort (descending): ";
    display(original, count);

    addfives(original, count);
    cout << "\n\nAdding Fives: ";
    display(original, count);

    radixsort(original);
    cout << "\n\nRadix Sort (descending): ";
    display(original, count);
    cout << endl;
    return 0;
}
