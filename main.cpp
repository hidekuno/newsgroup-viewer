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
using tree::create_tree;
using tree::Item;
using tree::create_tree_ordered;
using tree::create_visitor;
using tree::LineKind;

const char DELIMITER_CHAR = '.';
const int  MAX_LEVEL = 10;

enum class Ret {
    SUCCESS,
    ERROR,
};

Ret do_logic(char delimiter, bool ordered, int level, string& filename, Visitor* v) {

    try {
        shared_ptr<Item> top;
        istream* in = &cin;
        ifstream ifs;

        if (!filename.empty()) {
            ifs.open(filename);

            if  (ifs.fail()) {
                cerr << "file open fault" << endl;
                return Ret::ERROR;
            }
            in = &ifs;
        }
        if (ordered) {
            create_tree_ordered(top, *in, delimiter);
        } else {
            create_tree(top, *in, delimiter, level);
        }
        if (top.get() == nullptr) {
            return Ret::SUCCESS;
        }
        top->accept(*v);

        // Not close stream
    }
    catch (exception& x) {
        cerr << x.what() << endl;
        return Ret::ERROR;
    }
    return Ret::SUCCESS;
}
// return value 0 is error
int get_level(string& arg_level) {
    int  level = MAX_LEVEL;

    if (arg_level.empty()) {
        return level;
    }

    for (char const &c : arg_level) {
        if (std::isdigit(c) == 0) {
            cerr << "invalid value" << endl;
            return 0;
        }
    }
    level = atoi(arg_level.c_str());

    if (level > MAX_LEVEL) {
        cerr << "invalid value" << endl;
        return 0;
    }
    return level;
}
int main(int argc,char** argv) {


    LineKind lk = LineKind::Nothing;
    bool ordered = false;
    char delimiter = DELIMITER_CHAR;

    string filename;
    string arg_level;

    for (int opt = 0; (opt = getopt(argc, argv, "f:lmod:n:")) != -1; ) {
        switch (opt) {
        case 'f':
            filename = optarg;
            break;
        case 'l':
            lk = LineKind::HalfSize;
            break;
        case 'm':
            lk = LineKind::MultiSize;
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
    if (ordered && !arg_level.empty()) {
        cerr << "not both option -o and -n" << endl;
        return 1;
    }

    auto level = get_level(arg_level);
    if (0 == level) {
        return 1;
    }

    auto v = create_visitor(lk);

    if (Ret::ERROR == do_logic(delimiter, ordered, level, filename, v)) {
        return 1;
    }
    return 0;
}
