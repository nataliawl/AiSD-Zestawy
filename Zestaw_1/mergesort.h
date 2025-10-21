/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 20.10.25
Opis:
Algorytm sortowania przez scalanie, ktory
stosuje metode dziel i rzad. Sclajumey kolejno
czesci ciagu, az finalnie scalujemy posortowane
polowy ciagu w jedna calos.
-----------------------------------------------*/

#ifndef MERGESORT_H
#define MERGESORT_H
#include <stdio.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Algortm procesu scalania
template<typename T>
void merge(vector<T>& ptr, int left, int mid, int right){
	
	
	int size_left = mid - left + 1;
	
	int size_right = right - mid;
	
	vector<T> left_side(size_left);
	vector<T> right_side(size_right);
	
    //Kopiowanie lewej i prawej strony tablicy
    for (int i = 0; i < size_left; i++){
    	left_side[i] = ptr[left + i];   
	}
	
    for (int j = 0; j < size_right; j++){
    	right_side[j] = ptr[mid + 1 + j];
	}
	
	//Potrzebne zmienne pomocnicze
	int i = 0;
	int j = 0;
	int k = left;
	
   	//Scalujemy elementy     
	while(i < size_left && j < size_right){
		if(left_side[i] <= right_side[j]){
			ptr[k] = left_side[i];
			i++;
		}
		else{
			ptr[k] = right_side[j];
			j++;
		}
		k++;
	}
	
	//Kopiujemy pozostale elementy
	while(i < size_left){
		ptr[k] = left_side[i];
		i++;
		k++;
	}
	
	while(j < size_right){
		ptr[k] = right_side[j];
		j++;
		k++;
	}
	
}

//Algorytm sortowania przez scalanie
template<typename T>
void merge_sort(vector<T>& ptr, int left, int right){
	//Sprawdzamy czy dane sa wlasciwe
	if(left >= right){
		return;
	}
	
	int mid = left + (right - left)/2;
	merge_sort(ptr, left, mid);
	merge_sort(ptr, mid + 1, right);
	merge(ptr, left, mid, right);

}

#endif //MERGESORT_H
