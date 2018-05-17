#include<iostream>
#include<fstream>
#include<cctype>
using namespace std;

int stuff(int lineLength, istream& inf, ostream& outf);
int nextWordPortion (istream& inf, int num);
char getPreviousChar (istream& inf, int num);
char getNextChar (istream& inf, int num);

int main(){
    ifstream infile("/Users/apple/Desktop/Zhengjun Liang/College/Academics/Classes/CS/ComSci 31/Project 5/Project 5/data.txt");
    ofstream outfile("/Users/apple/Desktop/Zhengjun Liang/College/Academics/Classes/CS/ComSci 31/Project 5/Project 5/results.txt");
    //int n1 = nextWordPortion(infile, 10);
    //int n2 = nextWordPortion(infile, 3);
    //cerr << n1 << " " << n2 << endl;
    stuff(40, infile, outfile);
    //char next = getNextChar(infile, 3);
    //char prev = getPreviousChar(infile, 3);
    //cerr << prev << next << endl;
}

int nextWordPortion (istream& inf, int num){ //get the length of the word portion following pos, seems like it works
    inf.clear();
    inf.seekg(0, ios::beg);
    int pos = 0;
    int count = 0;
    char c;
    while (inf.get(c)){
        if (pos > num && c!=' ' && c!='-'){
            count++;
        }
        else if (pos > num && c=='-'){
            inf.clear();
            inf.seekg(0, ios::beg);
            for (int i=0; i<=num; i++){
                inf.get(c);
            }
            return count+1; //since '-' is also part of the wordportion
        }
        else if (pos > num){
            inf.clear();
            inf.seekg(0, ios::beg);
            for (int i=0; i<=num; i++){
                inf.get(c);
            }
            return count;
        }
        pos++;
    }
    inf.clear();
    inf.seekg(0, ios::beg);
    for (int i=0; i<=num; i++){
        inf.get(c);
    }
    return count;
}

char getPreviousChar (istream& inf, int num){
    inf.clear();
    inf.seekg(0, ios::beg);
    int count = 0;
    char c;
    char ch = ' ';
    while (inf.get(c)){
        if (count == num-1){
            ch = c;
        }
        count++;
    }
    inf.clear();
    inf.seekg(0, ios::beg);
    for (int i=0; i<=num; i++){
        inf.get(c);
    }
    return ch;
}

char getNextChar (istream& inf, int num){
    inf.clear();
    inf.seekg(0, ios::beg);
    int count = 0;
    char c;
    char ch = ' ';
    while (inf.get(c)){
        if (count == num+1){
            ch = c;
        }
        count++;
    }
    inf.clear();
    inf.seekg(0, ios::beg);
    for (int i=0; i<=num; i++){
        inf.get(c);
    }
    return ch;
}

int stuff(int lineLength, istream& inf, ostream& outf){
    if (lineLength < 1){
        return 2;
    }
    else{
        char c;
        int outCount = 0; //stores the num of chars we have gone stored in the outputfile
        int inCount = 0; //stores the num of chars we have gone through of the input file
        int lineLen = 0; //stores the num of chars in a line we have gone through in the output file
        while (inf.get(c)){
            if (c == ' '){
                if (getPreviousChar(inf, inCount)!=' '){
                    if (getNextChar(inf, inCount)!=' '){
                        if (getPreviousChar(inf, inCount) == '?' || getPreviousChar(inf, inCount) == '.'){
                            if (lineLen+nextWordPortion(inf, inCount)+2>lineLength){
                                outf << '\n';
                                lineLen = 0;
                            }
                            else{
                                outf << ' ' << ' ';
                                outCount+=2;
                                lineLen+=2;
                            }
                        }
                        else{
                            if (lineLen+nextWordPortion(inf, inCount)+1>lineLength){
                                outf << '\n';
                                lineLen = 0;
                            }
                            else{
                                outf << ' ';
                                outCount++;
                                lineLen++;
                            }
                        }
                    }
                    else{
                        outf << ' ';
                        outCount++;
                        lineLen++;
                    }
                }
            }
            else if (c == '-'){ //deal with '-'
                if (lineLen+nextWordPortion(inf, inCount)+1>lineLength){
                    outf << '-';
                    outf << '\n';
                    lineLen = 0;
                }
                else{
                    outf << '-';
                    outCount++;
                    lineLen++;
                }
            }
            else if (c == '\n'){
                if (getPreviousChar(inf, inCount)!='\n'){
                    if (getNextChar(inf, inCount)!=' ' && getNextChar(inf, inCount)!='\n'){
                        if (lineLen+nextWordPortion(inf, inCount)+1>lineLength){
                            outf << '\n';
                            lineLen = 0;
                        }
                        else{
                            if (getPreviousChar(inf, inCount) == '?' || getPreviousChar(inf, inCount) == '.'){
                                outf << ' ' << ' ';
                                outCount+=2;
                                lineLen+=2;
                            }
                            else{
                                outf << ' ';
                                outCount++;
                                lineLen++;
                            }
                        }
                    }
                    else{
                        outf << ' ';
                        outCount++;
                        lineLen++;
                    }
                }

            }
            else{
                lineLen++;
                outf << c;
                outCount++;
            }
            inCount++;
        }
        return 0;
    }
}
