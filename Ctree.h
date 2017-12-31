#ifndef CTREE_H_INCLUDED
#define CTREE_H_INCLUDED

#include "Operation.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <array>
#include <math.h>

using namespace std;

class Ctree {

public:
    Ctree(int start, int g, string op[], int bound, int mH, int po, int pi);

    ~Ctree();

    string strategy();

private:
    struct Node{
        int data;
        int size;
        int height;
        Node* ptrs[6];
        Operation *ops[6];

        Node(int i, int s, int h){
        data = i;
        size = s;
        height = h;
        }
    };


    Node *root;
    int goal;
    int maxHeight;
    int portout;
    int portin;

    void NodeDelete(Node *ptr);

    Node* apply(Node *ptr, Operation *o);

    string strategy(Node *ptr);

    int sizeofinsert(int num);

    int convert(int b, string so, string st);

    int inversion10(int b);

    int portprocessing(int r);

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

    int sumofDigits(int i){
        if (i == 0){
            return 0;
        } else {
            return (i % 10) + sumofDigits(i /10);
        }
    }

    int shiftleft(int i){
        string num = int2St(i);
        if (num.length()>1){
            char first = num.at(0);
            num = num.substr(1) + first;
        }
        return st2int(num);
    }

    int shiftright(int i){
        string num = int2St(i);
        if (num.length()>1){
            char last= num.at(num.length()-1);
            num = last + num.substr(0, num.length()-1);
        }
        return st2int(num);
    }

    Operation* ofind(Operation *p[], char c){
        for (int i = 0; i < 6; i++){
            if (p[i]){
                if (p[i]->opr == c){
                    return p[i];
                }
            }
        }
        return NULL;
    }

    bool checkinsertinRange(int a, int b){
        stringstream ss;
        ss << a << b;
        return (int2St(st2int(ss.str())).length() <=6);
    }
};

#endif // CTREE_H_INCLUDED
