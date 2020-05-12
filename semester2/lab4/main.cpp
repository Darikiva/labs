
// ************************************
///////////////////////////////////////
// BLOCK    TASK
// 0        1
// 1        6
// 2        7
// 3        16
// 4        19
// 5        21
// 6        22
///////////////////////////////////////
// ************************************


#include <iostream>
#include <cstdlib>
#include "tree.h"
#include "binary_tree.h"
#include "expr_tree.h"

const size_t max_node = 1000;

binary_node* build_binary(Node* node)
{
    if(node==nullptr) return nullptr;
    binary_node* new_bin_node = new binary_node(node->value);

    if(node->children.size()!=0)
    {
        new_bin_node->left = build_binary(node->children[0]);
        new_bin_node->left->parent = new_bin_node;
    }
    if(node->parent!=nullptr)
    {
        size_t index = 0;
        while(node->parent->children[index]!=node)
            index++;
        if (index+1<node->parent->children.size())
        {
            new_bin_node->right = build_binary(node->parent->children[index+1]);
            new_bin_node->right->parent = new_bin_node;
        }
    }
    return new_bin_node;
}

void building(binary_node* node, std::vector<node_order*>& answer, size_t& index)
{
    node_order* new_node = new node_order;
    new_node->value = node->value;
    size_t index_for_this_node = index;
    if(node->left!=nullptr)
    {
        index++;
        new_node->left = true;
        building(node->left, answer, index);
    }
    if(node->right!=nullptr)
    {
        index++;
        new_node->right = index;
        building(node->right, answer, index);
    }
    answer[index_for_this_node] = new_node;
}

std::vector <node_order*> build_in_order(binary_node* node)
{
    if(node==nullptr) return {};
    std::vector <node_order*> answer(max_node, nullptr);
    size_t index = 0;
    building(node, answer, index);
    return answer;
}

void interactive_tree();
void work_tree(std::pair<std::pair<std::string, Node*>, std::pair<int, int> >&);

void interactive_expression();
void work_expression(expr_tree*);

void demonstration_tree();
void demonstration_expression();

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    for(;;)
    {
        cout << "1. Tree\n";
        cout << "2. Expressions\n";
        cout << "3. Exit\n";
        cout << "Enter your choice(number): ";
        int choice;
        int mode;
        cin >> choice;
        switch(choice)
        {
        case 1:
            cout << "1. Interactive mode\n";
            cout << "2. Demonstrative mode\n";
            cout << "Enter the number: ";
            cin >> mode;
            switch(mode)
            {
            case 1:
                interactive_tree();
                break;
            case 2:
                demonstration_tree();
                break;
            }
            break;
        case 2:
            cout << "1. Interactive mode\n";
            cout << "2. Demonstrative mode\n";
            cout << "Enter the number: ";
            cin >> mode;
            switch(mode)
            {
            case 1:
                interactive_expression();
                break;
            case 2:
                demonstration_expression();
                break;
            }
            break;
        case 3:
            return 0;
        default:
            cout << "No such option!\n";
        }
    }
    return 0;
}

void interactive_tree()
{
    using namespace std;

    vector<pair<pair<string, Node*>, pair<int, int> > > trees;


    for(;;)
    {
        cout << "1. Make new tree" << endl;
        cout << "2. Choose the tree" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cout << "Enter number of your choice: ";
        cin >> choice;
        switch(choice)
        {
        case 1:
            {
                cout << "Enter the name of new tree: ";
                string name;
                cin >> name;

                cout << "Enter min number of children: ";
                int min;
                cin >> min;

                cout << "Enter max number of children: ";
                int max;
                cin >> max;

                trees.push_back({{name, nullptr}, {min, max}});
            }
            break;
        case 2:
            if (trees.size()==0) cout << "There are no trees!" << endl;
            else
            {
                for(int i=0; i<trees.size(); i++)
                {
                    cout << i << ". " << trees[i].first.first << endl;
                }
                cout << "Enter the number of the tree: ";
                int number;
                cin >> number;
                if(number<0 && number>=trees.size()) cout << "Wrong number!" << endl;
                else work_tree(trees[number]);
            }
            break;
        case 3:
            return;
        default:
            cout << "No such option!" << endl;
        }
    }
}

void work_tree(std::pair<std::pair<std::string, Node*>, std::pair<int, int> >& tree)
{
    using namespace std;

    int min = tree.second.first;
    int max = tree.second.second;
    Node* &root = tree.first.second;

    for(;;)
    {
        cout << "1. Add new element" << endl;
        cout << "2. Remove element" << endl;
        cout << "3. Print tree" << endl;
        cout << "4. Print binary version" << endl;
        cout << "5. Print a consistent presentation based on direct order" << endl;
        cout << "6. Back to main menu" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch(choice)
        {
        case 1:
            {
                cout << "Enter the value: ";
                int value;
                cin >> value;
                Node* new_element = new Node(value);
                add_element(root, new_element, min, max);
            }
            break;
        case 2:
            {
                cout << "Enter the value: ";
                int value;
                cin >> value;
                deleting(root, value);
            }
            break;
        case 3:
            print_tree(root);
            cout << endl;
            break;
        case 4:
            {
                print_tree(build_binary(root));
                cout << endl;
            }
            break;
        case 5:
            {
                binary_node* binary_tree = build_binary(root);
                vector <node_order*> order_tree = build_in_order(binary_tree);
                print_tree(order_tree);
                cout << endl;
            }
            break;
        case 6:
            return;
        default:
            cout << "Try again!" << endl;
        }
    }
}

void interactive_expression()
{
    using namespace std;

    vector<expr_tree*> expressions;

    for(;;)
    {
        cout << "1. Add new expression" << endl;
        cout << "2. Choose expression" << endl;
        cout << "3. Exit" << endl;

        int choice;

        cin >> choice;

        switch(choice)
        {
        case 1:
            {
                cout << "Enter expression, allowed operators: ^, *, /, -, +" << endl;
                string expression;
                cin >> expression;
                try
                {
                    expr_tree* new_tree = new expr_tree(opn(expression));
                    expressions.push_back(new_tree);
                }
                catch(runtime_error& ex)
                {
                    cout << ex.what();
                }
            }
            break;
        case 2:
            {
                if(expressions.size()==0) cout << "No expressions!" << endl;
                else
                {
                    for(size_t i=0; i<expressions.size(); i++)
                    {
                        cout << i << ". ";
                        expressions[i]->print();
                        cout << endl;
                    }
                    cout << "Enter the number of the expression: ";
                    int number;
                    cin >> number;
                    if(number<0 || number>=expressions.size()) cout << "Wrong!" << endl;
                    else work_expression(expressions[number]);
                }
            }
            break;
        case 3:
            return;
        default:
            cout << "No such option!" << endl;
        }
    }
}

void work_expression(expr_tree* expression)
{
    using namespace std;

    for(;;)
    {
        cout << "1. Calculate" << endl;
        cout << "2. Simplify" << endl;
        cout << "3. Print" << endl;
        cout << "4. Print expression tree" << endl;
        cout << "5. Back to the main menu" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
            expression->var_to_val();
            cout << expression->calculate(expression->root);
            cout << endl;
            break;
        case 2:
            expression->simplify(expression->root);
            break;
        case 3:
            expression->print();
            cout << endl;
            break;
        case 4:
            print_tree(expression->root);
            cout << endl;
            break;
        case 5:
            return;
        default:
            cout << "Try again!" << endl;
        }
    }
}

void demonstration_tree()
{
    using namespace std;

    cout << "Create new tree. Min = 3, max = 6\n";

    int min = 3;
    int max = 6;
    Node* root = nullptr;

    cout << "Add 15 new elements: \n";

    for(int i=0; i<15; i++)
    {
        Node* new_node = new Node(i);
        add_element(root, new_node, min, max);
    }
    print_tree(root);
    cout << endl;

    cout << "Build binary tree: ";

    binary_node* bin_node = build_binary(root);
    print_tree(bin_node);
    cout << endl;

    cout << "Build a consistent presentation based on direct order: ";

    vector<node_order*> ord_node = build_in_order(bin_node);
    print_tree(ord_node);
    cout << endl;

    cout << "Remove elements with value 3, 5, 19 (no node with this value), 0, 3" << endl;

    deleting(root, 3);
    print_tree(root);
    cout << endl;

    deleting(root, 5);
    print_tree(root);
    cout << endl;

    deleting(root, 19);
    print_tree(root);
    cout << endl;

    deleting(root, 0);
    print_tree(root);
    cout << endl;

    deleting(root, 3);
    print_tree(root);
    cout << endl;
}

void demonstration_expression()
{
    using namespace std;

    string expression = "3*98-11^2+(x^(5-y)+18*x+(13*y-12/x))*(x+y)";

    cout << "Create new expression tree with expression 3*98-11^2+(x^(5-y)+18*x+(13*y-12/x))*(x+y)";
    expr_tree tree(opn(expression));
    cout << endl;

    cout << "Calculate with x = 3, y = 4, z = 2.5: ";

    for(auto &i: tree.variables["x"])
        i->value = 3;
    for(auto &i: tree.variables["y"])
        i->value = 4;
    for(auto &i: tree.variables["z"])
        i->value = 2.5;

    cout << tree.calculate(tree.root);
    cout << endl;

    cout << "Simplify expression: ";
    tree.simplify(tree.root);
    tree.print();
    cout << endl;

    cout << "Calculate with x = 0 (should be mistake): ";

    for(auto &i: tree.variables["x"])
        i->value = 0;
    for(auto &i: tree.variables["y"])
        i->value = 4;
    for(auto &i: tree.variables["z"])
        i->value = 2.5;

    try
    {
        tree.calculate(tree.root);
    }
    catch (runtime_error &ex)
    {
        cout << ex.what();
    }

    cout << endl;
    cout << "Print tree: ";

    print_tree(tree.root);
    cout << endl;
}
