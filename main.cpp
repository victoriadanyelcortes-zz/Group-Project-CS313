#include <iostream>
#include "linked_list.h"
#include "Vector.h"
#include <cstdlib>
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
            c = int_dist(bl); // - '0';
            rand_string += c;
        }
        vect.push(std::move(rand_string));
        rand_string = "";
        j++;
    }

}

void fill_ll_rand_strings(List<std::string> &list, int size) {
    std::random_device rd;
    std::mt19937 bl(rd());
    std::uniform_int_distribution<int> int_dist(32, 126);
    std::string rand_string;
    char c;
    int j = 0;
    while (j < size) {
        for(int i = 0; i < size; ++i) {
            c = int_dist(bl); // - '0';
            rand_string += c;
        }
        list.prepend(std::move(rand_string));
        rand_string = "";
        j++;
    }
}

void fill_vect_with_randnums(Vector<int> &arr, int size) {
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
    std::random_device rd;
    std::mt19937 bloop(rd());
    std::uniform_int_distribution<int> int_dist(0,100);
    int j = 1;
    int random_offset;
    for (int i = 0; i < size; ++i) {
        list.append(j);
        random_offset = int_dist(bloop);
        j += random_offset;
    }
}

int recursive_binary_search(const int* arr, int left, int right, int target) {
    //right = right -1;
    if(left > right) {
        std::cout << "Not in list" << std::endl;
        return -1;
    }
    int mid = (left + right)/2;
    if(target == arr[mid]) {
        return mid;
    }
    else if(target < arr[mid]) {
        return recursive_binary_search(arr, left, mid-1, target);
    }
    else {
        return recursive_binary_search(arr, mid+1, right, target);
    }
}

int iterative_binary_search(const int* arr, int target, int size) {
    int left = 0, right = size-1;
    while(left <= right) {
        int mid = (right+left)/2;
        if(target == arr[mid]) {
            return mid;
        }
        else if (target < arr[mid]) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    std::cout << "Target element not in list" << std::endl;
    return -1;
}

void fill_with_rands(int* arr,int size) {
    srand(time(0));
    int random_offset;
    // start with one and add a random offset to each index of array
    int j = 1;
    for(int i = 0; i < size; ++i) {
        arr[i] = j;
        random_offset = rand() % 100;
        j = j + random_offset;
    }
}

int main() {

    std::cout << "Question 2 Output: " << std::endl;
    int hundred_mill= 100000000, ten_mill = 10000000, mill =1000000;
    //using dynamically allocated arrays as typical declaration caused seg fault
    // for trying to access too much stack mem for the two larger arrays
    int arr_mill[1000000];
    int* arr_10mill = new int[10000000];
    int* arr_100mill = new int[hundred_mill];

    //fill each with sorted random numbers
    fill_with_rands(arr_mill, 1000000);
    fill_with_rands(arr_10mill, 10000000);
    fill_with_rands(arr_100mill, hundred_mill);

    for(int  i = 0; i < 5; ++i) {
        std::cout << arr_100mill[i] << " ";
    }

    std::cout << arr_100mill[hundred_mill-1] << std::endl;


    //NOTE: all arrays  will be timed & searched twice, the first time will be with a
    // number that is definitely in the array, which will be 1, and the second with a random number
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

    //std::cout << recursive_binary_search(arr_10mill,1,0,10000000) << " ";
    //timing array of size 100 million with iterative and recursive binary search
    //auto binary_100mill_start = std::chrono::high_resolution_clock::now();
    iterative_binary_search(arr_100mill, 1,hundred_mill);
    //auto binary_100mill_stop = std::chrono::high_resolution_clock::now();
    //auto duration_100mill_iterative =std::chrono::duration_cast<std::chrono::microseconds>(binary_mill_stop - binary_mill_start).count();
    //std::cout << "Time to find the known number for array of size 100 million using iterative search: " << duration_100mill_iterative << std::endl;

    //auto start_100mill_rec= std::chrono::high_resolution_clock::now();
    recursive_binary_search(arr_100mill,0,hundred_mill-1, 1);
    //auto stop_100mill_rec = std::chrono::high_resolution_clock::now();
    //auto duration_100mill_recursive = std::chrono::duration_cast<std::chrono::microseconds>(start_mill_rec-stop_mill_rec).count();
    //std::cout << "Time to find the known number for array of size 100 million using recurisve search: "  << duration_100mill_recursive << std::endl;




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


    delete [] arr_100mill;
    delete [] arr_10mill;
    return 0;
}