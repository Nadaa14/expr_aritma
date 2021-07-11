#include <bits/stdc++.h>
using namespace std;

long unsigned int i;

bool isOp(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%')
        return true;
    return false;
}
int precedence(char c){
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/'||c=='%') return 2;
    return 0;
}
double applyOp(double num1, double num2, char op){
    switch(op){
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
    }
    return 0;
}
void calculate(string input){
    stack<double> data;
    stack<char>operasi;
    
    for(i=0; i<input.length(); i++){
        if(isdigit(input[i])){
            int value=0;
            while(i<input.length() && isdigit(input[i])){
                value = (value*10) + (input[i] - '0');
                i++;
            }
            i--;
            data.push(value);
        }
        else if(input[i] == '(')
            operasi.push(input[i]);
        else if(input[i] == ')'){
            while(!operasi.empty() && operasi.top() != '('){
                if(operasi.top() == '%'){
                    int value2 = data.top(); data.pop();
                    int value1 = data.top(); data.pop();
                    operasi.pop();
                    data.push(value1%value2);
                } else {
                    double value2 = data.top(); data.pop();
                    double value1 = data.top(); data.pop();
                    char op = operasi.top(); operasi.pop();
                    data.push(applyOp(value1, value2, op));
                }
            }
            if(!operasi.empty())
                operasi.pop();
        } else {
            if(input[i] == '-'){
                if(i==0){
                    if(isdigit(input[i+1])){
                        i++;
                        int value=0;
                        while(i<input.length() && isdigit(input[i])){
                            value = (value*10) + (input[i] - '0');
                            i++;
                        }
                        i--;
                        data.push(value*-1);
                    } else {
                        data.push(-1);
                        operasi.push('*');
                    }
                } else {
                    while(!operasi.empty() && precedence(operasi.top()) >= precedence(input[i]) && !isOp(input[i-1])){
                        if(operasi.top() == '%'){
                            int value2 = data.top(); data.pop();
                            int value1 = data.top(); data.pop();
                            operasi.pop();
                            data.push(value1%value2);
                        } else {
                            double value2 = data.top(); data.pop();
                            double value1 = data.top(); data.pop();
                            char op = operasi.top(); operasi.pop();
                            data.push(applyOp(value1, value2, op));
                        }
                    }
                    if((isdigit(input[i+1]) || input[i+1]=='(') && (isdigit(input[i-1]) || input[i-1]==')'))
                        operasi.push(input[i]);
                    else{
                        data.push(-1);
                        operasi.push('*');
                    }
                } 
            } else {
                while(!operasi.empty() && precedence(operasi.top()) >= precedence(input[i])){
                    if(operasi.top() == '%'){
                        int value2 = data.top(); data.pop();
                        int value1 = data.top(); data.pop();
                        operasi.pop();
                        data.push(value1%value2);
                    } else {
                        double value2 = data.top(); data.pop();
                        double value1 = data.top(); data.pop();
                        char op = operasi.top(); operasi.pop();
                        data.push(applyOp(value1, value2, op));
                    }
                }
                operasi.push(input[i]);
            }
        }
    }
    while(!operasi.empty()){
        if(operasi.top() == '%'){
            int value2 = data.top(); data.pop();
            int value1 = data.top(); data.pop();
            operasi.pop();
            data.push(value1%value2);
        } else {
            double value2 = data.top(); data.pop();
            double value1 = data.top(); data.pop();
            char op = operasi.top(); operasi.pop();
            data.push(applyOp(value1, value2, op));
        }
    }
    cout << data.top() << endl;
}

int main(){
    string ekspresi; getline(cin, ekspresi);
    string temp="";
    
    for(i=0; i<ekspresi.length(); i++){
        if(ekspresi[i]==' ')
            continue;
        else
            temp+=ekspresi[i];
    }
    calculate(temp);
        
    return 0;
}
