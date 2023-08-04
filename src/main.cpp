#include <thread>

#include "common.hpp"
#include "freerdp/freerdp.h"
#include "log_helper.hpp"
#include "use_header.hpp"
#include "winpr/synch.h"
#include "winpr/wtypes.h"

static BOOL wfreerdp_client_global_init(void)
{
	//	WSADATA wsaData;
	// WSAStartup(0x101, &wsaData);
	// freerdp_register_addin_provider(freerdp_channels_load_static_addin_entry, 0);

	LOG_INFO("wfreerdp_client_global_init");

	freerdp_handle_signals();
	return TRUE;
}

static void wfreerdp_client_global_uninit(void)
{
	LOG_INFO("wfreerdp_client_global_uninit");
	// WSACleanup();
}

static BOOL wfreerdp_client_new(freerdp* instance, rdpContext* context)
{
	LOG_INFO("wfreerdp_client_new");

	// 忽略服务器证书
	instance->settings->IgnoreCertificate = true;

	instance->PreConnect = [](freerdp* instance) -> BOOL {
		LOG_INFO("pre connect...");

		rdpGraphics* graphics = instance->context->graphics;

		// 初始化位图处理回调
		// init_bitmap_callbacks(graphics);

		// 初始化字形处理回调
		// init_glyph_callbacks(graphics);

		// 初始化指针处理回调
		// init_pointer_callbacks(graphics);

		return true;
	};
	instance->PostConnect = [](freerdp* instance) -> BOOL {
		LOG_INFO("PostConnect..");
		return true;
	};
	instance->PostDisconnect = [](freerdp* instance) { LOG_INFO("PostDisconnect..."); };

	instance->Authenticate =
		[](freerdp* instance, char** username, char** password, char** domain) -> BOOL {
		LOG_INFO("Authenticate");

		*username = "ly";
		*password = "1";
		LOG_INFO("认证....");
		return true;
	};

	// bool isConsole = true;
	// if (isConsole) {
	instance->VerifyCertificateEx = [](freerdp*	   instance,
									   const char* host,
									   UINT16	   port,
									   const char* common_name,
									   const char* subject,
									   const char* issuer,
									   const char* fingerprint,
									   DWORD	   flags) -> DWORD {
		// todo  忽略服务器证书.. 看样子 直接return 一个2 就可以了

		if (instance->settings->IgnoreCertificate) {
			LOG_INFO("Certificate validation bypassed");
			return 2; /* Accept only for this session */
		}
		return 0;
	};
	return true;
}

static void wfreerdp_client_free(freerdp* instance, rdpContext* context)
{
	LOG_INFO("wfreerdp_client_free");
	if (!context)
		return;
}

static int wfreerdp_client_start(rdpContext* context)
{
	LOG_INFO("wfreerdp_client_start");

	freerdp*	instance = context->instance;
	std::thread t1([&]() {
		if (!freerdp_connect(instance)) {
			LOG_ERROR("Connection failed...");
		};
		HANDLE handles[64];
		while (!freerdp_shall_disconnect(instance)) {
			DWORD nCount = 0;
			{
				DWORD result = freerdp_get_event_handles(context, &handles[nCount], 64 - nCount);
				if (result > 0) {
					LOG_INFO("Events ready: {}", result);
				} else {
					LOG_ERROR("No events ready...");
					break;
				}
				nCount += result;
			}

			DWORD waitStatus = WaitForMultipleObjects(nCount, handles, FALSE, INFINITE);
			if (waitStatus == WAIT_FAILED) {
				LOG_ERROR("WaitForMultipleObjects failed: {}", GetLastError());
				break;
			}

			{
				if (!freerdp_check_event_handles(context)) {
					LOG_ERROR("Failed to check FreeRDP event handles");
					if (freerdp_get_last_error(context) == FREERDP_ERROR_SUCCESS) {
						LOG_ERROR("Connection closed");
					}
					break;
				}
			}
		}
	});

	t1.join();

	return 0;
}

static int wfreerdp_client_stop(rdpContext* context)
{
	LOG_INFO("wfreerdp_client_stop");
	return 0;
}

int RdpClientEntry(RDP_CLIENT_ENTRY_POINTS* pEntryPoints)
{
	pEntryPoints->Version	   = 1;
	pEntryPoints->Size		   = sizeof(RDP_CLIENT_ENTRY_POINTS_V1);
	pEntryPoints->GlobalInit   = wfreerdp_client_global_init;
	pEntryPoints->GlobalUninit = wfreerdp_client_global_uninit;
	pEntryPoints->ContextSize  = 0;

	pEntryPoints->ClientNew	  = wfreerdp_client_new;
	pEntryPoints->ClientFree  = wfreerdp_client_free;
	pEntryPoints->ClientStart = wfreerdp_client_start;
	pEntryPoints->ClientStop  = wfreerdp_client_stop;
	return 0;
}

int main(int argc, char* argv[])
{
	// FREERDP_ERROR_CONNECT_TRANSPORT_FAILED
	RDP_CLIENT_ENTRY_POINTS clientEntryPoints = {0};

	RdpClientEntry(&clientEntryPoints);

	rdpContext* context = freerdp_client_context_new(&clientEntryPoints);

	rdpSettings* settings = context->settings;
	int			 status	  = freerdp_client_settings_parse_command_line(settings, argc, argv, FALSE);

	LOG_INFO("ip: {},{}", settings->ServerHostname, settings->ServerPort);
	if (freerdp_client_start(context) != 0) {
		LOG_ERROR("connect error ");
	}
	LOG_INFO("connect error ");

	getchar();

	return 0;
}
