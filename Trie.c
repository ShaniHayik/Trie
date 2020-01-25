#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BIGGER_SIZE 30
#define MAX 50


// A node of Trie
struct Node {
    char data;
    unsigned isEndOfString: 1;
    int count;
    char letter;
    struct Node* children[26];
    struct Node *left, *eq, *right;
};

// A function to create a new Trie node
struct Node* newNode(char data) {
    struct Node* temp = (struct Node*) malloc(sizeof( struct Node ));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    temp->count=0;
    temp->children[26]= NULL;
    return temp;
}

//this function changes bigger letters to small letters
void change_char(char *word){
    int i = 0;
    while (word[i] != '\0') {
        if (word[i] >= 65 && word[i] <= 90) {
            word[i] = word[i] + 32;
        }
        i++;
    }
}


// Function to insert a new word in a Trie
void insert(struct Node** root, char *word) {
    change_char(word);
    // Base Case: Tree is empty
    if (!(*root))
        *root = newNode(*word);

    // If current character of word is smaller than root's character, then insert this word in left of root
    if ((*word) < (*root)->data)
        insert(&( (*root)->left ), word);

        // If current character of word is greater than root's character, then insert this word in right of root
    else if ((*word) > (*root)->data)
        insert(&( (*root)->right ), word);

        // If current character of word is same as root's character,
    else{
        if (*(word+1))
            insert(&( (*root)->eq ), word+1);
            // the last character of the word
        else
        (*root)->isEndOfString = 1;

    }
    (*root)->count++;
}


// A recursive function to Trie
void print_help(struct Node* root, char* buffer, int depth) {
    if (root){
        // First traverse the left subtree
        print_help(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->isEndOfString){
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
           printf( "%d\n", root->count);
        }

        // Traverse the subtree using equal pointer (middle subtree)
        print_help(root->eq, buffer, depth + 1);

        // Finally Traverse the right subtree
        print_help(root->right, buffer, depth);
    }
}

// function to traverse a Trie
void print(struct Node* root) {
    char buffer[MAX];
    print_help(root, buffer, 0);
}

void print_help_reverse(struct Node* root, char* buffer, int depth) {
    if (root){
        // First traverse the right subtree
        print_help_reverse(root->right, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->isEndOfString){
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
            printf( "%d\n", root->count);
        }

        // Traverse the subtree using equal pointer (middle subtree)
        print_help_reverse(root->eq, buffer, depth + 1);

        // Finally Traverse the left subtree
        print_help_reverse(root->left, buffer, depth);
    }
}

//function to traverse a Trie reverse
void print_reverse(struct Node* root) {
    char buffer[MAX];
    print_help_reverse(root, buffer, 0);
}

//free memory of trie
void freeTrie(struct Node** head){
    struct Node* n = *head;
    for (size_t i = 0; i < 26; i++) {
        if(n->children[i]!=NULL){
            freeTrie(&(n->children[i]));
        }
    }
    free(n);
}


int main(int argc, char* argv[]){

    struct Node* root = NULL;
    int size = 256, end_file = 0, count = 0, reverse = 0;
    char* word = (char*)malloc(sizeof(char)*size);
    char* bigger = NULL;
    char c = getchar();


    //checks if reverse or regular
    if(argc==2 && strcmp(argv[1],"r") == 0) {
        reverse = 1;
    }

    while((c!=EOF) || (c==EOF && end_file!=1)){
        if(c!=' ' && c!= '\n' && c!='\0' && c!='\t'){
            if(count==size){
                bigger = (char*)realloc(word,(size+BIGGER_SIZE)*sizeof(char));
                size = size + BIGGER_SIZE;
                if(bigger==NULL && word!=NULL){
                    free(word);
                    return -1;
                }
                word=(char*)calloc(size,sizeof(char));
                strcpy(word,bigger);
                free(bigger);
            }
            word[count]=c;
            count++;
        }

        //insert word that not empty
        if((c==' ' || c=='\n' || c=='\t' || c=='\0') || c==EOF){
            word[count]='\0';
            if(word[0]!=' ' && count >= 1){
                insert(&root,word);
            }
            count=0;
        }

        if(c==EOF) end_file=1;
        c = getchar();
    }

    if(reverse == 1) {
        print_reverse(root);
    }
    else {
        print(root);
    }

    freeTrie(&root);
    free(word);

    return 0;
}