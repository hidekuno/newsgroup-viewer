/*
   This is c++-11 sample
   hidekuno@gmail.com

   g++ --std=c++11 tree.cpp -o tree
*/
#include <list>
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdexcept>

extern "C" {
  #include "unistd.h"
}
#include <tree.hpp>

using std::string;
using std::list;
using std::cout;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::unordered_map;
using std::vector;
using std::stringstream;
using std::cin;
using std::istream;
using std::ifstream;
using std::exception;
using std::getline;

namespace tree {
    void ItemVisitor::visit(Item& item) {
        for (int i = 0; i < level * 4; ++i) cout << " ";
        cout << item.myname() << endl;

        for (auto it = item.iterator(); it != item.iterator_end(); ++it) {
            shared_ptr<Item> si = item.get_ptr(it);
            level++;
            si->accept(*this);
            level--;
        }
    }
    void LineItemVisitor::visit(Item& item) {

        if (item.parent != nullptr) {
            vector<string> keisen;
            keisen.push_back((is_last(&item, item.parent->children.back()))?hline_last:hline_not_last);

            auto c = item.parent;
            while (c->parent != nullptr) {
                keisen.push_back((is_higher_last(c, c->parent->children.back()))?vline_last:vline_not_last);
                c = c->parent;
            }
            for (int i = keisen.size() - 1; 0 <= i; --i ){
                cout << keisen[i];
            }
        }
        cout << item.myname() << endl;
        for (auto it = item.iterator(); it != item.iterator_end(); ++it) {
            shared_ptr<Item> si = item.get_ptr(it);
            si->accept(*this);
        }
    }
    void split(vector<string>& v, const string &str, const char sep) {
        stringstream ss(str);
        string buffer;
        while( std::getline(ss, buffer, sep) ) {
            v.push_back(buffer);
        }
    }
    void create_tree_ordered(shared_ptr<Item>& top, istream& in, const char sep) {

        static unordered_map< string,shared_ptr<Item> > cache;
        string full_name;

        while (true) {
            if (!std::getline(in,full_name)) break;
            if (cache[full_name] != nullptr) continue;

            size_t ridx = full_name.rfind(sep);
            if (-1 == ridx) {
                top = cache[full_name] = shared_ptr<Item>(new Item(full_name, sep));
            } else {
                auto parent_name = full_name.substr(0,ridx);
                auto parent = cache[parent_name];
                cache[full_name] = shared_ptr<Item>(new Item(full_name, parent, sep));
                parent->add(cache[full_name]);
            }
        }
    }
    void create_tree(shared_ptr<Item>& top, istream& in, const char sep) {

        static unordered_map< string,shared_ptr<Item> > cache;
        string full_name;

        while (true) {
            if (!std::getline(in,full_name)) break;

            string items = "";
            vector<string> vec;
            split(vec, full_name, sep);

            for (auto it = vec.begin();  it != vec.end(); ++it) {

                if (items == "") {
                    items = *it;
                } else {
                    items = items + sep + *it;
                }

                auto k = cache.find(items);
                if (k != cache.end()) continue;

                size_t ridx = items.rfind(sep);

                if (-1 == ridx) {
                    top = cache[items] = shared_ptr<Item>(new Item(items,sep));
                } else {
                    auto parent_name = items.substr(0,ridx);
                    auto parent = cache[parent_name];
                    cache[items] = shared_ptr<Item>(new Item(items, parent, sep));
                    parent->add(cache[items]);
                }
            }
        }
    }
}
