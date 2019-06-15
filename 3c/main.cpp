#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void insertion_sort(vector<int>& sorted_list, int left, int right)
{
    if(right-left<=0) return;
    if(sorted_list[left]>sorted_list[left+1])
    {
        std::swap(sorted_list[left], sorted_list[left+1]);
    }
    for(int j=left+1; j<=right; j++)
    {
        int key = sorted_list[j];
        int i = int(j)-1;
        while(i>=int(left)&&sorted_list[i]>key)
        {
            sorted_list[i+1] = sorted_list[i];
            i--;
        }
        sorted_list[i+1] = key;
    }
}

void merge_mine(vector <int>& sorted_list, size_t first1, size_t last1,
                                     size_t first2, size_t last2)
{
    vector <int> answer;
    size_t index1 = first1;

    int counter1 = 0;
    int counter2 = 0;
    while(first1<=last1 && first2<=last2)
    {
        if(sorted_list[first1] < sorted_list[first2])
        {
            answer.push_back(sorted_list[first1]);
            first1++;
            counter1++;
            counter2 = 0;
        }
        else
        {
            answer.push_back(sorted_list[first2]);
            first2++;
            counter1 = 0;
            counter2++;
        }
        if(counter1==7)
        {

        }
    }
    while(first2<=last2)
    {
        answer.push_back(sorted_list[first2]);
        first2++;
    }
    while(first1<=last1)
    {
        answer.push_back(sorted_list[first1]);
        first1++;
    }

    for(size_t i=last2+1; i < sorted_list.size(); i++)
    {
        sorted_list[index1] = sorted_list[i];
        index1++;
    }

    size_t l=0;

    for(size_t i=index1; i<sorted_list.size(); i++)
    {
        sorted_list[i] = answer[l];
        l++;
    }
}

int get_minrun(int n)
{
    int r = 0;
    while(n>=64)
    {
        r |= n&1;
        n>>=1;
    }
    return n+r;
}

void reverse(vector <int>& sorted_list, size_t first, size_t last)
{
    for(size_t i=first; i<=(last/2); i++)
        swap(sorted_list[first+i], sorted_list[last-i]);
}

void timsort(vector <int>& sorted_list, bool is_demo = false)
{
    vector <pair <int, int> > for_merge;
    int minrun = get_minrun(sorted_list.size());
    if(is_demo) cout << '\t' << "Minrun = " << minrun << endl;
    int index = 0;
    int current_index = 1;
    bool q;
    bool is_increasing;

    int time = 0;

    auto start = steady_clock::now();
    while(index<sorted_list.size()-1)
    {
        q = true;
        if(sorted_list[current_index]>=sorted_list[current_index-1])
            is_increasing = true;
        else is_increasing = false;
        while(q)
        {
            if(current_index - index > minrun) q = false;
            if((sorted_list[current_index] >= sorted_list[current_index-1]) == is_increasing)
                q = true;
            else if(sorted_list[current_index] == sorted_list[current_index-1]) q = true;
            if(current_index+1>=sorted_list.size()) q = false;
            if(q) current_index++;
        }

        if(!is_increasing) reverse(sorted_list, index, current_index);

        for_merge.push_back(make_pair(index, current_index));
        insertion_sort(sorted_list, index, current_index);

        index = current_index+1;
        current_index+=2;
    }

    if(is_demo)
    {
        cout << '\t' << "New step\n";
        for(const auto& i:sorted_list) cout << i << " ";
        cout << endl;
    }

    size_t size_ = for_merge.size() - 1;
    while(size_>=2)
    {
        int Z = for_merge[size_].second - for_merge[size_].first+1;
        int Y = for_merge[size_-1].second - for_merge[size_-1].first+1;
        int X = for_merge[size_-2].second - for_merge[size_-2].first+1;
        if(((X > Y+Z)&& (Y>Z)) || (X>Z))
        {
            merge_mine(sorted_list, for_merge[size_-1].first, for_merge[size_-1].second,
                                    for_merge[size_].first, for_merge[size_].second);
            for_merge[size_-1].second = sorted_list.size()-1;
        }
        else
        {
            merge_mine(sorted_list, for_merge[size_-2].first, for_merge[size_-2].second,
                                    for_merge[size_-1].first, for_merge[size_-1].second);
            for_merge[size_-1].first += Z-X;
            for_merge[size_-1].second = sorted_list.size()-1;
            for_merge[size_-2].second = for_merge[size_-2].first + Z -1;
        }
        size_ --;
        if(is_demo)
        {
            cout << '\t' << "New step\n";
            for(const auto& i:sorted_list)
                cout << i << " ";
            cout << endl;
        }
    }

    if(size_>=1)
    {
        merge_mine(sorted_list, for_merge[0].first, for_merge[0].second,
                                    for_merge[1].first, for_merge[1].second);

        if(is_demo)
        {
            cout << '\t' << "New step\n";
            for(const auto& i:sorted_list)
                cout << i << " ";
            cout << endl;
        }
    }
}

void benchmark();
void demonstration();

int main()
{
    for(;;)
    {
        cout << "1. Demonstration\n";
        cout << "2. Benchmark\n";
        cout << "3. Exit\n";
        cout << "Enter your choice(number): ";
        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
            demonstration();
            break;
        case 2:
            benchmark();
            break;
        case 3:
            return 0;
        default:
            cout << "No such command, try again!\n";
        }
    }
}

void demonstration()
{
    int number = 100;
    vector<int> sorted_list(number);
    cout << "Timsort for " << number << " elements:\n";
    for(int i=0; i<number; i++)
    {
        sorted_list[i] = rand()%number-rand()%number;
    }
    timsort(sorted_list, true);
    cout << endl << '\t' << "SORTED LIST" << endl;
    for(const auto& i:sorted_list) cout << i << " ";
    cout << endl;


    number = 500;
    sorted_list.resize(number);
    cout << "Timsort for " << number << " elements:\n";
    for(int i=0; i<number; i++)
    {
        sorted_list[i] = rand()%number-rand()%number;
    }
    timsort(sorted_list, true);
    cout << endl << '\t' << "SORTED LIST" << endl;
    for(const auto& i:sorted_list) cout << i << " ";
    cout << endl;
}

void benchmark()
{
    vector<int> a;
    int N = 2;

    int time = 0;

    cout << '\t' << "Random elements\n";
    while(time<10000)
    {
        N*=2;

        for(int i=0; i<N; i++)
        {
            int value;
            value = rand()%1000;
            a.push_back(value);
        }

        auto start = steady_clock::now();
       // cout << N << " elements: ";
        timsort(a);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish - start).count();

        cout << N << " elements: " << time << " ms" << endl;

        a.resize(0);
    }

    cout << '\t' << "Elements in correct order: \n";
    N = 2;
    time = 0;

    while(time<5000 && N<10000000)
    {
        N*=2;

        for(int i=0; i<N; i++)
        {
            int value;
            if(i==0) value = -1000;
            else value = a[i-1] + rand()%10;
            a.push_back(value);
        }

        auto start = steady_clock::now();
        //cout << N << " elements: ";
        timsort(a);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish - start).count();
        cout << N << " elements: " << time << " ms" << endl;

        a.resize(0);
    }

    cout << '\t' << "Elements in incorrect order: \n";
    N = 2;
    time = 0;

    while(time<5000 && N<10000000)
    {
        N*=2;

        for(int i=0; i<N; i++)
        {
            int value;
            if(i==0) value = 1000;
            else value = a[i-1] - rand()%10;
            a.push_back(value);
        }

        auto start = steady_clock::now();
        timsort(a);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish - start).count();
        cout << N << " elements: " << time << " ms" << endl;

        a.resize(0);
    }

    cout << '\t' << "Some elements in correct order, some random\n";
    N = 2;
    time = 0;

    while(time<5000 && N<10000000)
    {
        N*=2;

        for(int i=0; i<N; i++)
        {
            int value;
            if(i%80<40) value = rand()%1000;
            else value = a[i-1] - rand()%10;
            a.push_back(value);
        }

        auto start = steady_clock::now();
        //cout << N << " elements: ";
        timsort(a);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish - start).count();
        cout << N << " elements: " << time << " ms" << endl;

        a.resize(0);
    }
}
