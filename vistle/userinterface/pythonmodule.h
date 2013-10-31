#ifndef PYTHON_MODULE_H
#define PYTHON_MODULE_H

#include <string>
#include <boost/python/object.hpp>

#include "export.h"

namespace vistle {

class VistleConnection;

class V_UIEXPORT PythonModule {

public:
   PythonModule();
   PythonModule(VistleConnection *vc);
   static PythonModule &the();

   VistleConnection &vistleConnection() const;
   bool import(boost::python::object *m_namespace);

private:
   VistleConnection *m_vistleConnection;
   static PythonModule *s_instance;
};

} // namespace vistle

#endif