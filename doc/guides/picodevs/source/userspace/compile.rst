.. _compile_pcie_drver_userspace:

Compiling the PC802 PCIe driver from source code
================================================

If you use igb_uio.ko to bind PC802 to linux kernel:

The source code can be cloned as follows:

.. code-block:: console

       git clone https://dpdk.org/git/dpdk-kmods

build igb_uio

.. code-block:: console

       cd path/to/git/repo/dpdk-kmods/linux/igb_uio
       make
       insmod igb_uio.ko

.. _build_PC802_PCIe_driver:

Build PC802 PCIe driver libs on NPU side from source code
---------------------------------------------------------

Contact `Picocom <info@picocom.com>`_ to get <PC-002911-DC - Picocom PC802_UDriver code> and enter the  root directory of DPDK.

#. X86 Platform:

.. code-block:: console

        cd ${your_DPDK_PATH}
        patch -p1 < ../Picocom-PC802-PCIe-UDriver-based-on-DPDK-21.08.patch
        meson build -Denable_multi_pc802=true
        #default path is /usr/local
        ninja -C build install

#. ARM Platform:

.. code-block:: console

        cd ${your_flexbuild_lsdk2108_PATH}
        cd components/apps/networking/dpdk
        patch  -p1 < ../Picocom-PC802-PCIe-UDriver-based-on-flexbuild-lsdk2108.patch
        meson aarch64-build-gcc --cross-file config/arm/arm64_armv8_linux_gcc
        meson configure -Dprefix=~/dpdk_arm_libs -Denable_multi_pc802=true aarch64-build-gcc
        #cross compile libs output to "~/dpdk_arm_libs"
        ninja -C aarch64-build-gcc install

More information on how to compile the DPDK, see `DPDK Documentation <https://www.dpdk.org/>`_ .

.. note:: If no source code, please contact `Picocom <info@picocom.com>`_ to get PC-002897-DC-A-PC802_UDriver_libs
.. note:: The new version supports multiple PC802. If you don't need this function, you can compile without the "-Denable_multi_pc802=true" option, and the interface is the same as release 1.

Compiling DPDK application using cmake with link static libraries
-----------------------------------------------------------------

Please refer to the CMakeLists.txt to compile the DPDK application through CMake.

Example of CMakeLists.txt::

   set (PCIE_DRIVER_LIBS
    -L/usr/local/lib/x86_64-linux-gnu
    -Wl,--as-needed
    -Wl,--no-undefined
    -Wl,-O1
    -Wl,--whole-archive
    -Wl,--start-group
    -l:librte_common_cpt.a
    -l:librte_common_dpaax.a
    -l:librte_common_iavf.a
    -l:librte_common_octeontx.a
    -l:librte_common_octeontx2.a
    -l:librte_bus_auxiliary.a
    -l:librte_bus_dpaa.a
    -l:librte_bus_fslmc.a
    -l:librte_bus_ifpga.a
    -l:librte_bus_pci.a
    -l:librte_bus_vdev.a
    -l:librte_bus_vmbus.a
    -l:librte_common_cnxk.a
    -l:librte_common_qat.a
    -l:librte_common_sfc_efx.a
    -l:librte_mempool_bucket.a
    -l:librte_mempool_cnxk.a
    -l:librte_mempool_dpaa.a
    -l:librte_mempool_dpaa2.a
    -l:librte_mempool_octeontx.a
    -l:librte_mempool_octeontx2.a
    -l:librte_mempool_ring.a
    -l:librte_mempool_stack.a
    -l:librte_net_af_packet.a
    -l:librte_net_ark.a
    -l:librte_net_atlantic.a
    -l:librte_net_avp.a
    -l:librte_net_axgbe.a
    -l:librte_net_bnxt.a
    -l:librte_net_bond.a
    -l:librte_net_cnxk.a
    -l:librte_net_cxgbe.a
    -l:librte_net_dpaa.a
    -l:librte_net_dpaa2.a
    -l:librte_net_e1000.a
    -l:librte_net_ena.a
    -l:librte_net_enetc.a
    -l:librte_net_enic.a
    -l:librte_net_failsafe.a
    -l:librte_net_fm10k.a
    -l:librte_net_hinic.a
    -l:librte_net_hns3.a
    -l:librte_net_i40e.a
    -l:librte_net_iavf.a
    -l:librte_net_ice.a
    -l:librte_net_igc.a
    -l:librte_net_ionic.a
    -l:librte_net_ixgbe.a
    -l:librte_net_kni.a
    -l:librte_net_liquidio.a
    -l:librte_net_memif.a
    -l:librte_net_netvsc.a
    -l:librte_net_nfp.a
    -l:librte_net_ngbe.a
    -l:librte_net_null.a
    -l:librte_net_octeontx.a
    -l:librte_net_octeontx2.a
    -l:librte_net_octeontx_ep.a
    -l:librte_net_pc802.a
    -l:librte_net_pfe.a
    -l:librte_net_qede.a
    -l:librte_net_ring.a
    -l:librte_net_sfc.a
    -l:librte_net_softnic.a
    -l:librte_net_tap.a
    -l:librte_net_thunderx.a
    -l:librte_net_txgbe.a
    -l:librte_net_vdev_netvsc.a
    -l:librte_net_vhost.a
    -l:librte_net_virtio.a
    -l:librte_net_vmxnet3.a
    -l:librte_raw_cnxk_bphy.a
    -l:librte_raw_dpaa2_cmdif.a
    -l:librte_raw_dpaa2_qdma.a
    -l:librte_raw_ioat.a
    -l:librte_raw_ntb.a
    -l:librte_raw_octeontx2_dma.a
    -l:librte_raw_octeontx2_ep.a
    -l:librte_raw_skeleton.a
    -l:librte_crypto_bcmfs.a
    -l:librte_crypto_caam_jr.a
    -l:librte_crypto_cnxk.a
    -l:librte_crypto_dpaa_sec.a
    -l:librte_crypto_dpaa2_sec.a
    -l:librte_crypto_nitrox.a
    -l:librte_crypto_null.a
    -l:librte_crypto_octeontx.a
    -l:librte_crypto_octeontx2.a
    -l:librte_crypto_scheduler.a
    -l:librte_crypto_virtio.a
    -l:librte_compress_octeontx.a
    -l:librte_regex_octeontx2.a
    -l:librte_vdpa_ifc.a
    -l:librte_event_cnxk.a
    -l:librte_event_dlb2.a
    -l:librte_event_dpaa.a
    -l:librte_event_dpaa2.a
    -l:librte_event_dsw.a
    -l:librte_event_octeontx2.a
    -l:librte_event_opdl.a
    -l:librte_event_skeleton.a
    -l:librte_event_sw.a
    -l:librte_event_octeontx.a
    -l:librte_baseband_acc100.a
    -l:librte_baseband_fpga_5gnr_fec.a
    -l:librte_baseband_fpga_lte_fec.a
    -l:librte_baseband_null.a
    -l:librte_baseband_turbo_sw.a
    -l:librte_node.a
    -l:librte_graph.a
    -l:librte_bpf.a
    -l:librte_flow_classify.a
    -l:librte_pipeline.a
    -l:librte_table.a
    -l:librte_port.a
    -l:librte_fib.a
    -l:librte_ipsec.a
    -l:librte_vhost.a
    -l:librte_stack.a
    -l:librte_security.a
    -l:librte_sched.a
    -l:librte_reorder.a
    -l:librte_rib.a
    -l:librte_regexdev.a
    -l:librte_rawdev.a
    -l:librte_pdump.a
    -l:librte_power.a
    -l:librte_member.a
    -l:librte_lpm.a
    -l:librte_latencystats.a
    -l:librte_kni.a
    -l:librte_jobstats.a
    -l:librte_ip_frag.a
    -l:librte_gso.a
    -l:librte_gro.a
    -l:librte_eventdev.a
    -l:librte_efd.a
    -l:librte_distributor.a
    -l:librte_cryptodev.a
    -l:librte_compressdev.a
    -l:librte_cfgfile.a
    -l:librte_bitratestats.a
    -l:librte_bbdev.a
    -l:librte_acl.a
    -l:librte_timer.a
    -l:librte_hash.a
    -l:librte_metrics.a
    -l:librte_cmdline.a
    -l:librte_pci.a
    -l:librte_ethdev.a
    -l:librte_meter.a
    -l:librte_net.a
    -l:librte_mbuf.a
    -l:librte_mempool.a
    -l:librte_rcu.a
    -l:librte_ring.a
    -l:librte_eal.a
    -l:librte_telemetry.a
    -l:librte_kvargs.a
    -lrte_node
    -lrte_graph
    -lrte_bpf
    -lrte_flow_classify
    -lrte_pipeline
    -lrte_table
    -lrte_port
    -lrte_fib
    -lrte_ipsec
    -lrte_vhost
    -lrte_stack
    -lrte_security
    -lrte_sched
    -lrte_reorder
    -lrte_rib
    -lrte_regexdev
    -lrte_rawdev
    -lrte_pdump
    -lrte_power
    -lrte_member
    -lrte_lpm
    -lrte_latencystats
    -lrte_kni
    -lrte_jobstats
    -lrte_ip_frag
    -lrte_gso
    -lrte_gro
    -lrte_eventdev
    -lrte_efd
    -lrte_distributor
    -lrte_cryptodev
    -lrte_compressdev
    -lrte_cfgfile
    -lrte_bitratestats
    -lrte_bbdev
    -lrte_acl
    -lrte_timer
    -lrte_hash
    -lrte_metrics
    -lrte_cmdline
    -lrte_pci
    -lrte_ethdev
    -lrte_meter
    -lrte_net
    -lrte_mbuf
    -lrte_mempool
    -lrte_rcu
    -lrte_ring
    -lrte_eal
    -lrte_telemetry
    -lrte_kvargs
    -Wl,--no-whole-archive
    -Wl,--no-as-needed
    -pthread
    -lm
    -ldl
    -lnuma
    -Wl,--export-dynamic
    -latomic
    -Wl,--end-group
    -Wl,-rpath,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    )

    execute_process(COMMAND pkg-config --cflags libdpdk
        OUTPUT_VARIABLE PCIE_DRIVER_C_FLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    set(PCIE_DRIVER_C_FLAGS "${PCIE_DRIVER_C_FLAGS} -m64 -pthread -D_GNU_SOURCE")

.. _check_PC802_active:

Check if PC802 is active
------------------------

.. code-block:: console

    cd ${your_DPDK_PATH}
    ./usertools/dpdk-devbind.py -s

.. code-block:: console

    Network devices using kernel driver
    ===================================
    ...
    Other Network devices
    =====================
    0000:01:00.0 'Device 0802' unused=vfio-pci
    No 'Crypto' devices detected
    ============================
    No 'Eventdev' devices detected
    ============================
    No 'Mempool' devices detected
    ============================
    No 'Compress' devices detected
    ============================

Optional driver ``01: 00.0`` appears::

    usertools/dpdk-devbind.py -b igb_uio 01:00.0

.. code-block:: console

    Network devices using DPDK-compatible driver
    ============================================
    0000:01:00.0 'Device 0802' drv=igb_uio unused=vfio-pci
    Network devices using kernel driver
    ===================================
    ...
    No 'Crypto' devices detected
    ============================
    No 'Eventdev' devices detected
    ==============================
    No 'Mempool' devices detected
    =============================
    No 'Compress' devices detected
    ==============================

Output shown in the above figure means that the binding is successful.


