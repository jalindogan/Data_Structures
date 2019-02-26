//HASH
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define SIZE 11 //prime hash number
#define QSTEPS 3

ifstream in("input.txt");

void displayarray(int *arr)
{
    for(int i = 1; i < SIZE; i++)
        cout << arr[i] << " ";
}

int modulodivision(int value)
{
    return(value%SIZE);
}

int doublehashing(int value, int index)
{
    return(index - value%SIZE);
}

void hashing(int *arr, bool *col, int temp)
{
    int index = modulodivision(temp);
    int collision = 0, probeindex = 1;
    bool probe = false;
    if(!col[index]) //checks if index is occupied
    {
        arr[index] = temp; //adds value to index element
        col[index] = true; //indexed element is now occupied
    }
    else
    {
        collision++; //collision hit once;
        index = doublehashing(temp, index); //double hash part
        if(!col[index]) //checks new index
        {
            arr[index] = temp;
            col[index] = true;
        }
        else
        {
            //quadratic probe
            while(probeindex < QSTEPS && !probe)
            {
                index = (index + (int)pow(probeindex, 2)) % SIZE;
                if(!col[index])
                {
                    arr[index] = temp;
                    col[index] = true;
                    probe = true;
                }
                else
                {
                    collision++; //additional collision
                    probeindex++;
                }
            }

            // linear probe
            probeindex = 0;
            while(probeindex < SIZE && !probe)
            {
                index = (index + 1) % SIZE;
                if(!col[index])
                {
                    arr[index] = temp;
                    col[index] = true;
                    probe = true;
                }
                else
                {
                  collision++;
                  probeindex++;
                }
            }
        }
    }

    if(collision > SIZE) //if collides with every spot except one
        cout << "\nError: Array full -- value: " << temp << " with " << collision << " collisions.\n" << endl;
    else
        cout << "Value (" << temp << ") inserted at index " << index << " with " << collision << " collisions.\n";
}

void hashsearch(int *arr, int key)
{
    int index = modulodivision(key);
    int probeindex = 1;
    bool found = false;

    if(arr[index] == key) //is element equal to key?
        found = true;
    else
    {
        index = doublehashing(key, index); //double hash
        if(arr[index] == key)
            found = true;
        else
        {
            //quadratic probe
            while(probeindex < QSTEPS)
            {
                index = (index + (int)pow(probeindex, 2)) % SIZE;
                if(arr[index] == key)
                {
                    found = true;
                    break;
                }
                else
                    probeindex++;
            }

            // linear probe
            probeindex = 0;
            while(probeindex < SIZE)
            {
                index = (index + 1) % SIZE;
                if(arr[index] == key)
                {
                    found = true;
                    break;
                }
                else
                  probeindex++;
            }
        }
    }

    if(found)
        cout << "\nElement (" << key << ") found at index " << index << endl;
    else
        cout << "\nValue not found in array.";
}

int main()
{
    int arr[SIZE] = {};
    bool col[SIZE] = {};
    int temp = 0, index = 0;

    while(in.good())
    {
        temp = 0;
        in >> temp;
        cout << "\n...Inserting " << temp;
        cin.get();
        hashing(arr, col, temp);
    }
    cout << "\nWhole array: ";
    displayarray(arr);

    //hash search
    cout << "\nSearch for element: ";
    cin >> temp;
    hashsearch(arr, temp);

}
