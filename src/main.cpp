#include <curl/curl.h>
#include "global.h"
#include <thread>
#include <asio.hpp>
#include <iostream>


int main(int argc, char* argv[])
{
	initlizeSpdlog();
	curl_global_init(CURL_GLOBAL_ALL);	
	std::string strip;
	getpublicipaddress(strip);

    try {
        asio::io_context io_context;

        // Create a UDP socket
        asio::ip::udp::socket socket(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 12345));

        while (true) {
            char recv_buf[1024];
            asio::ip::udp::endpoint sender_endpoint;

            // Receive data
            size_t len = socket.receive_from(asio::buffer(recv_buf), sender_endpoint);
            socket.send_to(asio::buffer(recv_buf, len), sender_endpoint);
            // Print received data
            std::cout << "Received: ";
            std::cout.write(recv_buf, len);
            std::cout << std::endl;
        }

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

	return 0;
}


