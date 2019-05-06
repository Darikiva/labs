#include <vector>

struct Node
{
    int value;
    int child_number = 0;
    std::vector<Node*> children = {};
    Node* parent = nullptr;
    Node(){}
    Node(int value_)
    {
        value = value_;

    }
};

void add_element(Node* &node, Node* new_element, unsigned min = 2, unsigned max = 10)
{
    if(node == nullptr)
    {
        node = new_element;
        return;
    }
    if(node->children.size()<min || node->children.size()==0)
    {
        if(node->children.size()==0) node->child_number++;
        node->children.push_back(new_element);
        new_element->parent = node;
        return;
    }
    Node* min_child = node->children[0];
    for(size_t i=1; i<node->children.size(); i++)
    {
        if(node->children[i]->children.size() < min_child->children.size())
        {
            min_child = node->children[i];
        }
    }
    if(min_child->children.size()<=max)
    {
        add_element(min_child, new_element, min, max);
    }
    else
    {
        if(node->children.size()<=max)
        {
            node->children.push_back(new_element);
            new_element->parent = node;
        }
        else
        {
            Node* min_depth = node->children[0];
            for(size_t i=1; i<node->children.size(); i++)
            {
                if(node->children[i]->child_number < min_depth->child_number)
                {
                    min_depth = node->children[i];
                }
            }
            add_element(min_depth, new_element, min, max);
        }
    }
}

void print_tree(Node* node)
{
    if(node==nullptr) return;
    std::cout << node->value;
    if(node->children.size()!=0) std::cout << "(";
    for(size_t i=0; i<node->children.size(); i++)
    {
        print_tree(node->children[i]);
        if(i!=node->children.size()-1) std::cout << ",";
    }
    if(node->children.size()!=0) std::cout << ")";
}

void add_from_deleted_tree(Node* node, int deleted_element, std::vector<int>& deleted_values)
{
    if(node->value!=deleted_element) deleted_values.push_back(node->value);
    for(size_t i=0; i<node->children.size(); i++)
    {
        add_from_deleted_tree(node->children[i], deleted_element, deleted_values);
    }
    delete node;
}

bool delete_element(Node* node, int deleted_element, std::vector <int>& deleted_values)
{
    bool answer = false;
    if(node->value == deleted_element)
    {
        if(node->parent == nullptr) answer = true;
        else
        {
            for(size_t i=0; i<node->parent->children.size(); i++)
            {
                if(node->parent->children[i]==node)
                {
                    node->parent->children.erase(node->parent->children.begin()+i);
                    break;
                }
            }
        }
        add_from_deleted_tree(node, deleted_element, deleted_values);
        return answer;
    }
    for(size_t i=0; i<node->children.size(); i++)
    {
        delete_element(node->children[i], deleted_element, deleted_values);
    }
    return answer;
}

void deleting(Node* &root, int deleted_element)
{
    if(root==nullptr) return;
    std::vector<int> deleted_values;
    if(delete_element(root, deleted_element, deleted_values))
    {
        if(deleted_values.size()==0){
            root = nullptr;
        }
        else root = new Node(deleted_values[0]);
        for(size_t i=1; i<deleted_values.size(); i++)
        {
            Node* new_element = new Node(deleted_values[i]);
            add_element(root, new_element);
        }
    }
    else
    {
        for(size_t i=0; i<deleted_values.size(); i++)
        {
            Node* new_element = new Node(deleted_values[i]);
            add_element(root, new_element);
        }
    }
}

void delete_tree(Node* &root)
{
    if(root == nullptr) return;
    for(int i=0; i<root->children.size(); i++)
    {
        delete_tree(root->children[i]);
    }
    delete root;
    root = nullptr;
}
