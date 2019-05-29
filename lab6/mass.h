#include <vector>

struct ArrNode
{
    std::vector<int> arr;
    ArrNode(int value)
    {
        arr.push_back(value);
    }
};

int calculate_memory(ArrNode* root)
{
    if(root == nullptr) return 0;
    int answer;
    answer = sizeof(*root);
    answer+=root->arr.size() * sizeof(int);
    return answer;
}

void add(ArrNode** root, int value)
{
    if(!*root) *root = new ArrNode(value);
    for(int i=0; i<(*root)->arr.size(); i++)
    {
        if((*root)->arr[i]>value)
        {
            int size = (*root)->arr.size();
            (*root)->arr.push_back(0);
            for(int j=size; j>i; j--)
                (*root)->arr[j] = (*root)->arr[j-1];
            (*root)->arr[i] = value;
            return;
        }
    }
    (*root)->arr.push_back(value);
}

void remove(ArrNode** root, int value)
{
    for(int i=0; i<(*root)->arr.size(); i++)
    {
        if((*root)->arr[i] == value)
        {
            (*root)->arr.erase((*root)->arr.begin()+i);
            return;
        }
    }
}

void find(ArrNode* root, int min, int max, std::vector<int>& answer)
{
    for(int i=0; i<root->arr.size(); i++)
    {
        if(root->arr[i]>max) return;
        if(root->arr[i]>=min && root->arr[i]<=max) answer.push_back(root->arr[i]);
    }
}

void print(ArrNode* root)
{
    for(const auto& i:root->arr) std::cout << i << " ";
}
