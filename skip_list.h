#ifndef TEMPLATE_PRACTICE_SKIP_LIST_H
#define TEMPLATE_PRACTICE_SKIP_LIST_H
template <typename K> class Skip_Node {
public:
    K key;

    Skip_Node(K k, int level) {
        key = k;
    }
};

template <typename K> class Skip_list {
    int max_lev;
    double P;
    Skip_Node<K> *head;

public:
    Skip_list(int max, double p) {
        //std::cout << "Constructor\n";
        max_lev = max;
        P = p;
        head = new Skip_Node<K> (NULL, max_lev);
        auto *end = new Skip_Node<K>(INTMAX_MAX,max_lev);
        for(int i = 0; i < max_lev; ++i) {
            head->forward[i] = end;
        }
    }

    //needed to insert into skip_list
    int random_level() {
        //srand(time(0));
        double r = (double)rand()/RAND_MAX;
        int new_lev = 0;
        while (new_lev < max_lev && r < P) {
            new_lev++;
            r = (double)rand()/RAND_MAX;
        }
        return new_lev;
    }

    Skip_Node<K>* create_node(K key, int lev) {
        auto* n = new Skip_Node<K>(key,lev);
        return n;
    }

    void insert(K key) {
        Skip_Node<K> *current = head;
        Skip_Node<K> *update_arr[max_lev+1];
//        auto *ender = new Skip_Node<K>(INTMAX_MAX,max_lev);
//        for(int i = 0; i < max_lev; ++i) {
//            update_arr->forward[i] = ender;
//        }


        for(int i = max_lev; i >= 0; --i) {
            //std::cout <<"oop\n";
            while(current->forward[i] != NULL && current->forward[i]->key < key){
                //std::cout << key << "\n";
                current = current->forward[i];
            }
            update_arr[i] = current;

        }
        current = current->forward[0];
        if(current== NULL || current->key != key) {
            int rand_lev = random_level();
            Skip_Node<K>* n = create_node(key, rand_lev);
            for(int i = 0; i < rand_lev; ++i){
                n->forward[i] = update_arr[i]->forward[i];
                update_arr[i]->forward[i] = n;
            }
            std::cout << "Inserted" << std::endl;
        }

    }

    void print_skip_list(){
        for(int i = 0; i < max_lev; ++i) {
            Skip_Node<K> *node = head->forward[i];
            while(node != NULL) {
                std::cout << node->key << " ";
                node = node->forward[i];
            }
        }
        std::cout << std::endl;
    }

    Skip_Node<K>* search( K key) {
        Skip_Node<K>* current = head;
        for(int i = max_lev; i >= 0; --i){

            while(current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        if(current && current->key == key) {
            std::cout << "found\n";
            return current;
        }
        else {
            std::cout << "nooooo\n";
            return nullptr;
        }
    }
};

#endif //TEMPLATE_PRACTICE_SKIP_LIST_H
