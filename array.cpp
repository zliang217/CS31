#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

int tally(const string a[], int n, string target);
int findMatch(const string a[], int n, string target);
bool findRun(const string a[], int n, string target, int& begin, int& end);
int positionOfMin(const string a[], int n);
int moveToEnd(string a[], int n, int pos);
int moveToBeginning(string a[], int n, int pos);
int findDifference(const string a1[], int n1, const string a2[], int n2);
int eliminateDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
int makeMerger(const string a1[], int n1, const string a2[], int n2,
               string result[], int max);
int separate(string a[], int n, string separator);

int main() {
}

int tally(const string a[], int n, string target){
    if (n<0){
        return -1;
    }
    else{
        int count=0;
        for (int i=0; i<n; i++){
            if (a[i]==target){
                count++;
            }
        }
        return count;
    }
}

int findMatch(const string a[], int n, string target){
    for (int i=0; i<n; i++){
        if(a[i]==target){
            return i;
        }
    }
    return -1;
}

bool findRun(const string a[], int n, string target, int& begin, int& end){ //check this function later
    for (int i=0; i<n; i++){
        if(a[i]==target){
            begin=i;
            int j=i+1;
            if (j<n && a[j]==a[j-1]){
                j++;
            }
            else{
                end=j-1;
                return true;
            }
        }
    }
    return false;
}

int positionOfMin(const string a[], int n){
    if (n==0){
        return -1;
    }
    else{
        int min=0;
        for (int i=0; i<n-1; i++){
            if (a[i].compare(a[min])<0){
                min = i;
            }
        }
        return min;
    }
}

int moveToEnd(string a[], int n, int pos){
    string elim=a[pos];
    for (int i=pos; i<n-1; i++){
        a[i]=a[i+1];
    }
    a[n-1]=elim;
    return pos;
}

int moveToBeginning(string a[], int n, int pos){
    string elim=a[pos];
    for (int i=0; i<pos; i++){
        a[i+1]=a[i];
    }
    a[0]=elim;
    return pos;
}

int findDifference(const string a1[], int n1, const string a2[], int n2){
    int n=min(n1, n2);
    for (int i=0; i<n; i++){
        if (a1[i]!=a2[i]){
            return i;
        }
    }
    return n+1;
}

int eliminateDups(string a[], int n){
    int begin;
    int end;
    for (int i=0; i<n; i++){
        if(findRun(a, n, a[i], begin, end)){
            for (int j=begin; j<=end){
                a[j]=a[j+begin-end]
            }
        }
    }
}




















