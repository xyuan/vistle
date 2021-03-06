#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include "shm.h"
#include "object.h"
#include "export.h"

namespace vistle {

class V_COREEXPORT PlaceHolder: public Object {
   V_OBJECT(PlaceHolder);

 public:
   typedef Object Base;

   PlaceHolder(const std::string &originalName, const Meta &originalMeta, const Object::Type originalType);

   void setReal(Object::const_ptr g);
   Object::const_ptr real() const;
   std::string originalName() const;
   Object::Type originalType() const;
   const Meta &originalMeta() const;

   V_DATA_BEGIN(PlaceHolder);
      boost::interprocess::offset_ptr<Object::Data> real;

      Data(const std::string & name, const std::string &originalName,
            const Meta &m, Object::Type originalType);
      ~Data();
      static Data *create();
      static Data *create(const std::string &originalName, const Meta &originalMeta, const Object::Type originalType);

      private:
      shm_name_t originalName;
      Meta originalMeta;
      Object::Type originalType;
   V_DATA_END(PlaceHolder);
};

} // namespace vistle

#ifdef VISTLE_IMPL
#include "placeholder_impl.h"
#endif
#endif
