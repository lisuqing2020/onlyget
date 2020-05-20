# onlyget

## 使用方法
1. 拷贝build/onlyget到你的http服务根目录
2. ./onlyget即可启动http服务，端口8080
3. 只支持get请求，非get会返回403 Forbidden

## 源码模块
1. http模块 --- http.h
    - 可以解析http request

2. tcp模块 --- tcp.h
    - select超时监测，封装了通信接口
