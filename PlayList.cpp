// Write your name and date here
// Name: Jimmy Hui
// Date: June 1, 2022
#include "PlayList.h"
#include <iostream>
using namespace std;

// PlayList method implementations go here

// Default Constructor
PlayList::PlayList(){
    numSongs = 0;
    head = NULL;
}

// Destructor
PlayList::~PlayList(){
    
    // Iterate through list and delete every node 
    PlayListNode* cur = head;
    PlayListNode* prev = NULL;

    while (cur !=NULL){
        prev = cur;
        cur = cur->next;
        delete prev;
    }
    
    if (cur != NULL){
        delete cur;
    }

}

// Copy Constructor
PlayList::PlayList(const PlayList& pl){
    
    if (pl.head == NULL){
        head = NULL;
    }
    else{
        head = new PlayListNode(pl.head->song);
        PlayListNode* old_cur = pl.head->next;
        PlayListNode* new_cur = head;
        unsigned count = 0;

        while (old_cur !=NULL){
            new_cur->next = new PlayListNode(old_cur->song);
            new_cur = new_cur->next;
            old_cur = old_cur->next;
            count++;
        }

        numSongs = count+=1;
    }
  
}

// Overload Assignment Operator
PlayList& PlayList::operator=(const PlayList& pl){

    // Call copy constructor on pl
    *this = PlayList(pl);

    return *this;
}

// Insert function
void PlayList::insert(Song sng, unsigned int pos){

    // Edge case: Inserting to position 0 when list is not empty
    if (head != NULL && pos == 0){
        PlayListNode* newNode = new PlayListNode(sng,head);
        head = newNode;
        numSongs++;
    }

    // Regular case
    else {

        // Have one fast pointer and one slow pointer
        PlayListNode* cur = head;
        PlayListNode* prev = NULL;
        unsigned int count = 0;

        // Iterate until cur is pointing to correct insertion position
        while (cur != NULL && count != pos) {
            prev = cur;
            cur = cur->next;
            count++;
        }
  
        // If list is empty, then set newnode to head
        if (head == NULL) {
            PlayListNode* newNode = new PlayListNode(sng,NULL);
            head = newNode;
            numSongs = 1;
        }

        // Rewire previous, newNode, and cur to correct position
        else {
            PlayListNode* newNode = new PlayListNode(sng,cur);
            prev->next = newNode;
            numSongs++;
        }
    } 
    
}

// Remove function
Song PlayList::remove(unsigned int pos) {

    // If node is head, then set head=head->next and return song and delete node
    if (pos == 0){
        Song res = head->song;
        PlayListNode* cur = head;
        head = head->next;
        delete cur;
        numSongs--;
        return res;
    }

    // If node is not head
    else {
        
        // Use a fast and slow pointer to find cur and prev node
        unsigned int count = 0;
        PlayListNode* cur = head;
        PlayListNode* prev = NULL;

        // Iterate until cur and prev pointers are at correct position
        while (count != pos && cur != NULL){
            prev = cur;
            cur = cur->next;
            count++;
        }

        // Save the removed song
        Song res = cur->song;
        PlayListNode* rm = cur;
        
        // Rewire nodes to exclude removing node
        prev->next = prev->next->next;
        numSongs--;

        // Delete node and return song
        delete rm;
        return res;
    }
}

// Swap function
void PlayList::swap(unsigned int pos1, unsigned int pos2) {

    // Set pos1 to always be less than pos2
    if (pos1 > pos2){
        unsigned int temp = pos2;
        pos2 = pos1;
        pos1 = temp;
    }

    // Iterate until first and first_prev index found 
    PlayListNode* first = head;
    PlayListNode* first_prev  = NULL;
    unsigned int first_count = 0;

    while (first != NULL && first_count != pos1){
        first_prev = first;
        first = first->next;
        first_count++;
    }

    // Iterate until second and second_prev index found
    PlayListNode* second = head;
    PlayListNode* second_prev = NULL;
    unsigned int second_count = 0;

    while (second != NULL && second_count != pos2){
        second_prev = second;
        second = second->next;
        second_count++;
    }

    // Store location of node after second
    PlayListNode* tempNode = second->next;

    // If pos1 and pos2 right next to each other
    if ((pos1 += 1) == pos2){

        second->next = first;
        first->next = tempNode;

        if (first_prev == NULL){
            head = second;
        }
        if (second_prev == NULL){
            head = first;
        }

        if (first_prev != NULL && second_prev != NULL && first == second_prev){
            first_prev->next = second;
        }

    }

    // If pos1 and pos2 are not beside each other
    else{

        second->next = first->next;
        first->next = tempNode;

        // If one of the nodes are head nodes, set head node
        if (first_prev == NULL){
            second_prev->next = first;
            head = second;
        }
        if (second_prev == NULL){
            first_prev->next = second;
            head = first;
        }

        // If neither nodes are head nodes 
        if (first_prev != NULL && second_prev != NULL){
            first_prev->next = second;
            second_prev->next = first;
        }
    }

}

// Get function
Song PlayList::get(unsigned int pos) const {
    
    // Have a ptr with a corresponding counter to index and iterate until at pos
    unsigned int counter = 0;
    PlayListNode* cur = head;

    while (cur != NULL  && counter != pos){
        cur = cur->next;
        counter++;
    }

    return cur->song;
}

// Size function
unsigned int PlayList::size() const {
    
    return numSongs;
}
