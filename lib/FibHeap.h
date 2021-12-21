#ifndef FIBHEAP
#define FIBHEAP

template <class T>
class FibNode {
public:
	T key;					// 键值
	int degree;				// 度数
	FibNode<T> *left;		// 左兄弟
	FibNode<T> *right;		// 右兄弟
	FibNode<T> *child;		// 儿子链表头
	FibNode<T> *parent;		// 双亲
	bool marked;			// 标记是否已失去儿子
	FibNode(const T& value);
};

template <class T>
class FibHeap {
private:
	int keyNum;				// 结点个数
	FibNode<T> *min;		// 最小节点
	FibNode<T> **cons;		// Consolidate辅助空间
public:
	FibNode<T> **hash;		// 映射空间
public:
	FibHeap();
	~FibHeap();
	// 插入节点 k ，键值为 key
	void Insert(const T& key, const int k);
	// 删除最小值
	void RemoveMin();
	// 获取最小值
	const T Minimum() const;
	// 将 k 节点键值减小至 key
	void Update(const int k, const T& key);
	// 判断堆空
	const bool Empty() const;
	// 初始化辅助空间
	void MakeHash(const int);
private:
	// 删除节点
	void RemoveNode(FibNode<T>* node) const;
	// 添加节点到指定位置
	void AddNode(FibNode<T>* node, FibNode<T>* root) const;
	// 插入节点
	void Insert(FibNode<T>* node);
	// 摘取 min 指向的节点
	FibNode<T>* ExtractMin();
	// 合并两树
	void Link(FibNode<T>* node, FibNode<T>* root) const;
	// 维护最小值
	void Consolidate();
	// 切断
	void Cut(FibNode<T>* node, FibNode<T>* parent) const;
	// 级联切断
	void CascadingCut(FibNode<T>* node) const;
};

#endif