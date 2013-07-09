#include "ufs_server_data.h"
#include "ufs_server_impl.h"

#define DEF_CONF_DIR "./conf/"
#define DEF_CONF_FILE (PROJECT_NAME ".conf")
#define strlcpy(dst, src, size) snprintf(dst, size, "%s", src)

//全局变量
ufs_server_conf_t g_conf;
ufs_server_data_t g_data;

STATIC int
serv_loadconf(const char *dir, const char *file)
{
    int ret = 0;
    
    ub_conf_data_t *conf = ub_conf_init(dir, file);
    if (NULL == conf){
        UB_LOG_FATAL("load config [dir:%s file:%s] failed.", dir, file);
        return -1;
    }

    UB_CONF_GETNSTR(conf, "log_dir", g_conf.log_dir, sizeof(g_conf.log_dir), "日志文件目录");
    UB_CONF_GETNSTR(conf, "log_file", g_conf.log_file, sizeof(g_conf.log_file), "日志文件名");
    UB_CONF_GETINT(conf, "log_size", &g_conf.log_size, "日志回滚大小（M）");
    UB_CONF_GETINT(conf, "log_level", &g_conf.log_level, "日志级别");
    ret = ub_log_init(g_conf.log_dir, g_conf.log_file, g_conf.log_size, g_conf.log_level);
    if (0 != ret){
        UB_LOG_FATAL("ub_log_init failed.[dir:%s file:%s size:%d level:%d]",
                g_conf.log_dir, g_conf.log_file, g_conf.log_size, g_conf.log_level);
        goto out;
    }

    UB_CONF_GETSVR(conf, "ufs", "server", &g_conf.svr, "UFS检索服务");


out:
    if (NULL != conf){
        ub_conf_close(conf);
        conf = NULL;
    }
    return ret;
}

STATIC int
serv_init()
{
    int ret = 0;
    
    signal(SIGPIPE, SIG_IGN);

    g_data.server = ub_server_create();
    if (NULL == g_data.server){
        UB_LOG_FATAL("ub_server_create failed.");
        ret = -1;
        goto out;
    }
    ret = ub_server_load(g_data.server, &g_conf.svr);
    if (0 != ret){
        UB_LOG_FATAL("ub_server_load failed.");
        ret = -1;
        goto out;
    }
    //ub_server_set_buffer
    ub_server_set_callback(g_data.server, callback_server_main);

out:
    if (0 != ret){
        if (g_data.server){
            ub_server_destroy(g_data.server);
            g_data.server = NULL;
        }
    }

    return ret;
}

STATIC int
serv_run()
{
    int ret = 0;
    
    ret = ub_server_run(g_data.server);
    if (0 != ret){
        UB_LOG_FATAL("ub_server_run failed.");
        return -1;
    }

    ub_server_join(g_data.server);
    return 0;
}

STATIC void 
serv_cleanup()
{
    if (g_data.server){
        ub_server_destroy(g_data.server);
        g_data.server = NULL;
    }
}

#ifndef _TEST
int
main(int argc, char **argv)
{
    int ret = 0;
    strlcpy(g_conf.conf_dir, DEF_CONF_DIR, PATH_SIZE);
    strlcpy(g_conf.conf_file, DEF_CONF_FILE, PATH_SIZE);

    ret = serv_loadconf(g_conf.conf_dir, g_conf.conf_file);
    if (0 == ret){
        UB_LOG_TRACE("load config [dir:%s file:%s] sucess.",
                g_conf.conf_dir, g_conf.conf_file);
    } else {
        UB_LOG_FATAL("load config [dir:%s file:%s] failed.",
                g_conf.conf_dir, g_conf.conf_file);
        goto out;
    }

    ret = serv_init();
    if (0 == ret){
        UB_LOG_TRACE("serv_init sucess.");
    } else {
        UB_LOG_FATAL("serv_init failed. [ret: %d]", ret);
        goto out;
    }
    
    ret = serv_run();
    if (0 == ret){
        UB_LOG_TRACE("serv_run sucess.");
    } else {
        UB_LOG_FATAL("serv_run failed. [ret: %d]", ret);
        goto out;
    }

out:
    serv_cleanup();
    return ret;
}
#endif
