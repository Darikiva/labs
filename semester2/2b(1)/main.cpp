#include <iostream>
#include <vector>

struct Element
{
    double x;
    double y;
    Element* next;
};

std::ostream& operator<<(std::ostream& out, Element* plural)
{
    Element* printed_element = plural;
    while(printed_element!=nullptr)
    {
        out << "(" << printed_element->x << "," << printed_element->y << ") ";
        printed_element = printed_element->next;
    }
    out << '\n';
    return out;
}

void print_list(std::vector<Element*> plural_list)
{
    for(int i=0; i<plural_list.size(); i++)
                {
                    std::cout << "Plural " << i+1 << ": ";
                    std::cout << plural_list[i];
                }
}

operator== (Element* plural, Element element)
{
    Element* help_pointer = plural;
    while(help_pointer!=nullptr)
    {
        if(help_pointer->x==element.x&&help_pointer->y==element.y) return true;
        help_pointer = help_pointer->next;
    }
    return false;
}

Element create_element()
{
    Element new_element;
    std::cout << "Enter 2 numbers: ";
    std::cin >> new_element.x >> new_element.y;
    new_element.next = nullptr;
    return new_element;
}

void add(Element* &plural, Element new_element)
{
    Element* help_el = new Element;
    help_el->x = new_element.x;
    help_el->y = new_element.y;
    if(plural==*help_el) return;
    Element* pocket = help_el;
    help_el->next = plural;
    plural = pocket;
}

void remove_element(Element* &plural, Element* deleted_element)
{
    Element* help_pointer = plural;

    if(plural==nullptr) return;
    if(plural->x==deleted_element->x&&plural->y==deleted_element->y)
    {
        Element* pocket = plural->next;
        delete plural;
        plural = pocket;
        return;
    }

    while(help_pointer->next!=nullptr)
    {
        if(help_pointer->next->x==deleted_element->x&&help_pointer->next->y==deleted_element->y)
        {
            Element* pocket = nullptr;
            if(help_pointer->next->next!=nullptr)   // если после удаленного элемента в списке есть еще элементы
            {
                pocket = help_pointer->next->next;
            }
            delete help_pointer->next;
            help_pointer->next = pocket;
            return;
        }
    }
}

Element* intersection_plurals(Element* A, Element* B)
{
    Element* result = nullptr;
    Element* copy_A = A;
    while(copy_A!=nullptr)
    {
        if(B==*copy_A) add(result, *copy_A);
        copy_A = copy_A->next;
    }
    return result;
}

Element* union_plurals(Element* A, Element* B)
{
    Element* result = nullptr;
    Element* copy_A = A;
    Element* copy_B = B;
    while(copy_A!=nullptr)
    {
        add(result, *copy_A);
        copy_A = copy_A->next;
    }
    while(copy_B!=nullptr)
    {
        add(result, *copy_B);
        copy_B = copy_B->next;
    }
    return result;
}

Element* complement_plurals(Element* A, Element* B)
{
    Element* result = nullptr;
    Element* copy_A = A;
    while(copy_A!=nullptr)
    {
        if(!(B==*copy_A)) add(result, *copy_A);
        copy_A = copy_A->next;
    }
    return result;
}

Element* composition_plurals(Element* A, Element* B)
{
    Element* result = nullptr;
    Element* copy_A = A;
    while(copy_A!=nullptr)
    {
        Element* copy_B = B;
        while(copy_B!=nullptr)
        {
            if(copy_A->y==copy_B->x)
            {
                Element new_element;
                new_element.x = copy_A->x;
                new_element.y = copy_B->y;
                new_element.next = nullptr;
                add(result, new_element);
            }
            copy_B = copy_B->next;
        }
        copy_A = copy_A->next;
    }
    return result;
}

Element* converse(Element* A)
{
    Element* result = nullptr;
    Element* copy_A = A;
    while(copy_A!=nullptr){
        Element new_element;
        new_element.x = copy_A->y;
        new_element.y = copy_A->x;
        new_element.next = nullptr;
        add(result, new_element);
        copy_A = copy_A->next;
    }
    return result;
}

bool is_reflexive(Element* A)
{
    Element* copy_A = A;
    while(copy_A!=nullptr)
    {
        bool is_x = false;
        bool is_y = false;
        Element* second_copy = A;
        while(second_copy!=nullptr&&!(is_x&&is_y))
        {
            if(second_copy->x==copy_A->x&&second_copy->y==copy_A->x) is_x = true;
            if(second_copy->x==copy_A->y&&second_copy->y==copy_A->y) is_y = true;
            second_copy = second_copy->next;
        }
        if(!is_x||!is_y) return false;
        copy_A = copy_A->next;
    }
    return true;
}

bool is_transitive(Element* A)
{
    Element* copy_A = A;
    while(copy_A!=nullptr)
    {
        bool is_x = false;
        bool is_y = false;
        Element* second_copy = A;
        while(second_copy!=nullptr)
        {
            if(second_copy->y==copy_A->x) is_x = true;
            if(second_copy->x==copy_A->y) is_y = true;
            second_copy = second_copy->next;
        }
        if(!is_x||!is_y) return false;
        copy_A = copy_A->next;
    }
    return true;
}

void help()
{
    std::cout << "1. Add new plural\n";
    std::cout << "2. Add new element\n";
    std::cout << "3. Remove element\n";
    std::cout << "4. Print all plurals\n";
    std::cout << "5. Intersections of 2 plurals\n";
    std::cout << "6. Union of 2 plurals\n";
    std::cout << "7. Composition 2 plurals\n";
    std::cout << "8. Converse of plural\n";
    std::cout << "9. Is plural reflexive\n";
    std::cout << "10. Is plural transitive\n";
    std::cout << "Enter your choice: ";
}

void interactive()
{
    std::vector <Element*> plural_list;
    help();
    unsigned int choice;
    while(std::cin>> choice)
    {
        switch(choice)
        {
        case 1: // new plural
            {
                Element* new_plural = nullptr;
                plural_list.push_back(new_plural);
            }
            break;

        case 2: // new element
            {
                unsigned int index;
                std::cout << "Enter index of plural: ";
                std::cin >> index;
                if(index>plural_list.size()-1) index = plural_list.size()-1;

                add(plural_list[index], create_element());
            }
            break;

        case 3: // delete
            {
                Element deleted;
                unsigned int index;
                std::cout << "Enter index of plural: ";
                std::cin >> index;
                if(index>plural_list.size()-1) index = plural_list.size()-1;

                std::cout << "Enter deleted element(2 coord): ";
                std::cin >> deleted.x >> deleted.y;

                remove_element(plural_list[index], &deleted);
            }
            break;

        case 4: // print
            {
                print_list(plural_list);
            }
            break;

        case 5: // intersection
            {
                unsigned int index1, index2;
                std::cout << "Enter 2 indexes: ";
                std::cin >> index1 >> index2;
                if(index1>plural_list.size()-1) index1 = plural_list.size()-1;
                if(index2>plural_list.size()-1) index2 = plural_list.size()-1;
                std::cout << intersection_plurals(plural_list[index1], plural_list[index2]);
            }
            break;

        case 6: // union
            {
                unsigned int index1, index2;
                std::cout << "Enter 2 indexes: ";
                std::cin >> index1 >> index2;

                if(index1>plural_list.size()-1) index1 = plural_list.size()-1;
                if(index2>plural_list.size()-1) index2 = plural_list.size()-1;
                std::cout << union_plurals(plural_list[index1], plural_list[index2]);
            }
            break;

        case 7: // composition
            {
                unsigned int index1, index2;
                std::cout << "Enter 2 indexes: ";
                std::cin >> index1 >> index2;

                if(index1>plural_list.size()-1) index1 = plural_list.size()-1;
                if(index2>plural_list.size()-1) index2 = plural_list.size()-1;
                std::cout << composition_plurals(plural_list[index1], plural_list[index2]);
            }
            break;

        case 8: //converse
            {
                unsigned int index;
                std::cout << "Enter index: ";
                std::cin >> index;

                if(index>plural_list.size()-1) index = plural_list.size()-1;
                std::cout << converse(plural_list[index]);
            }
            break;

        case 9: // is reflexive
            {
                unsigned int index;
                std::cout << "Enter index: ";
                std::cin >> index;

                if(index>plural_list.size()-1) index = plural_list.size()-1;
                if(is_reflexive(plural_list[index])) std::cout << "YES";
                else std::cout << "NO";
            }
            break;

        case 10: // is transitive
            {
                unsigned int index;
                std::cout << "Enter index: ";
                std::cin >> index;

                if(index>plural_list.size()-1) index = plural_list.size()-1;
                if(is_transitive(plural_list[index]))std::cout << "YES";
                else std::cout << "NO";
            }
            break;
        }
        std::cout << "\n\n";
        help();
    }
}

void demonstration()
{
    int number;
    std::vector <Element*> plural_list;
    std::cout << "Add 50 new plurals, and fill it with random amount of random elements: \n";
    for(int i=0; i<50; i++)
    {
        number = rand()%20;
        Element* new_plural = nullptr;
        plural_list.push_back(new_plural);
        for(int j=0; j<number; j++)
        {
            Element new_element;
            new_element.x = rand()%5;
            new_element.y = rand()%5;
            add(plural_list[i], new_element);
        }
    }
    print_list(plural_list);
    std::cout << "\n\n";
    std::cout << "Intersection of 2 random plurals (20 times): \n";
    for(int i=0; i<20; i++)
    {
        int index1 = rand()%plural_list.size();
        int index2 = rand()%plural_list.size();
        std::cout << "Plurals " << index1+1 << " and " << index2+1 << ": ";
        std::cout << intersection_plurals(plural_list[index1], plural_list[index2]);
    }

    std::cout << "\n\n";
    std::cout << "Union of 2 random plurals (7 times): \n";
    for(int i=0; i<7; i++)
    {
        int index1 = rand()%plural_list.size();
        int index2 = rand()%plural_list.size();
        std::cout << "Plurals " << index1+1 << " and " << index2+1 << ": ";
        std::cout << union_plurals(plural_list[index1], plural_list[index2]);
    }

    std::cout << "\n\n";
    std::cout << "Composition of 2 random plurals (20 times): \n";
    for(int i=0; i<20; i++)
    {
        int index1 = rand()%plural_list.size();
        int index2 = rand()%plural_list.size();
        std::cout << "Plurals " << index1+1 << " and " << index2+1 << ": ";
        std::cout << composition_plurals(plural_list[index1], plural_list[index2]);
    }

    std::cout << "\n\n";
    std::cout << "Converse of all plurals: \n";
    for(int i=0; i<plural_list.size(); i++)
    {
        std::cout << "Plural " << i+1 << ": " << converse(plural_list[i]);
    }

    std::cout << "\n\n";
    std::cout << "Check if is plural is reflexive: ";
    for(int i=0; i<plural_list.size(); i++)
    {
        if(is_reflexive(plural_list[i])) std::cout << "Plural " << i+1 << " is reflexive\n";
        else std::cout << "Plural " << i+1 << " is not reflexive\n";
    }

    std::cout << "\n\n";
    std::cout << "Check if plural is transitive: ";
    for(int i=0; i<plural_list.size(); i++)
    {
        if(is_transitive(plural_list[i])) std::cout << "Plural " << i+1 << " is transitive\n";
        else std::cout << "Plural " << i+1 << " is not transitive\n";
    }
}

int main()
{
    std::cout << "1. Interactive mode\n";
    std::cout << "2. Demonstration\n";
    std::cout << "Enter your choice: ";
    unsigned int choice;
    std::cin >> choice;
    switch(choice)
    {
        case 1: interactive();
        break;
        case 2: demonstration();
        break;
    }
    return 0;
}
