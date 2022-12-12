#include <iostream>

class Cell
{
public:
    int val = 0;

    Cell* Next() const
    {
        return pos_next;
    }

    Cell* Prev() const
    {
        return pos_prev;
    }

private:
    Cell* pos_next = nullptr;
    Cell* pos_prev = nullptr;


    //methods?

    //insert
    //locate
    //retrieve
    //delete
    //next 
    //previous

    //end(MyDualList L)
    //makenull(MyDualList L)

    friend class MyDualList;
};

class MyDualList
{
private:
    Cell* header = nullptr;
    Cell* footer = nullptr;

public:

    Cell* GetFirst()
    {
        return header;
    }

    Cell* GetLast()
    {
        return footer;
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
                return assignedpos->pos_prev;
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

            return i + 1;
        }
    }

    void InsertToEnd(Cell* elem)
    {
        Cell* A = footer;
        Cell* B = elem;

        if (header == nullptr)//insert to end in empty list
        {
            B->pos_next = nullptr;
            B->pos_prev = nullptr;
            header = B;
            footer = B;
        }
        else//insert to end in non-empty list
        {
            B->pos_next = nullptr;
            B->pos_prev = A;
            A->pos_next = B;
            footer = B;
        }
    }

    void InsertToBegin(Cell* elem)
    {
        Cell* A = header;
        Cell* B = elem;

        if (header == nullptr)//insert to begin in empty list
        {
            B->pos_next = nullptr;
            B->pos_prev = nullptr;
            header = B;
            footer = B;
        }
        else//insert to begin in non-empty list
        {
            B->pos_next = A;
            B->pos_prev = nullptr;
            A->pos_prev = B;
            header = B;
        }
    }

    Cell* InsertToEnd(int value)
    {
        Cell* temp = new Cell;
        temp->val = value;
        InsertToEnd(temp);
        return temp;
    }

    Cell* InsertToBegin(int value)
    {
        Cell* temp = new Cell;
        temp->val = value;
        InsertToBegin(temp);
        return temp;
    }

    void InsertAfterAssigned(Cell* elem, Cell* assignedpos)//????????????
    {
        if ((assignedpos == nullptr) || (elem == nullptr))
        {
            return;
        }

        if (header == nullptr)//try to insert into empty list
        {
            //std::cout << "Warning! List is empty! inserting failed" << std::endl;
            //throw std::string("InsertAfterAssigned: list is empty!");
            return;
        }
        else//insert to non-empty list
        {
            Cell* B = assignedpos;
            Cell* C = assignedpos->Next();
            Cell* D = elem;

            if (B == footer)
            {
                InsertToEnd(D);
                return;
            }

            B->pos_next = D;
            D->pos_prev = B;
            D->pos_next = C;
            C->pos_prev = D;
        }
    }

    void InsertBeforeAssigned(Cell* elem, Cell* assignedpos)//realisation in one-way list (from begin to end)
    {
        if ((assignedpos == nullptr) || (elem == nullptr))
        {
            return;
        }

        if (header == nullptr)//try to insert into empty list
        {
            //std::cout << "Warning! List is empty! inserting failed" << std::endl;
            //throw std::string("InsertAfterAssigned: list is empty!");
            return;
        }
        else//insert to non-empty list
        {
            Cell* B = assignedpos;
            Cell* A = assignedpos->Prev();
            Cell* D = elem;

            if (B == header)
            {
                InsertToBegin(D);
                return;
            }

            A->pos_next = D;
            D->pos_prev = A;
            D->pos_next = B;
            B->pos_prev = D;
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

        if (header->Next() == nullptr)
        {
            header = nullptr;
            footer = nullptr;
            return;
        }
        else
        {
            header = header->Next();
            header->pos_prev = nullptr;
            return;
        }

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
            footer = nullptr;
            return;
        }

        Cell* A = footer->pos_prev;
        footer = A;
        A->pos_next = nullptr;
    }

    void DeleteAssigned(Cell* assignedpos)
    {
        // empty list
        if (header == nullptr)
        {
            //throw exeption?
            return;
        }

        Cell* B = assignedpos;
        Cell* A = B->Prev();
        Cell* C = B->Next();

        if (B == header)
        {
            DeleteFirst();
            return;
        }

        if (B == footer)
        {
            DeleteLast();
            return;
        }

        A->pos_next = C;
        C->pos_prev = A;

    }

    Cell* PopFront()
    {
        if (header == nullptr)
        {
            return nullptr;
        }

        Cell* temp;
        temp = GetFirst();
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

    friend std::ostream& operator<< (std::ostream& strm, MyDualList& a)
    {
        a.Print();
        std::cout << std::endl;

        return strm;
    }

};

int dual_linked_main(void)
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

    Cell* NewCell_7 = new Cell;
    NewCell_7->val = 77;

    Cell* NewCell_8 = new Cell;
    NewCell_8->val = 88;

    Cell* NewCell_9 = new Cell;
    NewCell_9->val = 99;



    /*
        MyDualList L1;

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

    {
        MyDualList L1;

        L1.InsertToEnd(NewCell_1);

        L1.InsertToEnd(NewCell_2);

        L1.InsertToEnd(NewCell_3);

        L1.InsertToEnd(NewCell_4);

        std::cout << L1;
    }

    //////////////////////////insert to begin////////////////////////////////////////////////

    {
        MyDualList L2;

        L2.InsertToBegin(NewCell_1);//4

        //std::cout << L2;

        L2.InsertToBegin(NewCell_2);
        L2.InsertToBegin(NewCell_3);
        L2.InsertToBegin(NewCell_4);

        std::cout << L2;
    }

    //////////////////////////insert after assigned position/////////////////////////////////


    std::cout << "  insert after assigned position test" << std::endl;

    {
        MyDualList L3;
        Cell* c1 = L3.InsertToEnd(11);
        Cell* c2 = L3.InsertToEnd(22);
        Cell* c3 = L3.InsertToEnd(33);

        L3.InsertAfterAssigned(NewCell_7, c2);//insert after non-edge element
        L3.InsertAfterAssigned(NewCell_8, c3);//insert after last element
        L3.InsertAfterAssigned(NewCell_9, c1);//insert after first element
        L3.InsertAfterAssigned(NewCell_3, nullptr);//
        // 11 99 22 77 33 88

        std::cout << L3;

        MyDualList EmptyList;

        EmptyList.InsertAfterAssigned(NewCell_5, NewCell_1);
    }

    //////////////////////////insert before assigned position////////////////////////////////


    std::cout << "  insert before assigned position test" << std::endl;
    {
        MyDualList L4;

        L4.InsertToEnd(NewCell_1);//4
        L4.InsertToEnd(NewCell_2);//7
        L4.InsertToEnd(NewCell_3);//9
        L4.InsertToEnd(NewCell_4);//12
        L4.InsertToEnd(NewCell_5);//25

        std::cout << "L4 : " << std::endl;

        std::cout << L4;

        L4.InsertBeforeAssigned(NewCell_6, NewCell_3);//insert before non-edge element
        L4.InsertBeforeAssigned(NewCell_7, NewCell_5);//insert before last element
        L4.InsertBeforeAssigned(NewCell_8, NewCell_1);//insert before first element
        // 88 4 7 66 9 12 77 25

        std::cout << L4;
    }

    ////////////////////////////DeleteFirst test/////////////////////////////////////////////


    std::cout << "  DeleteFirst test" << std::endl;

    {
        MyDualList L5;


        L5.DeleteFirst();//empty

        L5.InsertToEnd(NewCell_1);//4

        L5.DeleteFirst();//one element
        //
        std::cout << L5;


        L5.InsertToEnd(NewCell_1);//4
        L5.InsertToEnd(NewCell_2);//7
        L5.DeleteFirst();//two elements
        //7
        std::cout << L5;


        L5.InsertToEnd(NewCell_7);//77
        L5.InsertToEnd(NewCell_8);//88
        L5.InsertToEnd(NewCell_9);//99
        //77 88 99

        L5.DeleteFirst();//three elements
        std::cout << L5;
    }



    ////////////////////////////DeleteLast test//////////////////////////////////////////////


    std::cout << "  DeleteLast test" << std::endl;

    {
        MyDualList L6;


        std::cout << L6;
        L6.DeleteLast();//empty
        std::cout << L6;
        //empty



        L6.InsertToEnd(NewCell_1);//4
        std::cout << L6;
        L6.DeleteLast();//one element
        std::cout << L6;
        //empty



        L6.InsertToEnd(NewCell_1);//4
        L6.InsertToEnd(NewCell_2);//7
        std::cout << L6;
        L6.DeleteLast();//two elements
        std::cout << L6;
        //4



        L6.InsertToEnd(NewCell_7);//77
        L6.InsertToEnd(NewCell_8);//88
        L6.InsertToEnd(NewCell_9);//99

        std::cout << L6;
        L6.DeleteLast();//three elements
        std::cout << L6;
        //4 77 88
    }

    ////////////////////////////DeleteAssigned test//////////////////////////////////////////

    std::cout << "  DeleteAssigned test" << std::endl;

    {
        MyDualList L7;


        std::cout << L7;
        L7.DeleteAssigned(NewCell_1);//deleting in empty list
        std::cout << L7;
        //empty



        L7.InsertToEnd(NewCell_1);//4
        std::cout << L7;
        //4

        L7.DeleteAssigned(NewCell_1);//4 //one element, deleting existing element inside of list
        std::cout << L7;
        //empty

        L7.InsertToEnd(NewCell_1);//4
        L7.InsertToEnd(NewCell_2);//7
        std::cout << L7;
        //4 7


        L7.DeleteAssigned(NewCell_1);//two elements, deleting the first element inside of list
        L7.DeleteAssigned(NewCell_2);//7 //two elements, deleting the second element inside of list
        std::cout << L7;
        //empty



        L7.InsertToEnd(NewCell_1);//4
        L7.InsertToEnd(NewCell_2);//7
        L7.InsertToEnd(NewCell_3);//9
        L7.InsertToEnd(NewCell_4);//12
        L7.InsertToEnd(NewCell_5);//25
        L7.InsertToEnd(NewCell_6);//66
        L7.InsertToEnd(NewCell_7);//77
        L7.InsertToEnd(NewCell_8);//88
        L7.InsertToEnd(NewCell_9);//99
        std::cout << L7;
        //4 7 9 12 25 66 77 88 99



        L7.DeleteAssigned(NewCell_1);//many elements, deleting the first
        std::cout << L7;
        //7 9 12 25 66 77 88 99

        L7.DeleteAssigned(NewCell_3);//many elements, deleting the second
        std::cout << L7;
        //7 12 25 66 77 88 99

        L7.DeleteAssigned(NewCell_9);//many elements, deleting the last
        std::cout << L7;
        //7 12 25 66 77 88

        L7.DeleteAssigned(NewCell_5);//many elements, deleting non-edge element
        std::cout << L7;
        //7 12 66 77 88
    }


    //////////////////////////////GetNext test///////////////////////////////////////

    {
        MyDualList L7;

        L7.InsertToEnd(NewCell_1);//4
        L7.InsertToEnd(NewCell_2);//7
        L7.InsertToEnd(NewCell_3);//9
        L7.InsertToEnd(NewCell_4);//12
        L7.InsertToEnd(NewCell_5);//25

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

        MyDualList L8;

        //L8.InsertToEnd(NewCell_1);

        Cell* rrrr;
        rrrr = L8.GetNext(NewCell_1);
    }

    ///////////////////////////GetNext and Search test//////////////////////////////////////////

    {
        MyDualList A;
        MyDualList B;

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

    }

    //////////////////////////////GetPrev test//////////////////////////////////////////////

    {
        MyDualList L7;

        L7.InsertToEnd(NewCell_1);//4
        L7.InsertToEnd(NewCell_2);//7
        L7.InsertToEnd(NewCell_3);//9
        //L7.InsertToEnd(NewCell_4);//12
        //L7.InsertToEnd(NewCell_5);//25

        Cell* qwerty;

        std::cout << std::endl << std::endl;
        std::cout << L7;

        qwerty = L7.GetPrev(NewCell_3);
        std::cout << "GetPrev: " << qwerty->val << std::endl;

        MyDualList L9;

        qwerty = L9.GetPrev(NewCell_1);//zero

        L9.InsertToEnd(NewCell_1);//one

        qwerty = L9.GetPrev(NewCell_1);
        //qwerty = L9.GetPrev(NewCell_2);


        L9.InsertToEnd(NewCell_2);//two

        qwerty = L9.GetPrev(NewCell_1);
        //qwerty = L9.GetPrev(NewCell_2);
        //qwerty = L9.GetPrev(NewCell_3);

        L9.InsertToEnd(NewCell_3);
        L9.InsertToEnd(NewCell_4);
        L9.InsertToEnd(NewCell_5);

        //qwerty = L9.GetPrev(NewCell_1);
        qwerty = L9.GetPrev(NewCell_2);
        //qwerty = L9.GetPrev(NewCell_3);
        //qwerty = L9.GetPrev(NewCell_4);
        //qwerty = L9.GetPrev(NewCell_5);
    }


    /////////////////////////////////////////////////////////////

    {
        std::cout << "  PopFront test" << std::endl;


        MyDualList L9;

        L9.InsertToEnd(NewCell_1);
        L9.InsertToEnd(NewCell_2);
        L9.InsertToEnd(NewCell_3);
        L9.InsertToEnd(NewCell_4);
        L9.InsertToEnd(NewCell_5);

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
    }


    ////////////////////////////////////////////////////////////////

    {
        std::cout << "  PopBack test" << std::endl;

        MyDualList L9;

        L9.InsertToEnd(NewCell_1);
        L9.InsertToEnd(NewCell_2);
        L9.InsertToEnd(NewCell_3);
        L9.InsertToEnd(NewCell_4);
        L9.InsertToEnd(NewCell_5);

        std::cout << L9;

        Cell* temp = nullptr;
        int i = 0;
        while (L9.GetLast() != nullptr)
        {
            temp = L9.PopBack();
            std::cout << "popback: #" << i << " = " << temp->val << std::endl;
            i++;
        }

        std::cout << L9;
    }




    return 0;
}
