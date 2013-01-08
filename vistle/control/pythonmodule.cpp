#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <core/message.h>
#include "communicator.h"
#include "pythonmodule.h"
#include "pythonembed.h"

//#define DEBUG

namespace bp = boost::python;

BOOST_PYTHON_MODULE(vector_indexing_suite_ext){
   bp::class_<std::vector<int> >("PyVec")
      .def(bp::vector_indexing_suite<std::vector<int> >());
}

namespace vistle {

static void print_output(const std::string &str) {

   PythonEmbed::print_output(str);
}

static void print_error(const std::string &str) {

   PythonEmbed::print_error(str);
}

static std::string raw_input(const std::string &prompt) {

   return PythonEmbed::raw_input(prompt);
}

static std::string readline() {

   return PythonEmbed::readline();
}

static void source(const std::string &filename) {

   PythonEmbed::the().exec_file(filename);
}

static void quit() {

#ifdef DEBUG
   std::cerr << "Python: quit" << std::endl;
#endif
   message::Quit m(0, Communicator::the().getRank());
   Communicator::the().broadcastAndHandleMessage(m);
   Communicator::the().setQuitFlag();
}

static void ping(char c) {

#ifdef DEBUG
   std::cerr << "Python: ping: " << c << std::endl;
#endif
   message::Ping m(0, Communicator::the().getRank(), c);
   Communicator::the().broadcastAndHandleMessage(m);
}

static int spawn(const char *module, int debugflag=0, int debugrank=0) {

#ifdef DEBUG
   std::cerr << "Python: spawn "<< module << std::endl;
#endif
   int id = Communicator::the().newModuleID();
   message::Spawn m(0, Communicator::the().getRank(), id, module, debugflag, debugrank);
   Communicator::the().broadcastAndHandleMessage(m);
   return id;
}
BOOST_PYTHON_FUNCTION_OVERLOADS(spawn_overloads, spawn, 1 , 3)

static void kill(int id) {

#ifdef DEBUG
   std::cerr << "Python: kill "<< id << std::endl;
#endif
   message::Kill m(0, Communicator::the().getRank(), id);
   Communicator::the().broadcastAndHandleMessage(m);
}

static std::vector<int> getRunning() {

#ifdef DEBUG
   std::cerr << "Python: getRunning " << std::endl;
#endif
   return Communicator::the().getRunningList();
}

static std::vector<int> getBusy() {

#ifdef DEBUG
   std::cerr << "Python: getBusy " << std::endl;
#endif
   return Communicator::the().getBusyList();
}

static std::vector<std::string> getInputPorts(int id) {

   return Communicator::the().portManager().getInputPortNames(id);
}

static std::vector<std::string> getOutputPorts(int id) {

   return Communicator::the().portManager().getOutputPortNames(id);
}

static std::vector<std::pair<int, std::string> > getConnections(int id, const std::string &port) {

   std::vector<std::pair<int, std::string> > result;

   const PortManager::ConnectionList *c = Communicator::the().portManager().getConnectionList(id, port);
   for (size_t i=0; i<c->size(); ++i) {
      const Port *p = c->at(i);
      result.push_back(std::pair<int, std::string>(p->getModuleID(), p->getName()));
   }

   return result;
}

static std::vector<std::string> getParameters(int id) {

   return std::vector<std::string>();
}

static std::string getParameterValue(int id, const std::string &param) {
}

static std::string getModuleName(int id) {

#ifdef DEBUG
   std::cerr << "Python: getModuleName(" id << ")" << std::endl;
#endif
   return Communicator::the().getModuleName(id);
}

static void connect(int sid, const char *sport, int did, const char *dport) {

#ifdef DEBUG
   std::cerr << "Python: connect "<< sid << ":" << sport << " -> " << did << ":" << dport << std::endl;
#endif
   message::Connect m(0, Communicator::the().getRank(),
         sid, sport, did, dport);
   Communicator::the().broadcastAndHandleMessage(m);
}

static void setIntParam(int id, const char *name, int value) {

#ifdef DEBUG
   std::cerr << "Python: setIntParam " << id << ":" << name << " = " << value << std::endl;
#endif
   message::SetIntParameter m(0, Communicator::the().getRank(),
         id, name, value);
   Communicator::the().broadcastAndHandleMessage(m);
}

static void setFloatParam(int id, const char *name, double value) {

#ifdef DEBUG
   std::cerr << "Python: setFloatParam " << id << ":" << name << " = " << value << std::endl;
#endif
   message::SetFloatParameter m(0, Communicator::the().getRank(),
         id, name, value);
   Communicator::the().broadcastAndHandleMessage(m);
}

static void setVectorParam(int id, const char *name, double v1, double v2, double v3) {

#ifdef DEBUG
   std::cerr << "Python: setVectorParam " << id << ":" << name << " = " << v1 << " " << v2 << " " << v3 << std::endl;
#endif
   message::SetVectorParameter m(0, Communicator::the().getRank(),
         id, name, Vector(v1, v2, v3));
   Communicator::the().broadcastAndHandleMessage(m);
}

static void setFileParam(int id, const char *name, const std::string &value) {

#ifdef DEBUG
   std::cerr << "Python: setFileParam " << id << ":" << name << " = " << value << std::endl;
#endif
   message::SetFileParameter m(0, Communicator::the().getRank(),
         id, name, value);
   Communicator::the().broadcastAndHandleMessage(m);
}

static void compute(int id) {

#ifdef DEBUG
   std::cerr << "Python: compute " << id << std::endl;
#endif
   message::Compute m(0, Communicator::the().getRank(), id);
   Communicator::the().broadcastAndHandleMessage(m);
}

#define param(T, f) \
   def("set" #T "Param", f, "set parameter `arg2` of module with ID `arg1` to `arg3`"); \
   def("setParam", f, "set parameter `arg2` of module with ID `arg1` to `arg3`");

BOOST_PYTHON_MODULE(_vistle)
{
    using namespace boost::python;
    def("_readline", readline);
    def("_raw_input", raw_input);
    def("_print_error", print_error);
    def("_print_output", print_output);

    def("source", source, "execute commands from file `arg1`");
    def("spawn", spawn, spawn_overloads(args("modulename", "debug", "debugrank"), "spawn new module `arg1`\n" "return its ID"));
    def("kill", kill, "kill module with ID `arg1`");
    def("getRunning", getRunning, "get list of IDs of running modules");
    def("getBusy", getBusy, "get list of IDs of busy modules");
    def("getModuleName", getModuleName, "get name of module with ID `arg1`");
    def("getInputPorts", getInputPorts, "get name of input ports of module with ID `arg1`");
    def("getOutputPorts", getOutputPorts, "get name of input ports of module with ID `arg1`");
    def("getConnections", getConnections, "get connections to/from port `arg2` of module with ID `arg1`");
    def("connect", connect, "connect output `arg2` of module with ID `arg1` to input `arg4` of module with ID `arg3`");
    def("compute", compute, "trigger execution of module with ID `arg1`");
    def("quit", quit, "quit vistle session");
    def("ping", ping, "send first character of `arg1` to every vistle process");

    param(Int, setIntParam);
    param(Float, setFloatParam);
    param(File, setFileParam);
    param(Vector, setVectorParam);
}

bool PythonModule::import(boost::python::object *ns) {

   try {
      init_vistle();
   } catch (bp::error_already_set) {
      std::cerr << "vistle Python module initialisation failed" << std::endl;
      PyErr_Print();
      return false;
   }

   try {
      (*ns)["_vistle"] = bp::import("_vistle");
   } catch (bp::error_already_set) {
      std::cerr << "vistle Python module import failed" << std::endl;
      PyErr_Print();
      return false;
   }

   if (!PythonEmbed::the().exec("import vistle"))
      return false;
   if (!PythonEmbed::the().exec("from vistle import *"))
      return false;

   return true;
}

PythonModule::PythonModule(int argc, char *argv[])
{
}


PythonModule::~PythonModule() {
}

} // namespace vistle
