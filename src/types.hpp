#ifndef WRAPDEFORMER_TYPES_HPP
#define WRAPDEFORMER_TYPES_HPP

#include "Eigen/Dense"


using f32 = float;
using f64 = double;

using str = std::string;
using f3 = Eigen::Vector3f;

using Matrix = Eigen::Matrix<f32, 3, 3, Eigen::ColMajor>;

using IntVector = std::vector<int>;
using f3Vector = std::vector<f3>;
using MatrixVector = std::vector<Matrix>;


#endif //WRAPDEFORMER_TYPES_HPP