#include <rainbowtable.h>
#include <chaingenerator.h>
#include <stdlib.h>

FILE * sourceFile;
char** chain = new char*[2];
int params[5];
char* alphabet;

void readChainFromFile(){
    fread(chain[0], 1, 10, sourceFile);
    fread(chain[1], 1, 10, sourceFile);
}

void readParamsFromFile(){
    fread(&params[0], sizeof(int), 1, sourceFile); //chain_count
    fread(&params[1], sizeof(int), 1, sourceFile); //alphabet_length
    fread(&alphabet, sizeof(char), params[1], sourceFile); //alphabet
    fread(&params[2], sizeof(int), 1, sourceFile); //min_len
    fread(&params[3], sizeof(int), 1, sourceFile); //max_len
    fread(&params[4], sizeof(int), 1, sourceFile); //chain_length
}

int main(int argc, char *argv[])
{
    chain[0] = (char*)malloc(10); //plain1
    chain[1] = (char*)malloc(10); //plain2
    char* h_res_salt = new char[3];
    char* h_res_text = new char[10];
    char* p_res_salt = new char[3];
    char* p_res_text = new char[10];

    sourceFile = fopen(argv[2], "rb");
    readParamsFromFile();

    ChainGenerator* chainGen = new ChainGenerator(alphabet, params[2], params[3], params[4]);
    char* transformedHash = argv[1];
    int hashReductionCounter = 0;
    int checkedChainsCounter = 0;
    while(hashReductionCounter < params[4]){
        chainGen->reduce(transformedHash, hashReductionCounter++, h_res_salt, h_res_text, true);
        while(checkedChainsCounter++ < params[0]){
            readChainFromFile();
            if(strcmp(strcat(h_res_salt, h_res_text), chain[1]) == 0){ //match found
                int plainReductionCounter = 0;
                char* transformedPlain1 = chain[0];
                while(plainReductionCounter < params[4]){
                    if(strcmp(transformedPlain1, argv[1]) == 0){ //right match found
                        printf(chain[0]);
                        return 0;
                    } else {
                        chainGen->reduce(transformedPlain1,plainReductionCounter++, p_res_salt, p_res_text, true);
                        transformedPlain1 = crypt(p_res_salt, p_res_text);
                    }
                }
            }
        }
        transformedHash = crypt(h_res_salt, h_res_text);
    }

    fclose(sourceFile);
    return 0;
}
