#pragma once


#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "exceptionhelper.h"

//Forward class declarations:
namespace CloudBankTester { class BankKeys; }

using namespace Newtonsoft::Json;

using namespace Founders;

namespace CloudBankTester
{
	class CloudBankUtils
	{
		//Fields
	private:
		BankKeys *keys;
		std::wstring rawStackForDeposit;
		std::wstring rawStackFromWithdrawal;
		std::wstring rawReceipt;
		HttpClient *cli;
		std::wstring receiptNumber;
		int totalCoinsWithdrawn = 0;
	public:
		int onesInBank = 0;
		int fivesInBank = 0;
		int twentyFivesInBank = 0;
		int hundresInBank = 0;
		int twohundredfiftiesInBank = 0;


		//Constructor
		virtual ~CloudBankUtils()
		{
			delete keys;
			delete cli;
		}

		CloudBankUtils(BankKeys *startKeys);

		//Methods
//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task showCoins()
		Task *showCoins();


		void loadStackFromFile(const std::wstring &filename);

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task sendStackToCloudBank(string toPublicURL)
		Task *sendStackToCloudBank(const std::wstring &toPublicURL);




//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task getReceipt(string toPublicURL)
		Task *getReceipt(const std::wstring &toPublicURL);

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task getStackFromCloudBank(int amountToWithdraw)
		Task *getStackFromCloudBank(int amountToWithdraw);


	private:
		int getDenomination(int sn);

	public:
//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task getReceiptFromCloudBank(string toPublicURL)
		Task *getReceiptFromCloudBank(const std::wstring &toPublicURL);

		std::wstring interpretReceipt();

		void saveStackToFile(const std::wstring &path);

		std::wstring getStackName();

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task transferCloudCoins(string toPublicKey, int coinsToSend)
		Task *transferCloudCoins(const std::wstring &toPublicKey, int coinsToSend);


	}; //end class
} //end namespace
