
#include<iostream>
#include<fstream>
#include<algorithm>

/**@brief templated class to form Nodes

	This class forms nodes to keep track of the data in the tree and to keep track of where in the tree
	it is located
*/

template<typename T, typename CMP=std::less<T>>
class TreeNode{
public:
	TreeNode();
	TreeNode(T);
	TreeNode(const TreeNode<T,CMP>&);
	void insert_node(TreeNode<T,CMP>* node);

private:
	T val;
	CMP isless;
	TreeNode<T,CMP>* left;
	TreeNode<T,CMP>* right;
	TreeNode<T,CMP>* parent;

	template<typename T,typename CMP>
	friend class BinarySearchTree;

	template<typename T,typename CMP>
	friend class TreeIterator;
};

/**@brief templated class to form a BinarySearchTree
	
	This class stores ints in the form of a tree. It keeps track of the root node, which latches 
	on to the other nodes
*/
template<typename T, typename CMP=std::less<T>>
class BinarySearchTree{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T,CMP>&);
	void insert(T);
//	void erase(T);
	T smallest();
	T largest();
	typename TreeIterator<T,CMP> begin();
	typename TreeIterator<T,CMP> end();
	void descend(TreeNode<T,CMP>* n);

	virtual ~BinarySearchTree(){//BinarySearchTree destructor
			this->descend(this->root);
	};


private:
	TreeNode<T,CMP>* root;

	template <typename T, typename CMP> friend class TreeNode;
	template<typename T,typename CMP> friend class TreeIterator;
};
/**
	This is a recursive function that visits each node in the binary tree and deletes them; we will use this with the destructor

	@param n is the TreeNode being recursed on then deleted
*/
template<typename T, typename CMP> void BinarySearchTree<T,CMP>::descend(TreeNode<T,CMP>* n){
	if(n==nullptr)
		return;
	descend(n->left);
	descend(n->right);
	delete n;
}

/**@brief templated class to form Iterators

	This class forms a TreeIterator, which keeps track of which node is being pointed to,
	as well as which BinarySearchTree it is pointng to
*/
template<typename T, typename CMP=std::less<T>>
class TreeIterator{
public:
	TreeIterator();
	TreeIterator(BinarySearchTree<T,CMP>*);
	TreeIterator(TreeNode<T,CMP>*,BinarySearchTree<T,CMP>*);
//	TreeIterator(TreeIterator<T,CMP> t);
	TreeIterator& operator++();
	TreeIterator operator++(int unused);
	TreeIterator& operator--();
	TreeIterator operator--(int unused);
	bool operator!=(TreeIterator);
	bool operator==(TreeIterator);
	T operator*();

private:
	TreeNode<T,CMP>* position;
	BinarySearchTree<T,CMP>* container;

	template<typename T, typename CMP> friend class TreeNode;
	template<typename T,typename CMP> friend class BinarySearchTree;
};
template<typename InputIterator> void print(InputIterator a, InputIterator b);
//template<typename T> std::ostream operator<<(ostream& out, T t);



/**
	This is the default constructor for the TreeNode class. It sets the different pointers to nullptr and the val to zero
*/
template<typename T, typename CMP> TreeNode<T,CMP>::TreeNode():val(0), left(nullptr), right(nullptr), parent(nullptr){};
/**
	This is the overloaded constructor for the TreeNode class. It sets the different pointers to nullptr and the val to the input
	@param data is the input for the new val
*/
template<typename T, typename CMP> TreeNode<T,CMP>::TreeNode(T data):val(data), left(nullptr), right(nullptr), parent(nullptr){};
/**
	This is the copy constructor for the TreeNode class.
	@param N is the TreeNode being copied
*/
template<typename T, typename CMP> TreeNode<T,CMP>::TreeNode(const TreeNode<T,CMP>& N):val(N.val),left(N.left),right(N.right),parent(N.parent),isless(N.isless){};

/**
	This function inserts a Node into the BinarySearchTree

	@param Node is the Node being inserted
*/
template<typename T,typename CMP> void TreeNode<T,CMP>::insert_node(TreeNode<T,CMP>* node){
	if(isless(node->val,val)){
		if(left==nullptr){
			left=node;
			node->parent=this;
		}
		else left->insert_node(node);
	}
	else if(isless(val,node->val)){
		if(right==nullptr){
			right=node;
			node->parent=this;
		}
		else right->insert_node(node);
	}
}

template<typename T, typename CMP> BinarySearchTree<T,CMP>::BinarySearchTree():root(nullptr){};
template<typename T, typename CMP> BinarySearchTree<T,CMP>::BinarySearchTree(const BinarySearchTree<T,CMP>& b){
	try{
		root=new *b.root;
	}
	catch(std::exception e){
		if(root){
			delete root;
			root=nullptr;
		}
		std::cerr<<"failed to allocate";
	}
}
/**
	This function inserts a value into the BinarySearchTree

	@param t is the value being inserted
*/
template<typename T, typename CMP> void BinarySearchTree<T,CMP>::insert(T t){
	if(root==nullptr){
		root=new TreeNode<T,CMP> (t);
		return;
	}
	TreeNode<T,CMP>* nod=new TreeNode<T,CMP>(t);
	root->insert_node(nod);
};

/**
	This function returns an iterator pointing to the first element in the tree

	@return the iterator pointing to the first element
*/
template<typename T, typename CMP> TreeIterator<T,CMP> BinarySearchTree<T,CMP>::begin(){
	TreeIterator<T,CMP> it(this->root,this);
	while(it.position->left!=nullptr)
		it.position=it.position->left;
	return it;
}

/**
	This function returns an iterator pointing to one after the last element in the tree

	@return the iterator pointing to the one after the last element
*/
template<typename T, typename CMP> TreeIterator<T,CMP> BinarySearchTree<T,CMP>::end(){
	TreeIterator<T,CMP> it(this->root, this);
	while(it.position->right!=nullptr)
		++it;
	it.position=it.position->right;	
	return it;
}
/**
	This function returns an iterator pointing to the largest element in the tree

	@return the iterator pointing to the largest element
*/
template<typename T, typename CMP> T BinarySearchTree<T,CMP>::largest(){
	TreeIterator<T,CMP> it(this->root,this);
	while(it.position->right!=nullptr)
		it.position=it.position->right;
	return it.position->val;
};
/** This is the default constructor of the TreeIterator class, it sets the position and container to nullptr
*/
template<typename T, typename CMP> TreeIterator<T,CMP>::TreeIterator():position(nullptr), container(nullptr){};

/** This is the overloaded constructor of the TreeIterator class
	@param t is the TreeNode the Iterator is pointing to
	@param b is the BinarySearchTree the Iterator is a part of
*/
template<typename T, typename CMP> TreeIterator<T,CMP>::TreeIterator(TreeNode<T,CMP>* t, BinarySearchTree<T,CMP>* b):position(t), container(b){};

/** This is the overloaded constructor of the TreeIterator class
	@param b is the BinarySearchTree the Iterator is a part of, the TreeIterator then points to the root node of b
*/
template<typename T, typename CMP> TreeIterator<T,CMP>::TreeIterator(BinarySearchTree<T,CMP>* b):position(b->root), container(b){};

/*template<typename T, typename CMP> TreeIterator<T,CMP>::TreeIterator(TreeIterator<T,CMP> t){
	position=new TreeNode<T,CMP>(t->position);
	container=new BinarySearchTree<T,CMP>(t->container);
}*/
/**
	This function prints out the dereferenced iterators

	@param a is the begin iterator
	@param b is the end iterator
*/
template<typename InputIterator> void print(InputIterator a, InputIterator b){
	while(a!=b){
		cout<<*a++<<",";
	}
};
/**
	This is the overloaded prefix ++ operator that moves the TreeIterator to point to the next largest element 
	@return the modified Iterator
*/
template<typename T,typename CMP> TreeIterator<T,CMP>& TreeIterator<T,CMP>::operator++(){
	if(this->position->val==this->container->largest()){
		this->position=this->position->right;
		return *this;
	}
	if(this->position->right!=nullptr){
		this->position=this->position->right;
		while (this->position->left!=nullptr)
			this->position=this->position->left;
	}
	else if(this->position->parent!=nullptr){
		while((this->position->parent!=nullptr)&&(this->position!=this->position->parent->left))
			this->position=this->position->parent;
		if(this->position==this->container->root)
			return *this;
		this->position=this->position->parent;			
	}
	return *this;
}
/**
	This is the overloaded postfix ++ operator that moves the TreeIterator to point to the next largest element 
	@param unused is a parameter to distinguish this function from the prefix operator
	@return the a copy of the Iterator before it was modified
*/
template<typename T,typename CMP> TreeIterator<T,CMP> TreeIterator<T,CMP>::operator++(int unused){
	TreeIterator<T,CMP> t(position,container);
	if(this->position->right!=nullptr){
		this->position=this->position->right;
		while (this->position->left!=nullptr)
			this->position=this->position->left;
	}
	else if(this->position->parent!=nullptr){
		while((this->position!=this->position->parent->left)&&(this->position->parent!=nullptr))
			this->position=this->position->parent;
			if(this->position->parent==this->container->root){
				this->position=this->position->parent;
				return *this;
			}
		this->position=this->position->parent;		
	}
	return t;
}

/**
	This is the overloaded * operator that dereferences the Iterator to the val of the Node it is pointing to
	@return the val of the TreeNode the TreeIterator is pointing to
*/
template<typename T,typename CMP> T TreeIterator<T,CMP>::operator*(){
	return this->position->val;
}
/**
	This is the overloaded != operator that compares two TreeIterators together
	@param it is the the second TreeIterator being compared
	@return a bool telling if the two Iterators are equal or not
*/
template<typename T,typename CMP> bool TreeIterator<T,CMP>::operator!=(TreeIterator it){
	if(this->position!=it.position)
		return true;
	return false;
}

/**
	This is the overloaded == operator that compares two TreeIterators together
	@param it is the the second TreeIterator being compared
	@return a bool telling if the two Iterators are equal or not
*/
template<typename T,typename CMP> bool TreeIterator<T,CMP>::operator==(TreeIterator){
	if(this->position==it.position)
		return true;
	return false;
}


/**
	This is the overloaded prefix -- operator that moves the TreeIterator to point to the next smallest element 
	@return the modified Iterator
*/
template<typename T,typename CMP> TreeIterator<T,CMP>& TreeIterator<T,CMP>::operator--(){
	if(this->position->val==this->container->smallest()){
		this->position=this->position->left;
		return *this;
	}
	if(this->position->left!=nullptr){
		this->position=this->position->left;
		while (this->position->right!=nullptr)
			this->position=this->position->right;
	}
	else if(this->position->parent!=nullptr){
		while((this->position->parent!=nullptr)&&(this->position!=this->position->parent->right))
			this->position=this->position->parent;
		if(this->position==this->container->root)
			return *this;
		this->position=this->position->parent;			
	}
	return *this;
}
/**
	This is the overloaded postfix -- operator that moves the TreeIterator to point to the next largest element 
	@param unused is a parameter to distinguish this function from the prefix operator
	@return the a copy of the Iterator before it was modified
*/
template<typename T,typename CMP> TreeIterator<T,CMP> TreeIterator<T,CMP>::operator--(int unused){
	TreeIterator<T,CMP> t(position,container);
	if(this->position->val==this->container->smallest()){
		this->position=this->position->left;
		return t;
	}
	if(this->position->left!=nullptr){
		this->position=this->position->left;
		while (this->position->right!=nullptr)
			this->position=this->position->right;
	}
	else if(this->position->parent!=nullptr){
		while((this->position->parent!=nullptr)&&(this->position!=this->position->parent->right))
			this->position=this->position->parent;
		if(this->position==this->container->root)
			return *this;
		this->position=this->position->parent;			
	}
	return t;
}



