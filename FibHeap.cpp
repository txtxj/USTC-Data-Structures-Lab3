/**
 * C++: 斐波那契堆
 *
 * @author skywang
 * @date 2014/04/06
 */

#ifndef _FIBONACCI_TREE_HPP_
#define _FIBONACCI_TREE_HPP_

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <class T>
class FibNode {
    public:
        T key;                // 关键字(键值)
        int degree;            // 度数
        FibNode<T> *left;    // 左兄弟
        FibNode<T> *right;    // 右兄弟
        FibNode<T> *child;    // 第一个孩子节点
        FibNode<T> *parent;    // 父节点
        bool marked;        // 是否被删除第一个孩子

        FibNode(T value):key(value), degree(0), left(this),right(this),child(NULL),parent(NULL), marked(false){}
};

template <class T>
class FibHeap {
    private:
        int keyNum;         // 堆中节点的总数
        int maxDegree;      // 最大度
        FibNode<T> *min;    // 最小节点(某个最小堆的根节点)
        FibNode<T> **cons;    // 最大度的内存区域
        FibNode<T> **hash;

    public:
        FibHeap();
        ~FibHeap();

        // 新建key对应的节点，并将其插入到斐波那契堆中
        void insert(T key, int k);
        // 移除斐波那契堆中的最小节点
        void removeMin();
        // 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
        T minimum(void);
        // 将斐波那契堆中键值oldkey更新为newkey
        void update(int k, T newkey);

        bool empty();

        void makeHash(int);

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
        // 将node从父节点parent的子链接中剥离出来，并使node成为"堆的根链表"中的一员。
        void cut(FibNode<T> *node, FibNode<T> *parent);
        // 对节点node进行"级联剪切"
        void cascadingCut(FibNode<T> *node) ;
        // 将斐波那契堆中节点node的值减少为key
        void decrease(FibNode<T> *node, T key);
        // 更新斐波那契堆的节点node的键值为key
        void update(FibNode<T> *node, T key);
};

/*
 * 构造函数
 */
template <class T>
FibHeap<T>::FibHeap()
{
    keyNum = 0;
    maxDegree = 0;
    min = NULL;
    cons = NULL;
}

/*
 * 析构函数
 */
template <class T>
FibHeap<T>::~FibHeap()
{
}

/*
 * 将node从双链表移除
 */
template <class T>
void FibHeap<T>::removeNode(FibNode<T> *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

/*
 * 将node堆结点加入root结点之前(循环链表中)
 *   a …… root
 *   a …… node …… root
*/
template <class T>
void FibHeap<T>::addNode(FibNode<T> *node, FibNode<T> *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

/*
 * 将节点node插入到斐波那契堆中
 */
template <class T>
void FibHeap<T>::insert(FibNode<T> *node)
{
    if (keyNum == 0)
        min = node;
    else
       {
        addNode(node, min);
        if (node->key < min->key)
            min = node;
    }
    keyNum++;
}

/*
 * 新建键值为key的节点，并将其插入到斐波那契堆中
 */
template <class T>
void FibHeap<T>::insert(T key, int k)
{
    FibNode<T> *node;

    node = new FibNode<T>(key);
    hash[k] = node;
    if (node == NULL)
        return ;

    insert(node);
}

/*
 * 将双向链表b链接到双向链表a的后面
 *
 * 注意： 此处a和b都是双向链表
 */
template <class T>
void FibHeap<T>::catList(FibNode<T> *a, FibNode<T> *b)
{
    FibNode<T> *tmp;

    tmp            = a->right;
    a->right       = b->right;
    b->right->left = a;
    b->right       = tmp;
    tmp->left      = b;
}

/*
 * 将"堆的最小结点"从根链表中移除，
 * 这意味着"将最小节点所属的树"从堆中移除!
 */
template <class T>
FibNode<T>* FibHeap<T>::extractMin()
{
    FibNode<T> *p = min;

    if (p == p->right)
        min = NULL;
    else
    {
        removeNode(p);
        min = p->right;
    }
    p->left = p->right = p;

    return p;
}

/*
 * 将node链接到root根结点
 */
template <class T>
void FibHeap<T>::link(FibNode<T>* node, FibNode<T>* root)
{
    // 将node从双链表中移除
    removeNode(node);
    // 将node设为root的孩子
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

/*
 * 创建consolidate所需空间
 */
template <class T>
void FibHeap<T>::makeCons()
{
    int old = maxDegree;

    // 计算log2(keyNum)，"+1"意味着向上取整！
    // ex. log2(13) = 3，向上取整为3+1=4。
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;

    // 因为度为maxDegree可能被合并，所以要maxDegree+1
    cons = (FibNode<T> **)realloc(cons,
            sizeof(FibHeap<T> *) * (maxDegree + 1));
}

/*
 * 合并斐波那契堆的根链表中左右相同度数的树
 */
template <class T>
void FibHeap<T>::consolidate()
{
    int i, d, D;
    FibNode<T> *x, *y;

    makeCons();//开辟哈希所用空间
    D = maxDegree + 1;

    for (i = 0; i < D; i++)
        cons[i] = NULL;

    // 合并相同度的根节点，使每个度数的树唯一
    while (min != NULL)
    {
        x = extractMin();                // 取出堆中的最小树(最小节点所在的树)
        d = x->degree;                    // 获取最小树的度数
        // cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
        while (cons[d] != NULL)
        {
            y = cons[d];                // y是"与x的度数相同的树"
            if (x->key > y->key)        // 保证x的键值比y小
                swap(x, y);

            link(y, x);    // 将y链接到x中
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    min = NULL;

    // 将cons中的结点重新加到根表中
    for (i=0; i<D; i++)
    {
        if (cons[i] != NULL)
        {
            if (min == NULL)
                min = cons[i];
            else
            {
                addNode(cons[i], min);
                if ((cons[i])->key < min->key)
                    min = cons[i];
            }
        }
    }
}

/*
 * 移除最小节点
 */
template <class T>
void FibHeap<T>::removeMin()
{
    if (min==NULL)
        return ;

    FibNode<T> *child = NULL;
    FibNode<T> *m = min;
    // 将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
    while (m->child != NULL)
    {
        child = m->child;
        removeNode(child);
        if (child->right == child)
            m->child = NULL;
        else
            m->child = child->right;

        addNode(child, min);
        child->parent = NULL;
    }

    // 将m从根链表中移除
    removeNode(m);
    // 若m是堆中唯一节点，则设置堆的最小节点为NULL；
    // 否则，设置堆的最小节点为一个非空节点(m->right)，然后再进行调节。
    if (m->right == m)
        min = NULL;
    else
    {
        min = m->right;
        consolidate();
    }
    keyNum--;

    delete m;
}

/*
 * 获取斐波那契堆中最小键值，并保存到pkey中；成功返回true，否则返回false。
 */
template <class T>
T FibHeap<T>::minimum()
{
    return min -> key;
}


/*
 * 将node从父节点parent的子链接中剥离出来，
 * 并使node成为"堆的根链表"中的一员。
 */
template <class T>
void FibHeap<T>::cut(FibNode<T> *node, FibNode<T> *parent)
{
    removeNode(node);
    parent->degree--;
    // node没有兄弟
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = false;
    // 将"node所在树"添加到"根链表"中
    addNode(node, min);
}

/*
 * 对节点node进行"级联剪切"
 *
 * 级联剪切：如果减小后的结点破坏了最小堆性质，
 *     则把它切下来(即从所在双向链表中删除，并将
 *     其插入到由最小树根节点形成的双向链表中)，
 *     然后再从"被切节点的父节点"到所在树根节点递归执行级联剪枝
 */
template <class T>
void FibHeap<T>::cascadingCut(FibNode<T> *node)
{
    FibNode<T> *parent = node->parent;
    if (parent != NULL)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

/*
 * 将斐波那契堆中节点node的值减少为key
 */
template <class T>
void FibHeap<T>::decrease(FibNode<T> *node, T key)
{
    FibNode<T> *parent;

    if (min==NULL ||node==NULL)
        return ;

    node->key = key;
    parent = node->parent;
    if (parent!=NULL && node->key < parent->key)
    {
        // 将node从父节点parent中剥离出来，并将node添加到根链表中
        cut(node, parent);
        cascadingCut(parent);
    }

    // 更新最小节点
    if (node->key < min->key)
        min = node;
}


/*
 * 更新斐波那契堆的节点node的键值为key
 */
template <class T>
void FibHeap<T>::update(FibNode<T> *node, T key)
{
    if(key < node->key)
        decrease(node, key);
}


template <class T>
void FibHeap<T>::update(int k, T newkey)
{
    FibNode<T> *node;

    node = hash[k];
    if (node!=NULL)
        update(node, newkey);
}

template <class T>
bool FibHeap<T>::empty()
{
    return min==NULL;
}

template <class T>
void FibHeap<T>::makeHash(int n)
{
    hash = new FibNode<T>*[n];
}

#endif