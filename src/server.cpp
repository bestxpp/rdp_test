#include "server.h"

#include <math.h>

#include <cstring>

#include "common.hpp"
#include "log_helper.hpp"

void wbserver::send(std::string&& s)
{
	if (client != nullptr && client->is_started()) {
		client->async_send(s);
	}
}

int wbserver::run()
{
	std::string_view host = "0.0.0.0";
	std::string_view port = "8039";

	server.bind_accept([&](std::shared_ptr<asio2::ws_session>& session_ptr) {
			  // accept callback maybe has error like "Too many open files", etc...
			  if (!asio2::get_last_error()) {
				  // Set the binary message write option.
				  session_ptr->ws_stream().binary(true);

				  // Set the text message write option. The sent text must be utf8 format.
				  // session_ptr->ws_stream().text(true);

				  // how to set custom websocket response data :
				  // the decorator is just a callback function, when the upgrade response is send,
				  // this callback will be called.
			  }
			  else {
				  printf("error occurred when calling the accept function : %d %s\n",
						 asio2::get_last_error_val(),
						 asio2::get_last_error_msg().data());
			  }
		  })
		.bind_recv([&](auto& session_ptr, std::string_view data) {
			//		printf("recv : %zu %.*s\n", data.size(), (int)data.size(), data.data());

			// {
			// 	MouseEvent ms{};
			// 	ms.x	= 50;
			// 	ms.y	= 50;
			// 	ms.mask = 0;

			// 	std::string tdata = serialize_test(ms);
			// 	for (int i = 0; i < tdata.length(); i++) {
			// 		LOG_ERROR("i: {0:x}", static_cast<unsigned char>(data.at(i)));
			// 	}
			// }
			// LOG_ERROR("分割..............");
			{
				std::string str(data.data(), data.size());
				MouseEvent	moums = deserialize_test(str);

				if (hda_client_ != nullptr) {
					hda_client_->SendMouseEvent(moums);
				}
			}
		})
		.bind_connect([this](auto& session_ptr) {
			client = session_ptr;
			if (hda_client_ != nullptr) {
				hda_client_->Stop();
			}

			hda_client_.reset(new hda_client());
			hda_client_->Start();
			printf("client enter : %s %u %s %u\n",
				   session_ptr->remote_address().c_str(),
				   session_ptr->remote_port(),
				   session_ptr->local_address().c_str(),
				   session_ptr->local_port());
		})
		.bind_disconnect([this](auto& session_ptr) {
			asio2::ignore_unused(session_ptr);
			if (hda_client_ != nullptr) {
				hda_client_->Stop();
				hda_client_.reset();
			}
			printf("client leave : %s\n", asio2::last_error_msg().c_str());
		})
		.bind_upgrade([](auto& session_ptr) {
		})
		.bind_start([&]() {
			if (asio2::get_last_error())
				printf("start websocket server failure : %s %u %d %s\n",
					   server.listen_address().c_str(),
					   server.listen_port(),
					   asio2::last_error_val(),
					   asio2::last_error_msg().c_str());
			else
				printf("start websocket server success : %s %u\n",
					   server.listen_address().c_str(),
					   server.listen_port());
		})
		.bind_stop([&]() {
			printf("stop websocket server : %s %u %d %s\n",
				   server.listen_address().c_str(),
				   server.listen_port(),
				   asio2::last_error_val(),
				   asio2::last_error_msg().c_str());
		});

	server.start(host, port);
	// blocked forever util some signal delivered.
	// Normally, pressing Ctrl + C will emit the SIGINT signal.
	server.wait_signal(SIGINT, SIGTERM);
	return 0;
}