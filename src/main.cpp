/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * FreeRDP Test UI
 *
 * Copyright 2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 * Copyright 2016,2018 Armin Novak <armin.novak@thincast.com>
 * Copyright 2016,2018 Thincast Technologies GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common.hpp"
#include "log_helper.hpp"

enum guac_rdp_security
{

	/**
	 * Legacy RDP encryption.
	 */
	GUAC_SECURITY_RDP,

	/**
	 * TLS encryption.
	 */
	GUAC_SECURITY_TLS,

	/**
	 * Network level authentication.
	 */
	GUAC_SECURITY_NLA,

	/**
	 * Extended network level authentication.
	 */
	GUAC_SECURITY_EXTENDED_NLA,

	/**
	 * Negotiate security methods supported by Hyper-V's "VMConnect" feature.
	 */
	GUAC_SECURITY_VMCONNECT,

	/**
	 * Negotiate a security method supported by both server and client.
	 */
	GUAC_SECURITY_ANY

} guac_rdp_security;

void guac_rdp_push_settings(freerdp* rdp)
{
	rdpSettings* rdp_settings = rdp->settings;

	/* Authentication */
	rdp_settings->Domain   = NULL;
	rdp_settings->Username = strdup("ly");
	rdp_settings->Password = strdup("1");

	/* Connection */
	rdp_settings->ServerHostname = strdup("192.168.68.130");
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
	return TRUE;
}

BOOL guac_rdp_gdi_opaquerect(rdpContext* context, const OPAQUE_RECT_ORDER* opaque_rect)
{
	return TRUE;
}

static BOOL rdp_freerdp_pre_connect(freerdp* instance)
{
	guac_rdp_push_settings(instance);

	freerdp_register_addin_provider(freerdp_channels_load_static_addin_entry, 0);

	if (!gdi_init(instance, PIXEL_FORMAT_RGB16)) {
		return FALSE;
	}

	init_bitmap_callbacks(instance->context->graphics);
	init_glyph_callbacks(instance->context->graphics);
	init_pointer_callbacks(instance->context->graphics);

	instance->update->PlaySound				= NULL;
	instance->update->SetKeyboardIndicators = NULL;

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

static BOOL rdp_freerdp_authenticate(freerdp* instance, char** username, char** password, char** domain)
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

int main(int argc, char* argv[])
{
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

	while (!freerdp_shall_disconnect(rdp_inst)) {
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
	return 0;
}
