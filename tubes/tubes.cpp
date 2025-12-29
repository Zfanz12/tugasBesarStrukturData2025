#include "tubes.h"
#include <algorithm>

// ===== helper =====
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

//create logic
void createListDivisi(adrDivisi &L) {
    L = nullptr;
}

void createListProject(adrProject &L) {
    L = nullptr;
}

//create new elm/node
adrDivisi newDivisi(divisi x) {
    adrDivisi P = new elmDivisi;
    P->info = x;
    P->next = nullptr;
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

adrRelasi newRelasi(adrProject Proj) {
    adrRelasi P = new elmRelasi;
    P->project = Proj;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

//Insert logic
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

// ===== FIND (CASE INSENSITIVE) =====
adrDivisi findDivisi(adrDivisi L, string namaDivisi) {
    string key = toLower(namaDivisi);
    while (L != nullptr) {
        if (toLower(L->info.namaDivisi) == key)
            return L;
        L = L->next;
    }
    return nullptr;
}

adrPanitia findPanitia(adrDivisi D, string nim) {
    adrPanitia P = D->firstPanitia;
    while (P != nullptr) {
        if (P->info.nim == nim)
            return P;
        P = P->next;
    }
    return nullptr;
}

adrProject findProject(adrProject L, string namaProject) {
    string key = toLower(namaProject);
    while (L != nullptr) {
        if (toLower(L->info.namaProject) == key)
            return L;
        L = L->next;
    }
    return nullptr;
}

adrRelasi findRelasi(adrPanitia P, string namaProject) {
    string key = toLower(namaProject);
    adrRelasi R = P->firstProject;
    while (R != nullptr) {
        if (toLower(R->project->info.namaProject) == key)
            return R;
        R = R->next;
    }
    return nullptr;
}

//delete logic
void deleteDivisi(adrDivisi &L, string namaDivisi) {
    adrDivisi P = findDivisi(L, namaDivisi);
    if (P == nullptr) return;

    while (P->firstPanitia != nullptr) {
        adrPanitia temp = P->firstPanitia;
        P->firstPanitia = temp->next;

        while (temp->firstProject != nullptr) {
            adrRelasi r = temp->firstProject;
            temp->firstProject = r->next;
            delete r;
        }
        delete temp;
    }

    if (P == L) {
        L = L->next;
    } else {
        adrDivisi Q = L;
        while (Q->next != P) Q = Q->next;
        Q->next = P->next;
    }
    delete P;
}

void deletePanitia(adrDivisi D, string nim) {
    adrPanitia P = findPanitia(D, nim);
    if (P == nullptr) return;

    if (P == D->firstPanitia) {
        D->firstPanitia = P->next;
        if (P->next) P->next->prev = nullptr;
    } else {
        P->prev->next = P->next;
        if (P->next) P->next->prev = P->prev;
    }

    while (P->firstProject != nullptr) {
        adrRelasi r = P->firstProject;
        P->firstProject = r->next;
        delete r;
    }
    delete P;
}

void deleteProject(adrProject &L, string namaProject, adrDivisi LDivisi) {
    adrProject P = L, prev = nullptr;

    // cari project
    while (P != nullptr && P->info.namaProject != namaProject) {
        prev = P;
        P = P->next;
    }
    if (P == nullptr) return;

    // ===== HAPUS SEMUA RELASI KE PROJECT INI =====
    adrDivisi D = LDivisi;
    while (D != nullptr) {
        adrPanitia Pan = D->firstPanitia;
        while (Pan != nullptr) {
            adrRelasi R = Pan->firstProject;
            while (R != nullptr) {
                adrRelasi nextR = R->next;
                if (R->project == P) {
                    // hapus relasi
                    if (R == Pan->firstProject) {
                        Pan->firstProject = R->next;
                        if (R->next) R->next->prev = nullptr;
                    } else {
                        R->prev->next = R->next;
                        if (R->next) R->next->prev = R->prev;
                    }
                    delete R;
                }
                R = nextR;
            }
            Pan = Pan->next;
        }
        D = D->next;
    }

    // ===== HAPUS PROJECT DARI LIST =====
    if (P == L) {
        L = P->next;
    } else {
        prev->next = P->next;
    }

    delete P;
}


void panitiaDoneProject(adrPanitia P, string namaProject) {
    adrRelasi R = findRelasi(P, namaProject);
    if (R == nullptr) return;

    if (R == P->firstProject) {
        P->firstProject = R->next;
        if (R->next) R->next->prev = nullptr;
    } else {
        R->prev->next = R->next;
        if (R->next) R->next->prev = R->prev;
    }
    delete R;
}

// ===== PRINT =====
void printDivisi(adrDivisi L) {
    while (L != nullptr) {
        cout << "Divisi: " << L->info.namaDivisi << endl;
        printPanitia(L->firstPanitia);
        cout << endl; // <-- BARIS KOSONG (FIX NOMOR 2)
        L = L->next;
    }
}

void printPanitia(adrPanitia P) {
    while (P != nullptr) {
        cout << " - " << P->info.nama << endl;
        adrRelasi R = P->firstProject;
        while (R != nullptr) {
            cout << "    * " << R->project->info.namaProject << endl;
            R = R->next;
        }
        P = P->next;
    }
}

void printPanitiaSimple(adrPanitia P) {
    int i = 1;
    while (P != nullptr) {
        cout << i++ << ". "
             << P->info.nama
             << " (" << P->info.nim << ")" << endl;
        P = P->next;
    }
}

void printProjectSimple(adrProject L) {
    while (L != nullptr) {
        cout << "- " << L->info.namaProject << endl;
        L = L->next;
    }
}

void printProjectWithPanitia(adrProject LProject, adrDivisi LDivisi) {
    if (LProject == nullptr) {
        cout << "Tidak ada project\n";
        return;
    }

    adrProject P = LProject;
    while (P != nullptr) {
        cout << P->info.namaProject;

        int count = 0;
        adrDivisi D = LDivisi;
        while (D != nullptr) {
            adrPanitia Pan = D->firstPanitia;
            while (Pan != nullptr) {
                adrRelasi R = Pan->firstProject;
                while (R != nullptr) {
                    if (R->project == P) count++;
                    R = R->next;
                }
                Pan = Pan->next;
            }
            D = D->next;
        }

        cout << " (" << count << " Staff)" << endl;

        D = LDivisi;
        while (D != nullptr) {
            adrPanitia Pan = D->firstPanitia;
            while (Pan != nullptr) {
                adrRelasi R = Pan->firstProject;
                while (R != nullptr) {
                    if (R->project == P) {
                        cout << " * " << Pan->info.nama
                             << " - " << D->info.namaDivisi << endl;
                    }
                    R = R->next;
                }
                Pan = Pan->next;
            }
            D = D->next;
        }

        cout << endl;
        P = P->next;
    }
}
