#include<iostream>
#include<unordered_map>
using namespace std;


struct Node{
    
  int key;
  int value;
  Node* prev;
  Node* next;
  
  Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr){};
  
};


class LRUCache{
public:
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    
    
    
public:
    void addFront(Node* node);  
    Node* removeLastNode();
    void removeAddFront(Node* node);
public:
    LRUCache(int cap) : capacity(cap), head(nullptr), tail(nullptr){};
    int get(int key);
    void put(int key, int value);
    void printCache();
};

void LRUCache::addFront(Node* node){
    
    if (head == NULL && tail == NULL){
        head = node;
        tail = node;
      
    }else{
        node->next = head;
        head->prev = node;
        head = node;
    }
}


Node* LRUCache::removeLastNode(){
    if (head == NULL && tail == NULL){
        std::cout << "No node found";
    }else{
            Node* temp = tail;
            tail = temp->prev;
            tail->next = NULL;
           return temp;
           
        }
}

void LRUCache::removeAddFront(Node* node){
    
    if(head == NULL && tail == NULL){
        std::cout << "No node found";
    }else{
        if (node == head){
            cout << "The node is the head value";
            head->value = node->value;
        }
        else if(tail == node){
            Node* temp = tail;
            tail = temp->prev;
            tail->next = NULL;
            temp->value = node->value;
            addFront(temp);
        }else{
            
            Node* temp = head;
            while(temp){
                if(temp == node){
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    temp->value = node->value;
                    addFront(temp);
                    break;
                }
                temp = temp->next;
            }   
        }
    }
    
    
    
}


int LRUCache::get(int key){
    //find the key in present in the  dictionary 
    auto cacheIterator = cache.find(key);
    if(cacheIterator != cache.end()){
        Node* node = cacheIterator->second;
        removeAddFront(node);
        return node->value;
    }else{
        return -1;
    }
}

void LRUCache::put(int key, int value){
    
    //first check the value is present in the linked list
    auto cacheIterator = cache.find(key);
    if(cacheIterator != cache.end()){
        Node* node = cacheIterator->second;
        node->value = value;
        removeAddFront(node);
        
    }else{
        if (capacity == 0){
            //remove the last node 
            Node* lastNode = removeLastNode();
            //erase from the cache 
            cache.erase(lastNode->key);
            //delete the pointer 
            delete lastNode;
            //create a node
            Node* node = new Node(key, value);
            //add the node in front 
            addFront(node);
            //update the cache
            cache[key] = node;
            
        }else{
             //create a node
            Node* node = new Node(key, value);
            //add the node in front 
            addFront(node);
            //update the cache
            cache[key] = node;
            capacity -= 1;
        }
    }
}
void LRUCache::printCache(){
    
    for(const auto&[key, value] : cache){
        cout << "Cache Key: " << key << endl;
    }
}



int main() {
    // Create an LRU cache with capacity 3
    LRUCache cache(3);

    // Add key-value pairs to the cache
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    // Get the value for key 2 (should be 20)
    std::cout << "Value for key 2: " << cache.get(2) << std::endl;
    cache.printCache();

    // // Add a new key-value pair, which will remove the least recently used element (key 1, value 10)
    cache.put(4, 40);
    //after adding the value 
    cout << "After removing the element " << endl;
    cache.printCache();

    // // The value for key 1 should now be -1 (not found)
    std::cout << "Value for key 1: " << cache.get(1) << std::endl;

    return 0;
}


