/*
 * Hardware Abstraction Layer (HAL)
 * 
 * Copyright (C) 2018 Khalid Baheyeldin
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#if defined(ESP32)
  // ESP32
  #define MCU_STR "ESP32"
  #include "HAL_ESP32.h"

#else
  #error "Unsupported Platform! If this is a new platform, it needs the appropriate entries in the HAL directory."
#endif

// create null decoration for catalogs as needed
#ifndef CAT_ATTR
  #define CAT_ATTR
#endif

// Non-volatile storage
#ifndef NV_ENDURANCE
  #define NV_ENDURANCE NVE_MID
#endif
