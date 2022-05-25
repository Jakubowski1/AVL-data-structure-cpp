#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>
#include <iostream>
using namespace std;

template<typename KeyType, typename ValueType>
class AVLTree
{
	friend class AVLTree<ValueType, KeyType>;
	private:
	struct AVL{
		KeyType key;
		ValueType value;
		AVL* right;
		AVL* left;
		int height;

		AVL(KeyType key, ValueType value){
			this->key = key;
			this->value = value;
			height = 0;
			right = nullptr;
			left = nullptr;
		}
		int BF()			//similar to newHeight()
	{

		int leftH, rightH;
		if(this->left == nullptr){
			leftH = -1;
		}else{
			leftH = left->height;
		}
		if(this->right== nullptr){
			rightH = -1;
		}else{
			rightH = right->height;
		}

		return leftH-rightH;
	}

	};
	AVL* root;
	size_t sizeCount = 0;
	
	
	string spaceCount(int tab) const{
		string spaces = "";
		for(int i= 0; i<tab;i++){
			spaces += "    ";
		}
		return spaces;
	}

	AVL* insert2(AVL* elem, KeyType const& k, ValueType const& v)
{
	
    if (elem == nullptr) {
		AVL* newElem = new AVL(k,v);
			return newElem;
		}
		if (k > elem->key) {
			elem->right = insert2(elem->right, k, v);
		}
		else if (k < elem->key) {
			elem->left = insert2(elem->left, k,v);
		}
		else {
			elem->value=v;
			sizeCount--;
			return elem;
        }

        newHeight(elem);
		return balance(elem);
}

AVL* balance(AVL* temp){
	if (temp->BF() > 1) 
	  {
            if (temp->left->BF() == -1) {
                temp->left =  left_rot(temp->left);
            }
            return right_rot(temp);
		}
        else if (temp->BF() < -1) {
            if (temp->right->BF()  == 1) {
                temp->right = right_rot(temp->right);
            }
            return left_rot(temp);
		}
		return temp;
}
void newHeight(AVL* elem){
	if(elem == nullptr){
	return;
	}
	int leftH, rightH;
	if(elem->left == nullptr){
		leftH = -1;
	}else{
		leftH = elem->left->height;
	}
	if(elem->right== nullptr){
		rightH = -1;
	}else{
		rightH = elem->right->height;
	}
	if(rightH>leftH){
		elem->height = rightH+1;
	}else{
		elem->height = leftH+1;
	}
}
AVL* right_rot(AVL* temp) {
        AVL* left = temp->left;
		//cutting the root off
        temp->left = left->right;
		//root placed on the right side
        left->right = temp;

		
        newHeight(temp->left);
        newHeight(left->right);
		newHeight(left);
        
        return left;
    }
AVL*  left_rot(AVL* temp) {
        AVL* right = temp->right;
		//cutting the root off
        temp->right = right->left;
		//root placed on the left side
        right->left = temp;

		
        newHeight(temp->right);
        newHeight(right->left);
		newHeight(right);
        return right;
    }

public:
AVLTree(){
    root = nullptr;
    sizeCount = 0;
}

bool empty() const{
    return root == nullptr;
}
void insert(KeyType const& k, ValueType const& v){
	root = insert2(root, k, v);
	sizeCount++;
}


ValueType* find(KeyType const& k){
    bool correct = false;
    AVL* temp = root;
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
//UNNECESSERY?
// unsigned int height(AVL* elem) const
// 	{
// 		if (elem == nullptr){
// 		return 0;
// 		}else{
// 		return elem->height;
// 		}
// 	}

size_t size() const{
    return sizeCount;
}

void clear(AVL* first)
{
    if (first != nullptr)
    {
        clear(first->left);
        clear(first->right);
        delete first;
    }
	sizeCount = 0;
}

~AVLTree()
{
    clear(root);
}
								

	std::string strHelper(AVL* temp) const{
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
	void printHelper(unsigned int tab, AVL* elem, StreamType& stream) const{
		if(!elem) return;
		if(elem != nullptr){
			stream << "[" << elem->key << ", " << elem->value << "]\n";
			tab++;
			if(elem->left != nullptr){
				stream<< spaceCount(tab)<< "L: ";
				printHelper(tab, elem->left, stream);
			}
			if(elem->right != nullptr){
				stream<<spaceCount(tab) << "R: ";
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
std::ostream& operator <<(std::ostream& stream, AVLTree<KeyType, ValueType> const& tree)
{
	tree.template print<std::ostream>(stream);
	return stream;
}

