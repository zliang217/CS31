#include<iostream>
#include<fstream>
#include<cctype>
using namespace std;

int stuff(int lineLength, istream& inf, ostream& outf);
int nextWordPortion (istream& inf, int num);
char getPreviousNChar (istream& inf, int num, int n);
char getNextNChar (istream& inf, int num, int n);
bool newParagraph (istream& inf, int num, int n);
bool lastRealChar (istream& inf, int num);

int main(){
    ifstream infile("/Users/apple/Desktop/Zhengjun Liang/College/Academics/Classes/CS/ComSci 31/Project 5/Project 5/data.txt");
    ofstream outfile("/Users/apple/Desktop/Zhengjun Liang/College/Academics/Classes/CS/ComSci 31/Project 5/Project 5/results.txt");
    //int n1 = nextWordPortion(infile, 10);
    //int n2 = nextWordPortion(infile, 3);
    //cerr << n1 << " " << n2 << endl;
    stuff(24, infile, outfile);
    //char next = getNextChar(infile, 3);
    //char prev = getPreviousChar(infile, 3);
    //cerr << prev << next << endl;
    //cerr << newParagraph(infile, 0) << newParagraph(infile, 5) << endl;
    //cerr << lastRealChar(infile, 24) << endl;
    
}

int nextWordPortion (istream& inf, int num){ //get the length of the word portion following pos, seems like it works
    inf.clear();
    inf.seekg(0, ios::beg); //clear up and go back to the beginning
    int pos = 0;
    int count = 0;
    char c;
    while (inf.get(c)){
        if (pos > num && c!=' ' && c!='-' && c!='\n'){
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
    inf.clear(); //clear up
    inf.seekg(0, ios::beg); //back to the beginning
    for (int i=0; i<=num; i++){ //go back to the original position to continue
        inf.get(c);
    }
    return count;
}

char getPreviousNChar (istream& inf, int num, int n){ //namely, get the char n index before the current char
    inf.clear();
    inf.seekg(0, ios::beg);
    int count = 0;
    char c;
    char ch = ' ';
    while (inf.get(c)){
        if (count == num-n){
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

char getNextNChar (istream& inf, int num, int n){ //namely, get the char n index behind the current char
    inf.clear();
    inf.seekg(0, ios::beg);
    int count = 0;
    char c;
    char ch = ' ';
    while (inf.get(c)){
        if (count == num+n){
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

bool lastRealChar (istream& inf, int num){ //used to verify that whether the current char is the last meaningful char
    inf.clear();
    inf.seekg(0, ios::beg); //clear up and go back to the beginning
    int pos = 0;
    char c;
    bool last = true;
    while (inf.get(c)){
        if (pos > num){
            if (c != ' ' && c != '\n'){
                last = false;
            }
            else if (newParagraph(inf, pos, 0)){
                for (int i=0; i<3; i++){
                    inf.get(c);
                }
                pos+=3;
            }
        }
        pos++;
    }
    inf.clear(); //clear up
    inf.seekg(0, ios::beg); //back to the beginning
    for (int i=0; i<=num; i++){ //go back to the original position to continue
        inf.get(c);
    }
    return last;
}

bool newParagraph (istream& inf, int num, int n){ //verify that whether we should start a new paragraph
    inf.clear();
    inf.seekg(0, ios::beg);
    int count = 0;
    char c;
    char pString[10] = "#P#";
    bool hasP = true;
    while (inf.get(c)){
        if (count == num+n){
            if (nextWordPortion(inf, count) == 3){
                for (int i=0; i<3; i++){
                    inf.get(c);
                    if (c != pString[i]){
                        hasP = false;
                    }
                }
            }
            else {
                hasP = false;
            }
        }
        count++;
    }
    inf.clear();
    inf.seekg(0, ios::beg);
    for (int i=0; i<=num; i++){
        inf.get(c);
    }
    return hasP;
}

//deal with #P#: multiple consecutive #P# treated as one
//end last line with a new line
//fix the issue of '\n'
//avoid the ' ' at the end of the line
//'\n' followed by ' ' or vice versa
//what if the end is a paragraph
int stuff(int lineLength, istream& inf, ostream& outf){
    int returnNum = 0;
    if (lineLength < 1){
        return 2;
    }
    else{
        char c;
        int outCount = 0; //stores the num of chars we have gone through in the outputfile
        int inCount = 0; //stores the num of chars we have gone through in the input file
        int lineLen = 0; //stores the num of chars in a line we have gone through in the output file
        while (inf.get(c)){
            bool adjPara = true;
            if (c == ' '){
                if (getPreviousNChar(inf, inCount, 1)==' ' || getPreviousNChar(inf, inCount, 1)=='\n'){
                    if (getNextNChar(inf, inCount, 1)!=' ' && getNextNChar(inf, inCount, 1)!='\n'){
                        if (newParagraph(inf, inCount, 0)){
                            int i=4;
                            while (getNextNChar(inf, inCount, i) == ' ') {
                                i++;
                            }
                            if (newParagraph(inf, inCount, i-1)){
                                adjPara=false;
                            }
                            if (adjPara){
                                outf << '\n' << '\n';
                                lineLen = 0;
                                for (int i=0; i<3; i++){
                                    inf.get(c);
                                }
                                inCount+=3;
                                outCount+=3;
                            }
                            else{
                                for (int i=0; i<3; i++){
                                    inf.get(c);
                                }
                                inCount+=3;
                                outCount+=3;
                            }
                        }
                        else{
                            if (lineLen+nextWordPortion(inf, inCount)+1>lineLength && lineLen!=0){
                                outf << '\n';
                                lineLen = 0;
                            }
                        }
                    }
                }
                else if (getPreviousNChar(inf, inCount, 1)!=' ' && getPreviousNChar(inf, inCount, 1)!='\n'){
                    if (getNextNChar(inf, inCount, 1)!=' ' && getNextNChar(inf, inCount, 1)!='\n'){
                        if (newParagraph(inf, inCount, 0)){
                            int i=4;
                            while (getNextNChar(inf, inCount, i) == ' ') { //what if the input file is empty?
                                i++;
                            }
                            if (newParagraph(inf, inCount, i-1)){
                                adjPara=false;
                            }
                            if (adjPara){
                                outf << '\n' << '\n';
                                lineLen = 0;
                                for (int i=0; i<3; i++){
                                    inf.get(c);
                                }
                                inCount+=3;
                                outCount+=3;
                            }
                            else{
                                for (int i=0; i<3; i++){
                                    inf.get(c);
                                }
                                inCount+=3;
                                outCount+=3;
                            }
                        }
                        else if (getPreviousNChar(inf, inCount, 1) == '?' || getPreviousNChar(inf, inCount, 1) == '.'){
                            if (lineLen+nextWordPortion(inf, inCount)+2>lineLength && lineLen!=0){
                                outf << '\n';
                                lineLen = 0;
                            }
                            else{//if it is the start of a new line, no need to output a space
                                if (lineLen != 0 && lineLen != lineLength-2){ //if it is the start of a new line, no need to output a space
                                    outf << ' ' << ' ';
                                    outCount+=2;
                                    lineLen+=2;
                                }
                            }
                        }
                        else{
                            if (lineLen+nextWordPortion(inf, inCount)+1>lineLength && lineLen!=0){
                                outf << '\n';
                                lineLen = 0;
                            }
                            else{
                                if (lineLen != 0 && lineLen != lineLength-1){ //if it is the start of a new line, no need to output a space
                                    outf << ' ';
                                    outCount++;
                                    lineLen++;
                                }
                            }
                        }
                    }
                    else{
                        if (lineLen != 0 && lineLen != lineLength-1){ //if it is the start of a new line, no need to output a space
                            outf << ' ';
                            outCount++;
                            lineLen++;
                        }
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
                if (getPreviousNChar(inf, inCount, 1)!='\n' && getPreviousNChar(inf, inCount, 1)!=' '){
                    if (getNextNChar(inf, inCount, 1)!=' ' && getNextNChar(inf, inCount, 1)!='\n'){
                        if (lineLen+nextWordPortion(inf, inCount)+1>lineLength && lineLen!=0){
                            outf << '\n';
                            lineLen = 0;
                        }
                        else{
                            if (getPreviousNChar(inf, inCount, 1) == '?' || getPreviousNChar(inf, inCount, 1) == '.'){
                                if (lineLen != lineLength-2){
                                    outf << ' ' << ' ';
                                    outCount+=2;
                                    lineLen+=2;
                                }
                            }
                            else{
                                if (lineLen!=0 && lineLen+1!=lineLength){
                                    outf << ' ';
                                    outCount++;
                                    lineLen++;
                                }
                            }
                        }
                    }
                    else{
                        if (lineLen!=0 && lineLen+1!=lineLength){
                            outf << ' ';
                            outCount++;
                            lineLen++;
                        }
                    }
                }
            }
            else{
                if (!lastRealChar(inf, inCount)){
                    if (lineLen>=lineLength){ //if any word portion is longer than length of the line
                        returnNum = 1;
                        lineLen = 1;
                        outf << '\n' << c;
                        outCount++;
                    }
                    else{
                        outf << c;
                        lineLen++;
                        outCount++;
                    }
                }
                else{
                    outf << c << '\n';
                    lineLen++;
                    outCount++;
                    return returnNum;

                }
            }
        inCount++;
        }
        return returnNum;
    }
}
