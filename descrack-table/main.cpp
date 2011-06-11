#include <rainbowtable.h>
#include <chaingenerator.h>

char** readChainFromFile(FILE* file){
    char** chain = new char[2];
    chain[0] = malloc(10);
    chain[1] = malloc(10);
    fread(chain[0], 1, 10, file);
    fread(chain[1], 1, 10, file);
    return chain;
}

int* readChainCountFromFile(FILE* file){
    int* count = malloc(sizeof(int));
    fread(count, 1, sizeof(int), file);
    return count;
}

int main(int argc, char *argv[])
{
    FILE * source;
    if(argc < 2){
        println("No source file specified!");
        return -1;
    } else {
        source = fopen(argv[1], "rb");
    }



    fclose(suorce);
    return 0;
}
