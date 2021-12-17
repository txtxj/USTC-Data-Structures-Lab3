#include <iomanip>
#include <iostream>
#include <cstddef>
#include <cmath>
#include "FibHeap.h"

template <class T>
FibHeap<T>::FibHeap()
{
	keyNum = 0;
	min = NULL;
	cons = NULL;
}


template <class T>
FibHeap<T>::~FibHeap()
{
}


template <class T>
void FibHeap<T>::RemoveNode(FibNode<T> *node)
{
	node -> left -> right = node -> right;
	node -> right -> left = node -> left;
}


template <class T>
void FibHeap<T>::AddNode(FibNode<T> *node, FibNode<T> *root)
{
	node -> left = root -> left;
	root -> left -> right = node;
	node -> right = root;
	root -> left = node;
}


template <class T>
void FibHeap<T>::Insert(FibNode<T> *node)
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
void FibHeap<T>::Insert(T key, int k)
{
	FibNode<T> *node;
	node = new FibNode<T>(key);
	hash[k] = node;
	if (node == NULL)
		return ;
	Insert(node);
}


template <class T>
void FibHeap<T>::CatList(FibNode<T> *a, FibNode<T> *b)
{
	FibNode<T> *tmp;
	tmp = a -> right;
	a -> right = b -> right;
	b -> right -> left = a;
	b -> right = tmp;
	tmp -> left = b;
}


template <class T>
FibNode<T>* FibHeap<T>::ExtractMin()
{
	FibNode<T> *p = min;
	if (p == p -> right)
	{
		min = NULL;
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
void FibHeap<T>::Link(FibNode<T>* node, FibNode<T>* root)
{
	RemoveNode(node);
	if (root -> child == NULL)
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
		cons[i] = NULL;
	}
	while (min != NULL)
	{
		x = ExtractMin();
		d = x -> degree;
		while (cons[d] != NULL)
		{
			y = cons[d];
			if (x -> key > y -> key)
			{
				std::swap(x, y);
			}
			Link(y, x);
			cons[d] = NULL;
			d++;
		}
		cons[d] = x;
	}
	min = NULL;
	for (int i = 0; i < maxDegree; i++)
	{
		if (cons[i] != NULL)
		{
			if (min == NULL)
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
	if (min == NULL) return;
	FibNode<T> *child = NULL;
	FibNode<T> *m = min;
	while (m -> child != NULL)
	{
		child = m -> child;
		RemoveNode(child);
		if (child -> right == child)
		{
			m -> child = NULL;
		}
		else
		{
			m -> child = child -> right;
		}
		AddNode(child, min);
		child -> parent = NULL;
	}
	RemoveNode(m);
	if (m -> right == m)
	{
		min = NULL;
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
T FibHeap<T>::Minimum()
{
	return min -> key;
}


template <class T>
void FibHeap<T>::Cut(FibNode<T> *node, FibNode<T> *parent)
{
	RemoveNode(node);
	parent -> degree--;
	if (node == node -> right)
	{
		parent -> child = NULL;
	}
	else
	{
		parent -> child = node -> right;
	}
	node -> parent = NULL;
	node -> left = node -> right = node;
	node -> marked = false;
	AddNode(node, min);
}


template <class T>
void FibHeap<T>::CascadingCut(FibNode<T> *node)
{
	FibNode<T> *parent = node -> parent;
	if (parent != NULL)
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
void FibHeap<T>::Update(int k, T key)
{
	FibNode<T> *node = hash[k];
	FibNode<T> *parent;
	if (min == NULL || node == NULL) return;
	node -> key = key;
	parent = node -> parent;
	if (parent != NULL && node -> key < parent -> key)
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
bool FibHeap<T>::Empty()
{
	return min == NULL;
}

template <class T>
void FibHeap<T>::MakeHash(int n)
{
	hash = new FibNode<T>*[n];
	cons = new FibNode<T>*[int(log(n) / log(2.0)) + 2];
}
