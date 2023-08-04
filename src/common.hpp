#pragma once

#include <errno.h>
#include <freerdp/log.h>
#include <freerdp/utils/signal.h>
#include <stddef.h>
#include <string.h>
#include <winpr/crt.h>

#include "log_helper.hpp"
#include "winpr/wtypes.h"

const int fatal_signals[] = {SIGABRT,	SIGALRM, SIGBUS,  SIGFPE,  SIGHUP,	SIGILL,
							 SIGINT,	SIGKILL, SIGQUIT, SIGSEGV, SIGSTOP, SIGTERM,
							 SIGTSTP,	SIGTTIN, SIGTTOU, SIGUSR1, SIGUSR2,
#ifdef SIGPOLL
							 SIGPOLL,
#endif
#ifdef SIGPROF
							 SIGPROF,
#endif
#ifdef SIGSYS
							 SIGSYS,
#endif
							 SIGTRAP,
#ifdef SIGVTALRM
							 SIGVTALRM,
#endif
							 SIGXCPU,	SIGXFSZ};

static void fatal_handler(int signum)
{
	struct sigaction default_sigaction;
	sigset_t		 this_mask;
	static BOOL		 recursive = FALSE;

	if (!recursive) {
		recursive = TRUE;

		// winpr_log_backtrace(TAG, WLOG_ERROR, 20);
	}
	if (terminal_needs_reset)
		tcsetattr(terminal_fildes, TCSAFLUSH, &orig_flags);

	default_sigaction.sa_handler = SIG_DFL;
	sigfillset(&(default_sigaction.sa_mask));
	default_sigaction.sa_flags = 0;
	sigaction(signum, &default_sigaction, NULL);
	sigemptyset(&this_mask);
	sigaddset(&this_mask, signum);
	pthread_sigmask(SIG_UNBLOCK, &this_mask, NULL);
	raise(signum);
}

inline int freerdp_handle_signals(void)
{
	size_t			 signal_index;
	sigset_t		 orig_set;
	struct sigaction orig_sigaction;
	struct sigaction fatal_sigaction;
	// WLog_DBG(TAG, "Registering signal hook...");
	sigfillset(&(fatal_sigaction.sa_mask));
	sigdelset(&(fatal_sigaction.sa_mask), SIGCONT);
	pthread_sigmask(SIG_BLOCK, &(fatal_sigaction.sa_mask), &orig_set);
	fatal_sigaction.sa_handler = fatal_handler;
	fatal_sigaction.sa_flags   = 0;

	for (signal_index = 0; signal_index < ARRAYSIZE(fatal_signals); signal_index++) {
		if (sigaction(fatal_signals[signal_index], NULL, &orig_sigaction) == 0) {
			if (orig_sigaction.sa_handler != SIG_IGN) {
				sigaction(fatal_signals[signal_index], &fatal_sigaction, NULL);
			}
		}
	}

	pthread_sigmask(SIG_SETMASK, &orig_set, NULL);
	/* Ignore SIGPIPE signal. */
	signal(SIGPIPE, SIG_IGN);
	return 0;
}

static BOOL my_bitmap_new(rdpContext* context, rdpBitmap* bitmap)
{
	// TODO: 实现自定义的位图数据结构的创建和初始化
	// ...
	return true;
}

static void my_bitmap_free(rdpContext* context, rdpBitmap* bitmap)
{
	// TODO: 实现自定义的位图数据结构的释放
	// ...
}

static BOOL my_bitmap_paint(rdpContext* context, rdpBitmap* bitmap)
{
	// TODO: 实现自定义的位图绘制逻辑
	// ...

	// 获取位图的宽度和高度
	int width  = bitmap->width;
	int height = bitmap->height;

	// 获取位图的像素数据
	BYTE* data = bitmap->data;

	// 获取位图数据的长度
	int length = bitmap->length;

	LOG_INFO("h{},w{},len{}", height, width, length);

	return true;
}

static BOOL my_glyph_new(rdpContext* context, const rdpGlyph* glyph)
{
	// TODO: 实现自定义的字形数据结构的创建和初始化
	// ...
	return true;
}

static void my_glyph_free(rdpContext* context, rdpGlyph* glyph)
{
	// TODO: 实现自定义的字形数据结构的释放
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
	// TODO: 实现自定义的字形绘制逻辑
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
	// TODO: 实现自定义的字形绘制前准备工作
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
	// TODO: 实现自定义的字形绘制后处理工作
	// ...
	return true;
}

static BOOL my_pointer_new(rdpContext* context, rdpPointer* pointer)
{
	// TODO: 实现自定义的指针数据结构的创建和初始化
	// ...

	return true;
}

static void my_pointer_free(rdpContext* context, rdpPointer* pointer)
{
	// TODO: 实现自定义的指针数据结构的释放
	// ...
}

static BOOL my_pointer_set(rdpContext* context, const rdpPointer* pointer)
{
	// TODO: 实现自定义的指针绘制逻辑
	// ...
	return true;
}

static BOOL my_pointer_set_null(rdpContext* context)
{
	// TODO: 实现自定义的空指针处理逻辑
	// ...
	return true;
}

static BOOL my_pointer_set_default(rdpContext* context)
{
	// TODO: 实现自定义的默认指针处理逻辑
	// ...
	return true;
}

// 初始化操作
static void init_bitmap_callbacks(rdpGraphics* graphics)
{
	graphics->Bitmap_Prototype->New	  = my_bitmap_new;
	graphics->Bitmap_Prototype->Free  = my_bitmap_free;
	graphics->Bitmap_Prototype->Paint = my_bitmap_paint;
}

static void init_glyph_callbacks(rdpGraphics* graphics)
{
	graphics->Glyph_Prototype->New		 = my_glyph_new;
	graphics->Glyph_Prototype->Free		 = my_glyph_free;
	graphics->Glyph_Prototype->Draw		 = my_glyph_draw;
	graphics->Glyph_Prototype->BeginDraw = my_glyph_begindraw;
	graphics->Glyph_Prototype->EndDraw	 = my_glyph_enddraw;
}

static void init_pointer_callbacks(rdpGraphics* graphics)
{
	graphics->Pointer_Prototype->New		= my_pointer_new;
	graphics->Pointer_Prototype->Free		= my_pointer_free;
	graphics->Pointer_Prototype->Set		= my_pointer_set;
	graphics->Pointer_Prototype->SetNull	= my_pointer_set_null;
	graphics->Pointer_Prototype->SetDefault = my_pointer_set_default;
}
