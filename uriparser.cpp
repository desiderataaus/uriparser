
#include <uriparser.h>

/*Abstract URI element*/
//Constructor
//URIElement::URIElement(string& type)
//    : m_type(type),m_content("")
//{
//}
//
////Destructor
//URIElement::~URIElement()
//{
//}
//
////Return element type string
//string URIElement::GetType()
//{
//    return m_type;
//}
//
//string URIElement::GetContent()
//{
//    return m_content;
//}


/*Abstract URI parser*/
//Constructor
URIParser::URIParser(string& parsername)
 : m_type(parsername)
{
}

URIParser::~URIParser()
{
}

unique_ptr<URIParser> URIParser::GetParser(string &type)
{
    if (type.compare("Scheme") == 0){
        return unique_ptr<URIParser>(new URIParserScheme());
    }
    if (type.compare("UserName") == 0){
        return unique_ptr<URIParser>( new URIParserUserName());
    }
    if (type.compare("Password") == 0){
        return unique_ptr<URIParser>(new URIParserPassword());
    }
    if (type.compare("Host") == 0){
        return unique_ptr<URIParser>(new URIParserHost());
    }    
    if (type.compare("Port") == 0){
        return unique_ptr<URIParser>(new URIParserPort());
    }    
    if (type.compare("Path") == 0){
        return unique_ptr<URIParser>(new URIParserPath());
    }    
    if (type.compare("Query") == 0){
        return unique_ptr<URIParser>(new URIParserQuery());
    }        
    if (type.compare("Fragment") == 0){
        return unique_ptr<URIParser>(new URIParserFragment());
    }            

    return nullptr;
}

//default implement of ParseIt(URIParser*, string &)
//bool URIParser::ParseIt(URIElement* pElement, string &result){
//    return false;
//}

/*URI scheme element*/
//URIElementScheme::URIElementScheme()
//    : URIElement("Scheme")
//{
//}

/*URI scheme parser*/
//Constructor
URIParserScheme::URIParserScheme()
 : URIParser(string("Scheme"))
{
}

//implement ParseIt
bool URIParserScheme::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }
    
    std::size_t pos = uristring.find_first_of(':');

    if (pos == std::string::npos){

        return false;
    }
    
    string schemestr = uristring.substr(0, pos);

    pos = schemestr.find_first_of("/?#[]@");

    if (pos != std::string::npos){

        return false;
    }
    
    result = schemestr;

    return true;

}

/*URI authority element*/
//URIElementScheme::URIElementAuthority()
//    : URIElement("Authority")
//{
//}

/*URI scheme parser*/
//Constructor
URIParserAuthority::URIParserAuthority()
 : URIParser(string("Authority"))
{
}

//implement ParseIt
bool URIParserAuthority::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    std::size_t pos = uristring.find("//");

    if (pos == std::string::npos) {
        return false;
    }
    

    string authoritystr = uristring.substr(pos + 2);

    pos = authoritystr.find_first_of("/?#");

    if (pos != std::string::npos){

        authoritystr = authoritystr.substr(0, pos);
    }

    result = authoritystr;

    return true;

}

/*URI user name parser*/
//Constructor
URIParserUserName::URIParserUserName()
: URIParserAuthority()
{
    m_type = "UserName";
}

//implement ParseIt
bool URIParserUserName::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    string authoritystr = "";
    if (!URIParserAuthority::ParseIt(uristring, authoritystr)){
        return false;
    }

    std::size_t pos = authoritystr.find_first_of("@");

    if (pos == std::string::npos) {
        return false;
    }
    

    string userinfostr = authoritystr.substr(0, pos);

    pos = userinfostr.find(":");

    if (pos == std::string::npos) {
        return false;
    }

    string usernamestr = userinfostr.substr(0, pos);

    result = usernamestr;

    return true;

}

/*URI password parser*/
//Constructor
URIParserPassword::URIParserPassword()
 : URIParserAuthority()
{
    m_type = "Password";
}

//implement ParseIt
bool URIParserPassword::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    string authoritystr = "";
    if (!URIParserAuthority::ParseIt(uristring, authoritystr)){
        return false;
    }

    std::size_t pos = authoritystr.find_first_of("@");

    if (pos == std::string::npos) {
        return false;
    }
    

    string userinfostr = authoritystr.substr(0, pos);

    pos = userinfostr.find(":");

    if (pos == std::string::npos) {
        return false;
    }

    string usernamestr = userinfostr.substr(pos + 1);

    result = usernamestr;

    return true;

}

/*URI host parser*/
//Constructor
URIParserHost::URIParserHost()
 : URIParserAuthority()
{
    m_type = "Host";
}

//implement ParseIt
bool URIParserHost::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    string authoritystr = "";
    if (!URIParserAuthority::ParseIt(uristring, authoritystr)){
        return false;
    }

    std::size_t pos = authoritystr.find_first_of("@");

    if (pos == std::string::npos) {
        pos = 0;
    } else {
        pos = pos + 1;
    }
    

    string hoststr = authoritystr.substr(pos);

    pos = hoststr.rfind("::");

    if (pos == std::string::npos){
        
        pos = 1;
    } else {
    
        pos = pos + 2;
    }
    
    std::size_t endpos = hoststr.substr(pos).find_last_of(":");

    if (endpos != std::string::npos) {
        
        hoststr = hoststr.substr(0, pos + endpos);
    }

    result = hoststr;

    return true;

}

/*URI port parser*/
//Constructor
URIParserPort::URIParserPort()
 : URIParserAuthority()
{
    m_type = "Port";
}

//implement ParseIt
bool URIParserPort::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    string authoritystr = "";
    if (!URIParserAuthority::ParseIt(uristring, authoritystr)){
        return false;
    }

    std::size_t pos = authoritystr.find_last_of(":");

    if (pos == std::string::npos) {
        return false;
    }
    

    string portstr = authoritystr.substr(pos + 1);

    pos = portstr.find_first_of(":@");

    if (pos != std::string::npos) {
        return false;
    }

    result = portstr;

    return true;

}

/*URI path parser*/
//Constructor
URIParserPath::URIParserPath()
 : URIParser(string("Path"))
{
}

//implement ParseIt
bool URIParserPath::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    std::size_t pos = uristring.find_first_of(":");

    if (pos == std::string::npos) {
        return false;
    }

    string pathstr = uristring.substr(pos + 1);

    URIParserAuthority uriap;

    string authoritystr = "";
    uriap.ParseIt(pathstr, authoritystr);

    pos = 0;
    
    if (authoritystr.length() > 0){

        pos = pathstr.find(authoritystr);

        if (pos == std::string::npos) {
            return false;
        } else {

            pos = pos + authoritystr.length() + 1;
        }
        
    }

    pathstr = pathstr.substr(pos);

    pos = pathstr.find_first_of("?#");

    if (pos != std::string::npos){

        pathstr = pathstr.substr(0, pos);
    }

    result = pathstr;

    return true;

}

/*URI query parser*/
//Constructor
URIParserQuery::URIParserQuery()
 : URIParser(string("Query"))
{
}

//implement ParseIt
bool URIParserQuery::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    std::size_t pos = uristring.find_first_of("?");

    if (pos == std::string::npos) {
        return false;
    }
    

    string querystr = uristring.substr(pos + 1);

    pos = querystr.find_first_of("#");

    if (pos != std::string::npos){

        querystr = querystr.substr(0, pos);
    }

    result = querystr;

    return true;

}

/*URI fragment parser*/
//Constructor
URIParserFragment::URIParserFragment()
 : URIParser(string("Fragment"))
{
}

//implement ParseIt
bool URIParserFragment::ParseIt(string& uristring, string &result)
{

    if (uristring.empty() || 0 == uristring.length()){
        return false;
    }

    std::size_t pos = uristring.find_first_of("#");

    if (pos == std::string::npos) {
        return false;
    }
    
    result = uristring.substr(pos + 1);

    return true;

}