#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Trie {
    int flag;
    struct Trie * children [26];
} Trie;

//function prototypes
void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);

void insert(struct Trie **ppTrie, char *word)
{
    if(*ppTrie == NULL) //defensive programming
        return;
    
    int length = strlen(word);
    Trie * temp = *ppTrie;

    for(int i = 0; i < length; i++) //loop through the length of the word
    {
        int index = word[i] - 'a'; //use ASCII values to find the index of the letter

        if(temp->children[index] == NULL)
            temp->children[index] = (Trie *) calloc(1, sizeof(Trie));
        
        temp = temp->children[index];
    }

    temp->flag++; //raise the flag at the end of the tree
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if(pTrie == NULL) //defensive programming
        return 0;

    int length = strlen(word);
    Trie *temp = pTrie;

    for(int i = 0; i < length; i++) //loop for the length of the word
    {
        int index = word[i] - 'a'; //use ASCII values to find the index of the letter

        if(temp->children[index] == NULL)
            return 0;
        
        temp = temp->children[index];
    }

    return temp->flag; //if the word is in the trie, the flag will be 1

}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i = 0; i < 26; i++) //loop for each letter of the alphabet
    {
        if(pTrie->children[i] != NULL)
        {
            deallocateTrie(pTrie->children[i]); //recursive call
        }
    }

    free(pTrie);

    return NULL;
}

int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    Trie *trie = calloc(1, sizeof(Trie));
    
    for (int i=0;i<5;i++)
    {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);

    if (trie != NULL)
        printf("There is an error in this program\n");

    return 0;
}