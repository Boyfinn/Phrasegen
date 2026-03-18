#include "cli.h"
#include <ctype.h>

int main(int argc, char* argv[])
{
    nArgs = make_default_args();

    if (!parse_args(argc, argv, &nArgs) || nArgs.help) {
        print_help(argv[0]);
        return 1;
    }

    FILE* file = fopen(nArgs.dict,"r");

    srand(strcmp(nArgs.seed, "RANDOM")? HashSeed(nArgs.seed): time(NULL));

    if(file!=NULL)
    {
        BuildIndexTable(file);
        GeneratePhrase(nArgs.words,file );
        fclose(file);
        //printf("\nTotal lines: %ld\n",lIndices);
    }
    else {
    printf("ERROR: Invalid dictionary file\n");
    return 0;
    }

    //printf("Seed: %s\n", nArgs.seed);
    return 0;
}

unsigned int HashSeed(char *str) //http://www.cse.yorku.ca/~oz/hash.html
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void BuildIndexTable(FILE* file)
{
    //TODO: Caching this?
    plIndices=malloc(nMaxLen*sizeof(long));
    long index = 0;
    int c;
    plIndices[nCount++]=0;

    while((c = fgetc(file))!=EOF)
    {
        index++;
        if(c=='\n')
        {
            if(nCount >= nMaxLen)
            {
                nMaxLen *=2; //Double if we ran out... TODO: Dynamic size?
                plIndices = realloc(plIndices,nMaxLen*sizeof(long) );
            }
            plIndices[nCount++] = index;
            lIndices = nCount;
        }
    }
}

void GeneratePhrase(int words, FILE* file)
{
    char passPhrase[512] = "";
    for(int i =0; i<words; i++)
    {
        long val = rand() %(lIndices);
        //printf("index:%li\n",val);
        fseek(file,plIndices[val],SEEK_SET);//TODO: this can mess up. HAndle this
        char buffer[512];

        fgets(buffer, sizeof(buffer), file);

        //Handle both Unix and Windows line endings first!!!
        int len = strlen(buffer);
        while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r' || buffer[len-1] == ' '))
            buffer[--len] = '\0';

        if(i <words-1 && strcmp(nArgs.delim, "NONE"))  //Replace with delimiter char
        {
            strcat(buffer, nArgs.delim);
            //https://stackoverflow.com/a/28462221/10035529
            //buffer[strcspn(buffer, "\n")] = '_';
        }
        switch(nArgs.upper)
        {
            case 0:{ //lol
                break;
            }

            case 1:{ //first letter
                buffer[0] = toupper(buffer[0]);
                break;
            }

            case 2:{ //all
                int j=0;
                while(buffer[j])
                {
                    buffer[j] = toupper(buffer[j]);
                    j++;
                }
                break;
            }
        }
        /*if(nArgs.upper)
        {
            buffer[0] = toupper(buffer[0]);
        }*/
        strcat(passPhrase,buffer);
    }
    printf("%s\n", passPhrase);
}
