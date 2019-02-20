#ifndef H_GAME
#define H_GAME

using std::vector;

class Game{
	public:
		Game(); 
		Player* get_player(int c);	// Oyundaki kullanicilardan sira kendisinde olani return eder.
		const int player_num() const;	// Oyundaki toplam kullanici sayisini return eder.
		const int player_cond() const;	// Oyunda hala aktif olan oyuncu sayisini return eder.
		void move(int p,bool flag = 0, int card_select = 0);	// Oyunda hareketliligi saglar
		void same_loc(Player& player, int p);	// Oyunda iki veya daha fazla kullanicinin ayni konumda olmasi durumunu kontrol eder.
		void rotate(int p,int card_select, int rot);	// Oyuncunun kartinin dondurulmesini saglar.
		void restore_loc(Player& player);	//Lokasyonu karta gore ayarlar
		void print_board() const;	// Mapi ekrana yazdirir.
		void add_card(int p,int c);	// Oyuna kart ekler.
	private:
		card get_card(const Player& player) const;	// Mapte kullanicinin oldugu lokasyondaki karti return eder.
		bool in_game(Player& player);	// Oyuncunun oyunun aktif bolgesinde olup olmadigina bakilir.
		bool is_empty(const Player& player);	// Oyuncunun oldugu lokasyonun bos olup olmadigina bakilir.
		bool get_sp(int &x,int &y);	// Random bir baslangic noktasi veririlir.
		vector <Player> players;
		int v_size;		
		card cards[9];
		int map[20][40];
};

#endif