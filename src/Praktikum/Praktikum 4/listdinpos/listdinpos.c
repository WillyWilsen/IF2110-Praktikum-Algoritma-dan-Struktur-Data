#include <stdio.h>
#include "listdinpos.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity) {
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list l kosong dengan kapasitas capacity + 1 */
/* Proses: Inisialisasi semua elemen list l dengan VAL_UNDEF */
    /* KAMUS */
    int i;
    /* ALGORITMA */
    BUFFER(*l) = (int*) malloc (capacity * sizeof(int));
    CAPACITY(*l) = capacity;
    for (i=0;i<capacity;i++) {
        ELMT(*l,i) = VAL_UNDEF;
    }
}

void dealocate(ListDin *l) {
/* I.S. l terdefinisi; */
/* F.S. TI(l) dikembalikan ke system, CAPACITY(l)=0; nEff(l)=0 */
    /* ALGORITMA */
    free(BUFFER(*l));
    CAPACITY(*l) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int length(ListDin l) {
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list kosong */
    /* KAMUS */
    int i = 0;
    /* ALGORITMA */
    while (i<CAPACITY(l) && ELMT(l,i) != VAL_UNDEF) {
        i++;
    }
    return i;
}

/* *** Selektor INDEKS *** */
IdxType getLastIdx(ListDin l) {
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
    /* KAMUS */
    int i = 0;
    /* ALGORITMA */
    while (i<CAPACITY(l) && ELMT(l,i) != VAL_UNDEF) {
        i++;
    }
    return i-1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, IdxType i) {
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran list */
/* yaitu antara indeks yang terdefinisi utk container*/
    /* ALGORITMA */
    return (i >= 0 && i < CAPACITY(l));
}
boolean isIdxEff(ListDin l, IdxType i) {
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..getLastIdx(l) */
    /* ALGORITMA */
    return (i >= 0 && i <= getLastIdx(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l) {
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
    /* ALGORITMA */
    return (ELMT(l,0) == VAL_UNDEF);
}
/* *** Test list penuh *** */
boolean isFull(ListDin l) {
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
    /* ALGORITMA */
    return (getLastIdx(l) == CAPACITY(l)-1);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l) {
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */
    /* KAMUS */
    int N;
    int i;
    /* ALGORITMA */
    scanf("%d", &N);
    while(N < 0 || N > CAPACITY(*l)) {
        scanf("%d", &N);
    }
    for (i=0;i<N;i++) {
        scanf("%d", &ELMT(*l,i));
    }
}
void displayList(ListDin l) {
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
    /* KAMUS */
    int i;
    /* ALGORITMA */
    printf("[");
    for (i=0;i<length(l);i++) {
        if(i == length(l)-1) {
            printf("%d", ELMT(l,i));
        }
        else {
            printf("%d,", ELMT(l,i));
        }
    }
    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus) {
/* Prekondisi : l1 dan l2 memiliki nEff sama dan tidak kosong */
/*              Jika plus=false, tidak ada elemen l1-l2 yang menghasilkan nilai <= 0 */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
    /* KAMUS */
    int i;
    ListDin l3;
    /* ALGORITMA */
    CreateListDin(&l3, CAPACITY(l1));
    for (i=0;i<length(l1);i++) {
        if(plus) {
            ELMT(l3,i) = ELMT(l1,i) + ELMT(l2,i);
        } else {
            ELMT(l3,i) = ELMT(l1,i) - ELMT(l2,i);
        }
    }
    return l3;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2) {
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */
    /* KAMUS */
    int i = 0;
    boolean sama = true;
    /* ALGORITMA */
    if(length(l1) == length(l2)) {
        while(i < length(l1) && (sama)) {
            if(ELMT(l1,i) != ELMT(l2,i)) {
                sama = false;
            } else {
                i++;
            }
        }
    } else {
        sama = false;
    }
    return sama;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
IdxType indexOf(ListDin l, ElType val) {
/* Search apakah ada elemen list l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan VAL_UNDEF */
/* Menghasilkan indeks tak terdefinisi (VAL_UNDEF) jika list l kosong */
/* Skema Searching yang digunakan bebas */
    /* KAMUS */
    int i = 0;
    /* ALGORITMA */
    while (i < length(l) && ELMT(l,i) != val) {
        i++;
    }
    if (length(l) == 0 || i == length(l)) {
        return VAL_UNDEF;
    } else {
        return i;
    }
}

/* ********** NILAI EKSTREM ********** */
void extremes(ListDin l, ElType *max, ElType *min) {
/* I.S. List l tidak kosong */
/* F.S. max berisi nilai maksimum l;
        min berisi nilai minimum l */
    /* KAMUS */
    int i;
    /* ALGORITMA */
    *max = ELMT(l,0);
    *min = ELMT(l,0);
    for (i=1;i<length(l);i++) {
        if(ELMT(l,i) < *min) {
            *min = ELMT(l,i);
        }
        if(ELMT(l,i) > *max) {
            *max = ELMT(l,i);
        }
    }
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut) {
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan Capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */
    /* KAMUS */
    int i;
    /* ALGORITMA */
    CreateListDin(lOut, CAPACITY(lIn));
    for (i=0;i<length(lIn);i++) {
        ELMT(*lOut,i) = ELMT(lIn,i);
    }
}
ElType sumList(ListDin l) {
/* Menghasilkan hasil penjumlahan semua elemen l */
/* Jika l kosong menghasilkan 0 */
    /* KAMUS */
    int sum = 0;
    int i;
    /* ALGORITMA */
    for (i=0;i<length(l);i++) {
        sum += ELMT(l,i);
    }
    return sum;
}
int countVal(ListDin l, ElType val) {
/* Menghasilkan berapa banyak kemunculan val di l */
/* Jika l kosong menghasilkan 0 */
    /* KAMUS */
    int i;
    int count_val = 0;
    /* ALGORITMA */
    for (i=0;i<length(l);i++) {
        if(ELMT(l,i) == val) {
            count_val += 1;
        }
    }
    return count_val;
}
boolean isAllEven(ListDin l) {
/* Menghailkan true jika semua elemen l genap. l boleh kosong */
    boolean flag = true;
    int i = 0;
    /* ALGORITMA */
    while(i < length(l) && (flag)) {
        if(ELMT(l,i) % 2 != 0) {
            flag = false;
        }
        i++;
    }
    return flag;
}

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc) {
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
   /* KAMUS */
   int i;
   int Pass;
   int IMax;
   int IMin;
   int temp;
   /* ALGORITMA */
   if (!isEmpty(*l)) {
       for(i=0;i<length(*l)-1;i++) {
            IMax = i;
            IMin = i;
            for(Pass=i+1;Pass<length(*l);Pass++) {
                if (ELMT(*l,Pass) < ELMT(*l,IMin)) {
                    IMin = Pass;
                }
                if (ELMT(*l,Pass) > ELMT(*l,IMax)) {
                    IMax = Pass;
                }
            }
            if(asc) {
                temp = ELMT(*l,IMin);
                ELMT(*l,IMin) = ELMT(*l,i);
                ELMT(*l,i) = temp;
            } else {
                temp = ELMT(*l,IMax);
                ELMT(*l,IMax) = ELMT(*l,i);
                ELMT(*l,i) = temp;
            }
       }
   }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, ElType val) {
/* Proses: Menambahkan X sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
    /* ALGORITMA */
    ELMT(*l,length(*l)) = val;
}
/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, ElType *val) {
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
    /* ALGORITMA */
    *val = ELMT(*l,length(*l)-1);
    ELMT(*l,length(*l)-1) = VAL_UNDEF;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void growList(ListDin *l, int num) {
/* Proses : Menambahkan kapasitas sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */
    /* KAMUS */
    ListDin temp;
    int i;
    /* ALGORITMA */
    BUFFER(temp) = (int*) malloc ((CAPACITY(*l)+num) * sizeof(int));
    for (i=0;i<length(*l);i++) {
        ELMT(temp,i) = ELMT(*l,i);
    }
    for (i=length(*l);i<(CAPACITY(*l)+num);i++) {
        ELMT(temp,i) = VAL_UNDEF;
    }
    CAPACITY(temp) = CAPACITY(*l) + num;
    *l = temp;
}

void shrinkList(ListDin *l, int num) {
/* Proses : Mengurangi kapasitas sebanyak num */
/* I.S. List sudah terdefinisi, ukuran Capacity > num, dan nEff < Capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */
    /* KAMUS */
    ListDin temp;
    int i;
    /* ALGORITMA */
    BUFFER(temp) = (int*) malloc ((CAPACITY(*l)-num) * sizeof(int));
    for (i=0;i<length(*l);i++) {
        ELMT(temp,i) = ELMT(*l,i);
    }
    for (i=length(*l);i<(CAPACITY(*l)-num);i++) {
        ELMT(temp,i) = VAL_UNDEF;
    }
    CAPACITY(temp) = CAPACITY(*l) - num;
    *l = temp;
}

void compactList(ListDin *l) {
/* Proses : Mengurangi kapasitas sehingga nEff = Capacity */
/* I.S. List tidak kosong */
/* F.S. Ukuran Capacity = nEff */
    /* KAMUS */
    ListDin temp;
    int i;
    /* ALGORITMA */
    BUFFER(temp) = (int*) malloc ((length(*l)) * sizeof(int));
    for (i=0;i<length(*l);i++) {
        ELMT(temp,i) = ELMT(*l,i);
    }
    CAPACITY(temp) = length(*l);
    *l = temp;
}
