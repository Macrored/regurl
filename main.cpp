#include <iostream>
#include <Windows.h>
#include "regurl.h"
#include "logger.h"
using namespace std;


int main(void) {
	string url_org[] = {
		"1.1.1.1",
		"AB::0001",
		"1.1.1.1:80",
		"AB::0001:80",
		"www.baidu.com",
		"baidu.com:80",
		"",
		" 1.1.1.1 ",
		"1.1.1.256",
		"1.1.1.256.1",
		"1011111.10.10.2536.77",
		"1.1.1.256f",
		"1.1.1.256:80",
		"1.1.1s3.256:80",
	};

	regurl url;

	for (size_t i = 0; i < sizeof(url_org)/sizeof(string); i++)
	{
		CplusLog(LOG_INFO) << url_org[i] << " -> " << url.CNormalize(url_org[i]);
	}

	return 0;
}
