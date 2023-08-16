#pragma once

#include <errno.h>
#include <freerdp/log.h>
#include <freerdp/utils/signal.h>
#include <stddef.h>
#include <string.h>
#include <winpr/crt.h>

#include "freerdp/client/rdpgfx.h"
#include "log_helper.hpp"
#include "winpr/wtypes.h"

static BOOL my_bitmap_new(rdpContext* context, rdpBitmap* bitmap)
{
	// TODO: Implement custom bitmap data structure creation and initialization
	// ...
	return true;
}

static void my_bitmap_free(rdpContext* context, rdpBitmap* bitmap)
{
	// TODO: Implement custom bitmap data structure release
	// ...
}

static BOOL my_bitmap_paint(rdpContext* context, rdpBitmap* bitmap)
{
	// TODO: Implement custom bitmap drawing logic
	// ...

	// Get the width and height of the bitmap
	int width  = bitmap->width;
	int height = bitmap->height;

	// Get the pixel data of the bitmap
	BYTE* data = bitmap->data;

	// Get the length of the bitmap data
	int length = bitmap->length;

	LOG_INFO("height={}, width={}, length={}", height, width, length);

	return true;
}

static BOOL my_Bitmap_SetSurface(rdpContext* context, rdpBitmap* bitmap, BOOL primary)
{
	return true;
}

static BOOL my_glyph_new(rdpContext* context, const rdpGlyph* glyph)
{
	// TODO: Implement custom glyph data structure creation and initialization
	// ...
	return true;
}

static void my_glyph_free(rdpContext* context, rdpGlyph* glyph)
{
	// TODO: Implement custom glyph data structure release
	// ...
}

static BOOL my_glyph_draw(rdpContext*	  context,
						  const rdpGlyph* glyph,
						  INT32			  x,
						  INT32			  y,
						  INT32			  w,
						  INT32			  h,
						  INT32			  sx,
						  INT32			  sy,
						  BOOL			  fOpRedundant)
{
	// TODO: Implement custom glyph drawing logic
	// ...
	return true;
}

static BOOL my_glyph_begindraw(rdpContext* context,
							   INT32	   x,
							   INT32	   y,
							   INT32	   width,
							   INT32	   height,
							   UINT32	   bgcolor,
							   UINT32	   fgcolor,
							   BOOL		   fOpRedundant)
{
	// TODO: Implement custom preparation work before drawing glyph
	// ...
	return true;
}

static BOOL my_glyph_enddraw(rdpContext* context,
							 INT32		 x,
							 INT32		 y,
							 INT32		 width,
							 INT32		 height,
							 UINT32		 bgcolor,
							 UINT32		 fgcolor)
{
	// TODO: Implement custom post-processing work after drawing glyph
	// ...
	return true;
}

static BOOL my_pointer_new(rdpContext* context, rdpPointer* pointer)
{
	// TODO: Implement custom pointer data structure creation and initialization
	// ...

	return true;
}

static void my_pointer_free(rdpContext* context, rdpPointer* pointer)
{
	// TODO: Implement custom pointer data structure release
	// ...
}

static BOOL my_pointer_set(rdpContext* context, const rdpPointer* pointer)
{
	// TODO: Implement custom pointer drawing logic
	// ...
	return true;
}

static BOOL my_pointer_set_null(rdpContext* context)
{
	// TODO: Implement custom handling logic for a null pointer
	// ...
	return true;
}

static BOOL my_pointer_set_default(rdpContext* context)
{
	// TODO: Implement custom handling logic for a default pointer
	// ...
	return true;
}

static BOOL my_Pointer_SetPosition(rdpContext* context, UINT32 x, UINT32 y)
{
	return true;
}

// Initialization
static void init_bitmap_callbacks(rdpGraphics* graphics)
{
	LOG_INFO("init_bitmap_callbacks");
	rdpBitmap bitmap{};

	bitmap.New		  = my_bitmap_new;
	bitmap.Free		  = my_bitmap_free;
	bitmap.Paint	  = my_bitmap_paint;
	bitmap.SetSurface = my_Bitmap_SetSurface;
	graphics_register_bitmap(graphics, &bitmap);
}

static void init_glyph_callbacks(rdpGraphics* graphics)
{
	LOG_INFO("init_glyph_callbacks");
	rdpGlyph glyph{};
	glyph.New		= my_glyph_new;
	glyph.Free		= my_glyph_free;
	glyph.Draw		= my_glyph_draw;
	glyph.BeginDraw = my_glyph_begindraw;
	glyph.EndDraw	= my_glyph_enddraw;
	graphics_register_glyph(graphics, &glyph);
}

static void init_pointer_callbacks(rdpGraphics* graphics)
{
	LOG_INFO("init_pointer_callbacks");
	rdpPointer pointer{};
	pointer.size		= sizeof(rdpPointer);
	pointer.New			= my_pointer_new;
	pointer.Free		= my_pointer_free;
	pointer.Set			= my_pointer_set;
	pointer.SetNull		= my_pointer_set_null;
	pointer.SetDefault	= my_pointer_set_default;
	pointer.SetPosition = my_Pointer_SetPosition;
	graphics_register_pointer(graphics, &pointer);
}

inline void guac_rdp_push_settings(freerdp* rdp)
{
	// 	rdpSettings* rdp_settings = rdp->settings;

	// 	/* Authentication */
	// 	rdp_settings->Username = strdup("ly");
	// 	rdp_settings->Password = strdup("1");

	// 	/* Connection */
	// 	// rdp_settings->ServerHostname = guac_strdup(guac_settings->hostname);
	// 	// rdp_settings->ServerPort	 = guac_settings->port;

	// 	/* Session */
	// 	rdp_settings->ColorDepth	 = 16;
	// 	rdp_settings->DesktopWidth	 = 800;
	// 	rdp_settings->DesktopHeight	 = 600;
	// 	rdp_settings->AlternateShell = NULL;
	// 	// rdp_settings->KeyboardLayout = guac_settings->server_layout->freerdp_keyboard_layout;

	// 	/* Performance flags */
	// 	/* Explicitly set flag value */
	// 	rdp_settings->PerformanceFlags = PERF_FLAG_NONE;

	// 	/* Set individual flags - some FreeRDP versions overwrite the above */
	// 	rdp_settings->AllowFontSmoothing	  = 0;
	// 	rdp_settings->DisableWallpaper		  = 0;
	// 	rdp_settings->DisableFullWindowDrag	  = 0;
	// 	rdp_settings->DisableMenuAnims		  = 0;
	// 	rdp_settings->DisableThemes			  = 0;
	// 	rdp_settings->AllowDesktopComposition = 0;

	// 	/* Client name */

	// 	/* Console */
	// 	rdp_settings->ConsoleSession	 = false;
	// 	rdp_settings->RemoteConsoleAudio = false;

	// 	/* Audio */
	// 	rdp_settings->AudioPlayback = false;

	// 	/* Audio capture */
	// 	rdp_settings->AudioCapture =

	// 		/* Display Update channel */
	// 		rdp_settings->SupportDisplayControl = 1;

	// 	/* Security */

	// 	// rdp_settings->Authentication	= !guac_settings->disable_authentication;
	// 	rdp_settings->IgnoreCertificate = true;

	// 	/* RemoteApp */

	// 	/* Preconnection ID */

	// 	/* Preconnection BLOB */
	// 	// if (guac_settings->preconnection_blob != NULL) {
	// 	// 	rdp_settings->NegotiateSecurityLayer = FALSE;
	// 	// 	rdp_settings->SendPreconnectionPdu	 = TRUE;
	// 	// 	rdp_settings->PreconnectionBlob		 = guac_strdup(guac_settings->preconnection_blob);
	// 	// }

	// 	/* Store load balance info (and calculate length) if provided */

	// 	// rdp_settings->GlyphSupportLevel = !guac_settings->disable_glyph_caching ?
	// GLYPH_SUPPORT_FULL
	// 	// : GLYPH_SUPPORT_NONE; 如果开启字形缓存，win server 2008 r2 点击命令行崩溃，
	// 	// GLYPH_SUPPORT_FULL
	// 	rdp_settings->GlyphSupportLevel = GLYPH_SUPPORT_NONE;

	// 	rdp_settings->OsMajorType	= OSMAJORTYPE_UNSPECIFIED;
	// 	rdp_settings->OsMinorType	= OSMINORTYPE_UNSPECIFIED;
	// 	rdp_settings->DesktopResize = TRUE;
	// 	/* Claim support only for specific updates, independent of FreeRDP defaults */
	// 	rdp_settings->OrderSupport[NEG_DSTBLT_INDEX]	= TRUE;
	// 	rdp_settings->OrderSupport[NEG_SCRBLT_INDEX]	= TRUE;
	// 	rdp_settings->OrderSupport[NEG_MEMBLT_INDEX]	= false;
	// 	rdp_settings->OrderSupport[NEG_MEMBLT_V2_INDEX] = FALSE;

	// 	rdp_settings->OrderSupport[NEG_GLYPH_INDEX_INDEX] = TRUE;
	// 	rdp_settings->OrderSupport[NEG_FAST_INDEX_INDEX]  = FALSE;
	// 	rdp_settings->OrderSupport[NEG_FAST_GLYPH_INDEX]  = FALSE;

	// #ifdef HAVE_RDPSETTINGS_ALLOWUNANOUNCEDORDERSFROMSERVER
	// 	/* Do not consider server use of unannounced orders to be a fatal error */
	// 	rdp_settings->AllowUnanouncedOrdersFromServer = TRUE;
	// #endif
	// 	rdp_settings->FastPathInput	 = FALSE;
	// 	rdp_settings->FastPathOutput = FALSE;
}

static UINT xf_UpdateSurfaces(RdpgfxClientContext* context)
{
	LOG_ERROR(__FUNCTION__);
	return 0;
}

static UINT xf_CreateSurface(RdpgfxClientContext* context, const RDPGFX_CREATE_SURFACE_PDU* createSurface)
{
	LOG_ERROR(__FUNCTION__);
	return 0;
}

static UINT xf_DeleteSurface(RdpgfxClientContext* context, const RDPGFX_DELETE_SURFACE_PDU* deleteSurface)
{
	LOG_ERROR(__FUNCTION__);
	return 0;
}