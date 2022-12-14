#pragma once
#include <string>
#include <random>
#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <iomanip>
#include "../Generator/Generator.h"
#include "../Hasher/Hasher.h"
#include "../Timer/Timer.h"
#include "../File/File.h"

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

typedef string hashVal;
typedef vector<string> originalVal;

#include <algorithm>

template <typename T>
void remove_duplicates(std::vector<T> &vec)
{
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}
struct AvalancheTestArr
{
    string s1;
    string s2;
    string h1;
    string h2;

    AvalancheTestArr(string s1, string s2, string h1, string h2) : s1(s1), s2(s2), h1(h1), h2(h2){};
};

class Tester
{
public:
    void runCollisionTest(size_t count, size_t symbolCount, string resFileName);
    void runCollisionTestByPairs(string resFileName);
    void runSpeedTest(size_t symbolCount);
    void testKonstitucija();
    void testAvalanche();

private:
    map<hashVal, originalVal> hashes;
    map<hashVal, originalVal> collisions;

    Generator gen;
    Hasher hasher;
    Timer timer;
    File fileReader;

    void testSpeed(size_t symbolCount);
    void testCollisions(string resFileName);
    int testCollisionsByPairs(stringstream &out_ss, size_t symbolCount);
    void generateStringsAndHashes(size_t count, size_t symbolCount);

    int LevenshteinDistance(string a, string b);
    double CalculateSimilarity(string source, string target);
};