#include<stdio.h>
#include<string.h>
#include<stdlib.h>
long double MAX;   					      // listedeki max degeri tutar
int k;              				         // musteri numarasi
long double *liste; 				        //sifrelerin tutuldugu liste
long double *asal;					       //verdigimiz asal sayilarin tutuldugu liste
int listeboy , lenasal;				      //listeboy: sifre listesinin anlik boyunu tutar,lenasal:girdiden alinan listenin uzunlu


int max(void){
    int i, p;
    MAX = 0;
    for(i = 0; i < listeboy; i++){							//listenin icinde dolas eleman Max dan buyukse elemani
        if ( liste[i] > MAX ){								//Max a ata
            MAX = liste[i];									
            p = i;											//p=Max elemanin indisi
        }
    }
    return p;												//indisi dondur
}
int arama(long double sifre){								
    int i;
    for( i = 0; i < listeboy; i++){							//sifrenin liste icinde olup olmadigiina bakar
      if ( liste[i] == sifre )								
            return 1;										//varsa 1 doner 
    }
    return 0;												//yoksa 0
}
void sort(){
    int i, j;
    long double tmp;
    for(i = 0; i < listeboy; i++)							//ayni listedeki elemanlari
        for(j = 0; j < listeboy; j++)						
            if ( liste[i] < liste[j] ){						//karsilastir kucukden buyuge
                tmp = liste[i];								//siralamak icin
                liste[i] = liste[j];						//yerlerini degistirerek buyukden kucuge 
                liste[j] = tmp;								//siralar
			} 
}
int sifreli(int i, int j, int durum){						
    long double sifre;
    int indis;
    sifre = liste[i]*asal[j];								//listenin i. elemani ile asal listesinin j. elemanini carp
    if ( arama(sifre) == 1 );								//olusan yeni sayiyi arama fonksiyonuna yolla 1 donerse bise yapma
    else if ( arama(sifre) == 0 ){							//icinde yoksa max fonksiyonuna yolla 
        indis = max();										//indis =MAx sayisinin indisi
        if ( MAX > sifre && k <= listeboy ){				//Max sayisi sifreden buyukse ve musteri no listeboyundan kucukesitse 
            liste[indis] = sifre;							//listeye ekle
        }
        else                                                //degilse
            if (listeboy < k){								//listeboyu musteri no dan kucukse
                liste[listeboy] = sifre;					//listenin son indisine sifreyi ata
                listeboy++;									//listeboyu 1 arttir
            }
    }
    if(durum == 1 && i < listeboy-1)						//1 durumunda ve i <listeboy-1 se
        sifreli(i+1, j, durum);								//sifrele fonksiyonuna git i+1 j ve 1 degerlerini arguman olarak al
    else if (listeboy < k && durum == 0)					//degilse ve listeboy<musteri no ve 0 durumundaysa
        sifreli(i+1, j, durum);								//sifreli fonksiyonuna don i+1 j ve 0 i arguman olarak al
    else {													//bunlarin hic biri deilse 
        if (j == (lenasal-1)){								//j==girilen listenin boyutu ise
			return 0;										// o don
		}
        else {												//degil ise
			i = 0;											//i ye 0 degerini ata 
			durum = 1;										//1 durumuna gec
			sifreli(i, j+1, durum);							//sifreli fonk don i j+1 ve 1 degerlerini arguman olarak al
		}
	}
	return 0;
}

int main(void){
    int state = 0, i, asal_adedi;
	printf("asal sayi adedini girin:");
	scanf("%d",&asal_adedi);									//asal sayi adedini iste
	listeboy = lenasal = asal_adedi;							//listboy ve lenasala bu degeri ata
	asal = calloc(asal_adedi,sizeof(long double));				//asal listesi icin bellekden yer al
	printf("asal sayilari aralarinda bir bosluk birakarak giriniz:");				
	for(i = 0 ; i < asal_adedi ; i++)							//asal adedi kadar 
		scanf("%Lf",&asal[i]);									//sayi oku
	printf("musteri numarasini giriniz");
	scanf("%d",&k);												//girile musteri no yu oku
	liste = calloc(k,sizeof(long double));						//sifre listesi icin belekden yer al
	for(i = 0 ; i < asal_adedi ; i++)							//0 dan asaladedi sayisina kadar
		liste[i] = asal[i];										//listenin 0. indisindne baslayarak asal listesinin
																//elemanlarini liste ye ata
    for(i = 0; i < k; i++){										//0. indis den basla musteri nosuna kadar
        sifreli(0, 0, state);									//sifreli fonksiyonuna git 0 0 0 argumanlarini al
        state = 1;												//1 durumuna gec
    }
    sort();														//sort fonksiyonunu cagir

	printf("\n%.0Lf",liste[k-1]);								// sifreyi yazdir
    free(liste);												//alinan bellegi serbest birak
    free(asal);													//"        "       "      "
    return 0;
}
