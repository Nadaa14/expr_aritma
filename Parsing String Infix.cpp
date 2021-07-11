#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void Split(string _input){
    vector<char> splt;
    string hasil;

    char angka[] = "0123456789";
	char kurung[] = "()";
    char simbol[] = "+-/%*";
    char chr[1];
    
    for(auto charInput : _input){
        chr[0] = charInput;

        if(strspn(chr, simbol) || strspn(chr, angka) || strspn(chr, kurung)){
            splt.push_back(charInput);
        }
    }
    
    for (int i = 0; i != splt.size(); i++){    
        chr[0] = splt[i];

        if((strspn(chr, simbol) || splt[i] == ')') && splt[i] != '(' && i > 0){
            hasil += " ";
        }
        
        if(strspn(chr, angka)){
            hasil += splt[i];
        }else{
            hasil += splt[i];

            if(i > 0){
                chr[0] = splt[i - 1];

                if(splt[i] != '(' && strspn(chr, simbol)){
                    hasil += "1 * ";
                }else if(splt[i] != ')'){
                    chr[0] = splt[i + 1];

                    if(!strspn(chr, simbol)){
                        hasil += " ";
                    }
                }
            }else if(splt[i + 1] == '('){
                hasil += "1 * ";                
            }
        }
    }

    cout << hasil << endl;
}

int main(){
    string input;
    getline(cin, input);
    Split(input);
    
    return 0;
}