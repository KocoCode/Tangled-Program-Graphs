#include <iostream>
#include <cassert>
#include "pool.h"

using namespace std;

struct Foo {
private:
    int val, refCount, id;
public:
    Foo(int v=0): val(v), refCount(0) {}
    void setId(int v) {
        id = v;
    }
    int getId() {
        return id;
    }
    int getRefCount() {
        return refCount;
    }
    void setRefCount(int v) {
        refCount = v;
    }
    int getVal() {
        return val;
    }
    int getAction() {
        return 0;
    }
};

struct Bar {
private:
    int val;
    bool root;
    int refCount, id;
public:
    Bar(int v=0, bool r=false): val(v), root(r), refCount(0) {}
    void setId(int v) {
        id = v;
    }
    int getId() {
        return id;
    }
    int getRefCount() {
        return refCount;
    }
    void setRefCount(int v) {
        refCount = v;
    }
    int getVal() {
        return val;
    }
    bool isRoot() {
        return root;
    }
    void setRoot(bool r) {
        root = r;
    }
};

int main() {
    BidderPool<Foo> bpool;
    for (int i = 0; i < 100; ++i) {
        bpool.insert(Foo(i));
    }
    for (int i = 0; i < 1000; ++i) {
        int id = bpool.random();
        int r = bpool.get(id).getVal();
        assert(r >= 0 and r < 100);
    }
    assert(bpool.size() == 100);
    for (int i = 0; i < 100; ++i) {
        if (i == 50) continue;
        bpool.remove(i);
    }
    for (int i = 0; i < 1000; ++i) {
        int id = bpool.random();
        int r = bpool.get(id).getVal();
        assert(bpool.get(r).getVal() == 50);
    }
    for (int i = 0; i < 50; ++i) {
        bpool.insert(Foo(i));
    }
    for (int i = 0; i < 1000; ++i) {
        int id = bpool.random();
        int r = bpool.get(id).getVal();
        assert(r >= 0 and r <= 50);
    }
    assert(bpool.size() == 51);

    TeamPool<Bar> tpool;
    tpool.addRootTeam(tpool.insert(Bar(0, true)));
    for (int i = 1; i < 10; ++i) {
        auto tmp = Bar(i, false);
        assert(tpool.insert(tmp) == i);
    }
    for (int i = 0; i < 1000; ++i) {
        int id = tpool.randomRootTeam();
        int r = tpool.get(id).getVal();
        assert(r >= 0 and r <= 9);
    }
    for (int i = 0; i < 1000; ++i) {
        int id = tpool.randomRootTeam();
        int r = tpool.get(id).getVal();
        assert(r == 0);
    }
    tpool.addRootTeam(9);
    tpool.removeRootTeam(0);
    for (int i = 0; i < 1000; ++i) {
        int id = tpool.randomRootTeam();
        int r = tpool.get(id).getVal();
        assert(r == 9);
    }
    for (int i = 6; i < 10; ++i) {
        tpool.remove(i);
    }
    for (int i = 0; i < 1000; ++i) {
        int id = tpool.random();
        int r = tpool.get(id).getVal();
        assert(r >= 0 and r <= 5);
    }
}
