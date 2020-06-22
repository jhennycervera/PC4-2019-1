/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//Author: Jhenny Cervera Vargas(20182841)     

#include <stdio.h>
#include <stdlib.h>
#include "FuncAux.h"
#include <string.h>

void GuadarArchiPal(char **palabras,int*numPal){
    FILE*arch;
    arch=AbrirArch("palabras.txt", "r");
    *numPal=0;
    char  *pt;
    while(1){
        pt=leerCadenaExacta(arch);   //retorna la Dm del arreglo dinamico que contiene la cadena, sino retorna NULL
        if(pt==NULL) break;
        palabras[*numPal]=pt;
        (*numPal)++;
    }
    fclose(arch);
}

char* leerCadenaExacta(FILE*arch){
    char buff[50],*pt;             //lee la palabra --- 50 es la cantidad max de letras que se va almacenar por la plabra 
    int lon;
    leerCadena(buff,50,arch);
    if(feof(arch)) return NULL;     //si leo la cadena y no hay nada retorno null
    lon=strlen(buff);
    pt=(char*)malloc(sizeof(char)*(lon+1));
    strcpy(pt, buff);
    return pt;
}

FILE* AbrirArch(char* nombre, char* modo){
    FILE*arch;
    arch=fopen(nombre,modo);
    if(arch==NULL){
        printf("ERROR, no se pude abrir el archivo %s", nombre);
        exit(1);
    }
    return arch;
}

void leerCadena(char * cad,int tope, FILE* arch){
    int lon;
    fgets(cad,tope,arch);
    lon=strlen(cad);
    cad[lon-1]=0;
}

void GuadarSinonimo(char **sinonimo,int*numSin){
    FILE*arch;
    arch=AbrirArch("sinonimos.txt", "r");
    *numSin=0;
    char *pt;
    while(1){
        pt=leerCadenaExacta(arch);
        if(pt==NULL) break;
        sinonimo[*numSin]=pt;
        (*numSin)++;
    }
    fclose(arch);
}     //no hacer free perderiamos lo que contiene sinonimo que esta apuntando al arrglo dinamico

void LeerEImprCuento(char* titulo,char* Alumno,char**palabras,
        int numPal, char** sinonimo,int numSin){
    FILE*arch;
    arch=AbrirArch("cuento.txt", "r");
    
    leerCadena(Alumno,500,arch);
    leerCadena(titulo,500,arch);
    fprintf(stdout, "El nombre del alumno es:%s\nEl nombre del cuento es:%s\n\n", Alumno,titulo);
    
    char linea[150], lineaCorregida[150], palindromas[100]={};    //palabras es por cada linea
    int contPal, arrContSinonimoEnc[500]={0}, contOrac=0;
    int i=0, pos;
    while(1){
        leerCadena(linea,150,arch);
        if(feof(arch)) break;
        CorregirLinYguardarPalindromos(linea,lineaCorregida,palindromas,palabras,
                                        numPal,sinonimo,numSin,arrContSinonimoEnc,&contOrac);
        
        printf("%s\n",lineaCorregida);
    }
    printf("%d\n\n",contOrac );
    for(int i=0; i<numPal; i++){
        printf("%s - %d\n", palabras[i],arrContSinonimoEnc[i]); 
    }
    printf("PALABRAS PALINDROMAS\n");
    printf("%s\n",palindromas);
    fclose(arch);
}

void CorregirLinYguardarPalindromos(char * linea,char* lineaCorregida, 
        char* palindromas,char**palabras,int numPal,char**sinonimo,int numSin,
                                  int* arrContSinonimoEnc, int* contOrac){
    
    int i=0, c, tam, pos, lonPalin, longPal;
    char palabra[50], palabraMinus[50];
    lineaCorregida[0]=0; //al momento de concat le da la dm de la pos=strlen(lineaCoregida)=0 de lineaCorregida y le copia la otra cad
    while(1){
        if(linea[i]==' ' || linea[i]==',' || linea[i]==';' || linea[i]=='.' 
                || linea[i]=='?' || linea[i]=='¿'){
            
            tam=strlen(lineaCorregida);
            lineaCorregida[tam]=linea[i]; //si no es una palabra le concateno o pongo en la ultima pos
            lineaCorregida[tam+1]=0;
            if(linea[i]=='.') (*contOrac)++;
            i++;
        }
        if(linea[i]==0) return;                            //no es break, ya que solo saldria 
        c=0;
        while(linea[i]!=' ' && linea[i]!=',' && linea[i]!=';' && linea[i]!='.' && linea[i]!='?' && linea[i]!='¿' &&  linea[i]!=0){
            palabra[c]=linea[i];
            c++;
            i++;
        }
        palabra[c]=0;
        strcpy(palabraMinus,palabra);
        for(int i=0; palabra[i]; i++)
            palabraMinus[i]+=(( palabraMinus[i]>='A' && palabraMinus[i]<='Z') ? 'a'-'A' : 0);
        //verificando si es palindroma y guardando
        longPal=strlen(palabra);
        if(longPal>1){
            if(EsPalindroma(palabraMinus)){  // la palabra a no es palindroma entonces tengo que verificar si tiene mas de dos letras
                strcat(palindromas,palabra);
                strcat(palindromas," ");
            }
        }
        
        //verificar palabra en arch y sinonimo    
        pos=BuscarPosPalabraArch(palabraMinus,palabras,numPal);
        if(pos!=-1){
            strcat(lineaCorregida,sinonimo[pos]);
            arrContSinonimoEnc[pos]++;
        }
        else 
            strcat(lineaCorregida,palabra);
    }   
}

int EsPalindroma(char *palabraM){
    char aux[50];
    strcpy(aux, palabraM);
    invertir(aux);
    if(strcmp(aux,palabraM)==0){
        return 1;
    }
    else return 0;
}

void invertir(char *aux){
    int lon;
    char invertido[50];
    lon=strlen(aux);
    for(int i=0, k=lon-1; aux[i]; i++, k--){
        invertido[i]=aux[k];
    }
    invertido[lon]=0;
    strcpy(aux, invertido);
}

int BuscarPosPalabraArch(char* palabra,char** palabras, int numPal){
    for(int i=0; i<numPal; i++)
        if(strcmp(palabra,palabras[i])==0){
            return i;
        }
    return -1;
}

