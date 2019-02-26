///Queues

/*
Jeremiah Alindogan
CISP 430
MW 5:30 PM
02/10/2018
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");

//structure
struct node{
    int item;
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

void traverse(node* mylist){ //traverse through nodes and displays their data
    node* curr = mylist;
    while(curr->next)
    {
        cout << curr->item << " ";
        curr = curr->next;
    }
    cout << curr->item;
}

void enqueue(int item, struct node *&front, struct node*&rear){ //inputs item into the rear
    struct node *newNode=new node;

    newNode->item=item;
    newNode->next=NULL;
    if (rear){
        rear ->next=newNode;
        rear =newNode;
    }else
        front = rear =newNode;
}

void dequeue(struct node *& front, struct node *& rear){ //takes off item from the front
    struct node *temp;

    if(front){
        temp= front;
        front = front->next;
        delete temp;
        if (!front)
            rear=NULL;
    }
}

void optimism(struct node*& front, struct node *& rear){ //removes all negatives
    struct node* temp = front;
    struct node* prev = front;
    while (temp){
        if(temp->item < 0){
            dequeue(temp, rear);
            prev->next = temp;
            prev = prev->next;
        }
        else{
            temp = temp->next;
        }
    }
}

int main(){
    struct node* front, *rear;
    front = rear = NULL;
    int item = 0;

    //Taking in inputs (positive integers)
    while(clean() && in.good()){
        in >> item;
        enqueue(item, front, rear);
    }

    cout << "Original output: \n ";
    traverse(front);
    cout << endl;

    optimism(front, rear);

    cout << "\n\nAfter removing negatives: \n";
    traverse(front);
}
