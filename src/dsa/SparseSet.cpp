#include "SparseSet.hpp"
#include <iostream>

void test() {
    std::cout << "Begin Sparse Set Test\n";
    auto data = dsa::SparseSet<int>();
    data.set(15, -9);
    data.set(23, -32);
    data.set(9, 19);
    auto* t1 = data.get_ref(111111);
    auto* t2 = data.get_ref(23);
    if (t1==nullptr) {
        std::cout << "14->nullptr\n";
    }
    std::cout << "23->" << t2->data << std::endl;
    data.remove(99999);
    std::cout << "1\n";
    data.remove(15);
    std::cout << "1\n";
    auto* t3 = data.get_ref(15);
    std::cout << "1\n";
    if (t3==nullptr) {
        std::cout << "15->nullptr\n";
    } else {
        std::cout << "15->" << t3->data << std::endl;
    }
    std::cout << "End Sparse Set Test\n";
}