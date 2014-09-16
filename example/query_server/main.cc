#include "text_query.h"
#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
    TextQuery text("in.txt");
    string word;
    while(cin >> word)
       cout << text.runQuery(word);
    return 0;
}
