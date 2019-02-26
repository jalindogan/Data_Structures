#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *next;
};

void traverse(struct node *head)
{
    while(head)
    {
        cout << head->data;
        head = head->next;
    }
}

void enqueue(int item, struct node *&front, struct node *&rear)
{
    struct node *newnode = new node;
    newnode->data = item;
    newnode->next = 0;

    if(!rear)
    {
        front = rear = newnode;
    }else
    {
        rear->next = newnode;
        rear = newnode;
    }

}

void dequeue(struct node *&front, struct node *&rear)
{
    struct node *temp;
    if(front)
    {
        temp = front;
        front = front->next;
        delete temp;
        if (!front)
            rear = '\0';
    }
}

int main()
{
    struct node *front, *rear;
    front = rear = 0;

    for(int i : {1, 2, 3, 4})
        enqueue(i, front, rear);

    cout << "List after enqueue: ";
    traverse(front);

    for(int i = 1; i < 3; i++)
        dequeue(front, rear);

    cout << "\nList after dequeuing 2 elements: ";
    traverse(front);

}
