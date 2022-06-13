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

using tree::Item;
using path::Path;

namespace path {

    void split(vector<string>& v, const string &str, const char sep) {
        stringstream ss(str);
        string buffer;
        while( std::getline(ss, buffer, sep) ) {
            v.push_back(buffer);
        }
    }
    void create_tree_ordered(shared_ptr<Item<Path>>& top, istream& in, const char sep) {

        static unordered_map< string,shared_ptr<Item<Path>> > cache;
        string full_name;

        while (true) {
            if (!std::getline(in,full_name)) break;
            if (cache[full_name] != nullptr) continue;

            size_t ridx = full_name.rfind(sep);
            if (string::npos == ridx) {
                top = cache[full_name] = shared_ptr<Item<Path>>(new Item<Path>(Path(full_name, sep)));
            } else {
                auto parent_name = full_name.substr(0,ridx);
                auto parent = cache[parent_name];
                cache[full_name] = shared_ptr<Item<Path>>(new Item<Path>(Path(full_name, sep),parent));
                parent->add(cache[full_name]);
            }
        }
    }
    void create_tree(shared_ptr<Item<Path>>& top, istream& in, const char sep, int level) {

        static google::dense_hash_map<string, shared_ptr<Item<Path>>, hash<string>> cache;
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
                    top = cache[items] = shared_ptr<Item<Path>>(new Item<Path>(Path(items,sep)));
                } else {
                    auto parent_name = items.substr(0,ridx);
                    auto parent = cache[parent_name];
                    cache[items] = shared_ptr<Item<Path>>(new Item<Path>(Path(items,sep), parent));
                    parent->add(cache[items]);
                }
            }
        }
    }
}
