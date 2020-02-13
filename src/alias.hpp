#ifndef WRAPDEFORMER_ALIAS_HPP
#define WRAPDEFORMER_ALIAS_HPP

#include "Eigen/Dense"


using str = std::string;
using f3 = Eigen::Vector3f;

using Matrix = Eigen::Matrix<float, 3, 3, Eigen::ColMajor>;

using IntVector = std::vector<int>;
using f3Vector = std::vector<f3>;
using MatrixVector = std::vector<Matrix>;


#endif // WRAPDEFORMER_ALIAS_HPP