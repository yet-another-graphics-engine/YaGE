#include "yage.h"
#include "window/window.h"

namespace yage {

int argc;
char **argv;

}  // namespace yage

int main(int argc, char **argv)
{
  yage::argc = argc;
  yage::argv = argv;
  return yage::window::Window::init(yage_main);
}
