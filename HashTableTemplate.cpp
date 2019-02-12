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
          return index;
        }
        index += step;
      }
      index = index - size;
    }

    for (int i = 0; i < size; i++)
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
    if (index == -1) return index;

	int char_lengh;
	for (int i = 0; *( value+i ) != '\0' ; i++)  // copy string to new string 
	{	
		char_lengh = i+1;
	}
	
	char* val = new char[char_lengh];		// 128 - string length limit 
	for (int i = 0; i <= char_lengh; i++)	// copy string to new string 
	{
		*( val + i ) = *( value+i );
		*( val + i + 1 ) = '\0';
	}

    slots[index] = val;
    return index;
  }

  int find(char* value)
  {    
	for (int index = 0; index < size; index++) // table
    {
		if (slots[index] != NULL)
		{				
			for (int i = 0; i < 128; i++) //  
			{
				char slot = *( slots[index]+i );
				char val  = *( value+i );
				
				if ( slot == val && val == 0 ) 
					return index;				

				if ( slot != val || val == 0)				
						break;
			}
		}
		else if (value == NULL)
				return index;
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
  char* value2 = "It’s";
  char value3[54] = "It’s better to light a candle than curse the darkness";
  char* value4 = "darkness";

  char* val_2 = "You can’t make bricks without straw";
  int step = Table->step;
  int test = 0;

  // FIND
  if (Table->find(NULL) != 0) test++;     // checking the filling of the empty table
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

  return test;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HashTable* Table = new HashTable(17, 3);
	HashTable* Table2 = new HashTable(12, 3);
	test_hash(Table, Table2);	
	return 0;
	delete Table;
	delete Table2;
}
*/
