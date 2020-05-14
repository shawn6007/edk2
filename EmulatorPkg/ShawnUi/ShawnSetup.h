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

#ifndef _SHAEWN_SETUP_H_
#define _SHAEWN_SETUP_H_

#define SHAWN_FRONT_PAGE_FORMSET_GUID \
  { \
    0x9e0c30bc, 0x3f06, 0x4ba6, {0x82, 0x88, 0x9, 0x17, 0x9b, 0x85, 0x5d, 0xcb} \
  }


#define SETUP_UTILITY_FORMSET_CLASS_GUID {0x7685453e, 0x2f03, 0x4989, 0xad, 0x3b, 0x4a, 0x84, 0x07, 0x91, 0xaf, 0x3a}
#define FORMSET_MAIN_GUID  { 0x9e0c30bc, 0x3f06, 0x4ba6, 0x82, 0x88, 0x9, 0x17, 0x9b, 0x85, 0x5d, 0xcb }
#define FORMSET_ADVANCED_GUID  { 0x7e0c30bc, 0x3f06, 0x4ba6, 0x82, 0x88, 0x9, 0x17, 0x9b, 0x85, 0x5d, 0xcb }


//
// These is  the VFR compiler generated data representing our VFR data.
//
extern UINT8  ShawnPageVfrBin[];
extern UINT8  ShawnAdvancedPageVfrBin[];

#endif
