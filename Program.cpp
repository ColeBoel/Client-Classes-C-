
#include "Program.h"
#include "BankKeys.h"
#include "CloudBankUtils.h"

using namespace banktesterforms;

namespace CloudBankTester
{

KeyboardReader *Program::reader = new KeyboardReader();
std::wstring Program::rootFolder = AppDomain::CurrentDomain->BaseDirectory;
std::wstring Program::prompt = L"Start Mode> ";
std::vector<std::wstring> Program::commandsAvailable = {L"Load Bank Keys", L"Show Coins", L"Deposite Coin", L"Withdraw Coins", L"Look at Receipt", L"Write Check", L"Get Check", L"quit"};
Random *Program::myRandom = new Random();
std::wstring Program::publicKey = L"";
std::wstring Program::privateKey = L"";
std::wstring Program::email = L"";
std::wstring Program::sign = L"Preston Linderman";
BankKeys *Program::myKeys;
CloudBankUtils *Program::receiptHolder;
HttpClient *Program::cli = new HttpClient();

	void Program::Main(std::vector<std::wstring> &args)
	{
		printWelcome();
		run()->Wait(); // Makes all commands available and loops
		std::wcout << L"Thank you for using CloudBank Tester. Goodbye." << std::endl;
	} // End main

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task run()
	Task *Program::run()
	{
		bool restart = false;
		while (!restart)
		{
			Console::ForegroundColor = ConsoleColor::Green;
			std::wcout << L"" << std::endl;
			//  Console.Out.WriteLine("========================================");
			std::wcout << L"" << std::endl;
			std::wcout << L"Commands Available:" << std::endl;
			Console::ForegroundColor = ConsoleColor::White;
			int commandCounter = 1;
			for (auto command : commandsAvailable)
			{
				std::wcout << commandCounter << (L". " << command) << std::endl;
				commandCounter++;
			}
			Console::ForegroundColor = ConsoleColor::Green;
			std::wcout << prompt;
			Console::ForegroundColor = ConsoleColor::White;
			int commandRecieved = reader->readInt(1,6);


			switch (commandRecieved)
			{
				case 1:
					loadKeys();
					break;
				case 2:
//There is no equivalent to 'await' in C++:
					await showCoins();
					break;
				case 3:
// There is no equivalent to 'await' in C++:
					receiptHolder = await depositAsync();
					break;
				case 4:
//There is no equivalent to 'await' in C++:
					await withdraw();
					break;
				case 5:
					receipt();
					break;
				case 6:
//There is no equivalent to 'await' in C++:
					await writeCheck();
					break;
				case 7:
//There is no equivalent to 'await' in C++:
					await GetCheck();
					break;
				case 8:
					std::wcout << L"Goodbye!" << std::endl;
					exit(0);
					break;
				default:
					std::wcout << L"Command failed. Try again." << std::endl;
					break;
			} // end switch
		} // end while
	} // end run method

	void Program::printWelcome()
	{
		Console::ForegroundColor = ConsoleColor::Green;
		std::wcout << L"╔══════════════════════════════════════════════════════════════════╗" << std::endl;
		std::wcout << L"║                   CloudBank Tester v.11.19.17                    ║" << std::endl;
		std::wcout << L"║          Used to Authenticate Test CloudBank                     ║" << std::endl;
		std::wcout << L"║      This Software is provided as is with all faults, defects    ║" << std::endl;
		std::wcout << L"║          and errors, and without warranty of any kind.           ║" << std::endl;
		std::wcout << L"║                Free from the CloudCoin Consortium.               ║" << std::endl;
		std::wcout << L"╚══════════════════════════════════════════════════════════════════╝" << std::endl;
		Console::ForegroundColor = ConsoleColor::White;
	} // End print welcome

	void Program::loadKeys()
	{
		publicKey = L"Preston.CloudCoin.global";
		privateKey = L"0DECE3AF-43EC-435B-8C39-E2A5D0EA8676";
		email = L"Preston@ChicoHolo.com";
		std::wcout << L"Public key is " << publicKey << std::endl;
		std::wcout << L"Private key is " << privateKey << std::endl;
		std::wcout << L"Email is " << email << std::endl;
		myKeys = new BankKeys(publicKey, privateKey, email);
	}

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task showCoins()
	Task *Program::showCoins()
	{
		CloudBankUtils *cbu = new CloudBankUtils(myKeys);
//There is no equivalent to 'await' in C++:
		await cbu->showCoins();
		std::wcout << L"Ones in our bank:" << cbu->onesInBank << std::endl;
		std::wcout << L"Five in our bank:" << cbu->fivesInBank << std::endl;
		std::wcout << L"Twenty Fives in our bank:" << cbu->twentyFivesInBank << std::endl;
		std::wcout << L"Hundreds in our bank:" << cbu->hundresInBank << std::endl;
		std::wcout << L"Two Hundred Fifties in our bank:" << cbu->twohundredfiftiesInBank << std::endl;
	} //end show coins

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task<CloudBankUtils> depositAsync()
	Task<CloudBankUtils*> *Program::depositAsync()
	{
		CloudBankUtils *sender = new CloudBankUtils(myKeys);
		std::wcout << L"What is the path to your stack file?" << std::endl;
		//string path = reader.readString();
		std::wstring path = AppDomain::CurrentDomain->BaseDirectory;
		path += reader->readString();
		std::wcout << L"Loading " << path << std::endl;
		sender->loadStackFromFile(path);
//There is no equivalent to 'await' in C++:
		await sender->sendStackToCloudBank(publicKey);
//There is no equivalent to 'await' in C++:
		await sender->getReceipt(publicKey);
		return sender;
	} //end deposit

// There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task withdraw()
	Task *Program::withdraw()
	{
		CloudBankUtils *receiver;
		if (receiptHolder == nullptr)
		{
			receiver = new CloudBankUtils(myKeys);
		}
		else
		{
			receiver = receiptHolder;
		}

		std::wcout << L"How many CloudCoins are you withdrawing?" << std::endl;
		int amount = reader->readInt();
//There is no equivalent to 'await' in C++:
		await receiver->getStackFromCloudBank(amount);
		receiver->saveStackToFile(AppDomain::CurrentDomain->BaseDirectory);
	} //end deposit

	void Program::receipt()
	{
		if (receiptHolder == nullptr)
		{
			std::wcout << L"There has not been a recent deposit. So no receipt can be shown." << std::endl;
		}
		else
		{
			std::wcout << receiptHolder->interpretReceipt() << std::endl;
		}
	} //end deposit

// There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task writeCheck()
	Task *Program::writeCheck()
	{
		std::wcout << L"How many CloudCoins are you withdrawing?" << std::endl;
		int amount = reader->readInt();
		std::wcout << L"Who are you Paying?" << std::endl;
		std::wstring payto = reader->readString();
		std::wcout << L"Who is being Emailed?" << std::endl;
		std::wstring emailto = reader->readString();
//There is no equivalent to 'await' in C++:
		auto request = await cli->GetAsync(L"https://" + publicKey + L"/write_check.aspx?pk=" + privateKey + L"&action=email&amount=" + std::to_wstring(amount) + L"&emailto=" + emailto + L"&payto=" + payto + L"&from=" + email + L"&signby=" + sign);
//There is no equivalent to 'await' in C++:
		std::wstring response = await request->Content.ReadAsStringAsync();
		std::wcout << response << std::endl;
	}

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task GetCheck()
	Task *Program::GetCheck()
	{
		std::wcout << L"What is the Check's Id?" << std::endl;
		std::wstring id = reader->readString();
// There is no equivalent to 'await' in C++:
		auto request = await cli->GetAsync(L"https://" + publicKey + L"/checks.aspx?id=" + id + L"&receive=json");
//There is no equivalent to 'await' in C++:
		std::wstring response = await request->Content.ReadAsStringAsync();
		std::wcout << response << std::endl;
	}
}
