/*
   This is c++-11 sample
   hidekuno@gmail.com
*/
#ifndef  _TREE_HPP
#define  _TREE_HPP

#include <list>
#include <string>
#include <iostream>
#include <memory>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <vector>

using std::vector;
using std::string;
using std::list;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::istream;
using std::exception;

namespace tree {

    class Visitor;
    class ItemVisitor;
    class LineItemVisitor;
    class Item;

    void split(vector<string>&, const string&, const char);
    void create_tree_ordered(shared_ptr<Item>&, istream&, const char);
    void create_tree(shared_ptr<Item>&, istream&, const char);

    class Visitor {
    public:
        virtual void visit(Item& item) = 0;
    };
    typedef weak_ptr<Item> ItemPtr;

    class Item {
        friend class LineItemVisitor;

    private:
        string name;
        shared_ptr<Item> parent;
        list<ItemPtr> children;
        const char sep;

    public:
        Item(string& s, const char _sep) : name(s), sep(_sep) {};
        Item(string& s, shared_ptr<Item> p,const char _sep) : name(s), parent(p), sep(_sep) {};

#if _DEBUG
        ~Item() {cout << "destructor:" + name << endl;};
#endif
        inline void add(ItemPtr c) { this->children.push_back(c); };

        inline string myname() {
            size_t ridx = this->name.rfind(this->sep);
            return this->name.substr(ridx + 1);
        };
        inline shared_ptr<Item> get_ptr(list<ItemPtr>::iterator it) {
            return  it->lock();
        };
        inline shared_ptr<Item> get_parent() {
            return  parent;
        };
        inline void accept(Visitor& v) {
            v.visit(*this);
        };
        const list<ItemPtr>::iterator iterator() {return children.begin();}
        const list<ItemPtr>::iterator iterator_end() {return children.end();}
    };

    class ItemVisitor : public Visitor {
    private:
        int level = 0;
    public:
        virtual void visit(Item&);
    };
    class LineItemVisitor : public Visitor {
    private:
        string vline_last;
        string vline_not_last;
        string hline_last;
        string hline_not_last;

        inline bool is_last(Item* p, ItemPtr& last_item) {
            shared_ptr<Item> si = last_item.lock();
            return (si.get() == p);
        };
        inline bool is_higher_last(shared_ptr<Item>& self, ItemPtr& last_item) {
            shared_ptr<Item> si = last_item.lock();
            return (si.get()== self.get());
        };
    public:
        LineItemVisitor(string vl,string vnl,string hl,string hnl)
            : vline_last(vl),vline_not_last(vnl),hline_last(hl),hline_not_last(hnl){};
        virtual void visit(Item&);
    };
}
#endif
