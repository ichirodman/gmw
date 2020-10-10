#include "cacher.hpp"
#include "cache_config.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <functional>

#define CACHE_DIR "./cache"

void createDirectoryIfNotExist(std::string);

void writeTextRepr(std::string, int, SuffixTreeBuilder *);

void SuffixTreeCacher::cache(SuffixTree *suffixTree, std::string globalSampleName, int cachePartSerialNumber)
{
    createDirectoryIfNotExist(globalSampleName);
    writeTextRepr(globalSampleName, cachePartSerialNumber, suffixTree->builder);
}

void createDirectoryIfNotExist(std::string cacheSubdir)
{
    std::string const cacheDir = CACHE_DIR + std::string("/") + cacheSubdir;
    if (mkdir(cacheDir.c_str(), 0777) == -1)
    {
        std::cerr << "Error :  " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "Directory created" << std::endl;
    }
}

std::string getFormatedVertexTextRepr(SuffixTreeVertex *);

void writeTextRepr(std::string cacheSubdir, int cachePartSerialNumber, SuffixTreeBuilder *builder)
{
    std::string const filePath = CACHE_DIR + std::string("/") + cacheSubdir + std::string("/") +
                                 std::to_string(cachePartSerialNumber) + std::string(".") + CACHE_FILES_EXTENSION;
    std::ofstream outfile(filePath);
    std::function<void (SuffixTreeVertex *)> recursiveTreeWritingToFile;
    recursiveTreeWritingToFile = [&outfile, &recursiveTreeWritingToFile](SuffixTreeVertex *vertex) {
        std::string vertexTextRepr = getFormatedVertexTextRepr(vertex);
        outfile << vertexTextRepr << std::endl;
        for (int i = 0; i < vertex->getChildren()->size(); ++i)
        {
            SuffixTreeVertex *child = vertex->getChildren()->at(i);
            recursiveTreeWritingToFile(child);
        }
    };
    recursiveTreeWritingToFile(builder->getRoot());
    outfile.close();
}

std::string getFormatedVertexTextRepr(SuffixTreeVertex *vertex)
{
    std::pair<int, int> entryIndexAndSubstringLength = vertex->getInfo();
    int childrenAmount = vertex->getChildren()->size();
    return std::to_string(entryIndexAndSubstringLength.first) + "," + 
        std::to_string(entryIndexAndSubstringLength.second) + "," + 
        std::to_string(childrenAmount) + ";";
}
