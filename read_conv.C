#include "X3Data.cpp"
#include "StarkMap.cpp"

void read_conv()
{
    auto ana = new LKChannelAnalyzer();

    auto file = new TFile("stark_0044.D0.conv.root");
    auto tree = (TTree *) file -> Get("event");

    TClonesArray *channelArray = nullptr;
    tree -> SetBranchAddress("RawData", &channelArray);

    auto starkMap = new StarkMap("stark_map.txt");

    auto file2 = new TFile("test.root","recreate");
    auto tree2 = new TTree("event","");
    TClonesArray *x3Array = new TClonesArray("X3Data",25);
    tree2 -> Branch("x3",&x3Array);

    X3Data* x3Data;

    auto numEvents = tree -> GetEntries();
    //for (auto iEvent=0; iEvent<numEvents; ++iEvent)
    //for (auto iEvent=0; iEvent<10; ++iEvent)
    for (auto iEvent : {4})
    {
        tree -> GetEntry(iEvent); // channelArray update for event number = iEvent

        auto numChannels = channelArray -> GetEntries();
        for (auto iChannel=0; iChannel<numChannels; ++iChannel)
        {
            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////
            auto channel = (GETChannel*) channelArray -> At(iChannel);

            auto cobo = channel -> GetCobo();
            auto asad = channel -> GetAsad();
            auto aget = channel -> GetAget();
            auto chan = channel -> GetChan();
            auto buffer = channel -> GetWaveformY();

            ana -> Analyze(buffer);
            if (ana -> GetNumHits()>0)
            {
                double energy = ana -> GetAmplitude(0);

                int siID = 1;
                int joID = 0; // 0: junction-up, 1: junction-down, 2: ohmic
                starkMap -> GetSiID(cobo,asad,aget,chan, siID,joID);

                if (siID>=0)
                {
                    bool foundX3Data = false;
                    auto numX3Data = x3Array -> GetEntries();
                    for (auto iX3=0; iX3<numX3Data; ++iX3)
                    {
                        x3Data = (X3Data*) x3Array -> At(iX3);
                        if (x3Data->fSiID==siID) {
                            foundX3Data = true;
                            break;
                        }
                    }

                    if (!foundX3Data)
                        x3Data = (X3Data*) x3Array -> ConstructedAt(x3Array->GetEntries());

                    x3Data -> fSiID = siID;
                    if (joID==0) x3Data -> fJuncUEnergy = energy;
                    if (joID==1) x3Data -> fJuncDEnergy = energy;
                    if (joID==2) x3Data -> fOhmicEnergy = energy;

                    cout << iEvent << " " << cobo << " " << asad << " " << aget << " " << chan << " " << energy << endl;
                }
            }
            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////
        }
        tree2 -> Fill();
    }

    file2 -> Write();
}
