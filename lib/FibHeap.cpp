#include <iomanip>
#include <iostream>
#include <cmath>
#include "FibHeap.h"

template <class T>
FibNode<T>::FibNode(const T& value)
{
	key = value;
	degree = 0;
	left = right = this;
	child = parent = nullptr;
	marked = false;
}


template <class T>
FibHeap<T>::FibHeap()
{
	keyNum = 0;
	min = nullptr;
	cons = nullptr;
}


template <class T>
FibHeap<T>::~FibHeap()
{
}


template <class T>
void FibHeap<T>::RemoveNode(FibNode<T>* node) const
{
	node -> left -> right = node -> right;
	node -> right -> left = node -> left;
}


template <class T>
void FibHeap<T>::AddNode(FibNode<T>* node, FibNode<T>* root) const
{
	node -> left = root -> left;
	root -> left -> right = node;
	node -> right = root;
	root -> left = node;
}


template <class T>
void FibHeap<T>::Insert(FibNode<T>* node)
{
	if (keyNum == 0)
	{
		min = node;
	}
	else
	{
		AddNode(node, min);
		if (node -> key < min -> key)
		{
			min = node;
		}
	}
	keyNum++;
}


template <class T>
void FibHeap<T>::Insert(const T& key, const int k)
{
	auto node = new FibNode<T>(key);
	hash[k] = node;
	if (node == nullptr)
		return;
	Insert(node);
}


template <class T>
FibNode<T>* FibHeap<T>::ExtractMin()
{
	auto p = min;
	if (p == p -> right)
	{
		min = nullptr;
	}
	else
	{
		RemoveNode(p);
		min = p -> right;
	}
	p -> left = p -> right = p;
	return p;
}


template <class T>
void FibHeap<T>::Link(FibNode<T>* node, FibNode<T>* root) const
{
	RemoveNode(node);
	if (root -> child == nullptr)
	{
		root -> child = node;
	}
	else
	{
		AddNode(node, root -> child);
	}
	node -> parent = root;
	root -> degree++;
	node -> marked = false;
}



template <class T>
void FibHeap<T>::Consolidate()
{
	int d, maxDegree;
	FibNode<T> *x, *y;
	maxDegree = (std::log(keyNum) / std::log(2.0)) + 2;
	for (int i = 0; i < maxDegree; i++)
	{
		cons[i] = nullptr;
	}
	while (min != nullptr)
	{
		x = ExtractMin();
		d = x -> degree;
		while (cons[d] != nullptr)
		{
			y = cons[d];
			if (x -> key > y -> key)
			{
				std::swap(x, y);
			}
			Link(y, x);
			cons[d] = nullptr;
			d++;
		}
		cons[d] = x;
	}
	min = nullptr;
	for (int i = 0; i < maxDegree; i++)
	{
		if (cons[i] != nullptr)
		{
			if (min == nullptr)
			{
				min = cons[i];
			}
			else
			{
				AddNode(cons[i], min);
				if (cons[i] -> key < min -> key)
				{
					min = cons[i];
				}
			}
		}
	}
}


template <class T>
void FibHeap<T>::RemoveMin()
{
	if (min == nullptr) return;
	FibNode<T> *child = nullptr;
	FibNode<T> *m = min;
	while (m -> child != nullptr)
	{
		child = m -> child;
		RemoveNode(child);
		if (child -> right == child)
		{
			m -> child = nullptr;
		}
		else
		{
			m -> child = child -> right;
		}
		AddNode(child, min);
		child -> parent = nullptr;
	}
	RemoveNode(m);
	if (m -> right == m)
	{
		min = nullptr;
	}
	else
	{
		min = m -> right;
		Consolidate();
	}
	keyNum--;
	delete m;
}


template <class T>
const T FibHeap<T>::Minimum() const
{
	return min -> key;
}


template <class T>
void FibHeap<T>::Cut(FibNode<T>* node, FibNode<T>* parent) const
{
	RemoveNode(node);
	parent -> degree--;
	if (node == node -> right)
	{
		parent -> child = nullptr;
	}
	else
	{
		parent -> child = node -> right;
	}
	node -> parent = nullptr;
	node -> left = node -> right = node;
	node -> marked = false;
	AddNode(node, min);
}


template <class T>
void FibHeap<T>::CascadingCut(FibNode<T>* node) const
{
	auto parent = node -> parent;
	if (parent != nullptr)
	{
		if (node -> marked == false)
		{
			node -> marked = true;
		}
		else
		{
			Cut(node, parent);
			CascadingCut(parent);
		}
	}
}


template <class T>
void FibHeap<T>::Update(const int k, const T& key)
{
	auto node = hash[k];
	if (min == nullptr || node == nullptr) return;
	node -> key = key;
	auto parent = node -> parent;
	if (parent != nullptr && node -> key < parent -> key)
	{
		Cut(node, parent);
		CascadingCut(parent);
	}
	if (node -> key < min -> key)
	{
		min = node;
	}
}

template <class T>
const bool FibHeap<T>::Empty() const
{
	return min == nullptr;
}

template <class T>
void FibHeap<T>::MakeHash(const int n)
{
	hash = new FibNode<T>*[n];
	cons = new FibNode<T>*[int(log(n) / log(2.0)) + 2];
}
