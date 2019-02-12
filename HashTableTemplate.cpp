#include <stdio.h>
#include < string.h > 

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
    if (value == NULL)
		return -1;
	int index = 0;	 
    index = (int)value[0];
    for (int i = 1; value[i] != 0; i++)  // adder of sumbols
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
          return index;
        }
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
  
  int put(char* value)
  {    
    int index = seekSlot(value);
    if (index == -1) return index;

	int char_lengh = strlen(value); 	
	char* val = new char[char_lengh];		
	strcpy (val, value);

    slots[index] = val;
    return index;
  }

  int find(char* value)
  { 
	int index = hashFun(value);						//get index
	if (index == -1) 
		return -1;

    for (int i = 0; i < 3; i++)						// 3 times 
    {
      while (index <= size - 1)						// table limit
      {
		if (slots[index] != NULL)					// if slot is not empty
		{	
			if ( strcmp(value, slots[index]) == 0)	// compare
			{
				return index;						// if equal
			}
		}
        index += step;								// go to next slot  
      }
      index = index - size;							// reaching limit			
    }

    for (int index = 0; index < size; index++)		// slot by slot
    {
		if (slots[index] != NULL)					// if slot is not empty
		{	
			if ( strcmp(value, slots[index]) == 0)	// compare
			{
				return index;						// if equal
			}
		}
    }
    return -1;
  }
};

//====================== TEST ========================
/*
int test_hash(HashTable* Table, HashTable* Table2)
{
  //HashTable* Table = new HashTable(17, 3);
  char* value = "dark";
  char* value2 = "ItÒs";
  char value3[54] = "ItÒs better to light a candle than curse the darkness";
  char* value4 = "darkness";

  char* val_2 = "You canÒt make bricks without straw";
  int step = Table->step;
  int test = 0;

  // FIND
  if (Table->find(NULL) != -1) test++;    // checking the filling of the empty table
                                          // if (Table->find(0) != -1) test++;       // this value is not in the table - don't work
  // PUT
  int index = Table->hashFun(value);        // index = 6
  for (int i = 0; i < Table->size - 2; i++) // fill the entire array except for one cell
  {
    index = (index <= Table->size - 1) ? index : index - Table->size;
    Table->put(value);
    index += step;
  }
  index = (index <= Table->size - 1) ? index : index - Table->size;
  if (Table->put(value3) != index) test++;
  if (Table->find(value3) != index) test++;
 
  if (Table->put(value2) != 12) test++;
  if (Table->put(val_2) != -1) test++;
  if (Table->find(val_2) != -1) test++;
  if (Table->put(value4) != -1) test++;    //the table is full
  if (Table->find(value4) != -1) test++;

  char t[3] = "0E";
  char* _t = t+1;
    
  for (int i = 0; i <= Table2->size; i++) // fill the entire array except for one cell
  {    
	*_t = 49 + i;	
    Table2->put(t);
  }
  if (Table2->put("en") != -1) test++;    //the table is full
  if (Table2->find("en") != -1) test++;
  if (Table2->find("01") != Table2->hashFun("01") ) test++;

  return test;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HashTable* Table = new HashTable(17, 3);
	HashTable* Table2 = new HashTable(11, 5);
	test_hash(Table, Table2);	
	delete Table;
	delete Table2;
	return 0;
}*/

