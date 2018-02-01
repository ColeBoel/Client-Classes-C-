
#include "CloudBankUtils.h"
#include "BankKeys.h"
#include "BankTotal.h"
#include "Receipt.h"

using namespace Newtonsoft::Json;
using namespace Founders;

namespace CloudBankTester
{

	CloudBankUtils::CloudBankUtils(BankKeys *startKeys)
	{
		keys = startKeys;
		cli = new HttpClient();
		totalCoinsWithdrawn = 0;
		onesInBank = 0;
		fivesInBank = 0;
		twentyFivesInBank = 0;
		hundresInBank = 0;
		twohundredfiftiesInBank = 0;
	} //end constructor

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task showCoins()
	Task *CloudBankUtils::showCoins()
	{
		std::wcout << L"https://" << keys->getpublickey() << L"/show_coins.aspx?k=" << keys->getprivatekey() << std::endl;
		std::wstring json = L"error";
		try
		{
//There is no equivalent to 'await' in C++:
			auto showCoins = await cli->GetAsync(L"https://" + keys->getpublickey() + L"/show_coins.aspx?k=" + keys->getprivatekey());
//There is no equivalent to 'await' in C++:
			json = await showCoins->Content.ReadAsStringAsync();
		}
		catch (const HttpRequestException &ex)
		{
			std::wcout << L"Exception" << ex->Message << std::endl;
		} //end try catch


		if (json.find(L"error") != std::wstring::npos)
		{
			std::wcout << json << std::endl;
		}
		else
		{
			auto bankTotals = JsonConvert::DeserializeObject<BankTotal*>(json);
			onesInBank = bankTotals->ones;
			fivesInBank = bankTotals->fives;
			twentyFivesInBank = bankTotals->twentyfives;
			hundresInBank = bankTotals->hundreds;
			twohundredfiftiesInBank = bankTotals->twohundredfifties;
			//rawStackFromWithdrawal = GET(cloudBankURL, receiptNumber);
		}

	} //end show coins

	void CloudBankUtils::loadStackFromFile(const std::wstring &filename)
	{
		//rawStackForDeposit = ReadFile( filename);
		rawStackForDeposit = File::ReadAllText(filename);
	}

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task sendStackToCloudBank(string toPublicURL)
	Task *CloudBankUtils::sendStackToCloudBank(const std::wstring &toPublicURL)
	{
		std::wstring CloudBankFeedback = L"";
		auto formContent = new FormUrlEncodedContent(std::vector<KeyValuePair<std::wstring, std::wstring>> {KeyValuePair<std::wstring, std::wstring>(L"stack", rawStackForDeposit)});

		std::wcout << L"CloudBank request: " << toPublicURL << L"/deposit_one_stack.aspx" << std::endl;
		std::wcout << L"Stack File: " << rawStackForDeposit << std::endl;

		try
		{
//There is no equivalent to 'await' in C++:
			auto result_stack = await cli->PostAsync(L"https://" + toPublicURL + L"/deposit_one_stack.aspx", formContent);
//There is no equivalent to 'await' in C++:
			CloudBankFeedback = await result_stack->Content.ReadAsStringAsync();
		}
		catch (const std::exception &ex)
		{
			std::wcout << ex.what() << std::endl;
		}

		std::wcout << L"CloudBank Response: " << CloudBankFeedback << std::endl;
		auto cbf = JsonConvert::DeserializeObject<std::unordered_map<std::wstring, std::wstring>>(CloudBankFeedback);
		//rawReceipt = cbf["receipt"];
		//receiptNumber = cbf["rn"];
		receiptNumber = cbf[L"receipt"];
		//Console.Out.WriteLine("Raw Receipt: " + rawReceipt);
	} //End send stack

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task getReceipt(string toPublicURL)
	Task *CloudBankUtils::getReceipt(const std::wstring &toPublicURL)
	{
		std::wcout << L"Geting Receipt: " << L"https://" << toPublicURL << L"/" << keys->getprivatekey() << L"/Receipts/" << receiptNumber << L".json" << std::endl;
//There is no equivalent to 'await' in C++:
		auto result_receipt = await cli->GetAsync(L"https://" + toPublicURL + L"/" + keys->getprivatekey() + L"/Receipts/" + receiptNumber + L".json");

//There is no equivalent to 'await' in C++:
		rawReceipt = await result_receipt->Content.ReadAsStringAsync();
		std::wcout << L"Raw Receipt: " << rawReceipt << std::endl;
	} //End get Receipt

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task getStackFromCloudBank(int amountToWithdraw)
	Task *CloudBankUtils::getStackFromCloudBank(int amountToWithdraw)
	{
		totalCoinsWithdrawn = amountToWithdraw;
//There is no equivalent to 'await' in C++:
		auto result_stack = await cli->GetAsync(L"https://" + keys->getpublickey() + L"/withdraw_account.aspx?amount=" + std::to_wstring(amountToWithdraw) + L"&k=" + keys->getprivatekey());
//There is no equivalent to 'await' in C++:
			rawStackFromWithdrawal = await result_stack->Content.ReadAsStringAsync();
			//rawStack = GET(cloudBankURL, receiptNumber);
	} //End get stack from cloudbank

	int CloudBankUtils::getDenomination(int sn)
	{
		int nom = 0;
		if ((sn < 1))
		{
			nom = 0;
		}
		else if ((sn < 2097153))
		{
			nom = 1;
		}
		else if ((sn < 4194305))
		{
			nom = 5;
		}
		else if ((sn < 6291457))
		{
			nom = 25;
		}
		else if ((sn < 14680065))
		{
			nom = 100;
		}
		else if ((sn < 16777217))
		{
			nom = 250;
		}
		else
		{
			nom = L'0';
		}

		return nom;
	} //end get denomination

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task getReceiptFromCloudBank(string toPublicURL)
	Task *CloudBankUtils::getReceiptFromCloudBank(const std::wstring &toPublicURL)
	{
//There is no equivalent to 'await' in C++:
		auto result_receipt = await cli->GetAsync(L"https://" + keys->getpublickey() + L"/get_receipt.aspx?rn=" + receiptNumber + L"&k=" + keys->getprivatekey());
//There is no equivalent to 'await' in C++:
		std::wstring rawReceipt = await result_receipt->Content.ReadAsStringAsync();
		if (rawReceipt.find(L"Error") != std::wstring::npos)
		{
			std::wcout << rawReceipt << std::endl;
		}
		else
		{
			auto deserialReceipt = JsonConvert::DeserializeObject<Receipt*>(rawReceipt);
			for (int i = 0; i < deserialReceipt->rd->Length; i++)
			{
				if (deserialReceipt->rd[i]->status == L"authentic")
				{
					totalCoinsWithdrawn += getDenomination(deserialReceipt->rd[i].sn);
				}
			}
//There is no equivalent to 'await' in C++:
			auto result_stack = await cli->GetAsync(keys->getpublickey() + L"/withdraw_one_stack.aspx?amount=" + std::to_wstring(totalCoinsWithdrawn) + L"&k=" + keys->getprivatekey());
//There is no equivalent to 'await' in C++:
			rawStackFromWithdrawal = await result_stack->Content.ReadAsStringAsync();
			//rawStackFromWithdrawal = GET(cloudBankURL, receiptNumber);
		}
	}

	std::wstring CloudBankUtils::interpretReceipt()
	{
		std::wstring interpretation = L"";
		if (rawReceipt.find(L"Error") != std::wstring::npos)
		{
			//parse out message
			interpretation = rawReceipt;
		}
		else
		{
			//tell the client how many coins were uploaded how many counterfeit, etc.
			auto deserialReceipt = JsonConvert::DeserializeObject<Receipt*>(rawReceipt);
			int totalNotes = deserialReceipt->total_authentic + deserialReceipt->total_fracked;
			int totalCoins = 0;
			for (int i = 0; i < deserialReceipt->rd->Length; i++)
			{
				if (deserialReceipt->rd[i]->status == L"authentic")
				{
					totalCoins += getDenomination(deserialReceipt->rd[i].sn);
				}
			}
			interpretation = L"receipt number: " + deserialReceipt->receipt_id + L" total authentic notes: " + std::to_wstring(totalNotes) + L" total authentic coins: " + std::to_wstring(totalCoins);


		} //end if error
		return interpretation;
	}

	void CloudBankUtils::saveStackToFile(const std::wstring &path)
	{
		File::WriteAllText(path + getStackName(), rawStackFromWithdrawal);
		//WriteFile(path + stackName, rawStackFromWithdrawal);
	}

	std::wstring CloudBankUtils::getStackName()
	{
		return std::to_wstring(totalCoinsWithdrawn) + L".CloudCoin." + receiptNumber + L".stack";
	}

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public async Task transferCloudCoins(string toPublicKey, int coinsToSend)
	Task *CloudBankUtils::transferCloudCoins(const std::wstring &toPublicKey, int coinsToSend)
	{
		//Download amount
//There is no equivalent to 'await' in C++:
		await getStackFromCloudBank(coinsToSend);
		rawStackForDeposit = rawStackFromWithdrawal; //Make it so it will send the stack it recieved
//There is no equivalent to 'await' in C++:
		await sendStackToCloudBank(toPublicKey);
		//Upload amount
	} //end transfer
}
