
///Merge Sort (top)
/*
Jeremiah Alindogan
CISP 430 MW 5:30-6:50PM
Sabzevary
03/07/2018
*/

/*
MergeSort(arr[], l,  r)
If r > l
     1. Find the middle point to divide the array into two halves:
             middle m = (l+r)/2
     2. Call mergeSort for first half:
             Call mergeSort(arr, l, m)
     3. Call mergeSort for second half:
             Call mergeSort(arr, m+1, r)
     4. Merge the two halves sorted in step 2 and 3:
             Call merge(arr, l, m, r)
*/

#include <iostream>
#include <cstdlib> //for creating random elements
using namespace std;

#define SIZE 8 //size of list

struct node
{
    int item;
    node *next;
    node *prev;
};

void traverse(node  *mylist) //traverse through nodes and displays their data
{
    node* curr = mylist;
    while(curr)
    {
        cout << curr->item << " ";
        curr = curr->next;
    }
    cout << endl;
}

//Pops node off stack
int pop(struct node *&top){ //returns popped item
    struct node *temp;
    int store = 0;
    if(top){
        temp=top;
        store = temp->item;
        top=top->next;
        delete temp;
    }
    return store;
}

//Pushes node onto stack
void push(int item, struct node *&top){
    struct node *newNode=new node;

    newNode->item = item;
    newNode->next = top;
    top = newNode;
}

void fill_list(node *&top)
{
    for(int i = 0; i < SIZE; i++) //adds SIZE amount of elements to list
    {
        push(rand()%10, top); //pushes tens
    }
}


void split (node* head, node*&a, node*&b) ///done
{
    int count = 0; ///created count so function is not dependent
                   ///on program (program already knows size of list)
    node *curr = head;

    if(!head || !head->next)
        return;

    //traverse through list to get count
    while(curr)
    {
        curr = curr->next;
        count++;
    }
    for(int i = 0; i < count/2; i++)
        push(pop(head), b); //will fill b with last contents of list
    for(int i = 0; i < count/2; i++)
        push(pop(head), a); //will fill a with content from other half
}

node* merge(node* a, node* b)
{
    node* c = 0;
    return(c);
}

node* mergeSort( node* head)
{
    node *a, *b, *c;
    a = b = 0;
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;
    split(head, a, b);
    a = mergeSort(a);
    b = mergeSort(b);
    c = merge(a,b);
    return(c);
}

int main()
{
    node* mylist = 0, *a = 0, *b = 0;
    fill_list(mylist);
    cout << "Original List: ";
    traverse(mylist);
    mylist = mergeSort(mylist);
    cout << "\nNew List: ";
    traverse(mylist);
}
