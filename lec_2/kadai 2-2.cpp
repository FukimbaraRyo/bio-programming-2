#include <iostream>
#include <string>
using namespace std;

int HammingDistance(string a, string b){
    if(a.length() != b.length()){
        return -1;
    }
    int distance = 0;
    for(int i=0; i<a.length(); i++){
        if(a[i] != b[i]){
            distance ++;
        }
    }
    return distance;
}

int main(void){
    string a = "AACCGT";
    string b = "AATCAT";
    string c = "AACCG";

    int dist1 = HammingDistance(a, b);
    if (dist1 != -1) {
        cout << "Hamming Distance: " << dist1 << endl;
    }else{
        cout << "The two strings have different lengths." << endl;
    }
    int dist2 = HammingDistance(a, c);
    if (dist2 != -1) {
        cout << "Hamming Distance: " << dist2 << endl;
    }else{
        cout << "The two strings have different lengths." << endl;
    }

    return 0;
}