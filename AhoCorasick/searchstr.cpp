/** searchstr.cpp
 * @file        searchstr.cpp
 * @author      Zhang, Chenbo (zhangcb@bu.edu)
 * @brief
 * @version     1.0
 * @date        2021-12-06
 *
 * @copyright   Copyright (c) 2021 Zhang, Chenbo
 *
 * @warning     input format:   data has no limitation
 *                              Pattern start with numbers of Pattern at the first line, then goes with string Patterns
 */
#include "AhoCorasickAlg.hpp"
// first arg data, second Pattern
bool errorhandle(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    bool bInputCheck;
    string inData;
    string inPattern;
    string outlocation;
    string *pdata;
    int nPatternnum;
    string Pattern;
    ifstream inFile;
    ofstream outFile;
    /** errorhandle return bInputCheck fail if input invalid,
     *  use default input data and pattern instead
     */
    bInputCheck = errorhandle(argc, argv);
    if (bInputCheck) // input check success
    {
        inData = argv[1];
        inPattern = argv[2];
    }
    else
    {
        inData = "data";
        inPattern = "Pattern";
    }

    // set output location
    outlocation = "MatchedPattern";
    cout << "in data: " << inData << endl;
    cout << "in Pattern: " << inPattern << endl;

    /* here goes code that new a CAhoTree and match Patterns within data using it*/
    CAhoTree oAhoCorasick(false); // true for case sensitive

    // here openfile and give data input
    inFile.open(inData);
    string str((istreambuf_iterator<char>(inFile)),
               istreambuf_iterator<char>());
    pdata = &str;
    inFile.close();
    // cout << *pdata << endl;

    // here openfile and give Pattern input
    inFile.open(inPattern);
    while (getline(inFile, Pattern))
    {
        oAhoCorasick.AddPattern(Pattern);
    }

    oAhoCorasick.Redirecting();
    map<string, int> mapOutput = oAhoCorasick.SearchPattern(*pdata);
    outFile.open(outlocation);
    for (auto it : mapOutput)
    {
        cout << it.first << '\t';
        outFile << left << it.first << '\t';
        outFile << left << it.second << endl;
        cout << it.second << endl;
    }
    outFile.close();
    return 0;
}

bool errorhandle(int argc, char *argv[])
{
    try
    {
        if (argc == 3)
        {
            return true;
        }
        else
        {
            throw(argc);
        }
    }
    catch (int argc)
    {
        cout << "need 2 input, first data, second pattern" << endl;
        cout << "input automatically set as 'data' and 'pattern'" << endl;
        // assert(false);
        return false;
    }
    return false;
}
