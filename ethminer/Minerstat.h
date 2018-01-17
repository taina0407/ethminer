#include <boost/asio.hpp>
#include <json/json.h>

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

class Minerstat
{
public:

	void updateStat(string _token, string _worker, string _pool, long _rate, int _accepted, int _rejected) {
		boost::asio::ip::tcp::iostream stream;

		float mh = _rate / 1000000.0f;
		char mhs[16];
		sprintf(mhs, "%.2f", mh);

		// Accepted
		char acceptedc[256];
		sprintf(acceptedc, "%i", _accepted);
		// Rejected
		char rejectedc[256];
		sprintf(rejectedc, "%i", _rejected);

		string message = "token=" + _token + "&pool="+ _pool +"&worker=" + _worker + "&hashrate=" + std::string(mhs) + "&accepted=" + std::string(acceptedc) + "&rejected=" + std::string(rejectedc);

		stream.connect("minerstat.farm", "80");
		stream << "POST /getstat.php HTTP/1.1 \r\n";
		stream << "Host: minerstat.farm\r\n";
		stream << "Content-Type: application/x-www-form-urlencoded; charset=utf-8\r\n";
		stream << "Content-Length: " << message.length() << "\r\n";
		stream << "Connection: close\r\n\r\n";

		stream << message;
		stream.flush();

	}
};
