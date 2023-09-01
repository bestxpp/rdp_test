#include "hda_client.h"

#include <math.h>

#include <algorithm>
#include <thread>

#include "freerdp/client.h"
#include "log_helper.hpp"
#include "server.h"

void guac_rdp_push_settings(freerdp* rdp)
{
	rdpSettings* rdp_settings = rdp->settings;

	/* Authentication */
	rdp_settings->Domain   = NULL;
	rdp_settings->Username = strdup("ly");
	rdp_settings->Password = strdup("1");

	/* Connection */
	rdp_settings->ServerHostname = strdup("192.168.68.134");
	rdp_settings->ServerPort	 = 3389;

	/* Session */
	rdp_settings->ColorDepth	 = 16;
	rdp_settings->DesktopWidth	 = 800;
	rdp_settings->DesktopHeight	 = 600;
	rdp_settings->AlternateShell = NULL;

	// 键盘暂时注释
	// rdp_settings->KeyboardLayout = guac_settings->server_layout->freerdp_keyboard_layout;

	/* Performance flags */
	/* Explicitly set flag value */
	rdp_settings->PerformanceFlags = PERF_FLAG_NONE;

	/* Set individual flags - some FreeRDP versions overwrite the above */
	rdp_settings->AllowFontSmoothing	  = false;
	rdp_settings->DisableWallpaper		  = true;
	rdp_settings->DisableFullWindowDrag	  = true;
	rdp_settings->DisableMenuAnims		  = true;
	rdp_settings->DisableThemes			  = true;
	rdp_settings->AllowDesktopComposition = false;

	/* Client name */
	// if (guac_settings->client_name != NULL) {
	// 	guac_strlcpy(rdp_settings->ClientHostname, guac_settings->client_name, RDP_CLIENT_HOSTNAME_SIZE);
	// }
	rdp_settings->ClientHostname = strdup("test");

	/* Console */
	rdp_settings->ConsoleSession	 = false;
	rdp_settings->RemoteConsoleAudio = false;

	/* Audio */
	rdp_settings->AudioPlayback = false;

	/* Audio capture */
	rdp_settings->AudioCapture = false;

	/* Display Update channel */
	rdp_settings->SupportDisplayControl = false;  //(guac_settings->resize_method == GUAC_RESIZE_DISPLAY_UPDATE);

	/* Device redirection */
	rdp_settings->DeviceRedirection = false;

	/* Security */
	switch (5) {
		/* Legacy RDP encryption */
		case GUAC_SECURITY_RDP:
			rdp_settings->RdpSecurity		  = TRUE;
			rdp_settings->TlsSecurity		  = FALSE;
			rdp_settings->NlaSecurity		  = FALSE;
			rdp_settings->ExtSecurity		  = FALSE;
			rdp_settings->UseRdpSecurityLayer = TRUE;
			rdp_settings->EncryptionLevel	  = ENCRYPTION_LEVEL_CLIENT_COMPATIBLE;
			rdp_settings->EncryptionMethods =
				ENCRYPTION_METHOD_40BIT | ENCRYPTION_METHOD_128BIT | ENCRYPTION_METHOD_FIPS;
			break;

		/* TLS encryption */
		case GUAC_SECURITY_TLS:
			rdp_settings->RdpSecurity = FALSE;
			rdp_settings->TlsSecurity = TRUE;
			rdp_settings->NlaSecurity = FALSE;
			rdp_settings->ExtSecurity = FALSE;
			break;

		/* Network level authentication */
		case GUAC_SECURITY_NLA:
			rdp_settings->RdpSecurity = FALSE;
			rdp_settings->TlsSecurity = FALSE;
			rdp_settings->NlaSecurity = TRUE;
			rdp_settings->ExtSecurity = FALSE;
			break;

		/* Extended network level authentication */
		case GUAC_SECURITY_EXTENDED_NLA:
			rdp_settings->RdpSecurity = FALSE;
			rdp_settings->TlsSecurity = FALSE;
			rdp_settings->NlaSecurity = FALSE;
			rdp_settings->ExtSecurity = TRUE;
			break;

		/* Hyper-V "VMConnect" negotiation mode */
		case GUAC_SECURITY_VMCONNECT:
			rdp_settings->RdpSecurity	= FALSE;
			rdp_settings->TlsSecurity	= TRUE;
			rdp_settings->NlaSecurity	= TRUE;
			rdp_settings->ExtSecurity	= FALSE;
			rdp_settings->VmConnectMode = TRUE;
			break;

		/* All security types */
		case GUAC_SECURITY_ANY:
			rdp_settings->RdpSecurity = TRUE;
			rdp_settings->TlsSecurity = TRUE;
			rdp_settings->NlaSecurity = TRUE;
			rdp_settings->ExtSecurity = FALSE;
			break;
	}

	/* Authentication */
	rdp_settings->Authentication	= TRUE;
	rdp_settings->IgnoreCertificate = TRUE;

	/* RemoteApp */
	// if (guac_settings->remote_app != NULL) {
	// 	rdp_settings->Workarea						= TRUE;
	// 	rdp_settings->RemoteApplicationMode			= TRUE;
	// 	rdp_settings->RemoteAppLanguageBarSupported = TRUE;
	// 	rdp_settings->RemoteApplicationProgram		= guac_strdup(guac_settings->remote_app);
	// 	rdp_settings->ShellWorkingDirectory			= guac_strdup(guac_settings->remote_app_dir);
	// 	rdp_settings->RemoteApplicationCmdLine		= guac_strdup(guac_settings->remote_app_args);
	// }

	// /* Preconnection ID */
	// if (guac_settings->preconnection_id != -1) {
	// 	rdp_settings->NegotiateSecurityLayer = FALSE;
	// 	rdp_settings->SendPreconnectionPdu	 = TRUE;
	// 	rdp_settings->PreconnectionId		 = guac_settings->preconnection_id;
	// }

	// /* Preconnection BLOB */
	// if (guac_settings->preconnection_blob != NULL) {
	// 	rdp_settings->NegotiateSecurityLayer = FALSE;
	// 	rdp_settings->SendPreconnectionPdu	 = TRUE;
	// 	rdp_settings->PreconnectionBlob		 = guac_strdup(guac_settings->preconnection_blob);
	// }

	/* Enable use of RD gateway if a gateway hostname is provided */
	// if (guac_settings->gateway_hostname != NULL) {
	// 	/* Enable RD gateway */
	// 	rdp_settings->GatewayEnabled = TRUE;

	// 	/* RD gateway connection details */
	// 	rdp_settings->GatewayHostname = guac_strdup(guac_settings->gateway_hostname);
	// 	rdp_settings->GatewayPort	  = guac_settings->gateway_port;

	// 	/* RD gateway credentials */
	// 	rdp_settings->GatewayUseSameCredentials = FALSE;
	// 	rdp_settings->GatewayDomain				= guac_strdup(guac_settings->gateway_domain);
	// 	rdp_settings->GatewayUsername			= guac_strdup(guac_settings->gateway_username);
	// 	rdp_settings->GatewayPassword			= guac_strdup(guac_settings->gateway_password);
	// }

	/* Store load balance info (and calculate length) if provided */
	// if (guac_settings->load_balance_info != NULL) {
	// 	rdp_settings->LoadBalanceInfo		= (BYTE*)guac_strdup(guac_settings->load_balance_info);
	// 	rdp_settings->LoadBalanceInfoLength = strlen(guac_settings->load_balance_info);
	// }

	rdp_settings->BitmapCacheEnabled	= true;
	rdp_settings->OffscreenSupportLevel = TRUE;

	// rdp_settings->GlyphSupportLevel = !guac_settings->disable_glyph_caching ? GLYPH_SUPPORT_FULL : GLYPH_SUPPORT_NONE;
	// 如果开启字形缓存，win server 2008 r2 点击命令行崩溃， GLYPH_SUPPORT_FULL
	rdp_settings->GlyphSupportLevel = GLYPH_SUPPORT_NONE;

	rdp_settings->OsMajorType	= OSMAJORTYPE_UNSPECIFIED;
	rdp_settings->OsMinorType	= OSMINORTYPE_UNSPECIFIED;
	rdp_settings->DesktopResize = TRUE;
	/* Claim support only for specific updates, independent of FreeRDP defaults */
	ZeroMemory(rdp_settings->OrderSupport, 32);
	rdp_settings->OrderSupport[NEG_DSTBLT_INDEX]	= TRUE;
	rdp_settings->OrderSupport[NEG_SCRBLT_INDEX]	= TRUE;
	rdp_settings->OrderSupport[NEG_MEMBLT_INDEX]	= TRUE;
	rdp_settings->OrderSupport[NEG_MEMBLT_V2_INDEX] = TRUE;

	rdp_settings->OrderSupport[NEG_GLYPH_INDEX_INDEX] = TRUE;
	rdp_settings->OrderSupport[NEG_FAST_INDEX_INDEX]  = TRUE;
	rdp_settings->OrderSupport[NEG_FAST_GLYPH_INDEX]  = TRUE;

#ifdef HAVE_RDPSETTINGS_ALLOWUNANOUNCEDORDERSFROMSERVER
	/* Do not consider server use of unannounced orders to be a fatal error */
	rdp_settings->AllowUnanouncedOrdersFromServer = TRUE;
#endif

	// rdp_settings->FastPathInput=FALSE;
	// rdp_settings->FastPathOutput=FALSE;
}

BOOL guac_rdp_gdi_desktop_resize(rdpContext* context)
{
	return TRUE;
}

BOOL guac_rdp_gdi_end_paint(rdpContext* context)
{
	/* IGNORE */
	return TRUE;
}

BOOL guac_rdp_gdi_set_bounds(rdpContext* context, const rdpBounds* bounds)
{
	return TRUE;
}

BOOL guac_rdp_gdi_dstblt(rdpContext* context, const DSTBLT_ORDER* dstblt)
{
	return TRUE;
}

BOOL guac_rdp_gdi_patblt(rdpContext* context, PATBLT_ORDER* patblt)
{
	return TRUE;
}

BOOL guac_rdp_gdi_scrblt(rdpContext* context, const SCRBLT_ORDER* scrblt)
{
	return TRUE;
}

BOOL guac_rdp_gdi_memblt(rdpContext* context, MEMBLT_ORDER* memblt)
{
	{
		/*
		rdpBitmap* bitmap = (rdpBitmap*)memblt->bitmap;
		// 获取图像数据
		BYTE* imageData = bitmap->data;
		// TODO: 根据需要转换图像数据
		// 生成唯一的文件名
		char filename[256] = {};
		snprintf(filename, sizeof(filename), "output_%d.png", image_counter++);

		// 使用libpng保存图像数据为PNG
		FILE*		fp		 = fopen(filename, "wb");
		png_structp png_ptr	 = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		png_infop	info_ptr = png_create_info_struct(png_ptr);
		png_init_io(png_ptr, fp);
		png_set_IHDR(png_ptr, info_ptr, bitmap->width, bitmap->height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
		png_write_info(png_ptr, info_ptr);

		// TODO: 根据图像数据的格式调整此部分
		for (int y = 0; y < bitmap->height; y++) {
			png_write_row(png_ptr, &imageData[y * bitmap->width * 4]);
		}

		png_write_end(png_ptr, NULL);
		fclose(fp);
		*/
	}

	{
		rdpBitmap* bitmap = (rdpBitmap*)memblt->bitmap;
		// 获取图像数据
		BYTE* imageData = bitmap->data;

		// 使用libpng保存图像数据到内存
		png_structp png_ptr	 = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		png_infop	info_ptr = png_create_info_struct(png_ptr);

		// 设置内存写入
		std::vector<png_byte> buffer;
		png_set_write_fn(
			png_ptr,
			&buffer,
			[](png_structp png_ptr, png_bytep data, png_size_t length) {
				auto& buf = *reinterpret_cast<std::vector<png_byte>*>(png_get_io_ptr(png_ptr));
				buf.insert(buf.end(), data, data + length);
			},
			nullptr);

		png_set_IHDR(png_ptr, info_ptr, bitmap->width, bitmap->height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
		png_write_info(png_ptr, info_ptr);

		// TODO: 根据图像数据的格式调整此部分
		for (int y = 0; y < bitmap->height; y++) {
			png_write_row(png_ptr, &imageData[y * bitmap->width * 4]);
		}

		png_write_end(png_ptr, NULL);

		ImageData imgData;
		imgData.x		= memblt->nLeftRect;
		imgData.y		= memblt->nTopRect;
		imgData.width	= bitmap->width;
		imgData.height	= bitmap->height;
		imgData.pngData = std::move(buffer);

		LOG_ERROR("x={},y={},w={},h={}", imgData.x, imgData.y, imgData.width, imgData.y);

		std::string serializedData = serialize(imgData);
		//  使用send接口发送数据
		wbserver::get().send(std::move(serializedData));
	}

	return TRUE;
}

BOOL guac_rdp_gdi_opaquerect(rdpContext* context, const OPAQUE_RECT_ORDER* opaque_rect)
{
	return TRUE;
}

UINT32 guac_rdp_get_native_pixel_format(BOOL alpha)
{
	uint32_t int_value;
	uint8_t	 raw_bytes[4] = {0x0A, 0x0B, 0x0C, 0x0D};

	memcpy(&int_value, raw_bytes, sizeof(raw_bytes));

	/* Local platform stores bytes in decreasing order of significance
	 * (big-endian) */
	if (int_value == 0x0A0B0C0D)
		return alpha ? PIXEL_FORMAT_ARGB32 : PIXEL_FORMAT_XRGB32;

	/* Local platform stores bytes in increasing order of significance
	 * (little-endian) */
	else
		return alpha ? PIXEL_FORMAT_BGRA32 : PIXEL_FORMAT_BGRX32;
}

BOOL rdp_freerdp_pre_connect(freerdp* instance)
{
	guac_rdp_push_settings(instance);

	freerdp_register_addin_provider(freerdp_channels_load_static_addin_entry, 0);

	if (!gdi_init(instance, guac_rdp_get_native_pixel_format(FALSE))) {
		return FALSE;
	}

	/* Set up bitmap handling */
	rdpContext*	 context  = instance->context;
	rdpGraphics* graphics = context->graphics;

	rdpBitmap bitmap  = *graphics->Bitmap_Prototype;
	bitmap.size		  = sizeof(guac_rdp_bitmap);
	bitmap.New		  = guac_rdp_bitmap_new;
	bitmap.Free		  = guac_rdp_bitmap_free;
	bitmap.Paint	  = guac_rdp_bitmap_paint;
	bitmap.SetSurface = guac_rdp_bitmap_setsurface;
	graphics_register_bitmap(graphics, &bitmap);

	/* Set up glyph handling */
	rdpGlyph glyph	= *graphics->Glyph_Prototype;
	glyph.size		= sizeof(guac_rdp_glyph);
	glyph.New		= guac_rdp_glyph_new;
	glyph.Free		= guac_rdp_glyph_free;
	glyph.Draw		= guac_rdp_glyph_draw;
	glyph.BeginDraw = guac_rdp_glyph_begindraw;
	glyph.EndDraw	= guac_rdp_glyph_enddraw;
	graphics_register_glyph(graphics, &glyph);

	/* Set up pointer handling */
	rdpPointer pointer = *graphics->Pointer_Prototype;
	pointer.size	   = sizeof(guac_rdp_pointer);
	pointer.New		   = guac_rdp_pointer_new;
	pointer.Free	   = guac_rdp_pointer_free;
	pointer.Set		   = guac_rdp_pointer_set;
	pointer.SetNull	   = guac_rdp_pointer_set_null;
	pointer.SetDefault = guac_rdp_pointer_set_default;
	graphics_register_pointer(graphics, &pointer);

	instance->update->PlaySound				= NULL;	 // guac_rdp_beep_play_sound;
	instance->update->SetKeyboardIndicators = NULL;	 // guac_rdp_keyboard_set_indicators;

	instance->update->DesktopResize = guac_rdp_gdi_desktop_resize;
	instance->update->EndPaint		= guac_rdp_gdi_end_paint;
	instance->update->SetBounds		= guac_rdp_gdi_set_bounds;

	rdpPrimaryUpdate* primary = instance->update->primary;
	primary->DstBlt			  = guac_rdp_gdi_dstblt;
	primary->PatBlt			  = guac_rdp_gdi_patblt;
	primary->ScrBlt			  = guac_rdp_gdi_scrblt;
	primary->MemBlt			  = guac_rdp_gdi_memblt;
	primary->OpaqueRect		  = guac_rdp_gdi_opaquerect;

	pointer_cache_register_callbacks(instance->update);
	glyph_cache_register_callbacks(instance->update);
	brush_cache_register_callbacks(instance->update);
	bitmap_cache_register_callbacks(instance->update);
	offscreen_cache_register_callbacks(instance->update);
	palette_cache_register_callbacks(instance->update);

	return TRUE;
}

BOOL rdp_freerdp_authenticate(freerdp* instance, char** username, char** password, char** domain)
{
	LOG_ERROR("认证....");
	*username = strdup("ly");
	*password = strdup("1");
	*domain	  = NULL;
	return TRUE;
}

DWORD rdp_freerdp_verify_certificate(freerdp*	 instance,
									 const char* host,
									 UINT16		 port,
									 const char* common_name,
									 const char* subject,
									 const char* issuer,
									 const char* fingerprint,
									 DWORD		 flags)
{
	/* Bypass validation if ignore_certificate given */

	LOG_ERROR("开始认证");

	if (instance->settings->IgnoreCertificate) {
		return 2; /* Accept only for this session */
	}
	return 0; /* Reject certificate */
}

void hda_client::Start()
{
	std::thread t1([self = shared_from_this()]() {
		freerdp* rdp_inst			  = freerdp_new();
		rdp_inst->PreConnect		  = rdp_freerdp_pre_connect;
		rdp_inst->Authenticate		  = rdp_freerdp_authenticate;
		rdp_inst->VerifyCertificateEx = rdp_freerdp_verify_certificate;

		if (!freerdp_context_new(rdp_inst)) {
			LOG_ERROR("failed ...........");
		}

		DWORD  nCount;
		DWORD  status;
		DWORD  result	   = 0;
		HANDLE handles[64] = {0};
		if (!freerdp_connect(rdp_inst)) {
			LOG_ERROR("failed ...........");
		}

		self->freerdpins_ = rdp_inst;

		// 开启鼠标
		// 开启键盘。
		while (!freerdp_shall_disconnect(rdp_inst)) {
			// LOG_ERROR("while..............");

			nCount = freerdp_get_event_handles(rdp_inst->context, &handles[0], 64);

			if (nCount == 0) {
				LOG_ERROR("freerdp_get_event_handles failed {}", __FUNCTION__);
				break;
			}

			status = WaitForMultipleObjects(nCount, handles, FALSE, 100);

			if (status == WAIT_FAILED) {
				LOG_ERROR("{}: WaitForMultipleObjects failed with {}", __FUNCTION__, status);
				break;
			}

			if (!freerdp_check_event_handles(rdp_inst->context)) {
				if (freerdp_get_last_error(rdp_inst->context) == FREERDP_ERROR_SUCCESS) {
					LOG_ERROR("Failed to check FreeRDP event handles");
				}
				break;
			}
		}
		LOG_ERROR("线程退出。。。。");
	});
	work_thread_ = std::move(t1);
}

void hda_client::Stop()
{
	if (freerdpins_) {
		freerdp_disconnect(freerdpins_);
		// freerdp_free(freerdpins_);
	}
}

void hda_client::SendMouseEvent(MouseEvent& ms)
{
	if (freerdpins_) {
		int x	 = ms.x;
		int y	 = ms.y;
		int mask = ms.mask;

		if (ms.mask == cur_mask_) {
			freerdpins_->input->MouseEvent(freerdpins_->input, PTR_FLAGS_MOVE, ms.x, ms.y);
		}
		else {
			/* Mouse buttons which have JUST become released */
			int released_mask = cur_mask_ & ~mask;

			/* Mouse buttons which have JUST become pressed */
			int pressed_mask = ~cur_mask_ & mask;

			/* Release event */
			if (released_mask & 0x07) {
				/* Calculate flags */
				int flags = 0;
				if (released_mask & 0x01)
					flags |= PTR_FLAGS_BUTTON1;
				if (released_mask & 0x02)
					flags |= PTR_FLAGS_BUTTON3;
				if (released_mask & 0x04)
					flags |= PTR_FLAGS_BUTTON2;

				freerdpins_->input->MouseEvent(freerdpins_->input, flags, x, y);
			}

			/* Press event */
			if (pressed_mask & 0x07) {
				/* Calculate flags */
				int flags = PTR_FLAGS_DOWN;
				if (pressed_mask & 0x01)
					flags |= PTR_FLAGS_BUTTON1;
				if (pressed_mask & 0x02)
					flags |= PTR_FLAGS_BUTTON3;
				if (pressed_mask & 0x04)
					flags |= PTR_FLAGS_BUTTON2;
				if (pressed_mask & 0x08)
					flags |= PTR_FLAGS_WHEEL | 0x78;
				if (pressed_mask & 0x10)
					flags |= PTR_FLAGS_WHEEL | PTR_FLAGS_WHEEL_NEGATIVE | 0x88;

				/* Send event */
				freerdpins_->input->MouseEvent(freerdpins_->input, flags, x, y);
			}

			/* Scroll event */
			if (pressed_mask & 0x18) {
				/* Down */
				if (pressed_mask & 0x08)
					freerdpins_->input->MouseEvent(freerdpins_->input, PTR_FLAGS_WHEEL | 0x78, x, y);

				/* Up */
				if (pressed_mask & 0x10)
					freerdpins_->input->MouseEvent(
						freerdpins_->input,
						PTR_FLAGS_WHEEL | PTR_FLAGS_WHEEL_NEGATIVE | 0x88,
						x,
						y);
			}
			cur_mask_ = mask;
		}
	}
}