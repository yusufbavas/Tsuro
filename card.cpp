#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>    
#include "board.h"
#include "card.h"

using namespace std;

// Kartin yapisi ayarlanir. Kapi yerleri ve portlar belirlenir.
card::card(){	
	int i,j;
	int x = 1;
	for(i=0;i<6;++i){
		for(j=0;j<12;++j){
			if(i == 0 || i == 5){	//  ilk ve son satir kontrol edilir.
				if(j != 4 && j != 7) a_card[i][j] = space1;	//	ilk ve son satir port disidaki yerler '.' yapilir.
				else{
					a_card[i][j] = x;	// Kapi numarasi verilir.
					x++;
				}
			}
			else {
				if(j== 0 || j == 11){	// ilk ve son blok içinde
					if(i == 2 || i == 3){	// 2. ve 3. satir portlari
						a_card[i][j] = x;
						x++;
					}
					else a_card[i][j] = space2;	
				}
				else if(j == 4 || j == 7){	
					a_card[i][j] = port;
				} 
				else a_card[i][j] = space;	// kalan yerleri boş birakilir.
			}
		}
	}
}

bool card::is_eq(int arr[],int indis,int random){
	int i;
	if(random == indis+1) return false;
	for(i=0;i<8;++i){
		if(i != indis && arr[i] == random) return false;
	}
	arr[random-1] = indis+1;
	return true;
}		
// Kartin portlari random doldurulur
bool card::set_card(){	
	bool result = true;
	int i,j;
	int arr[8];
	for(i=0;i<8;++i) arr[i] = 0;
	int indis = 0;

	for(i=0;i<8;++i){
		if(arr[i] == 0){
			do{
				arr[i] = rand() %8 +1;
			}while(is_eq(arr,i,arr[i]) == 0);
		}
	}

	for(i=1;i<5;++i){
		for(j=4;j<8;j+=3){
			if(a_card[i][j] == port){
				a_card[i][j] = arr[indis];
				indis++;
			}
		}
	}
	//Kart daha once uretilmis mi ona bakilir. Eger uretilmisse false dondurulur.
	for(i=0;i<cards_size;++i){
		if(*this == cards[i]){
			result = false;
		}
	} 
	// Eger uretilmemis ise vectore atilir.
	if(result){
		cards.push_back(*this);
		cards_size++;
	}
	return result;
}
// Kartin verilen giris kordinatlarina gore cikis kordinatlari bulunur.
void card::exit(int &loc_i, int &loc_j){	// cikis yerini belirliyor.
	int i;
	int j;
	int target;
	
	if(a_card[loc_i][loc_j] == 1 || a_card[loc_i][loc_j] == 2) {
		target = a_card[loc_i+1][loc_j];
	}
	else if(a_card[loc_i][loc_j] == 3 || a_card[loc_i][loc_j] == 5){
		target = a_card[loc_i][loc_j+4];
	}
	else if(a_card[loc_i][loc_j] == 4 || a_card[loc_i][loc_j] == 6){
		target = a_card[loc_i][loc_j-4];
	}
	else{
		target = a_card[loc_i-1][loc_j];	
	}

	for(i=0;i<6;++i){
		for(j=0;j<12;(i==0 || i == 5) ? ++j : j+=11 ){
			if(a_card[i][j] == target){
				loc_i = i;
				loc_j = j;
			}
		}
	}
} 
// Kartin heryerine space atilir.
void card::empty(){
	int i,j;
	for(i=0;i<6;++i){
		for(j=0;j<12;++j){
			a_card[i][j] = space;
		}
	}
}
//Karti verilen arrayin icerisine kopyalar
void card::get_card(int result[][12]) const{
	for(int i=0;i<6;++i){
		for(int j=0; j<12;++j) result[i][j] = a_card[i][j];
	}
}
// Kartlarin ayni olup olmadigi belirlenir bu sayede ayni kart bir daha oyunda kullanilmaz.
bool card::operator ==(const card& x) const{
	bool result=true;
	int temp[6][12];
	x.get_card(temp);
	int i,j;
	for(i=0;i<6;++i){
		for(j=0;j<12;++j){
			if(a_card[i][j] != temp[i][j]){
				result = false;
			} 
		}
	}
	return result;
}
// Karti ekrana yazdirir.
void card::print_card() const{
	int i,j;
	for(i=0;i<6;++i){
		for(j=0;j<12;++j){
			if(a_card[i][j] == space) cout<<" ";
			else if(a_card[i][j] == space1) cout<<".";
			else if(a_card[i][j] == space2) cout<<":";
			else{
				cout<<a_card[i][j];
			}
		}
		cout<<endl;
	}
	cout<<endl;
}
// Kart bastan bir daha olusturulur. Asil amac kaybedilen port yerlerini tekrar belirlemektir.
void card::card_restart(){
	int i,j;
	int x = 1;
	for(i=0;i<6;++i){
		for(j=0;j<12;++j){
			if(i == 0 || i == 5){	//  ilk ve son satir kontrolu
				if(j != 4 && j != 7) a_card[i][j] = space1;	//	ilk ve son satir portu
				else{
					a_card[i][j] = x;	// portu ekle ve arttır
					x++;
				}
			}
			else {
				if(j== 0 || j == 11){	// ilk ve son blok içinde
					if(i == 2 || i == 3){	// 2. ve 3. satir portlari
						a_card[i][j] = x;
						x++;
					}
					else a_card[i][j] = space2;	// kalan kısımlar ':'
				}
				else if(j == 4 || j == 7){	//	geçitleri ayarla
					a_card[i][j] = port;
				} 
				else a_card[i][j] = space;	// kalan yerleri boş bırak
			}
		}
	}
}
/* Kartlar konumlarindan yola cikilarak dondurulur. Donme islemi fonksiyonu her cagirmada saat yonunde 90 derece olarak ayarlanmistir.  */
void card::rotate( int x){

	int i,j;
	int temp,temp2;

	while(x>0){

		temp = a_card[1][4];
		temp2 = a_card[1][7];

		a_card[1][4] = a_card[3][4];
		a_card[1][7] = a_card[2][4];

		a_card[3][4] = a_card[4][7];
		a_card[2][4] = a_card[4][4];

		a_card[4][7] = a_card[2][7];
		a_card[4][4] = a_card[3][7];

		a_card[2][7] = temp;
		a_card[3][7] = temp2;

		for(i=1;i<5;++i){
			for(j=4;j<8;j+=3){
				if(a_card[i][j] == 1) a_card[i][j] = 4;
				else if(a_card[i][j] == 2) a_card[i][j] = 6;
				else if(a_card[i][j] == 3) a_card[i][j] = 2;
				else if(a_card[i][j] == 4) a_card[i][j] = 8;
				else if(a_card[i][j] == 5) a_card[i][j] = 1;
				else if(a_card[i][j] == 6) a_card[i][j] = 7;
				else if(a_card[i][j] == 7) a_card[i][j] = 3;
				else if(a_card[i][j] == 8) a_card[i][j] = 5;
			}
		}

		x--;

	}
}