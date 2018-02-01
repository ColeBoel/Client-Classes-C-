#pragma once

#include <string>

using namespace Newtonsoft::Json;

namespace CloudBankTester
{
	/*
	 example json file: 

	    {
	       "publickey":"preston.CloudCoin.Global",
	       "privatekey":"6e2b96d6204a4212ae57ab84260e747f",
	       "email":""
	     }
	     */

	class BankKeys
	{
	private:
		std::wstring privatepublickey;
		std::wstring privateprivatekey;
		std::wstring privateemail;

		//Fields
	public:
		std::wstring getpublickey() const;
		void setpublickey(const std::wstring &value);

		std::wstring getprivatekey() const;
		void setprivatekey(const std::wstring &value);

		std::wstring getemail() const;
		void setemail(const std::wstring &value);


		//Constructors
		BankKeys();

		BankKeys(const std::wstring &publickey, const std::wstring &privatekey, const std::wstring &email);


	};
}
