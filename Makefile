all:
	g++ -o program ExternalSort.cpp ExternalSearch.cpp main.cpp -std=c++11
clean: 
	$(RM) program 