#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000    // cirpi tablosu icin sabit bir boyut belirle 
#define MAXBUF 101  //Her satirdan okunacak en fazla karakter sayisi kural geregi 100 + \0 karakteri 

typedef struct new {
  char *cumle;
	int sayi;
	struct new *sonraki;
	struct new *onceki;
} SOZCUK;

 SOZCUK *sozcuk = NULL;				// kelimeleri tutacak olan struct yapisi
 SOZCUK *yapiDizisi[MAX]; 				// kelimelerin cirpi degerinde kelimelerin bilgilerinin tutuldugu struct dizisi
 SOZCUK *baslangic = NULL, *bitis = NULL;  // siralama satirinde yer kelimelere yer degisikligi icin struct'larin basinı ve sonunu belirle
 SOZCUK *isaretci;         				// maxsayac sayida olan kelimeleri yazdirmak icin siralamada kullanilan struct pointer */

static int durum;  				// ayniMI fonsiyonunda ayni slota denk gelen diger kelime ile o slotta blunan kelimenin esitlik durumunu global tut

                                   //cirpi tablosu boyutuna gore slot numarsi uret
int cirp(char s[]){
	int i, top = 0;
    i=0;
while( s[i] != '\0' && (s[i]=(s[i] >= 65 && s[i] <= 90) ? (s[i]+32):s[i])){ // eger buyuk harf ise kucuk yap ve cirp
		top += (i+1) * s[i]; 
		 i++;}
                                         // kendi belirledigimiz bir cirpi uretme ifadesi cakisma olsada kontrol yapilmakta
	return top % MAX;
}

                                            // maxsayac sayfasindaki kelimeleri alfabetik siralayarak yapi zincir fonksiyonu olustur
void sirala_ekle( SOZCUK *p){ 
	 SOZCUK *ilk, *w;
	int i;
	if(baslangic == NULL){
		baslangic = p;
		p->sonraki = NULL;
		p->onceki = NULL;
		return ;
	}
	for (isaretci = baslangic; isaretci;isaretci = isaretci->sonraki){
		i = 1;
		if(strcmp(p->cumle, isaretci->cumle) == -1){ // gelen kelime kucukse gir
			ilk = isaretci->onceki;
			i = 0;
				if (!isaretci->onceki){ 					// oncesi bossa basa koy
					isaretci->onceki = p;
					p->onceki = NULL;
					p->sonraki = isaretci;
					baslangic = p;
					return ;
				}
				if (isaretci->onceki ){					// doluysa araya koy
					p->onceki = ilk;
					p->sonraki = isaretci;
					isaretci->onceki = p;
					ilk->sonraki = p;
					return ;
				}
			break;
		}
		w = isaretci;
	}	
	if(i) isaretci = w;
	if (!isaretci->sonraki){								//gelen kelime en buyuk oldugundan sona ekle
		isaretci->sonraki = p;
		p->sonraki = NULL;
		p->onceki = isaretci;
		return ;
	}
}

                                                          //maxsayac sayida olan kelimeleri yaz
void yazdir(FILE *fp,int max_count){
	int i;
	 SOZCUK *p;
	 i = 0;
	while ( i < MAX ){
		if ((sozcuk = yapiDizisi[i]) != NULL)i++;}
			for (; sozcuk; sozcuk = sozcuk->sonraki)
				if (sozcuk->sayi == max_count){ 
					p = ( SOZCUK *)malloc(sizeof( SOZCUK));
					p->cumle = strdup(sozcuk->cumle);
				sirala_ekle(p);
				}
	for (isaretci = baslangic; isaretci; isaretci = isaretci->sonraki){
		printf("%s, ",isaretci->cumle);
	}
	for (isaretci = baslangic; isaretci; isaretci = isaretci->sonraki){
		free(isaretci);
	}
}

                                                  // alfabeden bir harf ise true don 
int harfMI(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

                             // gelen 2 kelime ayni mi kontrol et 
 SOZCUK *ayniMI( SOZCUK *f, char *b){
	int boyut, i;
	for (; f; f = f->sonraki){
		if ((boyut = strlen(f->cumle)) == strlen(b)){
			durum = 1;
			i = 0;
			while ( i < boyut){
				if (f->cumle[i] != b[i]){
					durum = 0; break;        // kelimeler icinde ilk farkli karakter icin donguden cik
				} i++;
			}
			if (durum) return f; 			// donguden ciktiginda durum = 1 ise (yani kelimeler esit ise) o anki yapi'in adresini don
		}
	}
      durum = 0;
	return f; 								// kelime boylari esit degil veya kelimeler esit degilse o anki yapinin adresini don 
}

                                          // kelimeleri h slotuna ekle
void yukle(char *b, int h){
	sozcuk = malloc(sizeof( SOZCUK));
	sozcuk->cumle = strdup(b);
	sozcuk->sayi = 1;         		
	sozcuk->sonraki = yapiDizisi[h];
	yapiDizisi[h] = sozcuk;
}

                                          
void bellek_bosalt(){                             // bellekleri geri ver
	int i;
	i = 0;
	while ( i < MAX){
		if ((sozcuk = yapiDizisi[i]) != NULL) i++;}
			for (; sozcuk; sozcuk = sozcuk->sonraki)
				free(sozcuk);
}

int main(){

	int cirpi, i, durum;
	int maxsayac = 2;								// Birden fazla kelime varsa yazdir
	char *buf, c;
	
	buf = malloc(sizeof(char)*MAXBUF);
	i = 0;
	  while ( (c = getchar()) != EOF ){         // "Stdin" dosyasindan karakter oku ve EOF ile sonlandir
		if (harfMI(c)){ 
			*(buf+(i++)*sizeof(char)) = c;
			durum =1;
			}                    

		else if( durum ){  				   		 // harf disinda karakter bulana kadar buf'a karakter ekle (kelimeleri ayikla)
			*(buf+i*sizeof(char)) = '\0';        // kelime sonu karakteri ekle 
			cirpi = cirp(buf);	                     // kelimeyi cirp fonk. gonder ve slot numarasini don
			if ((yapiDizisi[cirpi]) != NULL){             // cirp tablosunda cirpi slotu dolu mu?
				sozcuk = yapiDizisi[cirpi];
				sozcuk =ayniMI(sozcuk, buf);         // esitlik fonksiyonundan donen yapi adresi
				if (durum){
					sozcuk->sayi =sozcuk->sayi  + 1;  			 // cirp'daki cirpi slotu dolu ve ayni kelime ise sadece sayisini artir
					maxsayac = (sozcuk->sayi > maxsayac) ? sozcuk->sayi:maxsayac; 	// kelimenin sayisi maxsayac dan buyukse maxboyut'u 
																				    	//kelimenin sayisi ile degistir 
				}
				else
					 yukle(buf, cirpi);                 	// cirp'daki cirpi slotu dolu ve farkli kelime ise yeni kelimeyi yukle
			}
			else if(yapiDizisi[cirpi] == NULL)
				 yukle(buf, cirpi);            			// cirp'deki cirpi slotu bossa ilk kelimeyi yukle
			free(buf);
			buf = malloc(sizeof(char)*MAX);	
			i = 0;
			durum = 0;
		}
	}
	yazdir(stdout,maxsayac);    // "Stdout" dosyasina cikdi uret 
	 bellek_bosalt();
	return 0;
}
