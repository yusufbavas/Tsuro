#ifndef H_PLAYER
#define H_PLAYER

using std:: vector;

class Player{
	public:	
		void new_player();
		void location( int i, int j);	// Verilen lokasyonlari oyuncunun lokasyonu yapar.
		void get_location(int &i, int &j) const;	// Oyuncunun lokasyonuna verilen degerlere atar.	
		card get_card( int c) const;	//Oyuncunun istenen kartini return eder.
		bool cond() const;	// Oyuncunun ıyunda olup olmadigi bilgisini return eder
		const char get_token(); 

		friend class Game;
	private:
		vector <card> cards;
		char token;	
		int loc_i;
		int loc_j;
		bool in_game;
		static vector <char> selected_token;	// Tokenin her kullanici icin farkli olmasi icin tokenler tutulur.
		static int token_size;
};

#endif