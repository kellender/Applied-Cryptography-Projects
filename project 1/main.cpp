#include <iostream>
#include <vector>
#include<string>
#include<fstream>
#include<random>
#include <ctime>
using namespace std;
/*
This function checks if an int is in a vector. It's really trivial
*/
bool isInThere(vector<int> vec, int elem){
    for(size_t i = 0; i < vec.size(); i++){
        if (elem == vec[i]){
            return true;
        }
    }

    return false;
}

/*
This function sorts the words by their lengths. So we have a vector of string vectors where all the 1 letter, 2 letter,
3 letter, words, are sorted by size.
*/
void lengthWordSorter(vector<string> dict,vector<vector<string>>& dictByLength, int max_length){
    vector<int> lengthRec(max_length,0);

    for(size_t i=0; i< max_length; i++){
        vector<string> wordsOfSomeLength;
        dictByLength.push_back(wordsOfSomeLength);
    }


    for(size_t i = 0; i<dict.size(); i++){
        int strLen = (dict[i]).length();
        (dictByLength[strLen-1]).push_back(dict[i]);
    }
}

/*
I tried to randomly pick words from the text dictionary that would sum to be 500 characters but I don't
have it working right. I kind of messed up with the random function too. The problem is the sum of the characters is less than 500.
Like 489 instead of 500 so I don't know how to fix that problem. And my list of random words always starts with the same word.
*/
vector<string> createPlainText(vector<string>& dict, vector<vector<string>>& dictByLength){
    int sumLenString = 0;
    vector<string> plainTextVec;
    vector<int> indexAlreadyVisited;
    indexAlreadyVisited.push_back(-1);


    default_random_engine generator;
    uniform_int_distribution<int> dictDist(0,dict.size());

    while(sumLenString < 500 ){

        if(500-sumLenString>0 && 500-sumLenString < 10){
                //uniform_int_distribution<int> lengthDist(0, dictByLength[500-sumLenString].size());

                vector<string> tempVecString = dictByLength[500-sumLenString];

                //int temp = lengthDist(generator);
                int temp = rand() % dictByLength[500-sumLenString].size();
                plainTextVec.push_back(tempVecString[temp]);

                break;
            }

        //int random = dictDist(generator);
       // int random = rand() % dict.size();
        if(!isInThere(indexAlreadyVisited, dictDist(generator))){

            plainTextVec.push_back(dict[dictDist(generator)]);
            indexAlreadyVisited.push_back(dictDist(generator));

            sumLenString += (dict[dictDist(generator)]).length();
        }
    }
    for(size_t i = 0; i < plainTextVec.size(); i++){
        cout<<plainTextVec[i]<<endl;
    }
    return plainTextVec;
}

/*
This function returns a vector of vector ints that serve as the encryption for
the letters. So a gets 8 random numbers between 1 and 102, b gets 1 random number between 1 and 102 that is not
already used by a and so on for each character.n From this table we can encrypt a message. How it would work is that if
you read in the character a you randomly pink one of the eight numbers assigned to the "a" vector or in this case the first
vector of the vector of vector ints. That will be the encryption for that. Then repeat for each character.
*/
vector<vector<int>> genCryptTable(){
    vector<int> chooseIntsFrom;

    int numUniqueInts = 103;
    for(size_t i = 0; i < numUniqueInts; i++){
        chooseIntsFrom.push_back(i);
    }

    vector<vector<int>> cryptTable;


    // "a"
    vector<int> charNums0;
    for(size_t i=0; i<8; i++){

       int random = rand() % numUniqueInts;
       charNums0.push_back(chooseIntsFrom[random]);
       chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
       numUniqueInts--;
    }
    cryptTable.push_back(charNums0);


    //"b"
    vector<int> charNums1;
    int random = rand() % numUniqueInts;
    charNums1.push_back(chooseIntsFrom[random]);
    chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
    numUniqueInts -= 1;
    cryptTable.push_back(charNums1);

    //"c"
    vector<int> charNums2;
    for(size_t i=0; i<3; i++){

        int random = rand() % numUniqueInts;
        charNums2.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums2);


    //"d"
   vector<int> charNums3;
   for(size_t i=0; i<4; i++){

        int random = rand() % numUniqueInts;
        charNums3.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums3);

    //"e"
    vector<int> charNums4;
   for(size_t i=0; i<13; i++){

        int random = rand() % numUniqueInts;
        charNums4.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums4);

    //"f"
    vector<int> charNums5;
   for(size_t i=0; i<2; i++){

        int random = rand() % numUniqueInts;
        charNums5.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums5);

    //"g"
    vector<int> charNums6;
   for(size_t i=0; i<2; i++){

        int random = rand() % numUniqueInts;
        charNums6.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums6);

    //"h'
    vector<int> charNums7;
   for(size_t i=0; i<6; i++){

        int random = rand() % numUniqueInts;
        charNums7.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums7);

    //"i"
    vector<int> charNums8;
   for(size_t i=0; i<7; i++){

        int random = rand() % numUniqueInts;
        charNums8.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums8);


    //"j"
    vector<int> charNums9;
    int random1 = rand() % numUniqueInts;
    charNums9.push_back(chooseIntsFrom[random1]);
    chooseIntsFrom.erase(chooseIntsFrom.begin() + random1);
    numUniqueInts -= 1;
    cryptTable.push_back(charNums9);

    //"k"
    vector<int> charNums10;
    int random2 = rand() % numUniqueInts;
    charNums10.push_back(chooseIntsFrom[random2]);
    chooseIntsFrom.erase(chooseIntsFrom.begin() + random2);
    numUniqueInts -= 1;
    cryptTable.push_back(charNums10);

    //"l"
    vector<int> charNums11;
   for(size_t i=0; i<4; i++){

        int random = rand() % numUniqueInts;
        charNums11.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }
    cryptTable.push_back(charNums11);

    //"m"
    vector<int> charNums12;
   for(size_t i=0; i<2; i++){

        int random = rand() % numUniqueInts;
        charNums12.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }

    cryptTable.push_back(charNums12);

    //"n"
    vector<int> charNums13;
   for(size_t i=0; i<7; i++){


        int random = rand() % numUniqueInts;
        charNums13.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }

    cryptTable.push_back(charNums13);

    //"o"
    vector<int> charNums14;
   for(size_t i=0; i<8; i++){

        int random = rand() % numUniqueInts;
        charNums14.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums14);

    //"p"
    vector<int> charNums15;
   for(size_t i=0; i<2; i++){

        int random = rand() % numUniqueInts;
        charNums15.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }
    cryptTable.push_back(charNums15);

    //"q"
    vector<int> charNums16;
    int random3 = rand() % numUniqueInts;
    charNums16.push_back(chooseIntsFrom[random3]);
    chooseIntsFrom.erase(chooseIntsFrom.begin() + random3);
    numUniqueInts -= 1;
    cryptTable.push_back(charNums16);

    //"r"
    vector<int> charNums17;
   for(size_t i=0; i<6; i++){

        int random = rand() % numUniqueInts;
        charNums17.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }
    cryptTable.push_back(charNums17);

    //"s"
    vector<int> charNums18;
   for(size_t i=0; i<6; i++){

        int random = rand() % numUniqueInts;
        charNums18.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }
    cryptTable.push_back(charNums18);

    //"t"
    vector<int> charNums19;
   for(size_t i=0; i<9; i++){

        int random = rand() % numUniqueInts;
        charNums19.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }
    cryptTable.push_back(charNums19);

    //"u"
    vector<int> charNums20;
   for(size_t i=0; i<3; i++){

        int random = rand() % numUniqueInts;
        charNums20.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;

    }
    cryptTable.push_back(charNums20);

    //"v"
    vector<int> charNums21;
    int random4 = rand() % numUniqueInts;
    charNums21.push_back(chooseIntsFrom[random4]);
    chooseIntsFrom.erase(chooseIntsFrom.begin() + random4);
    numUniqueInts -= 1;
    cryptTable.push_back(charNums21);

    //"w"
    vector<int> charNums22;
   for(size_t i=0; i<2; i++){

        int random = rand() % numUniqueInts;
        charNums22.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }
    cryptTable.push_back(charNums22);

    //"x"
    vector<int> charNums23;
    int random5 = rand() % numUniqueInts;
    charNums23.push_back(chooseIntsFrom[random5]);
    chooseIntsFrom.erase(chooseIntsFrom.begin() + random5);
    numUniqueInts -= 1;
    cryptTable.push_back(charNums23);

    //"y"
    vector<int> charNums24;
   for(size_t i=0; i<2; i++){

        int random = rand() % numUniqueInts;
        charNums24.push_back(chooseIntsFrom[random]);
        chooseIntsFrom.erase(chooseIntsFrom.begin() + random);
        numUniqueInts-=1;
    }
    cryptTable.push_back(charNums24);

    //"z"
    vector<int> charNums25;
    int random6 = rand() % numUniqueInts;
    charNums25.push_back(chooseIntsFrom[random6]);
    chooseIntsFrom.erase(chooseIntsFrom.begin() + random6);
    numUniqueInts -= 1;
    cryptTable.push_back(charNums25);


    return cryptTable;

}

int main(){
    srand(time(0));
    ifstream ifs("dictionary.txt");

    if (!ifs) {
        cerr << "Could not open the file.\n";
    }

    //filling up dictionary vector
    string line;
    vector<string> dictionary;
    while (getline(ifs, line)) {
            if(!(line.empty())){
            dictionary.push_back(line);
            }
        }
    ifs.close();
    ifs.clear();

    int max = 0;
    for(size_t i = 0; i<dictionary.size(); i++){
        if((dictionary[i]).length() > max){
            max = (dictionary[i]).length();
        }
    }

    cout<<"Max length is: "<<max<<endl;


    cout<<"The number of words in the dictionary is: "<<dictionary.size()<<endl;

    vector<vector<string>> dictByLength;

    lengthWordSorter(dictionary,dictByLength,28);

    for(size_t i=0; i<dictByLength.size(); i++){
        cout<<"The number of "<<(i+1)<<" letter words are: "<<(dictByLength[i].size())<<endl;
    }

    //generates plain text
   cout<<"The plain text is: "<<endl;
   createPlainText(dictionary, dictByLength);

   //generates the crypt table that will be used for encryption
   cout<<"Crypt Table"<<endl;
   vector<vector<int>> cryptTable = genCryptTable();
   for(size_t i=0; i<cryptTable.size(); i++){
    for(size_t j=0; j<cryptTable[i].size(); j++ ){
        cout<<cryptTable[i][j]<<" ";
    }
    cout<<endl;
   }

    return 0;
}
