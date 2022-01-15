#include <stdio.h>
#include <stdlib.h>

int main(){
    char local[] = "arquivo.txt";
    FILE *obj;
    char *content[0];
    char get;
    int cont_vertex = 0;
    char *vertexs = (char*) malloc(cont_vertex * sizeof(char));
    int cont_face = 0;
    obj = fopen(local, "r");
    char x[50], y, z;

    if(obj == NULL){
        printf("Erro na abertura!\n");
        exit(1);
    }

    while(!feof(obj)){
        get = fgetc(obj);
        if(get == -1) break;

        if(get == 'v'){
            get = fgetc(obj);
            if(get == ' '){
                get = fgetc(obj);
                vertexs[con] = get;
                while(get != 10 && get != EOF){
                    get = fgetc(obj);
                    

                }
                cont_vertex++;
            }

            if(get == 'n'){

            }
        }

        if(get == 'f'){
            while(get != 10 && get != EOF){
                get = fgetc(obj);
            }
            cont_face++;
        }
    }
    printf("cont_vertex %i\n", cont_vertex);
    printf("cont_face %i\n", cont_face);
    printf("x %s\n", x);
    

    /*
    char *line;
    line = fgets(content, 7, obj); //7 - 1 caracteres
    if(*line == EOF){
        printf("Erro de leitura!\n");
    }else{
        printf("%s", line);
    }
    */

    fclose(obj);
    return 0;
}