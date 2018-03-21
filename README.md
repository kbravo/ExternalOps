# ExternalOps

A library for performing buffered data operations for needs that exceed the RAM.
  
 ---
 
#### Routines
 
##### External Sort

- **extern_sort**: Function for sorting the giant file.

- **sort**: Pick your favorite n*log(n) inplace sorting algorithm here. Possible options: Quicksort, Mergesort, Heapsort, etc.


- **write_chunk**: Writes a temporary chunk file.

- **k_merge**: Merges the k temporary chunks files.

 ##### External Search
 
 - **extern_search**: returns whether the target string is in the giant file (through segmentation of the file and status logging).
    

---

#### Future Work
- Multi-threaded model for performing operations on different chunks at the same time.
- Other modes and operations to be supported like External distribution sort.
- Performance evaluation and benchmarking

