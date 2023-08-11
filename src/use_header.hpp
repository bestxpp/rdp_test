#pragma once

#include <errno.h>
#include <freerdp/channels/channels.h>
#include <freerdp/client/channels.h>
#include <freerdp/client/cliprdr.h>
#include <freerdp/client/cmdline.h>
#include <freerdp/client/encomsp.h>
#include <freerdp/client/file.h>
#include <freerdp/client/rail.h>
#include <freerdp/client/rdpei.h>
#include <freerdp/client/rdpgfx.h>
#include <freerdp/constants.h>
#include <freerdp/freerdp.h>
#include <freerdp/gdi/gdi.h>
#include <freerdp/gdi/gfx.h>
#include <freerdp/log.h>
#include <freerdp/utils/signal.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <winpr/crt.h>
#include <winpr/synch.h>

#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "freerdp/freerdp.h"
#include "winpr/wtypes.h"

// 保存图片用。
#include <png.h>

#include "log_helper.hpp"