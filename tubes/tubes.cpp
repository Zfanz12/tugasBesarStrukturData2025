#include "tubes.h"

void createListDivisi(adrDivisi &L) {
    createListDivisi(L);
    L = nullptr;
}
void createListProject(adrProject &L) {
    createListProject(L);
    L =nullptr;
}

adrDivisi newDivisi(divisi x) {
    adrDivisi P = new elmDivisi;
    P->info = x;
    P->next= nullptr;
    P->firstPanitia = nullptr;
    return P'
}

adrPanitia newPanitia(panitia x) {
    adrPanitia P = new elmPanitia;
    P->info = x;
    P->next = nullptr;
    P->prev = nullptr;
    P->firstProject = nullptr;
    return P;

}
adrProject newProject(project x) {
    adrProject P = new elmProject;
    P->info = x;
    P->next = nullptr;
    return P;
}

adrRelasi newRelasi(adrProject P) {
    adrRelasi P = new elmRelasi;
    P->project = P;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void insertLastDivisi(adrDivisi &L, adrDivisi P);
void insertPanitia(adrDivisi D, adrPanitia P);
void insertLastProject(adrProject &L, adrProject P);
void assignProject(adrPanitia P, adrProject R);
void deleteDivisi(adrDivisi &L, string nama);
void deletePanitia(adrDivisi D, string nim);
void deleteProject(adrProject &L, string namaProject);
void panitiaDoneProject(adrPanitia P, string namaProject);
adrDivisi findDivisi(adrDivisi L, string namaDivisi);
adrPanitia findPanitia(adrDivisi D, string nim);
adrProject findProject(adrProject L, string namaProject);
adrRelasi findRelasi(adrPanitia P, string namaProject);
void printDivisi(adrDivisi L);
void printPanitia(adrPanitia P);
void printProject(adrProject L);
