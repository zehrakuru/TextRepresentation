//Zehra Kuru

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//struct for binary search tree
struct node{
	char *key;
	int key2;
	struct node *left,*right;
};

//struct for binary tree
struct BTnode{
	char *key;
	int frequency;
	struct BTnode *left,*right;
	int leftNodeCnt, rightNodeCnt;
};

//creating a new binary search tree node
struct node *newNode(char *item, int num) {
	
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	
	temp -> key2 = num;
	temp->left = NULL;
	temp->right = NULL;
	temp -> key = strdup(item);
	
	return temp;
}

//creating a new binary tree node
struct BTnode *newNodeBT(char *item, int num) {
	struct BTnode *temp = (struct BTnode*)malloc(sizeof(struct BTnode));
	
	temp -> frequency = num;
	temp->left = NULL;
	temp->right = NULL;
	temp -> key = strdup(item);
	
	return temp;
}

//inserting a new node to Binary Search Tree for words
struct node* insert(struct node* node,char *key, int key2){
	int result = NULL;
	
	if(node == NULL)
	   return newNode(key, key2);
	   
	 //compares two words  
	result = stricmp(key, node->key);
  	
  	//if the word comes before root, set it to left
	if(result<0){
		node->left = insert(node->left, key, key2);
	}	 
	
	//if the word comes after the root, set it to right  
	else if (result>0){
	node->right = insert(node->right, key, key2);
}
    return node;
}

//inserting a new node to Binary Search Tree for frequencies
struct node* insertFreq(struct node* node,char *key, int key2){
	
	if(node == NULL)
	   return newNode(key, key2);

  	//compares the frequencies
  	//if the frequency is smaller than the root, set it to left
	if(key2 < node->key2){
		node->left = insertFreq(node->left, key, key2);
	}
	//if the frequency is larger than the root, set it to right	   
	else if (key2 >= node->key2){
	node->right = insertFreq(node->right, key, key2);
}
    return node;
}


//for inorder traversal of Binary Search Tree
void inorder(struct node *root){
	if (root != NULL){
		inorder(root->left);
		printf("%s \n", root->key);
		inorder(root->right);
	}
}

//for inorder traversal of Binary Tree
void inorderFreq(struct BTnode *root){
	if (root != NULL){
		inorderFreq(root->left);
		printf("%d	%s\n", root->frequency, root->key);
		inorderFreq(root->right);
	}
}

//this method finds the max value of frequencies in binary search tree
struct node* findMaxVal(struct node* root) { 

    if (root == NULL) 
        return NULL; 
        
    if(root->right != NULL){
    	return findMaxVal(root->right);
    }
  return root;
} 

//looking for the tree whether perfect binary tree is or not
bool isPerfectBT(int cnt){
    cnt += 1;
    while (cnt % 2 == 0)
        cnt = cnt / 2;

    if (cnt != 1)
        return false;
    else
        return true;
}

//inserts the node from the binary search tree of frequencies to binary tree
struct BTnode* insertBinaryTree(struct BTnode* rootBT, struct node* node){
	
	if (rootBT == NULL) {
        rootBT = newNodeBT(node->key,node->key2);
        return rootBT;
    }
    
    //when counts of left sides are equal to counts of right sides
    if (rootBT->rightNodeCnt == rootBT->leftNodeCnt) {
        rootBT->left = insertBinaryTree(rootBT->left, node);
        rootBT->leftNodeCnt = rootBT->leftNodeCnt + 1;
    }
	
	
	else if (rootBT->rightNodeCnt < rootBT->leftNodeCnt) {
		//if left side is done, then add to right side
        if (isPerfectBT(rootBT->leftNodeCnt)) {
            rootBT->right = insertBinaryTree(rootBT->right, node);
            rootBT->rightNodeCnt += 1;
        }
        else {
            rootBT->left = insertBinaryTree(rootBT->left, node);
            rootBT->leftNodeCnt += 1;
        }
    }
    return rootBT;
}


struct node* minValue(struct node* node)
{
    struct node* current = node;
 
    //looks for left side
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
 
//delete the node from the binary search tree of frequencies after adding to binary tree
struct node* deleteNode(struct node* root, int freq) {

    if (root == NULL)
        return root;
 
    //if the wanted key is smaller than the root, then go to left
    if (freq < root->key2)
        root->left = deleteNode(root->left, freq);
 
    //if the wanted key is larger than the root, then go to right
    else if (freq > root->key2)
        root->right = deleteNode(root->right, freq);
 
    // if this is the key which is searched for, then delete it
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
 
        //find the smallest value in the right side
        struct node* temp = minValue(root->right);
        root->key2 = temp->key2;
 
        //then delete it
        root->right = deleteNode(root->right, temp->key2);
    }
    return root;
}
 
//*************************************************************************************//

//Total Access Time for binary search tree
int totalAccessTime(struct node* node, int depth) {

    if (node != NULL) {
       return (depth +1)*(node->key2) + totalAccessTime(node->left, depth + 1) + totalAccessTime(node->right, depth + 1);
    }
}

//Total Access Time for binary tree
int totAccessTimeBT(struct BTnode* btnode, int depth) {

    if (btnode != NULL) {
       return (depth +1)*(btnode->frequency) + totAccessTimeBT(btnode->left, depth + 1) + totAccessTimeBT(btnode->right, depth + 1);
    }
}

FILE *file;

int main(int argc, char *argv[]) {
	
	file = fopen("input.txt", "r");
	char line[100];
	char *number = NULL;
	char *word, *freq = NULL;
	int frequency =NULL;
	struct node* root = NULL;
	int num = NULL;
	struct node* rootBT = NULL;
	struct BTnode * btnode = NULL;
	
	//if the program cannot find the file, give a error message
	if (file == NULL) {
        printf("Error! cannot find the file");
        exit(1);
    }
    else {
    	int i = 0;
    	//reading file
    	while(fgets(line,sizeof line,file)!= NULL) {
    		
    		number = strtok(line,",");
    		word = strtok(NULL,",");
    		freq = strtok(NULL, ",");
    		
    		//convert string to integer
    		frequency = atoi(freq);
    		num = atoi(number);
			root = insert(root, word, frequency);
	 		rootBT = insertFreq(rootBT, word, frequency);
			
		}
		int totalBST = 0;
		printf("Binary Search Tree: \n\n");	
		//prints the BST by inorder traversal
		inorder(root);
		//Calculates the total access time for binary search tree
		totalBST = totalAccessTime(root,0);
		printf("\nTotal Access Time of Binary Search Tree: ");
		printf("%d\n", totalBST);
		//*************************************************************//
      	for(i=0; i < num; i++){
      		btnode = insertBinaryTree(btnode,findMaxVal(rootBT));
      		rootBT = deleteNode(rootBT, findMaxVal(rootBT)->key2);
		  }
		  
		printf("\nBinary Tree: \n\n");
		//prints the BT by inorder traversal	
        inorderFreq(btnode);
        int total =0;
        //Calculates the total access time for binary tree
        total = totAccessTimeBT(btnode,0);
        printf("\nTotal Access Time of Binary Tree: ");
        printf("%d", total);
}
	return 0;
}
