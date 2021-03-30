
class List
{
private:
    int* items;
    int itemCount, size;
    void increaseSizeIfNeed(int addSize);

public:
    List();
    ~List();
    int getItem(int index);
    void addItem(int itm);
    void insertItem(int index, int itm);
    int removeAt(int index);
    int removeItem(int itm);
    void print();
    void concat(List& list);
};

class OrderedList
{
private:
    int* items;
    int itemCount, size;
    void increaseSizeIfNeed(int addSize);
    void insertItem(int index, int itm);

public:
    OrderedList();
    ~OrderedList();
    int getItem(int index);
    void addItem(int itm);
    int removeAt(int index);
    int removeItem(int itm);
    void print();
    void concat(OrderedList& olist);
};



