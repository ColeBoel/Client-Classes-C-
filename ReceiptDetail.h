#pragma once


#include <string>

using namespace Newtonsoft::Json;

namespace Founders
{
	class ReceiptDetail
	{
	private:
		int privatenn = 0;
		int privatesn = 0;
		std::wstring privatestatus;
		std::wstring privatepown;
		std::wstring privatenote;

		//Fields
	public:
		int getnn() const;
		void setnn(const int &value);

		int getsn() const;
		void setsn(const int &value);

		std::wstring getstatus() const;
		void setstatus(const std::wstring &value);

		std::wstring getpown() const;
		void setpown(const std::wstring &value);

		std::wstring getnote() const;
		void setnote(const std::wstring &value);


		//Constructors
		ReceiptDetail();

		ReceiptDetail(int nn, int sn, const std::wstring &status, const std::wstring &pown, const std::wstring &note);

	}; //End Class
} //End Namespace
