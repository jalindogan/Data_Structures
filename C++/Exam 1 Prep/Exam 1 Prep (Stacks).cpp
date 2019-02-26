#include <iostream>
using namespace std;

///Stacks

struct node
{
    int data;
    node *next;
};

void pop(struct node *&top)
{
    if(top)
    {
        struct node *temp = top;
        top = top->next;
        delete temp;
    }
}

void push(int item, struct node *&top)
{
    struct node *newnode = new node;

    newnode->data = item;
    newnode->next = top; //making sure old top is below stack
    top = newnode;
}

void traverse(struct node *head)
{
    while(head)
    {
        cout << head->data;
        head = head->next;
    }
}

int main()
{
    struct node *top;
    top = 0;

    cout << "After pushing elements (top to bottom): ";
    for(int i : {1, 2, 3, 4, 5})
        push(i, top);
    traverse(top);

    cout << "\n\nAfter popping 2 elements: ";
    for(int i : {1, 2})
    {
        pop(top);
    }
    traverse(top);
}
