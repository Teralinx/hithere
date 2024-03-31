#include <asio.hpp>
#include <gtest/gtest.h>
#include "global.h"
TEST(ASIOUDPSENDDATA_TEST, NORMAL) {
    asio::io_context io_context;
    asio::ip::udp::socket socket(io_context);
    asio::ip::udp::endpoint endpoint(asio::ip::make_address("127.0.0.1"), 12345);

    socket.open(asio::ip::udp::v4());

    std::string data = "Hello, World!";
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        try
        {
            socket.send_to(asio::buffer(data), endpoint);
            asio::ip::udp::endpoint sender_endpoint;
            std::array<char, 1024> recv_buf;
            size_t len = socket.receive_from(asio::buffer(recv_buf), sender_endpoint);
            std::cout << "Received: " << std::string(recv_buf.data(), len) << std::endl;
		}
        catch (std::exception& e)
        {
            QUICKLOG(e.what());
		}

    }
}