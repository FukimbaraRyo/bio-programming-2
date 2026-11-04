#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#define NUM_TISSUES 68
#define NUM_GENES 19594

using namespace std;

void LoadExpressionFile(string file_name, vector<string>& tissue_name,
    vector<string>& gene_name, vector<vector<double> >& expression_matrix){

    ifstream ifs(file_name);
    if(!ifs){
        cerr << "Cannot open expression file:" << file_name << endl;
        exit(1);
    }
    string tmp;
    ifs >> tmp;

    for(int i=0; i<NUM_TISSUES; i++){
        ifs >> tissue_name[i];
    }
    for(int i=0; i<NUM_GENES; i++){
        ifs >> gene_name[i];
        for(int j=0; j<NUM_TISSUES; j++){
            ifs >> expression_matrix[i][j];
        }
    }
    ifs.close();
}
int main(void){
    vector<string> tissue_name(NUM_TISSUES);
    vector<string> gene_name(NUM_GENES);

    vector<vector<double>> expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0) );
    
    LoadExpressionFile("gene_expression.txt",tissue_name, gene_name, expression_matrix);

    vector<double> average(NUM_GENES, 0.0);

    for(int i = 0; i < NUM_GENES; i++){
        double sum = 0.0;
        for(int j = 0; j < NUM_TISSUES; j++){
            sum += expression_matrix[i][j];
        
        average[i] = sum / NUM_TISSUES;
        }
    }
    vector<double> original_a = average;

    sort(average.begin(), average.end(), greater<double>());

    cout << "平均発現量の上位5つ" << endl;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < NUM_GENES; j++) {
            if (average[i] == original_a[j]) {
                cout << gene_name[j] << " : " << average[i] << endl;
                break;
            }
        }
    }
    cout << "\n"<< endl;

    vector<double> variance(NUM_GENES, 0.0);

    for(int i = 0; i < NUM_GENES; i++){
        double sum = 0.0;
        for(int j = 0; j < NUM_TISSUES; j++){
            double diff = expression_matrix[i][j] - average[i];
            sum += diff * diff;
        }
        variance[i] = sum / NUM_TISSUES;
    }
    vector<double> score(NUM_GENES, 0.0);

    for(int i = 0; i < NUM_GENES; i++){
        score[i] = average[i] / (sqrt(variance[i]) + 0.01);
    }
    vector<double> original_s = score;

    sort(score.begin(), score.end(), greater<double>());

    cout << "scoreの上位5つ" << endl;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < NUM_GENES; j++) {
            if (score[i] == original_s[j]) {
                cout << gene_name[j] << " : " << score[i] << endl;
                break;
            }
        }
    }

    return 0;
}

