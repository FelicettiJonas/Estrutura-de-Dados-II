#include <stdio.h>
#include <stdlib.h>

/// @brief Estrutura do Node contendo um ponteiro pra esquerda, um pra direita e o valor contido no nodo
typedef struct sNode
{

    int data;

    struct sNode *left, *right;

} Node;

void preOrder (Node *);
void inOrder (Node *);
void postOrder (Node *);
void freeTree (Node *);
Node *newNode(int);
Node *insert(Node *, int);
Node *removeRoot(Node *);
Node *removeNode(Node *, int );

int main()
{

    Node *root = NULL;

    root = insert(root, 5);

    insert(root, 12);
    insert(root, 2);
    insert(root, 7);
    insert(root, 3);
    insert(root, 1);
    insert(root, 10);
    insert(root, 8);
    insert(root, 9);
    insert(root, 4);
    insert(root, 6);
    insert(root, 11);

    preOrder(root);

    root = removeNode(root, 10);

    printf("\n");
    preOrder(root);
    freeTree(root);

    return 0;
}

/// @brief Algoritimo de pré ordem para mostrar a construção da arvore.
/// @param node Raiz da arvore
void preOrder (Node *node)
{
    if (node != NULL)
    {
        printf("%i ", node->data);
        preOrder(node->left);
        preOrder(node->right);
    }
}

/// @brief Algoritimo de ordem para mostrar a construção da arvore.
/// @param node Raiz da arvore
void inOrder (Node *node)
{
    if (node != NULL)
    {
        inOrder(node->left);
        printf("%i ", node->data);
        inOrder(node->right);
    }
}

/// @brief Algoritimo de pós-ordem para mostrar a construção da arvore.
/// @param node Raiz da arvore
void postOrder (Node *node)
{
    if (node != NULL)
    {
        postOrder(node->left);
        postOrder(node->right);
        printf("%i ", node->data);
    }
}

/// @brief Algoritimo recursivo para desalocar a memória de todos os nodos da arvore.
/// @param node Raiz da arvore
void freeTree (Node *node)
{
    if (node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

/// @brief Realiza o processo de alocação de memória para o novo nodo.
/// @param data Valor contido no Node
/// @return Ponteiro para o espaço alocado.
Node *newNode(int data)
{

    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;

    temp->left = temp->right = NULL;
    return temp;
}

/// @brief Percorre a arvore recursivamente até encontrar a folha onde o novo nodo dever ser inserido
/// @param node Raiz da arvore
/// @param data Valor a ser inserido
/// @return Retorna o nodo a ser inserido
Node *insert(Node *node, int data)
{

    if (node == NULL)
        return newNode(data); // Return a new node if the tree if empty
    if (data <= node->data)
    {

        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {

        node->right = insert(node->right, data);
    }

    return node;
}

/// @brief Remove uma raiz, caso a mesma possua dois filhos, o nodo de maior valor a esquerda da raiz removida tomara seu lugar.
/// @param root Raiz que será removida
/// @return Retorna o nodo que subistituira a raiz
Node *removeRoot(Node *root)
{
    Node *p, *q;
    if (root->left == NULL)
    {
        q = root->right;
        free(root);
        return q;
    }
    if (root->right == NULL)
    {
        q = root->left;
        free(root);
        return q;
    }
    p = root;
    q = root->left;
    while (q->right != NULL)
    {
        p = q;
        q = q->right;
    }
    // q é nó anterior a root na ordem e-root-d
    // p é pai de q
    if (p != root)
    {
        p->right = q->left;
        q->left = root->left;
    }
    q->right = root->right;
    free(root);
    return q;
}

/// @brief Percorre a arvore para encontrar o nodo que deve ser removido e chama a função removeRoot() para realizar a remoção
/// @param node Raiz da arvore
/// @param data Valor a ser removido
/// @return Retorna a raiz após a remoção
Node *removeNode(Node *node, int data)
{

    if (node->data == data)
    {
        // faz a remoção
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            return NULL;
        }

        node = removeRoot(node);
        return node;
    }

    if (data <= node->data)
    {

        node->left = removeNode(node->left, data);
    }
    else if (data > node->data)
    {

        node->right = removeNode(node->right, data);
    }

    return node;
}