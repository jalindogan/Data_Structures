///Circular Doubly Linked List
/*
Jeremiah Alindogan
CISP 430
MW 5:30 PM
02/21/2018
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");

//doubly linked list
struct node
{
     char name[20]; //limits names to a character size of 20
     node *next;
     node *prev;
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

void traversecircle(node* head) //traverse through circle
{
    struct node* temp = head;
    do
    {
        cout << temp->name << " ";
        temp = temp->next;
    }while(temp!=head); //displays elements until temp has done a full circle
}

int createcircle(node *&head, node *&tail) //returns count and creates circular list
{
    int count = 0;
    head = new node;
    tail = head;
    do
    {
        count++;
        in >> tail->name;
        tail->next = new node;
        tail->next->prev = tail;
        if(in.good()) //keeps adding until there are no more inputs
            tail = tail->next;
        else //if no more inputs, link head and tail to create circular list
        {
            tail->next = head;
            head->prev = tail;
        }
    }while(in.good() && clean());
    return count;
}

void deletecircle(int user, int count, node *&head, node *&tail) //deletes the right
{
    if(user == count)
    {
        for(int i = 0; i < user; i++) //deleting every node
        {
            node* curr = tail;
            tail = tail->prev;
            delete curr;
        }
        delete tail; //deleting pointers
        delete head;
    }else
    {
        for (int i = 0; i < user; i++) //deletes "counter-clockwise"
        {
            node *curr = tail;
            tail = tail->prev;
            delete curr;
        }
        tail->next = head; //relinking circular list
        head->prev = tail;
    }
}

int main()
{
    struct node *head, *tail;
    int count = 0, user = 0;
    head = tail = '\0';

    count = createcircle(head, tail);

    cout << "Current list of names: \n";
    traversecircle(head);

    cout << "\n\nHow many names would you like to delete out of the " << count << "? \n";
    cin >> user;
    while(user > count) //input error handling
    {
        cout << "\nPlease enter a less than or equal to the size of the list: ";
        cin >> user;
    }

    deletecircle(user, count, head, tail);

    if(user == count) //if list is empty
        cout << "\nList is now empty.";
    else //if list still has elements
    {
        cout << "\nNew list of names: \n";
        traversecircle(head);
    }
}
