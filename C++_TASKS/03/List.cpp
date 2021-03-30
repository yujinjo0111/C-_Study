#include <iostream>
#include "List.h"
using namespace std;

const int ERROR = -99999;

List::List()
{
    itemCount = 0;
    items = new int[5];
    size = 5;
}

List::~List()
{
    delete[] items;
}

void List::increaseSizeIfNeed(int addSize)
{
    while (itemCount + addSize > size)
    {
        int* temp = new int[size];
        for (int i = 0; i < size; i++)
        {
            temp[i] = items[i];
        }
        items = new int[size * 2];
        for (int i = 0; i < size; i++)
        {
            items[i] = temp[i];
        }
        delete[] temp;
        size *= 2;
    }
}
int List::getItem(int index)
{
    return (index < itemCount ? items[index] : ERROR);
}

void List::addItem(int itm)
{
    increaseSizeIfNeed(1);
    items[itemCount++] = itm;
}

void List::insertItem(int index, int itm)
{
    increaseSizeIfNeed(1);
    for (int i = itemCount; i > index; i--)
    {
        items[i] = items[i - 1];
    }
    items[index] = itm;
    itemCount++;
}

int List::removeAt(int index)
{
    if (index > itemCount)
    {
        return ERROR;
    }

    int ret = items[index];
    for (int i = index; i < itemCount - 1; i++)
    {
        items[i] = items[i + 1];
    }
    itemCount--;
    return ret;
}

int List::removeItem(int itm)
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
        return ERROR;
    }
    else
    {
        removeAt(index);
        return index;
    }
}

void List::print()
{
    for (int i = 0; i < itemCount; i++)
    {
        cout << items[i] << (i == itemCount - 1 ? "\n" : " ");
    }
}

void List::concat(List& list)
{
    for (int i = 0; i < list.itemCount; i++)
    {
        addItem(list.items[i]);
    }
}


/* ######################################################################### */


OrderedList::OrderedList()
{
    itemCount = 0;
    items = new int[5];
    size = 5;
}

OrderedList::~OrderedList()
{
    delete[] items;
}

void OrderedList::increaseSizeIfNeed(int addSize)
{
    while (itemCount + addSize > size)
    {
        int* temp = new int[size];
        for (int i = 0; i < size; i++)
        {
            temp[i] = items[i];
        }
        items = new int[size * 2];
        for (int i = 0; i < size; i++)
        {
            items[i] = temp[i];
        }
        delete[] temp;
        size *= 2;
    }
}

int OrderedList::getItem(int index)
{
    return (index < itemCount ? items[index] : ERROR);
}

void OrderedList::insertItem(int index, int itm)
{
    increaseSizeIfNeed(1);
    for (int i = itemCount; i > index; i--)
    {
        items[i] = items[i - 1];
    }
    items[index] = itm;
    itemCount++;
}

void OrderedList::addItem(int itm)
{
    int insertIndex = itemCount;
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i] > itm)
        {
            insertIndex = i;
            break;
        }
    }
    insertItem(insertIndex, itm);
}

int OrderedList::removeAt(int index)
{
    if (index > itemCount)
    {
        return ERROR;
    }

    int ret = items[index];
    for (int i = index; i < itemCount - 1; i++)
    {
        items[i] = items[i + 1];
    }
    itemCount--;
    return ret;
}

int OrderedList::removeItem(int itm)
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
        return ERROR;
    }
    else
    {
        removeAt(index);
        return index;
    }
}

void OrderedList::print()
{
    for (int i = 0; i < itemCount; i++)
    {
        cout << items[i] << (i == itemCount - 1 ? "\n" : " ");
    }
}

void OrderedList::concat(OrderedList& olist)
{
    for (int i = 0; i < olist.itemCount; i++)
    {
        addItem(olist.items[i]);
    }
}
