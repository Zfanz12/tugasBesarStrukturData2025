#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

//pointer
typedef struct elmDivisi* adrDivisi;
typedef struct elmPanitia* adrPanitia;
typedef struct elmProject* adrProject;
typedef struct elmRelasi* adrRelasi;

//struct info
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

//node struct
struct elmDivisi {
    divisi info;
    adrDivisi next;           // SLL
    adrPanitia firstPanitia;  // 1-N
};

struct elmPanitia {
    panitia info;
    adrPanitia next;          // DLL
    adrPanitia prev;
    adrRelasi firstProject;   // M-N
};

struct elmProject {
    project info;
    adrProject next;          // SLL
};

struct elmRelasi {
    adrProject project;
    adrRelasi next;           // DLL
    adrRelasi prev;
};

//func
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

void deleteDivisi(adrDivisi &L, string namaDivisi);
void deletePanitia(adrDivisi D, string nim);
void deleteProject(adrProject &L, string namaProject, adrDivisi LDivisi);
void panitiaDoneProject(adrPanitia P, string namaProject);

adrDivisi findDivisi(adrDivisi L, string namaDivisi);
adrPanitia findPanitia(adrDivisi D, string nim);
adrProject findProject(adrProject L, string namaProject);
adrRelasi findRelasi(adrPanitia P, string namaProject);

void printDivisi(adrDivisi L);
void printPanitia(adrPanitia P);
void printPanitiaSimple(adrPanitia P);
void printProject(adrProject L);
void printProjectSimple(adrProject L);
void printProjectWithPanitia(adrProject LProject, adrDivisi LDivisi);

void pauseMenu();
string toLower(string s);
#endif
