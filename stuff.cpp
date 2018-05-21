#include<iostream>
#include<fstream>
#include<cctype>
using namespace std;

int stuff(int lineLength, istream& inf, ostream& outf);
int nextWordPortion (istream& inf, int num); //get the length of the word portion following pos
char getPreviousNChar (istream& inf, int num, int n); //namely, get the char n index before the current char
char getNextNChar (istream& inf, int num, int n); //namely, get the char n index after the current char, similar to the previous function
bool newParagraph (istream& inf, int num, int n); //verify that whether we should start a new paragraph, index n added for some flexibility
bool lastRealChar (istream& inf, int num); //used to verify that whether the current char is the last meaningful char

int main(){
    ifstream infile("/Users/apple/Desktop/Zhengjun Liang/College/Academics/Classes/CS/ComSci 31/Project 5/Project 5/data.txt");
    ofstream outfile("/Users/apple/Desktop/Zhengjun Liang/College/Academics/Classes/CS/ComSci 31/Project 5/Project 5/results.txt");
    stuff(20, infile, outfile);
}

int nextWordPortion (istream& inf, int num){ //get the length of the word portion following pos
    inf.clear();
    inf.seekg(0, ios::beg); //clear up and go back to the beginning
    int pos = 0; //used to denote the index of the current character
    int count = 0; //used to count the length of the word portion
    char c;
    while (inf.get(c)){
        if (pos > num && c!=' ' && c!='-' && c!='\n'){ //certain chars that are regarded as the end of a word portion
            count++;
        }
        else if (pos > num && c=='-'){ //if the next character is '-'
            inf.clear();
            inf.seekg(0, ios::beg); //stop counting and clear up
            for (int i=0; i<=num; i++){
                inf.get(c);
            } //get back to the original position
            return count+1; //return the length of the word portion, +1 since '-' is also part of the wordportion
        }
        else if (pos > num){//if we encounter either ' ' or '\n'
            inf.clear();
            inf.seekg(0, ios::beg); //stop counting and clear up
            for (int i=0; i<=num; i++){
                inf.get(c);
            } //get back to the original position
            return count; //return the length of the word portion
        }
        pos++;
    }
    inf.clear(); //clear up
    inf.seekg(0, ios::beg); //back to the beginning
    for (int i=0; i<=num; i++){ //go back to the original position to continue
        inf.get(c);
    }
    return count; //return the length of the word portion
}

char getPreviousNChar (istream& inf, int num, int n){ //namely, get the char n index before the current char
    inf.clear();
    inf.seekg(0, ios::beg);
    int count = 0;
    char c;
    char ch = ' '; //initialize ch as ' ' for convenience
    while (inf.get(c)){
        if (count == num-n){
            ch = c;
        } //if we get to the desired position, assign the character to ch, which we will return
        count++;
    }
    inf.clear();
    inf.seekg(0, ios::beg);
    for (int i=0; i<=num; i++){
        inf.get(c);
    }
    return ch;
}

char getNextNChar (istream& inf, int num, int n){ //namely, get the char n index behind the current char, similar to the previous function
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
    inf.clear(); //meaningful char means "we have something to print out"
    inf.seekg(0, ios::beg); //clear up and go back to the beginning
    int pos = 0; //used to denote the position of the current character
    char c;
    bool last = true; //true by default
    while (inf.get(c)){
        if (pos > num){
            if (c != ' ' && c != '\n'){
                last = false;
            } //this means that we encounter some meaningful character, so last is set to false
            else if (newParagraph(inf, pos, 0)){
                for (int i=0; i<3; i++){
                    inf.get(c);
                } // if we encounter #P#, we simply skip it, ans we don't change the value of last since #P# is not meaningful
                pos+=3; //we skip it, which has 3 characters
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

bool newParagraph (istream& inf, int num, int n){ //verify that whether we should start a new paragraph, index n added for some flexibility
    inf.clear(); //n is defined this way: n=0 means verifying whether we should start a paragraph after the current character, and so on
    inf.seekg(0, ios::beg);
    int count = 0;
    char c;
    char pString[10] = "#P#"; //for convenience
    bool hasP = true; //true by default
    while (inf.get(c)){
        if (count == num+n){
            if (nextWordPortion(inf, count) == 3){ //to make sure that #P# is "isolated", otherwise #P# doesn't have its special meaning
                for (int i=0; i<3; i++){
                    inf.get(c);
                    if (c != pString[i]){
                        hasP = false;
                    } //if any character is different from #P#, then we shouldn't start a new paragraph
                }
            }
            else { //if the length of the next word portion is not even 3, it's apparently not #P#
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

void startNewParagraph (istream& inf, ostream& outf, int lineLen, int inCount, bool adjPara){
    char c;
    if (newParagraph(inf, inCount, 0)){ //if we should start a new paragraph
        int i=4;
        while (getNextNChar(inf, inCount, i) == ' ') {
            i++;
        } //skip the following #P# and see if there is any more #P# behind it
        if (newParagraph(inf, inCount, i-1)){ //which means that there is consecutive #P#
            adjPara=false;
        }
        if (adjPara){ //if this is the last of the consecutive #P#, we start a new paragraph now
            outf << '\n' << '\n';
            lineLen = 0;
            for (int i=0; i<3; i++){
                inf.get(c);
            } //we skip #P#
            inCount+=3; //and since we fetched 3 chars in the input file, inCount+=3
        }
        else{ //if this is not the last, we'd rather wait than start a new paragraph right now
            for (int i=0; i<3; i++){
                inf.get(c);
            }
            inCount+=3;
        }
    }
}

//fix the issue of '\n'
//'\n' followed by ' ' or vice versa
//what if the end is a paragraph
int stuff(int lineLength, istream& inf, ostream& outf){ //the required function
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
            bool adjPara = true; //set for the case of consecutive #P#
            if (c == ' '){
                if (getPreviousNChar(inf, inCount, 1)==' ' || getPreviousNChar(inf, inCount, 1)=='\n'){
                    if (getNextNChar(inf, inCount, 1)!=' ' && getNextNChar(inf, inCount, 1)!='\n'){ //if the current char is followed by meaningful characters
                        if (newParagraph(inf, inCount, 0)){ //if we should start a new paragraph
                            int i=4;
                            while (getNextNChar(inf, inCount, i) == ' ') {
                                i++;
                            } //skip the following #P# and see if there is any more #P# behind it
                            if (newParagraph(inf, inCount, i-1)){ //which means that there is consecutive #P#
                                adjPara=false;
                            }
                            if (adjPara){ //if this is the last of the consecutive #P#, we start a new paragraph now
                                outf << '\n' << '\n';
                                lineLen = 0;
                                for (int i=0; i<3; i++){
                                    inf.get(c);
                                } //we skip #P#
                                inCount+=3; //and since we fetched 3 chars in the input file, inCount+=3
                            }
                            else{ //if this is not the last, we'd rather wait than start a new paragraph right now
                                for (int i=0; i<3; i++){
                                    inf.get(c);
                                }
                                inCount+=3;
                                outCount+=3;
                            }
                        }
                        else{ //chaging line if next word portion won't fit in the current line
                            if (lineLen+nextWordPortion(inf, inCount)+1>lineLength && lineLen!=0){
                                outf << '\n';
                                lineLen = 0;
                            }
                        }
                    }
                }
                else if (getPreviousNChar(inf, inCount, 1)!=' ' && getPreviousNChar(inf, inCount, 1)!='\n'){
                    if (getNextNChar(inf, inCount, 1)!=' ' && getNextNChar(inf, inCount, 1)!='\n'){
                        if (newParagraph(inf, inCount, 0)){ //same procesure as above
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
                        else if (getPreviousNChar(inf, inCount, 1) == '?' || getPreviousNChar(inf, inCount, 1) == '.'){ //deal with the case that the previous char is a '?' or '.'
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
                        else{ //same procedure as above
                            if (lineLen+nextWordPortion(inf, inCount)+1>lineLength && lineLen!=0){
                                outf << '\n';
                                lineLen = 0;
                            }
                            else{
                                if (lineLen != 0 && lineLen != lineLength-1){ //if it is the start of a new line or the end of a line, no need to output a space
                                    outf << ' ';
                                    outCount++;
                                    lineLen++;
                                }
                            }
                        }
                    }
                    else{
                        if (lineLen != 0 && lineLen != lineLength-1){ //if it is the start of a new line or the end of a line, no need to output a space
                            outf << ' ';
                            outCount++;
                            lineLen++;
                        }
                    }
                }
            }
            
            else if (c == '-'){ //deal with the case that the previous character is '-'
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
            else if (c == '\n'){ //deal with the case that the previous character is '\n'
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
            else{ //the case that the current character is meaningful
                if (!lastRealChar(inf, inCount)){ //if this is not the last meaningful char
                    if (lineLen>=lineLength){ //if any word portion is longer than length of the line
                        returnNum = 1; //changing returnNum to 1, which we will return
                        lineLen = 1; //get to the next line
                        outf << '\n' << c;
                        outCount++;
                    }
                    else{ //everything normal
                        outf << c;
                        lineLen++;
                        outCount++;
                    }
                }
                else{ //if this is the last meaningful char, wrap up with printing the last meaningful char and '\n' as required
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
