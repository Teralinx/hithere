#include <asio.hpp>
#include <gtest/gtest.h>

TEST(ASIOUDPREVCDATA_TEST, NORMAL) {
    asio::io_context io_context;
    asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), 12345);
    asio::ip::udp::socket socket(io_context);
    socket.open(asio::ip::udp::v4());
    socket.bind(endpoint);
    std::string data = "Hello, World!";
    while (true)
    {
        std::array<char, 1024> recv_buf;
        asio::ip::udp::endpoint sender_endpoint;
        try
        {
            size_t len = socket.receive_from(asio::buffer(recv_buf), sender_endpoint);
            std::cout << "Received: " << std::string(recv_buf.data(), len) << std::endl;
            socket.send_to(asio::buffer(data), sender_endpoint);
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}