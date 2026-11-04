#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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

    vector<int> count(NUM_TISSUES, 0);
    vector<double> tau(NUM_GENES, 0);
    vector<int> max_tissue(NUM_GENES, 0);
    vector<double> max_tpm(NUM_GENES, 0);

    for (int i = 0; i < NUM_GENES; i++) {
        double xmax = 0;
        int tissue;
        for (int j = 0; j < NUM_TISSUES; j++) {
            if (expression_matrix[i][j] > xmax) {
                xmax = expression_matrix[i][j];
                tissue = j;
            }
        }
        max_tissue[i] = tissue;
        max_tpm[i] = xmax;

        if (xmax == 0) {
            continue;
        }
        for (int j = 0; j < NUM_TISSUES; j++) {
            tau[i] += 1 - expression_matrix[i][j] / xmax;
        }
        tau[i] /= (NUM_TISSUES - 1);

        if(tau[i] >= 0.85){
            count[tissue]++;
        }
    }
    int most_tissue = 0;

    for (int j = 1; j < NUM_TISSUES; j++) {
        if (count[j] > count[most_tissue]) {
            most_tissue = j;
        }
    }
    cout << "組織特異的発言遺伝子数が最も多い組織: "<< tissue_name[most_tissue] << endl;
    cout << "遺伝子数: " << count[most_tissue] << endl;

    cout << "特異性が高く、TPMも高い遺伝子" << endl;
    for (int i = 0; i < NUM_GENES; i++) {
    if (tau[i] >= 0.95 && expression_matrix[i][most_tissue] >= 1000) {
        cout << gene_name[i] << endl;
    }
}
return 0;
}

