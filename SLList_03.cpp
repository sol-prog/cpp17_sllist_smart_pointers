#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;
    Node(int data) : data{data}, next{nullptr} {}
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

    void clean() {
        while(head) {
            head = std::move(head->next);
        }
    }

    ~List() {
        clean();
    }

private:
    std::unique_ptr<Node> head;
};

int main() {
    List list;

    for(int i = 0; i < 10'000'000; ++i) {
        list.push(i);
    }

    std::cout << "Last line of the program. After this, the list nodes will be iteratively destroyed!\n";
}
