#ifndef TEMPLATE_PRACTICE_LINKED_LIST_H
#define TEMPLATE_PRACTICE_LINKED_LIST_H

template <typename T> class List;

template <typename T> class Node {
    friend class List<T>;

    T val;
    Node<T> *next = nullptr;

public:
    explicit Node(T value) {
       val = value;
    }

    T& get_val() {
        return val;
    }
};

template <typename T> class List {
    Node<T> *head = nullptr;

public:
    void prepend(T val) {
        Node<T> *node = new Node<T>(val);
        node->next = head;
        head = node;
    }

    void print_list() {
      Node<T> *temp = head;

      while(temp != nullptr) {
          std::cout << temp->val << std::endl;
          temp = temp->next;
      }
    }

    ~List() noexcept {
        Node<T> *temp = head;

        while(temp != nullptr) {
            Node<T> *tempnext = temp->next;
            delete temp;
            temp = tempnext;
        }
    }

    class Itr {
        friend class List<T>;
        Node<T> *ptr_;

    public:
        using self_type = Itr;
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = T*;
        using reference = T&;

        explicit Itr(Node<T> *ptr) : ptr_(ptr) { }
        self_type operator++() {
            if(ptr_ == nullptr) {
                return *this;
            }
            self_type i = *this;
            ptr_ = ptr_->next;
            return i;
        }

        self_type operator++(int junk) {
            if (ptr_ == nullptr) {
                return *this;
            }
            ptr_ = ptr_->next;
            return *this;
        }

        reference operator*() {
            return ptr_->get_val();
        }

        pointer operator->() {
            return &ptr_->get_val();
        }

        bool operator==(const self_type& rhs) {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const self_type& rhs) {
            return ptr_!=rhs.ptr_;
        }
    };

    Itr begin() {
        return Itr(head);
    }

    Itr end() {
        return Itr(nullptr);
    }

};

//template <typename T>

#endif //TEMPLATE_PRACTICE_LINKED_LIST_H
