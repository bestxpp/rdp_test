#pragma once

#include <cstddef>
#include <memory>
#include <thread>

#include "common.hpp"
#include "log_helper.hpp"
#include "winpr/wtypes.h"

static int image_counter = 0;
void	   guac_rdp_push_settings(freerdp* rdp);
BOOL	   guac_rdp_gdi_desktop_resize(rdpContext* context);
BOOL	   guac_rdp_gdi_end_paint(rdpContext* context);
BOOL	   guac_rdp_gdi_set_bounds(rdpContext* context, const rdpBounds* bounds);
BOOL	   guac_rdp_gdi_dstblt(rdpContext* context, const DSTBLT_ORDER* dstblt);
BOOL	   guac_rdp_gdi_patblt(rdpContext* context, PATBLT_ORDER* patblt);
BOOL	   guac_rdp_gdi_scrblt(rdpContext* context, const SCRBLT_ORDER* scrblt);
BOOL	   guac_rdp_gdi_memblt(rdpContext* context, MEMBLT_ORDER* memblt);
BOOL	   guac_rdp_gdi_opaquerect(rdpContext* context, const OPAQUE_RECT_ORDER* opaque_rect);
UINT32	   guac_rdp_get_native_pixel_format(BOOL alpha);
BOOL	   rdp_freerdp_pre_connect(freerdp* instance);
BOOL	   rdp_freerdp_authenticate(freerdp* instance, char** username, char** password, char** domain);
DWORD	   rdp_freerdp_verify_certificate(freerdp*	  instance,
										  const char* host,
										  UINT16	  port,
										  const char* common_name,
										  const char* subject,
										  const char* issuer,
										  const char* fingerprint,
										  DWORD		  flags);

class hda_client : public std::enable_shared_from_this<hda_client>
{
  public:
	hda_client()
		: freerdpins_(NULL)
		, cur_mask_(0)
	{
	}
	~hda_client()
	{
		LOG_ERROR("释放....");
		work_thread_.join();
	}
	void Start();
	void Stop();

	void SendMouseEvent(MouseEvent& ms);

  private:
	std::thread work_thread_;
	freerdp*	freerdpins_;

	int cur_mask_;
};