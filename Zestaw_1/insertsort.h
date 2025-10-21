/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 20.10.25

Opis:
Algorytm sortowania przez wstawianie, ktory
porownuje dany element z elementami listy, dopóki
nie znajdzie wiêkszego badz rownego elementu. 
Wtedy dany element wstawiany w to miejsce.
Proces powtarzamy az do uporzadkowania listy
-----------------------------------------------*/
#ifndef INSERTSORT_H
#define INSERTSORT_H

//include <insertsort.h>
#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

template<typename T>
void insertsort(vector<T>& ptr, int n){
	int j;
	T insert_number;
	for(int i = 1; i < n; i++){
		insert_number = ptr[i];
		j = i - 1;
		while(j >= 0 && ptr[j] > insert_number){
			ptr[j+ 1] = ptr[j];
			j--;
		}
		ptr[j+ 1] = insert_number;
	}
}

#endif //INSERTSORT_H
