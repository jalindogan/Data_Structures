#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
    node *prev;
};

void addToEnd (struct node*&head, int data)
{
    //create node
    node *curr = head;
    //if head == NULL
    if(!head)
    {
        head = new node;
        head->next = head->prev = head;
        head->data = data;
    }
    //else
    else
    {
        if(curr->next == head)
            curr->next = new node;
        else
        {
            while(curr->next != head)
                curr = curr->next; //1, 2, 3
            curr->next = new node;
        }
        curr->next->prev = curr;
        curr = curr->next;
        curr->data = data;
        curr->next = head;
        head->prev = curr;
    }
}

void deleteFromEnd(struct node *&head)
{
    node *curr = head->prev;
    curr->prev->next = head;
    head->prev = curr->prev;
    delete curr;
}

int main()
{
    node *head = NULL;
    addToEnd(head, 1);
    addToEnd(head, 2);
    addToEnd(head, 3);

    node *curr = head;
    while(curr->next != head)
    {
        cout << curr->data; //1, 2, 3
        curr = curr->next;
    }
    cout << curr->data;

      //Deleting
    deleteFromEnd(head);
    deleteFromEnd(head);

    curr = head;
    //Traverse
    cout << endl;
    while(curr->next != head)
    {
        cout << curr->data; //1, 2, 3
        curr = curr->next;
    }
    cout << curr->data;

}
