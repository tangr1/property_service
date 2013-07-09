#ifndef __UFS_SERVER_DATA_H__
#define __UFS_SERVER_DATA_H__

#include "ul_def.h"
#include "ub.h"

typedef struct _ufs_server_conf_t{
    ub_svr_t svr;

    char conf_dir[PATH_SIZE];
    char conf_file[PATH_SIZE];

    char log_dir[PATH_SIZE];
    char log_file[PATH_SIZE];
    int log_size;
    int log_level;
} ufs_server_conf_t;

typedef struct _ufs_server_data_t{
    ub_server_t *server;
} ufs_server_data_t;

#endif
