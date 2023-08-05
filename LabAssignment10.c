#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie* children[26];
    int count;
};

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
    if (pTrie == NULL || word == NULL)
        return;

    struct Trie* currentNode = pTrie;

    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
        {
            currentNode->children[index] = (struct Trie*)malloc(sizeof(struct Trie));
            for (int j = 0; j < 26; ++j)
                currentNode->children[index]->children[j] = NULL;
            currentNode->children[index]->count = 0;
        }

        currentNode = currentNode->children[index];
    }

    currentNode->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct Trie* pTrie, char* word)
{
    if (pTrie == NULL || word == NULL)
        return 0;

    struct Trie* currentNode = pTrie;

    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index = word[i] - 'a';
        if (currentNode->children[index] == NULL)
            return 0;

        currentNode = currentNode->children[index];
    }

    return currentNode->count;
}

// Deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < 26; ++i)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie* createTrie()
{
    struct Trie* newNode = (struct Trie*)malloc(sizeof(struct Trie));
    for (int i = 0; i < 26; ++i)
        newNode->children[i] = NULL;
    newNode->count = 0;
    return newNode;
}

// This function will return the number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
    int numWords = 0;
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 0;
    }

    char word[256];
    while (fscanf(file, "%s", word) != EOF)
    {
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void)
{
    char* inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie* pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }

    // Parse line by line, and insert each word to the trie data structure
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    
    return 0;
}
