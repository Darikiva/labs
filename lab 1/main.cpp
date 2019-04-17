#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "lab3b.h"

using namespace std;
using namespace std::chrono;

unsigned int get_id()
{
    unsigned int id;
    ifstream file("id.txt");
    file >> id;
    file.close();
    return id;
}

class Product
{
public:
    string name;
    int amount;
    int meas_num;
    int term;
    tm date;
    unsigned int ID;
    void enter();
    void print();
    void get_id(unsigned int& id)
    {
        if (id==USHRT_MAX)
            id=1;
        ID = id;
        id++;
    };
    string measure[5] = {"", "kilograms", "liters", "pieces", "packages"};
    string rand_names[6] = {"lemon", "apple", "juice", "fish", "meat", "plate"};
private:
};

istream& operator>> (istream& in, tm& date)
{
    in >> date.tm_year;
    in >> date.tm_mon;
    in >> date.tm_mday;
    return in;
}

ostream& operator<< (ostream& out, vector <Product>& info_list)
{
    for(auto i:info_list)
    {
        i.print();
    }
    return out;
}

operator== (const Product& word1, const string& word2)
{
    if (word2.size()>word1.name.size())
        return false;
    for(unsigned int i=0; i<word2.size(); ++i)
        if (word1.name[word1.name.size()-1-i]!=word2[word2.size()-1-i])
            return false;
    return true;
}

operator== (const Product& product, const pair<tm, tm>& date_2)
{
    if(product.date.tm_year<date_2.first.tm_year)
        return false;
    if(product.date.tm_year>date_2.second.tm_year)
        return false;
    if(product.date.tm_year==date_2.first.tm_year||product.date.tm_year==date_2.second.tm_year)
    {
        if(product.date.tm_mon<date_2.first.tm_mon)
            return false;
        else if(product.date.tm_mon>date_2.second.tm_mon)
            return false;
        if (product.date.tm_mon==date_2.first.tm_mon||product.date.tm_mon==date_2.second.tm_mon)
        {
            if(product.date.tm_mday<date_2.first.tm_mday)
                return false;
            else if(product.date.tm_mday>date_2.first.tm_mday)
                return false;
        }
    }
    return true;
}

operator== (const Product& measure, const int& desired_meas)
{
    if(measure.meas_num==desired_meas)
        return true;
    else
        return false;
}

operator<(const tm date1, const tm date2)
{
    if(date1.tm_year<date2.tm_year)
        return true;
    if(date1.tm_yday>date2.tm_year)
        return false;
    if(date1.tm_mon<date2.tm_mon)
        return true;
    if(date1.tm_mon>date2.tm_mon)
        return false;
    if(date1.tm_mday<date2.tm_mday)
        return true;
    return false;
}

void delete_full_binary()
{
    ofstream file1("saved_list.bin", ios::trunc);
    file1.close();
}

void delete_full_txt()
{
    ofstream file("saved_list.txt", ios::trunc);
    file.close();
}

void add_product(vector <Product>& info_list, unsigned int& id)
{
    Product product;
    product.enter();
    product.get_id(id);
    info_list.push_back(product);
}

void save_txt(const vector <Product>& info_list)
{
    ofstream file("saved_list.txt", ofstream::app);
    for(auto item: info_list)
    {
        file << item.name << " " << item.meas_num << " ";
        file << item.amount << " ";
        file << item.date.tm_year << " " << item.date.tm_mon << " ";
        file << item.date.tm_mday << " " << item.term << " " << item.ID;
        file << endl;
    }
    file.close();
}

void save_binary(vector <Product> info_list)
{
    ofstream file("saved_list.bin", ios::in|ios::binary|ios::app);
    for(auto &i:info_list)
    {
        size_t name_size = i.name.size();
        file.write((char*)&name_size, sizeof (name_size));
        file.write(&i.name[0], name_size);
        file.write((char*)&i.meas_num, sizeof (int));
        file.write((char*)&i.amount, sizeof (int));
        file.write((char*)&i.date.tm_year, sizeof (int));
        file.write((char*)&i.date.tm_mon, sizeof (int));
        file.write((char*)&i.date.tm_mday, sizeof (int));
        file.write((char*)&i.term, sizeof (int));
        file.write((char*)&i.ID, sizeof(int));
    }
    file.close();
}

bool is_in_vector(const vector <Product>& info_list, unsigned int id)
{
    for(auto &i:info_list)
        if (i.ID == id)
            return true;
    return false;
}

void read_from_txt(vector <Product>& info_list)
{
    string line;
    ifstream file;
    file.open("saved_list.txt");
    while(getline(file, line))
    {
        Product new_product;
        istringstream record(line);
        record >> new_product.name;
        record >> new_product.meas_num;
        record >> new_product.amount;
        record >> new_product.date.tm_year >> new_product.date.tm_mon;
        record >> new_product.date.tm_mday;
        record >> new_product.term;
        record >> new_product.ID;
        if (!is_in_vector(info_list, new_product.ID))
            info_list.push_back(new_product);
    }
}

void read_from_binary(vector <Product>& info_list)
{
    ifstream file;
    file.open("saved_list.bin", ios::out|ios::binary);
    while(file.peek()!=EOF)
    {
        Product new_product;
        size_t name_size;
        file.read((char*)&name_size, sizeof (name_size));
        new_product.name.resize(name_size);
        file.read(&new_product.name[0], name_size);
        file.read((char*)&new_product.meas_num, sizeof (int));
        file.read((char*)&new_product.amount, sizeof(int));
        file.read((char*)&new_product.date.tm_year, sizeof(int));
        file.read((char*)&new_product.date.tm_mon, sizeof(int));
        file.read((char*)&new_product.date.tm_mday, sizeof (int));
        file.read((char*)&new_product.term, sizeof(int));
        file.read((char*)&new_product.ID, sizeof(int));
        if (!is_in_vector(info_list, new_product.ID))
            info_list.push_back(new_product);
    }
    file.close();
}

void print_all(vector <Product> info_list)
{
    read_from_binary(info_list);
    read_from_txt(info_list);
    if(info_list.size()!=0)
        cout << info_list;
}


template<typename T>
vector <Product> Find(vector <Product>& info_list, T element, int term = -1)
{
    vector <Product> result;
    for(auto item:info_list)
    {
        if (item == element)
        {
            if(term>-1&&item.term>term)
                result.push_back(item);
            else if (term==-1)
                result.push_back(item);
        }
    }
    return result;
}

void FIND(vector <Product> info_list)
{
    int choice, meas, term;
    string word;
    pair <tm, tm> date;
    vector <Product> result;

    read_from_txt(info_list);
    read_from_binary(info_list);

    cout << "1. Find by name\n";
    cout << "2. Find by measure\n";
    cout << "3. Find by date\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Enter the word: ";
        cin >> word;
        result = Find(info_list, word);
        break;

    case 2:
        cout << "Enter the number of measure: \n";
        cout << "1. kilograms\n";
        cout << "2. liters\n";
        cout << "3. pieces\n";
        cout << "4. packages\n";
        cin >> meas;
        cout << "Enter the term: ";
        cin >> term;
        result = Find(info_list, meas, term);
        break;

    case 3:
        cout << "Enter 2 dates: ";
        cin >> date.first;
        cin >> date.second;
        result = Find(info_list, date);
    }
    cout << result;
}

void modify(vector <Product> product_list)
{
    string name;
    cout << "Enter the name of modifying product: ";
    cin >> name;
    for(auto &item: product_list)
        if (item.name==name)
        {
            cout << item.name << " " << item.ID << endl;
            cout << "You want to modify this element?" << endl;
            cout << "1. Yes\n";
            cout << "2. No\n";
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                item.enter();
                break;
            case 2:
                break;
            }
        }
}

void modify_txt()
{
    vector <Product> new_list;
    read_from_txt(new_list);
    delete_full_txt();
    modify(new_list);
    save_txt(new_list);
}

void modify_bin()
{
    vector <Product> new_list;
    read_from_binary(new_list);
    delete_full_binary();
    modify(new_list);
    save_binary(new_list);
}

void delete_element(vector <Product>& info_list, string name)
{
    for(unsigned int i=0; i<info_list.size(); ++i)
    {
        if(info_list[i].name == name)
        {
            info_list.erase(info_list.begin()+i);
        }
    }
    vector <Product> new_list_bin;
    vector <Product> new_list_txt;
    read_from_txt(new_list_txt);
    read_from_binary(new_list_bin);
    delete_full_binary();
    delete_full_txt();
    for(unsigned int i=0; i<new_list_bin.size(); ++i)
    {
        if(new_list_bin[i].name == name)
            new_list_bin.erase(new_list_bin.begin()+i);
    }
    save_binary(new_list_bin);
    for(unsigned int i=0; i<new_list_txt.size(); ++i)
    {
        if(new_list_txt[i].name == name)
            new_list_txt.erase(new_list_txt.begin()+i);
    }
    save_txt(new_list_txt);
}

void help()
{
    cout << "1. Add\n";
    cout << "2. Find\n";
    cout << "3. Print\n";
    cout << "4. Save\n";
    cout << "5. Read from file\n";
    cout << "6. Delete from file\n";
    cout << "7. Delete element\n";
    cout << "8. Modify element\n";
    cout << "9. Counting sort (by measure)\n";
    cout << "10. Radix sort(by term)\n";
    cout << "11. Sort (by 1 or 2 fields)\n";
    cout << "12. Exit\n";
    return;
}

template <typename First, typename Second = nullptr_t>
void sort_list(vector <Product>& product_list,
               First (Product::*pointer1),
               Second (Product::*pointer2) = nullptr)
{
    sort(begin(product_list), end(product_list), [pointer1, pointer2](Product product1, Product product2)
    {
        if(product1.*pointer1 < product2.*pointer1)
            return true;
        if(product2.*pointer1 < product1.*pointer1)
            return false;
        if(pointer2!=nullptr)
        {
            if(product1.*pointer2 < product2.*pointer2) return true;
        }
        return false;
    });
    return;
}

int sort_command()
{
    int command;
    cout << "1. Name\n";
    cout << "2. Amount\n";
    cout << "3. Measure\n";
    cout << "4. Term\n";
    cout << "5. Date\n";
    cout << "Enter number: ";
    cin >> command;
    return command;
}

void sort_choice(vector <Product>& product_list)
{
    cout << "1. Sort by 1 field\n";
    cout << "2. Sort by 2 fields\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch(choice)
    {
    case 1:
    {
        switch(sort_command())
        {
        case 1:
            sort_list(product_list, &Product::name);
            break;
        case 2:
            sort_list(product_list, &Product::amount);
            break;
        case 3:
            sort_list(product_list, &Product::meas_num);
            break;
        case 4:
            sort_list(product_list, &Product::term);
            break;
        case 5:
            sort_list(product_list, &Product::date);
            break;
        default:
            cout << "No such sort!\n";
        }
    }
    break;
    case 2:
    {
        switch(sort_command())
        {
        case 1:
            switch(sort_command())
            {
            case 1:
                sort_list(product_list, &Product::name, &Product::name);
                break;
            case 2:
                sort_list(product_list, &Product::name, &Product::amount);
                break;
            case 3:
                sort_list(product_list, &Product::name, &Product::meas_num);
                break;
            case 4:
                sort_list(product_list, &Product::name, &Product::term);
                break;
            case 5:
                sort_list(product_list, &Product::name, &Product::date);
                break;
            }
            break;
        case 2:
            switch(sort_command())
            {
            case 1:
                sort_list(product_list, &Product::amount, &Product::name);
                break;
            case 2:
                sort_list(product_list, &Product::amount, &Product::amount);
                break;
            case 3:
                sort_list(product_list, &Product::amount, &Product::meas_num);
                break;
            case 4:
                sort_list(product_list, &Product::amount, &Product::term);
                break;
            case 5:
                sort_list(product_list, &Product::amount, &Product::date);
                break;
            }
            break;

        case 3:
            switch(sort_command())
            {
            case 1:
                sort_list(product_list, &Product::meas_num, &Product::name);
                break;
            case 2:
                sort_list(product_list, &Product::meas_num, &Product::amount);
                break;
            case 3:
                sort_list(product_list, &Product::meas_num, &Product::meas_num);
                break;
            case 4:
                sort_list(product_list, &Product::meas_num, &Product::term);
                break;
            case 5:
                sort_list(product_list, &Product::meas_num, &Product::date);
                break;
            }
            break;

        case 4:
            switch(sort_command())
            {
            case 1:
                sort_list(product_list, &Product::term, &Product::name);
                break;
            case 2:
                sort_list(product_list, &Product::term, &Product::amount);
                break;
            case 3:
                sort_list(product_list, &Product::term, &Product::meas_num);
                break;
            case 4:
                sort_list(product_list, &Product::term, &Product::term);
                break;
            case 5:
                sort_list(product_list, &Product::term, &Product::date);
                break;
            }
            break;

        case 5:
            switch(sort_command())
            {
            case 1:
                sort_list(product_list, &Product::date, &Product::name);
                break;
            case 2:
                sort_list(product_list, &Product::date, &Product::amount);
                break;
            case 3:
                sort_list(product_list, &Product::date, &Product::meas_num);
                break;
            case 4:
                sort_list(product_list, &Product::date, &Product::term);
                break;
            case 5:
                sort_list(product_list, &Product::date, &Product::date);
                break;
            }
            break;
        }
    }
    break;
    default:
        cout << "No such command!\n";
    }
}

void menu(vector<Product>& info_list, unsigned int& id);
void benchmark_bin(vector <Product>& info_list);
void benchmark_txt(vector<Product>& info_list);
void demonstrative(unsigned int& id);
void benchmark_sort(void(*func)(vector<Product>&));
template<typename First, typename Second = nullptr_t>
void benchmark_sort(void(*func)(vector<Product>&, First (Product::*pointer1), Second (Product::*pointer2)),
                    First (Product::*field1), Second (Product::*field2) = nullptr);

int main()
{
    unsigned int id = get_id();
    vector <Product> info_list;
    int mode_choice;
    int choice, command;
    cout << "1. Interactive\n";
    cout << "2. Demonstrative\n";
    cout << "3. Benchmark\n";
    cout << "Enter the number of mode: ";
    cin >> mode_choice;
    switch (mode_choice)
    {
    case(1):
    {
        menu(info_list, id);
    }
    break;
    case 2:
        demonstrative(id);
        break;
    case 3:
        cout << "1. Benchmark txt\n";
        cout << "2. Benchmark bin\n";
        cout << "3. Benchmark sort\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice)
        {
        case 1:
            benchmark_txt(info_list);
            break;
        case 2:
            benchmark_bin(info_list);
            break;
        case 3:
            {
                cout << "1. Counting sort\n";
                cout << "2. Radix sort\n";
                cout << "3. Sort by 1 field(name or amount)\n";
                cout << "4. Sort by 2 fields(name+amount or measure+date)\n";
                cout << "Enter your choice: ";
                cin >> command;
                switch(command)
                {
                case 1:
                    benchmark_sort(counting_sort);
                    break;
                case 2:
                    benchmark_sort(radix_sort);
                    break;
                case 3:
                    cout << "1. Name\n";
                    cout << "2. Amount\n";
                    cout << "Enter your command: ";
                    cin >> command;
                    switch(command)
                    {
                    case 1:
                        benchmark_sort(sort_list, &Product::name);
                        break;
                    case 2:
                        benchmark_sort(sort_list, &Product::amount);
                        break;
                    default:
                        cout << "No such command!\n";
                    }
                    break;
                case 4:
                    cout << "1. Name + amount\n";
                    cout << "2. Measure + date\n";
                    cout << "Enter your command: ";
                    cin >> command;
                    switch(command)
                    {
                    case 1:
                        benchmark_sort(sort_list, &Product::name, &Product::amount);
                        break;
                    case 2:
                        benchmark_sort(sort_list, &Product::meas_num, &Product::date);
                        break;
                    default:
                        cout << "No such command!\n";
                    }
                    break;
                default:
                    cout << "No such command!\n";
                }
            }
            break;
            default:
                cout << "No such option!\n";
        }
        break;
    }
    ofstream file("id.txt");
    file << id;
    file.close();
    return 0;
}

void Product::enter()
{
    Product new_product;
    cout << "Enter the name of the product: ";
    cin >> name;
    cout << "1) kilograms\n";
    cout << "2) liters\n";
    cout << "3) pieces\n";
    cout << "4) packages\n";
    cin >> meas_num;
    while(meas_num>4&&meas_num<1)
    {
        cout << "Wrong measure. Try again: ";
        cin >> meas_num;
    }
    cout << "Enter amount of the product: ";
    cin >> amount;
    cout << "Enter production date and time (year month day): ";
    cin >> date;
    cout << "Enter the expiration date: ";
    cin >> term;
    while(term/365>10000)
    {
        cout << "Wrong term, try again: ";
        cin >> term;
    }
}

void Product::print()
{
    cout << "Name: " << name << endl;
    cout << "Amount: " << amount << " " << measure[meas_num] << endl;
    cout << "Term: " << term << " days" << endl;
    cout << "Date: " << date.tm_year << "." << date.tm_mon << ".";
    cout << date.tm_mday << endl;
    cout << "ID: " << ID << endl;
    cout << endl;
}

void menu(vector<Product>& info_list, unsigned int& id)
{
    int number, choice;
    string name;
    while(cin)
    {
        help();
        cout << "Enter the number of command: ";
        cin >> number;
        switch(number)
        {
        case 1:
            add_product(info_list, id);
            break;
        case 2:
            FIND(info_list);
            break;
        case 3:
            print_all(info_list);
            break;
        case 4:
            cout << "1. Binary\n";
            cout << "2. txt\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                save_binary(info_list);
                break;
            case 2:
                save_txt(info_list);
                break;
            }
            break;
        case 5:
            cout << "1. Binary\n";
            cout << "2. txt\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                read_from_binary(info_list);
                break;
            case 2:
                read_from_txt(info_list);
                break;
            }
            break;
        case 6:
            delete_full_binary();
            delete_full_txt();
            break;
        case 7:
            cout << "Enter the name of deleted product: ";
            cin >> name;
            delete_element(info_list, name);
            break;
        case 8:
            cout << "1. From txt\n";
            cout << "2. From bin\n";
            cout << "3. From vector\n";
            cin >> choice;
            switch(choice)
            {
            case 1:
                modify_txt();
                break;
            case 2:
                modify_bin();
                break;
            case 3:
                modify(info_list);
                break;
            }
            break;
        case 9:
            counting_sort(info_list);
            break;
        case 10:
            radix_sort(info_list);
            break;
        case 11:
            sort_choice(info_list);
            break;
        case 12:
            return;
        }
    }
}

void benchmark_bin(vector <Product>& info_list)
{
    cout << "**************BENCHMARK BINARY*************\n";

    unsigned int time = 0;
    pair<tm, tm> date;
    int N = 10, l = 2, n = 0;

    while(time<=10000)
    {
        date.first.tm_year = rand()%2019;
        date.first.tm_mon = rand()%12;
        date.first.tm_mday = rand()%31;
        date.second.tm_year = date.first.tm_year + rand()%2019;
        date.second.tm_mon = date.first.tm_mon + rand()%12;
        date.second.tm_mday = date.first.tm_mday + rand()%31;
        Product product;
        delete_full_binary();

        if(time<=1000)
        {
            N*=2;
        }
        else
        {
            if (n==0)
                n = N;
            N = n*l;
            ++l;
        }

        for(int i=0; i<N; ++i)
        {
            Product new_product;
            new_product.name = new_product.rand_names[rand()%6];
            new_product.amount = rand()%1000;
            new_product.meas_num = rand()%4+1;
            new_product.term = rand()%10000;
            new_product.date.tm_year = rand()%2019;
            new_product.date.tm_mon = rand()%12+1;
            new_product.date.tm_mday = rand()%31+1;
            info_list.push_back(new_product);
        }

        string name = info_list[0].rand_names[rand()%6];
        auto start = steady_clock::now();
        save_binary(info_list);
        Find(info_list, name);
        Find(info_list, 2, 150);
        Find(info_list, date);
        info_list.resize(0);
        read_from_binary(info_list);
        auto finish = steady_clock::now();

        info_list.resize(0);
        time = duration_cast<milliseconds>(finish-start).count();
        cout << N << " : " << time << " ms\n";
    }

    delete_full_binary();
    cout << "****************************\n";
}

void benchmark_txt(vector <Product>& info_list)
{
    cout << "*****************BENCHMARK TXT********************\n";

    unsigned int time = 0;
    pair<tm, tm> date;
    int N = 10, l = 2, n = 0;

    while(time<=10000)
    {
        date.first.tm_year = rand()%2019;
        date.first.tm_mon = rand()%12;
        date.first.tm_mday = rand()%31;
        date.second.tm_year = date.first.tm_year + rand()%2019;
        date.second.tm_mon = date.first.tm_mon + rand()%12;
        date.second.tm_mday = date.first.tm_mday + rand()%31;
        Product product;
        delete_full_txt();

        if(time<=1000)
        {
            N*=2;
        }
        else
        {
            if (n==0)
                n = N;
            N = n*l;
            ++l;
        }

        auto start = steady_clock::now();
        for(int i=0; i<N; ++i)
        {
            Product new_product;
            new_product.name = new_product.rand_names[rand()%6];
            new_product.amount = rand()%1000;
            new_product.meas_num = rand()%4+1;
            new_product.term = rand()%10000;
            new_product.date.tm_year = rand()%2019;
            new_product.date.tm_mon = rand()%12+1;
            new_product.date.tm_mday = rand()%31+1;
            info_list.push_back(new_product);
        }

        string name = info_list[0].rand_names[rand()%6];
        save_txt(info_list);
        Find(info_list, name);
        Find(info_list, 2, 150);
        Find(info_list, date);
        info_list.resize(0);
        read_from_txt(info_list);
        info_list.resize(0);
        auto finish = steady_clock::now();

        time = duration_cast<milliseconds>(finish-start).count();
        cout << N << " : " << time << " ms\n";
    }
    delete_full_txt();
}

void demonstrative(unsigned int& id)
{
    vector <Product> info_list;
    vector <Product> trash_list;
    int number = 40;

    for(int i=0; i<number; ++i)
    {
        Product new_product;
        new_product.name = new_product.rand_names[rand()%6];
        new_product.meas_num = 1;
        new_product.amount = rand()%1000;
        new_product.date.tm_year = rand()%2019+1;
        new_product.date.tm_mon = rand()%12+1;
        new_product.date.tm_mday = rand()%31+1;
        new_product.term = rand()%10000;
        new_product.get_id(id);
        info_list.push_back(new_product);
    }
    cout << "Made " << number << " new elements:\n";
    cout << info_list;
    cout << "*********\n";

    cout << "Save to binary file\n";
    save_binary(info_list);
    cout << "*********\n";

    cout << "Delete vector\n";
    info_list.resize(0);
    cout << "*********\n";

    cout << "Read from binary file and print\n";
    read_from_binary(info_list);
    cout << info_list;
    cout << "*********";

    cout << "Save to txt file\n";
    save_txt(info_list);
    cout << "*********\n";

    cout << "Delete vector\n";
    info_list.resize(0);

    cout << "Read from txt file and print\n";
    read_from_txt(info_list);
    cout << info_list;
    cout << "*********\n";

    cout << "Delete all elements with name 'juice':\n";
    delete_element(info_list, "juice");
    cout << info_list;
    cout << "*********\n";

    cout << "Find elements with name 'meat':\n";
    trash_list = Find(info_list, "meat");
    cout << trash_list;
    cout << "*********\n";

    cout << "Find elements with name 'juice' (should be written elements from file):\n";
    trash_list = Find(info_list, "juice");
    cout << trash_list;
    cout << "*********\n";

    cout << "Find elements which were made between 1000.10.09 and 2000.8.12\n";
    pair <tm, tm> date;
    date.first.tm_year = 1000;
    date.first.tm_mon = 10;
    date.first.tm_mday = 9;
    date.second.tm_year = 2000;
    date.second.tm_mon = 8;
    date.second.tm_mday = 12;
    trash_list = Find(info_list, date);
    cout << trash_list;
    cout << "*********\n";

    cout << "Find elements, which measure is kilograms, and which term isn't less, than 500 days:\n";
    trash_list = Find(info_list, 1, 500);
    cout << trash_list;
    cout << "**********\n";

    cout << "Delete all elements with name 'apple':\n";
    delete_element(info_list, "apple");
    cout << info_list;
    cout << "*********";

    delete_full_binary();
    delete_full_txt();

}

void benchmark_sort(void (*func)(vector <Product>&))
{
    vector <Product> info_list;
    unsigned int time = 0;
    pair<tm, tm> date;
    int N = 10, l = 2, n = 0;
    while(time<=6000)
    {
        if(time<=1000)
        {
            N*=2;
        }
        else
        {
            if (n==0)
                n = N;
            N = n*l;
            ++l;
        }

        for(int i=0; i<N; ++i)
        {
            Product new_product;
            new_product.name = new_product.rand_names[rand()%6];
            new_product.amount = rand()%1000;
            new_product.meas_num = rand()%4+1;
            new_product.term = rand()%10000;
            new_product.date.tm_year = rand()%2019;
            new_product.date.tm_mon = rand()%12+1;
            new_product.date.tm_mday = rand()%31+1;
            info_list.push_back(new_product);
        }

        string name = info_list[0].rand_names[rand()%6];
        auto start = steady_clock::now();
        func(info_list);
        auto finish = steady_clock::now();
        info_list.resize(0);
        time = duration_cast<milliseconds>(finish-start).count();
        cout << N << " : " << time << " ms\n";
    }
}

template<typename First, typename Second>
void benchmark_sort(void(*func)(vector<Product>&, First (Product::*pointer1), Second (Product::*pointer2)),
                    First (Product::*field1), Second (Product::*field2))
{
    vector <Product> info_list;
    unsigned int time = 0;
    pair<tm, tm> date;
    int N = 10, l = 2, n = 0;
    while(time<=6000)
    {
        if(time<=1000)
        {
            N*=2;
        }
        else
        {
            if (n==0)
                n = N;
            N = n*l;
            ++l;
        }

        for(int i=0; i<N; ++i)
        {
            Product new_product;
            new_product.name = new_product.rand_names[rand()%6];
            new_product.amount = rand()%1000;
            new_product.meas_num = rand()%4+1;
            new_product.term = rand()%10000;
            new_product.date.tm_year = rand()%2019;
            new_product.date.tm_mon = rand()%12+1;
            new_product.date.tm_mday = rand()%31+1;
            info_list.push_back(new_product);
        }

        string name = info_list[0].rand_names[rand()%6];
        auto start = steady_clock::now();
        func(info_list, field1, field2);
        auto finish = steady_clock::now();
        info_list.resize(0);
        time = duration_cast<milliseconds>(finish-start).count();
        cout << N << " : " << time << " ms\n";
    }
}
