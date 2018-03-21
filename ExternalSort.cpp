#include "ExternalSort.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdbool>

using namespace std;

/*
	External Sorting algorithm.
	Step 1: Reads the input file one chunk at a time
	Step 2: Sorts each chunk
	Step 3: Writes each chunk to a temporary file
	Step 4: Performs a k-wise merge on the temporary files

	Your favorite n*log(n) sorting algorithm.
	Be sure that you use an in-place version of the algorithm.

	i.e. It does not generate a new array to return, but rather
	works by swapping elements in the input array.
	
	Possible options:
		-Quicksort
		-Mergesort
		-Heapsort
		
*/

string getName(int i) {
	string integ = to_string(i+1);
	if(integ.length() == 1) {
		return ("chunk0000" + integ);
	} else if(integ.length() == 2) {
		return ("chunk000"+integ);
	} else if(integ.length() == 3) { 
		return ("chunk00"+integ);
	} else if(integ.length() == 4) { 
		return ("chunk0"+integ);
	} else if(integ.length() >= 5) { 
		return "chunk"+integ;
	}
	return "chunk"+integ;
}

void sort(string * array, int left, int right) {
	int i = left;
	int j = right;
	string tmp;
	string pivot = array[(left+right)/2];

	while(i <= j) {
		while(array[i].compare(pivot) < 0)
			i++;
		while(array[j].compare(pivot) > 0)
			j--;

		if(i <= j) {
			tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
			i++;
			j--;
		}
	}

	if(left < j)
		sort(array, left, j);
	if(i < right)
		sort(array, i, right);
}



void extern_sort(string in_fname, string out_fname,
		string chunk_location, int chunk_size)
{
	infile = in_fname;
	outfile = out_fname;
	chunk_path = chunk_location;
	chunk_cap = chunk_size;
	
	if(chunk_path[0] == '/') {
		chunk_path = chunk_path.substr(1, chunk_path.length());
	}

	if(outfile[0] == '/') {
		outfile = outfile.substr(1, outfile.length());
	}

	if(infile[0] == '/') {
		infile = infile.substr(1, infile.length());
	}
	
	unsigned long int line_count = 0;
	
	fstream in;
	in.open(infile);
	

	string s;
	if(in.is_open()) {
		while(getline(in, s)) {
			line_count++;
		}
		in.close();
	} else {
		cout << "Unable to open file" << endl;
	}
	//LINES COUNTED
		
	unsigned long int chunks = line_count/chunk_cap;
	if(line_count % chunk_cap != 0) {
		chunks++;
	}

	//CHUNKS CALCULATED
	
	int lines_read = 0;

	string *sort_chunk = new string[chunk_cap];
	string chunk_name;
	bool flag = false;

	in.open(infile);
	for(int i = 0; i < chunks; i++) {
		lines_read = 0;
		flag = false;

		if(in.is_open()) {
			chunk_name = getName(i);
			while(getline(in, s)) {
				sort_chunk[lines_read] = s;
				lines_read++;
				if(lines_read == chunk_cap) {
					flag = true;
					sort(sort_chunk, 0, chunk_cap-1);
					write_chunk(chunk_name, sort_chunk, flag, line_count);
					break;
				}
			}
			if(flag == false) {
				sort(sort_chunk, 0, line_count%chunk_cap);
				write_chunk(chunk_name, sort_chunk, flag, line_count);
			} 
		}
	}
	in.close();

	k_merge(chunk_path, outfile, chunks);
	return;
} 

void write_chunk(string fileName, string *array, bool flag, int lines) {
	ofstream out;
	string full_path = chunk_path+fileName;	
	
	out.open(full_path);

	if(out.is_open()) {	
		if(flag == true) {
			for(int i = 0; i < chunk_cap; i++) {
				out << array[i] << "\n";
			}
		} else {
			for(int i = 0; i < lines%chunk_cap; i++) {
				out << array[i] << "\n";
			}
		}
	} else cout << "Unable to open \n";

	out.close();
}

void k_merge(string chunk_location, string out_fname, int num_chunks)
{

	ifstream * streams = new ifstream[num_chunks];
	string *list = new string[num_chunks];

	int files_exhausted = 0;
	int target_index = 0;
	int ahead = 0;

	ofstream output;
	output.open(outfile); //setting up the output stream

	for(int i = 0; i < num_chunks; i++) { // opening the chunk reads
		string chunks_route = chunk_location+getName(i);
		streams[i].open(chunks_route);
		if(!streams[i].is_open()) {
			cout << "file cannot be opened " << chunks_route << endl;
		}
	}

	for(int i = 0; i < num_chunks; i++) {
		getline(streams[i], list[i]);
	}

	while(1) {
		files_exhausted = 0;

		for(int i = 0; i < num_chunks; i++) {
			if(list[i].empty()) {
				files_exhausted++;
				continue;
			} else {
				target_index = i;
				break;
			}
		}
		//The first non-empty here. Can/cannot be the last

		if(files_exhausted >= num_chunks) {
			output.close();
			break;
		}

		for(int i = target_index+1; i < num_chunks; i++) {
			if(list[i].empty()) {
				files_exhausted++;
				continue;
			} else if(list[i] < list[target_index]) {
				target_index = i;
			}
		}

		
		if(files_exhausted >= num_chunks) {
			output.close();
			break;
		}

		if(output.is_open()) {
			output << list[target_index] << endl;
		}
		getline(streams[target_index], list[target_index]);
		if(list[target_index].empty())
			streams[target_index].close();
	}
}


