
1. Source Code:
    1) BHA model network device driver source code
        your-dpdk-path/drivers/net/pico_bha/

    2) BHA model crypto device driver source code
        your-dpdk-path/drivers/crypto/pico_sec/

    3) BHA test case source code
        your-dpdk-path/app/test-pico-bha/

2. Build
    1) Build bha model first
        Please reference the bha model git repo readme, build out the static library
        https://glhk.picocomtech.com/ip/model/bha_model

    2) Set env
        export BHA_MODEL_PATH=/to/your/bha_model/folder/path/

    3) Follow the dpdk build rule
        meson build
        cd build/
        ninja

3. Run
    1) Configure HugePage
        On my testing server, I reserved one 1GB hugepage
    
    2) Example for running unit test case
        //bha model pcap mode and crypto device testing
        sudo ./app/dpdk-test-pico-bha -l 0 -n 1 --vdev=net_bha,dqn=1,et0_qid=0,et0=0xaefe --vdev=crypto_psec
        BHA>> pcap ecpri
        BHA>> quit

        If run other case, please repeat the upper command and processing.
        Other test case:
        # pcap ecpri
        # pcap default
        # pcap jumbo

        //bha model tap mode and crypto device testing
        //[Note] You must set up environment to create "tap0" and setup bridge, and connect "tap0" and hw NIC with bridge
        //The network packets can rx/tx between "tap0" and hw NIC
        sudo ./app/dpdk-test-pico-bha -l 0 -n 1 --vdev=net_bha,tap=tap0,dqn=0 --vdev=crypto_psec
        //sudo ./app/dpdk-test-pico-bha -l 0 -n 1 --vdev=net_bha,tap=tap0,dqn=0 --vdev=crypto_psec,salt_parse_from_key=yes
        BHA>> tap default
        BHA>> quit

        If run other case, please repeat the upper command and processing.
        Other test case:
        # aes gcm

    3) BHA model network input parameters help
        # tap - enable bha network TAP mode and input the specific TAP eth dev interface name. For example "tap=tap0"
        # max_rxq_nb - rx queue max number setting. [Note] not in used
        # dqn - default queue id setting for rx packets of not match any filters. Currently support queue (0~4)
        # et?_qid - eth type filter (? is id[0~3]) bonding rx queue id. For example "et0_qid=0". Currently support eth type id (0~3)
        # et? - eth type filter configure type. For example "et0=0xaefe". So the bonding id rx queue 0 will receive ecpri type(0xaefe) packets only

    4) BHA model crypto input parameters help
        # salt_parse_from_key - parse salt behind key if get input parameter is "yes", and the IV should remove the first 4Bytes salt; if get "no" or not setting it, the salt is in IV for first 4Bytes
