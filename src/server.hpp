#include "session.hpp"

namespace rit{
    using boost::asio::ip::tcp;
    class server{
    private:	
		session* new_session;
        boost::asio::io_service& io_service_;
        tcp::acceptor acceptor_;
        unsigned int port_num_;

    public:
        server(boost::asio::io_service& io_service, unsigned int port_num)
            : io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port_num)), port_num_(port_num)
        {
            startAccept();
        }

        void startAccept(){
            std::cout << "START SERVER, Port NUM: " << port_num_ << std::endl;
			//session* new_session = new session(io_service_);
			new_session = new session(io_service_);						
            acceptor_.async_accept(new_session->getLocalSocket(),
                boost::bind(&server::handleAccept, this, new_session, boost::asio::placeholders::error));
        }
		void handleAccept(session* new_session, const boost::system::error_code& error){
            std::cout << "Connection is Accpeted" << std::endl;
            if(!error) {
                new_session->start();
            }
			else {
				delete new_session;
			}
            //startAccept();
        }
		int GetCmd() {
			int tmp = new_session->GetPhoneCmd();
			if (tmp != -1) {
				std::cout << "Android cmd: " << tmp << std::endl;			
			}
			return tmp;
		}
    };
};

