#include <iostream>
#include "list.h"
#include "mass.h"
#include "tree.h"
#include "AVL.h"
#include "2-3tree.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

template<typename T>
void Interactive(T*);

template<typename T>
void Demonstrative(T*);

template<typename T>
void Benchmark(T);

template<typename T>
void mode(T* root)
{
    cout << "1. Interactive\n";
    cout << "2. Demonstrative\n";
    cout << "3. Benchmark\n";
    int mode;
    cin >> mode;
    switch(mode)
    {
    case 1:
        Interactive(root);
        break;
    case 2:
        Demonstrative(root);
        break;
    case 3:
        Benchmark(root);
        break;
    }
}

int main()
{
    for(;;)
    {
        cout << "1. List\n";
        cout << "2. Array list\n";
        cout << "3. Binary tree\n";
        cout << "4. AVL tree\n";
        cout << "5. 2-3 tree\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
            {
                NodeList* root = nullptr;
                mode(root);
            }
            break;
        case 2:
            {
                ArrNode* root = nullptr;
                mode(root);
            }
            break;
        case 3:
            {
                TreeNode* root = nullptr;
                mode(root);
            }
            break;
        case 4:
            {
                AVLnode* root = nullptr;
                mode(root);
            }
            break;
        case 5:
            {
                TTnode* root = nullptr;
                mode(root);
            }
            break;
        case 6:
            return 0;
        default:
            cout << "No such option!\n";
        }
    }
    return 0;
}

template<typename T>
void Interactive(T* root)
{
    for(;;)
    {
        cout << "1. Add new element\n";
        cout << "2. Find by value\n";
        cout << "3. Find by range\n";
        cout << "4. Remove element\n";
        cout << "5. Print\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
            {
                cout << "Enter value: ";
                int value;
                cin >> value;
                add(&root, value);
                cout << endl;
            }
            break;
        case 2:
            {
                cout << "Enter value: ";
                int value;
                cin >> value;
                std::vector<int> answer;
                find(root, value, value, answer);
                for(const auto& i:answer) cout << i << " ";
                cout << endl;
            }
            break;
        case 3:
            {
                cout << "Enter 2 values: ";
                int min, max;
                cin >> min >> max;
                std::vector<int> answer;
                find(root, min, max, answer);
                for(const auto& i:answer) cout << i << " ";
                cout << endl;
            }
            break;
        case 4:
            {
                cout << "Enter value: ";
                int value;
                cin >> value;
                remove(&root, value);
                cout << endl;
            }
            break;
        case 5:
            {
                print(root);
                cout << endl;
            }
            break;
        case 6:
            return;
        default:
            cout << "No such option\n";
        }
    }
}

template<typename T>
void Demonstrative(T* root)
{
    cout << "Add 70 new elements (from 1 to 50)";
    for(int i=0; i<70; i++)
    {
        add(&root, i+1);
    }
    print(root);
    cout << endl;

    cout << "Remove element 45: ";
    remove(&root, 45);
    print(root);
    cout << endl;

    for(int i=0; i<30; i++)
    {
        int value = rand()%70;
        cout << "Remove element " << value << ": ";
        remove(&root, value);
        print(root);
        cout << endl;
    }

    cout << "Find all elements in range 4-25: ";
    std::vector<int> answer;
    find(root, 4, 25, answer);
    for(auto const& i:answer) cout << i << " ";
    cout << endl;

    cout << "Thanks for your attention!\n";
}

template<typename T>
void Benchmark(T* wow)
{
    int time = 0;
    int number = 10;

    while(number<100000)
    {
        T* root = nullptr;
        cout << number << " elements" << endl;
        auto start = steady_clock::now();
        for(int i=0; i<number; i++)
        {
            add(&root, rand()%1000);
        }
        auto finish = steady_clock::now();
        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Add " << number << " elements: " << time << " ms" << endl;

        cout << '\t' << "Memory: " << calculate_memory(root) << " bytes" << endl;

        if(time >= 7000) return;

        start = steady_clock::now();
        for(int i=0; i<number/4; i++)
        {
            std::vector<int> answer;
            int min = rand()%400;
            int max = min+rand()%600;
            find(root, min, max , answer);
        }
        finish = steady_clock::now();
        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Find " << number/4 << " times: " << time << " ms" << endl;

        if(time >= 7000) return;

        start = steady_clock::now();
        for(int i=0; i<number; i++)
        {
            remove(&root, rand()%1000);
        }
        finish = steady_clock::now();
        time = duration_cast<milliseconds>(finish-start).count();
        cout << '\t' << "Remove: " << time << " ms" << endl;

        if(time >= 7000) return;

        number = number*2;
    }
}
