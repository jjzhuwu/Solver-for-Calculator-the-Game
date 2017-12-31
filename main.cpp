#include <iostream>
#include <string>
#include "Ctree.h"
using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}

int main(){

    cout << "Welcome to the solver." << endl;

    while (true){

    bool port;
    int portin = 0;
    int portout = 0;

    cout << "Input 1 for regular game, 2 for portal game, or 0 to exit" << endl;
    int res;
    cin >> res;

    if (res == 0) break;
    port = (res == 2);

    cout << endl << "What is your start?" << endl;
    int st;
    cin >> st;

    cout << endl <<"What is your goal?" << endl;
    int gl;
    cin >> gl;

    cout << endl << "# of operands?" << endl;
    int bd;
    cin >> bd;

    cout << endl << "Operands?" << endl;
    string s[bd];
    bool p_exist = false;
    int p_position;
    for (int i = 0; i < bd; i++){
            string temp;
            cin >> temp;
            if (is_number(temp)){
                temp = "i" + temp;
            }
            if (temp == "p"){
                p_exist = true;
                p_position = i;
            }
        s[i] = temp;
    }

    if (p_exist){
        s[p_position] = s[bd-1];
        s[bd-1] = "p";
    }

    cout << endl << "What is the maximum number of moves?" << endl;
    int mH;
    cin >> mH;

    if (port){

        cout << endl << "Where are the portal out and portal in?" << endl;
        cin >> portout;
        cin >> portin;

        if (portin >= portout){
            cout << "Impossible, please re-enter ." << endl;
            break;
        }
    }

    Ctree* game = new Ctree(st, gl, s, bd, mH, portout, portin);
    cout << endl << game->strategy() << endl;
    }
}
