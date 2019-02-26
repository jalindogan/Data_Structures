///Merge Sort with Linked Lists
/*
Jeremiah Alindogan
CISP 430 MW 5:30 - 6:50 PM
Iraj Sabzevary
03/12/2018
*/

///objective: make a mergesort function for linked lists from a predefined array

#include <iostream>
#include <cstdlib>
using namespace std;

#define SIZE 12

struct node
{
    int item;
    node *next;
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

void addToEnd (struct node*&head, int item) //adds to end of doubly
{
    //create node
    node *curr = head;
    node *newnode = new node;
    newnode->item = item;
    newnode->next = 0;

    if(!head)
        head = newnode;
    else
    {
        while(curr->next != '\0')
            curr = curr->next;
        curr->next = newnode;
        curr = curr->next;
        curr->next = 0;
    }
}

///to create random arrays instead of user created array
void createarray(int origin[]) //Fills array with random numbers
{
    for (int i = 0; i < SIZE; i++)
        origin[i] = rand()%100; //hundreds
}

void arrtolist(int arr[], struct node *&mylist)
{
    for(int i = 0; i < SIZE; i++)
        addToEnd(mylist, arr[i]);
}

void display(int origin[]) //Displays Array
{
    cout << "[";
    for(int i=0; i<SIZE; i++)
        cout << origin[i]  << "  ";
	cout << "]\n";
}

int countlist(node *curr)
{
    int count = 0;
    while(curr)
    {
        curr = curr->next;
        count++;
    }
    return count;
}


void split(node *head, node*&a, node*&b) //splits a list into two separate lists
{
    int count = countlist(head);
    for(int i = 0; i < count/2; i++)
    {
        addToEnd(a, head->item);
        head = head->next;
    }

    /*once it reaches halfway, starts adding to b*/
    while(head)//the rest of list : |b| > |a|
    {
        addToEnd(b, head->item);
        head = head->next;
    }
}

node* merge(node* a, node* b) //compares elements of two lists and returns a merged list
{
    struct node* c = 0; //stores merged list

///Recursively
    /*
    //Base cases
    if (!a)
        return(b);
    else if (!b)
        return(a);

    if (a->item <= b->item) //checks first element
    {
        c= a; //points to first element
        c->next = merge(a->next, b); //goes to next a element
    }else
    {
        c = b; //points to first element
        c->next = merge(a, b->next); //goes to next b element
    }*/

///Non recursively
    while(a && b) //comparison
    {
        if(a->item <= b->item)
        {
            addToEnd(c, a->item);
            a = a->next;
        }else
        {
            addToEnd(c, b->item);
            b = b->next;
        }
    }

    while(a) //adds the rest of a
    {
        addToEnd(c, a->item);
        a = a->next;
    }
    while(b) //adds the rest of b
    {
        addToEnd(c, b->item);
        b = b->next;
    }

    return(c);
}

node* mergeSort( node* head)
{
    node *a, *b, *c;
    a = b = 0;

    //base cases
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
    int arr[SIZE] = {};
    char user = 0;
    node *mylist = 0; //a, c, and b are for testing

    while(!user)
    {
        cout << "Would you to create your own array? (Y/N)?";
        cin >> user;
        if (user == 'Y' || user == 'y')
        {
            //takes custom array of size SIZE
            cout << "Enter an array of size " << SIZE << endl;
            for (int i = 0; i < SIZE; i++)
            {
                cout << "[" << i << "]: ";
                cin >> arr[i];
            }
        }else
        {
            //creates array
            createarray(arr);
            cout << "Random Array: ";
            display(arr);
        }
    }
    //convert array to linked list
    arrtolist(arr, mylist);
    cout << "\nOriginal List(converted from array to list): ";
    traverse(mylist);

    //merge sort
    mylist = mergeSort(mylist);
    cout <<"\nMergeSorted List: ";
    traverse(mylist);
}
