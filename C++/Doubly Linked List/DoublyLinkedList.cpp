///Doubly Linked List

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
ofstream out("output.txt");

//doubly linked list
struct node
{
     int num;
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

void traverse(node* mylist) //traverse through nodes and displays their data
{
    struct node* curr = mylist;
    while(curr)
    {
        cout << curr->num << " ";
        curr = curr->next;
    }
}

node* createdoubly(node *&head, node *&tail)
{
    head = tail = new node;
    tail->prev = tail->next= 0;


    while(in.good() && clean())
    {

        in >> tail->num;
        if(in.good())
        {
            tail->next = new node;
            tail->next->prev = tail;
            tail = tail->next;
        }else
            tail->next = 0;
    }
}

void removechoice(int user, node *&start, node *& ending)
{
    struct node *curr = start;
    if(curr->prev == 0){ //if head
        for(int i = 1; i < user; i++)
        {
            curr = curr->next;
        }
        if(curr->prev && curr->next) //if deleting in middle
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }else if (!curr->prev) //if deleting head
        {
            start->next->prev = 0;
            start = start->next;
        }
        else if (!curr->next) //if deleting tail
        {
            ending->prev->next = 0;
            ending = ending->prev;
        }
        delete curr;
    }else if(curr->next == 0) //if tail
    {
        for(int i = 1; i < user; i++)
        {
            curr = curr->prev;
        }
        if(curr->prev && curr->next) //if deleting in middle
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }else if (!curr->prev) //if deleting head
        {
            ending->next->prev = 0;
            ending = ending->next; //changes head
        }
        else if (!curr->next) //if deleting tail
        {
            start->prev->next = 0;
            start = start->prev;
        }
        delete curr;
    }
}

int main()
{
    struct node *head = 0, *tail = 0;
    int user = 0;

    createdoubly(head, tail);
    cout << "Input.txt: \n";
    traverse(head);

    cout << "\n\nWhich item do you want to delete from the beginning?\n";
    cin >> user;

    removechoice(user, head, tail);
    traverse(head);

    cout << "\nWhich item do you want to delete from the end?\n";
    cin >> user;

    removechoice(user, tail, head);
    traverse(head);

    while(head)
    {
        out << head->num << " ";
        head = head->next;
    }
}
