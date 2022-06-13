#ifndef BLITZ_INCLUDE_CORE_ASIO_H
#define BLITZ_INCLUDE_CORE_ASIO_H

#include <boost/asio.hpp>

#define BLITZ_ALPHA_NOEXCEPT BLITZ_NOEXCEPT

namespace blitz {

/* struct Session {
  std::shared_ptr<boost::asio::ip::tcp::socket> sock;
  string buf;
};

void callback(const boost::system::error_code &ec) { cout << "done!" << endl; }

void socket_write(std::shared_ptr<asio::ip::tcp::socket> sock) {
  std::shared_ptr<Session> s(new Session);

  s->buf = std::string("Hello");
  s->sock = sock; */
  // Step 5. Initiating asynchronous write operation.
  // asio::async_write(s->sock, asio::buffer(s->buf), std::bind(callback));


// void socket_write(boost::asio::ip::tcp::socket& sock);

/* template <boost::asio::completion_handler_for<void(boost::asio::error_code
&ec)> CompletionToken> auto async_read_some(boost::asio::ip::tcp::socket &s,
const boost::asio:mutable_buffer &b, CompletionToken &&token) { auto init =
[](auto completion_handler, boost::asio::ip::tcp::socket *s, const
boost::asio::mutable_buffer &b) { std::thread(
        [](auto completion_handler, boost::asio::ip::tcp::socket *s,
           const boost::asio::mutable_buffer &b) {
          boost::asio::error_code ec;
          size_t n = s->read_some(b, ec);
          std::move(completion_handler)(ec, n);
        },
        std::move(completion_handler), s, b)
        .detach();
  };
  return boost::asio::async_result<decay_t<CompletionToken>,
void(boost::asio::error_code, size_t)>:: initiate(init,
std::forward<CompletionToken>(token), &s, b);
} */

} // namespace alpha

#endif