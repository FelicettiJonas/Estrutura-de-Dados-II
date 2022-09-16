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

    root = insert(root, (rand() % 50));
    root = insert(root, (rand() % 50));
    root = insert(root, (rand() % 50));
    root = insert(root, (rand() % 50));
    root = insert(root, (rand() % 50));
    root = insert(root, (rand() % 50));
    root = insert(root, (rand() % 50));
    root = insert(root, (rand() % 50));
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);
    root = insert(root, 80);
    root = insert(root, 90);
    // root = insert(root, 25);
    // root = insert(root, 8);
    // root = insert(root, 9);
    // root = insert(root, 4);
    // root = insert(root, 6);
    // root = insert(root, 11);

    preOrder(root);

    root = removeNode(root, 60);

    printf("\n");
    preOrder(root);

    root = removeNode(root, 70);

    printf("\n");
    preOrder(root);

    freeTree(root);

    return 0;
}

/// @brief Algorítimo de pré ordem para mostrar a construção da arvore.
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

/// @brief Algorítimo de ordem para mostrar a construção da arvore.
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

/// @brief Algorítimo de pós-ordem para mostrar a construção da arvore.
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

/// @brief Algorítimo recursivo para desalocar a memória de todos os nodos da arvore.
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

/// @brief Função auxiliar para descobrir a altura de um nodo.
/// @param node Nodo que terá a altura calculada.
/// @return Altura do nodo.
int height(Node *node)
{
    if (node == NULL)
        return 0;
    return 1+max(height(node->left), height(node->right));
}
 
/// @brief Função auxiliar para identificar o maior elemento dentre 2 variáveis.
/// @param a Variável que sera comparada com b.
/// @param b Variável que sera comparada com a.
/// @return O maior valor dentre a e b.
int max(int a, int b)
{
    return (a > b)? a : b;
}

/// @brief Algorítimo rightRotate. Realiza a troca da raiz pelo nodo a esquerda dela.
/// @param root Raiz que será rotacionada. 
/// @return Retorna a nova raiz.
Node *rightRotate(Node *root)
{
    Node *p = root->left;
    Node *q = p->right;
 
    //Faz a rotação
    p->right = root;
    root->left = q;
 
    //Atualiza as alturas
    root->height = height(root);
    p->height = height(p);
 
    //Retorna a nova raiz
    return p;
}
 
/// @brief Algorítimo leftRotate. Realiza a troca da raiz pelo nodo a direita dela.
/// @param root Raiz que será rotacionada. 
/// @return Retorna a nova raiz.
Node *leftRotate(Node *root)
{
    Node *p = root->right;
    Node *q = p->left;
 
    //Faz a rotação
    p->left = root;
    root->right = q;
 
    //Atualiza as alturas
    root->height = height(root);
    p->height = height(p);
 
    //Retorna a nova raiz
    return p;
}

/// @brief Função para descobrir o fator de balanceamento do nodo.
/// @param node Nodo que sera balanceado.
/// @return Fator de balanceamento do nodo.
int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

/// @brief Realiza o processo de alocação de memória para o novo nodo.
/// @param data Valor contido no Node
/// @return Ponteiro para o espaço alocado.
Node *newNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->height = 1;
    temp->left = temp->right = NULL;

    return temp;
}

/// @brief Percorre a arvore recursivamente até encontrar a folha onde o novo nodo dever ser inserido
/// @param node Raiz da arvore
/// @param data Valor a ser inserido
/// @return Retorna a raiz após a inserção
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

    //Atualiza a altura do nodo
    node->height = height(node);
 
    //Pega o fator de balanceamento atual
    int balance = getBalance(node);
 
    //Se o nodo estiver desbalanceado realiza o balanceamento
 
    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && data > node->left->data)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/// @brief Remove uma raiz, caso a mesma possua dois filhos, o nodo de maior valor a esquerda da raiz removida tomara seu lugar.
/// @param root Raiz que será removida
/// @return Retorna o nodo que substituirá a raiz
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
    // q é o nodo com valor mais alto a esquerda da raiz(Nodo que será removido - root)
    // p é pai de q
    if (p != root)//Evita que 'q' aponte pra ele mesmo
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

    //Pega o fator de balanceamento atual
    int balance = getBalance(node);
 
    //Se o nodo estiver desbalanceado realiza o balanceamento
 
    // Left Left Case
    if (balance > 1 && data > node->left->data)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && data < node->right->data)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && data < node->left->data)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && data > node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}