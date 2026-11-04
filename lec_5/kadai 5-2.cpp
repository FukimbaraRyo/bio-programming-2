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
    for(int i=0; i<NUM_TISSUES; i++){
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
    vector<double> tau(NUM_GENES, 0.0);
    vector<int> max_tissue(NUM_GENES, 0);
    vector<double> max_tpm(NUM_GENES, 0.0);

    for (int i = 0; i < NUM_GENES; i++) {
        double xmax = 0;
        int tissue = 0;
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

    }
}
