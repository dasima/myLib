#include "text_query.h"
#include <echo/exception.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

TextQuery::TextQuery(const string &filename)
{
    readFile(filename);
}

//读取文件，并建立单词到关联行号的map容器的映射
void TextQuery::readFile(const string &filename)
{
    //1. 打开文件
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");

    //2. 存储输入文件
    //读取每一行到line中，并存储到vector对象lines_中
    string line;
    while(getline(in, line))
        lines_.push_back(line);
    in.close();

    //3. 建立从单词关联到行号的map容器
    for(vector<string>::size_type line_num = 0; line_num != lines_.size(); ++line_num)
    {
        //将每一行分解为单词，对每一个单词进行操作
        istringstream iss(lines_[line_num]);
        string word;
        while(iss >> word)
            wordMap_[word].insert(line_num);
    }
}

//查询功能
string TextQuery::runQuery(const string &word) const
{
    map<string, set<LineNo> >::const_iterator loc;//const_iterator???
    loc = wordMap_.find(word);
    if(loc == wordMap_.end())
        return printResult(word, set<LineNo>());
    else
        return printResult(word, loc->second);
}   

//打印输出
string TextQuery::printResult(const string &word, const set<LineNo> &result) const
{
    string ret;
    size_t size = result.size();
    char buf[32];
    snprintf(buf, sizeof(buf), "%u", size);
    ret = word + " occurs " + buf + " time(s)\n";
    
    for(set<LineNo>::iterator it = result.begin(); it != result.end(); ++it)
    {
        snprintf(buf, sizeof(buf), "%u", *it + 1);
        ret += string("line") + buf + ")";
        ret += lines_[*it] + "\n";
    }
    return ret;
}


















