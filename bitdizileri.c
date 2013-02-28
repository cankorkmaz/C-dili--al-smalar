#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

static int uzunluk = 0;

void boc(int *bellek, int boy,int N){  // Bcd kodu 10 luga cevir
  int i, j, t, top;
	t = boy%4;
	i = 0;
	printf("hepsini iceren en kisa bit dizisi:");
	while ( i < boy ){
		top = 0;
		j = 0;
		
		while ( j < t ){
			top += bellek[i]*pow(2, t-j-1);
			j++; i++;
            }
	  if (t>0) {printf("%d",top);}
		t = 4;
	}
}

int *osic(int sayi){ // onlugu 2lige cevir
	int *bellek, i;
	bellek = malloc(sizeof(int)*15);
	if( bellek != NULL ){
	    i = 0;
     	while ( 0<sayi ){
		      bellek[i] = sayi%2;
              sayi = sayi/2;
		      uzunluk++;i++ ;}}
	
	else {
	     printf( "bellek yetersiz!" );
         exit(1);
         }
	return bellek;
}

int ucekle(int *S , int boy){ // 3 ekleme fonksiyonu.

	int gecici= 0, top= 0;
	int a, j, v, t;
    a = boy;
	while ( a> 0){
		if(a>4)v=4; // 4 bit 4 bit grupla en anlamli bitler 4 bitten kucuksede grupla
        else v=a;
        
		if( (v == 3 && S[a-3] && (S[a-2] || S[a-1])) || (v==4 && (S[a-4] || ( S[a-3] && (S[a-2] || S[a-1] ))) ) ){  // Basamak degeri 4'den buyukse 3 ekle
			j = 0;
            while ( j < v ){
				if (j < 2){
					top= top + S[a-1] + 1;
					S[a-1] = top%2;
					top = top/2; // Eldeyi sakla
					
				}
				else if (top){
					top = top + S[a-1];
					S[a-1] = top%2;
					top = top/2;
				}j++; a--;
			}
		}
		else a = a - v;
	}
	t = 0;
	if (top){ // En son elde 1 ise diziyi saga kaydir ve eldeyi en basa ekle
		gecici = top;
		a = 0;
		while( a < boy){
			top = gecici;
			gecici = S[a];
			S[a] = top;
			a++;
		}
		t = 1;
		S[a] = gecici;
	}
	return t;
}
void kaydir(int *ikildizi, int boy){ //Kaydirma fonksiyonu
	int a, n, i = 0;

	int *bellek;
	bellek= malloc(sizeof(int)*2*boy);
	if( bellek== NULL ){
		printf( "bellek yetersiz" );
		exit(1);
	}
    a = 0, n = 0;
	while( a < boy  ){
		n = n+i;
		bellek[n] = ikildizi[a]; 						// Bit bit kaydir
		if(n > 1 && a < boy - 1) i = ucekle(bellek, n+1);// 3 ekleme icin gonder
		n++; a++; 
	}

	boc(bellek,n,boy-1);

	free(bellek);
}

int  main(void){
	int *bellek, N, *ikil,ind ;
    printf("bit adedini giriniz:");
	scanf("%d",&N);
	bellek= malloc(sizeof(int)*(N+1));
	if( bellek == NULL ){
		printf( "Yetersiz bellek!" );
		exit(1);
	}
	bellek[0] = 1;
	ikil = osic(N-1); 		  // N-1 'in binary hesabini yap

	for (  ind = 0; ind < N ; ind++)
		*(bellek+ind+1) = 0; 			 // 2^N 'in binary karsiligini diziye ata

	for (  ind = 0 ; ind < uzunluk; ind++)
		bellek[N-ind] = ikil[ind]; 		// 2^N + N -1 'in binary karsiligi

	kaydir(bellek, N+1); 				// 2^N + N - 1 'in binary karsiligini kaydirmaya gonder
	free(bellek);
	free(ikil);
getchar();getchar();
	return 0;
}
