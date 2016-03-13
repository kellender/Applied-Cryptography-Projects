#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
using namespace std;





int main(){


	//1) read form the plaintext dictionary and store in memory
	ifstream ifs;
	ifs.open("plaintext_dictionary.txt");
	if(!ifs){
		cerr << "failed to open plaintext_dictionary.txt" << endl;
		exit(1);
	}

	//get the number of plain texts in the file
	string position, title, tmp;
	getline(ifs, title); //for the Plaintext Dictionary (5 plaintexts):
	cout << title << endl; 
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

	vector<vector<int>> vectorOfpositions;
	vector<string> ptvector;

	//store the plaon text in a vector
	int value = atoi(numPlaintxt.c_str());
	string plainText, plainTextNumber, trash;
	for(int i = 0; i < value; ++i){
		getline(ifs, trash); //White space
		getline(ifs, plainTextNumber); //The Plaintext number
		getline(ifs, plainText); //The Plaintext itself
		ptvector.push_back(plainText);

		//find the of the bs...
		vector<int> positions;
		int count = 0; // could use a bool instead...
		for(size_t i = 0; i < plainText.size(); ++i){
			if(plainText[i] == 'b' && count == 0){
				positions.push_back(i);
				++count;
			}
			else if(plainText[i] == 'b' && count == 1){
				positions.push_back(i);
				++count;
			}
		}
		vectorOfpositions.push_back(positions);
	}




	//2) get the cipher text form the input
	string ciphertext;
	cout << "Enter the ciphertext:";
	cin >> ciphertext;
	
	//4) loop through the plain text vector to see if the positions match
	for(int i = 0; i < vectorOfpositions.size(); ++i){
		if(ciphertext[vectorOfpositions[i][0] == ciphertext[vectorOfpositions[i][1]){
			cout << "My plaintext guess is:" << ptvector[i] << endl;
		}
	}

	ifs.close();

	return 0;
}
