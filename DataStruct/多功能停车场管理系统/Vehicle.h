struct MyPoint  //车辆位置
{
	int row, col;
};

template<typename T>
class Vehicle
{
	T veh;
public:
	Vehicle<T>();
	~Vehicle();
	int Time_spent(T t);
private:

};

template<typename T>
inline Vehicle<T>::Vehicle()
{
	
}

template<typename T>
inline Vehicle<T>::~Vehicle<T>()
{
}

template<typename T>
inline int Vehicle<T>::Time_spent(T t)  //计费系统
{
	int sum = 0;
	sum += (t.EndTime.tm_min - t.StarTime.tm_min) * 0.2;
	sum += (t.EndTime.tm_hour - t.StarTime.tm_hour) * 12;
	sum += (t.EndTime.tm_mday - t.StarTime.tm_mday)*50;
	sum += (t.EndTime.tm_mon - t.StarTime.tm_mon)*300;
	sum += (t.EndTime.tm_year - t.StarTime.tm_year)*1000;
	return sum;
}
