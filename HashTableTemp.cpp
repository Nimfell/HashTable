#include <stdio.h>

class HashTable
{
public:
  int size;
  int step;
  char** slots;

  HashTable(int sz, int stp)
  {
    size = sz;
    step = stp;
    slots = new char*[size];
    for (int i = 0; i<size; i++) slots[i] = NULL;
  }

  int hashFun(char* value)
  {
    //int len = value.Length();
    int index = 0;
    index = (int)value[0];
    for (int i = 1; value[i] != 0; i++)          // adder of sumbols
    {
      index += (int)value[i];
    }
    if (index < 0) index *= -1;          // number modulus
    while (index >= size)                // if larger that the size
    {
      index /= 3;
    }
    return index;

  }

  int seekSlot(char* value)
  {
    int index = hashFun(value);
    for (int i = 0; i < 3; i++)
    {
      while (index <= size - 1)
      {
        if (slots[index] == NULL)
        {
          //slots[index] = value;
          return index;
        }
        index += step;
      }
      index = index - size;
    }
    for (int i = 0; i <= size; i++)
    {
      if (slots[i] == NULL)
      {
       // slots[i] = value;
        return i;
      }
    }
    return -1;
  }

  int put(char* value)
  {
    int index = seekSlot(value);
    slots[index] = value;
    return index;
  }

  int find(char* value)
  {
    for (int index = 0; index < size; index++)
    {

      if (slots[index] == value) return index;
    }
    return -1;   
  }
};
/*
//====================== TEST ========================

int test_hash(HashTable* Table)
{
  //HashTable* Table = new HashTable(17, 3);
  char* value = "It’s better to light a candle than curse the darkness";
  char* val_2 = "You can’t make bricks without straw";
  int step = Table->step;
  int test = 0;

  // FIND
  if (Table->find(NULL) != 0) test++;     // checking the filling of the empty table
                                          // if (Table->find(0) != -1) test++;       // this value is not in the table - don't work

                                          // PUT
  int index = Table->hashFun(value);        // index = 6
  for (int i = 0; i < Table->size - 1; i++) // fill the entire array except for one cell
  {
    index = (index <= Table->size - 1) ? index : index - Table->size;
    if (Table->put(value) != index) test++;
    index += step;
  }
  // the last empty data cell
  index = (index <= Table->size - 1) ? index : index - Table->size;
  if (Table->put(val_2) != index) test++;
  if (Table->find(val_2) != index) test++;
  if (Table->put(val_2) != -1) test++;    //the table is full

  return test;
}
*/
