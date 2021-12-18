#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define UTF8_H //To be applied to utf8

char controlCSVFile(char *csvFileNameTemp);
//Check whether the file is csv or not

char controlXMLFile(char *xmlFileNameTemp);
//Check whether the file is xml or not

char controlSeparatorInCsvFile(char *csvFileName,char *separator);
//Separator control

char controlEmptyAndEndLine(char newCsvLine[],char arr[],char separator2,char endLine,int csvFileLineSize);
//Check of line break character
//Control of places where some information is not available

char printXmlFile(FILE *xmlFile,FILE *csvFile,char *xmlFileName,char *separator,char endLine,char separator2);
//writing information from csv file to xm file

//./2017510049 contacts.csv contacts.xml -separator     1    -opsys      1
//argv[0]    argv[1]      argv[2]      argv[3]     argv[4] argv[5] argv[6]
char main(char argc, char *argv[]){ 
    char *csvFileName=argv[1];
    char *xmlFileName=argv[2];
    char *csvFileNameTemp=argv[1];
    char *xmlFileNameTemp=argv[2];
    char *separator;
    char separator2;
    char *endLine;

    if(strncmp(argv[1],"-h",strlen("-h"))==0){
        printf("\nargv[0] --> Name of running c file (Example: ./2017510049)\n");
        printf("argv[1] --> Input csv file name (Example: Contacts.csv)\n");
        printf("argv[2] --> Output xml file name (Example: contacts.xml)\n");
        printf("argv[3] --> Write \"-separator\"\n");
        printf("argv[4] --> Separator options\n");
        printf(" \"1\" = comman(,)\n");
        printf(" \"2\" = tab(\t)\n");
        printf(" \"3\" = semicolon(;)\n");
        printf("argv[5] --> Write \"-opsys\"\n");
        printf("argv[6] --> End of line character options\n");
        printf(" \"1\" = windows\n");
        printf(" \"2\" = linux\n");
        printf(" \"3\" = macos\n\n");
        printf("Example= ./2017510049 Contacts.csv contacts.xml -separator 1 -opsys 1\n\n");
        return 0;
    }

    if(argc!=7){
       printf("\nWrong input!!\n");
       printf("Example= ./2017510049 inputfile.csv outputfile.xml -separator 1 -opsys 1\n\n");
       return 0;
    }

    if(strncmp(argv[3],"-separator",strlen("-separator"))!=0){
        printf(argv[3]);
        printf("\nWrong input!!\n");
        printf("Control -> argv[3] will be \"-separator\" \n\n");
        return 0;
    }
    if(strncmp(argv[5],"-opsys",strlen("-opsys"))!=0){
        printf(argv[5]);
        printf("\nWrong input!!\n");
        printf("Control -> argv[5] will be \"-opsys\" \n\n");
        return 0;
    }

    //Comparing input from user
    if(*argv[4]=='1'){
        separator=",";
        separator2=',';
    }
    else if(*argv[4]=='2'){
        separator="\t";
        separator2='\t';
    }
    else if(*argv[4]=='3'){
        separator=";";
        separator2=';';
    }
    else{
        printf("\nWrong seperator!!\n");
        printf("1 = comman(,)\n");
        printf("2 = tab(\t)\n");
        printf("3 = semicolon(;)\n\n");
        return 0;
    }
    
    if(*argv[6]=='1'){
        endLine="\r\n";
    }
    else if(*argv[6]=='2'){
        endLine="\r";
    }
    else if(*argv[6]=='3'){
        endLine="\n";
    }
    else{
        printf("\nWrong opsys!!\n\n");
        printf("1 = windows\n");
        printf("2 = linux\n");
        printf("3 = macos\n\n");
        return 0;
    }
    //Check whether the file is csv or not
    int csvNameControl=controlCSVFile(csvFileNameTemp);
    if(csvNameControl!=0){
        printf("\nThis file not csv!!\n");
        printf("Input file => inputfile.csv\n\n");
        return 0;
    }
    //Read csv file
    FILE *csvFile= fopen(csvFileName, "r");

    if(csvFile==NULL){
        printf("\nThis csv file not found!!!\n\n");
        return 0;
    }
    //Check whether the file is xml or not
    int xmlNameControl=controlXMLFile(xmlFileNameTemp);
    if(xmlNameControl!=0){
        printf("\nThis file not xml!!\n");
         printf("Output file => outputfile.xml\n\n");
        return 0;
    }
    
    int control=controlSeparatorInCsvFile(csvFileName,separator);
    if(control==1){
        printf("\nThis separator is not in the csv file!!\n\n");
        return 0;
    }
    //Creating a xml file
    FILE *xmlFile= fopen(xmlFileName, "w");
    printXmlFile( xmlFile, csvFile, xmlFileName,separator, *endLine,separator2);
    printf("\nCreat new xml file!\n\n");
   
    fclose(xmlFile);
    fclose(csvFile);
    return 0;
}

//Check whether the file is csv or not
char controlCSVFile(char *csvFileNameTemp){
    int control=0;
    int temp;
    int i=0;
    while(i!=strlen(csvFileNameTemp)){
        if(csvFileNameTemp[i]=='.'){
            temp=i;
            break;
        }
        i=i+1;
    }
    temp=temp+1;
    if(strlen(csvFileNameTemp)-temp!=3){
        control=1;
    }
    else if(strlen(csvFileNameTemp)-temp==3){
        if(csvFileNameTemp[strlen(csvFileNameTemp)-3]=='c'&&csvFileNameTemp[strlen(csvFileNameTemp)-2]=='s'&&csvFileNameTemp[strlen(csvFileNameTemp)-1]=='v'){
            control=0;
        }
        else{
            control=control+1;
        }
    }

    return control;
}

//Check whether the file is xml or not
char controlXMLFile(char *xmlFileNameTemp){
    int control=0;
    int temp;
    int i=0;
    while(i!=strlen(xmlFileNameTemp)){
        if(xmlFileNameTemp[i]=='.'){
            temp=i;
            break;
        }
        i=i+1;
    }
    temp=temp+1;
    if(strlen(xmlFileNameTemp)-temp!=3){
        control=1;
    }
    else if(strlen(xmlFileNameTemp)-temp==3){
        if(xmlFileNameTemp[strlen(xmlFileNameTemp)-3]=='x'&&xmlFileNameTemp[strlen(xmlFileNameTemp)-2]=='m'&&xmlFileNameTemp[strlen(xmlFileNameTemp)-1]=='l'){
            control=0;
        }
        else{
            control=control+1;
        }
    }

    return control;
}

//User entered separator control
//Check whether the separation process is applied to the file with that separator
char controlSeparatorInCsvFile(char *csvFileName,char *separator){
     FILE *csvFile= fopen(csvFileName, "r");
    char separatorCheck[__INT16_MAX__];
    int checkCounter=0;
    fgets(separatorCheck,__INT16_MAX__,csvFile);
    fgets(separatorCheck,__INT16_MAX__,csvFile);
    char *separatorControlToken;
    separatorControlToken=strtok(separatorCheck,separator);
    while(separatorControlToken){
        checkCounter=checkCounter+1;
        separatorControlToken=strtok(NULL,separator);
    }
    return checkCounter;
}

//writing information from csv file to xm file
//Reading rhe csv file line by line and writing to the xml file in accordance with the xml file format
char printXmlFile(FILE *xmlFile, FILE *csvFile,char *xmlFileName,char *separator,char endLine,char separator2){
    
    char *xmlFileNameToken=strtok(xmlFileName,".");
    char csvFileLine[__INT16_MAX__];
    char tempColumnName[__INT16_MAX__];
    char columnName[__INT16_MAX__];
    int j=0;
    int z=0;
    int i=0;  
    int rowId=1;

    fprintf(xmlFile,"<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");

    fgets(tempColumnName,__INT16_MAX__,csvFile);
    
    while(tempColumnName[j]!='\r'&&tempColumnName[j]!='\n'){
        if(tempColumnName[j]=='\t'){
            columnName[z]=',';
            z=z+1;
        }
        else if(tempColumnName[j]==' '&&tempColumnName[j-1]!=' '&&tempColumnName[j+1]!=' '){
            columnName[z]='_';
            z=z+1;
        }
        else if(tempColumnName[j]==' '&&tempColumnName[j+1]==' '&&tempColumnName[j-1]!=' '){
            columnName[z]=',';
            z=z+1;
        }
        else if(tempColumnName[j]!=' '){
            columnName[z]=tempColumnName[j];
            z=z+1;
        }      
        j=j+1;
    }
    columnName[z]='\n';
    char split;
    if(separator2!=';'){
        split=',';
    }
    else{
        split=separator2;
    }

    fprintf(xmlFile,"<%s>",xmlFileNameToken);
    while(fgets(csvFileLine,__INT16_MAX__,csvFile)!=NULL){
        int csvFileLineSize=strlen(csvFileLine);
        char newCsvLine[csvFileLineSize];
        controlEmptyAndEndLine(newCsvLine,csvFileLine, separator2, endLine,csvFileLineSize);
        char *csvToken;
        csvToken=strtok(newCsvLine,separator);
        
        int i=0; 
        int j=0;
        fprintf(xmlFile,"\n   <row id= \"%d\">",rowId);
        while(csvToken){
            int t=i;
            fprintf(xmlFile,"\n ");
            fprintf(xmlFile,"      <");
            while(i<strlen(columnName)&&columnName[i]!='\r'&&columnName[i]!='\n'&&columnName[i]!=split){
                fprintf(xmlFile,"%c",tolower(columnName[i]));
                i=i+1;
            }
            i=i+1;
            fprintf(xmlFile,">");
            int a=0;
            while(csvToken[a]!='*')
            {
                if(a==strlen(csvToken))
                    break;
                if(csvToken[0]==' ')
                    break;
                fprintf(xmlFile,"%c",csvToken[a]);
                a=a+1;
            }                        
            i=t;
            fprintf(xmlFile,"</");
            while(i<strlen(columnName)&&columnName[i]!='\r'&&columnName[i]!='\n'&&columnName[i]!=split){
                fprintf(xmlFile,"%c",tolower(columnName[i]));
                i=i+1;
            }
            i=i+1;
            fprintf(xmlFile,">");
            csvToken=strtok(NULL,separator);
        }
        rowId=rowId+1;
        fprintf(xmlFile,"\n   </row>");
    }
    fprintf(xmlFile,"\n<%s>",xmlFileNameToken);
}

//Check of line break character
//Control of places where some information is not available
char controlEmptyAndEndLine(char newCsvLine[__INT16_MAX__],char csvFileLine[],char separator2,char endLine,int csvFileLineSize){
    int i=0;
    int f=0;
    while(csvFileLine[i]!='\n'&&csvFileLine[i]!='\r'&&i<csvFileLineSize){      
       if(i==0&&csvFileLine[0]==separator2){
           newCsvLine[0]=' ';
           newCsvLine[1]=separator2;
           f=2;
        }
        else if(csvFileLine[i]==separator2&&(csvFileLine[i+1]=='\n'||csvFileLine[i+1]=='\r')&&csvFileLine[i-1]!=separator2){
           newCsvLine[f]=separator2;
           f=f+1;
           newCsvLine[f]=' ';
           f=f+1;  
        }
        else if(csvFileLine[i]==separator2&&csvFileLine[i-1]==separator2&&(csvFileLine[i+1]=='\n'||csvFileLine[i+1]=='\r')){
            newCsvLine[f]=' ';
            f=f+1;
            newCsvLine[f]=separator2;
            f=f+1;
            newCsvLine[f]=' ';
            f=f+1;      
        }
       else if(csvFileLine[i]==separator2&&csvFileLine[i-1]==separator2){
           newCsvLine[f]=' ';
           f=f+1;
           newCsvLine[f]=separator2;
           f=f+1;
        }    
       else{
           newCsvLine[f]=csvFileLine[i];
           f=f+1;
        }            
        i=i+1;
    }
    newCsvLine[f]='*';
}