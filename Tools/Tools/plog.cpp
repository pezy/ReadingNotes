#include "plog.h"
#include <windows.h>
#include <Share.h>

void OutputLog(const char *buf)
{
	FILE* fp;
	if ((fp = _fsopen("../das.log", "a", _SH_DENYNO)) != NULL) {
		fseek(fp, 0L, SEEK_END);
		long sz = ftell(fp);
		fclose(fp);
		if (MAX_FILE_SIZE <= sz) {
			fp = _fsopen("../das.log", "w+", _SH_DENYNO);
			fprintf(fp, buf);
			fclose(fp);
		} else {
			fp = _fsopen("../das.log", "a+", _SH_DENYNO);
			fprintf(fp, buf);
			fclose(fp);
		}
	}
}

int VDebugPrintF(const char* format, va_list argList)
{
	const unsigned int MAX_CHARS = 1023;
	static char s_buffer[MAX_CHARS + 1];
	int charsWritten
		= vsnprintf_s(s_buffer, MAX_CHARS, format, argList);
	s_buffer[MAX_CHARS] = '\0'; // be sure to
	// NIL-terminate
	// Now that we have a formatted string, call the
	// Win32 API.
	OutputDebugStringA(s_buffer);
	OutputLog(s_buffer);
	return charsWritten;
}

int DebugPrintF(const char* format, ...)
{
	va_list argList;
	va_start(argList, format);
	int charsWritten = VDebugPrintF(format, argList);
	va_end(argList);
	return charsWritten;
}

void VerboseDebugPrintF(int verbosity,
	const char* format, ...)
{
	// Only print when the global verbosity level is
	// high enough.
	if (VERBOSITY_LEVEL >= verbosity)
	{
		va_list argList;
		va_start(argList, format);
		VDebugPrintF(format, argList);
		va_end(argList);
	}
}