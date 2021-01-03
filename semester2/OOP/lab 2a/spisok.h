#include <fstream>

class spisok
{
public:
    Rectangle* first;
    Rectangle* last;
    unsigned int current_length;
    void create_empty(unsigned int k=0)
    {
        first = nullptr;
        last = nullptr;
        current_length = 0;
    }
    Rectangle* get(unsigned int k)
    {
        if(k>=current_length-1) return last;
        unsigned int number = 0;
        Rectangle* result = first;
        while(number!=k)
        {
            number++;
            result = result->next;
        }
        return result;
    }
    void push(Rectangle new_element)
    {
        Rectangle* new_rect = new Rectangle;
        *new_rect = new_element;
        new_rect->next = nullptr;
        new_rect->previous = nullptr;
        if(last==nullptr)
        {
            last = new_rect;
            first = new_rect;
            current_length++;
            return;
        }
        last->next = new_rect;
        new_rect->previous = last;
        last = new_rect;
        current_length++;
    }
    void insert_new(Rectangle new_element, unsigned int k)
    {
        Rectangle* new_rect = new Rectangle;
        (*new_rect) = new_element;
        if(last==nullptr)
        {
            last = new_rect;
            first = new_rect;
            return;
        }
        if(k>=current_length){
            push(new_element);
            return;
        }
        new_rect->next = get(k);
        get(k)->previous = new_rect;
        if(k==0)
        {
            new_rect->previous = nullptr;
            first = new_rect;
        }
        else
        {
            new_rect->previous = get(k-1);
            get(k-1)->next = new_rect;
        }
        current_length++;
    }
    void remove_element(unsigned int k)
    {
        if(last==nullptr) return;
        if(current_length==1)
        {
            delete first;
            first = nullptr;
            last = nullptr;
            current_length--;
            return;
        }
        if(k>=current_length-1)
        {
            Rectangle* pocket = last->previous;
            delete last;
            last = pocket;
            if (last!=nullptr) last->next = nullptr;
            current_length--;
            return;
        }
        if(k==0)
        {
            if(first->next!=nullptr)
            {
                get(1)->previous = nullptr;
                Rectangle* pocket = first->next;
                delete first;
                first = pocket;
            }
            else{
                delete first;
                first = nullptr;
                last = nullptr;
            }
        }
        else
        {
            Rectangle* pointer = get(k);
            pointer->previous->next = pointer->next;
            pointer->next->previous = pointer->previous;
            delete pointer;
        }
        current_length--;
    }
};


std::ostream& operator<<(std::ostream& out, const spisok& rect_list)
{
    Rectangle* next = rect_list.first;
    while(next!=nullptr)
    {
        out << "First point A(" << next->point1.x << ", " << next->point1.y << ")\n";
        out << "Second point B(" << next->point2.x << ", " << next->point2.y << ")\n";
        out << "\n";
        next = next->next;
    }
    return out;
}
