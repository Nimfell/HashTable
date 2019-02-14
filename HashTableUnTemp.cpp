#include <stdio.h>
#include <cstdlib>
#include <list>
using namespace std;

int hashFun_1(int value, int size)
{   
	if (value == NULL)
		return -1;

	int p = 37; // Prime number
	int a = 30; // 1 ... ð-1
	int b = 2;  // 0 ... ð-1

	int index = ( (a*value + b) % p ) % size;

	return index;
}

int hashFun_2(int value, int size)
{    
	if (value == NULL)
		return -1;
	int p = 17; // Prime number
	int a = 9;  // 1 ... ð-1
	int b = 5;  // 0 ... ð-1
	int index = ( (a*value + b) % p ) % size;
	return index;
}

int hashFun_3(int value, int size)
{    
	if (value == NULL) return -1;
	int p = 37; // Prime number
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
  list<int>* slots;  
  HashFunction _hashFun;
  int number_of_collisions;

  HashTable(int sz, int stp)
  {
    size = sz;
    step = stp;
	number_of_collisions = 0;
    slots = new list<int>[size];
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
          return index;  
  }
  
  int put(int value)
  {    
    int index = seekSlot(value);	// get empty slot index
    if (index == -1) return index;	// if no empty slots
    
	slots[index].push_back(value);			
    return index;
  }

  int find(int value)
  { 
	int index = hashFun(value);						//get index
	list<int> List = slots[index];

	for (auto i = List.begin(); i != List.end(); ++i)
	{		
		if (*i == value)
			return index;		
	}
	return -1;
  }
};
/*
//====================== TEST ========================
int test_hash(HashTable* Table)
{
	int test = 0;
	int t = 0;    
	for (int i = 0; i <= 100; i++) // fill the entire array 
	{    
		t++;	
		Table->put(t);
	}
	if (Table->find(1) != Table->hashFun(1) ) test++;
	if (Table->find(38) != Table->hashFun(38) ) test++;
	return test;
}

int main()
{
	//vector <int> v;
	HashTable* Table = new HashTable(17, 3);	
	test_hash(Table);			
	return 0;
}
*/
