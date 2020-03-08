#ifndef REG_URL__H
#define REG_URL__H

#include <string>
using namespace std;

class regurl
{
public:
	regurl();
	~regurl();

	// normalize the url
	string CNormalize(const string &str_in);
private:
	// the url that parsed resutl
	string parsed_url;
	string scheme;
	string host;
	string port;
	string domain;

	// preprocess for add http(s)://
	string PreProcess(const string &str_in);
	bool IsIpv4OrIpv6(const string &str_in);
	bool IsIpv4AddPort(const string &str_in);
	bool IsIpv6AddPort(const string &str_in);
	bool IsDomain(const string &str_in);
};



#endif
