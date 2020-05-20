#ifndef _HTTP_H_
#define _HTTP_H_

#include <string>
#include <map>
using namespace std;

enum ResourceType {
    RT_DIR, RT_FILE, RT_ERR
};

enum RequestType {
    RT_GET, RT_ELSE
};

class Http {
private:
    string line_[3];
    map<string, string> head_;
    string data_;
    void LineParse(string line);
    void HeadParse(string head);
public:
    Http(string request);
    RequestType Method();   // 获取请求方法
    string Path();          // 获取url路径，如果是目录补index.html，文件不存在则返回404
    string Protocol();      // 获取协议版本
    string Data();          // 获取请求体
    string Parameter();     // 获取url参数
    map<string, string> Head();
    ~Http();
};

#endif