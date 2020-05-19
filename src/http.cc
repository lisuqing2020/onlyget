#include "http.h"
#include <cstring>
#include <iostream>

Http::Http(string request) {
    char* s = (char*)request.data();
    char* token = strtok(s, "\r\n");

    for(int i = 0; token != NULL; ++i) {
        string tmp = token;
        if(i == 0) {
            line_ = tmp;
        } else {
            string k, v;
            int p = tmp.find(": ", 0);
            if(p != -1) {
                k.assign(tmp.data(), p);
                v.assign(tmp, p+2, tmp.size()-p-2);
                head_.insert(make_pair(k, v));
            }
        }
        token = strtok(NULL, "\r\n");
        if(token == NULL) {
            data_ = tmp;
        }
    }
}

Http::~Http() {}