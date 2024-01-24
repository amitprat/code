#include "../Header.h"

/*
https://www.careercup.com/question?id=11856466

Given a very long list of URLs, find the first URL which is unique ( occurred exactly once ).

I gave a O(n) extra space and O(2n) time solution, but he was expecting O(n) time, one traversal.
*/

/*
you can solve this in O(n) using a combination of trie and linked list. The leaf node of a trie maintains a flag to record 
duplicate urls and pointer to a node in a link list. If you encounter a new url, add a node to the head of the linked list 
and set the pointer in the trie. Whenever you encounter a url that is already in the trie, if the flag is not set, then set 
the flag, delete the node from the linked list and set pointer to null. If the flag is already set, then ignore and read the 
next url.
After processing all the urls, the link list should only contain the unique urls and the node at the tail is the first unique 
url from the list. For n urls, inserting urls into the trie in O(n) and link list operations are all constant time. The node 
could just keep the index of the url in the list so that we don't have to store urls in the link list as well.
*/