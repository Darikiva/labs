template<typename T>
void counting_sort(std::vector<T>& info_list)
{
    using namespace std;

    size_t n = info_list.size();
    vector<int> counter(4, 0);
    T new_product;
    vector<T> boofer(n, new_product);
    for(size_t i=0; i<n; i++)
    {
        counter[info_list[i].meas_num-1]++;
    }
    for(size_t i=1; i<4; i++)
    {
        counter[i]+=counter[i-1];
    }

    for(int i=n-1; i>=0; i--)
    {
        counter[info_list[i].meas_num-1]--;
        boofer[counter[info_list[i].meas_num-1]] = info_list[i];
    }
    info_list = boofer;
    return;
}

template<typename T>
void radix_sort(std::vector<T>& info_list)
{
    using namespace std;
    int max = 10000;
    int base = 10;
    vector< vector<T> > boofers(base);
    for (int b = 1; b < max; b *= base)
    {
        for( auto& boof : boofers) { boof.clear(); }

        for (auto cur : info_list)
        {
            boofers[ (cur.term / b) % base].push_back(cur);
        }

        info_list.clear();
        for( auto& boof : boofers)
        {
            info_list.insert(info_list.end(), boof.begin(), boof.end());
        }
    }
}
