///Group 8 (Bubble Sort, Selection Sort, Shell Sort, Insertion Sort, and Binary Search)
/*
Jeremiah Alindogan
CISP 430 MW 5:30 - 6:50 PM
Sabzevary
03/04/2018
*/

#include <iostream>
#include <cstdlib> //for rand()
using namespace std;

/**
Your program will sort a two dimensional array (5 * 4) based on the following:
a)	The entire array should be sorted using bubble sort based on
    the 1st column in ascending order and display the entire array.
b)	Reset the array to its original contents.
    The entire array should again be sorted using selection
    sort based on the 2nd column in descending order and display the entire array.
c)	Reset the array to its original contents.
    The entire array should again be sorted using shell sort
    based on the 3rd column in ascending order and display the entire array
d)	Reset the array to its original contents.
    The entire array should again be sorted using
    insertion sort based on the 5th row in ascending order and display the entire array

Ask the user for a number, search for that number in the 5th row of the array that was
sorted via insertion sort, using binary search. Display the entire column.Your array
could be declared as a global variable since it is being used everywhere.

*/

#define ROW 5
#define COL 4

void createoriginal(int origin[][COL]) //Fills 2D with random numbers
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            origin[i][j] = rand()%10;
    }
}

void display(int origin[][COL]) //Displays 2D Array
{
    for(int i=0; i<ROW; i++)
	{
		for(int j=0; j<COL; j++)
			cout << origin[i][j]  << "  ";
		cout << endl;
	}
	cout << endl;
}

///Sorting Algorithms

//bubble sort for columns in ascending order
void bubble(int arr[][COL], int limit, int column)
{
    int temp, index;
    //Determines the amount of passes
    for (;limit > 0;limit--)
    {
    	for (index=0; index<limit; index++)
        {
            if (arr[index][column] > arr[index+1][column]) //Based off decided column
            {
                //Swapping
                for(int i = 0; i < COL; i++)//swaps whole rows
                {
                    temp=arr[index][i];
                    arr[index][i]=arr[index+1][i];
                    arr[index+1][i]=temp;
                }
            }
        }
    }
}

//selection sort in descending order for column
void selection(int arr[][COL], int limit, int column)
{
    int temp, index_of_largest,index;
	//This loop is used to determine the number of passes
 	for(;limit > 0;limit--)
    {
        index_of_largest=0 ;
        for (index=1; index<=limit; index++)
        {
			if (arr[index][column] < arr[index_of_largest][column]) //descending order
      			index_of_largest=index; //Store the index array element
      	}
        //Swap
        if (limit !=index_of_largest){
            for(int i = 0; i < COL; i++)
            {
                temp=arr[limit][i];
                arr[limit][i]=arr[index_of_largest][i];
                arr[index_of_largest][i]=temp;
            }
        }
   	}
}

//Shell sort in ascending order for column
void shell(int arr[][COL], int limit, int column)
{
	int temp;
	for (int gap=limit/2; gap>=1; gap=gap/2)
    {
        for(int i=gap; i<=limit; i++)
			{
			    for (int j = i; j>=gap && arr[j-gap][column]>arr[j][column]; j=j-gap)
                {
                    for(int k = 0; k < COL; k++)
                    {
                        temp=arr[j-gap][k];
                        arr[j-gap][k]=arr[j][k];
                        arr[j][k]=temp;
                    }
                }
			}
    }
}

//insertion sort in ascending order for row
void insertion(int arr[][COL], int row)
{
	int temp;

	for (int i = 1; i < ROW; i++)
	{
		for (int j=i; j>0 && arr[row][j] < arr[row][j-1]; j--)
        {
			for(int k=0; k < ROW; k++)
            {
                temp = arr[k][j];
                arr[k][j] = arr[k][j - 1];
                arr[k][j - 1] = temp;
            }
		}
	}
}

///Binary Search for row *ARRAY MUST ALREADY BE SORTED
void binary_search(int arr[][COL], int target, int row)
{
    int high = ROW-1, low = 0, mid;
    int found=false;

    while (high >= low && !found)
    {
        // calculate the midpoint for roughly equal partition
        mid = (high + low ) / 2;

        if (target > arr[row][mid] )
            low = mid + 1;
        else if (target < arr[row][mid])
            high = mid - 1;
        else
            found = true;
    }

    if(found) //display found column
    {
        cout << "Found Column: \n";
        for(int i = 0; i < ROW; i++)
            cout << arr[i][mid] << endl;
    }
    else //if not found
    {
        cout << "Not found in 5th row";
    }
}


int main()
{
    int origin[ROW][COL] = {};
    int temp[ROW][COL] = {};
    int target = 0;
    createoriginal(origin);

/// a) Bubble sort ~ First column
    cout << "~Part A~\nOriginal Array\n";
    display(origin);
    copy(origin, origin+ROW, temp); //copies arrays
    bubble(temp, COL, 0); //first column
    cout << "Sorted by bubble based off 1st column in ascending order:\n";
    display(temp);

/// b) Selection sort ~ 2nd column
    cout << "\n~Part B~\nReset to Original Array\n";
    display(origin);
    copy(origin, origin+ROW, temp);
    selection(temp, COL, 1); //second column
    cout << "Sorted by selection based off 2nd column in descending order:\n";
    display(temp);

/// c) Shell sort ~ 3rd column
    cout << "\n~Part C~\nReset to Original Array\n";
    display(origin);
    copy(origin, origin+ROW, temp);
    shell(temp, COL, 2);
    cout << "Sorted by shell based off 3rd column in ascending order: \n";
    display(temp);

/// d) Insertion sort ~ 5th row
    cout << "\n~Part D~\nReset to Original Array\n";
    display(origin);
    copy(origin, origin+ROW, temp);
    insertion(temp, 4);
    cout << "Sorted by insertion based off 5th row in ascending order: \n";
    display(temp);

/// e) Don't reset; Binary Search ~ 5th Row; Display column
    cout << "\n~Part E~\nPrior Array\n";
    display(temp);
    cout << "Search for number in 5th row. Enter number: ";
    cin >> target;
    binary_search(temp, target, 4);
}
