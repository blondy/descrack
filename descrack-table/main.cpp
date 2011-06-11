#include <rainbowtable.h>
#include <chaingenerator.h>

FILE * sourceFile;
char** chain = new char[2];
int* params = new int[5];
char* alphabet;

void readChainFromFile(){
    fread(chain[0], 1, 10, sourceFile);
    fread(chain[1], 1, 10, sourceFile);
}

void readParamstFromFile(){
    fread(params[0], sizeof(int), 1, sourceFile); //chain_count
    fread(params[1], sizeof(int), 1, sourceFile); //alphabet_length
    fread(alphabet, sizeof(char), params[1], sourceFile); //alphabet
    fread(params[2], sizeof(int), 1, sourceFile); //min_len
    fread(params[3], sizeof(int), 1, sourceFile); //max_len
    fread(params[4], sizeof(int), 1, sourceFile); //chain_length
}

int main(int argc, char *argv[])
{
    chain[0] = malloc(10);
    chain[1] = malloc(10);

    if(argc < 2){
        println("No source file specified!");
        return -1;
    } else {
        source = fopen(argv[1], "rb");
    }



    fclose(suorce);
    return 0;
}
