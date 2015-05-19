#include "yage.h"
#include "window/window.h"

int main(int argc, char **argv)
{
  return yage::window::Window::init(yage_main);
}
