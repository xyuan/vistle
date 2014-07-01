#include <module/module.h>
#include <core/points.h>

using namespace vistle;

class ColorAttribute: public vistle::Module {

 public:
   ColorAttribute(const std::string &shmname, int rank, int size, int moduleID);
   ~ColorAttribute();

 private:
   virtual bool compute();

   StringParameter *p_color;
};

using namespace vistle;

ColorAttribute::ColorAttribute(const std::string &shmname, int rank, int size, int moduleID)
: Module("add color attribute", shmname, rank, size, moduleID)
{

   Port *din = createInputPort("data_in", "input data", Port::MULTI);
   Port *dout = createOutputPort("data_out", "output data", Port::MULTI);
   din->link(dout);

   p_color = addStringParameter("color", "hexadecimal RGB values", "#ff00ff");
}

ColorAttribute::~ColorAttribute() {

}

bool ColorAttribute::compute() {

   //std::cerr << "ColorAttribute: compute: execcount=" << m_executionCount << std::endl;

   auto color = p_color->getValue();
   while(Object::const_ptr obj = takeFirstObject("data_in")) {

      Object::ptr out = obj->clone();
      out->addAttribute("_color", color);

      addObject("data_out", out);
   }

   return true;
}

MODULE_MAIN(ColorAttribute)
