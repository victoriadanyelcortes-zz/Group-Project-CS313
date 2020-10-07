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
    Node<T> *tail = nullptr;
    int size = 0;

//   Example pre-allocation code:S
//   Node<T> storage[1000000];
//   unsigned char storage[sizeof(Node<T>) * 1000] = {0};

public:
    void prepend(T&& val) {
        // These two lines are an example of how pre-allocation would work.
        //void *tgt = &storage[size * sizeof(Node<T>)];
        //auto *node = new(tgt) Node<T>(val);
        auto *node = new Node<T>(val);
        if(head == nullptr) {
            head = node;
            tail = node;
            size++;
        }
        else {
            // set the new node's next equal to the current head
            // set the previous of the current head to the new node
            // set new node to head and increase size
            node->next = head;
            head->prev = node;
            head = node;
            size++;
        }
    }

    void append(T val) {
        // allocate new node for the value
        auto *node = new Node<T>(val);
        node->next = nullptr;
        // if the list is empty
        if(head == nullptr) {
            head = node;
            tail = node;
            size++;
        }
        else {
            // take the current take, set its next to the new node and
            // set the new nodes previous to the old tail
            // set node to tail and increase size
            tail->next = node;
            node->prev = tail;
            tail = node;
            size++;
        }
    }

    Node<T>* find_mid_node(Node<T>* start, Node<T>* end) {
        // if the linked list is empty
        if(start == nullptr) {
           return nullptr;
        }
        // set ahead node to be futher in the list than behind
        Node<T>* ahead = start->next;
        Node<T>* behind = start;
        while(ahead!=end) {
            //set ahead node 2X ahead the behind node, this ensure behind is
            //in the middle when ahead reaches the end
            ahead = ahead ->next;
            if(ahead!=end) {
                behind = behind->next;
                ahead = ahead->next;
            }
        }
        return behind;
    }

    Node<T>* binary_search(T target_val) {
        //set a "left/low" and "right/high" to find middle node
        Node<T>* start = head;
        Node<T>* end = nullptr;
        do {
            Node<T>* mid = find_mid_node(start,end);
            if(mid == nullptr) {
                //if the list if empty
                return nullptr;
            }
            if(mid->val == target_val){
                //if the val at the middle node is the target value,
                // our search has been successful
               // std::cout << "Found the target element! Value: " << mid->val <<std::endl;
                return mid;
            }
            else if(mid->val < target_val) {
                // reset start if the middle value is smaller to
                // mid+1 to search upper half of list
                start = mid->next;

            }
            else {
                //reset end to the middle if value is in lower half of list
                end = mid;
            }
        } while(end == nullptr || end->next != start);

        std::cout << "Element not present" << std::endl;
        return nullptr;
    }

    int get_size(){
        return size;
    }

    void print_list() {
      Node<T> *temp = head;

      // print out each value of the list until temp reaches the end
      while(temp != nullptr) {
          std::cout << temp->val << std::endl;
          temp = temp->next;
      }
    }

    ~List() noexcept {
        Node<T> *temp = head;
        // go through and delete each node
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

        // The following is just overloading operators that allow iteration through the list
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

        self_type operator--(int junk) {
            if(ptr_ == nullptr) {
                return *this;
            }
            ptr_ = ptr_->prev;
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


#endif //TEMPLATE_PRACTICE_LINKED_LIST_H
