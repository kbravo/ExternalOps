#include <iostream>
#include <string>
#include <cstdlib>
#include "ExternalSort.h"
#include "ExternalSearch.h"

using namespace std;

int main(int argc, const char* argv[])
{	
	if(argv[1] == string("1")) // Run P4 Part 1
	{
		
		int chunk_size = atoi(argv[4]);
		extern_sort(argv[2], argv[3], argv[5], chunk_size);
	}
	else if(argv[1] == string("2"))
	{
		for(int i = 3; i < argc; i++) {
			bool ret = extern_search(argv[2], argv[i]);
			if(ret == true)
				cout << "found" << endl;
			else
				cout << "missing" << endl;
		}
	}
	return 0;
}
