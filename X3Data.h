#ifndef X3DATA_HH
#define X3DATA_HH

#include "TObject.h"

class X3Data : public TObject
{
    public:
        X3Data() { Clear(); }
        ~X3Data() {}

        virtual void Clear();

        int fSiID = -1;
        int fJuncUEnergy = -1;
        int fJuncDEnergy = -1;
        int fOhmicEnergy = -1;

    ClassDef(X3Data, 1);
};

#endif
