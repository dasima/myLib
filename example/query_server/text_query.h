#ifndef _TEXT_QUERY_H_
#define _TEXT_QUERY_H_

#include <set>
#include <string>
#include <map>
#include <vector>

class TextQuery
{
    public:
        typedef std::vector<std::string>::size_type LineNo;

        TextQuery(const std::string &);
        void readFile(const std::string &);
        std::string runQuery(const std::string &) const;
        std::string printResult(const std::string &, const std::set<LineNo> &) const;

    private:
        std::vector<std::string> lines_;//存放每行的内容
        std::map<std::string, std::set<LineNo> > wordMap_;//单词和它出现的行号的映射

};


#endif  /*_TEXT_QUERY_H_*/
