#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

struct TTnode
{
    std::vector<double> values;
    TTnode *first = nullptr;
    TTnode *second = nullptr;
    TTnode *third = nullptr;
    TTnode *fourth = nullptr;
    TTnode *parent = nullptr;

    bool find(double k)
    {
        for (const auto& i:values)
            if (i == k)
                return true;
        return false;
    }

    void insert_to_node(double value)
    {
        values.push_back(value);
        sort(values.begin(), values.end());
    }

    void remove_from_node(double value)
    {
        if(values.size()>=1 && values[0] == value)
        {
            values.erase(values.begin());
        }
        else if(values.size()==2 && values[1] == value)
        {
            values[0] = values[1];
            values.pop_back();
        }
    }

    void become_node2(double k, TTnode *first_, TTnode *second_)
    {
        values.resize(0);
        values.push_back(k);

        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
    }

    bool is_leaf()
    {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
    }
    TTnode(double k)
    {
        values.push_back(k);
    }

    TTnode (double k, TTnode *first_, TTnode *second_, TTnode *third_, TTnode *fourth_, TTnode *parent_):
        values{k}, first(first_), second(second_), third(third_), fourth(fourth_), parent(parent_) {}

    friend TTnode *split(TTnode *item);
    friend TTnode *add(TTnode *p, double k);
    friend void print(TTnode*);
};

void do_something(TTnode* root, double (*f)(double))
{
    if(root==nullptr)
        return;
    do_something(root->first, f);
    root->values[0] = f(root->values[0]);
    do_something(root->second, f);
    if(root->values.size()==2)
        root->values[1] = f(root->values[1]);
    do_something(root->third, f);
}

int calculate_memory(TTnode* root)
{
    if(root==nullptr)
        return 0;
    int answer = sizeof(root);
    for(int i=0; i<root->values.size(); i++)
        answer+=sizeof(root->values[i]);
    answer+=calculate_memory(root->first);
    answer+=calculate_memory(root->second);
    answer+=calculate_memory(root->third);
    return answer;
}

TTnode *search(TTnode *p, double k)
{
    if (!p)
        return nullptr;

    if (p->find(k))
        return p;
    else if (k < p->values[0])
        return search(p->first, k);
    else if ((p->values.size() == 2) && (k < p->values[1]) || (p->values.size() == 1))
        return search(p->second, k);
    else if (p->values.size() == 2)
        return search(p->third, k);
}

TTnode* add(TTnode** root, double value)
{
    if (!*root)
    {
        *root = new TTnode(value);
        return *root;
    }

    if ((*root)->is_leaf())
        (*root)->insert_to_node(value);
    else if (value <= (*root)->values[0])
        add(&(*root)->first, value);
    else if (((*root)->values.size() == 1) || (((*root)->values.size() == 2)
             && value <= (*root)->values[1]))
        add(&(*root)->second, value);
    else
        add(&(*root)->third, value);

    return split(*root);
}

TTnode *split(TTnode *node)
{
    if (node->values.size() < 3)
        return node;

    TTnode *x = new TTnode(node->values[0], node->first, node->second, nullptr, nullptr, node->parent);
    TTnode *y = new TTnode(node->values[2], node->third, node->fourth, nullptr, nullptr, node->parent);
    if (x->first)
        x->first->parent = x;
    if (x->second)
        x->second->parent = x;
    if (y->first)
        y->first->parent = y;
    if (y->second)
        y->second->parent = y;

    if (node->parent)
    {
        node->parent->insert_to_node(node->values[1]);

        if (node->parent->first == node)
            node->parent->first = nullptr;
        else if (node->parent->second == node)
            node->parent->second = nullptr;
        else if (node->parent->third == node)
            node->parent->third = nullptr;

        if (node->parent->first == nullptr)
        {
            node->parent->fourth = node->parent->third;
            node->parent->third = node->parent->second;
            node->parent->second = y;
            node->parent->first = x;
        }
        else if (node->parent->second == nullptr)
        {
            node->parent->fourth = node->parent->third;
            node->parent->third = y;
            node->parent->second = x;
        }
        else
        {
            node->parent->fourth = y;
            node->parent->third = x;
        }

        TTnode *tmp = node->parent;
        delete node;
        return tmp;
    }
    else
    {
        x->parent = node;
        y->parent = node;
        node->become_node2(node->values[1], x, y);
        return node;
    }
}

TTnode *search_min(TTnode *p)   // Поиск узла с минимальным элементов в 2-3-дереве с корнем p.
{
    if (!p)
        return p;
    if (!(p->first))
        return p;
    else
        return search_min(p->first);
}

TTnode *redistribute(TTnode *leaf)
{
    TTnode *parent = leaf->parent;
    TTnode *first = parent->first;
    TTnode *second = parent->second;
    TTnode *third = parent->third;

    if ((parent->values.size() == 2) && (first->values.size() < 2) && (second->values.size() < 2) && (third->values.size() < 2))
    {
        if (first == leaf)
        {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = nullptr;
            parent->first->insert_to_node(parent->values[0]);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first != nullptr)
                parent->first->first = leaf->first;
            else if (leaf->second != nullptr)
                parent->first->first = leaf->second;

            if (parent->first->first != nullptr)
                parent->first->first->parent = parent->first;

            parent->remove_from_node(parent->values[0]);
            delete first;
        }
        else if (second == leaf)
        {
            first->insert_to_node(parent->values[0]);
            parent->remove_from_node(parent->values[0]);
            if (leaf->first != nullptr)
                first->third = leaf->first;
            else if (leaf->second != nullptr)
                first->third = leaf->second;

            if (first->third != nullptr)
                first->third->parent = first;

            parent->second = parent->third;
            parent->third = nullptr;

            delete second;
        }
        else if (third == leaf)
        {
            second->insert_to_node(parent->values[1]);
            parent->third = nullptr;
            parent->remove_from_node(parent->values[1]);
            if (leaf->first != nullptr)
                second->third = leaf->first;
            else if (leaf->second != nullptr)
                second->third = leaf->second;

            if (second->third != nullptr)
                second->third->parent = second;

            delete third;
        }
    }
    else if ((parent->values.size() == 2) && ((first->values.size() == 2)
             || (second->values.size() == 2) || (third->values.size() == 2)))
    {
        if (third == leaf)
        {
            if (leaf->first != nullptr)
            {
                leaf->second = leaf->first;
                leaf->first = nullptr;
            }

            leaf->insert_to_node(parent->values[1]);
            if (second->values.size() == 2)
            {
                parent->values[1] = second->values[1];
                second->remove_from_node(second->values[1]);
                leaf->first = second->third;
                second->third = nullptr;
                if (leaf->first != nullptr)
                    leaf->first->parent = leaf;
            }
            else if (first->values.size() == 2)
            {
                parent->values[1] = second->values[0];
                leaf->first = second->second;
                second->second = second->first;
                if (leaf->first != nullptr)
                    leaf->first->parent = leaf;

                second->values[0] = parent->values[0];
                parent->values[0] = first->values[1];
                first->remove_from_node(first->values[1]);
                second->first = first->third;
                if (second->first != nullptr)
                    second->first->parent = second;
                first->third = nullptr;
            }
        }
        else if (second == leaf)
        {
            if (third->values.size()== 2)
            {
                if (leaf->first == nullptr)
                {
                    leaf->first = leaf->second;
                    leaf->second = nullptr;
                }
                second->insert_to_node(parent->values[1]);
                parent->values[1] = third->values[0];
                third->remove_from_node(third->values[0]);
                second->second = third->first;
                if (second->second != nullptr)
                    second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
            else if (first->values.size() == 2)
            {
                if (leaf->second == nullptr)
                {
                    leaf->second = leaf->first;
                    leaf->first = nullptr;
                }
                second->insert_to_node(parent->values[0]);
                parent->values[0] = first->values[1];
                first->remove_from_node(first->values[1]);
                second->first = first->third;
                if (second->first != nullptr)
                    second->first->parent = second;
                first->third = nullptr;
            }
        }
        else if (first == leaf)
        {
            if (leaf->first == nullptr)
            {
                leaf->first = leaf->second;
                leaf->second = nullptr;
            }
            first->insert_to_node(parent->values[0]);
            if (second->values.size() == 2)
            {
                parent->values[0] = second->values[0];
                second->remove_from_node(second->values[0]);
                first->second = second->first;
                if (first->second != nullptr)
                    first->second->parent = first;
                second->first = second->second;
                second->second = second->third;
                second->third = nullptr;
            }
            else if (third->values.size() == 2)
            {
                parent->values[0] = second->values[0];
                second->values[0] = parent->values[1];
                parent->values[1] = third->values[0];
                third->remove_from_node(third->values[0]);
                first->second = second->first;
                if (first->second != nullptr)
                    first->second->parent = first;
                second->first = second->second;
                second->second = third->first;
                if (second->second != nullptr)
                    second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
        }
    }
    else if (parent->values.size() == 1)
    {
        leaf->insert_to_node(parent->values[0]);

        if (first == leaf && second->values.size() == 2)
        {
            parent->values[0] = second->values[0];
            second->remove_from_node(second->values[0]);

            if (leaf->first == nullptr)
                leaf->first = leaf->second;

            leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = nullptr;
            if (leaf->second != nullptr)
                leaf->second->parent = leaf;
        }
        else if (second == leaf && first->values.size() == 2)
        {
            parent->values[0] = first->values[1];
            first->remove_from_node(first->values[1]);

            if (leaf->second == nullptr)
                leaf->second = leaf->first;

            leaf->first = first->third;
            first->third = nullptr;
            if (leaf->first != nullptr)
                leaf->first->parent = leaf;
        }
    }
    return parent;
}

TTnode *merge(TTnode *leaf)
{
    TTnode *parent = leaf->parent;

    if (parent->first == leaf)
    {
        parent->second->insert_to_node(parent->values[0]);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;

        if (leaf->first != nullptr)
            parent->second->first = leaf->first;
        else if (leaf->second != nullptr)
            parent->second->first = leaf->second;

        if (parent->second->first != nullptr)
            parent->second->first->parent = parent->second;

        parent->remove_from_node(parent->values[0]);
        delete parent->first;
        parent->first = nullptr;
    }
    else if (parent->second == leaf)
    {
        parent->first->insert_to_node(parent->values[0]);

        if (leaf->first != nullptr)
            parent->first->third = leaf->first;
        else if (leaf->second != nullptr)
            parent->first->third = leaf->second;

        if (parent->first->third != nullptr)
            parent->first->third->parent = parent->first;

        parent->remove_from_node(parent->values[0]);
        delete parent->second;
        parent->second = nullptr;
    }

    if (parent->parent == nullptr)
    {
        TTnode *tmp = nullptr;
        if (parent->first != nullptr)
            tmp = parent->first;
        else
            tmp = parent->second;
        tmp->parent = nullptr;
        delete parent;
        return tmp;
    }
    return parent;
}

TTnode *fix(TTnode *leaf)
{
    if (leaf->values.size() == 0 && leaf->parent == nullptr)
    {
        delete leaf;
        return nullptr;
    }
    if (leaf->values.size() != 0)
    {
        if (leaf->parent)
            return fix(leaf->parent);
        else
            return leaf;
    }

    TTnode *parent = leaf->parent;
    if (parent->first->values.size() == 2 || parent->second->values.size() == 2 || parent->values.size() == 2)
        leaf = redistribute(leaf);
    else if (parent->values.size() == 2 && parent->third->values.size() == 2)
        leaf = redistribute(leaf);
    else
        leaf = merge(leaf);

    return fix(leaf);
}

void remove(TTnode** node, double value)
{
    TTnode* tmp = search(*node, value);

    if (!tmp)
        return;

    TTnode *min = nullptr;
    if (tmp->values[0] == value)
        min = search_min(tmp->second);
    else
        min = search_min(tmp->third);

    if (min)
    {
        double &z = (value == tmp->values[0] ? tmp->values[0] : tmp->values[1]);
        std::swap(z, min->values[0]);
        tmp = min;
    }

    tmp->remove_from_node(value);
    *node = fix(tmp);
}

void find(TTnode* root, double min, double max, std::vector<double>& answer)
{
    if(!root)
        return;
    if(root->values[0]>=min && root->values[0]<=max)
        answer.push_back(root->values[0]);
    find(root->first, min, max, answer);
    if(root->values[0]>max)
        return;
    if(root->values.size() == 2)
    {
        if(root->values[1]>=min && root->values[1]<=max)
            answer.push_back(root->values[1]);
        find(root->second, min, max, answer);
        if(root->values[1]>max)
            return;
        else
            find(root->third, min, max, answer);
    }
    else
    {
        find(root->second, min, max, answer);
    }
}

void print(TTnode* root)
{
    if(root == nullptr)
        return;
    print(root->first);
    cout << root->values[0] << " ";
    print(root->second);
    if(root->values.size()==2)
        cout << root->values[1] << " ";
    print(root->third);
}
