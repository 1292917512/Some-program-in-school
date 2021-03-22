#include<iostream>
#include <iomanip>
using std::setw;
using namespace std;

//����ṹ��
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

//��������
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

//��ʼ����������
template<typename T>
inline LinkNode<T>::LinkNode()
{
	head = new Node<T>;
	head->next = nullptr;
	len = 0;
}

//���������
template<typename T>
inline LinkNode<T>::~LinkNode()
{
	clear();
}

//����Ĳ��루ͷ�巨��
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

//���Ҷ�Ӧ���Ƶĳ��Ӳ�ɾ��
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

//������ʽ��������
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

//��ʱ������
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

//��ʾ������Ϣ
template<typename T>
inline void LinkNode<T>::displist()
{
	Node<T>* p = head->next;
	cout<< setiosflags(ios::left) << setw(20) << "����" << setw(20) << "����" << setw(20) << "���ʱ��" << endl;
	while (p!=nullptr)
	{
		cout << setiosflags(ios::left) << setw(20) << p->data.VehLicense << setw(20) << p->data.VehKind;
		cout << setiosflags(ios::left) << p->data.StarTime.tm_year + 1900 << "��" << p->data.StarTime.tm_mon + 1 << "��" << p->data.StarTime.tm_mday << "��" << p->data.StarTime.tm_hour << "ʱ" << p->data.StarTime.tm_min <<"��"<< endl;
		p = p->next;
	}
}


