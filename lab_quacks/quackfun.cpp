/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    T result;
    if(s.empty()){
        return 0;
    }else{
        T a = s.top();
        s.pop();
        result  = a + sum(s);
        s.push(a);
    }

    // Your code here
    return result; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * You are allowed only the use of one stack in this function, and no other local variables.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    stack<char> s;
    while(!input.empty()){
        if(input.front()==']'){
            if(!s.empty()){
              s.pop();
            }else{
              return false;
            }
        }else if(input.front()=='['){
            s.push(input.front());
        }
        input.pop();
    }
    if(!s.empty()){
      return false;
    }
    return true;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> que;
    unsigned long i= 1;
    unsigned long sum = 1;
    unsigned long size = q.size();
    while(sum-i<size){
        //cout<<"i "<<i<<"  sum"<<sum<<endl;
        if(i%2 == 1){
            for(unsigned long j = 0;j<i;j++){
                if(q.empty()){
                    break;
                }
                T a = q.front();
                //cout<<"j "<<j<<"  a"<<a<<endl;
                que.push(a);
                q.pop();
            }
        }else{
            for(unsigned long k = 0;k<i;k++){
                if(q.empty()){
                    break;
                }
                T b = q.front();
                //cout<<"k1 "<<k<<"  b"<<b<<endl;
                s.push(b);
                q.pop();
            }
            for(unsigned long k = 0;k<i;k++){
                if(s.empty()){
                    break;
                }
                T c = s.top();
                //cout<<"k2 "<<k<<"  c"<<c<<endl;
                que.push(c);
                s.pop();
            }
        }
        i++;
        sum+= i;
    }
    q.swap(que);
    // optional: queue<T> q2;

    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    if(s.size() == 0){
        return true;// base case, if stack size is zero, return true
    }
    T a = s.top();// store stack top
    T b;
    s.pop();//pop
    if(verifySame(s,q)){
        if(a == q.front()){  //check current stack top and queue front
            retval = true;
        }else{
            retval = false;
        }
    }else{
        retval = false; // not equal
    }
    b = q.front();
    q.pop();
    q.push(b); // dequeue front and attach it on the back
    s.push(a); // push stack top back
    return retval;

    // T temp1; // rename me
    // T temp2; // rename :)

    // Your code here

    return retval;
}

}
