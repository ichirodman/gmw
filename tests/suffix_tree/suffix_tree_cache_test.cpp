#include "../../source/suffix_tree/cache/cacher.hpp"
#include "../../source/suffix_tree/cache/cache_extractor.hpp"
#include "../../source/suffix_tree/cache/cache_file_format.hpp"
#include <assert.h>
#include <string>

// Do not change definitions to avoid assertions' failatures
#define TEST_STRING "abacaba" 
#define TEST_GLOBAL_CACHE_DIRNAME "cacher_test"

void cacheSuffixTreeTest();

void extractSuffixTreeCacheTest();

void functionalSuffixTreeCacheTest();

int main() {
    cacheSuffixTreeTest();
    extractSuffixTreeCacheTest();
    functionalSuffixTreeCacheTest();
    return 0;
}

void assertOutputFileContentEqualsToExpected();

void cacheSuffixTreeTest() {
    SuffixTree *st = new SuffixTree(TEST_STRING);
    SuffixTreeCacher *stc = new SuffixTreeCacher();

    stc->cache(st, TEST_GLOBAL_CACHE_DIRNAME, 0);

    assertOutputFileContentEqualsToExpected();

    delete st, stc;
}

void extractSuffixTreeCacheTest() {
    std::string testCacheDirPath = CACHE_DIR + std::string("/") +
        TEST_GLOBAL_CACHE_DIRNAME;
    SuffixSubtreeCache * ssc = new SuffixSubtreeCache(testCacheDirPath, 0);

    SuffixTree * extractedSuffixTree = ssc->translateSuffixTreeMask();

    // TODO
    assert(true);

    delete ssc, extractedSuffixTree;
}

void functionalSuffixTreeCacheTest() {
    std::string testCacheDirPath = CACHE_DIR + std::string("/") +
        TEST_GLOBAL_CACHE_DIRNAME;
    SuffixTreeCacheExtractor * stce = new SuffixTreeCacheExtractor(testCacheDirPath);

    assert(true);

    delete stce;
}

void assertOutputFileContentEqualsToExpected() {
    std::string const testCacheFilePath = CACHE_DIR + std::string("/") +
        TEST_GLOBAL_CACHE_DIRNAME + std::string("/") +
        std::string("0") + std::string(".") + CACHE_FILES_EXTENSION;

    std::ifstream testCacheFile(testCacheFilePath);
    std::string description, sequenceSource, suffixTreeCache;

    getline(testCacheFile, description);
    getline(testCacheFile, sequenceSource);
    getline(testCacheFile, suffixTreeCache);

    testCacheFile.close();

    std::string descriptionExpected = DEFAULT_SEQUENCE_DESCRIPTION,
                sequenceSourceExpected = TEST_STRING + std::string("$"),
                suffixTreeCacheExpected = "0,0,4;7,1,0;6,1,3;7,1,0;3,5,0;5,2,2;7,1,0;3,5,0;3,5,0;5,2,2;7,1,0;3,5,0;";

    assert(sequenceSource == sequenceSourceExpected);
    assert(description == descriptionExpected);
    assert(suffixTreeCache == suffixTreeCacheExpected);
}
