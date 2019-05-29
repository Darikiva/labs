#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

struct AVLnode
{
    int value;
    unsigned height;
    AVLnode* left;
    AVLnode* right;
    AVLnode(int val, AVLnode* lef = nullptr, AVLnode* rig = nullptr)
    {
        value = val;
        left = lef;
        right = rig;
        height = 0;
    }
    AVLnode()
    {
        height = 0;
        left = nullptr;
        right = nullptr;
    }
};

int calculate_memory(AVLnode* root)
{
    if(root==nullptr) return 0;
    int answer;
    answer = sizeof(*root);
    answer+=calculate_memory(root->left);
    answer+=calculate_memory(root->right);
    return answer;
}

unsigned height(AVLnode* root)
{
    return root?root->height:0;
}

int difference(AVLnode* root)
{
    return height(root->right) - height(root->left);
}


void print(AVLnode* root)
{
    if(root == nullptr) return;
    print(root->left);
    std::cout << root->value << " ";
    print(root->right);
}

void fix_height(AVLnode* root)
{
    unsigned hl = height(root->left);
    unsigned hr = height(root->right);
    root->height = (hl>hr?hl:hr) + 1;
}

AVLnode* rotate_right(AVLnode** root)
{
    AVLnode* tmp = (*root)->left;
    (*root)->left = tmp->right;
    tmp->right = *root;
    fix_height(*root);
    fix_height(tmp);
    *root = tmp;
    return tmp;
}

AVLnode* rotate_left(AVLnode** root)
{
    AVLnode* tmp = (*root)->right;
    (*root)->right = tmp->left;
    tmp->left = *root;
    fix_height(*root);
    fix_height(tmp);
    *root = tmp;
    return tmp;
}

AVLnode* balance(AVLnode** root)
{
    fix_height(*root);
    if(difference(*root)==2)
    {
        if(difference((*root)->right)<0)
            (*root)->right = rotate_right(&(*root)->right);
        return rotate_left(root);
    }
    if(difference(*root) == -2)
    {
        if(difference((*root)->left)>0)
            (*root)->left = rotate_left(&(*root)->left);
        return rotate_right(root);
    }
    return *root;
}

AVLnode* add(AVLnode** root, int value)
{
    if(!*root)
    {
        *root = new AVLnode(value);
        return *root;
    }
    if(value < (*root)->value)
    {
        (*root)->left = add(&(*root)->left, value);
    }
    else
    {
        (*root)->right = add(&(*root)->right, value);
    }
    return balance(root);
}

AVLnode* findmin(AVLnode* p)
{
	return p->left?findmin(p->left):p;
}

AVLnode* removemin(AVLnode* p)
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(&p);
}

AVLnode* remove(AVLnode** node, int k)
{
	if(!*node ) return 0;
	if( k < (*node)->value )
		(*node)->left = remove(&(*node)->left,k);
	else if( k > (*node)->value )
		(*node)->right = remove(&(*node)->right,k);
    else
	{
		AVLnode* q = (*node)->left;
		AVLnode* r = (*node)->right;
		delete *node;
		if( !r ) return q;
		AVLnode* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(&min);
	}
	return balance(node);
}

void find(AVLnode* root, int min, int max, std::vector<int>& answer)
{
    if(!root) return;
    if(root->value>=min) find(root->left, min, max, answer);
    if(root->value>=min && root->value<=max) answer.push_back(root->value);
    if(root->value<=max) find(root->right, min, max, answer);
}

void print_tree(AVLnode* root)
{
    if(root==nullptr) return;
    std::cout << root->value;
    if(root->left!=nullptr || root->right!=nullptr) std::cout << "(";
    print_tree(root->left);
    if(root->right!=nullptr && root->left!=nullptr) std::cout << ",";
    print_tree(root->right);
    if(root->left!=nullptr || root->right!=nullptr) std::cout << ")";
}

#endif // AVL_H_INCLUDED
