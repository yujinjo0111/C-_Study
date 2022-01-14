const int ERROR = -99999;

template <class T>
class List
{
private:
   T* items;
   int itemCount, size;
   void increaseSizeIfNeed(int addSize);

public:
    List();
    ~List();
    T getItem(int index);
    void addItem(T itm);
    void insertItem(int index, T itm);
    T removeAt(int index);
    int removeItem(T itm);
    void print();
    void concat(List &list);
    void clear();
    int length();
};

template <class T>
int List<T>::length() 
{
    return itemCount;
}

template <class T>
void List<T>::clear()
{
    itemCount = 0;
    delete[] items;
    items = new T[5];
    size = 5;
}

template <class T>
List<T>::List() 
{
    itemCount = 0;
    items = new T[5];
    size = 5;
}

template <class T>
List<T>::~List() 
{
    delete[] items;
}

template <class T>
void List<T>::increaseSizeIfNeed(int addSize)
{
    while (itemCount + addSize > size)
    {
        T *temp = new T[size];
        for (int i = 0; i < size; i++)
        {
            temp[i] = items[i];
        }
        items = new T[size * 2];
        for (int i = 0; i < size; i++)
        {
            items[i] = temp[i];
        }
        delete[] temp;
        size *= 2;
    }
}

template <class T>
T List<T>::getItem(int index)
{
    if (index < itemCount)
        return items[index];
    else
        throw "Error";
}

template <class T>
void List<T>::addItem(T itm)
{
    increaseSizeIfNeed(1);
    items[itemCount++] = itm;
}

template <class T>
void List<T>::insertItem(int index, T itm)
{
    increaseSizeIfNeed(1);
    for (int i = itemCount; i > index; i--)
    {
        items[i] = items[i - 1];
    }
    items[index] = itm;
    itemCount++;
}

template <class T>
T List<T>::removeAt(int index) 
{
    if (index > itemCount) 
    {
        throw "Error";
    }
    
    T ret = items[index];
    for (int i = index; i < itemCount - 1; i++) 
    {
        items[i] = items[i + 1];
    }
    itemCount--;
    return ret;
}

template <class T>
int List<T>::removeItem(T itm) 
{
    int index = -1;
    for (int i = 0; i < itemCount; i++) 
    {
        if (items[i] == itm) 
        {
            index = i;
            break;
        }
    }
    
    if (index == -1)
    {
        throw "Error";
    }
    else 
    {
        removeAt(index);
        return index;
    }
}

template <class T>
void List<T>::print() 
{
    for (int i = 0; i < itemCount; i++) 
    {
        cout << items[i] << (i == itemCount - 1 ? "\n" : " ");
    }
}

template <class T>
void List<T>::concat(List &list) 
{
    for (int i = 0; i < list.itemCount; i++)
    {
        addItem(list.items[i]);
    }
}

