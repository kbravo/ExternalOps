#include <iostream>
#include <string>
#include <cstdbool>

using namespace std;

string infile;
string outfile;
string chunk_location;
string chunk_path;
int chunk_cap;

// Main function for sorting the file
void extern_sort(string in_fname, string out_fname,
		string chunk_location, int chunk_size);

// Pick your favorite n*log(n) sorting algorithm here!		
void sort(); 

// Write a temporary chunk file
void write_chunk(string fileName, string* array, bool flag, int lines);

// Merges the k temporary files
void k_merge(string chunk_location, string out_fname, int num_chunks);
