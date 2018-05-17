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
    string h[7] = { "romanoff", "thor", "rogers", "banner", "", "parker", "rogers" };
    assert(tally(h, 7, "rogers") == 2);
    assert(tally(h, 7, "") == 1);
    assert(tally(h, 7, "rhodes") == 0);
    assert(tally(h, 0, "rogers") == 0);
    assert(findMatch(h, 7, "rogers") == 2);
    assert(findMatch(h, 2, "rogers") == -1);
    int bg;
    int en;
    assert(findRun(h, 7, "banner", bg, en) && bg == 3 && en == 3);
    
    string g[4] = { "romanoff", "thor", "banner", "parker" };
    assert(positionOfMin(g, 4) == 2);
    assert(findDifference(h, 4, g, 4) == 2);
    assert(subsequence(h, 7, g, 4));
    assert(moveToEnd(g, 4, 1) == 1 && g[1] == "banner" && g[3] == "thor");
    
    string f[4] = { "parker", "banner", "thor", "rogers" };
    assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "thor" && f[2] == "banner");
    
    string e[5] = { "parker", "parker", "parker", "thor", "thor" };
    assert(eliminateDups(e, 5) == 2 && e[1] == "thor");
    
    string x[4] = { "rhodes", "rhodes", "tchalla", "thor" };
    string y[4] = { "banner", "parker", "rhodes", "rogers" };
    string z[10];
    assert(makeMerger(x, 4, y, 4, z, 10) == 8 && z[5] == "rogers");
    
    assert(separate(h, 7, "rogers") == 3);
    
    cout << "All tests succeeded" << endl;
}

int tally(const string a[], int n, string target){
    if (n<0){
        return -1; //if n is negative return -1
    }
    else if (n==0){
        return 0;
    }
    else{
        int count=0;
        for (int i=0; i<n; i++){
            if (a[i]==target){
                count++; //add one if the element equals to the target
            }
        }
        return count; //return the number of items that are equal to the target
    }
}

int findMatch(const string a[], int n, string target){
    if (n == 0){
        return -1; //return -1 for empty string, since there is no such element
    }
    
    for (int i=0; i<n; i++){
        if(a[i]==target){
            return i; //this makes sure that the earliest element equal to the target element will be returned
        }
    }
    return -1; //this deals with all erraneous cases, including n being negative and no element equal to the target element
}

bool findRun(const string a[], int n, string target, int& begin, int& end){ //check this function later
    for (int i=0; i<n; i++){
        if(a[i]==target){
            begin=i; //set begin to the first element that equals to the target element
            int j=i+1;
            while (j<n && a[j]==a[j-1]){
                j++;
            } //test whether an element equals the previous element
            end=j-1; //return the last element that equals the previous element, which is j-1, since a[j]!=a[j-1]
            return true;
        }
    }
    return false;
}

int positionOfMin(const string a[], int n){
    if (n<=0){ //return -1 if the funciton should examine no element of the array
        return -1;
    }
    else{
        int min=0;
        for (int i=0; i<n; i++){
            if (a[i].compare(a[min])<0){
                min = i; //replace the previous min if there is a smaller element
            }
        }
        return min;
    }
}

int moveToEnd(string a[], int n, int pos){
    if (n < 0  ||  pos < 0  ||  pos >= n)
        return -1;
    
    string elim=a[pos]; //temporarily store the removed element
    for (int i=pos; i<n-1; i++){
        a[i]=a[i+1]; //move every element to the slot one after
    }
    a[n-1]=elim; //place the removed element to the end
    return pos;
}

int moveToBeginning(string a[], int n, int pos){ //similar to the one above
    if (n < 0  ||  pos < 0  ||  pos >= n)
        return -1;
    
    string elim=a[pos];
    for (int i=pos; i>0; i--){
        a[i]=a[i-1];
    }
    a[0]=elim;
    return pos;
}

int findDifference(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0  ||  n2 < 0)
        return -1;
    
    int n=min(n1, n2);
    for (int i=0; i<n; i++){
        if (a1[i]!=a2[i]){
            return i; //return the first element that is not the same
        }
    }
    return n+1; //if one array is a "subset" of the other, return the length of the smaller array + 1
}

int maxLength(string a[], int n){ //an auxiliary function I created myself, returning the maximum length of consecutive strings
    int begin;
    int end;
    int max = 1;
    for (int i=0; i<n; i++){
        findRun(a, n, a[i], begin, end);
        int len = end - begin + 1;
        if (len>max){
            max=len;
        }
    }
    return max;
}

int eliminateDups(string a[], int n){
    int begin = 0;
    int end = 0;
    int last = n;
    int i = 0;
    
    if (n < 0)
        return -1;
    if (n <= 1)
        return n;
    
    while (maxLength(a, last)>1) { //if there are repeated consecutive elements
        findRun(a, last, a[i], begin, end);
        for (int j=begin+1; j<=end; j++){
            moveToEnd(a, n, j); //move redundant elements to the end
        }
        last -= end - begin; //excluding the removed element
        i++;
    }
    return last; //returns the first element we are not concerned about anymore
}

bool subsequence(const string a1[], int n1, const string a2[], int n2){
    if (n1 < 0  ||  n2 < 0)
        return false;
    
    else if (n2 == 0){
        return true;
    }
    int index = -1;
    for (int i=0; i<n2; i++){
        if (tally(a1, n1, a1[findMatch(a1, n1, a2[i])])<tally(a2, n2, a2[i])){
            return false;
        }
        else{
            if (index <= findMatch(a1, n1, a2[i])) //see if elements of a2 appear in a1 in the original order
                index = findMatch(a1, n1, a2[i]);
            else{
                return false;
            }
        }
    }
    return index != -1;
}

bool nondec (const string a[], int n){ //An auxiliary funciton I made myself, verifying whether the elements in an array are non-decreasing
    /*string b[n];
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
    }*/
    //the previous portion creates a new
    for (int i=0; i<n-1; i++){
        if(a[i].compare(a[i+1])>0){
            return false;
        }
    }
    return true;
}

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max){
    if (n1 < 0  ||  n2 < 0  ||  n1+n2 > max  || !isOrdered(a1, n1)  ||
        !isOrdered(a2, n2))
        return -1;
    
    int pos = 0;
    if (!nondec(a1, n1) ||  (! nondec(a2, n2)) || (max<n1+n2) ){//return −1 if the result would have more than max elements or if a1 and/or a2 are not in nondecreasing order
        return -1;
    }
    else{
        /*string b[n1];
        for (int i=0; i<n1; i++){
            result[i]=a1[i];
        }

        for (int j=0; j<n2; j++){
            for (int i=0; i<n1; i++){
                b[i]=result[i];
            }
            pos = separate(b, n1+j, a2[j]);
            insert(result, a2[j], n1+j, pos);
        
        }*/
        //the above portion requires creating a new array
        for (int i=0; i<n1; i++){
            result[i]=a1[i]; //first put elements of a1 into the result array
        }
        for (int j=0; j<n2; j++){
            int i=0;
            while (i<n1+j && result[i].compare(a2[j])<0){
                i+=1;
            }
            pos=i;
            insert(result, a2[j], n1+j, pos); //insert elements of a2 to appropriate positions
        }
        return n1+n2;
    }
}

void insert(string a[], string s, int n, int pos){ //an auxiliary function I wrote myself, used to insert elements
    for (int i=n; i>pos; i--){
        a[i]=a[i-1];
    }
    a[pos]=s;
}

int separate(string a[], int n, string separator){
    if (n < 0)
        return -1;
    
    for (int i=0; i<n; i++){
        if (a[i].compare(separator) < 0){
            moveToBeginning(a, n, i);
        }
    } //move all the elements that are less than the seperator to the beginning
    for (int i=0; i<n; i++){
        if (a[i].compare(separator)>=0){
            return i;
        }
    } //find the first element that is greater than or equal to separator
    return n;
}
