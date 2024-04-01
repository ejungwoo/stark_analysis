#include "StarkMap.h"

StarkMap::StarkMap(TString fileName)
{
    fSiIDMap = new int***[fNumCobo];
    for(int i=0; i<fNumCobo; ++i) {
        fSiIDMap[i] = new int**[fNumAsad];
        for(int j=0; j<fNumAsad; ++j) {
            fSiIDMap[i][j] = new int*[fNumAget];
            for(int k=0; k<fNumAget; ++k) {
                fSiIDMap[i][j][k] = new int[fNumChan];
                for(int l=0; l<fNumChan; ++l) {
                    fSiIDMap[i][j][k][l] = -1;
                }
            }
        }
    }

    fJOIDMap = new int***[fNumCobo];
    for(int i=0; i<fNumCobo; ++i) {
        fJOIDMap[i] = new int**[fNumAsad];
        for(int j=0; j<fNumAsad; ++j) {
            fJOIDMap[i][j] = new int*[fNumAget];
            for(int k=0; k<fNumAget; ++k) {
                fJOIDMap[i][j][k] = new int[fNumChan];
                for(int l=0; l<fNumChan; ++l) {
                    fJOIDMap[i][j][k][l] = -1;
                }
            }
        }
    }

    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "ERROR!! " << fileName << " is not valid!" << endl;
        return;
    }

    int cobo, asad, aget, chan, si, jo;

    while (file >> cobo >> asad >> aget >> chan >> si >> jo)
    {
        fSiIDMap[cobo][asad][aget][chan] = si;
        fJOIDMap[cobo][asad][aget][chan] = jo;
    }
}

void StarkMap::GetSiID(int cobo, int asad, int aget, int chan, int &siID, int &joID)
{
    siID = fSiIDMap[cobo][asad][aget][chan];
    joID = fJOIDMap[cobo][asad][aget][chan];
}
