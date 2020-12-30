#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#define len 10

typedef struct {
	int musteri_no;
	char ad[20], soyad[20]; 
} Musteri;
int hash(int number);
void init();
void display();
void insert();
void search();
void delete();
void displayHashTable();
void avarageStep();
int find_current(int index);
/* global variable*/
int const bufferLength = 255;;
int size=0,i;
int hash_tablo[len][2];
Musteri *veri_liste[len];

int main(){

	FILE *fp;
	
   	if ((fp = fopen("veri.txt", "r")) == NULL) {
      	printf("File can not opened!\n");
      	exit(1);
  	}
	init();

	int id=0;
	Musteri *temp=malloc(sizeof(Musteri));
	char buffer[bufferLength];
	*veri_liste=(Musteri *)malloc(sizeof (Musteri));
	int cnt=0;
	while(fgets(buffer, bufferLength, fp) && id<len) {
		char array[3][20];
		int i=0,id;
    	char *token = strtok(buffer, " ");
		while (token != NULL) 
		{ 	
			strcpy(array[i++],token);
			token = strtok(NULL, " "); 
		}
		temp->musteri_no=atoi(array[0]);
		strcpy(temp->ad,array[1]);
		strcpy(temp->soyad,strtok(array[2],"\n"));
		insert(temp);
		temp=calloc(1,sizeof(Musteri));
	}
	int op;
	while(true){
		printf(  "\n**************************\n1-Ekleme Işlemi\n2-Arama İşlemi\n3-Silme İşlemi\n4-Hash tablosu listeleme\n5-Veri listesini listeleme\n6-Ortalama Adım Sayısı\n7-Exit from program\nPlease select the operation number(just integer): \n");
		scanf("%d", &op);
		
		switch(op){
			case 1:
			 	printf("Musteri no giriniz:");
    			scanf("%d",&(temp->musteri_no));
    			printf("İsim giriniz:");
    			scanf("%s",(temp->ad));
    			printf("Soyisim giriniz:");
    			scanf("%s",(temp->soyad));
				insert(temp);
				break;
			case 2:
				printf("Please enter the musteri number:\n");
				scanf("%d",&id);
				search(id);
				break;
			case 3:
				delete();
				break;
			case 4:
				displayHashTable();
				break;
			case 5:
				display();
				break;
			case 6:
				avarageStep();
				break;
			case 7:
				fclose(fp);
				exit(0);
			default:
				printf("Please enter the correct number");
				break;
			
		}
		printf("**************************\n");
	}
	
	
	return 0;
}

void insert(Musteri *musteri){
	int mNo=musteri->musteri_no;
	int val=hash(mNo);
	if(size==len){
		printf("Tablo Dolu\n");
	}
	if(hash_tablo[val][0]==-1){
		hash_tablo[val][0]=mNo;
		veri_liste[val]=musteri;
	}
	else{
		int i=0;
		int current=val;
		for(;i<len;i++){

			if(hash_tablo[i][0]==-1){
				hash_tablo[i][0]=mNo;
				hash_tablo[find_current(val)][1]=i;
				veri_liste[i]=musteri;
				break;
			}
			
		}
	}
}
int find_current(int index){
	
	while(hash_tablo[index][1]!=-1){
		index=hash_tablo[index][1];
	}
	return index;
}
void search(int musteri_no){
	int val=hash(musteri_no);
	int step=0;
	while(hash_tablo[val][1]!=-1 && step<10){
		if(hash_tablo[val][0]==musteri_no){
			
			break;
		}
		val=hash_tablo[val][1];
		step++;
	}
	if(step==10){
		printf("Veri bulunamadı !\n");
	}
	else{
		printf("%d  %s  %s\n",musteri_no,veri_liste[val]->ad,veri_liste[val]->soyad);
		printf("Veri %d adımda bulundu\n",step+1);
	}
	
}
void delete(int musteri_no){
	for(i=0;i<len;i++){
		if(musteri_no==hash_tablo[i][0]){
			hash_tablo[i][0]=-1;
			veri_liste[i]=calloc(1,sizeof(Musteri));
		}
	}
}
int hash(int number){
	return number%len;
}
void init(){

	for(int i=0;i<10;i++){
        for(int j=0;j<2;j++){
            hash_tablo[i][j]=-1;
        }
		veri_liste[i]=(Musteri *)malloc(sizeof(Musteri)); 
    }
}
void display(){
	int i;
	for (i=0;i<len;i++){
		printf("%d %s %s\n",veri_liste[i]->musteri_no,veri_liste[i]->ad,veri_liste[i]->soyad);
	}
}
void displayHashTable(){
	for(int i=0;i<10;i++){
            printf("| %d | %5d | %2d |\n",i,hash_tablo[i][0],hash_tablo[i][1]);
    }
}
void avarageStep(){
	int arr[10]={0,0,0,0,0,0,0,0,0,0};
	for( i=0;i<len;i++){
		
		if(hash_tablo[i][0]==-1){
			continue;
		}
		else{
			arr[hash(hash_tablo[i][0])]+=arr[hash(hash_tablo[i][0])]+1;
		}
	}
	int cnt=0,sum=0;
	for(i=0;i<len;i++){
		if(arr[i]!=0){
			cnt++;
			sum+=arr[i];
		}
	}
	printf("ortalama adım sayısı = %d\n",(sum/cnt));
}


