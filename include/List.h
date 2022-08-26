#include <iostream>
#include <string>
using namespace std;
#include "Item.h"
#include "Spell.h"
#pragma once


template <typename T>
struct node {          //list node that holds a pointer
    T *data;
    node *next;
    ~node() {
        delete data;
    }
};

template <typename T>
class List {
    private:
        node<T> *head;
        int length;   
    public:
        List() {
            head = NULL;
            length = 0;
        }

        List(const List& list) {
            this->head = list.head;
            this->length = list.length;
            cout << "list created by copy!" << endl;
        }

        ~List() {
            int count = length;
            node<T> *temp = head;
            while(temp != NULL) {        //delete each node from head to tail
                node<T> *lister = temp;
                temp = temp->next;
                delete lister;
                count--;
            }
            //if (count == 0) cout << "Scucces!" << endl;
            //else cout << "FAIL!!!" << endl;
        } 
        
        int get_length() {
            return length;
        }
        
        void display() const {
            node<T> *temp = head;
            int count = 1;
            while(temp != NULL) {
                
                cout << count << ": "; (temp->data)->print();
                cout << endl;
                temp = temp->next;
                count++;
            }
        }
        
        void insert_start(T *Data) {
            node<T> *temp = new node<T>;
            temp->data = Data;
            temp->next = head;
            head = temp;
            length++;
        }

        T *remove(int place) {
            if (place > length) { cout << "LIST ERROR"; return NULL;}
            if (head == NULL) { return NULL; }
            node<T> *current = head;
            node<T> *previous;
            if (length == 1) {
                head = NULL;
                length--;
                return current->data;
            }
            if (place == 1) {
                head = head->next;
                length--;
                return current->data;
            }
            
            for(int i=0; i < place-1; i++) {
                previous = current;
                current = current->next;
            }
            previous->next = current->next;
            length--;
            return current->data;
            
        }

        T *get_ith(int place) {
            node<T> *current = head;
            for(int i=0; i < place; i++) {
                current = current->next;
            }
            return current->data;
        }
}; 
