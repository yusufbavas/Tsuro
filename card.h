#ifndef H_CARD
#define H_CARD


using std::vector;

class card{
	public:
		card(); // Kartin yapisi ayarlanir.
		bool set_card(); // Kartin potlarina random degerler atilir.
		void get_card(int result[][12]) const; // Karti verilen arreye kopyalar.
		void rotate( int x); // Karti dondurur
		void exit(int &x, int &y); 	// Verilen giris kordinatlarindan kartin cikis kordinatlarini bulur.
		void empty(); // Kartin tum elemanlarina space atar
		void print_card() const;	// Karti ekrana yazdirir.
		void card_restart();	// Karti baslangic haline geri getirir.
		bool operator ==(const card& x) const;

		friend class Game;
	private:
		bool is_eq(int arr[], int x,int y); 
		int a_card[6][12];
		static vector <card> cards;
		static int cards_size;
		
};

#endif