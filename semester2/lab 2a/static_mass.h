#include <fstream>

class static_mass
{
public:
    Rectangle* main_pointer;
    unsigned int max_length;
    unsigned int current_length;
    void create_empty(unsigned int number)
    {
        main_pointer = new Rectangle[number];
        max_length = number;
        current_length = 0;
    };
    Rectangle* get(unsigned int k)
    {
        if(k>=current_length) return &main_pointer[current_length-1];
        else return &main_pointer[k];
    }
    int push(Rectangle new_element)
    {
        if(current_length+1>max_length)
        {
            return -1;
        }
        main_pointer[current_length]= new_element;
        current_length++;
        return 1;
    };
    int insert_new(Rectangle new_element, unsigned int k)
    {
        if(current_length+1>max_length)
        {
            return -1;
        }
        if(k>current_length) {
            push(new_element);
            return 0;
        }
        for(unsigned int i=current_length; i>k; i--)
        {
            main_pointer[i] = main_pointer[i-1];
        }
        main_pointer[k] = new_element;
        current_length++;
        return 0;
    }
    void remove_element(unsigned int k)
    {
        if(current_length==0) return;
        if(k>=current_length)
        {
            current_length--;
        }
        else
        {
            for(unsigned int i=k; i<current_length-1; i++)
            {
                main_pointer[i] = main_pointer[i+1];
            }
            current_length--;
        }
    }
    unsigned int length()
    {
        return current_length;
    }
    void delete_whole()
    {
        current_length = 0;
    }
};

std::ostream& operator<<(std::ostream& out, static_mass rect_list)
{
    for(unsigned int i=0; i<rect_list.current_length; ++i)
    {
        out << "First point A(" << rect_list.main_pointer[i].point1.x << "," << rect_list.main_pointer[i].point1.y;
        out << ")\n";
        out << "Second point B(" << rect_list.main_pointer[i].point2.x << "," << rect_list.main_pointer[i].point2.y;
        out << ")\n\n";
    }
    return out;
}
