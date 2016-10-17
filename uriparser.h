
#include <string>
#include <vector>
#include <memory>

using namespace std;

//Abstract URI parser
class URIParser{
    public:
        URIParser(string&);
        virtual ~URIParser();
        virtual bool ParseIt(string&, string &) = 0;  

        inline string GetType() {return m_type;}

        static unique_ptr<URIParser> GetParser(string&);

    protected:
            
        string m_type;
};

//Scheme parser
class URIParserScheme: public URIParser {
  
    public:
        URIParserScheme();
        bool ParseIt(string&, string &);
};

//Authority parser
class URIParserAuthority: public URIParser {
  
    public:
        URIParserAuthority();
        virtual bool ParseIt(string&, string &);
};  


//User name parser
class URIParserUserName: public URIParserAuthority {
  
    public:
        URIParserUserName();
        virtual bool ParseIt(string&, string &);
};

//Password parser
class URIParserPassword: public URIParserAuthority {
  
    public:
        URIParserPassword();
        virtual bool ParseIt(string&, string &);
};

//host parser
class URIParserHost: public URIParserAuthority {
  
    public:
        URIParserHost();
        virtual bool ParseIt(string&, string &);
};

//Port parser
class URIParserPort: public URIParserAuthority {
  
    public:
        URIParserPort();
        virtual bool ParseIt(string&, string &);
};

//Path parser
class URIParserPath: public URIParser {
  
    public:
        URIParserPath();
        virtual bool ParseIt(string&, string &);
};


//Query parser
class URIParserQuery: public URIParser {
  
    public:
        URIParserQuery();
        virtual bool ParseIt(string&, string &);
};

//Fragment parser
class URIParserFragment: public URIParser {
  
    public:
        URIParserFragment();
        virtual bool ParseIt(string&, string &);
};

