// Created by Victoria Cortes

#ifndef TEMPLATE_PRACTICE_VECTOR_H
#define TEMPLATE_PRACTICE_VECTOR_H

template<typename T> class Vector {
private:
    T *arr;
    int cur_size;
    int capacity;

public:
    Vector(){
        cur_size = 0;
        capacity = 10;
        arr = new T[capacity];
    }

    explicit Vector(int size) {
        cur_size = size;
        capacity = size*2;
        arr = new T[capacity];
    }

    //copy constructor
    Vector(const Vector& obj) {
        this->cur_size = obj.cur_size;
        this->capacity = obj.capacity;
        arr = new T[cur_size];

        for(int i = 0; i < cur_size; ++i) {
            arr[i] = obj.arr[i];
        }
    }

    //assignment operator
    Vector& operator=(const Vector &obj) {
        if(this!= &obj) {
            if(cur_size > 0) {
                delete [] arr;
            }
            this->cur_size = obj.cur_size;
            this->capacity = obj.capacity;
            arr = new T[this->capacity];
            for(int i = 0; i < cur_size; ++i) {
                this->arr[i] = obj.arr[i];
            }
        }
    }

    T& operator[](int index) {
        return arr[index];
    }

    //move operator =
    Vector& operator=(Vector&& obj) noexcept {
        if(this != &obj){
            delete [] arr;
            this->cur_size = obj.cur_size;
            this->capacity = obj.capacity;
            arr = obj.arr;
            obj.arr = nullptr;
        }
        return *this;
    }

    //move constructor
    Vector(Vector&& obj) noexcept{
        this->cur_size = obj.cur_size;
        this->capacity = obj.capacity;
        arr = obj.arr;
        obj.arr = nullptr;
    }

    //destructor
    ~Vector() {
        delete [] arr;
    }

    void push(T data) {

        // check if size and capacity are equal
        // and resize array if we have reached the capacity using doubling so array is .5 to 1 in "fullness"
        // to try and decrease memory overhead
        if(cur_size == capacity) {
            T* temp = new T[capacity*2];

            // set temp equal to the "old" array
            for(int i = 0; i < cur_size; ++i) {
                temp[i] = arr[i];
            }

            // delete "old" array and set array equal to temp
            // and increase capacity
            delete [] arr;
            arr = temp;
            capacity = capacity*2;
        }

        // add data to the "back" of the array(set as info in last index)
        // and increase size
        arr[cur_size] = data;
        cur_size++;
    }

    T pop() {
        arr[cur_size-1] = 0;
        cur_size--;
    }

    int size() {
        return cur_size;
    }

};

#endif //TEMPLATE_PRACTICE_VECTOR_H
