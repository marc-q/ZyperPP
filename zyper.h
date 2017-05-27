#ifndef __ZYPER_H__
#define __ZYPER_H__

class Zyper
{
	public:
		Zyper (std::string filename);
		virtual ~Zyper ();

	private:
		// Members
		int lifes;
		std::vector<std::string> words;
		std::random_device rd;
		std::mt19937 gen;
		std::uniform_int_distribution<> dis;
		
		
		// Methods
		std::string& next_word (void);
		void wait (const unsigned short);
		void countdown ();
		void gameloop ();
};

#endif // __ZYPER_H__
