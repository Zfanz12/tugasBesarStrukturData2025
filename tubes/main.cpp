#include <iostream>
#include "tubes.h"
using namespace std;

void pauseMenu() {
    cout << "\nTekan ENTER untuk kembali ke menu utama...";
    cin.get();
}

int main() {
    adrDivisi listDivisi;
    adrProject listProject;

    createListDivisi(listDivisi);
    createListProject(listProject);

    int pilihan;
    do {
        cout << "\n===== SIMULATOR ORGANISASI =====\n\n";
        cout << "===== Tambah =====\n";
        cout << "1. Tambah Divisi\n";
        cout << "2. Tambah Panitia ke Divisi\n";
        cout << "3. Tambah Project\n";
        cout << "\n===== Manage Kepanitiaan =====\n";
        cout << "4. Assign Panitia ke Project\n";
        cout << "5. Panitia Selesai Project\n";
        cout << "6. Hapus Panitia\n";
        cout << "7. Hapus Project\n";
        cout << "\n===== Lihat Info =====\n";
        cout << "8. Daftar Seluruh Panitia\n";
        cout << "9. Daftar Divisi & Anggota\n";
        cout << "10. Daftar Project & Staff\n";
        cout << "11. Tampilkan Semua Data\n";
        cout << "0. Keluar\n";
        cout << "\nPilih menu: ";
        cin >> pilihan;
        cin.ignore();

        // ================== TAMBAH DIVISI ==================
        if (pilihan == 1) {
            divisi d;
            cout << "Nama divisi: ";
            getline(cin, d.namaDivisi);

            adrDivisi D = newDivisi(d);
            insertLastDivisi(listDivisi, D);

            cout << "\nDivisi \"" << d.namaDivisi << "\" berhasil ditambahkan.\n";
            pauseMenu();
        }

        // ================== TAMBAH PANITIA ==================
        else if (pilihan == 2) {
            if (listDivisi == nullptr) {
                cout << "Belum ada divisi.\n";
                pauseMenu();
                continue;
            }

            panitia p;
            cout << "Nama panitia: ";
            getline(cin, p.nama);
            cout << "NIM: ";
            getline(cin, p.nim);
            cout << "Skill: ";
            getline(cin, p.skill);

            cout << "\nDaftar Divisi:\n";
            adrDivisi temp = listDivisi;
            while (temp != nullptr) {
                cout << "- " << temp->info.namaDivisi << endl;
                temp = temp->next;
            }

            string namaDivisi;
            cout << "\nMasukkan nama divisi: ";
            getline(cin, namaDivisi);

            adrDivisi D = findDivisi(listDivisi, namaDivisi);
            if (D == nullptr) {
                cout << "Divisi tidak ditemukan.\n";
                pauseMenu();
                continue;
            }

            adrPanitia P = newPanitia(p);
            insertPanitia(D, P);

            cout << "\nPanitia \"" << p.nama
                 << "\" berhasil ditambahkan ke divisi "
                 << namaDivisi << ".\n";
            pauseMenu();
        }

        // ================== TAMBAH PROJECT ==================
        else if (pilihan == 3) {
            project p;
            cout << "Nama project: ";
            getline(cin, p.namaProject);
            cout << "Deadline: ";
            getline(cin, p.deadline);

            adrProject P = newProject(p);
            insertLastProject(listProject, P);

            cout << "\nProject \"" << p.namaProject << "\" berhasil ditambahkan.\n";
            pauseMenu();
        }

        // ================== ASSIGN PROJECT ==================
        if (pilihan == 4) {
            if (listProject == nullptr) {
                cout << "Belum ada project.\n";
                pauseMenu();
                continue;
            }

            cout << "\nDaftar Project:\n";
            printProjectSimple(listProject);

            string namaProject;
            cout << "\nMasukkan nama project: ";
            getline(cin, namaProject);

            adrProject Proj = findProject(listProject, namaProject);
            if (Proj == nullptr) {
                cout << "Project tidak ditemukan.\n";
                pauseMenu();
                continue;
            }

            cout << "\nDaftar Divisi:\n";
            adrDivisi D = listDivisi;
            while (D != nullptr) {
                cout << "- " << D->info.namaDivisi << endl;
                D = D->next;
            }

            string namaDivisi;
            cout << "\nMasukkan nama divisi: ";
            getline(cin, namaDivisi);

            adrDivisi Div = findDivisi(listDivisi, namaDivisi);
            if (Div == nullptr || Div->firstPanitia == nullptr) {
                cout << "Divisi tidak ditemukan / belum ada panitia.\n";
                pauseMenu();
                continue;
            }

            cout << "\nDaftar Panitia:\n";
            printPanitiaSimple(Div->firstPanitia);

            string nim;
            cout << "\nMasukkan NIM panitia: ";
            getline(cin, nim);

            adrPanitia Pan = findPanitia(Div, nim);
            if (Pan == nullptr) {
                cout << "Panitia tidak ditemukan.\n";
                pauseMenu();
                continue;
            }

            // CEK SUDAH ADA DI PROJECT ATAU BELUM
            if (findRelasi(Pan, namaProject) != nullptr) {
                cout << "\nPanitia sudah terdaftar di project ini.\n";
                pauseMenu();
                continue;
            }

            assignProject(Pan, Proj);
            cout << "\nPanitia \"" << Pan->info.nama
                 << "\" (" << Div->info.namaDivisi
                 << ") berhasil menjadi staff project \""
                 << namaProject << "\".\n";
            pauseMenu();
        }

        // ================== PANITIA SELESAI PROJECT ==================
        else if (pilihan == 5) {
            if (listProject == nullptr) {
                cout << "Belum ada project.\n";
                pauseMenu();
                continue;
            }

            cout << "\nDaftar Project:\n";
            printProjectSimple(listProject);

            string namaProject;
            cout << "\nMasukkan nama project: ";
            getline(cin, namaProject);

            adrProject Proj = findProject(listProject, namaProject);
            if (Proj == nullptr) {
                cout << "Project tidak ditemukan.\n";
                pauseMenu();
                continue;
            }

            cout << "\nDaftar Divisi & Panitia:\n";
            printDivisi(listDivisi);

            string namaDivisi;
            cout << "\nMasukkan nama divisi: ";
            getline(cin, namaDivisi);

            adrDivisi Div = findDivisi(listDivisi, namaDivisi);
            if (Div == nullptr) {
                cout << "Divisi tidak ditemukan.\n";
                pauseMenu();
                continue;
            }

            cout << "\nDaftar Panitia:\n";
            printPanitiaSimple(Div->firstPanitia);

            string nim;
            cout << "\nMasukkan NIM panitia: ";
            getline(cin, nim);

            adrPanitia Pan = findPanitia(Div, nim);
            if (Pan == nullptr) {
                cout << "Panitia tidak ditemukan.\n";
                pauseMenu();
                continue;
            }

            panitiaDoneProject(Pan, namaProject);
            cout << "\nPanitia \"" << Pan->info.nama
                 << "\" selesai mengerjakan project \""
                 << namaProject << "\".\n";
            pauseMenu();
        }
        // ================== HAPUS PANITIA ==================
         if (pilihan == 6) {
            if (listDivisi == nullptr) {
                cout << "Belum ada divisi.\n";
                pauseMenu();
                continue;
            }

            cout << "\n=== DAFTAR SELURUH PANITIA ===\n";
            adrDivisi D = listDivisi;
            while (D != nullptr) {
                adrPanitia P = D->firstPanitia;
                while (P != nullptr) {
                    cout << "- " << P->info.nama
                         << " (" << P->info.nim << ")"
                         << " [" << D->info.namaDivisi << "]\n";
                    P = P->next;
                }
                D = D->next;
            }

            string nim;
            cout << "\nMasukkan NIM panitia yang akan dihapus: ";
            getline(cin, nim);

            bool ketemu = false;
            D = listDivisi;
            while (D != nullptr && !ketemu) {
                adrPanitia P = findPanitia(D, nim);
                if (P != nullptr) {
                    deletePanitia(D, nim);
                    cout << "\nPanitia dengan NIM " << nim
                         << " berhasil dihapus dari divisi "
                         << D->info.namaDivisi << ".\n";
                    ketemu = true;
                }
                D = D->next;
            }

            if (!ketemu) {
                cout << "\nPanitia dengan NIM tersebut tidak ditemukan.\n";
            }

            pauseMenu();
        }


        // ================== HAPUS PROJECT ==================
else if (pilihan == 7) {
    if (listProject == nullptr) {
        cout << "Belum ada project.\n";
        pauseMenu();
        continue;
    }

    cout << "\nDaftar Project:\n";
    printProjectSimple(listProject);

    string namaProject;
    cout << "\nMasukkan nama project yang ingin dihapus: ";
    getline(cin, namaProject);

    deleteProject(listProject, namaProject, listDivisi);
    cout << "\nProject \"" << namaProject << "\" berhasil dihapus.\n";
    pauseMenu();
}
        // ================== LIHAT INFO ==================
        else if (pilihan == 8) {
            cout << "\n=== DAFTAR SELURUH PANITIA ===\n";
            adrDivisi D = listDivisi;
            while (D != nullptr) {
                printPanitiaSimple(D->firstPanitia);
                D = D->next;
            }
            pauseMenu();
        }

        else if (pilihan == 9) {
            cout << "\n=== DAFTAR DIVISI & ANGGOTA ===\n";
            printDivisi(listDivisi);
            pauseMenu();
        }

        else if (pilihan == 10) {
            cout << "\n=== DAFTAR PROJECT & STAFF ===\n";
            printProjectWithPanitia(listProject, listDivisi);
            pauseMenu();
        }

        else if (pilihan == 11) {
            cout << "\n=== DATA DIVISI ===\n";
            printDivisi(listDivisi);

            cout << "\n=== DATA PROJECT ===\n";
            printProjectWithPanitia(listProject, listDivisi);
            pauseMenu();
        }

    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}
