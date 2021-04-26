#include "MRKLog.h"

#include <fstream>
#include "../Universal/vmprotect.h"

namespace MRK
{
	std::string ms_LogPath;
	void MRKSetLogPath(std::string path) 
	{
		Protect();
		ms_LogPath = path;
		ProtectEnd();
	}
	void MRKLog(std::string log, bool clear, bool sep) 
	{
		Protect();
		/*_STD ofstream stream(ms_LogPath.c_str(), clear ? _STD ios_base::out : _STD ios_base::app);
		if (sep)
			stream << '\n';

		stream << log;
		stream.close();*/
		ProtectEnd();
	}
}
