#include <stack>
#include <map>
#include <string>
#include <numeric>
#include <cmath>
#include <set>

struct expr_node
{
    std::string name = "";
    double value = 0;
    expr_node* left = nullptr;
    expr_node* right = nullptr;
};

expr_node* expr_to_tree(const std::string& expression, int& index,
                        std::map<std::string, std::vector<expr_node*> >& variables);

class expr_tree
{
public:
    expr_node* root = nullptr;
    std::map<std::string, std::vector<expr_node*> > variables;
    expr_tree(const std::string& expression)
    {
        int index = expression.size()-1;
        root = expr_to_tree(expression, index, variables);
    }
    expr_tree(){}
    void var_to_val();
    double calculate(expr_node*);
    bool simplify(expr_node*&);
    void print();
};

std::string opn(const std::string& expression)
{
    using namespace std;
    string answer;
    stack<char> operations;
    int count_operations = 0;
    map<char, int> priority = {{'(', 4}, {')',4}, {'^', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1}};
    for(string::size_type i=0; i<expression.size(); i++)
    {
        if(expression[i]==' ') continue;
        else if(isalpha(expression[i]))
        {
            count_operations = 0;
            while(isalpha(expression[i])&&i<expression.size())
            {
                answer+=expression[i];
                i++;
            }
            i--;
            answer+=' ';
        }
        else if(isalnum(expression[i]))
        {
            count_operations = 0;
            int dot_count = 0;
            while((isalnum(expression[i]) || expression[i]=='.') && i<expression.size())
            {
                if(expression[i]=='.') dot_count++;
                answer+=expression[i];
                i++;
            }
            if(dot_count>1) throw runtime_error("Wrong expression!\n");
            i--;
            answer+=' ';
        }
        else if(priority.count(expression[i])!=0)
        {
            if(count_operations>=1 && expression[i]!='('
               && expression[i]!=')') throw runtime_error("Wrong expression!\n");
            else if(expression[i]!='(' && expression[i]!=')') count_operations++;
            if(!operations.empty())
            {
                if(expression[i]=='(')
                {
                    operations.push(expression[i]);
                }
                else if(expression[i]==')')
                {
                    while(!operations.empty()&&operations.top()!='(')
                    {
                        answer+=operations.top();
                        answer+=' ';
                        operations.pop();
                    }
                    if(operations.empty())
                    {
                        throw runtime_error("Incorrect brackets!\n");
                    }
                    else operations.pop();
                }
                else
                {
                    while(!operations.empty()&&priority[expression[i]]<=priority[operations.top()]&&operations.top()!='(')
                    {
                        answer+=operations.top();
                        answer+=' ';
                        operations.pop();
                    }
                    operations.push(expression[i]);
                }
            }
            else operations.push(expression[i]);
        }
        else throw runtime_error("Wrong expression1!\n");
    }
    while(!operations.empty())
    {
        if(operations.top()=='(') throw runtime_error("Incorrect brackets!\n");
        answer+=operations.top();
        answer+=' ';
        operations.pop();
    }
    return answer;
}

int char_to_int(char c)
{
    return c - '0';
}

double string_to_double(const std::string& number)
{
    double answer = 0;
    int index = number.size()-1;

    while(isalnum(number[index]) && index>=0) index--;

    double k = 1;

    if(number[index]=='.')
    {
        index--;
        while(index<number.size())
        {
            index--;
            k/=10;
        }
    }

    for(index = 0; index<number.size(); index++)
    {
        if(number[index]=='.') continue;
        answer += char_to_int(number[index])*k;
        k*=10;
    }
    return answer;
}

expr_node* expr_to_tree(const std::string& expression, int& index,
                        std::map<std::string, std::vector<expr_node*> >& variables)
{
    using namespace std;
    if(expression[index]==' ') index--;
    if(index<0) return nullptr;
    string name;
    expr_node* new_node = new expr_node;
    if(isalpha(expression[index]))
    {
        while(isalpha(expression[index])&&index>=0)
        {
            name+=expression[index];
            index--;
        }
        new_node->name = name;
        variables[name].push_back(new_node);
    }
    else if(isalnum(expression[index]))
    {
        while((isalnum(expression[index]) || expression[index]=='.') && index>=0)
        {
            name+=expression[index];
            index--;
        }
        new_node->value = string_to_double(name);
    }
    else
    {
        new_node->name = expression[index];
        index--;
        new_node->right = expr_to_tree(expression, index, variables);
        new_node->left = expr_to_tree(expression, index, variables);
    }
    return new_node;
}

void print_tree(expr_node* node)
{
    if(node==nullptr) return;
    if(node->name=="") std::cout << node->value;
    else std::cout << node->name;
    if(node->left!=nullptr || node->right!=nullptr) std::cout << "(";
    print_tree(node->left);
    if(node->right!=nullptr && node->left!=nullptr) std::cout << ",";
    print_tree(node->right);
    if(node->left!=nullptr || node->right!=nullptr) std::cout << ")";
}

void expr_tree::var_to_val()
{
    std::cout << std::endl;
    for(auto& var:variables)
    {
        std::cout << var.first << " = ";
        double value;
        std::cin >> value;
        for(auto& i:var.second)
        {
            i->value = value;
        }
    }
}

double expr_tree::calculate(expr_node* node)
{
    if(node->left==nullptr && node->right==nullptr) return node->value;
    if(node->left==nullptr)
    {
        if(node->name == "-") return -calculate(node->right);
        else throw std::runtime_error("Wrong expression!\n");
    }
    if(node->right==nullptr)
    {
        if(node->name == "-") return -calculate(node->left);
        else throw std::runtime_error("Wrong expression!\n");
    }
    if(node->name == "+")
        return calculate(node->left)+calculate(node->right);
    else if(node->name == "-")
        return calculate(node->left)-calculate(node->right);
    else if(node->name == "*")
        return calculate(node->left)*calculate(node->right);
    else if(node->name == "^")
        return pow(calculate(node->left),calculate(node->right));
    else if(node->name == "/")
    {
        double left = calculate(node->left);
        double right = calculate(node->right);
        if(right == 0) throw std::runtime_error("Division by zero\n");
        else return left/right;
    }
    else throw std::runtime_error("Wrong expression!\n");
}

void remove(expr_node* &node)
{
    if(node==nullptr) return;
    if(node->left==nullptr && node->right==nullptr)
    {
        delete node;
        node = nullptr;
        return;
    }
    if(node->left!=nullptr) remove(node->left);
    if(node->right!=nullptr) remove(node->right);
    delete node;
    node = nullptr;
}

bool expr_tree::simplify(expr_node* &node)
{
    if(node==nullptr) return true;
    if(node->name=="") return true;

    std::set<char> operations = {'-', '^', '+', '/', '*'};

    if(operations.count(node->name[0]) == 0)
    {
        simplify(node->left);
        simplify(node->right);
        return false;
    }
    bool q1 = simplify(node->left);
    bool q2 = simplify(node->right);
    if(q1 && q2)
    {
        node->value = calculate(node);
        node->name = "";
        remove(node->left);
        remove(node->right);
    }
    else return false;
}

void print_expression(expr_node* node)
{
    if(node==nullptr) return;

    std::map<char, int> priority = {{'^', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1}};

    if(node->left!=nullptr && priority.count(node->left->name[0])>0
       && priority[node->name[0]]>priority[node->left->name[0]])
    {
        std::cout << "(";
        print_expression(node->left);
        std::cout << ")";
    }
    else print_expression(node->left);

    if(node->name!="") std::cout << node->name;
    else std::cout << node->value;

    if(node->right!=nullptr && priority.count(node->right->name[0])>0
       && priority[node->name[0]]>priority[node->right->name[0]])
    {
        std::cout << "(";
        print_expression(node->right);
        std::cout << ")";
    }
    else print_expression(node->right);
}

void expr_tree::print()
{
    print_expression(root);
}
