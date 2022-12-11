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
            //std::cout << "nullptr returned!" << std::endl;
            return nullptr;
        }
        
    }

    Cell* GetNext(Cell* assignedpos)
    {
        if (assignedpos != nullptr)
        {
            if (Search(assignedpos) != nullptr)
            {
                return assignedpos->pos_next;
            }
        }

        return nullptr;
    }

    Cell* GetPrev(Cell* assignedpos)
    {
        if (assignedpos != nullptr)
        {
            if (Search(assignedpos) != nullptr)
            {
                //empty list
                if (header == nullptr)
                {
                    return nullptr;
                }

                //list of only one element
                if (header->Next() == nullptr)
                {
                    return nullptr;
                }

                //list of at least two elements
                Cell* previous = header;
                Cell* current = header->Next();
                while (current != nullptr)
                {
                    if (current == assignedpos)
                    {
                        return previous;
                    }

                    previous = current;
                    current = current->Next();
                }
            }
        }

        return nullptr;
    }

    Cell* Search(Cell* elem)
    {
        if (elem != nullptr)
        {
            if (header == nullptr)
            {
                return nullptr;
            }

            Cell* current = header;
            while (current != nullptr)
            {
                if (current == elem)
                {
                    return current;
                }

                current = current->Next();
            }
        }
        else
        {
            return nullptr;
        }

        return nullptr;
    }

    bool IsEmpty()
    {
        if (header == nullptr)
        {
            return true;
        }

        return false;
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
                return;
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
                return;
            }
        }
    }

    void DeleteFirst()
    {
        //first case: empty list
        if (header == nullptr)
        {
            //throw std::string("DeleteLast: list is empty!");
            return;
        }

        //second case: list is not empty
        header = header->Next();
        return;

    }

    void DeleteLast()
    {
        //first case: empty list
        if (header == nullptr)
        {
            //throw std::string("DeleteLast: list is empty!");
            return;
        }

        //second case: list contains only one element
        if (header->Next() == nullptr)
        {
            header = nullptr;
            return;
        }

        //third case: list contains more than one element
        Cell* previous = header;
        Cell* current = header->Next();

        while (current->Next() != nullptr)//getting pre-last element
        {
            previous = current;
            current = current->Next();
        }

        // after while(), "previous" contains pre-last element and "current" contains last element
        previous->pos_next = nullptr;
        return;
    }

    void DeleteAssigned(Cell* assignedpos)
    {
        // empty list
        if (header == nullptr)
        {
            //throw exeption?
            return;
        }

        //list contains only one element
        if (header->Next() == nullptr)
        {
            if (header == assignedpos)
            {
                DeleteFirst();
                return;
            }

            return;
        }

        //list contains only two elements
        Cell* previous = header;
        Cell* current = header->Next();
        if (current->Next() == nullptr)
        {
            if (previous == assignedpos)//checking the first element
            {
                DeleteFirst();
                return;
            }

            if (current == assignedpos)//checking the last element
            {
                DeleteLast();
                return;
            }

            return;
        }

        // list contains more than two elements
        previous = header;
        current = header->Next();

        if (header == assignedpos)//checking the first element
        {
            DeleteFirst();
            return;
        }

        while (current->Next() != nullptr) //checking other elements (except the last)
        {
            if (current == assignedpos)
            {
                previous->pos_next = current->Next();
                return;
            }

            previous = current;
            current = current->Next();
        }

        if (current == assignedpos)// checking the last element
        {
            //DeleteLast();//no need to go through list again, because after while() cycle we alredy have needed elements
            previous->pos_next = nullptr;
            return;
        }

        return;//assigned element doesn't exist in the list
    }

    Cell* PopFront()
    {
        if (header == nullptr)
        {
            return nullptr;
        }

        Cell* temp;
        temp = header;
        DeleteFirst();

        return temp;
    }

    Cell* PopBack()
    {
        if (header == nullptr)
        {
            return nullptr;
        }

        Cell* temp;
        temp = GetLast();
        DeleteLast();
        return temp;
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

/*
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

*/

////////////////////////////DeleteFirst test/////////////////////////////////////////////

/*
    std::cout << "  DeleteFirst test" << std::endl;

    MyList L5;

    std::cout << L5;
    L5.DeleteFirst();//empty
    std::cout << L5;



    L5.InsertToEnd(NewCell_1);//4

    L5.DeleteFirst();//one element
    std::cout << L5;



    L5.InsertToEnd(NewCell_1);//4
    L5.InsertToEnd(NewCell_2);//7

    std::cout << L5;
    L5.DeleteFirst();//two elements
    std::cout << L5;



    L5.InsertToEnd(NewCell_1);//4
    L5.InsertToEnd(NewCell_2);//7
    L5.InsertToEnd(NewCell_3);//9

    std::cout << L5;
    L5.DeleteFirst();//three elements
    std::cout << L5;



    L5.InsertToEnd(NewCell_1);//4
    L5.InsertToEnd(NewCell_2);//7
    L5.InsertToEnd(NewCell_3);//9
    L5.InsertToEnd(NewCell_4);//12
    L5.InsertToEnd(NewCell_5);//25

    std::cout << L5;
    L5.DeleteFirst();//a lot of elements
    std::cout << L5;
*/

////////////////////////////DeleteLast test//////////////////////////////////////////////

/*
    std::cout << "  DeleteLast test" << std::endl;
    MyList L6;


    std::cout << L6;
    L6.DeleteLast();//empty
    std::cout << L6;



    L6.InsertToEnd(NewCell_1);//4
    std::cout << L6;
    L6.DeleteLast();//one element
    std::cout << L6;



    L6.InsertToEnd(NewCell_1);//4
    L6.InsertToEnd(NewCell_2);//7
    std::cout << L6;
    L6.DeleteLast();//two elements
    std::cout << L6;



    L6.InsertToEnd(NewCell_1);//4
    L6.InsertToEnd(NewCell_2);//7
    L6.InsertToEnd(NewCell_3);//9

    std::cout << L6;
    L6.DeleteLast();//three elements
    std::cout << L6;



    L6.InsertToEnd(NewCell_1);//4
    L6.InsertToEnd(NewCell_2);//7
    L6.InsertToEnd(NewCell_3);//9
    L6.InsertToEnd(NewCell_4);//12
    L6.InsertToEnd(NewCell_5);//25

    std::cout << L6;
    L6.DeleteLast();//a lot of elements
    std::cout << L6;

*/


////////////////////////////DeleteAssigned test//////////////////////////////////////////

    std::cout << "  DeleteAssigned test" << std::endl;
    MyList L7;

    /*
        std::cout << L7;
        L7.DeleteAssigned(NewCell_1);//deleting in empty list
        std::cout << L7;
    */

/*
    L7.InsertToEnd(NewCell_1);
    std::cout << L7;
    L7.DeleteAssigned(NewCell_2);//one element, deleting the missing element inside of list
    std::cout << L7;
    L7.DeleteAssigned(NewCell_1);//one element, deleting existing element inside of list
    std::cout << L7;

    L7.InsertToEnd(NewCell_1);
    L7.InsertToEnd(NewCell_2);
    std::cout << L7;

    L7.DeleteAssigned(NewCell_3);//two elements, deleting the missing element inside of list
    std::cout << L7;

    //L7.DeleteAssigned(NewCell_1);//two elements, deleting the first element inside of list
    L7.DeleteAssigned(NewCell_2);//two elements, deleting the second element inside of list
    std::cout << L7;

*/

    L7.InsertToEnd(NewCell_1);//4
    L7.InsertToEnd(NewCell_2);//7
    L7.InsertToEnd(NewCell_3);//9
    L7.InsertToEnd(NewCell_4);//12
    L7.InsertToEnd(NewCell_5);//25
    std::cout << L7;



    //L7.DeleteAssigned(NewCell_1);//many elements, deleting the first
    //std::cout << L7;

    //L7.DeleteAssigned(NewCell_2);//many elements, deleting the second
    //std::cout << L7;

    //L7.DeleteAssigned(NewCell_6);//many elements, deleting the last
    //std::cout << L7;

    //L7.DeleteAssigned(NewCell_4);//many elements, deleting non-edge element
    //std::cout << L7;

    L7.DeleteAssigned(NewCell_6);//many elements, deleting the missing element
    std::cout << L7;

//////////////////////////////GetNext test///////////////////////////////////////

/*
    Cell* NextCell = new Cell;

    NextCell = L7.GetNext(NewCell_3);
    //NextCell = L7.GetNext(nullptr);

    if (NextCell != nullptr)
    {
        std::cout << NextCell->val;
    }
    else
    {
        std::cout << "NexCell constains nullptr" << std::endl;
    }

    MyList L8;

    //L8.InsertToEnd(NewCell_1);

    Cell* rrrr;
    rrrr = L8.GetNext(NewCell_1);

*/

///////////////////////////GetNext and Search test//////////////////////////////////////////

/*
    MyList A;
    MyList B;

    A.InsertToEnd(NewCell_1);
    A.InsertToEnd(NewCell_2);

    B.InsertToEnd(NewCell_3);
    B.InsertToEnd(NewCell_4);

    Cell* ttt = A.Search(NewCell_1);//getting first element from list A
    Cell* tttnnn = A.GetNext(ttt);//getting next element after assigned from list A

    std::cout << "List A; Next element after " << ttt->val << " is " << tttnnn->val << std::endl;

    Cell* qqq = B.GetNext(ttt);//getting next element after assigned but from list B

    if (qqq == nullptr)
    {
        std::cout << "element " << ttt->val << " not found in list B!" << std::endl;
    }

 */

//////////////////////////////GetPrev test//////////////////////////////////////////////
    
    std::cout << std::endl << std::endl;
    std::cout << L7;

    Cell* qwerty = L7.GetPrev(NewCell_3);
    std::cout << "GetPrev: " << qwerty->val << std::endl;

    MyList L9;

    qwerty = L9.GetPrev(NewCell_1);//zero

    L9.InsertToEnd(NewCell_1);//one

    //qwerty = L9.GetPrev(NewCell_1);
    //qwerty = L9.GetPrev(NewCell_2);


    L9.InsertToEnd(NewCell_2);//two

    //qwerty = L9.GetPrev(NewCell_1);
    //qwerty = L9.GetPrev(NewCell_2);
    //qwerty = L9.GetPrev(NewCell_3);

    L9.InsertToEnd(NewCell_3);
    L9.InsertToEnd(NewCell_4);
    L9.InsertToEnd(NewCell_5);

    //qwerty = L9.GetPrev(NewCell_1);
    //qwerty = L9.GetPrev(NewCell_2);
    //qwerty = L9.GetPrev(NewCell_3);
    //qwerty = L9.GetPrev(NewCell_4);
    //qwerty = L9.GetPrev(NewCell_5);
    //qwerty = L9.GetPrev(NewCell_6);

/////////////////////////////////////////////////////////////

    std::cout << "  PopFront test" << std::endl;

    std::cout << L9;

    Cell* temp = nullptr;
    int i = 0;
    while (L9.GetFirst() != nullptr)
    {
        temp = L9.PopFront();
        std::cout << "popfront: #" << i << " = " << temp->val << std::endl;
        i++;
    }

    std::cout << L9;

////////////////////////////////////////////////////////////////

    std::cout << "  PopBack test" << std::endl;

    L9.InsertToEnd(NewCell_1);
    L9.InsertToEnd(NewCell_2);
    L9.InsertToEnd(NewCell_3);
    L9.InsertToEnd(NewCell_4);
    L9.InsertToEnd(NewCell_5);

    std::cout << L9;

    temp = nullptr;
    i = 0;
    while (L9.GetLast() != nullptr)
    {
        temp = L9.PopBack();
        std::cout << "popback: #" << i << " = " << temp->val << std::endl;
        i++;
    }

    std::cout << L9;



    return 0;
}
