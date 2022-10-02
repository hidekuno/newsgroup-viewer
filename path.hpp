/*
   This is c++-11 sample
   hidekuno@gmail.com
*/
#ifndef  _PATH_HPP
#define  _PATH_HPP

#include <string>
#include <vector>
#include <tree.hpp>

using std::vector;
using std::string;
using std::shared_ptr;
using std::istream;

using tree::Item;
using tree::Visitor;
using tree::LineKind;
using tree::LineItemVisitor;
using tree::ItemVisitor;

namespace path {

    struct Path {
    public:
        string name;
        char sep;
    public:
        Path(string& s, const char _sep) : name(s), sep(_sep) {};
        inline string myname() {
            size_t ridx = this->name.rfind(this->sep);
            return this->name.substr(ridx + 1);
        };
    };

    void split(vector<string>&, const string&, const char);
    void create_tree_ordered(shared_ptr<Item<Path>>&, istream&, const char);
    void create_tree(shared_ptr<Item<Path>>&, istream&, const char, int);
}
#endif
