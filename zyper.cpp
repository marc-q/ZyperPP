/*
 * zyper.cpp
 * Copyright (C) 2017  Marc Volker Dickmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;
#include "zyper.h"

Zyper::Zyper (const string& filename)
{
	// Read the file containing the words
	ifstream f (filename.c_str ());
	if (!f.is_open ())
	{
		cout << "ERROR: Can't open the file " << filename << "!\n";
		return;
	}
	
	string a;
	while (f >> a)
	{
		words.push_back (a);
	}
	f.close ();
	
	// Random device
	gen = mt19937 (rd ());
	dis = uniform_int_distribution<> (0, words.size () - 1);
	
	// Start the game
	gameloop ();
}

Zyper::~Zyper (void)
{
	words.clear ();
}

void
Zyper::wait (const int secs)
{
	this_thread::sleep_for (seconds (secs));
}

void
Zyper::countdown (void)
{
	cout << "3\n";
	wait (1);
	
	cout << "2\n";
	wait (1);
	
	cout << "1\n";
	wait (1);
	
	cout << "GO!\n";
}

void
Zyper::gameloop (void)
{
	// Print the rules
	cout << "Welcome to Zyper!\nType the given word correctly.\n"
	     << "Youve got 3 lifes and 1 minute.\nEach failure results in "
	     << "losing 1 life.\n";
	
	countdown ();
	
	// Variables
	int lifes = 3, tl = 60, words_correct = 0;
	size_t word;
	string word_in;
	system_clock::time_point t;
	
	while (lifes > 0)
	{
		// Select a random word to type
		word = dis (gen);
		cout << "\nType: " << words[word] << "\n";
		
		t = system_clock::now ();
		cin >> word_in;
		
		// Calculate the time left
		tl -= duration_cast<seconds>(system_clock::now () - t).count ();
		
		if (tl <= 0)
		{
			cout << "TIMES UP!\n";
			break;
		}
		
		if (word_in == words[word])
		{
			cout << "DONE " << tl << " seconds left!\n";
			++words_correct;
		}
		else
		{
			cout << "WRONG " << --lifes << " lifes left!\n";
		}
	}
	
	cout << "\n\nCorrect words: " << words_correct << "\n";
}

int
main (int argc, char *argv[])
{
	Zyper game (argc == 2 ? argv[1] : "lang_c.txt");
	return 0;
}
