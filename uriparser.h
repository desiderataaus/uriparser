
#include <string>
#include <vector>
#include <memory>

using namespace std;
//Abstract URI element
//class URIElement
//{
//    public:
//        URIElement(string&, string&);
//        virtual ~URIElement();
//        virtual string GetType();
//        virtual string GetContent();
//
//    protected:
//        string m_type;    
//        string m_content;
//};

//Abstract URI parser
class URIParser{
    public:
        URIParser(string&);
        virtual ~URIParser();
        //string Get();
        virtual bool ParseIt(string&, string &) = 0;  
        //virtual bool ParseIt(URIElement*, string &) = 0; 

        static unique_ptr<URIParser> GetParser(string&);

    protected:
            
        string m_type;
        //vector<string> m_vDelimiters;
};

//Scheme parser and element
//Scheme element
//class URIElementScheme: public URIElement{
//    public:
//        URIElementScheme();
//    
//};

//Scheme parser
class URIParserScheme: public URIParser {
  
    public:
        URIParserScheme();
        bool ParseIt(string&, string &);
};

//Authority parser and element
//Authority element
//class URIElementAuthority : public URIElement{
//    public:
//        URIElementAuthority();
//
//};

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

