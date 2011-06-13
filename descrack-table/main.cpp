#include <chaingenerator.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <crypt.h>

FILE * sourceFile;
char** planesChain = new char*[2];
int chain_count;
int alphabet_length;
int min_length;
int max_length;
int chain_length;
char* alphabet;
ChainGenerator* chainGen;

char* findPlainForHash(char* hash);
void readParamsFromFile();
void readChainFromFile();
bool doesChainLeadToHash(char* reducedHash);
bool doesPlainLeadToHash(char* plain, char* hash);
int crackMain(int argc, char** argv);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Invalid parameters!\n");
        return -1;
    }

    if(strcmp(argv[1], "crack") == 0)
    {
        return crackMain(argc, argv);
    }
    else if(strcmp(argv[1], "hash") == 0)
    {
        if(argc < 4)
        {
            printf("Usage: descrack-table hash PASSWORD SALT\n");
            return -1;
        }
        printf("Hash for %s with salt %s = %s\n", argv[2], argv[3], crypt(argv[2], argv[3]));
        return 0;
    }
    else
    {
        printf("Unknown option %s\n", argv[1]);
        return 0;
    }
}

int crackMain(int argc, char** argv)
{
    if(argc < 4)
    {
        printf("Usage: descrack-table crack HASH TABLE\n");
        return -1;
    }

    sourceFile = fopen(argv[3], "rb");
    if(sourceFile == NULL){
        printf("An error during opening file has occured!\n");
        return -1;
    }

    readParamsFromFile();
    chainGen = new ChainGenerator(alphabet, min_length, max_length, chain_length);

    planesChain[0] = (char*)malloc(10);
    planesChain[1] = (char*)malloc(10);

    char* plane = findPlainForHash(argv[2]);
    if(plane != NULL){
        printf("%s\n", plane);
    } else {
        printf("No plane text found for given hash :(\n");
    }

    fclose(sourceFile);

    delete planesChain[0];
    delete planesChain[1];
    delete planesChain;

    return 0;

}

char* findPlainForHash(char* hash){
    char res_salt[3];
    char res_text[10];
    char reduced[11];
    char* transformedHash = hash;
    int hashReductionCounter = 0;
    int checkedChainsCounter = 0;

    while(hashReductionCounter < chain_length){
        chainGen->reduce(transformedHash, hashReductionCounter++, res_salt, res_text, true);
        memcpy(reduced, res_salt, 2);
        memcpy(reduced+2, res_text, 9);

        while(checkedChainsCounter++ < chain_count){
            readChainFromFile();
            if(doesChainLeadToHash(reduced)){
                return planesChain[0];
            }
        }
        transformedHash = crypt(res_salt, res_text);
    }

    return NULL;
}

void readParamsFromFile(){
    fread(&chain_count, sizeof(int), 1, sourceFile);
    fread(&alphabet_length, sizeof(int), 1, sourceFile);
    alphabet = new char[alphabet_length+1];
    alphabet[alphabet_length] = 0x00; //nul terminating alphabet, ChainGenerator expects string as alphabet
    fread(alphabet, sizeof(char), alphabet_length, sourceFile);
    fread(&min_length, sizeof(int), 1, sourceFile);
    fread(&max_length, sizeof(int), 1, sourceFile);
    fread(&chain_length, sizeof(int), 1, sourceFile);
}

void readChainFromFile(){
    fread(planesChain[0], 1, 10, sourceFile);
    fread(planesChain[1], 1, 10, sourceFile);
}

bool doesChainLeadToHash(char* reducedHash){
    if(strcmp(reducedHash, planesChain[1]) == 0){
        return doesPlainLeadToHash(planesChain[0], reducedHash);
    } else {
        return false;
    }
}

bool doesPlainLeadToHash(char* plain, char* hash){
    int reductionCounter = 0;
    char* transformedPlain = plain;
    char res_salt[3];
    char res_text[10];
    while(reductionCounter < chain_length){
        if(strcmp(transformedPlain, hash) == 0){
            return true;
        } else {
            chainGen->reduce(transformedPlain,reductionCounter++, res_salt, res_text, true);
            transformedPlain = crypt(res_salt, res_text);
        }
    }
    return false;
}
