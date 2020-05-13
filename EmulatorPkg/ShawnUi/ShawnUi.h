/**@file

Copyright (c) 2006, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

Module Name:

  WinNtThunk.h

Abstract:

**/

#ifndef _SHAEWN_UI_H_
#define _SHAEWN_UI_H_

#include <Include/Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>

#define SHAWN_FRONT_PAGE_FORMSET_GUID \
  { \
    0x9e0c30bc, 0x3f06, 0x4ba6, {0x82, 0x88, 0x9, 0x17, 0x9b, 0x85, 0x5d, 0xcb} \
  }

//
// These is  the VFR compiler generated data representing our VFR data.
//
extern UINT8  ShawnPageVfrBin[];

#endif
