#include "Ctree.h"

Ctree::Ctree(int start, int g, string op[], int bound, int mH, int po, int pi){

  //  cout << checkinsertinRange(100,100) << " Line 5 " << endl;
    root = new Node(start, bound, 0);
    goal = g;

    for (int i= 0; i < 6; i++){
            if (i < bound){
                root->ops[i] = new Operation(op[i]);
            } else {
                root->ops[i] = NULL;
            }
    }

    maxHeight = mH;
    portout = po-1;
    portin = pi-1;
}

Ctree::~Ctree(){

    NodeDelete(root);
    }

void Ctree::NodeDelete(Node *ptr){

    if (ptr){
        for (int i = 0; i < ptr->size; i++){
            NodeDelete(ptr->ptrs[i]);
        }
        delete ptr;

        for (int j = 0; j < 6; j++){
            if (ptr->ops[j]){
                delete ptr->ops[j];
            }
        }
    }
}

Ctree::Node* Ctree::apply(Node *ptr, Operation *o){
    int base = ptr->data;
    char op = o->opr;
    int operand = st2int(o->number);
    int newHeight = ptr->height+1;
    int newsize = ptr->size;

    int result;
    Operation *newop[6];
    for (int i = 0; i < 6; i++){
            if (ptr->ops[i]){
            newop[i] = new Operation(*(ptr->ops[i]));
            } else {
                newop[i] = NULL;
            }
    }
    if (op == '+'){
        result = base + operand;
    } else if (op == '-'){
        result = base - operand;
    } else if (op == '*'){
        result = base * operand;
    } else if (op == '/'){
        if (base % operand == 0){
            result = base / operand;
        } else {
            return NULL;
        }
    } else if (op == 'i'){
        if (checkinsertinRange(base, operand)){
            if (base >= 0){
                result = base * sizeofinsert(operand) + operand;
            } else {
                result = base * sizeofinsert(operand) - operand;
            }
        } else {
            return NULL;
        }
    } else if (op == 'd'){
        result = base / 10;
    } else if (op == 'c'){
        result = convert(base, o->number, o->number2);
        if (result == base){
            return NULL;
        }
    } else if (op == '^'){
        double result1 = pow(base, operand);
        result = (int) result1;
    } else if (op == 'n'){
        result = 0 - base;
    } else if (op == 'r'){
        bool neg = (base < 0);
        if (neg){
            base = 0 - base;
        }
        string temp = int2St(base);
        reverse(temp.begin(), temp.end());
        result = st2int(temp);
        if (neg){
            result = 0 - result;
        }
    } else if (op == 's'){
        result = sumofDigits(base);
    } else if (op == '<'){
        result = shiftleft(base);
    } else if (op == '>') {
        result = shiftright(base);
    } else if (op == 'm'){
        bool neg = (base < 0);
        if (neg){
            base = 0-base;
        }
        string temp = int2St(base);
        if (temp.length() <= 3){
            string temp1 = temp;
            reverse(temp1.begin(), temp1.end());
            result = st2int(temp+temp1);
            if (neg){
                result = 0 - result;
            }
        } else {
            return NULL;
        }
    } else if (op == '['){
            for (int j = 0; j < ptr->size; j++){
                    newop[j]->add(operand);
            }
            result = base;
    } else if (op == 'p'){
        Operation *q = ofind(newop, 'q');
        newHeight = newHeight - 1;
        if (q){
            if (base == st2int(q->number)){
                return NULL;
            } else {
                q->number = int2St(base);
            }
        } else {
            newop[newsize] = new Operation('q', int2St(base));
            newsize++;
        }
        result = base;
    } else if (op == 'q') {
        if (checkinsertinRange(base, operand)){
            if (base >= 0){
                result = base * sizeofinsert(operand) + operand;
            } else {
                result = base * sizeofinsert(operand) - operand;
            }
        } else {
        return NULL;
        }
    } else if (op == 'v'){
        result = inversion10(base);
    }else {
        cout << "Not supported " << op << endl;
        throw new exception();
    }

    result = portprocessing(result);
    Node *ret = new Node(result, newsize, newHeight);
    for (int k = 0; k < 6; k++){
        ret->ops[k] = newop[k];
    }
    return ret;
}

string Ctree::strategy(){
 //   cout << "Line 59 " << root->data << endl;
    return strategy(root);
}

string Ctree::strategy(Node *ptr){

    if (ptr){
    stringstream ss;
    int cHeight = ptr->height;

    if (cHeight <= maxHeight){

        int b = ptr->data;
        if (b == goal){
            return "Success";
        } else {
            for (int i = 0; i < ptr->size; i++){
                ptr->ptrs[i] = apply(ptr, ptr->ops[i]);
                string result = strategy(ptr->ptrs[i]);
            if (result != ""){
                ss << ptr->ops[i]->opr << " " << ptr->ops[i]->number << " " << ptr->ops[i]->number2 <<" " << result << " ";
                return ss.str();
            }
            }
        }
    }
    }
    return "";
}

int Ctree::sizeofinsert(int num){

    stringstream ss;
    ss << num;
    double ret = pow(10, ss.str().length());

    return (int) ret;
}

int Ctree::convert(int b, string so, string st){

    string sb = int2St(b);

    size_t nPos = sb.find(so, 0); // fist occurrence
    while(nPos != string::npos)
    {
        sb = sb.substr(0, nPos) + st + sb.substr(nPos+so.length());
        nPos = sb.find(so, nPos+st.length());
    }

    return st2int(sb);

}

int Ctree::inversion10(int b){
    if (b == 0){
        return 0;
    } else if (b % 10 == 0){
        return 10*inversion10(b/10);
    } else {
        return 10 - (b % 10) + 10 * inversion10(b/10);
    }
}

int Ctree::portprocessing(int r){
    if (portout == -1)
        return r;
    double t1 = pow(10, portout);
    int t = (int) t1;

    if (r < t){
        return r;
    } else {
        int r_end = r % t;
        int r_mid = (r / t) % 10;
        int r_begin = (r / (t * 10));
        return portprocessing(r_end + r_mid*pow(10,portin) + r_begin * t);
    }
}
