/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 20.10.25

Opis:
Program sluzacy do testowania algorytmu
insertsort oraz mergesort.
-----------------------------------------------*/
#include "insertsort.h"
#include "mergesort.h"
#include <stdio.h>
using namespace std;

int main(){
	vector<int> array_insert = {1,3,4,0,6,1,5,2};
	vector<int> array_merge = {1,3,4,0,6,1,5,2};
	
	int n = array_insert.size();
	
	cout << "Nieposortowana lista:\n";
	for(int i = 0; i < n; i++){
		cout << array_insert[i] << "\n";
	}
	
	int left = 0;
	int right = array_merge.size() - 1;
	

	merge_sort<int>(array_merge, left, right );
	insertsort<int>(array_insert, n);
	
	assert(is_sorted(array_insert.begin(), array_insert.end()) );
	assert(is_sorted(array_merge.begin(), array_merge.end()) );
	
	cout << "Lista pozosrtowana metoda insertsort\n";
	for(int i = 0; i < n; i++){
		cout << array_insert[i] << "\n";
	}
	cout << "\n" << "Lista pozosrtowana metoda mergesort\n";
	
	for(int i = 0; i < n; i++){
		cout << array_insert[i] << "\n";
	}
	
	return 0;
}
