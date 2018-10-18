#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "ArgumentManager.h"

using namespace std;

bool isOperand(char character) {
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') ||
        (character >= '0' && character <= '9')) {
        return true;
    } else
    {return false;}
};

template <class Type>
class stack
{
private:
    Type* arr;
    int top;
    int stackSize;
public:

    stack()
    {
        stackSize=100;
        arr=new Type[stackSize];
        top=0;



    }
    ~stack(){delete [] arr;}
    int priority(char c)
    {
        if (c=='^')
            return 3;
        else if (c=='*'||c=='/')
            return 2;
        else if(c=='+'||c=='-')
            return 1;
        else if(c==')'||'(')
            return 0;
        else
            return -1;
    }
    bool is_empty() const
    {
        return (top==0);
    }
    template<class elem>
    void push(elem a)
    {
        arr[top]=a;
        top++;
    }
    Type top_element()
    {
        return arr[top-1];

    }
    void pop()
    {
        top--;

    }
    bool matching(Type a, Type b)
    {
        return((a==')' && b=='(')||(a=='}'&&b=='{')||(a==']'&&b=='['));
    }
    string infix_to_postfix(string input_expression)
    {
        char topElement; // to store the top element here
        string output_string; // to return the postfix through this variable
        int i=0;

        while(input_expression[i]!='\0') //iterate through the expression until we reach the end
        {
            bool match=false; // we need this variable to push characters in case we failed to find a match

            // if the character is number, add it to the outpu_string
            if(isOperand(input_expression[i]))
            {
                output_string+=input_expression[i];
            }

            else
            {
                // if the stack is empty, dump the charter in
                if(is_empty())
                {
                    push(input_expression[i]);
                    topElement=top_element();
                }
                    // if the character is '(', dump it in the stack regardless
                else if(input_expression[i]=='(' ||input_expression[i]=='['||input_expression[i]=='{')
                {
                    push(input_expression[i]);
                    topElement=top_element();

                }
                else
                {
                    // checking the precedence of each character, keeping the least one at the bottom cells of the stack
                    while(priority(input_expression[i])<=priority(topElement))   // priority(top_element()))
                    {
                        // if the character is ')', we need to match it with the '(', and break
                        if(matching(input_expression[i], top_element()))
                        {
                            pop();
                            topElement=top_element();
                            match=true;
                            break;
                        }
                            // if the precedence of the character is lower that the top element, pop the top element, add it to the out_string,then update the top element
                        else
                        {
                            output_string+=top_element();
                            pop();
                            topElement=top_element();
                        }
                    }
                    // after exiting the while loop, we will push the character into the stack
                    if(match==false)
                    {
                        push(input_expression[i]);
                        topElement=top_element();
                    }
                }

            }
            i++;
        }
        // poping the rest of the stack, and add them to the output_string
        while(top>0)
        {
            output_string+=top_element();
            top--;
        }


        return output_string;
    }
};
bool balance(string line) {
    stack<char> infilestack;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '(' || line[i] == '{' || line[i] == '[') {
            infilestack.push(line[i]);
        }
        else if (line[i] == ')')
        {
            if (infilestack.top_element() != '(') {
                infilestack.pop();
                return false;
            } else infilestack.pop();

        }
        else if (line[i] == ']')
        {
            if (infilestack.top_element() != '[') {
                infilestack.pop();
                return false;
            }
            else infilestack.pop();

        }
        else if (line[i] == '}')
        {
            if (infilestack.top_element() != '{') {
                infilestack.pop();
                return false;
            }
            else infilestack.pop();
        }

    }
    if (infilestack.is_empty()){
        return true;
    }else{
        return false;
    }
};

string infix_to_postfix(string input_expression)
{
    stack<char>  Mystack;
    char topElement; // to store the top element here
    string output_string; // to return the postfix through this variable
    int i=0;

    while(input_expression[i]!='\0') //iterate through the expression until we reach the end
    {
        bool match=false; // we need this variable to push characters in case we failed to find a match

        // if the character is number, add it to the outpu_string
        if(isOperand(input_expression[i]))
        {
            output_string+=input_expression[i];
        }

        else
        {
            // if the stack is empty, dump the charter in
            if(Mystack.is_empty())
            {
                Mystack.push(input_expression[i]);
                topElement=Mystack.top_element();
            }
                // if the character is '(', dump it in the stack regardless
            else if(input_expression[i]=='(' ||input_expression[i]=='['||input_expression[i]=='{')
            {
                Mystack.push(input_expression[i]);
                topElement=Mystack.top_element();

            }
            else
            {
                // checking the precedence of each character, keeping the least one at the bottom cells of the stack
                while(Mystack.priority(input_expression[i])<=Mystack.priority(topElement))   // priority(top_element()))
                {
                    // if the character is ')', we need to match it with the '(', and break
                    if(Mystack.matching(input_expression[i], Mystack.top_element()))
                    {
                        Mystack.pop();
                        topElement=Mystack.top_element();
                        match=true;
                        break;
                    }
                        // if the precedence of the character is lower that the top element, pop the top element, add it to the out_string,then update the top element
                    else
                    {
                        output_string+=Mystack.top_element();
                        Mystack.pop();
                        topElement=Mystack.top_element();
                    }
                }
                // after exiting the while loop, we will push the character into the stack
                if(match==false)
                {
                    Mystack.push(input_expression[i]);
                    topElement=Mystack.top_element();
                }
            }

        }
        i++;
    }
    // poping the rest of the stack, and add them to the output_string
    while(!Mystack.is_empty())
    {
        output_string+=Mystack.top_element();
        Mystack.pop();
    }


    return output_string;
};


int postfix_evaluation(string input_expression)
{
    stack<int>  Mystack;
    int value;
    int topDigit;
    int lowerDigit;
    int digit;
    int i=0;
    while (input_expression[i]!='\0')
    {
        if (isOperand(input_expression[i]))
        {
            digit=input_expression[i]-'0';
            Mystack.push(digit);
        }
        else
        {
            topDigit=Mystack.top_element();
            Mystack.pop();
            lowerDigit=Mystack.top_element();
            Mystack.pop();
            switch (input_expression[i])
            {
                case '+':
                    value=lowerDigit+topDigit;
                    Mystack.push(value);
                    break;
                case '-':
                    value=lowerDigit-topDigit;
                    Mystack.push(value);
                    break;
            }
        }
        i++;
    }

    return value;
}
void addZero(string &line) {

    for (int i = 0; line[i]; i++) {
        {
            if (line[i] == '+' ||line[i] == '-'){
                if (i==0){
                    line.insert(0,"0");}
                if(line[i-1] == '('|| line[i-1] == '['|| line[i-1] == '{' ) {
                    line.insert(i,"0");}
            }
        }

    }
};
void build(const string &infilename) { // reads and stores from a txt file
    string line;
    int counter =0;
    ifstream myfile(infilename);
            if (!myfile.eof()) {
                while (myfile >> line) {
                    counter++;
                    if(balance(line)) {
                         addZero(line);
                        cout<< postfix_evaluation(infix_to_postfix(line)) << endl;

                    }
                    else if (!balance(line)){
                        cout <<"Didnt work at: "<< counter  << endl;
                    }
                }
    }

};


int main(int argc, char* argv[]) {

    stack<char> infix;
    ArgumentManager am(argc, argv);
    std::string expression;
    std::string infilename = am.get("input");
    std::string commandfilename = am.get("command");
    std::string outfilename = am.get("output");
    std::cout << "File name for input: " << infilename << std::endl
              << "File name for command: " << infilename << std::endl
              << "File name for output: " << outfilename << std::endl;
    build(infilename);

    return 0;
}





















































































































////#include <iostream>
////#include <stdio.h>
////#include <stdlib.h>
////#include <math.h>
////#include <cassert>
////#include <fstream>
////#include <string>
////#include <sstream>
////#include <iomanip>
////#include "ArgumentManager.h"
////
////using namespace std;
//////Worked on this stack infix with my group partners int the infix to postfix problem
////class MyStack
////{
////public:
////    MyStack(int MaxSize);
////    MyStack(const MyStack<Type> &OtherStack);
////    ~MyStack(void);
////
////    void        Push(const Type &Item); // Adds Item to the top
////    Type        Pop(void);              // Returns Item from the top
////
////private:
////    Type     *input;           // The  input array
////    int       top;    // The top number of elements
////    const int MAX_NUM;        // Maximum number of elements
////};
////
////
////// Stack Constructor function
////template <class Type>
////MyStack<Type>::MyStack(int) :
////        MAX_NUM( 100 )    // Initialize the constant
////{
////    input = new Type[MAX_NUM];
////    top = 0;
////}
////
////// Stack Destructor function
////template <class Type>
////MyStack<Type>::~MyStack(void)
////{
////    delete[] input;
////}
////
////// Push() function
////template <class Type>
////void MyStack<Type>::Push(const Type &Item)
////{
////
////    assert(top < MAX_NUM);
////
////    input[top++] = Item;
////}
////
////// Pop() function
////template <class Type>
////Type MyStack<Type>::Pop(void)
////{
////
////    assert(top > 0);
////
////    return input[--top];
////}
////bool realOperand(char character);
////bool realOperator(char character);
////bool realOperand(char character){
////    if( character >= '0' && character <='9' || character >= 'A' && character <='Z'||character >= 'a' && character <='z'){
////        return true;
////    }
////    return false;
////}
////bool  realOperator(char character){
////    if( character == '*' && character =='+' || character >= '/' && character <='^'){
////        return true;
////    }
////    return false;
////}
////
////
////template <class Type>
////Type MyStack<Type>::int priority(char c)
////    {
////        if (c=='^')
////            return 3;
////        else if (c=='*'||c=='/')
////            return 2;
////        else if(c=='+'||c=='-')
////            return 1;
////        else if(c==')'||'(')
////            return 0;
////        else
////            return -1;
////    }
////    bool is_empty() const
////    {
////        return (top==0);
////    }
////    template<class elem>
////    void push(elem a)
////    {
////        arr[top]=a;
////        top++;
////    }
////    Type top_element()
////    {
////        return arr[top-1];
////
////    }
////    void pop()
////    {
////        top--;
////
////    }
////    bool matching(Type a, Type b)
////    {
////        return((a==')' && b=='(')||(a=='{'&&b=='}')||(a=='['&&b==']'));
////    }
////    string infix_to_postfix(string input_expression)
////    {
////        char topElement; // to store the top element here
////        string output_string; // to return the postfix through this variable
////        int i=0;
////
////        while(input_expression[i]!='\0') //iterate through the expression until we reach the end
////        {
////            bool match=false; // we need this variable to push characters in case we failed to find a match
////
////            // if the character is number, add it to the outpu_string
////            if(isdigit(input_expression[i]))
////            {
////                output_string+=input_expression[i];
////            }
////
////            else
////            {
////                // if the MyStack is empty, dump the charter in
////                if(is_empty())
////                {
////                    push(input_expression[i]);
////                    topElement=top_element();
////                }
////                    // if the character is '(', dump it in the MyStack regardless
////                else if(input_expression[i]=='(')
////                {
////                    push(input_expression[i]);
////                    topElement=top_element();
////
////                }
////                else
////                {
////                    // checking the precedence of each character, keeping the least one at the bottom cells of the MyStack
////                    while(priority(input_expression[i])<=priority(topElement))   // priority(top_element()))
////                    {
////                        // if the character is ')', we need to match it with the '(', and break
////                        if(matching(input_expression[i], top_element()))
////                        {
////                            pop();
////                            topElement=top_element();
////                            match=true;
////                            break;
////                        }
////                            // if the precedence of the character is lower that the top element, pop the top element, add it to the out_string,then update the top element
////                        else
////                        {
////                            output_string+=top_element();
////                            pop();
////                            topElement=top_element();
////                        }
////                    }
////                    // after exiting the while loop, we will push the character into the MyStack
////                    if(match==false)
////                    {
////                        push(input_expression[i]);
////                        topElement=top_element();
////                    }
////                }
////
////            }
////            i++;
////        }
////        // poping the rest of the MyStack, and add them to the output_string
////        while(top>0)
////        {
////            output_string+=top_element();
////            top--;
////        }
////
////
////        return output_string;
////    }
////    string postfix_to_infix(string input_expression)
////    {
////        string topElement;
////        string lowerElement;
////        string stackElement;
////        string output_expression;
////        int i=0;
////        while(input_expression[i]!='\0')
////        {
////            if(isspace(input_expression[i]))
////            {
////                push(input_expression[i]);
////
////            }
////            else
////            {
////                topElement=top_element();
////                pop();
////                lowerElement=top_element();
////                stackElement="("+lowerElement+input_expression[i]+topElement+")";
////                push(stackElement);
////            }
////            i++;
////
////
////        }
////        output_expression=top_element();
////
////        return output_expression;
////    }
////    int postfix_evaluation(string input_expression)
////    {
////        int value;
////        int topDigit;
////        int lowerDigit;
////        int digit;
////        int i=0;
////        while (input_expression[i]!='\0')
////        {
////            if (isdigit(input_expression[i]))
////            {
////                digit=input_expression[i]-'0';
////                push(digit);
////            }
////            else
////            {
////                topDigit=top_element();
////                pop();
////                lowerDigit=top_element();
////                pop();
////                switch (input_expression[i])
////                {
////                    case '+':
////                        value=lowerDigit+topDigit;
////                        push(value);
////                        break;
////                    case '-':
////                        value=lowerDigit-topDigit;
////                        push(value);
////                        break;
////                    case '*':
////                        value=lowerDigit*topDigit;
////                        push(value);
////                        break;
////                    case '/':
////                        value=lowerDigit/topDigit;
////                        push(value);
////                        break;
////                    case'^':
////                        value=pow(lowerDigit,topDigit);
////                        push(value);
////                        break;
////                }
////            }
////            i++;
////        }
////
////        return value;
////    }
////
////    void build(const string &infilename) { // reads and stores from a txt file
////        string line;
////        std::string position;
////        ifstream myfile(infilename);
////        if (myfile.good()) {
////            while (getline(myfile, line)){
////
////                if (line.empty())
////                {
////                    continue;
////                }
////                else{
////
////                }
////            }
////        }
////    }
////};
////
////
////int main(int argc, char* argv[]) {
////    MyStack<char> infix;
////    ArgumentManager am(argc, argv);
////    std::string expression;
////    std::string infilename = am.get("input");
////    std::string commandfilename = am.get("command");
////    std::string outfilename = am.get("output");
////    std::cout << "File name for input: " << infilename << std::endl
////              << "File name for command: " << infilename << std::endl
////              << "File name for output: " << outfilename << std::endl;
////    cout << "Please give an expression: ";
////    getline(cin, expression);
////    cout<<infix.infix_to_postfix(expression)<<endl;
////
////    return 0;
////}
////
////
//
//
//
//
//#include "ArgumentManager.h"
//#include <iostream>
//#include <string>
//#include <assert.h>
//using namespace std;
//
//#define MaxSize = 100
//int arr[100];
//
//template <class Type>
//class MyStack
//{
//public:
//    MyStack(int MaxSize);
//    MyStack(const MyStack<Type> &OtherStack);
//    ~MyStack(void);
//    void        Push(const Type &Item); // Adds Item to the top
//    Type        Pop(void);// Returns Item from the top
//    bool matching(const Type &Item,const Type &sItem);
//    bool isEmptyStack() const;          //Checks if its empty
//    bool isFullStack() const;           //checks if its full
//    bool realOperand(char &i) const;           //checks if the operands are real
//    std::string infix_to_postfix(string input_expression);
//    int priority(char c)
//    {
//        if (c=='^')
//            return 3;
//        else if (c=='*'||c=='/')
//            return 2;
//        else if(c=='+'||c=='-')
//            return 1;
//        else if(c==')'||'(')
//            return 0;
//        else
//            return -1;
//    }
//
//    char top_element() {
//
//        // assert(top!=0);
//
//        return arr[top - 1];
//
//    }
//private:
//    Type     *input;           // The  input array
//    int       top;    // The top number of elements
//    const int MAX_NUM;        // Maximum number of elements
//};
//// Stack Constructor function
//template <class Type>
//MyStack<Type>::MyStack(int) :
//        MAX_NUM( 100 )    // Initialize the constant
//{
//    input = new Type[MAX_NUM];
//    top = 0;
//}
//// Stack Destructor function
//template <class Type>
//MyStack<Type>::~MyStack(void)
//{
//    delete[] input;
//}
//// Push() function
//template <class Type>
//void MyStack<Type>::Push(const Type &Item)
//{
//    assert(top < MAX_NUM);
//    input[top++] = Item;
//}
//// Pop() function
//template <class Type>
//Type MyStack<Type>::Pop(void)
//{
//    assert(top > 0);
//    return input[--top];
//}
//template <class Type>
//bool MyStack<Type>::isEmptyStack() const {
//    {
//        return(top == 0);
//    }//end isEmptyStack
//
//}
//template <class Type>
//bool MyStack<Type>::isFullStack() const {
//    {
//        return(top == MAX_NUM);
//    }//end isEmptyStack
//
//}
//bool isOperand(char character) {
//    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') ||
//        (character >= '0' && character <= '9')) {
//        return true;
//    }
//}
//
//
//bool IsOperator(char character)
//    {
//        if(character == '+' || character == '-' || character == '*' || character == '/' || character== '$')
//            return true;
//
//    }
//template <class Type>
//bool matching(char a, char b);
//
////template<class Type>
////bool matching(string expression) {
////    string chekline;
////    for(string i = 0; i<chekline; i++)
////
////}
//
//
//template <class Type>
//string MyStack<Type>::infix_to_postfix(string input_expression)
//{
//    char topElement; // to store the top element here
//    string output_string; // to return the postfix through this variable
//    int i=0;
//
//    while(input_expression[i]!='\0') //iterate through the expression until we reach the end
//    {
//        bool match=false; // we need this variable to push characters in case we failed to find a match
//
//        // if the character is number, add it to the outpu_string
//        if(isdigit(input_expression[i]))
//        {
//            output_string+=input_expression[i];
//        }
//
//        else
//        {
//            // if the stack is empty, dump the charter in
//            if(isEmptyStack())
//            {
//                Push(input_expression[i]);
//                topElement=top_element();
//            }
//                // if the character is '(', dump it in the stack regardless
//            else if(input_expression[i]=='(')
//            {
//                Push(input_expression[i]);
//                topElement=top_element();
//
//            }
//            else
//            {
//                // checking the precedence of each character, keeping the least one at the bottom cells of the stack
//                while(priority(input_expression[i])<=priority(topElement))   // priority(top_element()))
//                {
//                    // if the character is ')', we need to match it with the '(', and break
//                    if(matching(input_expression[i], top_element()))
//                    {
//                        Pop();
//                        topElement=top_element();
//                        match=true;
//                        break;
//                    }
//                        // if the precedence of the character is lower that the top element, pop the top element, add it to the out_string,then update the top element
//                    else
//                    {
//                        output_string+=top_element();
//                        Pop();
//                        topElement=top_element();
//                    }
//                }
//                // after exiting the while loop, we will push the character into the stack
//                if(match==false)
//                {
//                    Push(input_expression[i]);
//                    topElement=top_element();
//                }
//            }
//
//        }
//        i++;
//    }
//    // poping the rest of the stack, and add them to the output_string
//    while(top>0)
//    {
//        output_string+=top_element();
//        top--;
//    }
//
//
//    return output_string;
//}
//int main(int argc, char* argv[]) {
//    MyStack<char> infix;
//    ArgumentManager am(argc, argv);
//    std::string expression;
//    std::string infilename = am.get("input");
//    std::string commandfilename = am.get("command");
//    std::string outfilename = am.get("output");
//    std::cout << "File name for input: " << infilename << std::endl
//              << "File name for command: " << infilename << std::endl
//              << "File name for output: " << outfilename << std::endl;
//    cout << "Please give an expression: ";
//    getline(cin, expression);
//    cout << infix.infix_to_postfix(expression) << endl;
//
//    return 0;
//}
//
//string postfix_to_infix(string input_expression)
//{
//    string topElement;
//    string lowerElement;
//    string stackElement;
//    string output_expression;
//    int i=0;
//    while(input_expression[i]!='\0')
//    {
//        if(isspace(input_expression[i]))
//        {
//            push(input_expression[i]);
//
//        }
//        else
//        {
//            topElement=top_element();
//            pop();
//            lowerElement=top_element();
//            stackElement="("+lowerElement+input_expression[i]+topElement+")";
//            push(stackElement);
//        }
//        i++;
//
//
//    }
//    output_expression=top_element();
//
//    return output_expression;
//}
//int postfix_evaluation(string input_expression)
//{
//    int value;
//    int topDigit;
//    int lowerDigit;
//    int digit;
//    int i=0;
//    while (input_expression[i]!='\0')
//    {
//        if (isdigit(input_expression[i]))
//        {
//            digit=input_expression[i]-'0';
//            push(digit);
//        }
//        else
//        {
//            topDigit=top_element();
//            pop();
//            lowerDigit=top_element();
//            pop();
//            switch (input_expression[i])
//            {
//                case '+':
//                    value=lowerDigit+topDigit;
//                    push(value);
//                    break;
//                case '-':
//                    value=lowerDigit-topDigit;
//                    push(value);
//                    break;
//                case '*':
//                    value=lowerDigit*topDigit;
//                    push(value);
//                    break;
//                case '/':
//                    value=lowerDigit/topDigit;
//                    push(value);
//                    break;
//                case'^':
//                    value=pow(lowerDigit,topDigit);
//                    push(value);
//                    break;
//            }
//        }
//        i++;
//    }
//
//    return value;
//}