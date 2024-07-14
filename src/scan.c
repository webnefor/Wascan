#include "scan.h"

int setArgv(int args, char *argv[]) {

    p_scan config;
    s_host host_start;
    e_host host_end;

    char addr[1024][1024];

    char start_ip [SIZE_BLOCK][1024];
    char end_ip   [SIZE_BLOCK][1024];

    char *MainArgs;
    char *hostStart;
    char *hostEnd;

    memset(start_ip, 0, SIZE_BLOCK);
    memset(end_ip,   0, SIZE_BLOCK);

    getParams(args, argv, &config);

    MainArgs = config.a_host;

    split(MainArgs, '-', addr);


    hostStart = addr[1];
    hostEnd   = addr[2];


    if (split(hostStart, '.', start_ip) != 0){
        perror("");
        return -1;
    }


    if (split(hostEnd,   '.',   end_ip) != 0) {
        perror("");
        return -1;
    }


    host_start.one   = atoi(start_ip[1]);
    host_start.two   = atoi(start_ip[2]);
    host_start.three = atoi(start_ip[3]);
    host_start.four  = atoi(start_ip[4]);

    host_end.one     = atoi(end_ip[1]);
    host_end.two     = atoi(end_ip[2]);
    host_end.three   = atoi(end_ip[3]);
    host_end.four    = atoi(end_ip[4]);

    scan_target(&host_start, &host_end, &config);

    return 0;

}

int getParams(int argc, char *argv[], struct params_scan *config) {

    static int count = 0;

    char *argv_m[] = {"-h", "-p"};

    char *strtemp[255];

    char portlist[1024][1024];


    for (int countl = 0;countl < argc;countl++) {

        if (strcmp(argv[countl], "-h") == 0)
        {
            config->a_host = argv[countl+1];
        }
        if ((strcmp(argv[countl], "-p") == 0))
        {
            strtemp[0] = concat(argv, argc);
            split(strtemp[0], 'p', portlist);
        }
    }

    if (strstr(portlist[2], "-h") != NULL)
        config->a_port = strtok(portlist[2], "-h");
    else
        config->a_port = portlist[2];


    return 0;
}

int scanning(p_args *args) {

    int s_socket, port, client, result = 0;

    char *end,*temp;

    struct sockaddr_in configuration;

    memset(&configuration, 0, sizeof(configuration));

    socklen_t sizelen_ts = sizeof(configuration);
    s_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (s_socket == -1) {
        perror("[-] Error");
        exit(-1);
    }

    temp = mvstring((int)args->v_num1, \
                            (int)args->v_num2, \
                                (int)args->v_num3, \
                                    (int)args->v_num4);

    configuration.sin_family = AF_INET;
    configuration.sin_addr.s_addr = inet_addr(temp);
    configuration.sin_port = htons((int)args->port);

    sizelen_ts = sizeof(configuration);

    int flags = fcntl(s_socket,F_GETFL);

    if (flags >= 0)
        flags = fcntl(s_socket, F_SETFL, O_NONBLOCK);

    int status = connect(s_socket, (struct sockaddr*)&configuration,sizelen_ts);


    if (errno != EINPROGRESS && errno != EWOULDBLOCK)
        return 1;

    if (status < 0) {

        struct timeval tv;

        tv.tv_sec = 0;
        tv.tv_usec = 50000;

        fd_set wset;

        FD_ZERO(&wset);
        FD_SET(s_socket,&wset);

        status = select(s_socket + 1,NULL,&wset,NULL,&tv);

        if (status) {

            close(s_socket);
            free(temp);
            printf("\033[032m[%i]",args->port);

            return 0;

        } else {

            printf("\033[031m[%i]",args->port);
            close(s_socket);
            free(temp);
            return -1;
        }
    }


    close(s_socket);
    free(temp);


    return 0;
}

int scan_target(s_host *config_start, e_host *config_end, p_scan *config) {

    system("clear");

    logo();

    int i1, i2, i3, i4;
    int s1,s2,s3,s4;
    int b1,b2,b3,b4;

    int count_port;
    int args_param[1000];

    char argb[1024][1024];

    p_args args;

    s1 = config_start->one,
    s2 = config_start->two,
    s3 = config_start->three,
    s4 = config_start->four;

    b1 = config_end->one,
    b2 = config_end->two,
    b3 = config_end->three,
    b4 = config_end->four;

    int thread_num_pr = (2048);

    pthread_t thread[thread_num_pr];

    args.ports = config->a_port;


    for (i1 = s1;i1 <= b1;i1++)
        for (i2 = s2;i2 <= b2;i2++)
            for (i3 = s3;i3 <= b3;i3++)
                for (i4 = s4;i4 <= b4;i4++) {

                    args.v_num1 = i1;
                    args.v_num2 = i2;
                    args.v_num3 = i3;
                    args.v_num4 = i4;

                    printf("\033[039m[%i.%i.%i.%i] \n └─", i1,i2,i3,i4 );

                    if (pthread_create(&thread[count_threads], NULL, (void *)&in_main_thread, &args) != 0) {
                        return 1;
                    }

                    pthread_join(thread[count_threads], NULL);
                    pthread_detach(thread[count_threads]);

                    count_threads+=1;
                }

    return 0;

}

int in_main_thread(p_args *in) {

    char *portlist[255];

    char * strcasem = in->ports;

    splet(strcasem, ',', portlist);


    int len_port = lensplit(strcasem,',');

    pthread_t thread[len_port];


    for (int i = 0; i < len_port; i++) {
        in->port = atoi(portlist[i]);

        if (pthread_create(&thread[i], NULL, (void *)&scanning, &(*in)) != 0) {
            return -1;
        }

        pthread_join(thread[i], NULL);
        // pthread_detach(thread[i]);
        // return 0;
    }
    printf("\n");

    return 0;

}


int  lensplit(char *___str, char splitel) {

    int count = 0;

    for (int i = 0; i < strlen(___str); i++) {
        if (___str[i] == splitel) {
            count++;
        }
    }
    count+=1;

    return count;
}

void logo() {
    printf( "\033[032m_____________________________________\n"       );
    printf( "\033[033m /    / //\\\\  |_--| ||//  //\\ |\\\\ |\n"    );
    printf( "\033[033m/_/\\_/ //--\\\\|___|  ||\\\\ //--\\| \\\\|\n" );
    printf( "\033[032m-------------------------------------\n"       );
}