#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <set>

namespace vistle {

class Port {

 public:
   enum Type { ANY = 0, INPUT = 1, OUTPUT = 2 };

   Port(int moduleID, const std::string &name, const Port::Type type);
   int getModuleID() const;
   const std::string & getName() const;
   Type getType() const;

 private:
   const int moduleID;
   const std::string name;
   const Type type;
};


class PortManager {

 public:
   PortManager();
   Port * addPort(const int moduleID, const std::string & name,
                  const Port::Type type);

   void addConnection(const Port * out, const Port * in);
   void addConnection(const int a, const std::string & na,
                      const int b, const std::string & nb);

   typedef std::vector<const Port *> ConnectionList;

   const ConnectionList *getConnectionList(const Port * port) const;
   const ConnectionList *getConnectionList(const int moduleID,
                                                       const std::string & name)
      const;

   Port * getPort(const int moduleID, const std::string & name) const;

   std::vector<std::string> getPortNames(const int moduleID, Port::Type type) const;
   std::vector<std::string> getInputPortNames(const int moduleID) const;
   std::vector<std::string> getOutputPortNames(const int moduleID) const;

 private:

   // module ID -> list of ports belonging to the module
   std::map<int, std::map<std::string, Port *> *> ports;

   // port -> list of ports that the port is connected to
   std::map<const Port *, std::vector<const Port *> *> connections;
};
} // namespace vistle

#endif
