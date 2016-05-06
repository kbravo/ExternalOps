#include <iostream>
#include <fstream>
#include "ExternalSearch.h"

using namespace std;

bool extern_search(string fileName, string toFind)
{

	if(false && fileName[0] == '/') {
		fileName = fileName.substr(1, fileName.length());
	}

	ifstream stream1;
	stream1.open(fileName);

	stream1.seekg(0, stream1.end);
	long end = stream1.tellg();
	stream1.seekg(0,stream1.beg);

	long front = 0;
	long mid = 0;
	long last = -1;

	string x;
	string middle;
	
	while(front < end) {
		
		mid = (front+end)/2;
		
		long offset = 0;
		long last = -1;

		while(1) {
			stream1.seekg(mid + offset);
			stream1 >> x;

			if(last == x.length()) {
				middle = x;
				break;
			} else
				last = x.length();

			offset--;
		}

		if(toFind == middle) {
			stream1.close();
			return true;
		} else if(toFind < middle) {
			end = mid;
		}
		else {
			front = mid + 1;
		}
	}

	stream1.close();
	return false;
}

