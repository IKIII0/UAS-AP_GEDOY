#include <iostream> //header untuk cipupus/cpp
#include <vector> //header untuk vector
#include <chrono> //header untuk waktu
#include <iomanip> //header untuk manipulasi output
#include <cmath> //header untuk fungsi matematika

using namespace std; //untuk tidak perlu menggunakan std berulang
using namespace chrono; //untuk fungsi waktu 

vector<string> merk_kendaraan; // vector untuk merk kendaraan 
vector<string> plat_kendaraan; // vector untuk plat kendaraan
vector<string> warna_kendaraan; // vector untuk warna kendaraan
vector<system_clock::time_point> waktu_kendaraan; // vector untuk fungsi waktu ketika kendaraan pertama kali diinput

// class kendaraan
class kendaraan{
public:
    string plat;
    string merk;
    string warna;
};

// struct nama petugas
struct petugas{
    string nama;
    string id;
};

// fungsi untuk menambah kendaraan
void tambah_kendaraan(string merk, string plat, string warna){
    //push_back untuk menambah sesuatu ke vector yang diinginkan
    merk_kendaraan.push_back(merk); 
    plat_kendaraan.push_back(plat);
    warna_kendaraan.push_back(warna);
    waktu_kendaraan.push_back(system_clock::now());
}

//fungsi untuk hiasan
void hiasan(){
    cout << "=====================================================================================================" << endl;
}

//fungsi untuk menghias awalan
void hiasan_utama(){
    cout << "=====================================================================================================" << endl;
    cout << "-------------------------------------- S E L A M A T D A T A N G ------------------------------------" << endl;
    cout << "                                      DI PORTAL PARKIR KHUSUS MOBIL                                  " << endl;
    cout << "                                              MALL PRIENAL                                           " << endl;
    cout << "=====================================================================================================\n" << endl;
    
}

// fungsi untuk menampilkan kendaraan
void tampilkan_semua_kendaraan(){
    system("cls");
    // mengecek kendaraan kosong atau tidak
    if (merk_kendaraan.empty()){
        cout << "Tidak Ada Data Kendaraan" << endl;
        return; //fungsi return untuk mengembalikan nilai dan menghentikan eksekusi fungsi
    }
    //menampilkan daftar mobil yang sudah terparkir
    cout << "DAFTAR MOBIL YANG SUDAH TERPARKIR :" << endl;
    hiasan();
    for (int i = 0; i < merk_kendaraan.size(); i++){
        time_t waktu_masuk = system_clock::to_time_t(waktu_kendaraan[i]); 
        system_clock::time_point waktu_sekarang = system_clock::now();
        duration<double> durasi = waktu_sekarang - waktu_kendaraan[i];

        cout << "Mobil ke-" << i + 1 << endl;
        cout << "Plat Mobil   : " << plat_kendaraan[i] << endl;
        cout << "Merk Mobil   : " << merk_kendaraan[i] << endl;
        cout << "Warna Mobil  : " << warna_kendaraan[i] << endl;
        cout << "Waktu masuk : " << put_time(localtime(&waktu_masuk), "%H:%M:%S") << endl;
        cout << fixed << setprecision(2);
        cout << "Durasi Parkir: " << durasi.count() << " detik" << endl;
        cout << "\n";
        hiasan();
    }
}

//fungsi untuk pembayaran parkir
void pembayaran(){
    balik:
    system("cls");
    tampilkan_semua_kendaraan(); //menampilkan semua kendaraan yang sudah terparkir terlebih dahulu
    if (merk_kendaraan.empty()){ //mengecek apakah kosong atau tidak
        cout << "Tidak Ada Kendaraan Untuk Pembayaran" << endl;
        return;
    }
    string plat;
    cin.ignore(); //untuk mengampil newline
    cout << "Masukkan Plat Mobil yang akan keluar: "; getline(cin, plat);

    for (size_t i = 0; i < plat_kendaraan.size(); i++){
        if (plat_kendaraan[i] == plat){ //mengecek apakah sama plat yang diinput
            system_clock::time_point waktu_keluar = system_clock::now();
            duration<double> durasi = waktu_keluar - waktu_kendaraan[i];

            double biaya = ceil(durasi.count() / 60) * 5000; // Setiap 60 detik (1 menit) dikenakan biaya 5000
            cout << "Mobil dengan plat " << plat << " telah parkir selama " << int(durasi.count()) << " detik." << endl;
            cout << "B I A Y A  P A R K I R : Rp" << biaya << endl;

            // Hapus kendaraan dari daftar menggunakan fungsi erase
            merk_kendaraan.erase(merk_kendaraan.begin() + i);
            plat_kendaraan.erase(plat_kendaraan.begin() + i);
            warna_kendaraan.erase(warna_kendaraan.begin() + i);
            waktu_kendaraan.erase(waktu_kendaraan.begin() + i);

            return;
        }
    }
    cout << "Plat mobil tidak ditemukan!" << endl;
    goto balik; //fungsi balik
    
}

int main(){
    system("cls");
    petugas petugas;
    string *nama_petugas = &petugas.nama,*id_petugas = &petugas.id; //membuat pointer dengan berisikan alamat nama petugas dan id dari petugas
    kendaraan mobil;
    int pilih, jumlah_mobil;
    
    hiasan_utama();
    cout << "Kami senang Anda telah hadir." << endl;
    cout << "Sebelum melanjutkan, silahkan masukkan informasi Anda yang akan bertugas hari ini.\n" << endl;
    
    
    cout << "Masukkan nama : "; getline(cin, *nama_petugas);
    cout << "Masukkan ID   : "; cin >> *id_petugas;
    
    while (true){
        system("pause");
        system("cls");
        if (plat_kendaraan.size() >= 20 || jumlah_mobil >= 20){ //jika plat kendaraan sudah mencapai 20 atau lebih
                cout << "Maaf, parkiran hanya dapat memuat 20 mobil !" << endl;
                return 0; //keluar dari program
            }
        hiasan();
        //menampilkan nama dan id dari petugas
        cout << "Nama Petugas : " << *nama_petugas << endl;
        cout << "ID Petugas   : " << *id_petugas << endl;
        cout << "                                     TERIMA KASIH ATAS KERJASAMANYA !                                " << endl;
        cout << "------------------------------------- S E L A M A T  B E R T U G A S --------------------------------" << endl;
        hiasan();
        cout << "\n\n";
        //memilih opsi yang telah disediakan
        cout << "Silahkan input opsi berikut dalam bentuk angka." << endl;
        cout << "1. Tambahkan Daftar kendaraan" << endl;
        cout << "2. Tampilkan Daftar kendaraan" << endl;
        cout << "3. Pembayaran" << endl;
        cout << "4. Keluar Program" << endl;
        cout << "Masukkan opsi : "; cin >> pilih;
        
        //menambah mobil
        if (pilih == 1){
            cout << "Masukan jumlah mobil yang akan dipakirkan : "; cin >> jumlah_mobil;
            cin.ignore();
            if (plat_kendaraan.size() >= 20 || jumlah_mobil >= 20){ //jika plat kendaraan sudah mencapai 20 atau lebih
                cout << "Maaf, parkiran hanya dapat memuat 20 mobil !" << endl;
                return 0; //keluar dari program
            }
            for (int i = 0; i < jumlah_mobil; i++){
                cout << "Mobil ke-" << i + 1 << endl;
                cout << "Masukkan plat mobil  : "; getline(cin, mobil.plat);
                cout << "Masukkan merk mobil  : "; getline(cin, mobil.merk);
                cout << "Masukkan warna mobil : "; getline(cin, mobil.warna);
                tambah_kendaraan(mobil.merk, mobil.plat, mobil.warna);
                cout << "\n";
            }
        }
        //menampilkan semua kendaraan yang telah di masukkan
        else if (pilih == 2){
            tampilkan_semua_kendaraan();
        }
        //fitur untuk pembayaran parkir
        else if (pilih == 3){
            pembayaran();
        }
        //keluar dari program
        else if (pilih == 4){
            cout << "Terima kasih telah menggunakan layanan kami." << endl;
            break;
        }
        //jika memilih selain opsi
        else{
            cout << "Pilihan tidak valid. Program akan keluar." << endl;
            return 0;
        }
    }
}
