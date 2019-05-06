struct binary_node
{
    int value;
    binary_node* left = nullptr;
    binary_node* right = nullptr;
    binary_node* parent = nullptr;
    binary_node(){}
    binary_node(int value_)
    {
        value = value_;
    }
};

struct node_order
{
    int value;
    size_t right = 0;
    bool left = false;
    node_order(){}
    node_order(size_t right_, bool left_ = false)
    {
        right = right_;
        left = left_;
    }
};

void print_tree(binary_node* node)
{
    if(node==nullptr) return;
    std::cout << node->value;
    if(node->left!=nullptr || node->right!=nullptr) std::cout << "(";
    print_tree(node->left);
    if(node->right!=nullptr && node->left!=nullptr) std::cout << ",";
    print_tree(node->right);
    if(node->left!=nullptr || node->right!=nullptr) std::cout << ")";
}

void print_tree(std::vector<node_order*> node_list)
{
    for(size_t i=0; i<node_list.size() && node_list[i]!=nullptr; i++)
        std::cout << node_list[i]->value << " ";
}
