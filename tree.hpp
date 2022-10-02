/*
   This is c++-11 sample
   hidekuno@gmail.com
*/
#ifndef  _TREE_HPP
#define  _TREE_HPP

#include <list>
#include <string>
#include <memory>
#include <iostream>
#include <cstdio>
#include <vector>

using std::vector;
using std::string;
using std::list;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;
using std::exception;
using std::unique_ptr;

namespace tree {

    template <class _T>  class Visitor;
    template <class _T>  class ItemVisitor;
    template <class _T>  class LineItemVisitor;
    template <class _T>  class Item;

    enum class LineKind {
        Nothing,
        HalfSize,
        MultiSize,
        MultiSizeBold
    };

    template <class T>
    class Visitor {
    public:
        virtual void visit(Item<T>& item) = 0;
    };

    template <class T>
    using ItemPtr = weak_ptr<Item<T>>;

    template<class T>
    class Item {
        friend class LineItemVisitor<T>;

    private:
        unique_ptr<T> element;
        shared_ptr<Item> parent;
        list<ItemPtr<T>> children;

    public:
        Item(unique_ptr<T> _element) { this->element = std::move(_element); };
        Item(unique_ptr<T> _element, shared_ptr<Item> p) : parent(p) { this->element = std::move(_element); };

#if _DEBUG
        ~Item() {cout << "destructor:" << endl;};
#endif
        inline void add(ItemPtr<T> c) { this->children.push_back(c); };

        inline string myname() {
            return this->element->myname();
        };
        inline shared_ptr<Item<T>> get_ptr(typename list<ItemPtr<T>>::iterator it) {
            return it->lock();
        };
        inline shared_ptr<Item<T>> get_parent() {
            return parent;
        };
        inline void accept(Visitor<T>& v) {
            v.visit(*this);
        };
        const typename list<ItemPtr<T>>::iterator iterator() {return children.begin();}
        const typename list<ItemPtr<T>>::iterator iterator_end() {return children.end();}
    };

    template<class T>
    class ItemVisitor : public Visitor<T> {
    private:
        int level = 0;
    public:
        virtual void visit(Item<T>&);
    };

    template<class T>
    class LineItemVisitor : public Visitor<T> {
    private:
        string vline_last;
        string vline_not_last;
        string hline_last;
        string hline_not_last;

        inline bool is_last(Item<T>* p, ItemPtr<T>& last_item) {
            shared_ptr<Item<T>> si = last_item.lock();
            return (si.get() == p);
        };
        inline bool is_higher_last(shared_ptr<Item<T>>& self, ItemPtr<T>& last_item) {
            shared_ptr<Item<T>> si = last_item.lock();
            return (si.get()== self.get());
        };
    public:
        LineItemVisitor(string vl,string vnl,string hl,string hnl)
            : vline_last(vl),vline_not_last(vnl),hline_last(hl),hline_not_last(hnl){};

        LineItemVisitor(string* l)
            : vline_last(l[0]),vline_not_last(l[1]),hline_last(l[2]),hline_not_last(l[3]){};

        virtual void visit(Item<T>&);
    };
    template <class T>
    Visitor<T>* create_visitor(LineKind& lk) {

        string lines[][4] = {{"    ",  "|   ", "`-- " , "|-- "},
                             {"　　 " ,"│　 ", "└── " , "├── "},
                             {"　　 " ,"┃　 ", "┗━━ " , "┣━━ " }};
        Visitor<T>* v;

        switch (lk) {
        case LineKind::HalfSize:
            v = new LineItemVisitor<T>(lines[0]);
            break;
        case LineKind::MultiSize:
            v = new LineItemVisitor<T>(lines[1]);
            break;
        case LineKind::MultiSizeBold:
            v = new LineItemVisitor<T>(lines[2]);
            break;
        case LineKind::Nothing:
        default:
            v = new ItemVisitor<T>();
        }
        return v;
    }
}
#endif
