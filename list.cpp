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

    Cell* GetFirst()
    {
        return header;
    }

    Cell* GetLast()
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

    int GetLength()
    {
        if (header == nullptr)
        {
            return 0;//empty list            
        }
        else
        {
            Cell* current = header;
            int i = 0;
            while (current->Next() != nullptr)
            {
                i++;
                current = current->Next();//go to next            
            }

            return i+1;
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
            Cell* oldlast = GetLast();
            oldlast->pos_next = elem;
            elem->pos_next = nullptr;
        }                
    }

    void InsertToBegin(Cell* elem)
    {
        if (header == nullptr)//insert to begin in empty list
        {
            std::cout << "InsertToBegin: empty list detected. inserting into empty list...." << std::endl;
            header = elem;
            elem->pos_next = nullptr;
        }
        else//insert to begin in non-empty list
        {
            Cell* oldfirst = GetFirst();
            elem->pos_next = oldfirst;
            header = elem;     
        }
    }

    void InsertAfterAssigned(Cell* elem, Cell* assignedpos)//????????????
    {
        if (header == nullptr)//try to insert into empty list
        {
            std::cout << "Warning! List is empty! inserting failed" << std::endl;
            //throw std::string("InsertAfterAssigned: list is empty!");
        }
        else//insert to non-empty list
        {                                 
            Cell* current = header;
            int i = 0;
            while (current->Next() != nullptr)
            {
                if (current == assignedpos)
                {
                    //... -> A -> B -> C -> ...
                    // D -> nullptr
                    // assigned == A
                    // 
                    //... -> A -> D -> B -> C -> ...
                    // 
                    //A->next() = D
                    //D->next() = B

                    Cell* temp;

                    temp = current->Next();//-> B
                    current->pos_next = elem;//A -> D          
                    elem->pos_next = temp; //D -> B

                    break;//no need to go further;

                }

                i++;
                current = current->Next();

                //checking last element:
                if ((current->Next() == nullptr) && (current == assignedpos))
                {
                    InsertToEnd(elem);
                }
            }

            //include last element (equal to situation when assignedpos == nullptr)
            //in previous cycle While(), last element doesn't participate in cycle (because it points to nullptr)
            if ((current->Next() == nullptr) && (current == assignedpos))
            {
                /*
                Cell* temp;

                temp = current->Next();//-> nullptr
                current->pos_next = elem;//A -> D          
                elem->pos_next = temp; //D -> nullptr
                */

                InsertToEnd(elem);
            }
            else
            {
                //throw std::string("InsertAfterAssigned: there is no assigned position in the list!");
            }
        }
    }    

    void InsertBeforeAssigned(Cell* elem, Cell* assignedpos)//realisation in one-way list (from begin to end)
    {
        if (header == nullptr)//try to insert into empty list
        {
            std::cout << "Warning! List is empty! inserting failed" << std::endl;
            //throw std::string("InsertAfterAssigned: list is empty!");
        }
        else//insert to non-empty list
        {
            Cell* current = header;
            int i = 0;
            while (current->Next() != nullptr)
            {
                if (current == assignedpos)//equal to inserting to begin
                {
                    InsertToBegin(elem);
                    break;
                }

                if (current->Next() == assignedpos)
                {
                    //... -> A -> B -> C -> ...
                    // D -> nullptr
                    // assigned == C
                    // 
                    //... -> A -> B -> D -> C -> ...
                    // 
                    // temp = -> C
                    // A->next()->next() = D
                    // D->next() = C

                    Cell* temp;

                    temp = current->Next();//-> C
                    current->pos_next = elem;//A -> D
                    elem->pos_next = temp; //D -> B

                    break;//no need to go further;

                }

                i++;
                current = current->Next();
            }

            //include last element (equal to situation when assignedpos == nullptr)
            if ((current->Next() == nullptr) && (current == assignedpos))
            {
                Cell* temp;

                temp = current->Next();//-> nullptr
                current->pos_next = elem;//A -> D
                elem->pos_next = temp; //D -> nullptr
            }
            else
            {
                //throw std::string("InsertAfterAssigned: there is no assigned position in the list!");
            }
        }
    }

    void Print()
    {
        if (header != nullptr)
        {
            Cell* current = header;

            int i = 0;
            while (current->Next() != nullptr)
            {
                //print
                std::cout << "#" << i << ": " << current->val << std::endl;

                //go to next
                current = current->Next();
                i++;
            }

            //print the last element
            std::cout << "#" << i << ": " << current->val << std::endl;
        }
        else
        {
            std::cout << "List is empty!" << std::endl;            
        }
    }

    friend std::ostream& operator<< (std::ostream& strm, MyList& a)
    {
        a.Print();
        std::cout << std::endl;

        return strm;
    }
    
};

int main(void)
{
    Cell* NewCell_1 = new Cell;
    NewCell_1->val = 4;

    Cell* NewCell_2 = new Cell;
    NewCell_2->val = 7;

    Cell* NewCell_3 = new Cell;
    NewCell_3->val = 9;

    Cell* NewCell_4 = new Cell;
    NewCell_4->val = 12;

    Cell* NewCell_5 = new Cell;
    NewCell_5->val = 25;

    Cell* NewCell_6 = new Cell;
    NewCell_6->val = 66;



/*
    MyList L1;

    Cell* h1;
    Cell* elem;

    h1 = L1.GetFirst();

    if (h1 == nullptr)
    {
        std::cout << "Error! nullptr" << std::endl;
    }
    else
    {
        elem = h1->Next();
    }


    Cell* e1;

    e1 = L1.GetLast();
*/

///////////////////////////insert to end/////////////////////////////////////////////////

/*
    L1.InsertToEnd(NewCell_1);

    L1.InsertToEnd(NewCell_2);

    L1.InsertToEnd(NewCell_3);

    L1.InsertToEnd(NewCell_4);

    std::cout << L1;

*/

//////////////////////////insert to begin////////////////////////////////////////////////

/*
    MyList L2;

    L2.InsertToBegin(NewCell_1);

    //std::cout << L2;

    L2.InsertToBegin(NewCell_2);
    L2.InsertToBegin(NewCell_3);
    L2.InsertToBegin(NewCell_4);

    std::cout << L2;
*/

//////////////////////////insert after assigned position/////////////////////////////////

/*
    std::cout << "  insert after assigned position test" << std::endl;

    std::cout << L2;

    //L2.InsertAfterAssigned(NewCell_5, NewCell_1);//insert after non-edge element
    //L2.InsertAfterAssigned(NewCell_5, NewCell_1);//insert after last element
    //L2.InsertAfterAssigned(NewCell_5, NewCell_4);//insert after first element
    //L2.InsertAfterAssigned(nullptr, NewCell_3);//insert after first element

    std::cout << L2;

    MyList EmptyList;

    EmptyList.InsertAfterAssigned(NewCell_5, NewCell_1);
*/

//////////////////////////insert before assigned position////////////////////////////////


    std::cout << "  insert before assigned position test" << std::endl;

    MyList L3;

    L3.InsertToEnd(NewCell_1);//4
    L3.InsertToEnd(NewCell_2);//7
    L3.InsertToEnd(NewCell_3);//9
    L3.InsertToEnd(NewCell_4);//12
    L3.InsertToEnd(NewCell_5);//25

    std::cout << "L3 : " << std::endl;

    std::cout << L3;

    //L3.InsertBeforeAssigned(NewCell_6, NewCell_3);//insert before non-edge element
    //L3.InsertBeforeAssigned(NewCell_6, NewCell_5);//insert before last element
    L3.InsertBeforeAssigned(NewCell_6, NewCell_1);//insert before first element

    std::cout << L3;




    return 0;
}
