//과제//
//class List 순서x
//class OrderedList 순서o 
//{
// private:
// int *items;
// int itemCount;
// int size;
// public:
//    Array();
//   ~Array();
//  int getItem(int index);
//  void addItem(int itm);
//  void insertItem( int index, int itm);
//  void removeItem(int index);
//  void operator+ (List&list);
// };

class Array
{
private:
	int* data;
	int size;
	int dataCount;
public:
	Array();
	int getData(int index);
	void addData(int value);
	void insertData(int index, int value);
	void removeData(int index);

};
Array::Array()
{
	dataCount = 0;
	size = 10;
	data = new int[size]; //malloc

}
Array::Array()
{
	delete[] data; //free

}
void Array::addData(int value)
{
	if (dataCount < 10)
	{
		int pos;
		for (pos = 0; pos < dataCount; pos++)
			if (data[pos] > value)
				break;
		if (pos == dataCount) {
			data[dataCount] = value;
			dataCount++;
		}
		else
		{
			insertData(pos, value);

		}
	}
	else
	{
		int* newData = new int[size * 2];
		for (int i = 0; i < dataCount; i++)
			newData[i] = data[i];
		newData[dataCount] = value;
		dataCount++;
		delete[] data;
		data= newData;
		size = size * 2; //사이즈를 넓혀서 저장


	}
}
int Array::getData(int index)
{
	if (index < dataCount)

		return data[index];
	else
		return -99999;
}

//아래꺼는 함수 구현해 준것이고 그냥 쓸때는 아래처럼
//Array arr;
//for (int i = 0; i < 1000; i++)
//	arr.addData(i);
