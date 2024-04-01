#ifndef STARKMAP_HH
#define STARKMAP_HH

class StarkMap
{
    public:
        StarkMap(TString fileName = "stark_map.txt");
        ~StarkMap() {};
        void GetSiID(int cobo, int asad, int aget, int chan, int &siID, int &joID);

        const int fNumCobo = 3;
        const int fNumAsad = 4;
        const int fNumAget = 4;
        const int fNumChan = 68;

        int**** fSiIDMap;
        int**** fJOIDMap;

    ClassDef(StarkMap, 1);
};

#endif
