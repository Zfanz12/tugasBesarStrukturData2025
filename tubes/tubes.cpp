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
    return P;
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


adrRelasi newRelasi(adrProject Proj) {
    adrRelasi P = new elmRelasi;
    P->project = P;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void insertLastDivisi(adrDivisi &L, adrDivisi P) {
    if (L == nullptr) {
        L = P;
    } else {
        adrDivisi Q = L;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertPanitia(adrDivisi D, adrPanitia P) {
    if (D->firstPanitia == nullptr) {
        D->firstPanitia = P;
    } else {
        adrPanitia Q = D->firstPanitia;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
        P->prev = Q;
    }
}

void insertLastProject(adrProject &L, adrProject P) {
    if (L == nullptr) {
        L = P;
    } else {
        adrProject Q = L;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void assignProject(adrPanitia P, adrProject R) {
    adrRelasi rel = newRelasi(R);
    if (P->firstProject == nullptr) {
        P->firstProject = rel;
    } else {
        adrRelasi Q = P->firstProject;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = rel;
        rel->prev = Q;
    }
}

void deleteDivisi(adrDivisi &L, string nama) {
    adrDivisi P = findDivisi(L, nama);
    if (P == nullptr) {
        cout << "Divisi tidak ditemukan" << endl;
        return;
    }
    
    // Ngehapus semua panitia di divisi spesifik ini
    while (P->firstPanitia != nullptr) {
        adrPanitia temp = P->firstPanitia;
        P->firstPanitia = P->firstPanitia->next;
        
        // Ngehapus semua relasi project
        while (temp->firstProject != nullptr) {
            adrRelasi relTemp = temp->firstProject;
            temp->firstProject = temp->firstProject->next;
            delete relTemp;
        }
        delete temp;
    }

    // Ngehapus divisi dari list
    if (P == L) {
        L = L->next;
    } else {
        adrDivisi Q = L;
        while (Q->next != P) {
            Q = Q->next;
        }
        Q->next = P->next;
    }
    delete P;
}

// DELETE PANITIA SAMPE FIND RELASI BELUM
// BIKIN DISINI XOXOXO

void printDivisi(adrDivisi L) {
    if (L == nullptr) {
        cout << "List divisi kosong" << endl;
        return;
    }
    
    adrDivisi P = L;
    int no = 1;
    while (P != nullptr) {
        cout << no++ << ". Divisi: " << P->info.namaDivisi 
             << " (No: " << P->info.no << ")" << endl;
        
        if (P->firstPanitia != nullptr) {
            cout << "   Panitia:" << endl;
            printPanitia(P->firstPanitia);
        } else {
            cout << "   Belum ada panitia" << endl;
        }
        cout << endl;
        P = P->next;
    }
}

void printPanitia(adrPanitia P) {
    if (P == nullptr) {
        cout << "   List panitia kosong" << endl;
        return;
    }
    
    while (P != nullptr) {
        cout << "   - " << P->info.nama << " (NIM: " << P->info.nim 
             << ", Skill: " << P->info.skill << ")" << endl;
        
        if (P->firstProject != nullptr) {
            cout << "     Project yang dikerjakan:" << endl;
            adrRelasi R = P->firstProject;
            while (R != nullptr) {
                cout << "     * " << R->project->info.namaProject 
                     << " (Deadline: " << R->project->info.deadline << ")" << endl;
                R = R->next;
            }
        }
        P = P->next;
    }
}

void printProject(adrProject L) {
    if (L == nullptr) {
        cout << "List project kosong" << endl;
        return;
    }
    
    adrProject P = L;
    int no = 1;
    while (P != nullptr) {
        cout << no++ << ". Project: " << P->info.namaProject 
             << " (Deadline: " << P->info.deadline << ")" << endl;
        P = P->next;
    }
}

void deletePanitia(adrDivisi D, string nim);
void deleteProject(adrProject &L, string namaProject);
void panitiaDoneProject(adrPanitia P, string namaProject);

adrDivisi findDivisi(adrDivisi L, string namaDivisi) {
    adrDivisi P = L;
    while (P != nullptr) {
        if (P->info.namaDivisi == namaDivisi) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

adrPanitia findPanitia(adrDivisi D, string nim);
adrProject findProject(adrProject L, string namaProject);
adrRelasi findRelasi(adrPanitia P, string namaProject);
