#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "card.h"
#include "player.h"
#include "game.h"    

using namespace std;

int card::cards_size=0;	// static member
int Player::token_size = 0;
vector<card> card::cards;
vector <char> Player::selected_token;

int main(){
	srand(time(NULL));
	Game game;
	int i,j,rot;
	int player_num;
	int card_select;
	Player * player;
	for(i=0;game.player_cond() > 1;++i){
		system("cls");
		player_num = i % game.player_num();
		player = game.get_player(player_num);
		if(player->cond() == false)	continue;
	// Her oyuncunun ilk olarak onunde bir kart varsa o kart uzerinde oynamasi saglanir.
		game.move(player_num);
	// Eger bu hareket sonunda oyunun disina cikmis ise kaybetmis olur.
		if(player->cond() == false){
			cout<<"Player "<<player_num+1<<" (Token :"<<player->get_token()<<")"<<" out!!!"<<endl;
			system("pause");
			continue;
		}
	// Eger oyuncunun onu bossa oyun ekrani ve kartlari ekrana basilir ve oyuna koymak istedigi karti sorulur.
		cout<<"Player "<<player_num +1<<" (Token :"<<player->get_token()<<")"<<endl;
		game.print_board();
		for(j=0;j<3;++j){
			cout<<j+1<<endl;
			player->get_card(j).print_card();
		}
		
		do{
			cout<<"Select a card: (1 - 2 - 3) "<<endl;
			cin>>card_select;
			cin.clear();
			cin.ignore(100,'\n');
		}while(!(card_select <4 && card_select > 0));


		card_select--;
	// Sectigi karti dondurmek isteyip istemedigi sorulur.
		do{
			cout<<"Don't Rotate : 0\n90 degrees : 1\n180 degrees : 2\n270 degrees: 3"<<endl;
			cin>>rot;
			cin.clear();
			cin.ignore(100,'\n');
		}while(!(rot>=0 && rot <4));

		game.rotate(player_num,card_select,rot);
	// Yeni kart uzerinde hareket saglanir. Eger bu hareket sonunda oyundan cikarsa kaybetmis ilan edilir.
		game.move(player_num,1,card_select);


		if(player->cond() == false){
			cout<<"Player "<<player_num+1<<" (Token :"<<player->get_token()<<")"<<" out!!!"<<endl;
			system("pause");
			continue;
		}

	}
/* Oyunda kalan son kullanici kazanan ilan edilir. Eger hic kimse oyunda kalamamis ise kazanan olmaz. */
	for(i=0;i<game.player_num();++i){
		if(game.get_player(i)->cond() == true){
			cout<<"--- Player "<<i+1<<" Win ---"<<endl;
			break;
		}
		if(i==game.player_num()-1){
			cout<<"No Winner..."<<endl;
		}

	}

	return 0;
}