template<typename T>
class CMyStack
{
	T* pBuff;
	size_t len;
	size_t maxSize;
public:
	CMyStack();
	~CMyStack();
	void clear();
public:
	void push(T const& elem);
	void pop();
	T const& getTop() const { return pBuff[len - 1]; }
	bool empty() const { return len == 0; }
};

template<typename T>
void CMyStack<T>::pop()
{
	--len;
}

template<typename T>
void CMyStack<T>::push(T const& elem)
{
	if (len >= maxSize)
	{
		maxSize = maxSize + ((maxSize >> 1) > 1 ? (maxSize >> 1) : 1);
		T* tempBuff = new T[maxSize];
		for (size_t i = 0; i < len; ++i)
			tempBuff[i] = pBuff[i];
		if (pBuff != nullptr)
			delete[] pBuff;
		pBuff = tempBuff;
	}
	pBuff[len++] = elem;
}

template<typename T>
void CMyStack<T>::clear()
{
	if (pBuff != nullptr)
		delete[] pBuff;
	pBuff = nullptr;
	len = maxSize = 0;
}

template<typename T>
CMyStack<T>::~CMyStack()
{
	clear();
}

template<typename T>
CMyStack<T>::CMyStack()
{
	pBuff = nullptr;
	len = maxSize = 0;
}
