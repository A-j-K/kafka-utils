
#include <cctype>
#include <sstream>
#include <iomanip>

#include "hexdump.hpp"

namespace KafkaUtils {

std::string
Hexdump::hexdump(void *s, size_t len)
{
	size_t i, offset = 0;
	const char *p = static_cast<const char*>(s);
	std::stringstream out;

	for (offset = 0 ; offset < len ; offset += 16) {
		int charcount = 16;
		for (i = offset ; i < ((int)offset+16) && i < (int)len ; i++, charcount--) {
			std::stringstream oss;
			oss << std::setw(2) << std::hex << ((int)(p[i] & 0xff)) << " ";
			out << oss.str();
		}
		while(charcount-- > 0) {
			out << "   ";
		}
		for (i = offset ; i < ((int)offset+16) && i < (int)len ; i++) {
			std::stringstream oss;
			oss << ((char)(std::isprint(p[i]) ? p[i] : '.'));
			out << oss.str();
		}
		out << std::endl;
	}
	return out.str();
}

}; // namespace KafkaUtils
