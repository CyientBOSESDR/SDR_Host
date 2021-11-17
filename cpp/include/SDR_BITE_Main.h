/******************************************************************************
 * FILE NAME: SDR_BITE_Main.h                                                 *
 *                                                                            *
 * PURPOSE: This header file consist declaration of API's, global variables,  *       
 *         and macros used for CBIT  framework.                               *
 *                                                                            *
 * GLOBAL VARIABLES:                                                          *
 *                                                                            *
 * Variable                 Type                Description                   *
 *                                                                            *
 * g_Head_ptr               Cbit_Data_st *      Pointer to first CBIT node in * 
 *                                              link list.                    *
 * DEVELOPMENT/ CHANGE HISTORY:                                               *
 *                                                                            *
 * Date       Author            Release         Description Of Change         *
 * 01/10/17   Vishal Badole      1.0.0          None                          *
 *                                                                            *
 *                                                                            *
 *****************************************************************************/

#ifndef _SDR_BITE_MAIN_H_
#define _SDR_BITE_MAIN_H_

#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include "SDR_BITE_Std.h"

/* MACRO declaration */
#define NAME_SZ      100
#define TYPE_SZ      10
#define DAT_TYPE_SZ  100

#define FILE_NAME    "cbit_data_file"

struct Cbit_Data {
   UI_16   cbit_arg_count;
   SI_8   cbit_type[TYPE_SZ];
   SI_8   cbit_arg_data_type[DAT_TYPE_SZ];
   SI_8   cbit_name[NAME_SZ];
   SI_16  cbit_id;
   struct Cbit_Data *next_cbit_ptr;
};

typedef struct Cbit_Data Cbit_Data_st;

/* Global variable declaration */
extern Cbit_Data_st *g_Head_ptr;

/*function declaration*/  

SI_8  SDR_BITE_AddCbitTest(Cbit_Data_st **loc_head_double_ptr);

SI_8  SDR_BITE_PrintCbitTestsInfo(Cbit_Data_st *loc_head_ptr);

SI_8  SDR_BITE_DelAllCbitTests(Cbit_Data_st **loc_head_double_ptr);

SI_8  SDR_BITE_DelCbitTest(Cbit_Data_st **loc_head_double_ptr, SI_16 loc_cbit_Id);

SI_8  SDR_BITE_CpyCbitTestsInfoToFile(Cbit_Data_st *loc_head_ptr, SI_8 *loc_file_name_ptr);

SI_8  SDR_BITE_CpyCbitInfo(Cbit_Data_st **loc_head_double_ptr, Cbit_Data_st *loc_cbit_obj_ptr);

SI_8  SDR_BITE_InitLinkListFromFile(Cbit_Data_st **loc_head_double_ptr, SI_8 *loc_file_name_ptr);

SI_8  SDR_BITE_SearchCbitIdInLinkList(Cbit_Data_st *loc_head_ptr, SI_16 loc_cbit_id);

SI_16  SDR_BITE_CountCbitTest(Cbit_Data_st *loc_head_ptr);

#endif
