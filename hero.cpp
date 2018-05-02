#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool hasCorrectSyntax(string song);
bool isTranslatable(string song);
bool isColor(char c);
string translation(string song);
int numBeat(string song);
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
    }
    else if (hasCorrectSyntax(mySong)){
        cout <<"The bad beat is the "<<badBeat<<"th "<<endl;
    }
    else{
        cout <<"Incorrect Syntax"<<endl;
    }
}

bool hasCorrectSyntax(string song){
    bool correctness=false;
    if (!isColor(song[0]) && song[0]!='/'){
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
            if (song[i+1]=='/'){
                correctness=true;
            }
            else if (song[i+1]=='/' && !isdigit(song[i+2]) && i!=song.size()-2){
                correctness=true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    correctness=(song[song.size()-1]=='/');
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
                    digit=10*(int(song[i])-48)+(int(song[i+1])-48);
                    if(digit<2){
                        return false;
                    }
                    
                    for(int j=1;j<digit;j++){
                        if(i+1+digit>song.size()-1 || song[j+i]!='/'){
                            return false;
                        }
                    }
                    
                }
                else{
                    digit=int(song[i])-48;
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
    if (c=='G' || c=='g' || c=='R' || c=='r' || c=='Y'|| c=='y' || c=='B' || c=='b' || c=='O' || c=='o'){
        return true;
    }
    return false;
}

int numBeat(string song){
    int count = 0;
    for (int i=0;i<song.size();i++){
        if(song[i]=='/'){
            count++;
        }
    }
    return count;
}

int translateSong(string song, string& instructions, int& badBeat){
    if(isTranslatable(song)){
        instructions=translation(song);
        return 0;
    }
    
    if(! hasCorrectSyntax(song)){
        //ONLY FOR TESTING!!!
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
                    
                else if(i+1+digit<=song.size()-1) {
                    for(int j=1;j<digit;j++){
                        if(song[j+i]!='/'){
                            badBeat=j+i;
                            return 3;
                        }
                    }
                }
                    
                else if(i+1+digit>song.size()-1){
                    badBeat=int(song.size())+1;
                    return 4;
                }
                    
            }
            digit=song[i]-48;
            if(digit<2){
                badBeat=numBeat(song.substr(0,i+1))+1;
                return 2;
            }
            else if(i+digit<=song.size()-1) {
                for(int j=1;j<digit;j++){
                    if(song[j+i]!='/'){
                        badBeat=j+i;
                        return 3;
                    }
                }
            }
            else if(i+1+digit>song.size()-1){
                badBeat=int(song.size())+1;
                return 4;
            }
        }
    }
    return 0;
}

string translation(string song){ //since we use this function only when song is translatable, we don't need to worry about the erraneous situations
    int digit;
    string newSong = "";
    if (song==""){
        return song;
    }
    
    else{
        int i=0;
        while(i<song.size()){
            if (isColor(song[i])){
                if(isdigit(song[i+1])){
                    if(isdigit(song[i+2])){
                        digit=10*(int(song[i+1])-48)+(int(song[i+2])-48);
                        for (int j=0; j<digit; j++){
                            newSong+=toupper(song[i]);
                        }
                        i=i+2+digit+1;
                    }
                    else{
                        digit=int(song[i+1])-48;
                        for (int j=0; j<digit; j++){
                            newSong+=toupper(song[i]);
                        }
                        i=i+1+digit+1;
                        }
                    }
                    newSong+=tolower(song[i]);
                    i+=2;
            }
            
            else if(song[i]=='/'){
                newSong+='x';
                i++;
            }
        }
        return newSong;
    }
}
