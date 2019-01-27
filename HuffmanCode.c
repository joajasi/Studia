#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_CHARS 7

typedef struct HuffNode {
    char chr;
    int freq;
    struct HuffNode* left; 
    struct HuffNode* right; 
} HuffNode;

typedef struct QueueNode {
    HuffNode* node; 
    struct QueueNode* next; 
} QueueNode;


QueueNode* createQueueNode(HuffNode* huffNode) {
    printf("createQueueNode %c\n", huffNode->chr);
    QueueNode* queueNode = (QueueNode*) malloc(sizeof(QueueNode));
    queueNode->node = huffNode;
    queueNode->next = NULL;
    return queueNode;
}

void addToQueue(QueueNode** root, HuffNode* node) {
    printf("addToQueue %c\n", node->chr);
    QueueNode* queueNode = createQueueNode(node);
    if(!*root) {
        *root = queueNode;
    } else {
        printf("addtoQueue: 2\n");
        if((*root)->node->freq > node->freq) {
            queueNode->next = *root; 
            *root = queueNode;
        } else {
            QueueNode* temp = *root; 
            while (temp->next && temp->next->node->freq < node->freq) {
                temp = temp->next;
            }
            if (temp->next) {
                queueNode->next = temp->next;
            }
            temp->next = queueNode;
        }
    }
}

HuffNode* removeFromQueue(QueueNode** root) {
    printf("removeFromQueue\n");
    if (!*root) {
        return NULL;
    }
    HuffNode* node = (*root)->node;
    QueueNode* temp = *root;
    *root = (*root)->next;
    free(temp);
    return node;
}

HuffNode* createHuffNode(char chr, int freq, HuffNode* left, HuffNode*right) {
    printf("createHuffNode %c\n", chr);
    HuffNode* node = (HuffNode*)malloc(sizeof(HuffNode));
    if (freq) {
        node->left = NULL;
        node->right = NULL; 
        node->chr = chr;
        node->freq = freq;
    }
    else {
        node->freq = left->freq + right->freq;
        node->left = left;
        node->right = right;
        node->chr = 0;
    }
    return node;
}

void printHuff(HuffNode* node, int lvl, char* table) {
    if (node) {
        if (node->left) {
            table[lvl] = '0'; 
            table[lvl+1] = 0;
            printHuff(node->left, lvl +1, table); 
        }
        if (node->right) {
            table[lvl] = '1'; 
            table[lvl+1] = 0;
            printHuff(node->right, lvl + 1, table);
        }
        if (node->chr) {
            printf("%c: %s\n", node->chr, table);
        }
    }
}
void huffman(char* chars, int* freqs, int size, HuffNode** root) {
    printf("huffman\n"); 
    QueueNode* queueRoot = NULL; 
    for (int i = 0; i < size; i = i + 1) {
        printf("huffman: addToQueue \n");
        addToQueue(&queueRoot, createHuffNode(chars[i], freqs[i], NULL, NULL));
    }

    HuffNode* node1 = removeFromQueue(&queueRoot);
    HuffNode* node2 = removeFromQueue(&queueRoot);

    while (node1 && node2) {
        if (node1->freq < node2->freq) {
            addToQueue(&queueRoot, createHuffNode(0, 0, node1, node2));
        } else {
            addToQueue(&queueRoot, createHuffNode(0, 0, node2, node1));
        }
        node1 = removeFromQueue(&queueRoot);
        node2 = removeFromQueue(&queueRoot);
    }
    
    *root = node1;
    
}   

int main() {
    
    char characters[NUMBER_OF_CHARS] = {'a', 'b' , 'c', 'd', 'e', 'f', 'g'};
    int frequencies[NUMBER_OF_CHARS] = {12, 2, 11, 4, 17, 6, 9};
    
    HuffNode* root = NULL;
    huffman(characters, frequencies, NUMBER_OF_CHARS, &root);
    char table[10] = {};
    printHuff(root, 0, table);
    return 0; 
    
}
