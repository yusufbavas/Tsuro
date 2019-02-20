#include <iostream>
#include <vector>
#include "board.h"
#include "card.h"
#include "player.h"    
#include "game.h"

using namespace std;
/* Bu constructor ile oyun mapi olusturulur ve kenarlari ayarlanir. */
Game::Game(){	
	int i,j,count;
	Player player;
	for(i=0;i<9;++i){
		cards[i].empty();
	}
	for(i=0;i<20;++i){	
		for(j=0;j<40;++j)
			map[i][j] = space;
	}
	for(i=0;i<20;++i){
		for(j=0;j<40;++j){
			if(i == 0 || i == 19){
				if( j % 6 == 0 && j % 4 == 2 ){
					
					map[i][j] = starting_point;
					map[i][j+3] = starting_point;
				}
				
				else if(map[i][j] != starting_point){
					map[i][j] = wall1;
				}
			}
			else if(j == 0 || j == 39){
				if( i % 3 == 0 && i % 2 == 1){
					map[i][j] = starting_point;
					map[i+1][j] = starting_point;
				}
				else if(map[i][j] != starting_point){
					map[i][j] = wall2;
				}
			}
		}
	}
	
	do{
		cout<<"How many player :? (At least 2 players)"<<endl;
		cin>>count;
		cin.clear();
		cin.ignore();
	}while(!(count >= 2 && count < 10));	

	v_size = 0;
// Her kullnici icin new_player fonksiyonu cagirilir ve oyuncularda olusturulmus olur.
	for(i=0;i<count;++i,v_size++){
		cout<<"For player "<<i+1<<endl;
		player.new_player();
		players.push_back(player);
		while(get_sp(players[i].loc_i,players[i].loc_j) == false);
	}
	
}
/* Board ekrana bastirilir.*/
void Game::print_board() const{
	bool flag;

	for(int i=0;i<20;++i){
		for(int j=0;j<40;++j){
			flag = true;
			for(int k=0;k<v_size;++k){
				if(players[k].loc_i == i && players[k].loc_j == j){
					 cout<<players[k].token;
					 flag = false;
				
				}
			}
			if(flag){
				if(map[i][j] == wall1) cout<<"-";
				else if(map[i][j] == wall2) cout<<"|";
				else if(map[i][j] == starting_point || map[i][j] == starting_point_2) cout<<"o";
				else if(map[i][j] == space) cout<<" ";
				else if(map[i][j] == space1) cout<<".";
				else if(map[i][j] == space2) cout<<":";
				else cout<<map[i][j];
			}
		}
		
		cout<<endl;
	}
	cout<<endl;
}
/* 
	Oyuncuya rastgele bir baslangic noktasi verilir. 
	Eger verilen konum daha once bir kullaniciya verilmisse fasle dondurulur ve fonksiyon bir daha cagirilir.
*/
bool Game::get_sp(int &x,int &y){	//true: basarili false: basarisiz

	int i,j,result;
	bool flag = true;

	result = rand() % 24 + 1;

	for(i=0;i<20;++i){
		for(j=0;j<40;++j){
			if(map[i][j] == starting_point){
				result--;
				if(result == 0){
					map[i][j] = starting_point_2;
					x = i;
					y = j;
				}
			}
			else if(map[i][j] == starting_point_2) result--;
		}
	}
	for(i=0;i<v_size;++i){
		if(players[i].loc_i == x && players[i].loc_j == y)
			flag = false;
	}
	return flag;
}
/* Oyuncunun konumuna gore mapin neresine kart eklenecegine karar verilir ve kart eklenir.
Eklenen kart oyuncunun elindeki kartlardan cikarilir ve yerine yenisi verilir. */
void Game::add_card(int p,int c){
	card new_card;
	
	int temp_i = players[p].loc_i - 1;
	int temp_j = players[p].loc_j - 2 ;
	int location = (temp_i / 6) * 3  + (temp_j  / 12);

	cards[location] = players[p].cards[c]; 

	players[p].cards.erase(players[p].cards.begin()+c);
	new_card.set_card();
	players[p].cards.push_back(new_card);

	for(int i=0;i<6;++i){
		for(int j=0;j<12;++j){

			map[location /3 *6  + i + 1][location % 3 * 12 + j +2] = cards[location].a_card[i][j];
		}
	}
}
// Siradaki oyuncuya gecis icin oyuncuyu isaret eden bir adres dondurulur.
Player* Game::get_player(int c){
	return &players[c];
}
// Oyuna baslayan oyuncu sayisi dondurulur.
const int Game::player_num() const{
	return v_size;
}
// Kartta karta gecis icin konumlar duzenlenir. Kartin cikislari belli oldugu icin konum arttirma veya azaltmalariyla saglanir.
void Game::restore_loc(Player& player){

	if(map[player.loc_i][player.loc_j] == 1 ||
		map[player.loc_i][player.loc_j] == 2 ){
		
		player.loc_i--;
	}
	else if(map[player.loc_i][player.loc_j] == 3 ||
		map[player.loc_i][player.loc_j] == 5 ){
	
		if(player.loc_j < 5) player.loc_j--;
		player.loc_j--;

	}
	else if(map[player.loc_i][player.loc_j] == 4 ||
		map[player.loc_i][player.loc_j] == 6 ){
		
		if(player.loc_j > 30)	player.loc_j++;	
		player.loc_j++;	
	
	}
	else if(map[player.loc_i][player.loc_j] == 7 ||
		map[player.loc_i][player.loc_j] == 8 ){
		
		player.loc_i++;	
	}

}
// Oyuncunun konumunun mapin aktif bolumunde olup olmadigina bakilir. Eger degilse in_game false yapilir ve oyuncu kaybetmis olur.
bool Game::in_game(Player& player){
	bool result = true;
	if(map[player.loc_i][player.loc_j] < 0){
		player.in_game = false;
		result = false;
	}
	return result;
}
// konumun bos olup olmadigina bakilir. 
bool Game::is_empty(const Player& player){
	bool result = false;
	if(map[player.loc_i][player.loc_j] == space){
		result = true;
	}
	return result;
}
// Uzerine gelinen kartin mapteki hangi kart oldugu bulunur ve o kart return edilir.
card Game::get_card(const Player& player) const{
	int temp_i = player.loc_i - 1;
	int temp_j = player.loc_j - 2 ;
	int location = (temp_i / 6) * 3  + (temp_j  / 12);
	return cards[location];
}
// Oyunda hala aktif olan oyuncu sayisi dondurulur.
const int Game::player_cond() const{

	int i,result = 0;
	for(i=0;i<v_size;++i){
		if(players[i].in_game == true) result++;
	}
	return result;
}
/*
	Bu fonksiyonda kartlar uzerinde hareket saglanir.
*/
void Game::move(int p,bool flag,int card_select){
	int loc_i, loc_j; 
	int temp_i,temp_j,a,b;

	Player temp;
	temp.in_game = true;

	loc_i = players[p].loc_i; 
	loc_j = players[p].loc_j;

	temp.location(loc_i,loc_j);
/*	
	Eger oyunun en basiysa yani oyuncular daha mapin icerisine girmemisse girmeleri saglanir.
	Eger girmislerse bir ilerideki lokasyona hareketleri saglanir.
*/
	if(loc_i == 0 ) temp.loc_i++;
	else if(loc_i == 19) temp.loc_i--;
	else if(loc_j == 0) temp.loc_j += 2;
	else if(loc_j == 39) temp.loc_j -= 2;
	else restore_loc(temp);
	
	same_loc(temp,p);
/*
	Eger oyuna bir kart konulmussa flag 1 yani true olur. 
	Haritaya kart etkelemek icin add_card fonksiyonu cagirilir.
*/
	if(flag){
		players[p].location(temp.loc_i,temp.loc_j);
		add_card(p,card_select);
		temp.location(players[p].loc_i,players[p].loc_j);
	}
	same_loc(temp,p);
/*
	Eger oyuncu hareketler sonunda oyunda degil ise in_game'i yani oyunda mi bilgisi false yapilir ve fonksiyon bitirilir.
*/
	if(in_game(temp) == false){
		players[p].location(temp.loc_i,temp.loc_j);
		players[p].in_game = false;
		return;
	}

/* Kullanicinin onundeki hucre bos olmadigi surece hareketi saglanir. */
	while(is_empty(temp) == false){

		temp_i = (temp.loc_i - 1) % 6;	// loc karta gore ayarla
		temp_j = (temp.loc_j - 2) % 12;

		a = (temp.loc_i -1) / 6;		// loc duzeltmek icin
		b = (temp.loc_j - 2 ) / 12;

		get_card(temp).exit(temp_i,temp_j);
/* Harita ile kart arasindaki konum farkliliklari giderilir ve hareket saglanir */

		loc_i = temp_i + 1 + a * 6;	// loc mapa gore ayarla
		loc_j = temp_j + 2 + b * 12;

		temp.location(loc_i,loc_j);

		players[p].location(loc_i,loc_j);

		restore_loc(temp);
		same_loc(temp, p);
/* Eger hareket sonunda oyun disinda kalinirsa in_game false yapilir ve fonksiyon bitirilir. */
		if(in_game(temp) == false){
			players[p].location(temp.loc_i,temp.loc_j);
			players[p].in_game = false;
			break;
		}
		
	}

}
/*
	Hamle yapan oyuncunun diger oyunculardan herhangi biri ile ayni konumda olup olmadigina bakilir
	Eger ayni ise iki kullanicida kaybetmis sayilir.
 */
void Game::same_loc(Player& player, int p){

	for(int i=0;i<v_size;++i){
		if(i==p) continue;
		if(player.loc_i == players[i].loc_i &&
			player.loc_j == players[i].loc_j){

			player.in_game = false;
			players[i].in_game = false;
		}
	}

}
/* Oyundaki karti dondurmek icin bu fonksiyon cardin rotate'i cagirilir. */
void Game::rotate(int p,int card_select, int rot){
	players[p].cards[card_select].rotate(rot);
}