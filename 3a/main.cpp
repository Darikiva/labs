#include <iostream>
#include <algorithm>
#include <chrono>
#include <algorithm>
template <typename T>
void insertion_sort(T *sorted_list, int left, int right, bool is_demonstration = false)
{
    if(right-left<=0) return;
    if(sorted_list[left]>sorted_list[left+1])
    {
        std::swap(sorted_list[left], sorted_list[left+1]);
    }
    for(int j=left+1; j<=right; j++)
    {
        T key = sorted_list[j];
        int i = int(j)-1;
        while(i>=int(left)&&sorted_list[i]>key)
        {
            sorted_list[i+1] = sorted_list[i];
            i--;
        }
        sorted_list[i+1] = key;
        if(is_demonstration)
        {
            std::cout << std::endl << "\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
            for(int index=0; index<=(right-left); index++)
            {
                std::cout << sorted_list[index] << " ";
            }
            std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
            std::cout << std::endl;
        }
    }
}

template <typename T>
int partition_(T *sorted_list, int left, int right)
{
    if(left>=right) return right;
    int i = left;
    for(int j=left; j<right; j++)
    {
        if(sorted_list[j]<=sorted_list[right])
        {
            std::swap(sorted_list[i], sorted_list[j]);
            i++;
        }
    }
    std::swap(sorted_list[i], sorted_list[right]);
    return i;
}

template <typename T>
void quick_sort(T *sorted_list, int left, int right, bool is_demonstration = false)
{
    if (left>=right) return;
    int p = partition_(sorted_list, left, right);
    if(is_demonstration)
    {
        std::cout << std::endl << "\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
        for(int index=0; index<=(right-left); index++)
        {
            std::cout << sorted_list[index] << " ";
        }
        std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
        std::cout << std::endl;
    }
    if(p>0) quick_sort(sorted_list, left, p-1, is_demonstration);
    if(p<right) quick_sort(sorted_list, p+1, right, is_demonstration);
}

template <typename T>
T* merge_sort(T *sorted_list, T *boofer, int left, int right,      // combined sort was implemented as
              int threshold = -1, bool is_demonstration = false)   // a part of merge sort
{
    if(is_demonstration)
        {
            std::cout << std::endl << "\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
            for(int index=0; index<=(right-left); index++)
            {
                std::cout << sorted_list[index] << " ";
            }
            std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\" << std::endl;
            std::cout << std::endl;
        }

    if(right-left<threshold)
    {
        for(int i=left; i<=right; i++)
        {
            bool q = true;
            for(int j=left; j<=right-i; j++)
            {
                if(sorted_list[i]<sorted_list[j])
                {
                    std::swap(sorted_list[i], sorted_list[j]);
                    q = false;
                }
            }
            if(q) break;
        }
        return sorted_list;
    }

    if (left == right)
    {
        boofer[left] = sorted_list[left];
        return boofer;
    }

    int middle = (left + right) / 2;

    T *l_buff = merge_sort(sorted_list, boofer, left, middle, is_demonstration);
    T *r_buff = merge_sort(sorted_list, boofer, middle + 1, right, is_demonstration);

    T *target = l_buff == sorted_list ? boofer : sorted_list;

    int l_cur = left, r_cur = middle + 1;
    for (int i = left; i <= right; i++)
    {
        if (l_cur <= middle && r_cur <= right)
        {
            if (l_buff[l_cur] < r_buff[r_cur])
            {
                target[i] = l_buff[l_cur];
                l_cur++;
            }
            else
            {
                target[i] = r_buff[r_cur];
                r_cur++;
            }
        }
        else if (l_cur <= middle)
        {
            target[i] = l_buff[l_cur];
            l_cur++;
        }
        else
        {
            target[i] = r_buff[r_cur];
            r_cur++;
        }
    }
    return target;
}

void demonstration(int*, int, void (*func)(int*, int, int, bool));
void demonstration(int*, int, int* (*func)(int*, int*, int, int, int, bool), int range = -1);
void demonstration_total(int);
unsigned benchmark(int sorted_list[], int N, void (*func)(int*, int, int, bool));
unsigned benchmark(int sorted_list[], int N, int* (*func)(int*, int*, int, int, int, bool), int range = -1);
void benchmark_total();

int help()
{
    using namespace std;
    cout << "1. Demonstration\n";
    cout << "2. Benchmark\n";
    cout << "3. Exit\n";
    cout << "Enter your choice(only numbers!): ";
    int choice;
    cin >> choice;
    if(!cin) throw runtime_error("Error! Only numbers can be used!");
    return choice;
}

int main()
{
    try
    {
        for(;;)
        {
            switch(help())
            {
            case 1:
                int n;
                std::cout << "Enter number of elements: ";
                std::cin >> n;
                demonstration_total(n);
                break;
            case 2:
                benchmark_total();
                break;
            case 3:
                return 0;
            default:
                std::cout << "No such command, try again\n";
            }
        }
    }
    catch(std::runtime_error ex)
    {
        std::cout << ex.what();
    }
    return 0;
}

void demonstration(int* sorted_list, int N, void (*func)(int*, int, int, bool))
{
    using namespace std;

    cout << "*****************Input massive******************* \n" << endl;
    for(int i=0; i<N; i++)
    {
        cout << sorted_list[i] << " ";
    }

    func(sorted_list, 0, N-1, true);

    cout << endl << "*****************Sorted massive******************* " << endl;
    for(int i=0; i<N; i++)
    {
        cout << sorted_list[i] << " ";
    }
    cout << endl;
}

void demonstration(int* sorted_list, int N, int* (*func)(int*, int*, int, int, int, bool), int range)
{
    using namespace std;

    int boof[N];

    cout << "*****************Input massive******************* \n" << endl;
    for(int i=0; i<N; i++)
    {
        cout << sorted_list[i] << " ";
    }

    func(sorted_list, boof, 0, N-1, range, true);

    cout << endl << "*****************Sorted massive******************* " << endl;
    for(int i=0; i<N; i++)
    {
        cout << sorted_list[i] << " ";
    }
    cout << endl;
}

void demonstration_total(int N)
{
    using namespace std;

    int sorted_list[N];
    cout << "****RANDOM MASSIVE******" << endl;

    for(int i=0; i<N; i++)
    {
        sorted_list[i] = rand()%1000 - rand()%2000;
    }
    cout << "INSERTION SORT" << endl << endl;
    demonstration(sorted_list, N, insertion_sort);

    cout << "QUICK SORT" << endl << endl;
    demonstration(sorted_list, N, quick_sort);

    cout << "MERGE SORT" << endl << endl;
    demonstration(sorted_list, N, merge_sort);

    cout << "COMBINED SORT (range is N/10)" << endl << endl;
    demonstration(sorted_list, N, merge_sort, N/10);
    /////////////////////
    /////////////////////

    cout << "****MASSIVE IN THE CORRECT ORDER******" << endl;

    for(int i=0; i<N; i++)
    {
        if(i!=0) sorted_list[i] = sorted_list[i-1] + rand()%100;
        else sorted_list[i] = -rand()%2000;
    }

    cout << "INSERTION SORT" << endl << endl;
    demonstration(sorted_list, N, insertion_sort);

    cout << "QUICK SORT" << endl << endl;
    demonstration(sorted_list, N, quick_sort);

    cout << "MERGE SORT" << endl << endl;
    demonstration(sorted_list, N, merge_sort);

    cout << "COMBINED SORT (range is N/10)" << endl << endl;
    demonstration(sorted_list, N, merge_sort, N/10);
    /////////////////////
    /////////////////////

    cout << "****MASSIVE IN THE INCORRECT ORDER******" << endl;

    for(int i=0; i<N; i++)
    {
        if(i!=0) sorted_list[i] = sorted_list[i-1] - rand()%100;
        else sorted_list[i] = rand()%2000;
    }

    cout << "INSERTION SORT" << endl << endl;
    demonstration(sorted_list, N, insertion_sort);

    cout << "QUICK SORT" << endl << endl;
    demonstration(sorted_list, N, quick_sort);

    cout << "MERGE SORT" << endl << endl;
    demonstration(sorted_list, N, merge_sort);

    cout << "COMBINED SORT (range is N/10)" << endl << endl;
    demonstration(sorted_list, N, merge_sort, N/10);
}

unsigned benchmark(int sorted_list[], int N, void (*func)(int*, int, int, bool))
{
    using namespace std;
    using namespace std::chrono;

    auto start = steady_clock::now();

    func(sorted_list, 0, N-1, false);

    auto finish = steady_clock::now();

    unsigned time = duration_cast<milliseconds>(finish-start).count();
    return time;
}

unsigned benchmark(int sorted_list[], int N, int* (*func)(int*, int*, int, int, int, bool), int range)
{
    using namespace std::chrono;

    int* boof = new int[N];

    auto start = steady_clock::now();

    func(sorted_list, boof, 0, N-1, range, false);

    auto finish = steady_clock::now();

    unsigned time = duration_cast<milliseconds>(finish-start).count();
    return time;
}

void benchmark_total()
{
    using namespace std;

    bool q1 = true, q2 = true, q3 = true, q4 = true, q5 = true;
    unsigned time1, time2, time3, time4, time5;

    int N = 10, l = 2, n = 0;
    cout << "Random elements: " << endl;
    while((q1||q2||q3||q4||q5)&&N<13'000'000)
    {
        cout << N << " elements: " << endl;

        if(N>=100'000'000) q1 = false;
        int* sorted_list = new int[N];
        int* boof = new int[N];

        for(int i=0; i<N; i++)
        {
            sorted_list[i] = rand()%N;
        }

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Insertion sort: ";
        if(q1)
        {
            time1 = benchmark(boof, N, insertion_sort);
            cout << time1 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Quick sort: ";
        if(q2)
        {
            time2 = benchmark(boof, N, quick_sort);
            cout << time2 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Merge sort: ";
        if(q3)
        {
            time3 = benchmark(boof, N, merge_sort);
            cout << time3<< "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' << "Combined(merge+bubble) sort: ";
        if(q4)
        {
            time4 = benchmark(boof, N, merge_sort, 10);
            cout << time4 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }

        cout << '\t' <<"Library sort: ";
        if(q5)
        {
            using namespace std::chrono;
            auto start = steady_clock::now();

            sort(boof, boof+N);

            auto finish = steady_clock::now();

            time5 = duration_cast<milliseconds>(finish-start).count();
            cout << time5 << "ms" << endl;
        }
        else cout << "too long" << endl;

        if(time1>=10000) q1 = false;
        if(time2>=10000) q2 = false;
        if(time3>=10000) q3 = false;
        if(time4>=10000) q4 = false;
        if(time5>=10000) q5 = false;

        if(N<10000) N*=2;
        else if(N>=100'000)
        {
            N+=N*0.7;
        }
        else
        {
            if(n==0) n = N;
            N = l*n;
            l++;
        }

        delete sorted_list;
        delete boof;
    }


    q1 = true; q2 = true; q3 = true; q4 = true; q5 = true;
    time1 = 0; time2 = 0; time3 = 0; time4 = 0; time5 = 0;
    cout << endl << endl;

    N = 10, l = 2, n = 0;
    cout << '\t' << "Massive in correct order elements: " << endl;
    while((q1||q2||q3||q4||q5)&&N<13'000'000)
    {
        cout << N << " elements: " << endl;

        if(N>=40'000) q2 = false;
        if(N>=100'000'000) q1 = false;

        int* sorted_list = new int[N];
        int* boof = new int[N];

        for(int i=0; i<N; i++)
        {
            if(i!=0) sorted_list[i] = rand()%100+sorted_list[i-1];
            else sorted_list[i] = -rand()%10000;
        }

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Insertion sort: ";
        if(q1)
        {
            time1 = benchmark(boof, N, insertion_sort);
            cout << time1 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Quick sort: ";
        if(q2)
        {
            time2 = benchmark(boof, N, quick_sort);
            cout << time2 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Merge sort: ";
        if(q3)
        {
            time3 = benchmark(boof, N, merge_sort);
            cout << time3<< "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' << "Combined(merge+bubble) sort: ";
        if(q4)
        {
            time4 = benchmark(boof, N, merge_sort, 10);
            cout << time4 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Library sort: ";
        if(q5)
        {
            using namespace std::chrono;
            auto start = steady_clock::now();

            sort(boof, boof+N);

            auto finish = steady_clock::now();

            time5 = duration_cast<milliseconds>(finish-start).count();
            cout << time5 << "ms" << endl;
        }
        else cout << "too long" << endl;

        if(time1>=10000) q1 = false;
        if(time2>=10000) q2 = false;
        if(time3>=10000) q3 = false;
        if(time4>=10000) q4 = false;
        if(time5>=10000) q5 = false;

        if(N<10000) N*=2;
        else if(N>=100'000)
        {
            N+=N*0.7;
        }
        else
        {
            if(n==0) n = N;
            N = l*n;
            l++;
        }

        delete sorted_list;
        delete boof;
    }

    q1 = true; q2 = true; q3 = true; q4 = true; q5 = true;
    time1 = 0; time2 = 0; time3 = 0; time4 = 0; time5 = 0;

    cout << endl << endl;

    N = 10, l = 2, n = 0;
    cout << '\t' << "Massive in incorrect order: " << endl;
    while((q1||q2||q3||q4||q5)&&N<13'000'000)
    {
        cout << N << " elements: " << endl;

        if(N>=40'000) q2 = false;
        if(N>=100'000'000) q1 = false;

        int* sorted_list = new int[N];
        int* boof = new int[N];

        for(int i=0; i<N; i++)
        {
            if(i!=0) sorted_list[i] = sorted_list[i-1] - rand()%100;
            else sorted_list[i] = rand()%10000;
        }

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Insertion sort: ";
        if(q1)
        {
            time1 = benchmark(boof, N, insertion_sort);
            cout << time1 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Quick sort: ";
        if(q2)
        {
            time2 = benchmark(boof, N, quick_sort);
            cout << time2 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Merge sort: ";
        if(q3)
        {
            time3 = benchmark(boof, N, merge_sort);
            cout << time3<< "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' << "Combined(merge+bubble) sort: ";
        if(q4)
        {
            time4 = benchmark(boof, N, merge_sort, 10);
            cout << time4 << "ms" << endl;
        }
        else cout << "too long" << endl;

        for(int i=0; i<N; i++)
        {
            boof[i] = sorted_list[i];
        }
        cout << '\t' <<"Library sort: ";
        if(q5)
        {
            using namespace std::chrono;
            auto start = steady_clock::now();

            sort(boof, boof+N);

            auto finish = steady_clock::now();

            time5 = duration_cast<milliseconds>(finish-start).count();
            cout << time5 << "ms" << endl;
        }
        else cout << "too long" << endl;

        if(time1>=10000) q1 = false;
        if(time2>=10000) q2 = false;
        if(time3>=10000) q3 = false;
        if(time4>=10000) q4 = false;
        if(time5>=10000) q5 = false;

        if(N<10000) N*=2;
        else if(N>=100'000)
        {
            N+=N*0.7;
        }
        else
        {
            if(n==0) n = N;
            N = l*n;
            l++;
        }
        delete sorted_list;
        delete boof;
    }
}

