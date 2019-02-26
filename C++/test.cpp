#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int NUM_ELEM = 11, HASH_NUM = 11, NULL_ELEM = 0, QUAD_PROBE_STEPS = 3;

ifstream in("input.txt");


void hashdul(int *arr, int val, int hash)
{
  int hashIndex = val % hash, numCollisions = 0, probeIndex = 1;
  bool indexAvailable = false;
  if (arr[hashIndex] == NULL_ELEM)
    arr[hashIndex] = val;
  else
  {
    numCollisions++;
    hashIndex = hashIndex - (val % hashIndex);
    if (arr[hashIndex] == NULL_ELEM)
      arr[hashIndex] = val;
    else
    {
      numCollisions++;

      // quadratic probe
      while (probeIndex < QUAD_PROBE_STEPS && !indexAvailable)
      {
        hashIndex = (hashIndex + (int)pow(probeIndex, 2)) % hash;
        if(arr[hashIndex] == NULL_ELEM)
        {
          arr[hashIndex] = val;
          indexAvailable = true;
        }
        else
        {
          numCollisions++;
          probeIndex++;
        }
      }

      // linear probe
      probeIndex = 0;
      while(probeIndex < NUM_ELEM && !indexAvailable)
      {
        hashIndex = (hashIndex + 1) % hash;
        if(arr[hashIndex] == NULL_ELEM)
        {
          arr[hashIndex] = val;
          indexAvailable = true;
        }
        else
        {
          numCollisions++;
          probeIndex++;
        }
      }
    }
  }

  if (numCollisions >= NUM_ELEM)
    cout << "\nError for val " << val << ": Not enough room to insert element.\n";
  else
    cout << '\n' << val << " inserted at index " << hashIndex << ". Number of collisions: " << numCollisions << '\n';
}

void hashSearch(int *arr, int val, int hash)
{
  int hashIndex = val % hash, numCollisions = 0, probeIndex = 1;
  bool indexAvailable = false, foundIndex = false;
  if (arr[hashIndex] == val)
      foundIndex = true;
  else
  {
    hashIndex = hashIndex - (val % hashIndex);
    if (arr[hashIndex] == val)
      foundIndex = true;
    else
    {
      // quadratic probe
      while (probeIndex < QUAD_PROBE_STEPS && !foundIndex)
      {
        hashIndex = (hashIndex + (int)pow(probeIndex, 2)) % hash;
        if(arr[hashIndex] == val)
          foundIndex = true;
        else
          probeIndex++;
      }

      // linear probe
      probeIndex = 0;
      while(probeIndex < NUM_ELEM && !foundIndex)
      {
        hashIndex = (hashIndex + 1) % hash;
        if (hashIndex >= NUM_ELEM)
          hashIndex -= NUM_ELEM;
        if(arr[hashIndex] == val)
          foundIndex = true;
        else
          probeIndex++;
      }
    }
  }
  if (foundIndex)
    cout << '\n' <<val << " found at index " << hashIndex << "\n";
  else
    cout << '\n' << val << " not in list " << '\n';
}


int main()
{
  int arr[NUM_ELEM], buffer;

  for (int i = 0; i < NUM_ELEM; i++)
    arr[i] = NULL_ELEM;

  in >> buffer;
  while(in.good() && !in.eof())
  {
    hashdul(arr, buffer, HASH_NUM);
    in >> buffer;
  }
  cout << "\nEnter a value to search for: ";
  cin >> buffer;
  hashSearch(arr, buffer, HASH_NUM);
}

