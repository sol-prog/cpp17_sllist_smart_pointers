#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;
    Node(int data) : data{data}, next{nullptr} {}
    ~Node() {
        std::cout << "Destroy node with data: " << data << '\n';
    }
};

int main() {
    auto n0{std::make_unique<Node>(0)};

    auto n1{std::make_unique<Node>(1)};
    n1->next = std::move(n0);

    auto n2{std::make_unique<Node>(2)};
    n2->next = std::move(n1);
}
