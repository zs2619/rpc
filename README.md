## rpc

结构化数据存储格式,用于结构化数据的序列化,支持序列化反序列化二进制，和序列化成json，也可以生成Rpc接口
支持c++ as3 c# golang

## 依赖
flex and bison

## 构建
#### Linux 
    cmake .
    make 

## 使用
Usage: rpc [options] file
Options:
  -o   dir    output file directory
  -i   dir    input  file directory
  -gen lang   cpp as3 cs go Generate code .
  -json       serialize json.