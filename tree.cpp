/*
   This is c++-11 sample
   hidekuno@gmail.com
*/
#include <unordered_map>
#include <sstream>
#include <google/dense_hash_map>
#include <tree.hpp>

using std::stringstream;
using std::unordered_map;
using std::hash;

namespace tree {

    void ItemVisitor::visit(Item& item) {
        std::printf("%*s%s\n", level*4, "", item.myname().c_str());
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
            for (auto it  = keisen.rbegin(); it != keisen.rend(); it++) {
                std::printf("%s", (*it).c_str());
            }
        }
        std::printf("%s\n", item.myname().c_str());
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
            if (string::npos == ridx) {
                top = cache[full_name] = shared_ptr<Item>(new Item(full_name, sep));
            } else {
                auto parent_name = full_name.substr(0,ridx);
                auto parent = cache[parent_name];
                cache[full_name] = shared_ptr<Item>(new Item(full_name, parent, sep));
                parent->add(cache[full_name]);
            }
        }
    }
    void create_tree(shared_ptr<Item>& top, istream& in, const char sep, int level) {

        static google::dense_hash_map<string, shared_ptr<Item>, hash<string>> cache;
        cache.set_empty_key("DUMMY");
        cache.resize(40960);
        string full_name;

        std::ios_base::sync_with_stdio(false);
        while (true) {
            if (!std::getline(in,full_name)) break;

            string items = "";
            stringstream ss(full_name);
            string it;

            for (int c = 0; std::getline(ss, it, sep); c++) {
                if (items == "") {
                    items = it;
                } else {
                    items += sep;
                    items += it;
                }
                if (c > level) {
                    break;
                }
                auto k = cache.find(items);
                if (k != cache.end()) continue;

                size_t ridx = items.rfind(sep);
                if (string::npos == ridx) {
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
    Visitor* create_visitor(LineKind& lk) {

        string lines[][4] = {{"    ",  "|   ", "`-- " , "|-- " },
                             {"　　 " ,"│　 ", "└── " , "├── "},
                             {"　　 " ,"┃　 ", "┗━ "  , "┣━ " }};
        Visitor* v;

        switch (lk) {
        case LineKind::Nothing:
            v = new ItemVisitor();
            break;
        case LineKind::HalfSize:
            v = new LineItemVisitor(lines[0]);
            break;
        case LineKind::MultiSize:
            v = new LineItemVisitor(lines[1]);
            break;
        case LineKind::MultiSizeBold:
            v = new LineItemVisitor(lines[2]);
            break;
        default:
            v = new ItemVisitor();
        }

        return v;
    }
}
