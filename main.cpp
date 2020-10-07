#include <iostream>
#include "linked_list.h"
#include "Vector.h"
#include <vector>
#include <chrono>
#include <random>

void fill_vect_rand_stings(Vector<std::string> &vect, int size) {
    //using random device & mt19937 to generate random
    //numbers & then converting them to corresponding acsii characters
    // Only using numbers between 32 and 126 since they are printable characters
    std::random_device rd;
    std::mt19937 bl(rd());
    std::uniform_int_distribution<int> int_dist(32, 126);
    std::string rand_string;
    char c;
    int j = 0;
    while (j < size) {
        for(int i = 0; i < size; ++i) {
            //adding characters to the strings
            c = int_dist(bl); // - '0';
            rand_string += c;
        }
        //resetting the string and adding to the vector
        vect.push(std::move(rand_string));
        rand_string = "";
        j++;
    }

}

void fill_ll_rand_strings(List<std::string> &list, int size) {
    //using random device & mt19937 to generate random
    //numbers & then converting them to corresponding acsii characters
    // Only using numbers between 32 and 126 since they are printable characters
    std::random_device rd;
    std::mt19937 bl(rd());
    std::uniform_int_distribution<int> int_dist(32, 126);
    std::string rand_string;
    char c;
    int j = 0;
    while (j < size) {
        for(int i = 0; i < size; ++i) {
            //adding characters to the strings
            c = int_dist(bl); // - '0';
            rand_string += c;
        }
        //prepending to the list using move semantics
        list.prepend(std::move(rand_string));
        rand_string = "";
        j++;
    }
}

void fill_vect_with_randnums(Vector<int> &arr, int size) {
    //using random device & mt19937 to generate random
    std::random_device rd;
    std::mt19937 bl(rd());
    std::uniform_int_distribution<int> int_dist(0,100);
    int j = 1;
    int random_offset;
    // start with one and add a random offset to each index of array
    for (int i = 0; i < size; ++i) {
        arr.push(j);
        random_offset = int_dist(bl);
        j += random_offset;
    }
}

void fill_ll_with_randnums(List<int> &list, int size) {
    //using random device & mt19937 to generate random
    std::random_device rd;
    std::mt19937 bl(rd());
    std::uniform_int_distribution<int> int_dist(0,100);
    int j = 1;
    int random_offset;
    for (int i = 0; i < size; ++i) {
        // start with one and add a random offset to insert rands into the list
        list.append(j);
        random_offset = int_dist(bl);
        j += random_offset;
    }
}

int recursive_binary_search(uint64_t *arr, int left, int right, int target) {
    if(left > right) {
        std::cout << "Not in list" << std::endl;
        return -1;
    }
    int mid = (left + right)/2;
    if(target == arr[mid]) {
        //if number is found, return
        return mid;
    }
    else if(target < arr[mid]) {
        // call again with upper bound decreased
        return recursive_binary_search(arr, left, mid-1, target);
    }
    else {
        // call again with lower bound increased
        return recursive_binary_search(arr, mid+1, right, target);
    }
}

int iterative_binary_search(const uint64_t* arr, int target, int size) {
    //set a left and right
    int left = 0, right = size-1;
    while(left <= right) {
        //find middle
        int mid = (right+left)/2;
        if(target == arr[mid]) {
            //if the number is found
            //std::cout << "Found at index: " << mid << std::endl; <-- This line can be uncommented for testing purposes
            return mid;
        }
        else if (target < arr[mid]) {
            //if it's less than the number at the middle, decrease the upper bound
            right = mid - 1;
        }
        else {
            // increase the lower bound
            left = mid + 1;
        }
    }
    std::cout << "Target element not in list" << std::endl;
    return -1;
}

void fill(uint64_t* arr, int size) {
    //using random device & mt19937 to generate random
    std::random_device rd;
    std::mt19937 bl(rd());
    std::uniform_int_distribution<int> int_dist(0,100);
    int random_offset;
    // start with one and add a random offset to each index of array
    int j = 1;
    for(int i = 0; i < size; ++i) {
        //insert random number into the array
        arr[i] = j;
        random_offset = int_dist(bl);
        j += random_offset;
    }
}

int main() {

    std::cout << "Question 2 Output: " << std::endl;
    int hundred_mill= 100000000, ten_mill = 10000000, mill =1000000; // so I don't have to type a bunch of 0s multiple times
    //using dynamically allocated arrays as typical declaration caused seg fault
    // for trying to access too much stack mem for the two larger arrays, using uint64_t to prevent overflow
    uint64_t arr_mill[mill];
    auto* arr_10mill = new uint64_t [ten_mill];
    auto* arr_100mill = new uint64_t[hundred_mill];

    //declare lists of the required sizes to be search and compared to
    List<int> list_1mill;
    List<int> list_10mill;

    //fill lists with random numbers
    fill_ll_with_randnums(list_10mill,ten_mill);
    fill_ll_with_randnums(list_1mill,mill);

    //fill each array with sorted random numbers
    fill(arr_mill, mill);
    fill(arr_10mill, ten_mill);
    fill(arr_100mill,hundred_mill);


    //NOTE: all arrays and lists  will be timed & searched with a
    // number that is definitely in the array, which will be 1

    // timing of linked list sizes 1 million and 10 million using linked-type binary search
    auto binary_ll_start = std::chrono::high_resolution_clock::now();
    list_1mill.binary_search(1);
    auto binary_ll_stop = std::chrono::high_resolution_clock::now();
    auto time_ll = std::chrono::duration_cast<std::chrono::microseconds>(binary_ll_stop-binary_ll_start).count();
    std::cout << "Time to find the known number for linked list of size 1 million(linked-type search): " << time_ll << std::endl;

    auto binary_ll_start_10mil = std::chrono::high_resolution_clock::now();
    list_10mill.binary_search(1);
    auto binary_ll_stop_10mil = std::chrono::high_resolution_clock::now();
    auto time_ll_10mill = std::chrono::duration_cast<std::chrono::microseconds>(binary_ll_stop-binary_ll_start).count();
    std::cout << "Time to find the known number for linked list of size 10 million(linked-type search): " << time_ll_10mill << std::endl << std::endl;

    //timing array of size 1 million with iterative and recursive binary search
    auto binary_mill_start = std::chrono::high_resolution_clock::now();
    iterative_binary_search(arr_mill, 1, 1000000);
    auto binary_mill_stop = std::chrono::high_resolution_clock::now();
    auto duration_iterative =std::chrono::duration_cast<std::chrono::microseconds>(binary_mill_stop - binary_mill_start).count();
    std::cout << "Time to find the known number for array of size 1 million using iterative search: " << duration_iterative << std::endl;

    auto start_mill_rec= std::chrono::high_resolution_clock::now();
    recursive_binary_search(arr_mill,0,1000000-1,1);
    auto stop_mill_rec = std::chrono::high_resolution_clock::now();
    auto duration_recursive = std::chrono::duration_cast<std::chrono::microseconds>(start_mill_rec-stop_mill_rec).count();
    std::cout << "Time to find the known number for array of size 1 million using recurisve search: "  << duration_recursive << std::endl <<std::endl;

    //timing array of size 10 million with iterative and recursive binary search
    auto binary_10mill_start = std::chrono::high_resolution_clock::now();
    iterative_binary_search(arr_10mill, 1,10000000);
    auto binary_10mill_stop = std::chrono::high_resolution_clock::now();
    auto duration_10mill_iterative =std::chrono::duration_cast<std::chrono::microseconds>(binary_mill_stop - binary_mill_start).count();
    std::cout << "Time to find the known number for array of size 10 million using iterative search: " << duration_10mill_iterative << std::endl;

    auto start_10mill_rec= std::chrono::high_resolution_clock::now();
    recursive_binary_search(arr_10mill,0,10000000-1, 1);
    auto stop_10mill_rec = std::chrono::high_resolution_clock::now();
    auto duration_10mill_recursive = std::chrono::duration_cast<std::chrono::microseconds>(start_mill_rec-stop_mill_rec).count();
    std::cout << "Time to find the known number for array of size 10 million using recurisve search: "  << duration_10mill_recursive << std::endl << std::endl;

    //timing array of size 100 million with iterative and recursive binary search
    auto binary_100mill_start = std::chrono::high_resolution_clock::now();
    iterative_binary_search(arr_100mill, 1,hundred_mill);
    auto binary_100mill_stop = std::chrono::high_resolution_clock::now();
    auto duration_100mill_iterative =std::chrono::duration_cast<std::chrono::microseconds>(binary_mill_stop - binary_mill_start).count();
    std::cout << "Time to find the known number for array of size 100 million using iterative search: " << duration_100mill_iterative << std::endl;

    auto start_100mill_rec= std::chrono::high_resolution_clock::now();
    recursive_binary_search(arr_100mill,0,hundred_mill-1, 1);
    auto stop_100mill_rec = std::chrono::high_resolution_clock::now();
    auto duration_100mill_recursive = std::chrono::duration_cast<std::chrono::microseconds>(start_mill_rec-stop_mill_rec).count();
    std::cout << "Time to find the known number for array of size 100 million using recurisve search: "  << duration_100mill_recursive << std::endl;

    // delete dynamically allocated memory when I'm done with it
    delete [] arr_100mill;
    delete [] arr_10mill;

    // This is where Question 7 output begins
    // asking for a size to know how many random strings and numbers to fill with
    std::cout << "\nQuestion 7 Output:" << std::endl;
    int size;
    std::cout << "What size would you like the vector and list to be? ";
    std::cin >> size;

    std::cout << "\nNow timing filling Linked List with random strings: "  <<std::endl;
    List<std::string> list_strings;
    auto start_ll_strings = std::chrono::high_resolution_clock::now();
    fill_ll_rand_strings(list_strings, size);
    auto stop_ll_strings = std::chrono::high_resolution_clock::now();
    auto time_strings = std::chrono::duration_cast<std::chrono::microseconds>(stop_ll_strings - start_ll_strings).count();
    std::cout << "Time to fill with random nums: "<< time_strings << std::endl;

    std::cout << "\nNow timing filling Vector with random strings: "  <<std::endl;
    Vector<std::string> vect_strings;
    auto start_vect_strings = std::chrono::high_resolution_clock::now();
    fill_vect_rand_stings(vect_strings,size);
    auto stop_vect_strings = std::chrono::high_resolution_clock::now();
    auto duration_strings = std::chrono::duration_cast<std::chrono::microseconds>(stop_vect_strings - start_vect_strings).count();
    std::cout << "Time to fill with random strings: "<< duration_strings << std::endl;

    std::cout << "\nNow timing filling Linked List with random numbers: "  <<std::endl;
    List<int> list;
    auto start_ll = std::chrono::high_resolution_clock::now();
    fill_ll_with_randnums(list, size);
    auto stop_ll = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop_ll - start_ll).count();
    std::cout << "Time to fill with random nums: "<< time << std::endl;

    std::cout << "\nNow timing filling Vector with random numbers" << std::endl;
    Vector<int> vect_int;
    auto start_vect = std::chrono::high_resolution_clock::now();
    fill_vect_with_randnums(vect_int, size);
    auto stop_vect = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_vect - start_vect).count();
    std::cout << "Time to fill with random nums: "<< duration << std::endl;


    return 0;
}