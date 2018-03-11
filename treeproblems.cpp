
struct node
{
    int data;
    node* left;
    node* right;
};
/*
 * This function traverses a tree in preOrder system
 */

void preOrder(node *root) {
    if(!root)return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}
 /*
 * This function traverses a tree in preOrder system
 */
 
void postOrder(node *root) {
    if(!root)return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);

}
/*
 * This function traverses a tree in preOrder system
 */
void inOrder(node *root) {
    if(!root)return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

/*
 * This function accurately finds the height of a tree
*/
int height(Node* root){
	if(!root || (!root->left && !root->right))return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
        
    if(leftHeight > rightHeight){
		return 1 + leftHeight;
    }else{
        return 1 + rightHeight;
    }
}
/*
 * This function finds the top view of a tree. the top view is 
 * defined as the horizontal distance from a node to the root node
 * This implementation is a simple BFS using a stack.
*/


void topView(node * root) {
    if(!root)return;
    node *curr = root;
    stack<node *> s;
    while(curr){
        s.push(curr);
        curr = curr->left;
    }
    while(!s.empty()){
        node *n = s.top();
        s.pop();
        printf("%d ", n->data);
    }
    node *r = root->right;
    while(r){
        printf("%d ", r->data);
        r = r->right;
    }
  
}
/*
 * This is a level order traversal problem
 * print the nodes at each level
 * for level in levels:
 *    printNodes at level
 * printNodes at level algorithm:
 */ 

int get_height(node* root){
    if(!root || (!root->left && !root->right))return 0;
    int leftHeight = get_height(root->left);
    int rightHeight = get_height(root->right);
        
    if(leftHeight > rightHeight){
        return 1 + leftHeight;
    }else{
        return 1 + rightHeight;
    }
}

void print_level(node *root, int level){
    if(!root)return;
    if(level == 0){
        printf("%d ", root->data);
    }else if(level > 0){
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}
void levelOrder(node * root) {
    if(!root)return;
    node *temp = root;
    int height = get_height(temp);
    for(int level = 0; level <= height; level++){
        print_level(root, level);
    }
}
/* 
 * As all tree problems here is simple decoding problem
 * where s is a string "10010101" where a '1' denotes a 
 * left traversal while '0' requires a right traversal
 * the character is located where a parent node has no
 * children. 
 */

void decode_huff(node * root, string s)
{
    string result = "";
    node *temp = root;
    for(int i = 0; i <= s.length(); i++){
        if(!temp->left && !temp->right){
            result += temp->data;
            temp = root;
        }
        if(s[i] == '1'){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    cout << result << endl;
}
/*
 * Lowest common ancestor problem. This is my implementation 
 * attempting to use 0(1) space and 0(n) time. The implementation
 * doesn't is correct for most lca problems but fails when the 
 * v1 is the parent node of v2. My next task is to debug it. 
 * Will implement using disjointed-set forest 
 */
 node *lca(node *root, int v1,int v2)
{
    node *result = root;
    node *temp = root;
    while((root->data == v1) && (temp->data == v2)){
        if((temp && root) && temp->data == root->data && (temp->data != v1 && temp->data != v2)){
            result = root; //ancestor
        }
        if((root && root->left) && (root->left->data <= v1)){
            root = root->right;
        }else{
            root = root->left;
        }
        if((temp && temp->left) && (temp->left->data <= v2)){
            temp = temp->right;
        }else{
            temp = temp->left;
        }
    }
    return result;  
}
  
