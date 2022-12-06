#include <iostream>

class Cell
{
public:
    int val = 0;

    Cell* Next() const
    {
        return pos_next;
    }

private:
    Cell* pos_next = nullptr;


    //methods?

    //insert
    //locate
    //retrieve
    //delete
    //next 
    //previous

    //end(MyList L)
    //makenull(Mylist L)

    friend class MyList;
};

class MyList
{
private:
    Cell* header = nullptr;

public:

    Cell* First()
    {
        return header;
    }

    Cell* Last()
    {
        if (header != nullptr)
        {
            Cell* current = header;

            while (current->Next() != nullptr)
            {
                current = current->Next();
            }

            return current;
        }
        else
        {
            std::cout << "nullptr returned!" << std::endl;
            return nullptr;
        }
        
    }

    void InsertToEnd(Cell* elem)
    {
        if (header == nullptr)//insert to end in empty list
        {
            header = elem;
            elem->pos_next = nullptr;
        }
        else//insert to end in non-empty list
        {
            Cell* oldlast = Last();
            oldlast->pos_next = elem;
            elem->pos_next = nullptr;
        }                
    }

    void InsertToPos(Cell* elem, Cell* pos)//????????????
    {
        if (header == nullptr)//insert to end in empty list
        {
            
        }
        else//insert to end in non-empty list
        {
            
        }
    }

};

int main(void)
{
    MyList L1;

    Cell* h1;
    Cell* elem;

    h1 = L1.First();

    if (h1 == nullptr)
    {
        std::cout << "Error! nullptr" << std::endl;
    }
    else
    {
        elem = h1->Next();
    }


    Cell* e1;

    e1 = L1.Last();

//////////////////////////////////////

    Cell* NewCell_1 = new Cell;
    NewCell_1->val = 4;

    L1.InsertToEnd(NewCell_1);

    Cell* NewCell_2 = new Cell;
    NewCell_2->val = 7;

    L1.InsertToEnd(NewCell_2);

    Cell* NewCell_3 = new Cell;
    NewCell_3->val = 9;
    L1.InsertToEnd(NewCell_3);

    return 0;
}
