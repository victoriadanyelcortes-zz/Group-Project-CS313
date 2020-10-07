# Group-Project-CS313
This repo contains the code for homework 1 for CSCI 313. The solutions for questions 2 and 7 are included here,the other questions were completed by the other members
of group 1. All relevant code is included in the master branch, other branches are only for research purposes.

# Question 2 Explanation
For the arrays I decided to make the type uint64_t to prevent integer overflow especially for the larget size array.
When it came to implementing the iterative and recursive binary search for the arrays, I decided to take an "if it ain't
broke don't fix it" approach. So, I used the given code from class and changed it to better fit my usage. But, when it came
to the linked-type binary search I decided to implement binary search on a linked list. I do not think this is the most efficient
implementation of linked-type binary search, but I will include what I think would be a better structure to implement in my conclusion section
I used my own linked list ADT, which I implemented for question 7, and to that added a function to find the middle node 
using a dual pointer method. In the function to find the middle node, there is an ahead and behind pointer, and the behind
pointer contains the middle node. Then, the actual search function acts very similarly to iteravtive binary search.
I was not able to fill a linked with with 100 million random numbers to perform the search since it required too much space.
I will continue to look into ways to make this possible. After I implemented the binary search functions, I timed each 
type of search using chrono in microseconds since milliseconds was too small, which finished the problem. All conclusions
about time will be included in the conclusions sections.
 
# Question 7 Explanation
For this question I implemented my own linked list and vector ADTs. I did this using templates so they could be used for 
multiple types. For the linked list, I created a node class, list class, and iterator. Implementing the Node class was fairly easy, as well as the list class as I had 
done this before. For the iterator, there are using statements in the class because that is a standard, but not all are used. The class itself is fairly standard,
and the implementation is well commented. I decided to make the prepend function in the list class take an rvalue and used that to add random strings to the list. 
But, I did not modify the append function to do the same. In both functions, a pointer to the next value and previous value are created to ensure there is a link.
For the vector class, I started by using the rule of 5 and implemented everything that was needed to complete that. I used the videos on move semantics to help. After that,
I implemented a simple push and pop function meant to act like push_back and pop_back. For the push function, I decided that the array should be doubled each time the 
capacity is met. For pop, I just decreased the size by 1. And, I implemented a basic size function that returns the current size of the array, not the capacity. I think
it would be interesting to make this a more full-fledged impementation, but for the purposes of this assignment these functions were the most useful. Again in the main function,
I filled these with a user given amount of random numbers and random strings using the c++11 random library, and then timed using chrono. All conclusions made will be included in the conclusions 
section. 

# Conclusions

With regards to question 2, it seems that recursive search is a bit faster. But, I would consider this to be a neglible difference
since the two are typically within a couple microseconds of each other. The binary search on the linked list takes much more 
time, but this is due to the fact that finding the middle node is at least O(n) time, meaning the search itself becomes at 
least O(nlogn). An interesting, and in my opinion better, alternative for the linked-type binary search would be to implement
a skip-list. This structure would allow for comparable time complexity for search to binary search on an array with fast insertion as well. I would have
implemented this structure had I had enough time after researching it.

With regards to question 7, it ends up taking about the same amount of time or a bit longer to insert random strings and numbers in the list with comparison to the vector due to the fact that each
node has to be allocated when appended or prepended to the list, creating an overhead. This could be alleviated if one were to pre-allocate space and then used that 
pre-allocated space when inserting into the list, commented out code is left in the class to show how that process would work. Additionally, it takes longer to fill both the
list and vector with random strings and this is due to my implementation. I was not able to generate and add the strings using less than two loops, making this very
costly in terms of time when it comes to vectors or lists of very large sizes. I will continue to work on this to bring the time cost down. 
