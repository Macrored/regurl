#include <regex>
#include <algorithm>
#include "regurl.h"
#include "logger.h"

regurl::regurl()
{
}

regurl::~regurl()
{
}

string regurl::CNormalize(const string &str_in) {
	if (str_in.length() > 1024 * 5) {
		return string();
	}

	string str_noml = str_in;
	str_noml = PreProcess(str_noml);

	bool res = false;

	if (IsIpv4OrIpv6(str_noml)) {
		res = true;
	}

	if (!res && IsIpv4AddPort(str_noml)) {
		res = true;
	}

	if (!res && IsIpv6AddPort(str_noml)) {
		res = true;
	}
	if (!res && IsDomain(str_noml)) {
		res = true;
	}

	if (res) {
		return str_noml;
	}
	return string();
}

string regurl::PreProcess(const string &str_in)
{
	if (str_in.length() <= 0) {
		return string();
	}

	string str_procs = str_in;
	for (string::iterator it = str_procs.begin(); it != str_procs.end();)
	{
		if (*it == ' ') {
			str_procs.erase(it);
		}
		else {
			it++;
		}
	}

	return str_procs;
}

bool regurl::IsIpv4OrIpv6(const string &str_in) {
	
	// 过滤非法IP和端口
	/*std::regex IpRegex("((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})"
		"(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}");*/
	
	regex re(
		"(^(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)(\\.(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)){3}$)|"
		"(^(?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$)|"
		"(^((?:[0-9A-Fa-f]{1,4}(:[0-9A-Fa-f]{1,4})*)?)::((?:([0-9A-Fa-f]{1,4}:)*[0-9A-Fa-f]{1,4})?)$)|"
		"(^(::(?:[0-9A-Fa-f]{1,4})(?::[0-9A-Fa-f]{1,4}){0,6})|((?:[0-9A-Fa-f]{1,4})(?::[0-9A-Fa-f]{1,4}){0,6}::)$)");
	smatch sm;

	if (regex_match(str_in, sm, re)) {
		return true;
	}

	return false;
}

bool regurl::IsIpv4AddPort(const string &str_in) {
	regex re(
		"^((?:25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)(?:\\.(?:25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)){3})"
		":(6553[0-5]|655[0-2]\\d|65[0-4]\\d{2}|6[0-4]\\d{4}|[1-5]\\d{4}|[1-9]\\d{1,3}|[0-9]{1,3})$");
	smatch sm;

	if (regex_match(str_in, sm, re)) {
		return true;
	}

	return false;
}

bool regurl::IsIpv6AddPort(const string & str_in)
{
	regex re(
		"^\\[(((?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4})|"
		"(((?:[0-9A-Fa-f]{1,4}(:[0-9A-Fa-f]{1,4})*)?)::((?:([0-9A-Fa-f]{1,4}:)*[0-9A-Fa-f]{1,4})?))|"
		"((::(?:[0-9A-Fa-f]{1,4})(?::[0-9A-Fa-f]{1,4}){0,6})|((?:[0-9A-Fa-f]{1,4})(?::[0-9A-Fa-f]{1,4}){0,6}::)))\\]"
		":(6553[0-5]|655[0-2]\\d|65[0-4]\\d{2}|6[0-4]\\d{4}|[1-5]\\d{4}|[1-9]\\d{1,3}|[0-9]{1,3})$");
	smatch sm;

	if (regex_match(str_in, sm, re)) {
		return true;
	}

	return false;
}

bool regurl::IsDomain(const string & str_in)
{
	// Specification provision: domain name total length cannot exceed 253
	if (str_in.length() > 253) {
		return false;
	}

	// domain match
	regex re1(
		"^([a-z0-9]{0,63}|[a-z0-9][a-z0-9-]{0,61}[a-z0-9])"
		"(\\.([a-z0-9]{0,63}|[a-z0-9][a-z0-9-]{0,61}[a-z0-9]))*"
		"(:(6553[0-5]|655[0-2]\\d|65[0-4]\\d{2}|6[0-4]\\d{4}|[1-5]\\d{4}|[1-9]\\d{1,3}|[0-9]{1,3}))?$");
	// lllegal ip filtering
	regex re2(".*[a-z].*");
	smatch sm1, sm2;

	if (regex_match(str_in, sm1, re1)) {
		if (regex_match(str_in, sm2, re2)) {
			return true;
		}
		else if (3 < count(str_in.begin(), str_in.end(), '.')) {
			return true;
		}
	}
	return false;
}


