#ifndef __ZYPER_H__
#define __ZYPER_H__

class Zyper
{
	public:
		Zyper (const string&);
		virtual ~Zyper ();
	private:
		// Members
		vector<string> words;
		random_device rd;
		mt19937 gen;
		uniform_int_distribution<> dis;
		
		// Methods
		void wait (const int);
		void countdown (void);
		void gameloop (void);
};

#endif // __ZYPER_H__
