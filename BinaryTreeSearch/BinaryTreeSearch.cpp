﻿// BinaryTreeSearch.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
int tabs = 0; //Для создания отступов
//Кол-во отступов высчитывается по кол-ву рекурсивного вхождения при выводе в фукцию print_tree
class Node {
public:
    int m_data;     //ключ - число, хранящееся в вершине
    Node* m_left;    //указатель на левого потомка данной вершины
    Node* m_right;  //указатель на правого потомка данной вершины
    // Конструктор класса
    //Левые и правые поддеревья инициализирует нулевыми указателями
    Node(int val)
    {
        m_left = nullptr;
        m_right = nullptr;
        m_data = val;
    }
};
class Search_tree
{
private:
    int key;

    Node* m_root;        //указатель на корень дерева
    int m_size;                       //количество элементов в дереве
    void print_tree(Node*);   //используется в рекурсивном алгоритме обхода дерева
    void delete_tree(Node*); //используется в рекурсивном алгоритме удаления в дереве
public:
    Node* createIdealTree(const int treeSize, int& nodeKey);
    Search_tree(int);      //конструктор
    ~Search_tree();         //деструктор    
    void print();             //вывод всех элементов поддерева
    bool find(int);          //поиск элемента в дереве
    void insert(int);         //добавление нового элемента (узла) 
    void erase(int);         //удаление узла с указанным ключом 
    int size();                  // возврат количества элементов в дереве 
    int FindMax(Node* m_root);//найти максимальный ключ дерева
    int FindMin(Node* m_root); //найти минимальный ключ дерева
    Search_tree& operator=(Search_tree x); //оператор присваивания
    void inorder(Node* root);
};
Node* Search_tree::createIdealTree(const int treeSize, int& nodeKey)
{
    if (treeSize <= 0)
    {
        return nullptr; //Точка остановки рекурсии
    }
    int leftSubtreeSize = (treeSize - 1) / 2;
    int rightSubtreeSize = treeSize - 1 - leftSubtreeSize;
   
    createIdealTree(leftSubtreeSize, nodeKey);
    createIdealTree(rightSubtreeSize, nodeKey);
}
void Search_tree::print_tree(Node* curr)
{
    if (!curr) return;
    tabs++;

    print_tree(curr->m_left);

    for (int i = 0; i < tabs; i++) cout << "  ";
    cout << curr->m_data << endl;
    print_tree(curr->m_right);

    tabs--;
    return;
    
}

void Search_tree::delete_tree(Node* curr)
{
    if (curr)
    {
        delete_tree(curr->m_left);
        delete_tree(curr->m_right);
        delete curr;
    }
}



Search_tree::Search_tree(int key)
{
    m_root = new Node(key);
    m_size = 1;
}

Search_tree::~Search_tree()
{
    delete_tree(m_root);
}

void Search_tree::print()
{
    print_tree(m_root);
    cout << endl;
}

bool Search_tree::find(int key)
{
    Node* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
    return curr != NULL;
}
// Отсортированный (inorder) обход
void Search_tree::inorder(Node* root)
{
    if (root != NULL) {
        // Обходим лево
        inorder(root->m_left);

        // Обходим корень
        cout << root->m_data << " -> ";

        // Обходим право
        inorder(root->m_right);
    }
}

void Search_tree::insert(int key)
{
    Node* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key && curr->m_left == NULL)
        {
            curr->m_left = new Node(key);
            ++m_size;
            return;
        }
        if (curr->m_data < key && curr->m_right == NULL)
        {
            curr->m_right = new Node(key);
            ++m_size;
            return;
        }
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
}

void Search_tree::erase(int key)
{
    Node* curr = m_root;
    Node* parent = NULL;
    while (curr && curr->m_data != key)
    {
        parent = curr;
        if (curr->m_data > key)
        {
            curr = curr->m_left;
        }
        else
        {
            curr = curr->m_right;
        }
    }
    if (!curr)
        return;
    if (curr->m_left == NULL)
    {
        // Вместо curr подвешивается его правое поддерево
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_right;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_right;
        --m_size;
        delete curr;
        return;
    }
    if (curr->m_right == NULL)
    {
        // Вместо curr подвешивается его левое поддерево
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_left;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_left;
        --m_size;
        delete curr;
        return;
    }
    // У элемента есть два потомка, тогда на место элемента поставим
    // наименьший элемент из его правого поддерева
    Node* replace = curr->m_right;
    while (replace->m_left)
        replace = replace->m_left;
    int replace_value = replace->m_data;
    erase(replace_value);
    curr->m_data = replace_value;
}

int Search_tree::size()
{
    return m_size;
}
int Search_tree::FindMax(Node* m_root)
{
    if (m_root == NULL)
        return -1;
    else if (m_root->m_right == NULL)
        return m_root->m_data;
    else
        return FindMax(m_root->m_right);
}
int Search_tree::FindMin(Node* m_root)
{
    if (m_root == NULL)
        return -1;
    else if (m_root->m_left == NULL)
        return m_root->m_data;
    else
        return FindMin(m_root->m_left);

}
Search_tree& Search_tree::operator=(Search_tree x)
{
    if (this != &x) {
        swap(m_root, x.m_root);
        return *this;
    }
}



int main(int& nodeKey) 
{
    setlocale(LC_ALL, "Ru");
    Node* root = nullptr;    // Объявляем структуру дерева
    int a, n; 
    Search_tree tree(1);
    cout << "Введите кол-во узлов = ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Введите узел " << i + 1 << ": ";
        cin >> a;
        tree.createIdealTree(n,nodeKey);
        tree.inorder(root);
        tree.insert(a);
    }

    Node* print(root);    
    tree.print();
    Search_tree print_tree(); 
    Search_tree FindMax();
    Search_tree FindMin();
    cin.get();  cin.get();
    return 0;

}
