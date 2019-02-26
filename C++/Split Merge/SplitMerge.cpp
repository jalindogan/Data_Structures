///Split Merge

/*
Jeremiah Alindogan
CISP 430
Mon/Wed 5:30 PM
02/04/2018
*/

///even number of first names

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

#define SIZE 20 //Size of storage for the characters of the names

ifstream in("input.txt");

///node structure
struct node
{
    char data[SIZE]; //stores strings of up to SIZE characters
    node *next;
};

int clean(){
      string comments;  //store the comments in this variable
       while (in.peek()=='\n' || in.peek()=='/' || in.peek()==' ' || in.peek()=='\t'){
           if (in.peek()=='/' )
              getline(in, comments);  //read the entire line because it is a comment
           else
              in.get();    //eat the newline, space and tab characters
      }
      return 1;
}

node* Readfile(node* olist) //reads input.txt for inputs
{
    node* curr = olist;
    node* p; //previous node
    while(clean() && in.good())
    {
        in >> curr->data;
        curr->next= new node; //sets *next to point at newly created node
        p=curr; //holds address of the current
        curr = curr->next; //current will now point to the next node
    }
    p->next = '\0'; //sets last input node's *next to null
    delete curr; //deletes the extra node
    return olist;
}

void Traverse(node* mylist) //traverse through nodes and displays their data
{
    node* curr = mylist;
    while(curr->next)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << curr->data;
}

node* Merge(node* list1, node* list2) //merges two lists
{
    node* head = list1;
    node* curr = head;
    while(curr->next)
        curr = curr->next;
    curr->next = list2;
    return list1;
}

void SplitMerge(node* mylist) //Splits list, displays split lists, merges lists, then displays merged list
{
    node* curr = mylist;
    node* mylist2 = mylist;
    int splitcount = 0;

    //splitting
    while(curr)
    {
        splitcount++;
        curr = curr->next;
    }
    curr = mylist;

    for(int i = 0; i < splitcount/2; i++)
    {
        curr = mylist2;
        mylist2 = mylist2->next;
    }
    curr->next = NULL;

    cout <<"~Splitted Lists~\nList 1: ";
    Traverse(mylist);
    cout  << endl << "List 2: ";
    Traverse(mylist2);

    cout << endl << endl;

    mylist = Merge(mylist, mylist2);

    cout << "Merged: ";
    Traverse(mylist);
}

int main()
{
    node* mylist = new node;
    mylist = Readfile(mylist);
    SplitMerge(mylist);
    delete mylist;
    return 0;
}

