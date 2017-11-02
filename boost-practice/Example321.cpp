#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>

using namespace boost::asio;

void handler(const boost::system::error_code&){

	std::cout << "3 sec " << std::endl;

}

int main()
{
  io_service ioservice;

  // steady_timer timer{ioservice, std::chrono::seconds{3}};
  steady_timer timer(ioservice);

  timer.expires_from_now(std::chrono::seconds(3));
  // timer.async_wait([](const boost::system::error_code &ec)
  // { std::cout << "3 sec\n"; });

  boost::system::error_code ec;

  timer.async_wait(handler);

  ioservice.run();

}

// compile with:
// g++ -std=c++11 Example321.cpp -o Example321 -lboost_system