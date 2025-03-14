/**
 * @file common.hpp
 * @author Stan Merlijn
 * @brief In this file we define the common types and include the libraries we will use
 * @version 0.1
 * @date 2025-03-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

// Include the standard library
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>

// include glm library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Including openmp for parallelism
#include <omp.h>

// Define the types we will use
using color = glm::dvec3;
using dpoint3 = glm::dvec3;
using dvec3 = glm::dvec3;
