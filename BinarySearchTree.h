#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iostream>
#include <iomanip>
using namespace std;

template<typename KeyType, typename ValueType>

class BinarySearchTree
{
	struct BST{
		KeyType key;
		ValueType value;
		BST* right;
		BST* left;

		BST(KeyType key, ValueType value) {
            this->key = key;
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
	};
	BST* root;
	size_t sizeCount = 0;

public:

BinarySearchTree(){
    root = nullptr; 
}
~BinarySearchTree(){
    clear(root);
}

bool empty() const{
    return root == nullptr;

}

void remove(KeyType const& key){
    BST* parent = nullptr;
    BST* temp = this->root;
    
    while (temp != nullptr){
    if (temp->key == key){
        if (temp->left != nullptr && temp->right != nullptr){
            BST* succ = temp->left;
            ValueType succVal;
            KeyType succKey;
            while (succ->right != nullptr){
                succ = succ->right;
            }
            succKey = succ->key;
            succVal = succ->value;
            remove(succ->key);
            temp->key = succKey;
            temp->value = succVal;
        }
        else{
            BST* child = temp->left;
            if(child == nullptr){
                child = temp->right;
            }else{
                child = temp->left;
            }
            if (parent == nullptr){
                root = child;
            }
            else{
                if (key < parent->key){
                    parent->left = child;
                }
                else if(key >= parent->key){
                    parent->right = child;
                }
            }
            sizeCount--;
            delete temp;
        }
        break;
    }
    else{
        parent = temp;
        if (key < temp->key){
            temp = temp->left;
        }
        else if(key >= temp->key){
            temp = temp->right;
        }
    }
    }
}
	void clear(BST* first)
{
    if (first != nullptr){
        clear(first->left);
        clear(first->right);
        delete first;
    }
    sizeCount = 0;
}
void insert(KeyType const& k, ValueType const& v)
{
    BST* temp = root;
    BST* parentOfInsert = nullptr;      
    bool matched = false;   
    sizeCount++; 
    while (!matched && temp != nullptr)
    {    
        parentOfInsert = temp;
        if(k < temp->key){
            temp = temp->left;      
        }
        else if (k > temp->key){ 
            temp = temp->right;  
        }
        else{                            
            matched = true; 
			if(temp->value != v){
				temp->value = v;
			}
			else{
                //such element exist
                sizeCount--;
				delete temp;
			}
		
        }
    }      
    if (!matched)
    {                
        temp = new BST(k,v);      
        if (parentOfInsert == nullptr)
        {                      
            root = temp; 
             
        }  
        else if (k < parentOfInsert->key)
        {
            parentOfInsert->left = temp;
        }
        else if(k > parentOfInsert->key)
        {      
            parentOfInsert->right = temp;
        }
    }
    
}


ValueType* find(KeyType const& k){
    bool correct = false;
    BST* temp = root;
    if(root == nullptr) return NULL;
    while(temp != nullptr && !correct){
        if(k > temp->key){
            temp = temp->right;
        }
        else if(k < temp->key){
            temp= temp->left;
        }
        else correct = true;

    }
    if(temp == nullptr) {
        return NULL;
    }
    return &(temp->value);
}

string spaceCounter(int tab) const{
		string spaces = "";
		for(int i= 0; i<tab;i++){
			spaces += "    ";
		}
		return spaces;
	}

unsigned int height(BST* first){
	if(first == nullptr) {
        return 0;
    }
    else{
    	int l,r;
        l = height(first->left);
        r = height(first->right);
        if(l>r) return l;
        else return r;
    }
}

size_t size() const{
    return sizeCount;

}								
std::string strHelper(BST* temp) const{
	if(temp == nullptr) {
		return "";
	}else{
	string line =  "(["+ to_string(temp->key) + "," + to_string(temp->value) + "]," + strHelper(temp->left) + "," + strHelper(temp->right) + ")";
	return line;
	}
}								
 
std::string toString() const{
	return strHelper(root);
}

template<typename StreamType>
void printHelper(unsigned int tab, BST* elem, StreamType& stream) const{
	if(!elem) return;
	if(elem != nullptr){
		stream << "[" << elem->key << ", " << elem->value << "]\n";
		tab++;
		if(elem->left != nullptr){
			stream<< spaceCounter(tab)<< "L: ";
			printHelper(tab, elem->left, stream);
		}
		if(elem->right != nullptr){
			stream<<spaceCounter(tab) << "R: ";
			printHelper(tab, elem->right, stream);
		}
	}
}

template<typename StreamType>
void print(StreamType& stream) const{
	this->printHelper(0, root, stream);
}

};

template<typename KeyType, typename ValueType>
std::ostream& operator << (std::ostream& stream, BinarySearchTree<KeyType, ValueType> const& tree)
{
	
	tree.print(stream);
	return stream;
}
