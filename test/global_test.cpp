#include "../src/global.h"
#include <gtest/gtest.h>
#include <curl/curl.h>
#include <asio.hpp>


TEST(GETIP_TEST, NORAMAL) {

	curl_global_init(CURL_GLOBAL_ALL);	
	std::string ip;
	getpublicipaddress(ip);
}


TEST(SEND_DATA, NORAMAL) {
    try {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        asio::io_context io_context;
        asio::ip::udp::socket socket(io_context, asio::ip::udp::v4());

        // Create the remote endpoint directly
        asio::ip::udp::endpoint remote_endpoint(asio::ip::address::from_string("127.0.0.1"), 12345);

        std::string send_message = "Hello, Server!\n";
        socket.send_to(asio::buffer(send_message), remote_endpoint);

        char recv_buf[1024];
        asio::ip::udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf, len);
        std::cout << std::endl;

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


	
}



