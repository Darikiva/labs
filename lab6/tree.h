#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

struct TreeNode
{
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val, TreeNode* lef = nullptr, TreeNode* rig = nullptr)
    {
        value = val;
        left = lef;
        right = rig;
    }
    TreeNode()
    {
        left = nullptr;
        right = nullptr;
    }
};

int calculate_memory(TreeNode* root)
{
    if(root==nullptr) return 0;
    int answer = sizeof(*root);
    answer+=calculate_memory(root->left);
    answer+=calculate_memory(root->right);
    return answer;
}

TreeNode* add(TreeNode** root, int value)
{
    if(*root == nullptr)
    {
        *root = new TreeNode(value);
        return *root;
    }
    if((*root)->value < value)
    {
        (*root)->right = add(&((*root)->right), value);
    }
    else
    {
        (*root)->left = add(&((*root)->left), value);
    }
    return *root;
}

void find(TreeNode* root, int min, int max, std::vector<int>& answer)
{
    if(root == nullptr) return;
    if(root->value>=min) find(root->left, min, max, answer);
    if(root->value>=min && root->value<=max) answer.push_back(root->value);
    if(root->value<=max) find(root->right, min, max, answer);
    return;
}

TreeNode** find_prev(TreeNode* root)
{
    TreeNode** cur = &(root->left);
    while((*cur)->right)
    {
        cur = &((*cur)->right);
    }
    return cur;
}

void remove(TreeNode** root, int val)
{
    if(*root==nullptr)
    {
        return;
    }
    if (val<(*root)->value)
    {
        remove(&((*root)->left),val);
    }
    else if (val>(*root)->value)
    {
        remove(&((*root)->right),val);
    }
    else
    {
        if ((*root)->left)
        {
            if ((*root)->right)   //both children
            {
                TreeNode** prev_node = find_prev(*root);
                (*root)->value = (*prev_node)->value;
                TreeNode* tmp = (*prev_node)->left;
                delete * prev_node;
                *prev_node = tmp;
            }
            else     //only left child
            {
                TreeNode* tmp = (*root)->left;
                delete *root;
                *root = tmp;
            }
        }
        else
        {
            if ((*root)->right)   //only right child
            {
                TreeNode* tmp = (*root)->right;
                delete *root;
                *root = tmp;
            }
            else     //no children
            {
                delete *root;
                *root = nullptr;
            }
        }
    }
}

void print(TreeNode* root)
{
    if(root == nullptr) return;
    print(root->left);
    std::cout << root->value << " ";
    print(root->right);
}

#endif // TREE_H_INCLUDED
