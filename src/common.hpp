#pragma once

#include "log_helper.hpp"
#include "use_header.hpp"

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

};

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
	// LOG_INFO(__func__);
	return true;
}

static void guac_rdp_bitmap_free(rdpContext* context, rdpBitmap* bitmap)
{
	// LOG_INFO(__func__);
	//  TODO: Implement custom bitmap data structure release
	//  ...
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
	// LOG_INFO(__func__);
	//  TODO: Implement custom pointer data structure creation and initialization
	//  ...

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

struct ImageData
{
	int					  x;		// x坐标
	int					  y;		// y坐标
	int					  width;	// 图像宽度
	int					  height;	// 图像高度
	std::vector<png_byte> pngData;	// PNG图像数据
};

struct MouseEvent
{
	int x;
	int y;
	int mask;
};

inline std::string serialize(const ImageData& data)
{
	std::string result;
	// 添加坐标和尺寸信息
	result.append(reinterpret_cast<const char*>(&data.x), sizeof(data.x));
	result.append(reinterpret_cast<const char*>(&data.y), sizeof(data.y));
	result.append(reinterpret_cast<const char*>(&data.width), sizeof(data.width));
	result.append(reinterpret_cast<const char*>(&data.height), sizeof(data.height));

	// 添加PNG数据长度
	size_t pngSize = data.pngData.size();
	result.append(reinterpret_cast<const char*>(&pngSize), sizeof(pngSize));

	// 添加PNG数据
	result.append(reinterpret_cast<const char*>(data.pngData.data()), pngSize);

	return result;
}