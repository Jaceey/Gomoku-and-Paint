#pragma once
/*!	\file		XError.hpp
	\author		Jaceey Tuck
	\date		2019-02-18

	XError class declaration.
*/
#include <Windows.h>
#include <string>
#include <sstream>

using namespace std;

#ifndef XERROR_H
#define XERROR_H
#endif // !XERROR_H

#pragma once
#if defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "APILib-mt-gd.lib")	// debug regular build
#elif defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "APILib-mt-sgd.lib")
#elif !defined(_DEBUG) && defined(_DLL)	
#pragma comment (lib, "APILib-mt.lib")	// released
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "APILib-mt-s.lib")
#endif
#pragma comment(linker, "/ENTRY:mainCRTStartup")

//=======================================================
// Error exception class and utilities
//=======================================================
#pragma region XError

/* ErrorDescription */
inline string ErrorDescription(DWORD dwMessageID) {
	char* msg;
	auto c = FormatMessageA(
		/* flags */			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
		/* source*/			NULL,
		/* message ID */	dwMessageID,
		/* language */		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		/* buffer */		(LPSTR)&msg,
		/* size */			0,
		/* args */			NULL
	);

	string strMsg = (c == 0)
		? "unknown"
		: msg;
	LocalFree(msg);
	return strMsg;
}


/* Console error exception class. */
class XError {
public:
	using id_type = decltype(GetLastError());
	using file_type = char const *;
	using string_type = std::string;
private:
	id_type code_;
	int	line_;
	file_type file_;
public:
	XError(int line, file_type file) : code_(GetLastError()), line_(line), file_(file) {}
	auto code() const -> id_type { return code_; }
	auto line() const -> int { return line_; }
	auto file() const -> file_type { return file_; }

	string_type msg() const {
		ostringstream oss;
		oss << "Error: " << code() << "\n";
		oss << ErrorDescription(code()) << "\n";
		oss << "In: " << file() << "\n";
		oss << "Line: " << line() << "\n";
		return oss.str();
	}
};



/* Console error exception throw helper macros. */
#define THROW_IF_CONSOLE_ERROR(res) if(!res) throw XError(__LINE__,__FILE__)
#define THROW_CONSOLE_ERROR(res) throw XError(__LINE__,__FILE__)



#pragma endregion