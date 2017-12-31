#include "Operation.h"

Operation::Operation(char c, string num){
    opr = c;
    number = num;
    number2 = "";
}

Operation::Operation(string str)
{
    opr = str.at(0);
    std::size_t found = str.find('_');
    if (found!=std::string::npos){
     number = str.substr(1, found-1);
     number2 = str.substr(found+1);
    } else {
        number = str.substr(1).c_str();
        number2 = "";
    }
   // cout << opr << " " << number << endl;
}

Operation::~Operation()
{
    //dtor
}

Operation::Operation(const Operation &other){
    opr = other.opr;
    number = other.number;
    number2 = other.number2;

}

Operation& Operation::operator=(const Operation &other){

    if (this != &other){
        opr = other.opr;
        number = other.number;
        number2 = other.number2;
    }
    return *this;
}

void Operation::add(int i){

    if (opr != '['){
        number = int2St(st2int(number)+i);
        number2 = int2St(st2int(number2)+i);
    }
}
