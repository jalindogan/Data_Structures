///Infix Notation to Postfix Notation
///only operators allowed: ( ) + - * /

/*
Jeremiah Alindogan
CISP 430
MW 5:30PM
02/13/2018
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream in("input.txt");

struct node{
    char item;
    node *next;
};

void traverse(node* mylist){ //traverse through nodes and displays their data
    node* curr = mylist;
    while(curr->next)
    {
        cout << curr->item;
        curr = curr->next;
    }
    cout << curr->item;
}


///for stack ~ for the operands
void pop(struct node *&top){
    struct node *temp;

    if(top){
        temp=top;
        top=top->next;
        delete temp;
    }
}

void push(int item, struct node *&top){
    struct node *newNode=new node;

    newNode->item=item;
    newNode->next=top;
    top=newNode;
}


///for queue
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

int main(){
    struct node *front, *rear; //queue ~ for postfix notation
    struct node *top = 0; //stack ~ for operands
    char item = '\0'; //stores items
    front = rear = NULL;

    cout << "Infix Notation: \n";

    //Precedence part
    while((in >> item) && in.good()){
        cout << item; //Displays infix notation
        if(isalpha(item) || isdigit(item)){ //accepts both digits and letters
            enqueue(item, front, rear);
        }else if((item == '*') || (item == '/') || (item == '+') || (item == '-') || (item == '(') || (item == ')')){ //checks for permitted operators
            if (!top)
                push(item, top);
            else if(((item == '+') || (item == '-')) && ((top->item == '*') || (top-> item == '/'))){ //since * and / have higher precedence
                while((top) && ((top->item == '*') || (top->item == '/'))){ //any higher precedence
                    enqueue(top->item, front, rear);
                    pop(top);
                }
                push(item, top);
            }else if (item == ')'){
                while(top->item != '('){ //displays everything until it finds ( in stack
                    enqueue(top->item, front, rear);
                    pop(top);
                }
                pop(top); //pops ( from stack
            }else{
                push(item, top);
            }
        }
    }

    cout << "\n\nPostfix Notation:\n";

    //Display everything in stack
    while(top){
        enqueue(top->item, front, rear);
        pop(top);
    }

    traverse(front); //Display Postfix Notation

    cout << endl;
}
