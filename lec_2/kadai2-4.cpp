#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main(void){
    ifstream ist("human_protein_interaction.txt");

    string line;
    map<string, int> count;

    while (getline(ist, line)){
        int pos = line.find(' ');

        string p1 = line.substr(0, pos);
        string p2 = line.substr(pos + 1);

        count[p1]++;
        count[p2]++;
    }
    string maxProtein;
    int maxCount = 0;

    for(map<string, int>::const_iterator p = count.begin(); p != count.end(); p++){
        if(p->second > maxCount){
            maxProtein = p->first;
            maxCount = p->second;
        }
    }
    cout << maxProtein << " " << maxCount << endl;

    return 0;
}