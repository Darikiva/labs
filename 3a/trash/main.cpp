#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
template <typename T>
void integration(vector<T>& sorted_list, size_t l, size_t r)
{
    size_t m = (l+r)/2;
    vector<T> help_vector;
    while(l<=m)
    {
        if(sorted_list[l]>sorted_list[m+1])
        {
            help_vector.push_back(sorted_list[m+1]);
            m++;
        }
        else l++;
    }
    for(size_t i=0; i<help_vector.size(); i++)
    {
        sorted_list[l+i] = help_vector[i];
    }
}

template <typename T>
void intersection_sort(vector<T>& sorted_list, size_t l, size_t r)
{
    if(r == l+1)
    {
        if(sorted_list[l]>sorted_list[r])
            swap(sorted_list[l], sorted_list[r]);
        return;
    }
    if(l>=r) return;
    size_t m = (l+r)/2;
    intersection_sort(sorted_list, l, m);
    intersection_sort(sorted_list, m+1, r);
    integration(sorted_list, l, r);
}

class Product
{
public:
    string name;
    int amount;
};

template <typename First>
void sort_list(vector <Product> product_list, First (Product::*pointer))
{
    for(auto i:product_list) cout << i.*pointer << " ";
    return;
}

template <typename First, typename Second = int>
void print(First first, Second* second = nullptr)
{
    cout << first;
    if(second!=nullptr) cout << *second;
}

int main()
{
    int a = 5;
    print(a);
    return 0;
}
