
#include "uriparser.h"
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char* argv[])
{

    //string uri1 = "abc://username:password@example.com:123/path/data?key=value&key2=value2#fragid1";
    //string uri1 = "urn:example:mammal:monotreme:echidna";

    if (1 == argc){
        cout << "Usage: uriparser URI string to parse"<<endl;
        cout << "For example, uriparser \"abc://username:password@example.com:123/path\""<<endl;
        return 0;
    }

    string uristr = argv[1];

    string typelist[] = {"Scheme", "UserName", "Host", "Path", "Password", "Query", "Fragment"};
    set<string> uritypes(begin(typelist), end(typelist));
    
    for (set<string>::iterator it=uritypes.begin(); it!=uritypes.end(); ++it){\
        
        string type = *it;

        std::unique_ptr<URIParser> pParser = URIParser::GetParser(type);
    
        string result = "Not set";

        if (pParser != nullptr){
            pParser->ParseIt(uristr, result);
        }

        cout<<type<<": "<<result<<endl;

        //delete pParser;
    }
    
	return 0;
}

