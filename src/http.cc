#include "http.h"
#include <cstring>
#include <sys/stat.h>
#include <iostream>

Http::Http(string request) {
    char* s = (char*)request.data();
    char* token = strtok(s, "\r\n");

    for(int i = 0; token != NULL; ++i) {
        string tmp = token;
        if(i == 0) {   
            LineParse(tmp); // 获取请求行
        } else {    
            HeadParse(tmp); // 获取请求头
        }
        token = strtok(NULL, "\r\n");
        if(token == NULL && !strcasecmp(line_[0].data(), "GET")) {
            data_ = tmp;    // 不是get，拿请求体（get无请求体）
        }
    }
}

void Http::LineParse(string line) {
    int L = line.find(' ');
    int R = line.rfind(' ');
    line_[0].assign(line.data(), L);
    line_[1].assign(line, L+1, R-L-1);
    line_[2].assign(line, R+1, line.size()-R-1);
}

void Http::HeadParse(string head) {
    string k, v;
    int p = head.find(": ");
    if(p != -1) {
        k.assign(head.data(), p);
        v.assign(head, p+2, head.size()-p-2);
        head_.insert(make_pair(k, v));
    }
}

RequestType Http::Method() {
    if(!strcasecmp(line_[0].data(), "GET")) {
        return RT_GET;
    }
    return RT_ELSE;
}

string Http::Path() {
    int p = line_[1].find("?");
    string r = line_[1];
    if(p != -1) {
        r.assign(line_[1].data(), p);
    }
    r = "." + r;

    struct stat status;
    int ret = stat(r.data(), &status);
    if(ret == -1) {
        return "404";
    }
    if(S_ISDIR(status.st_mode)) {
        if(r.at(r.size()-1) == '/') {
            r.erase(r.size()-1, 1);
        }
        r = r + "/index.html";
        if(stat(r.data(), &status) != -1) {
            return r;
        } else {
            return "404";
        }
    } else if(S_ISREG(status.st_mode)) {
        return r;
    } else {
        return "404";
    }
}

string Http::Parameter() {
    int p = line_[1].find("?");
    string r = "";
    if(p != -1) {
        r.assign(line_[1], p+1, line_[1].size()-p-1);
    }
    return r;
}

string Http::Protocol() {
    return line_[2];
}

string Http::Data() {
    return data_;
}

map<string, string> Http::Head() {
    return head_;
}

Http::~Http() {}