#include <vector>

struct coord
{
    double x;
    double y;
};

struct Rectangle
{
    coord point1;
    coord point2;
    Rectangle* next;
    Rectangle* previous;
};

class dynamic_mass
{
public:
    std::vector <Rectangle> rects;
    unsigned int current_length;
    void create_empty(unsigned int k=0)
    {
        current_length = 0;
    }
    Rectangle* get(unsigned int k)
    {
        if(k>=current_length) return &rects[current_length];
        else return &rects[k];
    }
    void push(Rectangle new_rect)
    {
        rects.push_back(new_rect);
        current_length++;
    }
    void insert_new(Rectangle new_rect, unsigned int k)
    {
        if(k>=current_length) rects.push_back(new_rect);
        else
        {
            if (current_length==0) rects.push_back(new_rect);
            else {
                Rectangle new_element;
                new_element = rects[current_length-1];
                rects.push_back(new_element);
                for(unsigned int i=current_length-1; i>k; i--)
                {
                    rects[i] = rects[i-1];
                }
                rects[k] = new_rect;
            }
        }
        current_length++;
    }
    void remove_element(unsigned int k)
    {
        if(current_length==0) return;
        if(k>=current_length) rects.pop_back();
        else
        {
            rects.erase(rects.begin()+k);
        }
        current_length--;
    }
    unsigned int length()
    {
        return current_length;
    }
    void delete_whole()
    {
        rects.resize(0);
    }
};

std::ostream& operator<< (std::ostream& out, const dynamic_mass& rect_list)
{
    for (unsigned int i=0; i<rect_list.current_length; ++i)
    {
        out << "First point A(" << rect_list.rects[i].point1.x << ", " << rect_list.rects[i].point1.y << ")\n";
        out << "Second point B(" << rect_list.rects[i].point2.x << ", " << rect_list.rects[i].point2.y << ")\n";
        out << "\n";
    }
    return out;
}
