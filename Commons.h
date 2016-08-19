#ifndef COMMONS_H
#define COMMONS_H

#include <QString>

#define SAFE_DELETE(p) if(p) delete p;
#define SAFE_DELETE_ARRAY(a) if(a) delete [] a;

namespace commons
{
    static QString sDataFile = "info.dat";

}

#endif // COMMONS_H
