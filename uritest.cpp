
#include "uriparser.h"
#include <iostream>
#include <set>

using namespace std;

void ParseAndDispay(std::unique_ptr<URIParser> pParser, string& URIstring)
{
    string result = "Not set";

    if (pParser != nullptr){
        
        pParser->ParseIt(URIstring, result);
    }

    cout<<pParser->GetType()<<": "<<result<<endl;    
}

void ParseURI(string& URIstring, set<string>& typeset)
{
    for (set<string>::iterator it=typeset.begin(); it!=typeset.end(); ++it){\
        
        string type = *it;

        std::unique_ptr<URIParser> pParser = URIParser::GetParser(type);
    
        if (pParser == nullptr){
            cout << type << " is not a valid type. Ignore it."<<endl;
            continue;
        }

        ParseAndDispay(move(pParser), URIstring);
    }    
}

int main(int argc, char* argv[])
{


    if (argc < 2){
        cout << "Usage: uriparser \"URI string\" [type list]"<<endl;
        cout << "For example, uriparser \"abc://username:password@example.com:123/path\" Scheme Host"<<endl;
        return 0;
    }

    string uristr = "";
    if (argc > 1){
        uristr = argv[1];
    }

    set<string> uritypes;
    if (argc > 2){
        
        for(int i = 2; i < argc; i++){
            uritypes.insert(argv[i]);
        }
    
        cout<<"Parsing URI string based on input typelist..."<<endl;

        ParseURI(uristr, uritypes);

        cout << endl;
    }
    
    cout<<"Parsing URI string based on preset typelist..."<<endl;
    uritypes.clear();

    string typelist[] = {"Scheme", "UserName", "Host", "Path", "Password", "Query", "Fragment"};
    uritypes = std::set<string>(begin(typelist), end(typelist));

    ParseURI(uristr, uritypes);
    cout << endl;

    cout<<"Parsing URI string by specified types"<<endl;

    ParseAndDispay(unique_ptr<URIParser>(new URIParserUserName), uristr);
    ParseAndDispay(unique_ptr<URIParser>(new URIParserPassword), uristr);
    cout << endl;
   
	return 0;
}

