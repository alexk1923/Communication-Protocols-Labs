#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct frame{
    char *info;
    int secv;
    int conf;
}frame;

void printFrame(frame fr) {
    printf("---------------------\n");
    printf("Info: %s\n", fr.info);
    printf("Nr secventa: %d\n", fr.secv);
    printf("Nr confirmare: %d\n", fr.conf);
    printf("---------------------\n");
}

void LaRetea(frame fr) {
    printf("LaRetea: Leg de date => Retea\n");
    printFrame(fr);
}

void LaFizic(frame fr) {
    printf("LaFizic: Leg de date => fizic\n");
    printFrame(fr);
}

void DeLaFizic(frame fr) {
    printf(" DeLaFizic: Fizic => Leg de date\n");
    printFrame(fr);
}

void DeLaRetea(frame fr) {
    printf("DeLaRetea : Retea => Leg de date");
    printFrame(fr);
}

void StartCeas() {
    printf("Starting Timer...\n");
}

void StopCeas() {
    printf("STOP TIMER !\n");
}

void prot(char *even, char infos[3][30], int inf_dim) {
    printf("Se pregateste un cadru\n");
    int cadruUrmator = 0;
    int cadruAsteptat = 0;
    frame newFrame;
    newFrame.info = strdup(infos[inf_dim++]);
    newFrame.secv = cadruUrmator;
    newFrame.conf = 1 - cadruAsteptat;
    LaFizic(newFrame);

    StartCeas();
    int step = 0;

    do {
        step++;
        if(strcmp(even, "SosireCadru") == 0) {
            DeLaFizic(newFrame);

            // daca receptorul primeste
            if(newFrame.secv == cadruAsteptat) {
                printf("Numar de secventa corect\n");
                printf("Deci se trimite mai departe la retea");
                LaRetea(newFrame);
                cadruAsteptat++;
            }

            // daca transmitatorul primeste
            if(newFrame.conf == cadruUrmator) {
                printf("Numar de confirmare corect");
                StopCeas();
                printf("GET NEW PACKAGE de la Retea\n");

                newFrame.info = strdup(infos[inf_dim++]);
                DeLaRetea(newFrame);
                cadruUrmator++;
            }

            // construieste si transmite un nou cadru
            newFrame.secv = cadruUrmator;
            newFrame.conf = 1 - cadruAsteptat;
            LaFizic(newFrame);
            StartCeas();
        }

    }while(step < 15);
}

int main() {
    printf("Please choose operation\n");
    char infos[3][30] = {"String1", "String2", "String3"};
    prot("SosireCadru", infos, 0);
}