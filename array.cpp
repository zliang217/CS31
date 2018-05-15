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
    int b;
    int e;
    string folks[8] = {
        "parker", "thor", "stark", "romanoff",
        "banner", "tchalla", "rhodes", "rogers"
    };
    string people[5] = { "parker", "thor", "stark", "banner", "romanoff" };
    string d[9] = {
        "thor", "romanoff", "parker", "parker", "stark", "stark", "stark", "parker", "parker"
    };
    string cast[5] = { "parker", "thor", "stark", "banner", "romanoff" };
    string roles[4] = { "parker", "thor", "tchalla", "rhodes" };
    string big[10] = { "parker", "thor", "stark", "banner", "romanoff", "stark" };
    string little1[10] = { "thor", "banner", "romanoff" };
    string little2[10] = { "stark", "thor" };
    string little3[10] = { "thor", "stark", "stark" };
    string little4[10] = { "thor", "thor", "stark" };
    string x[5] = { "banner", "rhodes", "rogers", "stark", "tchalla" };
    string y[4] = { "parker", "rogers", "rogers", "thor" };
    string z[20];
    string f[6] = { "rhodes", "banner", "stark", "parker", "thor", "rogers" };
    string g[4] = { "romanoff", "rogers", "thor", "banner" };
    cout << "The function you want to call: ";
    string function;
    cin >> function;
    if (function == "tally"){
        int n = tally(d, 0, "thor");
        cout << n <<endl;
    }
    else if (function == "findMatch"){
        int n = findMatch(d, 9, "parker" );
        cout << n <<endl;
    }
    else if (function == "findRun"){
        bool b1 = findRun(d, 9, "parker", b, e);
        cout << b1 << endl;
        cout << b << endl;
        cout << e << endl;
    }
    else if (function == "positionOfMin"){
        int n = positionOfMin(people, 5);
        cout << n << endl;
    }
    else if (function == "moveToEnd"){
        int n = moveToEnd(people, 5, 1);
        for (int j=0; j<5; j++){
            cout << people[j] << " ";
        }
        cout << endl;
        cout << n << endl;
    }
    else if (function == "moveToBeginning"){
        int n = moveToBeginning(people, 5, 1);
        for (int j=0; j<5; j++){
            cout << people[j] << " ";
        }
        cout << endl;
        cout << n << endl;
    }
    else if (function == "findDifference"){
        string cast[5] = { "parker", "thor", "stark", "banner", "romanoff" };
        string roles[4] = { "parker", "thor", "tchalla", "rhodes" };
        int k = findDifference(cast, 5, roles, 4);
        cout << k << endl;
        int m = findDifference(cast, 2, roles, 1);
        cout << m << endl;
    }
    else if (function == "eliminateDups" ){
      
        string d[10] = {
            "thor", "romanoff", "parker", "parker", "jasper", "stark", "stark", "stark", "parker", "parker"
        };
        int p = eliminateDups(d, 10);
        for (int j=0; j<10; j++){
            cout << d[j] << " ";
        }
        cout << endl;
        cout << p << endl;
    }
    else if (function == "subsequence" ){
        string s;
        getline(cin, s);
        int i;
        cin >> i;
        bool b1 = subsequence(big, 6, little1, 3);  // returns true
        bool b2 = subsequence(big, 6, little2, 2);  // returns false
        bool b3 = subsequence(big, 6, little3, 3);  // returns true
        bool b4 = subsequence(big, 6, little4, 3);  // returns false
        cout << b1 << " " << b2 << " " << b3 << " " << b4 << " " << endl;
    }
    else if (function == "makeMerger"){
        int n = makeMerger(x, 5, y, 4, z, 20);
        for (int j=0; j<n; j++){
            cout << z[j] << " ";
        }
        cout << endl;
        cout << n << endl;
        
    }
    else if (function == "separate"){
        int r = separate(f, 6, "romanoff");
        for (int j=0; j<6; j++){
            cout << f[j] << " ";
        }
        cout << endl;
        cout << r << endl;
    }
}

int tally(const string a[], int n, string target){
    if (n<0){
        return -1; //if n is negative return -1
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
        return 0; //return 0 for empty string
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
    string elim=a[pos]; //temporarily store the removed element
    for (int i=pos; i<n-1; i++){
        a[i]=a[i+1]; //move every element to the slot one after
    }
    a[n-1]=elim; //place the removed element to the end
    return pos;
}

int moveToBeginning(string a[], int n, int pos){ //similar to the one above
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
    int index = -1;
    for (int i=0; i<n2; i++){
        if (index <= findMatch(a1, n1, a2[i])) //see if elements of a2 appear in a1 in the original order
            index = findMatch(a1, n1, a2[i]);
        else{
            return false;
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
