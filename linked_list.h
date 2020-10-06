#ifndef TEMPLATE_PRACTICE_LINKED_LIST_H
#define TEMPLATE_PRACTICE_LINKED_LIST_H

template <typename T> class List;

template <typename T> class Node {
    friend class List<T>;

    T val;
    Node<T> *next = nullptr;
    Node<T> *prev = nullptr;

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
    int size = 0;

//    Node<T> storage[1000000];
 //   unsigned char storage[sizeof(Node<T>) * 1000] = {0};

public:
    void prepend(T val) {
        //void *tgt = &storage[size * sizeof(Node<T>)];
        //auto *node = new(tgt) Node<T>(val);
        auto *node = new Node<T>(val);
        node->next = head;
        head = node;
        size++;
    }

    int get_size(){
        return size;
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
            // The delete line would not be included if I was pre-allocating space
            // for the list to remove the overhead of allocating for every element of list
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
