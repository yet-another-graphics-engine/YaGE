#include "yage.h"
#include "core/window.h"

namespace yage {
namespace core {

yage::util::Runner gtk_runner;

}  // namespace core
}  // namespace yage

extern "C" int yage_main(void);

int main(int argc, char **argv)
{
  return yage::core::Window::init(yage_main);
}
