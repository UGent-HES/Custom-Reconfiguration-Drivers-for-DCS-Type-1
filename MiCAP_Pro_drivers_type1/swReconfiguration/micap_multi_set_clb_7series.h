/******************************************************************************************************
DISCLAIMER NOTICE
*******************************************************************************************************
We are not affiliated, associated, authorized, endorsed by, 
or in any way officially connected with Xilinx, Inc. 
or any of its subsidiaries or its affiliates.  
In no event whatsoever shall Xilinx, Inc. 
or any of its subsidiaries or its affiliates have any warranty or support commitment for this software 
or liability for loss, injury or damage in connection with this software, 
including but not limited to the use or display thereof.
*******************************************************************************************************
*/
/**
* Replacement for the XHwIcap_GetClbBits and XHwIcap_SetClbBits functions for the Zynq.
* Created by Ghent University.
**/


#include "xil_assert.h"
#include <xstatus.h>

#include "micap_custom.h"
#include "xil_assert.h"
#include "locations.h"
#include <xstatus.h>
#include <xparameters.h>
#include "treeMult4b.h"
#include "xaxidma.h"
#include "xgpio.h"

#if (XHI_FAMILY != XHI_DEV_FAMILY_7SERIES)
    #error You are using the wrong xhwicap_getset_clb driver files. This file is specific to 7 series FPGAs only!!
#endif

typedef struct {
	long slice_row;
	long slice_col;
	const u8 (*Resource)[2];
	const u8 *Value;
	long NumBits;
} LUT_config_type;

//Signatures
/**
* Returns true if the configuration of two slices are stored in the same set of frames.
**/
u8 MiCAP_Custom_IsSameFrame(long slice_row0, long slice_col0, long slice_row1, long slice_col1);

/**
* Sets bits contained in multiple LUTs specified by the coordinates and data in the lut_configs array.
*
* @return	XST_SUCCESS or XST_FAILURE.
**/
int MiCAP_Custom_SetMultiClbBits(LUT_config_type  *lut_configs, u32 num_lut_configs);

void MiCAP_GetConfigurationCoordinates(long slice_row, long slice_col,
        u8 *bottom_ntop_p, int *clock_row_p, u32 *major_frame_address_p, u32 *word_offset_p);


