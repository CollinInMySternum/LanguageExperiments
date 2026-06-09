#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "scanner.cc"

using namespace std;

int main(int argc, char *argv[])
{
    std::filebuf fb;

    string fileString = "";

    if (argc == 1)
    {
        cout << "Please enter an input file as the second argument.\n";

        return 0;
    }

    if (fb.open(argv[1], std::ios::in))
    {
        cout << "Found file '" << argv[1] << "' in the current directory.\n";

        std::istream is(&fb);
        std::stringstream buffer;
        buffer << is.rdbuf();
        fileString = buffer.str();

        fb.close();

        Scanner newScanner = Scanner(fileString);
        newScanner.ScanTokens();

        for (Token Token : newScanner.tokens)
        {
            cout << Token.ToString() << '\n';
        }
    }
    else
    {
        cout << "Could not find file '" << argv[1] << "' in the current directory.\n";
    }

    return 1;
}