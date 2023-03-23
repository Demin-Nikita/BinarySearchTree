#pragma once
#include <iostream>
#include "LimitedStack.h"
#include "LimitedQueue.h"
#include "Stack.h"
#include "Queue.h"

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& src) = delete;
	BinarySearchTree(BinarySearchTree<T>&& src) noexcept;
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;
	~BinarySearchTree();

	// Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T& key) const;
	// Вставка нового элемента в дерево: true, если элемент добавлен; false, если элемент уже был
	bool insert(const T& key);
	// Удаление элемента из дерева, не нарушающее порядка элементов. true, если элемент удален; false, если элемента не было
	bool deleteKey(const T& key);
	// Печать строкового изображения дерева в выходной поток out, используются скобки, чтобы показать структуру дерева
	void print(std::ostream& out) const;
	// Определение количества узлов дерева
	size_t getCount() const;
	// Определение высоты дерева
	int getHeight() const;
	// Инфиксный обход дерева (итеративный) 
	void iterativeInorderWalk() const;
	// Инфиксный обход дерева (рекурсивный) 
	void inorderWalk() const;
	// Обход двоичного дерева по уровням (в ширину). 
	void walkByLevels() const;
	// Являются ли два дерева похожими
	bool isSimilar(const BinarySearchTree<T>& other) const;
	// Есть одинаковые ключи в двух деревьях поиска
	bool isIdenticalKey(const BinarySearchTree<T>& other) const;
private:
	template <class T>
	struct Node {
		T key_;
		Node<T>* left_;
		Node<T>* right_;
		Node<T>* p_;
		
		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr):
			key_(key), left_(left), right_(right), p_(p)
		{}
		~Node() {
			if (left_) left_->~Node();
			if (right_) right_->~Node();
		}
	};
	// Функция поиска адреса узла по ключу в бинарном дереве поиска
	Node<T>* iterativeSearchNode(const T& key) const;
	// Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(std::ostream& out, Node<T>* root) const;
	// Рекурсивная функция определения количества узлов дерева
	size_t getCount(const Node<T>* node) const;
	// Рекурсивная функция определения высоты дерева
	int getHeight(const Node<T>* node) const;
	// Рекурсивная функция для инфиксного обхода узлов дерева.
	void inorderWalk(Node<T>* node) const;

	Node<T>* root_;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src) noexcept {
	if (root_ == src.root_) { return this; }
	std::swap(root_, src.root_);
	return this; 
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	root_->~Node();
}

template <class T>
BinarySearchTree <T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& src) noexcept {
	if (root_ == src.root_) { return this; }
	std::swap(root_, src.root_);
	return this;
}

template <class T>
bool BinarySearchTree<T>::insert(const T& key) {
	Node<T>* newNode = new Node<T>(key);
	if (root_ == nullptr) { root_ = newNode; }

	else {
		Node<T>* current = root_;
		while (current != nullptr) {
			if (key == current->key_) { return false; }
			else if (key < current->key_) {
				if (current->left_ == nullptr) {
					current->left_ = newNode;
					newNode->p_ = current;
					return true;
				}
				current = current->left_;
			}
			else {
				if (current->right_ == nullptr) {
					current->right_ = newNode;
					newNode->p_ = current;
					return true;
				}
				current = current->right_;
			}
		}
	}
	return false;
}

template <class T>
inline BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const {
	Node<T>* current = root_;
	while (current) {
		if (key < current->key_) {
			current = current->left_;
		}
		else if (key > current->key_) {
			current = current->right_;
		}
		else {
			return current;
		}
	}
	return nullptr;
}

template <class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key) const {
	Node<T>* current = root_;
	while (current) {
		if (key < current->key_) {
			current = current->left_;
		}
		else if (key > current->key_) {
			current = current->right_;
		}
		else {
			return true;
		}
	}
	return false;
}

template <class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const {
	if (root == nullptr) {
		out << std::endl;
		return;
	}
	
	out << root->key_;
	
	if (!root->left_ && !root->right_) { return; }

	else {
		out << '(';
		if (root->left_) { printNode(out, root->left_); }
		out << ')';

		out << '(';
		if (root->right_) { printNode(out, root->right_); }
		out << ')';
	}
}

template <class T>
void BinarySearchTree<T>::print(std::ostream& out) const { printNode(out, root_); }

template <class T>
size_t BinarySearchTree<T>::getCount(const Node<T>* node) const {
	if (node == nullptr) { return 0; }
	return (1 + getCount(node->left_) + getCount(node->right_));
}

template <class T>
size_t BinarySearchTree<T>::getCount() const { return getCount(this->root_); }

template<class T>
inline int BinarySearchTree<T>::getHeight(const Node<T>* node) const {
	if (!node->left_ && !node->right_) { return 1; }
	else if (!node->left_) { return getHeight(node->right_) + 1; }
	else if (!node->right_) { return getHeight(node->left_) + 1; }
	else { return std::max(getHeight(node->left_) + 1, getHeight(node->right_) + 1); }
}

template<class T>
inline int BinarySearchTree<T>::getHeight() const {
	return getHeight(root_);
}

template <class T>
bool BinarySearchTree<T>::deleteKey(const T& key) {
	Node<T>* xNode = iterativeSearchNode(key);

	if (xNode == nullptr) { return false; }

	else if (!xNode->left_ && !xNode->right_) {
		xNode->p_->key_ < xNode->key_ ? xNode->p_->right_ = nullptr : xNode->p_->left_ = nullptr;
		delete xNode;
	}
	else if (xNode->left_ && xNode->right_) {
		Node<T>* rightMn = xNode->right_;
		while (rightMn->left_ != nullptr) { rightMn = rightMn->left_; }
		xNode->key_ = rightMn->key_;
		rightMn->p_->key_ == xNode->key_ ? rightMn->p_->right_ = nullptr : rightMn->p_->left_ = nullptr;
		delete rightMn;
	}
	else {
		if (xNode->p_ == nullptr) { xNode->left_ ? root_ = xNode->left_ : root_ = xNode->right_; }
		else if (xNode->left_) { xNode->key_ < xNode->p_->key_ ? xNode->p_->left_ = xNode->left_ : xNode->p_->right_ = xNode->left_; }
		else { xNode->key_ < xNode->p_->key_ ? xNode->p_->left_ = xNode->right_ : xNode->p_->right_ = xNode->right_; }
		delete xNode;
	}
}

template <class T>
void BinarySearchTree<T>::inorderWalk(Node<T>* node) const {
	if (node) {
		this->inorderWalk(node->left_);
		std::cout << node->key_ << ' ';
		this->inorderWalk(node->right_);
	}
	return;
}

template <class T>
void BinarySearchTree<T>::inorderWalk() const {
	this->inorderWalk(root_);
}

template <class T>
void BinarySearchTree<T>::iterativeInorderWalk() const {
	if (root_ != nullptr) {
		LimitedStack<Node<T>*> stack(this->getCount());

		Node<T>* current = root_;
		stack.push(current);

		bool goLeftNext = true;

		while (!stack.isEmpty()) {
			if (goLeftNext) {
				while (current->left_ != nullptr) {
					stack.push(current);
					current = current->left_;
				}
			}

			std::cout << current->key_ << ' ';

			if (current->right_ != nullptr) {
				current = current->right_;
				goLeftNext = true;
			}
			else {
				current = stack.pop();
				goLeftNext = false;
			}
		}
	}
}

template <class T>
void BinarySearchTree<T>::walkByLevels() const {
	if (root_ == nullptr) { return; }

	LimitedQueue<Node<T>*> queue(getCount()/2);
	queue.enQueue(root_);

	Node<T>* current = nullptr;

	while (!queue.isEmpty()) {
		current = queue.deQueue();
		std::cout << current->key_ << ' ';

		if (current->left_) { queue.enQueue(current->left_); }
		if (current->right_) { queue.enQueue(current->right_); }
	}
}

template <class T>
bool BinarySearchTree<T>::isSimilar(const BinarySearchTree<T>& other) const {
	if (!root_ && !other.root_) { return true; }
	else if (this->getCount() == other.getCount()) {
		LimitedQueue<Node<T>*> queue(getCount() / 2);
		queue.enQueue(root_);

		Node<T>* current = nullptr;

		while (!queue.isEmpty()) {
			current = queue.deQueue();
			if (!iterativeSearch(current->key_)) { return false; }

			if (current->left_) { queue.enQueue(current->left_); }
			if (current->right_) { queue.enQueue(current->right_); }
		}
	}
	else { return false; }

	return true;
}

template <class T>
bool BinarySearchTree<T>::isIdenticalKey(const BinarySearchTree<T>& other) const {
	if (!root_ || !other.root_) { return false; }
	else {
		LimitedQueue<Node<T>*> queue(getCount() / 2);
		queue.enQueue(root_);

		Node<T>* current = nullptr;

		while (!queue.isEmpty()) {
			current = queue.deQueue();
			if (iterativeSearch(current->key_)) { return true; }

			if (current->left_) { queue.enQueue(current->left_); }
			if (current->right_) { queue.enQueue(current->right_); }
		}
	}

	return false;
}