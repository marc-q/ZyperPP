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
#include "zyper.h"
using namespace std;
using namespace std::chrono;

Zyper::Zyper (string filename)
{
	// Set the default values
	this->lifes = 3;
	
	// Read the file containing the words
	ifstream f (filename.c_str());
	if (!f.is_open ())
	{
		cout << "ERROR: Can't open the file " << filename << "!\n";
		return;
	}
	
	string a;
	while (f >> a)
	{
		this->words.push_back (a);
	}
	
	// Random device
	this->gen = mt19937 (this->rd());
	this->dis = uniform_int_distribution<> (0, this->words.size() - 1);
	f.close ();
	
	// Start the game
	this->gameloop ();
}

Zyper::~Zyper (void)
{
	this->words.clear();
}

string&
Zyper::next_word (void)
{
	return this->words.at (this->dis (gen));
}

void
Zyper::wait (const unsigned short secs)
{
	this_thread::sleep_for (seconds (secs));
}

void
Zyper::countdown (void)
{
	cout << "1\n";
	this->wait (1);
	
	cout << "2\n";
	this->wait (1);
	
	cout << "3\n";
	this->wait (1);
	
	cout << "GO!\n";
}

void
Zyper::gameloop (void)
{
	// Print the rules
	cout << "Welcome to Zyper!\nType the given wrd correctly.";
	cout << "Youve got " << to_string (this->lifes) << " lifes. Each ";
	cout << "failure results in losing 1 life.\nYouve got 1 minute!\n";

	// Variables
	string word = "";
	string word_in = "";
	int words_correct = 0;
	
	this->countdown ();
	
	// Starttime
	system_clock::time_point t;
	int tl = 60;
	
	while (this->lifes > 0)
	{
		word = this->next_word ();
		cout << "Type: " << word << "\n";
		
		t = system_clock::now(); 
		cin >> word_in;
		
		// Calculate the time left
		tl -= duration_cast<seconds>(system_clock::now() - t).count();
		
		if (tl <= 0)
		{
			cout << "TIMES UP!\n";
			break;
		}
		
		if (word_in == word)
		{
			cout << "DONE " << to_string (tl) << " seconds left!\n";
			words_correct++;
		}
		else
		{
			cout << "WRONG! Lifes: " << --this->lifes << "\n";
		}
	}
	
	cout << "\n\nCorrect words: " << to_string (words_correct) << "\n";
}

int main (int argc, char const* argv[])
{
	Zyper game ((argc == 2 ?  (string)argv[1] : "lang_c.txt"));
	return 0;
}
