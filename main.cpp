#include<bits/stdc++.h>
using namespace std;
//sorting whole matrix using AVL TREE  in nlogn time

int max(int a,int b){return (a>b) ? a:b;}
class Node{
public:
    int data;
    Node* left;
    Node* right;
    int height;
};

Node* newNode(int x){
    Node* node = new Node();
    node->data = x;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(Node* node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}
Node* LRotate(Node* x){
    Node* y = x->right;
    Node* temp = y->left;
    y->left = x;
    x->right = temp;


    //update height after changing the links
    x->height = max(height(x->left),height(x->right))+1;
    y->height = max(height(y->left),height(y->right))+1;

    return y;
}
Node* RRotate(Node* x){
    Node* y = x->left;
    Node* temp = y->right;
    y->right = x;
    x->left = temp;
    x->height = max(height(x->left),height(x->right))+1;
    y->height = max(height(y->left),height(y->right))+1;
    return y;
}

int getBalance(Node* N){
    if(N == NULL){
        return 0;
    }
    return height(N->left)-height(N->right);
}
Node* insert(Node* node,int x){
    //inserting just like in the binary search tree
    if(node == NULL){
        return newNode(x);
    }
    if(x <= node->data){
        //cout<<"going left"<<endl;
        node->left = insert(node->left,x);
    }
    else{
        //cout<<"going right"<<endl;
        node->right = insert(node->right,x);
    }
    node->height = max(height(node->left), height(node->right))+1;
    int balance = getBalance(node);

    /*
     * balance factor > 1 ->right rotation for x < node->left->data
     * balance factor < -1 ->left rotation for x > node->right->data
     * balance factor > 1 -> insertion at left of right position of x [x > node->left->data]
     * balance factor < -1 -> insertion at right of left position of x [x < node->right->data]
     */
    if(balance > 1 && x < node->left->data){
        //cout<<"balance disturbed - r rotate"<<endl;
        return RRotate(node);
    }
    if(balance < -1 && x > node->right->data){
        //cout<<"balance disturbed - l rotate"<<endl;
        //cout<<node->data<<endl;
        return LRotate(node);
    }
    if(balance > 1 && x > node->left->data){
        //cout<<"balance disturbed"<<endl;
        node->left = LRotate(node->left);
        return RRotate(node);
    }
    if(balance < -1 && x < node->right->data){
        //cout<<"balance disturbed"<<endl;
        node->right = RRotate(node->right);
        return LRotate(node);
    }
    return node;
}

//inorder traversal gives sorted array
vector<int> v;
void inorder(Node* root){
    if(root == NULL)
        return;
    inorder(root->left);
    v.push_back(root->data);
    inorder(root->right);
}
int main(){
    int r,c;
    cin>>r>>c;
    int a[r*c+1];
    int count = 0;
    for(int i = 0;i<r;i++){
        for(int j = 0;j<c;j++){
            int p;
            cin>>p;
            a[count] = p;
            count++;
        }
    }
    Node* root = NULL;
    for(int i = 0;i<r*c;i++){
        root = insert(root,a[i]);
    }
    inorder(root);
    int mat[r][c];
    int mark = 0;
    for(int i = 0;i<r;i++){
        for(int j = 0;j<c;j++){
            mat[i][j] = v[mark];
            mark++;
        }
    }
    /*
    for(int i = 0;i<r;i++){
        for(int j = 0;j<c;j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    cout<<mat[0][0]<<endl<<mat[r-1][c-1];
}