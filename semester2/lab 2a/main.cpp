#include <iostream>
#include "dynamic_mass.h"
#include "static_mass.h"
#include "spisok.h"
#include <chrono>

using namespace std::chrono;

std::istream& operator>> (std::istream& in, Rectangle& new_element)
{
    in >> new_element.point1.x >> new_element.point1.y;
    in >> new_element.point2.x >> new_element.point2.y;
    return in;
}

void help()
{
    using namespace std;
    cout << "Indexing starts from zero. Make sure you made empty list!\n";
    cout << "1. Create empty\n";
    cout << "2. Append\n";
    cout << "3. Insert\n";
    cout << "4. Remove\n";
    cout << "5. Get\n";
    cout << "6. Length\n";
    cout << "7. Print\n";
    cout << "8. Exit\n";
}

int choice()
{
    using namespace std;
    cout << "*******LIST*******\n\n";
    cout << "1. Static array\n";
    cout << "2. Dynamic array\n";
    cout << "3. List\n";
    cout << "4. Finish\n";
    cout << "Enter your choice: ";
    int result;
    cin >> result;
    return result;
}

int mode()
{
    using namespace std;
    int result;
    cout << "1. Interactive mode\n";
    cout << "2. Demonstration mode\n";
    cout << "3. Benchmark mode\n";
    cout << "Enter mode: ";
    cin >> result;
    return result;
}

template <typename T>
void interactive(T rect_list, unsigned int number = 0);

template <typename T>
void demonstration(T rect_list);

template <typename T>
void benchmark(T rect_list);

int main()
{
    int k;
    k = choice();
    while(k!=4)
    {
        switch(k)
        {
        static_mass rect_static;
        spisok rect_spisok;

        case (1):
                switch (mode())
                {
                case 1:
                    int number;
                    std::cout << "Enter number of elements: ";
                    std::cin >> number;
                    interactive(rect_static, number);
                    break;
                case 2:
                    demonstration(rect_static);
                    break;
                case 3:
                    benchmark(rect_static);
                    break;
                default:
                    std::cout << "There is no such mode!\n";
                }
                break;
        case (2):
            {
                dynamic_mass rect_dynamic;
                switch(mode())
                {
                case 1:
                    interactive(rect_dynamic);
                    break;
                case 2:
                    demonstration(rect_dynamic);
                    break;
                case 3:
                    benchmark(rect_dynamic);
                    break;
                default:
                    std::cout << "There is no such mode!\n";
                }
            }
            break;
        case (3):
                switch(mode())
                {
                case 1:
                    interactive(rect_spisok);
                    break;
                case 2:
                    demonstration(rect_spisok);
                    break;
                case 3:
                    benchmark(rect_spisok);
                    break;
                default:
                    std::cout << "There is no such mode!\n";
                }
                break;
        default:
            std::cout << "No such a choice!\n";
            break;
        }
        k = choice();
    }
    return 0;
}

template <typename T>
void benchmark(T rect_list)
{
    using namespace std;
    unsigned int N = 10;
    unsigned int time = 0;
    while(N<50000 && time<5000)
    {
        if(time<1000) N*=2;
        else N+=0.2*N;

        cout << N << " elements\n";

        rect_list.create_empty(N);

        auto start = steady_clock::now();
        for(unsigned int i=0; i<N; ++i)
        {
            Rectangle new_element;
            new_element.point1.x = rand()%10;
            new_element.point1.y = rand()%10;
            new_element.point2.x = rand()%10;
            new_element.point2.y = rand()%10;
            rect_list.push(new_element);
        }
        auto finish = steady_clock::now();
        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Add: " << time << " ms\n";

        if(time > 5000) return;

        start = steady_clock::now();
        for(unsigned int i=0; i<N; i++)
        {
            unsigned int index = rand()%N;
            rect_list.remove_element(index);
        }
        finish = steady_clock::now();
        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Remove: " << time << " ms\n";

        if(time > 5000) return;

        start = steady_clock::now();
        for(unsigned int i=0; i<N; i++)
        {
            unsigned int index = rand()%N;
            Rectangle new_element;
            new_element.point1.x = rand()%10;
            new_element.point1.y = rand()%10;
            new_element.point2.x = rand()%10;
            new_element.point2.y = rand()%10;
            rect_list.insert_new(new_element, index);
        }
        finish = steady_clock::now();
        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Insert: " << time << " ms\n";
    }
}

template <typename T>
void demonstration(T rect_list)
{
    using namespace std;
    rect_list.create_empty(50);
    cout << "Add 5 random elements in the end: \n";
    for(unsigned int i=0; i<5; ++i)
        {
            Rectangle new_element;
            new_element.point1.x = rand()%10;
            new_element.point1.y = rand()%10;
            new_element.point2.x = rand()%10;
            new_element.point2.y = rand()%10;
            rect_list.push(new_element);
        }
    cout << rect_list;
    cout << "Insert 5 random elements in begin: \n";
    for(unsigned int i=0; i<5; ++i)
        {
            Rectangle new_element;
            new_element.point1.x = rand()%10;
            new_element.point1.y = rand()%10;
            new_element.point2.x = rand()%10;
            new_element.point2.y = rand()%10;
            rect_list.insert_new(new_element, 0);
        }
    cout << rect_list;
    cout << "Remove 7 random elements: \n";
    for(unsigned int i=0; i<7; i++)
        {
            unsigned int index = rand()%(rect_list.current_length-1);
            rect_list.remove_element(index);
        }
    cout << rect_list;
    cout << "Remove remaining elements by putting index = 5000: \n";
    for(; rect_list.current_length!=0 ;)
        {
            unsigned int index = 5000;
            rect_list.remove_element(index);
        }
    cout << "Add 5 random elements, where coords are equal to i, in the end by insert: \n";
    for(unsigned int i=0; i<5; i++)
        {
            unsigned int index = rect_list.current_length;
            Rectangle new_element;
            new_element.point1.x = i;
            new_element.point1.y = i;
            new_element.point2.x = i;
            new_element.point2.y = i;
            rect_list.insert_new(new_element, index);
        }
    cout << rect_list;
    cout << "Add 5 random elements in random places: \n";
    for(unsigned int i=0; i<5; i++)
        {
            unsigned int index = rand()%(rect_list.current_length-1);
            Rectangle new_element;
            new_element.point1.x = rand()%10;
            new_element.point1.y = rand()%10;
            new_element.point2.x = rand()%10;
            new_element.point2.y = rand()%10;
            rect_list.insert_new(new_element, index);
        }
    cout << rect_list;
    cout << "Remove all elements by putting random index: \n";
    for(unsigned int i=0; i<rect_list.current_length; i++)
        {
            unsigned int index = rand()%5000;
            rect_list.remove_element(index);
        }
}

template <typename T>
void interactive(T rect_list, unsigned int number)
{
    help();
    std::cout << "Enter your choice: \n";
    unsigned int choice;
    Rectangle new_element;
    unsigned int index;
    while (std::cin>>choice)
    {
        switch (choice)
        {
        case 1:
            rect_list.create_empty(number);
            break;
        case 2:
            std::cout << "Enter coords of 2 dots: ";
            std::cin >> new_element;
            rect_list.push(new_element);
            break;
        case 3:
            std::cout << "Enter coords of 2 dots: ";
            std::cin >> new_element;
            std::cout << "Enter index: ";
            std::cin >> index;
            rect_list.insert_new(new_element, index);
            break;
        case 4:
            std::cout << "Enter index: ";
            std::cin >> index;
            rect_list.remove_element(index);
            break;
        case 5:
            std::cout << "Enter index: ";
            std::cin >> index;
            rect_list.get(index);
            break;
        case 6:
            std::cout << rect_list.current_length;
            break;
        case 7:
            std::cout << rect_list;
            break;
        case 8:
            return;
        default:
            std::cout << "There is no such command! Try again: ";
            break;
        }
    std::cout << "\n";
    help();
    std::cout << "Enter your choice: ";
    }
}
