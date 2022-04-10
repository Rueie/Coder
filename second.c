#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char* argv[]){
    FILE* data_file;
    FILE* cod_file;
    FILE* result_file;
    char buffer_for_data[BUFSIZ+1];
    int number_of_bytes;
    memset(buffer_for_data,0,BUFSIZ);
    char buffer_for_code[BUFSIZ+1];
    memset(buffer_for_code,0,BUFSIZ);

    char comand_1[128]="./program_1 ";
    char comand_result[256];
    strcat(comand_result,comand_1);
    strcat(comand_result,argv[1]);
    data_file=popen(comand_result,"r");
    if(data_file!=NULL){
        memset(comand_result,0,strlen(comand_result));
        strcat(comand_result,comand_1);
        strcat(comand_result,argv[2]);
        cod_file=popen(comand_result,"r");
        if(cod_file!=NULL){
            result_file=fopen(argv[3],"w+");
            if(result_file!=NULL){
                number_of_bytes=fread(buffer_for_code,sizeof(char),BUFSIZ,cod_file);
                if(number_of_bytes>0){
                    buffer_for_code[number_of_bytes]='\0';
                }
                int counter_cod=0;
                number_of_bytes=fread(buffer_for_data,sizeof(char),BUFSIZ,data_file);
                printf("<%s>|%d\n<%s>|%d\n",buffer_for_data,(int)strlen(buffer_for_data),buffer_for_code,(int)strlen(buffer_for_code));
                while(number_of_bytes>0){
                    if(number_of_bytes>0){
                        buffer_for_data[number_of_bytes]='\0';
                    }
                    int counter_data=0;
                    while(buffer_for_data[counter_data]!='\0'){
                        if(buffer_for_code[counter_cod]=='\0')//тут все норм
                            counter_cod=0;
                        char result=buffer_for_code[counter_cod]^buffer_for_data[counter_data];
                        fwrite(&result,sizeof(char),1,result_file);
                        counter_data++;
                        counter_cod++;
                    }
                    number_of_bytes=fread(buffer_for_data,sizeof(char),BUFSIZ,data_file);
                }
                fwrite("\n",sizeof(char),1,result_file);
            }
            else{
                pclose(data_file);
                pclose(cod_file);
                return 3;
            }
        }
        else{
            printf("Не удалось открыть файл с кодировкой!\n");
            pclose(data_file);
            return 2;
        }
    }
    else{
        printf("Не удалось открыть файл с данными!\n");
        return 1;
    }
    pclose(data_file);
    pclose(cod_file);
    fclose(result_file);
    return 0;
}