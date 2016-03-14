#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;



int main(){


	//1) get plain text file and store in memory
	//rd form file
	ifstream ifs;
	ifs.open("plaintext_dictionary.txt");
	if(!ifs){
		cerr << "failed to open plaintext_dictionary.txt" << endl;
		exit(1);
	}


	//get the number of plain texts in the file from the title
	string position, title, tmp;
	getline(ifs, title); //for the Plaintext Dictionary (5 plaintexts):
	stringstream ss;
	ss << title;
	string numPlaintxt = "";
	while(!ss.eof()){
		ss >> tmp;
		for(int i = 0; i < tmp.size(); ++i){
			if (isdigit(tmp[i])){
				numPlaintxt.push_back(tmp[i]);
			}
		}
	}

	//store the plaintext in a vector
	vector<string> ptvector;
	int value = atoi(numPlaintxt.c_str());
	string plainText, plainTextNumber, trash;
	for(int i = 0; i < value; ++i){
		getline(ifs, trash);						//White space
		getline(ifs, plainTextNumber);				//The Plaintext number
		getline(ifs, plainText);					//The Plaintext itself
		ptvector.push_back(plainText);
	}
	ifs.close();



	while(true){
		//2) get cipher text
		string input;
		cout << "Enter the ciphertext:";
		getline(cin, input);

		if(input == "exit"){
			break;
		}
	
		//3) split the cipher text by white space and words and add them to a vector
		istringstream buf(input);
		istream_iterator<string> beg(buf), end;
		vector<string> tokens(beg, end); // done!
		vector<string> ciphertext;


		for(auto& s: tokens){
			//std::cout << '"' << s << '"' << '\n';
			stringstream ss;
			while(ss << s){
				string letter;
				while(getline(ss, letter, ',')){
					ciphertext.push_back(letter);
				}
				ciphertext.push_back(" ");
			}
		}



		//4) check for similarities within the cipher text and record in a vector!!!
		vector<vector<int>> vectorOfpositions;
		for(size_t i = 0; i < ciphertext.size(); ++i){
			for(size_t j = 1; j < ciphertext.size(); ++j){
				if(ciphertext[i] == ciphertext[j]){
					vector<int> positions;
					positions.push_back(i);
					positions.push_back(j);
					vectorOfpositions.push_back(positions);
				}
			}
		}


		//5) compare the ciphertext with the planetext
		int count = 0;
		int max = 0;				// max numer of matches
		int postionOfMatch = 0;

		for(size_t j = 0; j < ptvector.size(); ++j){
			for(size_t i = 0; i < vectorOfpositions.size(); ++i){
				if(ptvector[j][vectorOfpositions[i][0]] == ptvector[j][vectorOfpositions[i][1]]){
					++count;
				}
			}
			if(count > max){
				max = count;
				count = 0;
				postionOfMatch = j;
			}
		}


		cout <<  "My plaintext guess is:" << ptvector[postionOfMatch] << endl;
	}
	return 0;
}
