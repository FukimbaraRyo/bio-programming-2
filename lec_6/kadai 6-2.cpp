#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

#define NUM_TRAIN 11892
#define NUM_TEST 740

void LoadSequenceFile(string file_name, vector<string>& sequences,
    vector<int>& labels){

    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Cannot open sequence file:" << file_name << endl;
        exit(1);
    }
    int tmp;
    ifs >> tmp;

    for(int i=0; i<sequences.size(); i++){
        ifs >> sequences[i] >> labels[i];
    }
    ifs.close();
}

vector<double> CalcAAProb(string seq, map<char, int>& aa_to_index){

    vector<double> aa_prob(20, 0.0);

    for(int i=0; i<seq.size(); i++){
        aa_prob[aa_to_index[seq[i]]] += 1.0 / seq.size();
    }

    return aa_prob;
}

double CalcDistance(vector<double> prob1, vector<double> prob2){
    double distance = 0.0;

    for(int i=0; i<20; i++){
        distance += (prob1[i] - prob2[i]) * (prob1[i] - prob2[i]);
    }
    return sqrt(distance);
}

int main(void){
    vector<string> train_sequences(NUM_TRAIN);
    vector<int> train_labels(NUM_TRAIN);
    vector<string> test_sequences(NUM_TEST);
    vector<int> test_labels(NUM_TEST);

    LoadSequenceFile("train_mitochondrion_cytoplasm_dataset.txt",
        train_sequences, train_labels);

    LoadSequenceFile("test_mitochondrion_cytoplasm_dataset.txt",
        test_sequences, test_labels);

    string aa_order = "ACDEFGHIKLMNPQRSTVWY";
    map<char, int> aa_to_index;
    for(int i=0; i<20; i++){
        aa_to_index[aa_order[i]] = i;
    }

    vector<vector<double>> train_prob(NUM_TRAIN, vector<double>(20, 0.0));

    for(int i=0; i<NUM_TRAIN; i++){
        train_prob[i] = CalcAAProb(train_sequences[i].substr(0, 30), aa_to_index);
    }
    vector<vector<double>> test_prob(NUM_TEST, vector<double>(20, 0.0));

    for(int i=0; i<NUM_TEST; i++){
        test_prob[i] = CalcAAProb(test_sequences[i].substr(0, 30), aa_to_index);
    }

    for(int k=1; k<=7; k+=2){
        int TP = 0;
        int FN = 0;
        int FP = 0;
        int TN = 0;

        for(int i=0; i<NUM_TEST; i++){
            vector<double> distances(NUM_TRAIN);
            for(int j=0; j<NUM_TRAIN; j++){
                distances[j] = CalcDistance(test_prob[i], train_prob[j]);
            }
        }
    }
}