#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#define BUFFER_LENGTH 128

class SerialComm
{
private:
	unsigned char send_buffer_[BUFFER_LENGTH];
	unsigned char recv_buffer_[BUFFER_LENGTH];
	const unsigned int m_baud_rate;
	bool active_;
	boost::asio::serial_port serial_;
public:
	SerialComm(boost::asio::io_service& io, const unsigned int baud_rate, const std::string& port):  
	    m_baud_rate(baud_rate), 
	    active_(false),
	    serial_(io)
    {
		serial_.open(port);
		if(serial_.is_open()){
			active_ = true;
			std::cout << "serial open success" << std::endl;
			start();
		}
		else
			std::cout << "Serial fail to open" << std::endl;
    }
	~SerialComm(void){
	    serial_.close();
	    active_ = false;
	    std::cout << "Serial close" << std::endl;
	}
	void start(){
	    serial_.set_option(boost::asio::serial_port::baud_rate(m_baud_rate));
	    serial_.set_option(boost::asio::serial_port::flow_control());
	    serial_.set_option(boost::asio::serial_port::stop_bits());
	    serial_.set_option(boost::asio::serial_port::character_size());
	    serial_.set_option(boost::asio::serial_port::parity());
	    std::cout << "Start serial Communication!" << std::endl;
	}
	void write(unsigned char* data, int length) {
	    for(int i = 0; i < length; ++i)
			send_buffer_[i] = data[i];
	    serial_.write_some(boost::asio::buffer(send_buffer_, length));
	}
	int read(unsigned char* data) {
	    int length = serial_.read_some(boost::asio::buffer(send_buffer_));
	    for(int i = 0; i < length; ++i) 
			data[i] = send_buffer_[i];
	    return length;
	}
	bool active() const {// return true if the socket is still active
	    return active_;
	}
};

