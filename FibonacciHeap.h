#pragma once

template <typename T>
class FibHeap {
private:
    template <typename S>
	class FibNode
	{
    public:
        S key;
        int degree;
        FibNode<S> *left;
        FibNode<S> *right;
        FibNode<S> *child;
        FibNode<S> *parent;
        bool marked;
	};

    int keyNum;
    int maxDegree;
    FibNode<T> *min;
    FibNode<T> **cons;
public:
    FibHeap();
    ~FibHeap();
    void insert(T key);
    void removeMin(void);
    T* minimum(void);

private:
    // 将node从双链表移除
    void removeNode(FibNode<T> *node);
    // 将node堆结点加入root结点之前(循环链表中)
    void addNode(FibNode<T> *node, FibNode<T> *root);
    // 将双向链表b链接到双向链表a的后面
    void catList(FibNode<T> *a, FibNode<T> *b);
    // 将节点node插入到斐波那契堆中
    void insert(FibNode<T> *node);
    // 将"堆的最小结点"从根链表中移除，
    FibNode<T>* extractMin();
    // 将node链接到root根结点
    void link(FibNode<T>* node, FibNode<T>* root);
    // 创建consolidate所需空间
    void makeCons();
    // 合并斐波那契堆的根链表中左右相同度数的树
    void consolidate();
    // 修改度数
    void renewDegree(FibNode<T> *parent, int degree);
    // 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
    void cut(FibNode<T> *node, FibNode<T> *parent);
    // 对节点node进行"级联剪切"
    void cascadingCut(FibNode<T> *node) ;
    // 将斐波那契堆中节点node的值减少为key
    void decrease(FibNode<T> *node, T key);
    // 将斐波那契堆中节点node的值增加为key
    void increase(FibNode<T> *node, T key);
    // 更新斐波那契堆的节点node的键值为key
    void update(FibNode<T> *node, T key);
    // 在最小堆root中查找键值为key的节点
    FibNode<T>* search(FibNode<T> *root, T key);
    // 在斐波那契堆中查找键值为key的节点
    FibNode<T>* search(T key);
    // 删除结点node
    void remove(FibNode<T> *node);
    // 销毁斐波那契堆
    void destroyNode(FibNode<T> *node);
};