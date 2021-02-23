# GMW or Genetic Magic Wand ![](https://img.icons8.com/ios/40/000000/fantasy.png)

##### The GMW is a simplified solution for making align of pair of bacterias' genomes.

## Setup

Before using the tool, you need to setup the system by downloading some libs for python. Use the prepared script:

<pre><code>sh setup.sh</code></pre>

## Using data

The tool works **only** with **fasta** files. You can find genomes' samples in the ncbi database:

[ncbi web-site](https://www.ncbi.nlm.nih.gov/) (https://www.ncbi.nlm.nih.gov/)

## Makefile

In the makefile you can find a few commands to interact with the tool.

To run align module for representation:

<pre><code>make main_algo</code></pre>

To run all of the tests:

<pre><code>make all_tests</code></pre>

To make a plot based on tool's output:

<pre><code>make slice_matches_plot</code></pre>

Finally, to clean the project:

<pre><code>make clean</code></pre>

All of said you can easily find in the Makefile.

## Sample

The main class you may be needed in is **ApproximateAligner** which is placed in **src/approximate_aligner/approximate_aligner.hpp**. So there is a sample of using this tool, which is exactly the content of **tests/align_module_test.cpp* file and it runs by a Makefile what was said in the previous paragraph. The sample:
 
<pre><code>
#include "../src/approximate_aligner/approximate_aligner.hpp"


int main() {
    std::string firstFilename = "large1/large_genome2.fasta", secondFilename = "large1/large_genome1.fasta";
    ApproximateAligner *aligner = new ApproximateAligner(firstFilename, secondFilename, 100);
    aligner->align();

    delete aligner;

    return 0;
}
</code></pre>
## P.S.
The repository updated regularly, so keep for updates.