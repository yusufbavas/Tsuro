#include <iostream>
#include <vector>
#include "card.h"  
#include "player.h"

using namespace std;

/* Oyuncunun tokeni sorulur. Oyunda bilgisi ayarlanir ve eline 3 tane kart verilir. */
void Player::new_player(){
	card x;
	int i;
	cout<<"What is your token ?"<<endl;
	cin>>token;

	cin.clear();
	cin.ignore(100,'\n');
	if(token_size == 0){
		selected_token.push_back(token);
	}
	for(i=0;i<token_size;++i){
		if(selected_token[i] == token){
			cout<<"You can't use this token"<<endl;
			cout<<"What is your token ?:"<<endl;
			cin>>token;
			cin.clear();
			cin.ignore(100,'\n');
			i=-1;
		}

	}
	selected_token.push_back(token);
	token_size++;
	

	in_game= true;
	for(i=0;i<3;++i){
		if(x.set_card() == false){
			i--;
			continue;
		}
		cards.push_back(x);	
		x.card_restart();
	}	
}
// Oyuncunun konumuna verilen degerleri atar
void Player::location(int x, int y){	
	loc_i = x;
	loc_j = y;
}
// Oyuncunun konumumu verilen degerlere atar
void Player::get_location(int &i, int& j) const{	
	i = loc_i;
	j = loc_j;
}
// Oyuncunun elindeki kartlardan istenilen kart dondurulur.
card Player::get_card( int c) const{
	return cards[c];
}
// Oyuncunun oyunda olup olmadigi bilgisi dondurulur.
bool Player::cond() const{
	bool result = true;
	if(in_game == false) result = false;
	return result;
}
const char Player::get_token(){
	return token;
} 