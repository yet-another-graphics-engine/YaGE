#ifndef BASE_POLY_H_KQTZGCRA
#define BASE_POLY_H_KQTZGCRA
#include "shape_property.h"
#include <vector>

namespace yage {
namespace draw {

class BasePoly {
	public:
		using Vertexes = std::vector<Point>; ///< Type for the container of all vertexes
		Vertexes vertex;	///< All vertexes
};

} // namespace draw
} // namespace yage
#endif /* end of include guard: BASE_POLY_H_KQTZGCRA */
