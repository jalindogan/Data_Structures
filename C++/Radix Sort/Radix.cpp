///Group 8.5 (Radix Sort)

/*
Jeremiah Alindogan
CISP 430 MW 5:30 - 6:50 PM
Sabzevary
03/04/2018
*/

/******************************************************************
Come up with an unsorted array of numbers (integer array).
Sort the numbers in ascending order and descending order and display
them using radix sort.

First sort in ascending, then reset the array to its original order
and finally sort the array again in descending order

******************************************************************/

#include <iostream>
#include <cstdlib> //for rand()
using namespace std;

#define SIZE 10

//determines whether to sort in ascending or descending
enum type_sort {ASCEND, DESCEND};

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

void createoriginal(int origin[]) //Fills array with random numbers
{
    for (int i = 0; i < SIZE; i++)
    {
        origin[i] = rand()%1000; //hundredss
    }
}

void display(int origin[]) //Displays Array
{
    cout << "[";
    for(int i=0; i<SIZE; i++)
	{
        cout << origin[i]  << "  ";
	}
	cout << "]\n";
}

void radixsort(int origin[], type_sort type)
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

    if(type == ASCEND)
    {
        while(N <= MAX) //until every digit in every number has been evaluated
        {
            for(int i = 0, k = 0; i < 10; i++) //0 through 9
            {
                for(int k = 0; k < SIZE; k++) //for array
                {
                    if(i == (origin[k]%M)/N)
                        enqueue(origin[k], que[i].front, que[i].rear);
                }
            }

            //dequeue all queues and repopulate array
            for(int i = 0, k = 0; i < 10; i++) //0 through 9
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
    }else if (type == DESCEND)
    {
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
}

int main()
{
    int origin[SIZE] = {}, temp[SIZE] = {}; //initializing arrays
    createoriginal(origin); //creating numbers
    copy(origin, origin+SIZE, temp); //copies array to a temporary one

    //Ascending sort
    cout << "Array: ";
    display(temp);
    radixsort(temp, ASCEND);
    cout << "\nSorted Array (ascending): ";
    display(temp);

    //Descending sort
    copy(origin, origin+SIZE, temp);
    cout << "\nReset array: ";
    display(temp);
    radixsort(temp, DESCEND);
    cout << "\nSorted Array (descending): ";
    display(temp);
}
