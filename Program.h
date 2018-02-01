#pragma once


#include <string>
#include <vector>
#include <iostream>

//Forward class declarations:
namespace CloudBankTester { class BankKeys; }
namespace CloudBankTester { class CloudBankUtils; }

using namespace banktesterforms;

namespace CloudBankTester
{
	class Program
	{

		/* INSTANCE VARIABLES */
	public:
		static KeyboardReader *reader;
		//  public static String rootFolder = System.getProperty("user.dir") + File.separator +"bank" + File.separator ;
		static std::wstring rootFolder;
		static std::wstring prompt;
		static std::vector<std::wstring> commandsAvailable;
   //public static int timeout = 10000; // Milliseconds to wait until the request is ended. 
	   // public static FileUtils fileUtils = new FileUtils(rootFolder, bank);
		static Random *myRandom;
		static std::wstring publicKey;
		static std::wstring privateKey;
		static std::wstring email;
		static std::wstring sign;
		static BankKeys *myKeys;
	private:
		static CloudBankUtils *receiptHolder;
		static HttpClient *cli;




		/* MAIN METHOD */
	public:
		static void Main(std::vector<std::wstring> &args);

		/* STATIC METHODS */
//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: public static async Task run()
		static Task *run();


		static void printWelcome();



	private:
		static void loadKeys();

		/* Show coins will populate the CloudBankUtils with the totals of each denominations
		 These totals are public properties that can be accessed */
//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task showCoins()
		static Task *showCoins();


		/* Deposit allow you to send a stack file to the CloudBank */
//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task<CloudBankUtils> depositAsync()
		static Task<CloudBankUtils*> *depositAsync();


//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task withdraw()
		static Task *withdraw();
		static void receipt();

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task writeCheck()
		static Task *writeCheck();

//There is no equivalent in C++ to the 'async' keyword:
//ORIGINAL LINE: static async Task GetCheck()
		static Task *GetCheck();
	};
}
