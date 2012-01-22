#ifndef MODULE_H
#define MODULE_H

#define MPICH_IGNORE_CXX_SEEK
#include <mpi.h>
#include <iostream>

#include <list>
#include <map>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace vistle {

typedef boost::interprocess::managed_shared_memory::handle_t shm_handle_t;

class Parameter;

namespace message {
class Message;
class MessageQueue;
}

class Object;

class Module {

 public:
   Module(const std::string &name,
          const int rank, const int size, const int moduleID);
   virtual ~Module();

   virtual bool dispatch();

 protected:

   bool createInputPort(const std::string & name);
   bool createOutputPort(const std::string & name);

   bool addFileParameter(const std::string & name, const std::string & value);
   void setFileParameter(const std::string & name, const std::string & value);
   const std::string * getFileParameter(const std::string & name);

   bool addObject(const std::string &portName, const shm_handle_t & handle);
   bool addObject(const std::string & portName, const void *p);
   message::MessageQueue *sendMessageQueue;

   std::list<vistle::Object *> getObjects(const std::string &portName);
   void removeObject(const std::string &portName, vistle::Object *object);

   const std::string name;
   const int rank;
   const int size;
   const int moduleID;

 protected:
   message::MessageQueue *receiveMessageQueue;
   bool handleMessage(const message::Message *message);

 private:
   bool addInputObject(const std::string & portName,
                       const shm_handle_t & handle);

   virtual bool addInputObject(const std::string & portName,
                               const Object * object);

   virtual bool compute() = 0;

   std::map<std::string, std::list<shm_handle_t> *> outputPorts;
   std::map<std::string, std::list<shm_handle_t> *> inputPorts;

   std::map<std::string, Parameter *> parameters;
};

} // namespace vistle

#define MODULE_MAIN(X) int main(int argc, char **argv) {        \
      int rank, size, moduleID;                                 \
      if (argc != 2) {                                          \
         std::cerr << "module missing parameters" << std::endl; \
         exit(1);                                               \
      }                                                         \
      MPI_Init(&argc, &argv);                                   \
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);                     \
      MPI_Comm_size(MPI_COMM_WORLD, &size);                     \
      moduleID = atoi(argv[1]);                                 \
      X module(rank, size, moduleID);                           \
      while (!module.dispatch());                               \
      MPI_Barrier(MPI_COMM_WORLD);                              \
      return 0;                                                 \
   }

#endif