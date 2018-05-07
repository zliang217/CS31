#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool hasCorrectSyntax(string song);
bool isTranslatable(string song); //verify whether the song is translatable
bool isColor(char c); //verify whether a certain character is a color
string translation(string song); //input song, return the translation of the song
int numBeat(string song); //input a string, count how many beats are in that string
int translateSong(string song, string& instructions, int& badBeat);

int main() {
    string mySong;
    cout << "Enter your song: ";
    getline(cin, mySong);
    string myInstruct;
    int badBeat;
    translateSong(mySong, myInstruct, badBeat);
    if(isTranslatable(mySong)){
        cout <<myInstruct<<endl;
        cout <<"Numbers returned: "<<int(translateSong(mySong, myInstruct, badBeat))<<endl;
    }
    else if (hasCorrectSyntax(mySong)){
        cout <<"The bad beat is the "<<badBeat<<"th "<<endl;
        cout <<"Number returned: "<<int(translateSong(mySong, myInstruct, badBeat))<<endl;
    }
    else{
        cout <<"Incorrect Syntax"<<endl;
        cout <<"Numbers returned: "<<int(translateSong(mySong, myInstruct, badBeat))<<endl;
    }
}

bool hasCorrectSyntax(string song){
    bool correctness=false;
    if (song==""){ //empty string true by default
        return true;
    }
    else if (!isColor(song[0]) && song[0]!='/'){ //Given an unempty string, the first char can only be color or '/'
        return false;
    }
    for (int i=0; i<song.size()-1; i++){
        if(song[i]=='/'){
            correctness=true;
        }
        else if (isColor(song[i])){
            if (song[i+1]!='/' && !isdigit(song[i+1])){
                return false;
            }
            correctness=true;
        }
        else if (isdigit(song[i])){
            //the only allowed characters after it are a single digit and '/'
            if (song[i+1]=='/'){ //if it is '/', true by default
                correctness=true;
            }
            else if (isdigit(song[i+1]) && !isdigit(song[i+2]) && i!=song.size()-2){ //there can only be consecutive two digits, and make sure that the digits are not out of bound
                correctness=true; //which might be redundant, but doesn't hurt anything
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    correctness=(song[song.size()-1]=='/'); //the last char must be a '/'
    return correctness;
}

bool isTranslatable(string song){
    if (!hasCorrectSyntax(song)){
        return false;
    }
    else{
        for (int i=0; i<song.size();i++){
            if(isdigit(song[i])){
                int digit;
                if(isdigit(song[i+1])) { //no need to worry about boundary problems since it has correct syntax already
                    digit=10*(int(song[i])-48)+(int(song[i+1])-48); //use ASCII code conversion to translate the chars to their corresponding integer values
                    if(digit<2){
                        return false;
                    }
                    
                    for(int j=2;j<=digit;j++){
                        if(i+1+digit>song.size()-1 || song[j+i]!='/'){ //while sustained note is in effect, some non-slash beat sneaks in
                            return false;
                        }
                    }
                    i++; //skip the next digit
                    
                }
                else{
                    digit=int(song[i])-48; //similar to above, in the case of one digit
                    if(digit<2){
                        return false;
                    }
                    for(int j=1;j<=digit;j++){
                        if(i+digit>song.size()-1 || song[j+i]!='/'){
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
}

bool isColor(char c){
    if (c=='G' || c=='g' || c=='R' || c=='r' || c=='Y'|| c=='y' || c=='B' || c=='b' || c=='O' || c=='o'){// only allowed letters for a color
        return true;
    }
    return false;
}

int numBeat(string song){ //count '/' for counting beat numbers, and this is only used when the song has correct syntax, so no need to worry about weird characters
    int count = 0;
    for (int i=0;i<song.size();i++){
        if(song[i]=='/'){
            count++;
        }
    }
    return count;
}

int translateSong(string song, string& instructions, int& badBeat){
    if(isTranslatable(song)){ //if the song is translatable, give the translation
        instructions=translation(song);
        return 0;
    }
    
    if(! hasCorrectSyntax(song)){ //if the song has incorrect syntax, give up and return 1
        return 1;
    }
    
    for (int i=0; i<song.size();i++){
        if(isdigit(song[i])){
            int digit;
            if(isdigit(song[i+1])) { //no need to worry about boundary problems since it has correct syntax already
                digit=10*(song[i]-48)+(song[i+1]-48);
                if(digit<2){
                    badBeat=numBeat(song.substr(0,i+2))+1; //song[i+2] will definitely be / since song doesn't end prematurely
                    return 2;
                }
                
                else if(i+1+digit<=song.size()-1) { //get the number of the abrupt beat when sustained note is in effect
                    for(int j=2;j<digit;j++){
                        if(song[j+i]!='/'){
                            badBeat=numBeat(song.substr(0,i+j+1))+1;
                            return 3;
                        }
                    }
                }
                
                else if(i+1+digit>song.size()-1){ //end prematurely
                    badBeat=numBeat(song)+1;
                    return 4;
                }
                i++;
            }
            else if (!isdigit(song[i+1])){ //similar to above, just this time the case of a single digit
                digit=int(song[i])-48;
                if(digit<2){
                    badBeat=numBeat(song.substr(0,i+1))+1;
                    return 2;
                }
                else if(i+digit<=song.size()-1) {
                    for(int j=1;j<=digit;j++){
                        if(song[j+i]!='/'){
                            badBeat=numBeat(song.substr(0,i+j+1))+1;
                            return 3;
                        }
                    }
                }
                else if(i+1+digit>song.size()-1){
                            badBeat=numBeat(song)+1;
                            return 4;
                }
            }
        }
    }
    return 5;
}
string translation(string song){ //since we use this function only when song is translatable, we don't need to worry about the erraneous situations
    int digit;
    string newSong = "";
    if (song==""){// if the song is empty, just return the empty string
        return song;
    }
    else{
        for(int i=0; i<song.size(); i++){
            if (isColor(song[i])){
                if(isdigit(song[i+1])){
                    if(isdigit(song[i+2])){
                        digit=10*(int(song[i+1])-48)+(int(song[i+2])-48);
                        for (int j=0; j<digit; j++){
                            newSong+=toupper(song[i]);
                        }
                        i=i+2+digit;
                    }
                    else{
                        digit=int(song[i+1])-48;
                        for (int j=0; j<digit; j++){
                            newSong+=toupper(song[i]); //sustained notes are capitalized
                        }
                        i=i+1+digit;
                    }
                }
                else{
                    newSong+=tolower(song[i]); //normal notes are lower case
                    i++;
                }
            }
            
            else if(song[i]=='/'){
                newSong+='x';
                i++;
            }
        }
        return newSong;
    }
}
