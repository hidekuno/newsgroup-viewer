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

int main(int argc,char** argv) {

    int rtc = 0;
    string filename = "";
    bool line = false;
    bool mline = false;
    void (*create_tree_impl)(shared_ptr<Item>&, istream&, const char);
    create_tree_impl = create_tree;

    for (int opt = 0; (opt = getopt(argc, argv, "f:lmo")) != -1; ) {
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
            create_tree_impl = create_tree_ordered;
            break;
        default:
            break;
        }
    }

    shared_ptr<Item> top;
    try {
        if (filename == "") {
            create_tree_impl(top, cin, DELIMITER_CHAR);
        } else {
            ifstream ifs(filename);
            create_tree_impl(top, ifs, DELIMITER_CHAR);
            ifs.close();
        }
        Visitor* v;
        if (line) {
            v = new LineItemVisitor("   ","|  ", "`--" ,"|--" );
        } else if (mline) {
            v = new LineItemVisitor("　　", "　┃","　┗━","　┣━");
        } else {
            v = new ItemVisitor();
        }
        top->accept(*v);
    }
    catch (exception& x) {
        cerr << x.what() << endl;
        rtc = 1;
    }
    return rtc;
}
