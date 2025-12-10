#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;


typedef struct elmDivisi *adrDivisi;
typedef struct elmPanitia *adrPanitia;
typedef struct elmProject *adrProject;
typedef struct elmRelasi *adrRelasi;

struct divisi {
    string namaDivisi;
    string no;
};

struct panitia {
    string nama;
    string skill;
    string nim;
};

struct project {
    string namaProject;
    string deadline;
};

struct elmDivisi {
    divisi info;
    adrDivisi next;
    adrPanitia firstPanitia;
};

struct elmPanitia {
    panitia info;
    adrPanitia next;
    adrPanitia prev;
    adrRelasi firstProject;
};

struct elmProject {
    project info;
    adrProject next;
};

struct elmRelasi {
    adrProject project;
    adrRelasi next;
    adrRelasi prev;
};

void createListDivisi(adrDivisi &L);
void createListProject(adrProject &L);
adrDivisi newDivisi(divisi x);
adrPanitia newPanitia(panitia x);
adrProject newProject(project x);
adrRelasi newRelasi(adrProject P);
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


#endif // TUBES_H_INCLUDED
