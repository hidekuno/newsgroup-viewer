/*
   This is c++-11 sample
   hidekuno@gmail.com
*/
#include <unordered_map>
#include <sstream>
#include <google/dense_hash_map>
#include <tree.hpp>

#include <path.hpp>
using std::stringstream;
using std::unordered_map;
using std::hash;
using std::shared_ptr;
using std::istream;

using path::Path;

namespace tree {
    template<class T>
    void ItemVisitor<T>::visit(Item<T>& item) {
        std::printf("%*s%s\n", level*4, "", item.myname().c_str());
        for (auto it = item.iterator(); it != item.iterator_end(); ++it) {
            shared_ptr<Item<T>> si = item.get_ptr(it);
            level++;
            si->accept(*this);
            level--;
        }
    }
    template<class T>
    void LineItemVisitor<T>::visit(Item<T>& item) {
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
            shared_ptr<Item<T>> si = item.get_ptr(it);
            si->accept(*this);
        }
    }
}
// Explicit Instance
template class ItemVisitor<Path>;
template class LineItemVisitor<Path>;
