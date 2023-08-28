#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// w moim rozwiazaniu korzystam z drzew AVL
// implementujac ta strukture opieralem sie na fragmentach
// kodu zaprezentowanych na stronie Geeksforgeeks.org
// w artykule dotyczacym drzew AVL

//wiezly drzewa AVL
struct Node{
    long long v;
    struct Node *left;
    struct Node *right;
    int height;
};

//funkcja zwracajaca wysokosc drzewa AVL ukorzenionego w node
int height(struct Node *node){
    if(node == NULL)
        return 0;
    return node->height;
}

//funkcja obliczajaca maksimum dwoch liczb
int maximum(int a, int b){
    int maxi = a;
    if(b > a)
        maxi = b;
    return maxi;
}

//funkcja obliczajace wysokosc drzewa AVL w node
int max_height(struct Node *node){
    return maximum(height(node->left), height(node->right)) + 1;
}

//funkcja tworzaca nowy wezel drzewa AVL
struct Node* create_node(long long v){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    node->v = v;
    return node;
}

//funkcja wykonujaca rotacje w prawo
struct Node *rotate_right(struct Node *node){
    struct Node *t1 = node->left;
    struct Node *t2 = t1->right;
    t1->right = node;
    node->left = t2;
    node->height = max_height(node);
    t1->height = max_height(t1);
    return t1;
}

//funkcja wykonujaca rotacje w lewo
struct Node *rotate_left(struct Node *node){
    struct Node *t1 = node->right;
    struct Node *t2 = t1->left;
    t1->left = node;
    node->right = t2;
    node->height = max_height(node);
    t1->height = max_height(t1);
    return t1;
}

//funkcja obliczajaca roznice w wysokosci dzieci
int get_balance(struct Node *node){
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

//funkcja wstawiajaca nowy wezel do drzewa AVL
struct Node* insert_node(struct Node* node, long long v){
    if (node == NULL)
        return create_node(v);
    if (v < node->v)
        node->left  = insert_node(node->left, v);
    else if (v > node->v)
        node->right = insert_node(node->right, v);
    else
        return node;

    node->height = max_height(node);
    int balance = get_balance(node);
    if (balance > 1 && v < node->left->v)
        return rotate_right(node);
    if (balance < -1 && v > node->right->v)
        return rotate_left(node);
    if (balance > 1 && v > node->left->v){
        node->left =  rotate_left(node->left);
        return rotate_right(node);
    }
    if (balance < -1 && v < node->right->v){
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

//funkcja zwracajaca wezel o najmniejszej wartosci w drzewie
//ukorzenionym w node
struct Node* get_min_node(struct Node* node){
    struct Node* cur = node;
    while (cur->left != NULL)
        cur = cur->left;
    return cur;
}

//funkcja usuwajaca wezel z drzewa AVL
struct Node* delete_node(struct Node* root, long long v, int *answ){
    if (root == NULL)
        return root;

    if (v < root->v)
        root->left = delete_node(root->left, v, answ);
    else if(v > root->v)
        root->right = delete_node(root->right, v, answ);
    else{
        *answ = 1;
        if((root->left == NULL) || (root->right == NULL)){
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else{
            struct Node* temp = get_min_node(root->right);
            root->v = temp->v;
            root->right = delete_node(root->right, temp->v, answ);
        }
    }
    if (root == NULL)
      return root;

    root->height = max_height(root);
    int balance = get_balance(root);
    int left_bal = get_balance(root->left);
    int right_bal = get_balance(root->right);

    if (balance < -1 && right_bal <= 0)
        return rotate_left(root);
    if (balance < -1 && right_bal > 0){
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    if (balance > 1 && left_bal >= 0)
        return rotate_right(root);
    if (balance > 1 && left_bal < 0){
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    return root;
}

//funkcja obliczajaca wartosc upper(x)
long long upper(struct Node* root, long long x, int *answ){
    if (root == NULL)
        return LLONG_MAX;

    if (x < root->v){
        long long temp = upper(root->left, x, answ);
        *answ = 1;
        if(temp < root->v)
            return temp;
        return root->v;
    }
    else if(x > root->v)
        return upper(root->right, x, answ);
    else{
        *answ = 1;
        return x;
    }
}

//funkcja obliczajaca wartosc lower(x)
long long lower(struct Node* root, long long x, int *answ){
    if (root == NULL)
        return LLONG_MIN;

    if (x < root->v)
        return lower(root->left, x, answ);
    else if(x > root->v){
        long long temp = lower(root->right, x, answ);
        *answ = 1;
        if(temp > root->v)
            return temp;
        return root->v;
    }
    else{
        *answ = 1;
        return x;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    struct Node *root = NULL;
    char o;
    long long x;
    long long answ;
    int found;
    for(int i=0; i<n; i++){
        scanf(" %c %lld", &o, &x);
        if(o == 'I'){
            root = insert_node(root, x);
        }
        else if(o == 'D'){
            found = 0;
            root = delete_node(root, x, &found);
            if(found == 0)
                printf("BRAK\n");
            else
                printf("OK\n");
        }
        else if(o == 'U'){
            found = 0;
            answ = upper(root, x, &found);
            if(found == 1)
                printf("%lld\n", answ);
            else
                printf("BRAK\n");
        }
        else if(o == 'L'){
            found = 0;
            answ = lower(root, x, &found);
            if(found == 1)
                printf("%lld\n", answ);
            else
                printf("BRAK\n");
        }
    }
}