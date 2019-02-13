
#include <stdio.h>
#include <cstdlib>
//#include <string.h> 

int hashFun_1(int value, int size)
{   
	if (value == NULL)
		return -1;

	int p = 37; // prime number
	int a = 30; // 1 ... ð-1
	int b = 2;  // 0 ... ð-1

	int index = ( (a*value + b) % p ) % size;

	return index;
}

int hashFun_2(int value, int size)
{    
	if (value == NULL)
		return -1;
	int p = 17; // prime number
	int a = 9;  // 1 ... ð-1
	int b = 5;  // 0 ... ð-1
	int index = ( (a*value + b) % p ) % size;
	return index;
}

int hashFun_3(int value, int size)
{    
	if (value == NULL) return -1;
	int p = 37; // prime number
	int a = 18; // 1 ... ð-1
	int b = 9;  // 0 ... ð-1
	int index = ( (a*value + b) % p ) % size;
	return index;
}

typedef int (*HashFunction)(int value, int size);


HashFunction _hashFun_1 = & hashFun_1 ;
HashFunction _hashFun_2 = & hashFun_2 ;
HashFunction _hashFun_3 = & hashFun_3 ;


HashFunction hash_func_arr[3] = 
{
	_hashFun_1, 
	_hashFun_2,
	_hashFun_3  
};

class HashTable
{
public:
  int size;
  int step;
  int* slots;  
  HashFunction _hashFun;
  int number_of_collisions;

  HashTable(int sz, int stp)
  {
    size = sz;
    step = stp;
	number_of_collisions = 0;
    slots = new int[size];
    for (int i = 0; i < size; i++) slots[i] = NULL;

	_hashFun = hash_func_arr[ rand() % 3 ]; // arg = 0 by 2	
  }

  ~ HashTable()
  { delete [] slots;}
  
  int hashFun(int value)
  { 
	int index = _hashFun(value, size);
	return index;
  }

  int seekSlot(int value)
  {
    int index = hashFun(value);

    for (int i = 0; i < 3; i++)
    {
      while (index <= size - 1)
      {
        if (slots[index] == NULL)
        {          
          return index;
        }
		number_of_collisions++;
        index += step;
      }
      index = index - size;
    }
	
    for (int i = 0; i < size; i++)		// slot by slot
    {
      if (slots[i] == NULL)
      {      
        return i;
      }
    }
    return -1;
  }
  
  int put(int value)
  {    
    int index = seekSlot(value);	// get empty slot index
    if (index == -1) return index;	// if no empty slots
    slots[index] = value;			
    return index;
  }

  int find(int value)
  { 
	int index = hashFun(value);						//get index
	if (index == -1) 
		return -1;

    for (int i = 0; i < 3; i++)						// 3 times 
    {
      while (index <= size - 1)						// table limit
      {	
		if ( slots[index] == value)				// compare
		{
			return index;						// if equal
		}
        index += step;								// go to next slot  
      }
      index = index - size;							// reaching limit			
    }

    for (int index = 0; index < size; index++)		// slot by slot
    {	
		if ( slots[index] == value)				// compare
		{
			return index;						// if equal
		}		
    }
    return -1;
  }
};

//====================== TEST ========================
int test_hash(HashTable* Table)
{
  int test = 0;
  int t = 0;    
  for (int i = 0; i <= Table->size; i++) // fill the entire array 
  {    
	t++;	
    Table->put(t);
  }

  if (Table->put(88) != -1) test++;    //the table is full
  if (Table->find(88) != -1) test++;
  if (Table->find(1) != Table->hashFun(1) ) test++;
  return test;
}

int main()
{
	HashTable* Table = new HashTable(11, 3);	
	test_hash(Table);		
	return 0;
}
