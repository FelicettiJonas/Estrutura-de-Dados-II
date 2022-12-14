#include <stdio.h>
#include <stdlib.h>

/// @brief Estrutura do Node contendo um ponteiro pra esquerda, um pra direita e o valor contido no nodo e sua altura na arvore.
typedef struct sNode
{
    int data;
    int height;
    struct sNode *left, *right;
} Node;

void preOrder (Node *);
void inOrder (Node *);
void postOrder (Node *);
void freeTree (Node *);
int height(Node *);
int max(int, int);
Node *rightRotate(Node *);
Node *leftRotate(Node *);
int getBalance(Node *);
Node *newNode(int);
Node *insert(Node *, int);
Node *removeRoot(Node *);
Node *removeNode(Node *, int );

int main()
{
    Node *root = NULL;

    // root = insert(root, 5);

    // root = insert(root, (rand() % 50));
    // root = insert(root, (rand() % 50));
    // root = insert(root, (rand() % 50));
    // root = insert(root, (rand() % 50));
    // root = insert(root, (rand() % 50));
    // root = insert(root, (rand() % 50));
    // root = insert(root, (rand() % 50));
    // root = insert(root, (rand() % 50));
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);
    root = insert(root, 45);
    root = insert(root, 65);
    root = insert(root, 55);
    root = insert(root, 44);
    root = insert(root, 34);
    root = insert(root, 24);
    root = insert(root, 10);
    root = insert(root, 15);
    root = removeNode(root, 25);
    root = removeNode(root, 35);
    root = removeNode(root, 15);
    root = insert(root, 42);
    root = insert(root, 40);
    root = insert(root, 43);
    root = removeNode(root, 44);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 50);
    root = insert(root, 67);
    root = insert(root, 64);
    root = removeNode(root, 65);
    // root = insert(root, 25);
    // root = insert(root, 8);
    // root = insert(root, 9);
    // root = insert(root, 4);
    // root = insert(root, 6);
    // root = insert(root, 11);
    printf("\n");
    preOrder(root);

    // root = removeNode(root, 60);
    // printf("\n");
    // preOrder(root);

    // root = removeNode(root, 70);
    // printf("\n");
    // preOrder(root);

    // root = removeNode(root, 28);
    // printf("\n");
    // preOrder(root);

    freeTree(root);

    return 0;
}

/// @brief Algor??timo de pr?? ordem para mostrar a constru????o da arvore.
/// @param node Raiz da arvore
void preOrder (Node *node)
{
    if (node != NULL)
    {
        printf("%i-%i ", node->data, node->height);
        preOrder(node->left);
        preOrder(node->right);
    }
}

/// @brief Algor??timo de ordem para mostrar a constru????o da arvore.
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

/// @brief Algor??timo de p??s-ordem para mostrar a constru????o da arvore.
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

/// @brief Algor??timo recursivo para desalocar a mem??ria de todos os nodos da arvore.
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

/// @brief Fun????o auxiliar para descobrir a altura de um nodo.
/// @param node Nodo que ter?? a altura calculada.
/// @return Altura do nodo.
int height(Node *node)
{
    if (node == NULL)
        return 0;
    return 1+max(height(node->left), height(node->right));
}
 
/// @brief Fun????o auxiliar para identificar o maior elemento dentre 2 vari??veis.
/// @param a Vari??vel que sera comparada com b.
/// @param b Vari??vel que sera comparada com a.
/// @return O maior valor dentre a e b.
int max(int a, int b)
{
    return (a > b)? a : b;
}

/// @brief Algor??timo rightRotate. Realiza a troca da raiz pelo nodo a esquerda dela.
/// @param root Raiz que ser?? rotacionada. 
/// @return Retorna a nova raiz.
Node *rightRotate(Node *root)
{
    Node *p = root->left;
    Node *q = p->right;
 
    //Faz a rota????o
    p->right = root;
    root->left = q;
 
    //Atualiza as alturas
    root->height = height(root);
    p->height = height(p);
 
    //Retorna a nova raiz
    return p;
}
 
/// @brief Algor??timo leftRotate. Realiza a troca da raiz pelo nodo a direita dela.
/// @param root Raiz que ser?? rotacionada. 
/// @return Retorna a nova raiz.
Node *leftRotate(Node *root)
{
    Node *p = root->right;
    Node *q = p->left;
 
    //Faz a rota????o
    p->left = root;
    root->right = q;
 
    //Atualiza as alturas
    root->height = height(root);
    p->height = height(p);
 
    //Retorna a nova raiz
    return p;
}

/// @brief Fun????o para descobrir o fator de balanceamento do nodo.
/// @param node Nodo que sera balanceado.
/// @return Fator de balanceamento do nodo.
int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// @brief Realiza o balanceamento de um nodo.
/// @param node Nodo a ser balanceado
/// @return Retorna o nodo ap??s ser balanceado
Node *doBalance(Node *node)
{
    //Pega o fator de balanceamento atual
    int balance = getBalance(node);
 
    //Se o nodo estiver desbalanceado realiza o balanceamento
 
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
 
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);
 
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/// @brief Realiza o processo de aloca????o de mem??ria para o novo nodo.
/// @param data Valor contido no Node
/// @return Ponteiro para o espa??o alocado.
Node *newNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->height = 1;
    temp->left = temp->right = NULL;

    return temp;
}

/// @brief Percorre a arvore recursivamente at?? encontrar a folha onde o novo nodo dever ser inserido
/// @param node Raiz da arvore
/// @param data Valor a ser inserido
/// @return Retorna a raiz ap??s a inser????o
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

    node->height = height(node);

    node = doBalance(node);

    return node;
}

/// @brief Remove uma raiz, caso a mesma possua dois filhos, o nodo de maior valor a esquerda da raiz removida tomara seu lugar.
/// @param root Raiz que ser?? removida
/// @return Retorna o nodo que substituir?? a raiz
Node *removeRoot(Node *root)
{
    Node *p, *q;
    if (root->left == NULL)//Caso 2 - apenas elemento a direita da raiz
    {
        q = root->right;
        free(root);
        return q;
    }
    if (root->right == NULL)//Caso 2 - apenas elemento a esquerda raiz
    {
        q = root->left;
        free(root);
        return q;
    }
    p = root;
    q = root->left;
    while (q->right != NULL)//Caso 3 - encontra o elemento mais a direita da sub arvore da esquerda
    {
        p = q;
        q = q->right;
    }
    // q ?? o nodo com valor mais alto a esquerda da raiz(Nodo que ser?? removido - root)
    // p ?? pai de q
    if (p != root)//Evita que 'q' aponte pra ele mesmo
    {
        p->right = q->left;
        q->left = root->left;
    }
    q->right = root->right;
    free(root);
    return q;
}

/// @brief Percorre a arvore para encontrar o nodo que deve ser removido e chama a fun????o removeRoot() para realizar a remo????o
/// @param node Raiz da arvore
/// @param data Valor a ser removido
/// @return Retorna a raiz ap??s a remo????o
Node *removeNode(Node *node, int data)
{
    if (node->data == data)
    {
        // faz a remo????o
        if (node->left == NULL && node->right == NULL)//Caso 1 - Removendo uma folha
        {
            free(node);
            return NULL;
        }

        node = removeRoot(node);
        node->height = height(node);
    }else if (data <= node->data)
    {
        node->left = removeNode(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = removeNode(node->right, data);
    }

    //Atualiza a altura do nodo
    node->height = height(node);

    node = doBalance(node);

    return node;
}