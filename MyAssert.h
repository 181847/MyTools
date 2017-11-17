#pragma once
#include <exception>
#include <string>
class  SimpleException: std::exception
{
public:
	const char* expr;
	const char* file;
	const int line;

public:
	SimpleException(const char *e, const char* f, const int line)
		:expr(e), file(f), line(line)
	{
	}

	inline std::string SimpleException::ToString()
	{
		char lineString[256];
		std::string returnval;

		sprintf_s(lineString, "\nFile:\t\t%s\nLine:\t\t%d\nExperssion:\t%s", file, line, expr);

		returnval += lineString;
		return returnval;
	}
};





#if ASSERTIONS_ENABLED
#define ASSERT(expr) \
	if(expr){}\
	else\
	{\
		throw SimpleException( #expr, __FILE__, __LINE__);\
	}
#else
#define ASSERT(expr)//����ֵ
#endif


// Simulate to the ThrowIfFailed(HRESULT).
// Here we just use a boolean to togole the exception.
// If you 
#if CHECK_THROW_IF_ENABLED
#define ThrowIfFalse(expr)\
	if (expr){}\
	else\
	{\
		throw SimpleException(#expr, __FILE__, __LINE__); \
	}
#else
#define ThrowIfFalse(expr) expr
#endif

//�����������һЩ����û��ʵ�ֵ�ʱ���׳�����쳣����ֹ����һЩ�����ʵ��
#define THROW_UNIMPLEMENT_EXCEPTION(pChar)\
	{\
		throw SimpleException(pChar, __FILE__, __LINE__);\
	}
