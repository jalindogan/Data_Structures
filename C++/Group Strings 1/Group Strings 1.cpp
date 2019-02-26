///Group Strings 1

/*
Jeremiah Alindogan
CISP 430
Mon/Wed 5:30 PM
01/24/2018
*/

#include <iostream>
#include <fstream>
using namespace std;

#define SIZE 25
ifstream in("input.txt"); //input.txt is the file that we read from
ofstream out("output.txt"); //output.txt is the file that we write into

void stringCopy(char *A, char *B);
bool stringCompare(char *A, char *B);
void stringConcatenation (char *A, char *B);
int stringPosition(char *A, char B);
int stringLength(char *A);
int clean();

int main()
{
    char string1[SIZE] = {'\0'},
         string2[SIZE] = {'\0'}; //stores strings //making sure arrays have no garbage
    char letter;
    // can use in.good() to check if for end of file
    if(clean() && in.good()){
        //1st line
        in >> string1 >> string2;
        stringCopy(string1, string2);
        out<< string1 <<"  "<< string2 << endl;

        //2nd line
        in >> string1 >> string2;
        if(stringCompare(string1, string2))
            out << "true" << endl;
        else
            out << "false" << endl;

        //3rd line
        in >> string1 >> string2;
        stringConcatenation(string1, string2);
        out << string1 <<"  "<< string2 << endl;

        //4th line
        in >> string1 >> letter;
        out << stringPosition(string1, letter) << endl;

        //5th line
        in >> string1;
        stringLength(string1);
        out << string1 << endl;
    }

    in.close();
    out.close();
}

void stringCopy(char *A, char *B)///copies second parameter into first
{
    for (int i = 0;; i++)
    {
        A[i] = B[i];
        if (B[i] == '\0')
            break;
    }
}

bool stringCompare(char*A, char *B) ///compares for equality
{
    int i = 0;
    while(A[i] == B[i++])
    {
        if(A[i] != B[i])
            return false;
        if(A[i] == '\0' || B[i] == '\0')
            break;
    }
    return true;
}

void stringConcatenation(char *A, char *B) ///Concatenates the second array to the first
{
    /*for(int i = stringLength(A), j = 0; i < (stringLength(A) + stringLength(B)); i++, j++)
    {
        A[i] = B[j];
    }*/

    for (int i = 0, j = 0;; i++)
    {
        if (A[i] == '\0')
        {
            A[i] = B[j++];
            if (B[j] == '\0')
                break;
        }
    }
}

int stringPosition(char *A, char B) ///searches first parameter for the second parameter
{
    int i = 0; //index
    while(A[i] != '\0')
    {
        if (A[i] == B)
            return i;
        i++;
    }
    return -1;
}

int stringLength(char *A) ///returns the length of the array
{
    char temp[SIZE] = {'\0'}; //empty
    int len = 0;
    for (int i = 0; A[i] != '\0'; i++)
    {
        temp [i+1] = A[i];
        len++;
        temp[0] = len + '0';
    }
    stringCopy(A, temp);
    return len;
}

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
