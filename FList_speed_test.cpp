#include <iostream>
#include <forward_list>

int main() {
    std::forward_list<int> list;

    // Push 10 millions elements
    for(int i = 0; i < 10'000'000; ++i) {
        list.emplace_front(i);
    }

    // Clean the list
    list.clear();

    // Push another 10 elements
    for(int i = 0; i < 10; ++i) {
        list.emplace_front(i);
    }
}
