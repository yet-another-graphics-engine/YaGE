#include "yage.h"
#include "core/window.h"

int main(int argc, char **argv)
{
  return yage::core::Window::init(yage_main);
}
