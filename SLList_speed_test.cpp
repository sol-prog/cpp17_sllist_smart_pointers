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

    void pop() {
        if(head == nullptr) {
            return;
        }

        std::unique_ptr<Node> temp = std::move(head);
        head = std::move(temp->next);
    }

    void clean() {
        while(head) {
            head = std::move(head->next);
        }
    }

    List(const List &list) {
        Node *root = list.head.get();

        std::unique_ptr<Node> new_head{nullptr};
        Node *pnew_head{nullptr};
        while(root) {
            auto temp{std::make_unique<Node>(root->data)};
            if(new_head == nullptr) {
                new_head = std::move(temp);
                pnew_head = new_head.get();
            } else {
               pnew_head->next = std::move(temp);
               pnew_head = pnew_head->next.get();
            }
            root = root->next.get();
        }
        head = std::move(new_head);
    }


    List(List &&list) {
        head = std::move(list.head);
    }

    void reverse() {
        List tmp;
        Node *root = head.get();
        while(root) {
            tmp.push(root->data);
            root = root->next.get();
        }
        clean();
        head = std::move(tmp.head);
    }

    ~List() {
        clean();
    }

    friend std::ostream& operator<<(std::ostream &os, const List &list);

private:
    std::unique_ptr<Node> head;
};

std::ostream& operator<<(std::ostream &os, const List &list) {
    Node *head = list.head.get();
    while(head) {
        os << head->data << ' ';
        head = head->next.get();
    }
    return os;
}

int main() {
    List list;

    // Push 10 millions elements
    for(int i = 0; i < 10'000'000; ++i) {
        list.push(i);
    }

    // Clean the list
    list.clean();

    // Push another 10 elements
    for(int i = 0; i < 10; ++i) {
        list.push(i);
    }
}
