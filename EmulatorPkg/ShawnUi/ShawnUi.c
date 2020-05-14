/**@file

Copyright (c) 2006, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials                          
are licensed and made available under the terms and conditions of the BSD License         
which accompanies this distribution.  The full text of the license may be found at        
http://opensource.org/licenses/bsd-license.php                                            
                                                                                          
THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             


Abstract:

  Produce WinNtThunk protocol and it's associated device path and controller 
  state protocols. WinNtThunk is to the NT emulation environment as 
  PCI_ROOT_BRIGE is to real hardware. The WinNtBusDriver is the child of this
  driver.

  Since we are a root hardware abstraction we do not install a Driver Binding
  protocol on this handle. This driver can only support one one WinNtThunk protocol
  in the system, since the device path is hard coded.

**/

#include "ShawnUi.h"
#include "ShawnSetup.h"
#include <Protocol/SimpleTextOut.h>
#include <Protocol/HiiConfigAccess.h>
#include <Library/HiiLib.h>
#include <Library/UefiHiiLib/InternalHiiLib.h>
#include <Library/DebugLib.h>

EFI_STATUS
EFIAPI
ShawnUiEntryPoint (
  IN EFI_HANDLE                            ImageHandle,
  IN EFI_SYSTEM_TABLE                      *SystemTable
  )
{
  EFI_HII_HANDLE                     HiiHandle[2];
  EFI_HII_HANDLE                     SetupHiiHandle;
  EFI_STATUS                         Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL       *GraphicsOutput;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *SimpleTextOut;
  //UINTN                              BootTextColumn;
  //UINTN                              BootTextRow;
  EFI_FORM_BROWSER2_PROTOCOL      *FormBrowser2;
  //EFI_HANDLE                      DriverHandle;
  EFI_GUID   mClassFrontPageGuid      = SETUP_UTILITY_FORMSET_CLASS_GUID;
  EFI_GUID   mMainFrontPageGuid      = FORMSET_MAIN_GUID;
  EFI_GUID   mAdvancedFrontPageGuid      = FORMSET_ADVANCED_GUID;
  EFI_BROWSER_ACTION_REQUEST  ActionRequest;

  EFI_INPUT_KEY                Key;
  UINTN             EventIndex;

  Status = EFI_UNSUPPORTED;
  //
  // After the console is ready, get current video resolution
  // and text mode before launching setup at first time.
  //
  Status = gBS->HandleProtocol (
                  gST->ConsoleOutHandle,
                  &gEfiGraphicsOutputProtocolGuid,
                  (VOID**)&GraphicsOutput
                  );
  if (EFI_ERROR (Status)) {
    Print (L"GraphicsOutput Status = %r\n", Status);
    GraphicsOutput = NULL;
  //  return Status;
  }

  Status = gBS->HandleProtocol (
                  gST->ConsoleOutHandle,
                  &gEfiSimpleTextOutProtocolGuid,
                  (VOID**)&SimpleTextOut
                  );
  if (EFI_ERROR (Status)) {
    Print (L"SimpleTextOut Status = %r\n", Status);
    SimpleTextOut = NULL;
  //  return Status;
  }

  Status = gBS->LocateProtocol (&gEfiFormBrowser2ProtocolGuid, NULL, (VOID **) &FormBrowser2);
  if (EFI_ERROR (Status)) {
    Print (L"gEfiFormBrowser2ProtocolGuid Status = %r\n", Status);
  //  return Status;
  }  

  //
  // Install Device Path Protocol and Config Access protocol to driver handle
  //
  //DriverHandle = NULL;
  //Status = gBS->InstallMultipleProtocolInterfaces (
  //                DriverHandle,
  //                &gEfiDevicePathProtocolGuid,
  //                &mFrontPageHiiVendorDevicePath,
  //                &gEfiHiiConfigAccessProtocolGuid,
  //                &gFrontPagePrivate.ConfigAccess,
  //                NULL
  //                );


  //
  // Publish our HII data
  //
  HiiHandle[0] = HiiAddPackages (
                              &mMainFrontPageGuid,
                              ImageHandle,
                              ShawnPageVfrBin,
                              ShawnUiStrings,
                              NULL
                              );

  HiiHandle[1] = HiiAddPackages (
                              &mAdvancedFrontPageGuid,
                              ImageHandle,
                              ShawnAdvancedPageVfrBin,
                              ShawnUiStrings,
                              NULL
                              );
  //ASSERT (HiiHandle != NULL);                                  
  //ActionRequest = EFI_BROWSER_ACTION_REQUEST_RESET;
  //DEBUG ((DEBUG_INFO, "Ready send broswer form\n"));  
  //Status = FormBrowser2->SendForm (
  //                          FormBrowser2,
  //                          &HiiHandle[0],
  //                          1,
  //                          &mClassFrontPageGuid,
  //                          0,
  //                          NULL,
  //                          &ActionRequest
  //                          );
  SetupHiiHandle = HiiHandle[0];

  do {
    Status = FormBrowser2->SendForm (
                          FormBrowser2,
                          &SetupHiiHandle,
                          1,
                          &mClassFrontPageGuid,
                          0,
                          NULL,
                          &ActionRequest
                          );
    DEBUG ((DEBUG_INFO, "while loop\n"));
    DEBUG ((DEBUG_INFO, "Ready to wait for key event\n"));
    gBS->WaitForEvent (1, &gST->ConIn->WaitForKey, &EventIndex);
    DEBUG ((DEBUG_INFO, "Finish key event\n"));
    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
    DEBUG ((DEBUG_INFO, "Read Key stroke status %r, key %d\n", Status, Key.ScanCode));

    switch (Key.ScanCode)
    {
    case SCAN_RIGHT:
        SetupHiiHandle = HiiHandle[1];
      break;
    case SCAN_LEFT:
        SetupHiiHandle = HiiHandle[0];
      break;

    default:
      break;
    }


  } while (TRUE);
  return Status;
}


