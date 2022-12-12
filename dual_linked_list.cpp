#include <iostream>

template <class Type>
class Cell
{
public:
    Type val = 0;

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

     template<class Type>
     friend class MyDualList;
};

template<class Type>
class MyDualList
{
    typedef Cell<Type> CELLT;
private:
    CELLT* header = nullptr;
    CELLT* footer = nullptr;

public:

    CELLT* GetFirst()
    {
        return header;
    }

    CELLT* GetLast()
    {
        return footer;
    }

    CELLT* GetNext(CELLT* assignedpos)
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

    CELLT* GetPrev(CELLT* assignedpos)
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

    CELLT* Search(CELLT* elem)
    {
        if (elem != nullptr)
        {
            if (header == nullptr)
            {
                return nullptr;
            }

            CELLT* current = header;
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
            CELLT* current = header;
            int i = 0;
            while (current->Next() != nullptr)
            {
                i++;
                current = current->Next();//go to next            
            }

            return i + 1;
        }
    }

    void InsertToEnd(CELLT* elem)
    {
        CELLT* A = footer;
        CELLT* B = elem;

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

    void InsertToBegin(CELLT* elem)
    {
        CELLT* A = header;
        CELLT* B = elem;

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

    CELLT* InsertToEnd(int value)
    {
        CELLT* temp = new CELLT;
        temp->val = value;
        InsertToEnd(temp);
        return temp;
    }

    CELLT* InsertToBegin(int value)
    {
        CELLT* temp = new CELLT;
        temp->val = value;
        InsertToBegin(temp);
        return temp;
    }

    void InsertAfterAssigned(CELLT* elem, CELLT* assignedpos)//????????????
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
            CELLT* B = assignedpos;
            CELLT* C = assignedpos->Next();
            CELLT* D = elem;

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

    void InsertBeforeAssigned(CELLT* elem, CELLT* assignedpos)//realisation in one-way list (from begin to end)
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
            CELLT* B = assignedpos;
            CELLT* A = assignedpos->Prev();
            CELLT* D = elem;

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

        CELLT* A = footer->pos_prev;
        footer = A;
        A->pos_next = nullptr;
    }

    void DeleteAssigned(CELLT* assignedpos)
    {
        // empty list
        if (header == nullptr)
        {
            //throw exeption?
            return;
        }

        CELLT* B = assignedpos;
        CELLT* A = B->Prev();
        CELLT* C = B->Next();

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

    CELLT* PopFront()
    {
        if (header == nullptr)
        {
            return nullptr;
        }

        CELLT* temp;
        temp = GetFirst();
        DeleteFirst();

        return temp;
    }

    CELLT* PopBack()
    {
        if (header == nullptr)
        {
            return nullptr;
        }

        CELLT* temp;
        temp = GetLast();
        DeleteLast();
        return temp;
    }

    void Print()
    {
        if (header != nullptr)
        {
            CELLT* current = header;

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
    Cell<int>* NewCell_1 = new Cell<int>;
    NewCell_1->val = 4;

    Cell<int>* NewCell_2 = new Cell<int>;
    NewCell_2->val = 7;

    Cell<int>* NewCell_3 = new Cell<int>;
    NewCell_3->val = 9;

    Cell<int>* NewCell_4 = new Cell<int>;
    NewCell_4->val = 12;

    Cell<int>* NewCell_5 = new Cell<int>;
    NewCell_5->val = 25;

    Cell<int>* NewCell_6 = new Cell<int>;
    NewCell_6->val = 66;

    Cell<int>* NewCell_7 = new Cell<int>;
    NewCell_7->val = 77;

    Cell<int>* NewCell_8 = new Cell<int>;
    NewCell_8->val = 88;

    Cell<int>* NewCell_9 = new Cell<int>;
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
        MyDualList<int> L1;

        L1.InsertToEnd(NewCell_1);

        L1.InsertToEnd(NewCell_2);

        L1.InsertToEnd(NewCell_3);

        L1.InsertToEnd(NewCell_4);

        std::cout << L1;
    }

    //////////////////////////insert to begin////////////////////////////////////////////////

    {
        MyDualList<int> L2;

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
        MyDualList<int> L3;
        Cell<int>* c1 = L3.InsertToEnd(11);
        Cell<int>* c2 = L3.InsertToEnd(22);
        Cell<int>* c3 = L3.InsertToEnd(33);

        L3.InsertAfterAssigned(NewCell_7, c2);//insert after non-edge element
        L3.InsertAfterAssigned(NewCell_8, c3);//insert after last element
        L3.InsertAfterAssigned(NewCell_9, c1);//insert after first element
        L3.InsertAfterAssigned(NewCell_3, nullptr);//
        // 11 99 22 77 33 88

        std::cout << L3;

        MyDualList<int> EmptyList;

        EmptyList.InsertAfterAssigned(NewCell_5, NewCell_1);
    }

    //////////////////////////insert before assigned position////////////////////////////////


    std::cout << "  insert before assigned position test" << std::endl;
    {
        MyDualList<int> L4;

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
        MyDualList<int> L5;


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
        MyDualList<int> L6;


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
        MyDualList<int> L7;


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
        MyDualList<int> L7;

        L7.InsertToEnd(NewCell_1);//4
        L7.InsertToEnd(NewCell_2);//7
        L7.InsertToEnd(NewCell_3);//9
        L7.InsertToEnd(NewCell_4);//12
        L7.InsertToEnd(NewCell_5);//25

        Cell<int>* NextCell = new Cell<int>;

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

        MyDualList<int> L8;

        //L8.InsertToEnd(NewCell_1);

        Cell<int>* rrrr;
        rrrr = L8.GetNext(NewCell_1);
    }

    ///////////////////////////GetNext and Search test//////////////////////////////////////////

    {
        MyDualList<int> A;
        MyDualList<int> B;

        A.InsertToEnd(NewCell_1);
        A.InsertToEnd(NewCell_2);

        B.InsertToEnd(NewCell_3);
        B.InsertToEnd(NewCell_4);

        Cell<int>* ttt = A.Search(NewCell_1);//getting first element from list A
        Cell<int>* tttnnn = A.GetNext(ttt);//getting next element after assigned from list A

        std::cout << "List A; Next element after " << ttt->val << " is " << tttnnn->val << std::endl;

        Cell<int>* qqq = B.GetNext(ttt);//getting next element after assigned but from list B

        if (qqq == nullptr)
        {
            std::cout << "element " << ttt->val << " not found in list B!" << std::endl;
        }

    }

    //////////////////////////////GetPrev test//////////////////////////////////////////////

    {
        MyDualList<int> L7;

        L7.InsertToEnd(NewCell_1);//4
        L7.InsertToEnd(NewCell_2);//7
        L7.InsertToEnd(NewCell_3);//9
        //L7.InsertToEnd(NewCell_4);//12
        //L7.InsertToEnd(NewCell_5);//25

        Cell<int>* qwerty;

        std::cout << std::endl << std::endl;
        std::cout << L7;

        qwerty = L7.GetPrev(NewCell_3);
        std::cout << "GetPrev: " << qwerty->val << std::endl;

        MyDualList<int> L9;

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


        MyDualList<int> L9;

        L9.InsertToEnd(NewCell_1);
        L9.InsertToEnd(NewCell_2);
        L9.InsertToEnd(NewCell_3);
        L9.InsertToEnd(NewCell_4);
        L9.InsertToEnd(NewCell_5);

        std::cout << L9;

        Cell<int>* temp = nullptr;
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

        MyDualList<int> L9;

        L9.InsertToEnd(NewCell_1);
        L9.InsertToEnd(NewCell_2);
        L9.InsertToEnd(NewCell_3);
        L9.InsertToEnd(NewCell_4);
        L9.InsertToEnd(NewCell_5);

        std::cout << L9;

        Cell<int>* temp = nullptr;
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
