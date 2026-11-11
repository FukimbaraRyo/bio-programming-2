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
            vector<double> distance(NUM_TRAIN);
            for(int j=0; j<NUM_TRAIN; j++){
                 distance[j] = CalcDistance(test_prob[i], train_prob[j]);
            }
            vector<bool> used(NUM_TRAIN, false);
            int count1 = 0;
            int count0 = 0;

            for(int n=0; n<k; n++){
                double min_distance = 100;
                int min_index = -1;
                for(int j=0; j<NUM_TRAIN; j++){
                    if(used[j] == false && distance[j] < min_distance){
                        min_distance = distance[j];
                        min_index = j;
                    }
                }
                used[min_index] = true;
                if(train_labels[min_index] == 1){
                    count1++;
                }
                if(train_labels[min_index] == 0){
                    count0++;
                }
            }
        int prediction = 0;
        if(count1 > count0){
            prediction = 1;
        }
        if(test_labels[i] == 1 && prediction ==1){
            TP++;
        }
        else if(test_labels[i] == 1 && prediction ==0){
            FN++;
        }
        else if(test_labels[i] == 0 && prediction ==1){
            FP++;
        }
        else if(test_labels[i] == 0 && prediction ==0){
            TN++;
        }
    }
    double sensitivity = (double)TP / (TP+FN);
    double specificity = (double)TN / (TN+FP);

    double balanced_accuracy = (sensitivity + specificity) / 2.0;
    cout << "k = " << k << endl;
    cout << "Balanced Accuracy: " << balanced_accuracy << endl;
    }
    return 0;
}


//実行結果↓
//k = 1
//Balanced Accuracy: 0.672675
//k = 3
//Balanced Accuracy: 0.67664
//k = 5
//Balanced Accuracy: 0.66712
//k = 7
//Balanced Accuracy: 0.667985