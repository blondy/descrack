#include <rainbowtable.h>
#include <chaingenerator.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("Invalid parameters!\n");
        return -1;
    }

    sourceFile = fopen(argv[2], "rb");
    if(sourceFile == NULL){
        printf("An error during opening file has occured!\n");
        return -1;
    }

    readParamsFromFile();
    chainGen = new ChainGenerator(alphabet, min_length, max_length, chain_length);

    planesChain[0] = (char*)malloc(10);
    planesChain[1] = (char*)malloc(10);

    char* plane = findPlainForHash(argv[1]);
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
    char* res_salt = new char[3];
    char* res_text = new char[10];
    char* transformedHash = hash;
    int hashReductionCounter = 0;
    int checkedChainsCounter = 0;

    while(hashReductionCounter < chain_length){
        chainGen->reduce(transformedHash, hashReductionCounter++, res_salt, res_text, true);
        char* reducedHash = strcat(res_salt, res_text);
        while(checkedChainsCounter++ < chain_count){
            readChainFromFile();
            if(doesChainLeadToHash(reducedHash)){
                delete res_salt;
                delete res_text;
                return planesChain[0];
            }
        }
        transformedHash = crypt(res_salt, res_text);
    }

    delete res_salt;
    delete res_text;

    return NULL;
}

void readParamsFromFile(){
    fread(&chain_count, sizeof(int), 1, sourceFile);
    fread(&alphabet_length, sizeof(int), 1, sourceFile);
    fread(&alphabet, sizeof(char), alphabet_length, sourceFile);
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
        return doesPlainLeadToHash(planesChain[0], transformedHash);
    } else {
        return false;
    }
}

bool doesPlainLeadToHash(char* plain, char* hash){
    int reductionCounter = 0;
    char* transformedPlain = plain;
    char* res_salt = new char[3];
    char* res_text = new char[10];
    while(reductionCounter < chain_length){
        if(strcmp(transformedPlain, hash) == 0){
            delete res_salt;
            delete res_text;
            return true;
        } else {
            chainGen->reduce(transformedPlain,reductionCounter++, res_salt, res_text, true);
            transformedPlain = crypt(res_salt, res_text);
        }
    }
    delete res_salt;
    delete res_text;
    return false;
}
