#ifndef _HTTP_H_
#define _HTTP_H_

#include <string>
#include <map>
using namespace std;

class Http {
private:
    string line_;
    map<string, string> head_;
    string data_;
public:
    Http(string request);
    ~Http();
};

#endif