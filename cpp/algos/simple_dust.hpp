#pragma once

#include <string>
#include "../utils/fasta.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

void dust(FastaSequence const *seq, int min_len = 7, float score_increase_threshold = 2.25,
          float threshold_score_difference = 0.7, bool print_progress = false, bool debug = false);
