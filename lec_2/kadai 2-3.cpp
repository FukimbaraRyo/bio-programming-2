#include <iostream>
#include <vector>
#include <string>
using namespace std;

double CalcGCContent(string seq){
    int gc = 0;
    for(int i=0; i<seq [i]; i++){
        for(int j=0; j<seq.length(); j++){
            if(seq[i][j] == "G" || seq[i][j] == "C"){
            gc++;
        }  
    }
}
if(gc / seq.length() >= 0.5){

}
}
int main(void){
    vector<string> sequences = {
        "ATGCGAT",
        "GCGCGCGC",
        "ATATATAC",
        "CCCGGGTT",
        "TTAACCGA"
    };

    //GC contentが50%以上の配列をhigh_gc_sequencesに格納する。
    vector<string> high_gc_sequences; 
    
    //この部分を適切に実装せよ。

    //結果の出力
    cout << "GC含量が50%以上の配列：" << endl;
    for(int i = 0; i < high_gc_sequences.size();i++){
        cout << high_gc_sequences[i] << endl;
    }
    return 0;
}
