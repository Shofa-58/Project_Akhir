#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

struct Menu_Restoran
{
    int ID;
    char nama[30];
    char kategori[20];
    int harga;
};

struct Node
{
    Menu_Restoran data;
    Node *next;
};

Node *head = nullptr;
int pilihmenu;
char menu_kembali;
int jumlah_data_diinput;
bool found;

Node *buatNode(const Menu_Restoran &r)
{
    Node *temp = new Node;
    temp->data = r;
    temp->next = nullptr;
    return temp;
}

void loadData()
{
    FILE *f = fopen("datarestoran.txt", "r");
    if (!f)
        return;

    Menu_Restoran tempstruct;
    while (fscanf(f, "%d|%29[^|]|%19[^|]|%d\n",
                  &tempstruct.ID, tempstruct.nama, tempstruct.kategori, &tempstruct.harga) == 4)
    {
        Node *temp = buatNode(tempstruct);
        if (!head)
        {
            head = temp;
        }
        else
        {
            Node *t = head;
            while (t->next)
                t = t->next;
            t->next = temp;
        }
    }
    fclose(f);
}

void Input_Data()
{
    FILE *f = fopen("datarestoran.txt", "a");
    if (!f)
    {
        cout << "Gagal buka datarestoran.txt untuk append"<<endl;
        return;
    }

    cout << "Ingin berapa kali input? ";
    cin >> jumlah_data_diinput;
    cin.ignore();

    for (int i = 1; i <= jumlah_data_diinput; ++i)
    {
        Menu_Restoran tempstruct;
        cout << "\n--- INPUT DATA KE-" << i << " ---\n"<<endl;
        cout << "ID       : ";
        cin >> tempstruct.ID;
        cin.ignore();
        cout << "Nama     : ";
        cin.getline(tempstruct.nama, 30);
        cout << "Kategori : ";
        cin.getline(tempstruct.kategori, 20);
        cout << "Harga    : ";
        cin >> tempstruct.harga;
        cin.ignore();

        fprintf(f, "%d|%s|%s|%d\n",
                tempstruct.ID, tempstruct.nama, tempstruct.kategori, tempstruct.harga);

        Node *temp = buatNode(tempstruct);
        temp->next = head;
        head = temp;

        cout << "Data ke-" << i << " berhasil ditambahkan"<<endl;
    }
    fclose(f);
}

void Output_Data()
{
    if (!head)
    {
        cout << "\nData kosong.\n";
        return;
    }
    cout << "\n====== DAFTAR MENU ======\n";
    cout << left
         << setw(5) << "ID" << "|"
         << setw(30) << "Nama" << "|"
         << setw(20) << "Kategori" << "|"
         << setw(10) << "Harga" << "|\n";

    Node* New = head;
    while(New)
    {
        cout << left
             << setw(5) << New->data.ID << "|"
             << setw(30) << New->data.nama << "|"
             << setw(20) << New->data.kategori << "|"
             << setw(10) << New->data.harga << "|\n";
             New = New->next;
    }
    
}

void Cari_Data()
{
    if (!head)
    {
        cout << "\nData kosong."<<endl;
        return;
    }
    int IDcari;
    cout << "\nMasukkan ID yang dicari: ";
    cin >> IDcari;
    found = false;

    Node *temp = head;
    found = false;

    while (temp)
    {
        if (temp->data.ID == IDcari)
        {
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (found)
    {
        cout << "\nData ditemukan:\n"
             << "ID       : " << temp->data.ID << "\n"
             << "Nama     : " << temp->data.nama << "\n"
             << "Kategori : " << temp->data.kategori << "\n"
             << "Harga    : " << temp->data.harga << "\n";
    }
    else
    {
        cout << "\nData dengan ID " << IDcari << " tidak ditemukan"<<endl;
    }
}


void Urut_Data()
{
    if (!head || !head->next)
    {
        cout << "\nData tidak cukup untuk diurutkan.\n";
        return;
    }

    Node *temp = head;
    int index = 0;

    Node *data[100]; // buat array baru untuk menyalin dari index, index bertujuan sebagai patokan total data index
    while (temp != nullptr && index < 100)
    {
        data[index] = temp;
        temp = temp->next;
        index++;
    }

    for (int i = 0; i < index - 1; i++)
    {
        for (int j = 0; j < index - 1 - i; j++)
        {
            if (data[j]->data.ID > data[j + 1]->data.ID)
            {
                swap(data[j]->data, data[j + 1]->data);
            }
        }
    }
    FILE *f = fopen("datarestoran.txt", "w");
Node* New = head;
while (New) {
    fprintf(f, "%d|%s|%s|%d\n",
            New->data.ID,
            New->data.nama,
            New->data.kategori,
            New->data.harga);
    New = New->next;
}

fclose(f);

    Output_Data();
    
    cout << "\nData berhasil diurutkan dan disimpan ulang"<<endl;
}

void Edit_Data()
{
    if (!head)
    {
        cout << "\nData kosong. Tidak ada yang bisa diedit"<<endl;
        return;
    }

    int IDedit;
    cout << "\nMasukkan ID yang ingin diedit: ";
    cin >> IDedit;
    cin.ignore();

    Node *temp = head;
    found = false;

    while (temp)
    {
        if (temp->data.ID == IDedit)
        {
            cout << "\nData ditemukan. Masukkan data baru:"<<endl;
            cout << "ID baru       : ";
            cin >> temp->data.ID;
            cin.ignore();
            cout << "Nama baru     : ";
            cin.getline(temp->data.nama, 30);
            cout << "Kategori baru : ";
            cin.getline(temp->data.kategori, 20);
            cout << "Harga baru    : ";
            cin >> temp->data.harga;
            cin.ignore();

            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "\nData dengan ID " << IDedit << " tidak ditemukan"<<endl;
        return;
    }
    FILE *f = fopen("datarestoran.txt", "w");
    if (!f)
    {
        cout << "Gagal membuka file untuk menyimpan perubahan"<<endl;
        return;
    }

Node* New = head;
while (New) {
    fprintf(f, "%d|%s|%s|%d\n",
            New->data.ID,
            New->data.nama,
            New->data.kategori,
            New->data.harga);
    New = New->next;
}
fclose(f);
}

void Hapus_Data()
{
    if (!head)
    {
        cout << "\nData kosong. Tidak ada yang bisa dihapus"<<endl;
        return;
    }

int IDcari;
cout << "\nMasukkan ID yang ingin dihapus: ";
cin >> IDcari;


if (head->data.ID == IDcari) {//jika node head yang ingin dihapus
    Node* hapus = head;
    head = head->next;
    delete hapus;
    found = true;
} else {//jika node lain
    Node* temp = head;
    while (temp->next) {
        if (temp->next->data.ID == IDcari) {
            Node* hapus = temp->next;
            temp->next = temp->next->next;
            delete hapus;
            found = true;
            break;
        }
        temp = temp->next;
    }
}

if (found) {
    cout << "Data dengan ID " << IDcari << " berhasil dihapus dari memori"<<endl;

    FILE* f = fopen("datarestoran.txt", "w");
    Node* New = head;
    while (New) {
        fprintf(f, "%d|%s|%s|%d\n",
            New->data.ID,
            New->data.nama,
            New->data.kategori,
            New->data.harga);
        New = New->next;
    }
    fclose(f);
    cout << "File berhasil diperbarui setelah penghapusan"<<endl;
} else {
    cout << "\nData dengan ID " << IDcari << " tidak ditemukan"<<endl;
}
}

int main()
{
    loadData();

    do
    {
        cout << "\nMENU PILIHAN:\n"
             << "1. Input Data Item\n"
             << "2. Tampilkan Data Item\n"
             << "3. Mencari Data\n"
             << "4. Mengurutkan Data Item\n"
             << "5. Mengedit Data Item\n"
             << "6. Hapus Data Item\n"
             << "7. Keluar\n"
             << "Pilih [1-7]: ";
        cin >> pilihmenu;
        cin.ignore();

        switch (pilihmenu)
        {
        case 1:
        {
            Input_Data();
            break;
        }
        case 2:
        {
            Output_Data();
            break;
        }
        case 3:
        {
            Cari_Data();
            break;
        }
        case 4:
        {
            Urut_Data();
            break;
        }
        case 5:
        {
            Edit_Data();
            break;
        }
        case 6:
        {
            Hapus_Data();
            break;
        }
        case 7:
        {
            cout << "\nTerima kasih!\n";
            exit(0);
            break;
        }
        default:
            cout << "\nPilihan tidak valid"<<endl;
        }

        cout << "\nKembali ke menu? (y/n): ";
        cin >> menu_kembali;
        cin.ignore();
    } while (menu_kembali == 'y' || menu_kembali == 'Y');

    return 0;
}
