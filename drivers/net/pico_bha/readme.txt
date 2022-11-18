
1. Source Code:
    1) BHA model driver source code
        your-dpdk-path/drivers/net/pico_bha/

    2) BHA test case source code
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
    
    2) For my running cmd
        sudo ./build/app/dpdk-test-pico-bha -l 0 -n 1 --vdev=net_bha  
