#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "element.h"
#include <vector>

struct NodeList
{
    double value;
    NodeList* next;
    NodeList* previous;
    NodeList(double val, NodeList* nex = nullptr, NodeList* prev = nullptr)
    {
        value = val;
        next = nex;
        previous = prev;
    }
    NodeList()
    {
        next = nullptr;
        previous = nullptr;
    }
};

int calculate_memory(NodeList* root)
{
    int answer = 0;
    while(root)
    {
        answer+=sizeof(*root);
        root = root->next;
    }
    return answer;
}

void do_something(NodeList* root, double (*f)(double))
{
    if(root==nullptr) return;
    while(root)
    {
        root->value = f(root->value);
        root = root->next;
    }
}

void add(NodeList** root, double value)
{
    if(*root == nullptr)
    {
        *root = new NodeList(value);
        return;
    }
    if((*root)->value > value)
    {
        NodeList* tmp = *root;
        *root = new NodeList(value);
        (*root)->next = tmp;
        tmp->previous = *root;
        return;
    }
    NodeList** node = root;
    while((*node)->next)
    {
        if((*node)->value > value)
        {
            NodeList* tmp = *node;
            *node = new NodeList(value);
            (*node)->next = tmp;
            tmp->previous = *node;
            return;
        }
        node = &((*node)->next);
    }
    if((*node)->value <= value) (*node)->next = new NodeList(value, nullptr, *node);
    else
    {
        NodeList* tmp = *node;
        *node = new NodeList(value);
        (*node)->next = tmp;
        tmp->previous = *node;
        return;
    }
}

void remove(NodeList** root, double value)
{
    if(*root == nullptr) return;
    if(value>(*root)->value) remove((&(*root)->next), value);
    else if(value<(*root)->value) return;
    else
    {
        if((*root)->next == nullptr)
        {
            delete *root;
            *root = nullptr;
        }
        else
        {
            NodeList* tmp = (*root)->next;
            (*root)->next = tmp->next;
            (*root)->value = tmp->value;
            delete tmp;
        }
    }
}

void print(NodeList* root)
{
    while(root)
    {
        std::cout << root->value << " ";
        root = root->next;
    }
}

void find(NodeList* root, double first, double second, std::vector<double>& answer)
{
    while(root)
    {
        if(root->value>=first && root->value<=second)
        {
            answer.push_back(root->value);
        }
        root = root->next;
    }
    return;
}

#endif // LIST_H_INCLUDED
