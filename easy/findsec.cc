#include <iostream>
#include <stdio.h>
using namespace std;
void find(int *a,int n){
	for(int i=0;i+1<n;i+=2)
		if(a[i]<a[i+1]) swap(a,i,i+1);
	int shell=2;
	for(int shell=4;shell<n;shell*=2){
		for(int i=0;i<n;i+=shell){
			int t=shell/2;
			if(a[i+t+1]>a[i+1])  swap(a,i+1,i+t+1);
			if(a[i+t]>a[i]) {
				if(a[i+t+1]>a[i+1])  swap(a,i+1,i+t+1);
			if(a[

int main(){
	
