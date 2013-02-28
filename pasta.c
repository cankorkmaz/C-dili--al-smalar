#include<stdio.h>
#include<stdlib.h>

int main(){
  long int mpasta, pasta2, carpim, pasta1 = 0; // mpasta = Mahmutun pastası
	int say = 0;
	printf("mahmutun ziyan ettigi pasta:");
	scanf("%ld", &mpasta);
	if (!mpasta) {
		printf("==>> %ld pasta bulunamadi",mpasta);
		exit(1);
	}
	pasta2 = ((mpasta+1)*mpasta)/(pasta1+1); 		// pasta1+1 zaberceddinin ilk yedigi pasta ona karsılık diger yiyecegi pasta pasta2'dir
	if (pasta2 != mpasta+1){ 				// zeber ayni pastadan mi yiyor.
		pasta1 = 1;
		say++;
		pasta1 = 2;
		while ( pasta1 + mpasta < pasta2){ 
			carpim = (mpasta+pasta1)*mpasta;
			if (!(carpim % pasta1) && (pasta1+mpasta != carpim/pasta1)){// zeber tek seferde ve aynı dilimden yemiyorsa 
				say++;                                                     // durumu arttır
				pasta2 = carpim/pasta1; 						// yeni pasta2 degerini uret yiyecegi araligi daralt
			}pasta1++;
		}
	}getchar();
	printf("zeberceddin %d farkli sekilde yiyebilir\n",say);
	getchar();
	return 0;
}
