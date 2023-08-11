#pragma once

#include "log_helper.hpp"
#include "use_header.hpp"

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