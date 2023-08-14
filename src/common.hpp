#pragma once

#include "log_helper.hpp"
#include "use_header.hpp"

struct guac_rdp_bitmap
{
	/**
	 * FreeRDP bitmap data - MUST GO FIRST.
	 */
	rdpBitmap bitmap;
	int		  used;
};

struct guac_rdp_glyph
{
	rdpGlyph glyph;
};

struct guac_rdp_pointer
{
	rdpPointer pointer;
};

static BOOL guac_rdp_bitmap_new(rdpContext* context, rdpBitmap* bitmap)
{
	// TODO: Implement custom bitmap data structure creation and initialization
	// ...
	LOG_INFO(__func__);
	return true;
}

static void guac_rdp_bitmap_free(rdpContext* context, rdpBitmap* bitmap)
{
	LOG_INFO(__func__);
	// TODO: Implement custom bitmap data structure release
	// ...
}

static BOOL guac_rdp_bitmap_paint(rdpContext* context, rdpBitmap* bitmap)
{
	LOG_INFO(__func__);
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

static BOOL guac_rdp_bitmap_setsurface(rdpContext* context, rdpBitmap* bitmap, BOOL primary)
{
	LOG_INFO(__func__);

	return true;
}

static BOOL guac_rdp_glyph_new(rdpContext* context, const rdpGlyph* glyph)
{
	LOG_INFO(__func__);
	// TODO: Implement custom glyph data structure creation and initialization
	// ...
	return true;
}

static void guac_rdp_glyph_free(rdpContext* context, rdpGlyph* glyph)
{
	LOG_INFO(__func__);
	// TODO: Implement custom glyph data structure release
	// ...
}

static BOOL guac_rdp_glyph_draw(rdpContext*		context,
								const rdpGlyph* glyph,
								INT32			x,
								INT32			y,
								INT32			w,
								INT32			h,
								INT32			sx,
								INT32			sy,
								BOOL			fOpRedundant)
{
	LOG_INFO(__func__);
	// TODO: Implement custom glyph drawing logic
	// ...
	return true;
}

static BOOL guac_rdp_glyph_begindraw(rdpContext* context,
									 INT32		 x,
									 INT32		 y,
									 INT32		 width,
									 INT32		 height,
									 UINT32		 bgcolor,
									 UINT32		 fgcolor,
									 BOOL		 fOpRedundant)
{
	LOG_INFO(__func__);
	// TODO: Implement custom preparation work before drawing glyph
	// ...
	return true;
}

static BOOL guac_rdp_glyph_enddraw(rdpContext* context,
								   INT32	   x,
								   INT32	   y,
								   INT32	   width,
								   INT32	   height,
								   UINT32	   bgcolor,
								   UINT32	   fgcolor)
{
	LOG_INFO(__func__);
	// TODO: Implement custom post-processing work after drawing glyph
	// ...
	return true;
}

static BOOL guac_rdp_pointer_new(rdpContext* context, rdpPointer* pointer)
{
	LOG_INFO(__func__);
	// TODO: Implement custom pointer data structure creation and initialization
	// ...

	return true;
}

static void guac_rdp_pointer_free(rdpContext* context, rdpPointer* pointer)
{
	LOG_INFO(__func__);
	// TODO: Implement custom pointer data structure release
	// ...
}

static BOOL guac_rdp_pointer_set(rdpContext* context, const rdpPointer* pointer)
{
	LOG_INFO(__func__);
	// TODO: Implement custom pointer drawing logic
	// ...
	return true;
}

static BOOL guac_rdp_pointer_set_null(rdpContext* context)
{
	LOG_INFO(__func__);
	// TODO: Implement custom handling logic for a null pointer
	// ...
	return true;
}

static BOOL guac_rdp_pointer_set_default(rdpContext* context)
{
	LOG_INFO(__func__);
	// TODO: Implement custom handling logic for a default pointer
	// ...
	return true;
}

static BOOL guac_rdp_beep_play_sound(rdpContext*			  context,
									 const PLAY_SOUND_UPDATE* play_sound)
{
	LOG_INFO(__func__);
	return TRUE;
}

static BOOL guac_rdp_keyboard_set_indicators(rdpContext* context, UINT16 flags)
{
	LOG_INFO(__func__);
	// Initializatio
	return TRUE;
}