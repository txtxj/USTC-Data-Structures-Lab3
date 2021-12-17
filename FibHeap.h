#pragma once

template <class T>
class FibNode {
public:
	T key;
	int degree;
	FibNode<T> *left;
	FibNode<T> *right;
	FibNode<T> *child;
	FibNode<T> *parent;
	bool marked;
	FibNode(T value) : key(value), degree(0), left(this), right(this), child(NULL), parent(NULL), marked(false){}
};

template <class T>
class FibHeap {
private:
	int keyNum;
	FibNode<T> *min;
	FibNode<T> **cons;
	FibNode<T> **hash;

public:
	FibHeap();
	~FibHeap();
	void Insert(T, int);
	void RemoveMin();
	T Minimum(void);
	void Update(int, T);
	bool Empty(void);
	void MakeHash(int);
private:
	void RemoveNode(FibNode<T>*);
	void AddNode(FibNode<T>*, FibNode<T>*);
	void CatList(FibNode<T>*, FibNode<T>*);
	void Insert(FibNode<T>*);
	FibNode<T>* ExtractMin(void);
	void Link(FibNode<T>*, FibNode<T>*);
	void Consolidate(void);
	void Cut(FibNode<T>*, FibNode<T>*);
	void CascadingCut(FibNode<T>*) ;
};