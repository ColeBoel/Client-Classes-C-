
#include "BankKeys.h"

using namespace Newtonsoft::Json;

namespace CloudBankTester
{

	std::wstring BankKeys::getpublickey() const
	{
		return privatepublickey;
	}

	void BankKeys::setpublickey(const std::wstring &value)
	{
		privatepublickey = value;
	}

	std::wstring BankKeys::getprivatekey() const
	{
		return privateprivatekey;
	}

	void BankKeys::setprivatekey(const std::wstring &value)
	{
		privateprivatekey = value;
	}

	std::wstring BankKeys::getemail() const
	{
		return privateemail;
	}

	void BankKeys::setemail(const std::wstring &value)
	{
		privateemail = value;
	}

	BankKeys::BankKeys()
	{

	} //end of constructor

	BankKeys::BankKeys(const std::wstring &publickey, const std::wstring &privatekey, const std::wstring &email)
	{
		this->setpublickey(publickey);
		this->setprivatekey(privatekey);
		this->setemail(email);
	} //end of constructor
}
