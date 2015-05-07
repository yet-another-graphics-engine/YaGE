#ifndef POLY_H_KQTZGCRA
#define POLY_H_KQTZGCRA
#include "basic_shape.h"
#include <vector>


namespace yage {
namespace draw {

class Poly : public BasicShape {
	public:
		using Vertexes = std::vector<Point>; ///< Type for the container of all vertexes
		Vertexes vertex;	///< All vertexes
	    Poly(std::string name="");
};

} // namespace draw
} // namespace yage
#endif /* end of include guard: POLY_H_KQTZGCRA */
