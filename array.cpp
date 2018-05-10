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
int maxLength(string a[], int n); //a function I created myself, used to get the maximum length of consecutive identical strings
int eliminateDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
bool nondec(string a[], int n);//a function I created myself, to test whether a given array of strings are sorted in decending order
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max);
void insert(string a[], string s, int n, int pos); //a function I created myself, used to insert a string to a given array, once at a call
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

int moveToBeginning(string a[], int n, int pos){ //interestingly n is not used in this function, not sure whether I made a mistake here
    string elim=a[pos];
    for (int i=pos; i>0; i--){
        a[i]=a[i-1];
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

int maxLength(string a[], int n){
    int begin=0;
    int end=0;
    int len = end - begin + 1;
    int max = 1;
    int i = 0;
    while(i<n){
        findRun(a, n, a[i], begin, end);
        if (len>max){
            max=len;
        }
        i+=len;
    }
    return max;
}

int eliminateDups(string a[], int n){
    int begin = 0;
    int end = 0;
    int last = 0;
    int i = 0;
    while (maxLength(a, last)>1) {
        last = n - (end - begin);
        findRun(a, last, a[i], begin, end);
        for (int j=i; j<end; j++){
            moveToEnd(a, n, i+1);
        }
        i++;
    }
    return last;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2){
    int index = -1;
    for (int i=0; i<n2; i++){
        if (index <= findMatch(a1, n1, a2[i]))
            index = findMatch(a1, n1, a2[i]);
        else{
            return false;
        }
    }
    return index != -1;
}

bool nondec (const string a[], int n){
    string b[n];
    int last = n;
    for (int i=0; i<n; i++){
        b[i]=a[i];
    }
    for (int j=0; j<n; j++){
        if (positionOfMin(b, last) != 0){
            return false;
        }
        moveToEnd(b, n, 0);
        last--;
    }
    return true;
}

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max){
    int pos;
    if (!nondec(a1, n1) ||  (! nondec(a2, n2)) || (max<n1+n2) ){
        return -1;
    }
    else{
        
        string b[n1];
        for (int i=0; i<n1; i++){
            b[i]=a1[i];
            result[i]=a1[i];
        }
        for (int j=0; j<n2; j++){
            pos=separate(b, n1, a2[j]);
            insert(result, a2[j], n1+1+j, pos);
        }
        return n1+n2;
    }
}

void insert(string a[], string s, int n, int pos){
    for (int i=n; i>pos; i++){
        a[i]=a[i-1];
    }
    a[pos]=s;
}

int separate(string a[], int n, string separator){
    for (int i=0; i<n; i++){
        if (a[i].compare(separator) < 0){
            moveToBeginning(a, n, i);
        }
    }
    for (int i=0; i<n; i++){
        if (a[i].compare(separator)>=0){
            return i;
        }
    }
    return n;
}
