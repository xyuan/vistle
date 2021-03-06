#include "coords.h"

namespace vistle {

Coords::Coords(const Index numVertices,
             const Meta &meta)
   : Coords::Base(static_cast<Data *>(NULL))
{}

bool Coords::isEmpty() const {

   return Base::isEmpty();
}

bool Coords::checkImpl() const {

   return true;
}

Coords::Data::Data(const Index numVertices,
      Type id, const std::string &name,
      const Meta &meta)
   : Coords::Base::Data(numVertices,
         id, name,
         meta)
{
}

Coords::Data::Data(const Coords::Data &o, const std::string &n)
: Coords::Base::Data(o, n)
{
}

Coords::Data::Data(const Vec<Scalar, 3>::Data &o, const std::string &n, Type id)
: Coords::Base::Data(o, n, id)
{
}

Coords::Data *Coords::Data::create(Type id, const Index numVertices,
            const Meta &meta) {

   assert("should never be called" == NULL);

   return NULL;
}

Index Coords::getNumVertices() const {

   return getSize();
}

Index Coords::getNumCoords() const {

   return getSize();
}

V_SERIALIZERS(Coords);

} // namespace vistle
