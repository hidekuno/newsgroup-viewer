/*
   This is c++-11 sample
   hidekuno@gmail.com
*/
#include <string>
#include <iostream>
#include <memory>
#include <cstdio>
#include <fstream>

extern "C" {
    #include "unistd.h"
}

#include <tree.hpp>
using std::cin;
using std::cerr;
using std::ifstream;
using tree::Visitor;
using tree::ItemVisitor;
using tree::LineItemVisitor;
using tree::create_tree;
using tree::Item;
using tree::create_tree_ordered;

const char DELIMITER_CHAR = '.';
const int  MAX_LEVEL = 10;
const int  SUCCESS = 0;
const int  ERROR   = -1;

int do_logic(char delimiter, bool ordered, int level, string& filename, Visitor* v) {

    int rtc = SUCCESS;

    try {
        shared_ptr<Item> top;
        istream* in = &cin;
        ifstream ifs;

        if (filename != "") {
            ifs.open(filename);
            if  (ifs.fail()) {
                cerr << "file open fault" << endl;
                return ERROR;
            }
            in = &ifs;
        }
        if (ordered) {
            create_tree_ordered(top, *in, delimiter);
        } else {
            create_tree(top, *in, delimiter, level);
        }
        if (top.get() == nullptr) {
            return SUCCESS;
        }
        top->accept(*v);
    }
    catch (exception& x) {
        cerr << x.what() << endl;
        rtc = ERROR;
    }
    return rtc;
}

int get_level(string& arg_level) {
    int  level = MAX_LEVEL;

    if (arg_level != "") {
        for (char const &c : arg_level) {
            if (std::isdigit(c) == 0) {
                cerr << "invalid value" << endl;
                return ERROR;
            }
        }
        level = atoi(arg_level.c_str());

        if (level > MAX_LEVEL) {
            cerr << "invalid value" << endl;
            return ERROR;
        }
    }
    return level;
}
Visitor* create_visitor(bool line, bool mline) {

    Visitor* v;

    if (line) {
        v = new LineItemVisitor("    ","|   ", "`-- " ,"|-- " );
    } else if (mline) {
        v = new LineItemVisitor("　　 " ,"┃　 ", "└── "  ,"├── " );
    } else {
        v = new ItemVisitor();
    }

    return v;
}
int main(int argc,char** argv) {

    string filename = "";
    bool line = false;
    bool mline = false;
    bool ordered = false;

    char delimiter = DELIMITER_CHAR;
    string arg_level = "";

    for (int opt = 0; (opt = getopt(argc, argv, "f:lmod:n:")) != -1; ) {
        switch (opt) {
        case 'f':
            filename = optarg;
            break;
        case 'l':
            line = true;
            break;
        case 'm':
            mline = true;
            break;
        case 'o':
            ordered = true;
            break;
        case 'd':
            delimiter = optarg[0];
            break;
        case 'n':
            arg_level = optarg;
            break;
        default:
            break;
        }
    }
    if (ordered && arg_level != "") {
        cerr << "not both option -o and -n" << endl;
        return 1;
    }

    auto level = get_level(arg_level);
    if (ERROR == level){
        return 1;
    }

    auto v = create_visitor(line,mline);

    if (ERROR == do_logic(delimiter, ordered, level, filename, v)) {
        return 1;
    }
    return 0;
}
