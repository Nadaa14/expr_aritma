#include <bits/stdc++.h>
using namespace std;

bool oibreoir(char r){
    if(r == '+' || 
       r == '-' || 
       r == '*' || 
       r == '/' || 
       r == '%'   ){
        return true;
    }
    else{
        return false;
    }
}

int prioritet(string r){
    if(r == "+" ||
       r == "-"   ){
        return 1;
    }
    else if(r == "*" ||
            r == "/" ||
            r == "%"   ){
        return 2;
    }
    return 0;
}

bool grande(string r, string s){
    int Nilai1, Nilai2;
    Nilai1 = prioritet(r); Nilai2 = prioritet(s);
    
    return Nilai1 <= Nilai2;
}

vector <string> infix; vector <string> postfix; string temp; vector <string>::iterator remake; vector <string>::iterator itu;

void MasukkanData(){
    string khayt;
    char harf;
    
    while(cin.get(harf)){
        if(harf == '\n'){
            break;
        }
        if(harf != ' '){
            khayt.push_back(harf);
        }
    }
    int length = khayt.length();

    for(int i = 0; i < length; i++){
        if(khayt[i] == '(' ||
           khayt[i] == ')'){
            if(temp.length() != 0){
                infix.push_back(temp);
                temp.clear();
            }
            infix.push_back(khayt.substr(i, 1));
        }
        if(isdigit(khayt[i]) ||
           (khayt[i] == '-' &&
            i == 0 &&
            isdigit(khayt[i+1]))){
            
            temp.push_back(khayt[i]);
            continue;
        }
        if(oibreoir(khayt[i])){
            if(temp.length() != 0){
                
                infix.push_back(temp);
                temp.clear();
            }
            if((khayt[i] == '-' &&
                oibreoir(khayt[i-1])) ||
               (khayt[i] == '-' &&
                i == 0 && khayt[i+1] == '(') ||
               (khayt[i] == '-' &&
                khayt[i-1] == '(')){
                
                infix.push_back("-1");
                infix.push_back("*");
            }else{
                infix.push_back(khayt.substr(i, 1));
            }
        }
    }
    if(temp.length() != 0){
        infix.push_back(temp);
        temp.clear();
    }
}

void InfixtoPostfix(){
    stack <string> temp2;
    int i = 0;
    for(remake = infix.begin(); remake != infix.end() ; remake++, i++){
        if(isdigit(infix[i].back())){
            postfix.push_back(infix[i]);
            continue;
        }
        if(infix[i] == "("){
            
            temp2.push(infix[i]);
            continue;
        }
        if(infix[i] == ")"){
            while(!temp2.empty() &&
                  (temp2.top() != "(")){
                
                string toPush = temp2.top();
                postfix.push_back(toPush);
                temp2.pop();
            }
            temp2.pop();
            continue;
        }
        if(oibreoir(infix[i][0])){
            if(temp2.empty() ||
               temp2.top() == "("){
               temp2.push(infix[i]);
            }
            else{
                while(!temp2.empty() &&
                     (temp2.top() != "(") &&
                      grande(infix[i], temp2.top())){
                    
                    string toPush = temp2.top();
                    postfix.push_back(toPush);
                    temp2.pop();
                }
                temp2.push(infix[i] );
            }
            continue;
        }
    }
    while(!temp2.empty()){
        string toPush = temp2.top();
        postfix.push_back(toPush);
        temp2.pop();
    }
}

int main(){
    MasukkanData();
    InfixtoPostfix();
    for(itu = postfix.begin(); itu != postfix.end() ; itu++){
        cout << *itu << " ";
    }
}
