/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Jhenny Cervera Vargas(20182841)
 *
 * Created on 21 de junio de 2020, 21:44
 */

#include <stdio.h>
#include <stdlib.h>
#include"FuncAux.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    char titulo[50], Alumno[50];
    int numLin,numPal,numSin;
    char *palabras[500],*sinonimo[500];
    
    GuadarArchiPal(palabras,&numPal);
    GuadarSinonimo(sinonimo,&numSin);
    LeerEImprCuento( titulo, Alumno,palabras,numPal,sinonimo, numSin);

    return (EXIT_SUCCESS);
}

