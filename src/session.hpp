#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/timer/timer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <list>
#include <string>

namespace rit{
    const std::size_t MAX_BUFFER_LENGTH = 1024;
    const std::size_t MAX_CONNECTIONS = 1024;
	const unsigned char max_command = 0x50;   
	unsigned char command;
	using boost::asio::ip::tcp;
    class session{
    public:
        session(boost::asio::io_service& io_service)
            : is_sending(false), socket(io_service), offset(0)
        {
			client_rcv = false;
        }

        ~session(){

        }

        tcp::socket& getLocalSocket(){
            return socket;
        }
		int GetPhoneCmd(){
			if(client_rcv) {
				client_rcv = false;
				return (int)command;
			}
			return -1;
		}

        void clear(){

            try{

            }catch(std::exception& e){
                //	std::cout << "ERROR on termination session: " << e.what() << std::endl;

            }

        }
		
        void start(){
            std::cout << "SESSION STARTED" << std::endl;
            socket.async_read_some(boost::asio::buffer(data_,MAX_BUFFER_LENGTH),
                boost::bind(&session::handle_read, this, 
                boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
        }

        template <class T>
        void write(const T& src){
            send_buffer.insert(send_buffer.end(), src.begin(), src.end());
            start_write();
        }

        //virtual void read_handler(const std::string& recv_str) = 0;
		void read_handler(const std::string& recv_str){
            std::vector<std::string> splited_strs;
            std::string header;
            header.push_back(0x7f);
            header.push_back(0x7f);
            header.push_back(0x01);
            boost::split_regex(splited_strs, recv_str, boost::regex(header));
            for(std::size_t i = 0; i < splited_strs.size(); ++i){
                std::string target = splited_strs[i];

                if(target.size() == 1){
                    //unsigned char command = target[0];
					command = target[0];
                    if(command <= max_command){
						client_rcv = true;
                        //command_parser();
                    }
                }
            }
        }
		/*
        // command parser
        void command_parser(){
			client_rcv = true;
            std::cout << "Command: " << (int) command << std::endl;
            switch(command){
                case 0:
                    {
                        std::string temp("RETURN LEFT");
                        write<std::string>(temp);
                    }
                    break;
                case 1:
                    {
                        std::string temp("RETURN RIGHT");
                        write<std::string>(temp);
                    }
                    break;
                case 2:
                    {
                        std::string temp("RETURN UP");
                        write<std::string>(temp);
                    }
                    break;
                case 3:
                    {
                        std::string temp("RETURN DOWN");
                        write<std::string>(temp);
                    }
                    break;
                default:
                    {
                        std::string temp("RETURN DEFAULT");
                        write<std::string>(temp);
                    }
                    break;
            }
        }
		*/
    private:
        void start_write(){
		    if(!is_sending){
		        is_sending = true;
		        std::size_t length = send_buffer.size();
		        if(((length - offset) < MAX_BUFFER_LENGTH) && ((length - offset) > 0)){
		            for( std::size_t i = 0; i < (length - offset); ++i){
		                send_data[i] = send_buffer[i+offset];
		            }
		            boost::asio::async_write(socket, boost::asio::buffer(send_data,(length - offset)),
		                    boost::bind(&session::handle_write, this, boost::asio::placeholders::error));
		            offset += length - offset;	
		        }
		        else if(((length - offset) >= MAX_BUFFER_LENGTH)){
		            for( std::size_t i = 0; i < MAX_BUFFER_LENGTH; ++i){
		                send_data[i] = send_buffer[i+offset];
		            }
		            boost::asio::async_write(socket, boost::asio::buffer(send_data,MAX_BUFFER_LENGTH),
		                    boost::bind(&session::handle_write, this, boost::asio::placeholders::error));

		            offset += MAX_BUFFER_LENGTH;	
		        }
		        else{
		            send_buffer.clear();
		            offset = 0;
		            is_sending = false;
		            //std::cout << "Transmission Success !" << std::endl;
		        }
		    }
		}
        void handle_read(const boost::system::error_code& error, size_t bytes_transferred){
	        if(!error){
		        for(std::size_t i = 0; i < bytes_transferred; ++i){
		            received_buffer.push_back(data_[i]);
		        }
		        std::string temp_str;
		        temp_str.insert(temp_str.begin(), received_buffer.begin(), received_buffer.end());
		        read_handler(temp_str);
		        received_buffer.clear();
		        socket.async_read_some(boost::asio::buffer(data_,MAX_BUFFER_LENGTH),
		                boost::bind(&session::handle_read, this, 
		                    boost::asio::placeholders::error, 
		                    boost::asio::placeholders::bytes_transferred));
		    }
		    else{
		        delete this;
		    }
	    }
		void handle_write(const boost::system::error_code& error){
		    //    std::cout<< "HANDLE WRITE"<< std::endl;
		    if(!error){
		        std::size_t length = send_buffer.size();
		        //std::cout << "WRITE: " << offset << "/ " << length << std::endl;
		        if(((length - offset) < MAX_BUFFER_LENGTH) && ((length - offset) > 0)){
		            for( std::size_t i = 0; i < (length - offset); ++i){
		                send_data[i] = send_buffer[i+offset];
		            }
		            boost::asio::async_write(socket, boost::asio::buffer(send_data,(length - offset)),
		                    boost::bind(&session::handle_write, this, boost::asio::placeholders::error));

		            offset += length - offset;	
		        }
		        else if(((length - offset) >= MAX_BUFFER_LENGTH)){
		            for( std::size_t i = 0; i < MAX_BUFFER_LENGTH; ++i){
		                send_data[i] = send_buffer[i+offset];
		            }
		            boost::asio::async_write(socket, boost::asio::buffer(send_data,MAX_BUFFER_LENGTH),
		                    boost::bind(&session::handle_write, this, boost::asio::placeholders::error));

		            offset += MAX_BUFFER_LENGTH;	
		        }
		        else{

		            send_buffer.clear();
		            offset = 0;
		            is_sending = false;
		            //std::cout << "Transmission Success !" << std::endl;
		        }
		    }		 
		}
    private:

        bool is_sending;
		bool client_rcv;
        tcp::socket socket;

        int offset;

        unsigned char data_[MAX_BUFFER_LENGTH];
        unsigned char send_data[MAX_BUFFER_LENGTH];

        std::vector<unsigned char> received_buffer;
        std::vector<unsigned char> send_buffer;
    };
};


