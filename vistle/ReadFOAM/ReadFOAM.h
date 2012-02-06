#ifndef READFOAM_H
#define READFOAM_H

#include <string.h>
#include "module.h"

class ReadFOAM: public vistle::Module {

 public:
   ReadFOAM(int rank, int size, int moduleID);
   ~ReadFOAM();

 private:
   /*
   vistle::Object * readObject(const int fd, const iteminfo * info,
                               uint64_t start);
   */
   vistle::Object * load(const std::string & casedir);
   virtual bool compute();
};

#endif