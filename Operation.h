#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Operation
{
    public:
        char opr;
        string number;
        string number2;

        Operation(char c, string num);
        Operation(string str);
        Operation(const Operation &other);
        Operation& operator=(const Operation &other);
        ~Operation();
        void add(int i);

        string int2St(int i){
        stringstream ss;
        ss << i;
        return ss.str();
    }

    int st2int(string s){
        stringstream ss(s);
        int result = 0;
        ss >> result;
        return result;
    }

};

#endif // OPERATION_H
