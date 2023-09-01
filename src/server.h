#pragma once

#include <asio2/websocket/ws_server.hpp>
#include <cstdio>
#include <cstring>
#include <memory>

#include "asio2/base/server.hpp"
#include "hda_client.h"
#include "log_helper.hpp"

struct wbserver
{
  public:
	static wbserver& get()
	{
		static wbserver s;
		return s;
	}

	void send(std::string&& s);
	int	 run();

  private:
	wbserver(){};
	asio2::ws_server				   server;
	std::shared_ptr<hda_client>		   hda_client_;
	std::shared_ptr<asio2::ws_session> client;
};
