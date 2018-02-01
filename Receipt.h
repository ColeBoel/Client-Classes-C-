

#include <string>
#include <vector>

//Forward class declarations:
namespace Founders { class ReceiptDetail; }

using namespace Newtonsoft::Json;
namespace Founders
{
	class Receipt
	{
	private:
		std::wstring privatereceipt_id;
		std::wstring privatetime;
		std::wstring privatetimezone;
		std::wstring privatebank_server;
		int privatetotal_authentic = 0;
		int privatetotal_fracked = 0;
		int privatetotal_counterfeit = 0;
		int privatetotal_lost = 0;
		std::vector<ReceiptDetail*> privaterd;

	public:
		std::wstring getreceipt_id() const;
		void setreceipt_id(const std::wstring &value);

		std::wstring gettime() const;
		void settime(const std::wstring &value);

		std::wstring gettimezone() const;
		void settimezone(const std::wstring &value);

		std::wstring getbank_server() const;
		void setbank_server(const std::wstring &value);

		int gettotal_authentic() const;
		void settotal_authentic(const int &value);

		int gettotal_fracked() const;
		void settotal_fracked(const int &value);

		int gettotal_counterfeit() const;
		void settotal_counterfeit(const int &value);

		int gettotal_lost() const;
		void settotal_lost(const int &value);

		std::vector<ReceiptDetail*> getrd() const;
		void setrd(std::vector<ReceiptDetail*> &value);

	};
}
