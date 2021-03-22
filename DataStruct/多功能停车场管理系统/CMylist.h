#include<iostream>
#include <iomanip>
using std::setw;
using namespace std;

//链表结构体
template<typename T>
struct Node
{
	T data;
	Node* next;
};

template<typename T>
class LinkNode
{
public:
	Node<T>* head;
	int len;
public:
	LinkNode();
	~LinkNode();
	void inset(T elme);
	bool ListFind(string e, T& t);
	bool ListFind_only(string e);
	bool empty() const { return len == 0; }
	void selsesort();
	void displist();
	void clear();
private:
};

//链表的清除
template<typename T>
inline void LinkNode<T>::clear()
{
	if (head != nullptr)
	{

		Node<T>* pre = head, * p = head->next;
		while (p != nullptr)
		{
			delete[] pre;
			pre = p;
			p = pre->next;
		}
		head = nullptr;
		len = 0;
	}
}

//初始化链表、构造
template<typename T>
inline LinkNode<T>::LinkNode()
{
	head = new Node<T>;
	head->next = nullptr;
	len = 0;
}

//链表的析构
template<typename T>
inline LinkNode<T>::~LinkNode()
{
	clear();
}

//链表的插入（头插法）
template<typename T>
inline void LinkNode<T>::inset(T elme)
{
	Node<T>*s = new Node<T>;
	s->data = elme;
	s->next = head->next;
	head->next = s;
	len++;
}

template<typename T>
inline bool LinkNode<T>::ListFind_only(string e)
{
	Node<T>* p = head->next;
	while (p != nullptr)
	{
		if (p->data.VehLicense == e)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}

//查找对应车牌的车子并删除
template<typename T>
inline bool LinkNode<T>::ListFind(string e, T& t)
{
	if (head == nullptr)
	{
		return false;
	}
	Node<T>* p = head->next,*q = head;
	while (p != nullptr)
	{
		if (p->data.VehLicense == e)
		{
			q->next = p->next;
			t = p->data;
			delete p;
			return true;
		}
		q = p;
		p = p->next;
	}
	return false;
}

//创建方式开创链表
template<typename T>
void createlist(Node<T>*& L, T a[], int n) 
{
	Node<T>* s, * r;
	L = new Node<T>;
	r = L;
	for (size_t i = 0; i < n; i++)
	{
		s = new Node<T>;
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = nullptr;
}

//按时间排序
template<typename T>
inline void LinkNode<T>::selsesort()
{
	if (head == nullptr)
		return;
	Node<T>* p = head->next, * q, * min;
	Node<T> t;
	min = p;
	while (p!= nullptr)
	{
		q = p->next;
		while (q!=nullptr)
		{
			if (min->data.StarTime > q->data.StatTime)
			{
				min = q;
			}
			q = q->next;
		}
		if (p!= min)
		{
			t = p->data;
			p->data = min->data;
			min->data = t;
		}
		p = p->next;
	}
}

//显示车辆信息
template<typename T>
inline void LinkNode<T>::displist()
{
	Node<T>* p = head->next;
	cout<< setiosflags(ios::left) << setw(20) << "车牌" << setw(20) << "种类" << setw(20) << "入库时间" << endl;
	while (p!=nullptr)
	{
		cout << setiosflags(ios::left) << setw(20) << p->data.VehLicense << setw(20) << p->data.VehKind;
		cout << setiosflags(ios::left) << p->data.StarTime.tm_year + 1900 << "年" << p->data.StarTime.tm_mon + 1 << "月" << p->data.StarTime.tm_mday << "日" << p->data.StarTime.tm_hour << "时" << p->data.StarTime.tm_min <<"分"<< endl;
		p = p->next;
	}
}


