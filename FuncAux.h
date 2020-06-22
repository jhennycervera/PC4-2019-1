/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAux.h
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 21 de junio de 2020, 22:24
 */

#ifndef FUNCAUX_H
#define FUNCAUX_H
void GuadarArchiPal(char **,int*);
void GuadarSinonimo(char **,int*);
FILE* AbrirArch(char* , char* );
void leerCadena(char * ,int , FILE*);
int verificarEnPalArch(char* ,char** , int );
char* leerCadenaExacta(FILE*);
void LeerEImprCuento(char* ,char*,char**,int , char** ,int );
void CorregirLinYguardarPalindromos(char * ,char* , char* ,char**,int ,char**,int , int*, int*);
int EsPalindroma(char *);
void invertir(char *);
int BuscarPosPalabraArch(char* ,char** , int );



#endif /* FUNCAUX_H */

