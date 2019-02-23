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

struct List {
    List() : head{nullptr} {};

    void push(int data) {
        auto temp{std::make_unique<Node>(data)};
        if(head) {
            temp->next = std::move(head);
            head = std::move(temp);

        } else {
            head = std::move(temp);
        }
    }

    void pop() {/* ... */}
    ~List() {/* ... */}

private:
    std::unique_ptr<Node> head;
};

int main() {
    List list;

    list.push(0);
    list.push(1);
    list.push(2);
    list.push(3);
}
