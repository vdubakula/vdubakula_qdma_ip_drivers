**Xilinx QDMA Library Interface Definitions**


Header file *libqdma_export.h* defines data structures and function
signatures exported by Xilinx QDMA (libqdma) Library.
libqdma is part of Xilinx QDMA Linux Driver.

libqdma exports the configuration and control APIs for device and
queue management and data processing APIs. Configuration APIs
shall not be invoked in interrupt context by upper layers.

.. c:function:: QDMA_FUNC_ID_INVALID ()


**Parameters**


.. c:function:: QDMA_DEV_NAME_MAXLEN ()

   Maxinum length of the QDMA device name

**Parameters**


.. c:function:: DEVICE_VERSION_INFO_STR_LENGTH ()

   QDMA HW version string array length, change this if QDMA_HW_VERSION_STRING_LEN is changed in access code

**Parameters**


.. c:function:: QDMA_QUEUE_NAME_MAXLEN ()

   Maximum queue name length

**Parameters**


.. c:function:: QDMA_QUEUE_IDX_INVALID ()

   Invalid queue index

**Parameters**


.. c:function:: QDMA_QUEUE_VEC_INVALID ()

   Invalid MSIx vector index

**Parameters**


.. c:function:: QDMA_REQ_OPAQUE_SIZE ()

   Maximum request length

**Parameters**


.. c:function:: QDMA_UDD_MAXLEN ()

   Maximum length of the user defined data

**Parameters**




.. c:type:: enum qdma_q_mode

   per queue DMA AXI Interface option

**Constants**

``QDMA_Q_MODE_MM``
  AXI Memory Mapped Mode 

``QDMA_Q_MODE_ST``
  AXI Stream Mode 




.. c:type:: enum qdma_q_dir

   Direction of the queue

**Constants**

``QDMA_Q_DIR_H2C``
  host to card 

``QDMA_Q_DIR_C2H``
  card to host 




.. c:type:: enum qdma_drv_mode

   PF/VF qdma driver modes

**Constants**

``AUTO_MODE``
  Auto mode is mix of Poll and Interrupt Aggregation
   mode. Driver polls for the write back status updates. Interrupt
   aggregation is used for processing the completion ring

``POLL_MODE``
  In Poll Mode, Software polls for the write back
   completions (Status Descriptor Write Back)

``DIRECT_INTR_MODE``
  Direct Interrupt mode, each queue is
   assigned to one of the available interrupt vectors in a round robin
   fashion to service the requests. Interrupt is raised by the HW upon
   receiving the completions and software reads the completion status.

``INDIRECT_INTR_MODE``
  In Indirect Interrupt mode or Interrupt
   Aggregation mode, each vector has an associated Interrupt
   Aggregation Ring. The QID and status of queues requiring service
   are written into the Interrupt Aggregation Ring. When a PCIe MSI-X
   interrupt is received by the Host, the software reads the Interrupt
   Aggregation Ring to determine which queue needs service. Mapping of
   queues to vectors is programmable

``LEGACY_INTR_MODE``
  Driver is inserted in legacy interrupt mode
   Software serves status updates upon receiving the legacy interrupt

**Description**


QDMA PF/VF drivers can be loaded in one of these modes.
Mode options is exposed as a user configurable module parameter




.. c:type:: enum queue_type_t


**Constants**

``Q_H2C``
  host to card 

``Q_C2H``
  card to host 

``Q_CMPT``
  cmpt queue

``Q_H2C_C2H``
  Both H2C and C2H directions




.. c:type:: enum intr_ring_size_sel

   qdma interrupt ring size selection

**Constants**

``INTR_RING_SZ_4KB``
  accommodates 512 entries 

``INTR_RING_SZ_8KB``
  accommodates 1024 entries 

``INTR_RING_SZ_12KB``
  accommodates 1536 entries 

``INTR_RING_SZ_16KB``
  accommodates 2048 entries 

``INTR_RING_SZ_20KB``
  accommodates 2560 entries 

``INTR_RING_SZ_24KB``
  accommodates 3072 entries 

``INTR_RING_SZ_28KB``
  accommodates 3584 entries 

``INTR_RING_SZ_32KB``
  accommodates 4096 entries 

**Description**


Each interrupt vector can be associated with 1 or more interrupt rings.
The software can choose 8 different interrupt ring sizes. The ring size
for each vector is programmed during interrupt context programming




.. c:type:: enum qdma_dev_qmax_state


**Constants**

``QMAX_CFG_UNCONFIGURED``
  queue max not configured 

``QMAX_CFG_INITIAL``
  queue max configured with
   initial default values

``QMAX_CFG_USER``
  queue max configured from
   sysfs as per user choice

**Description**


Each PF/VF device can be configured with 0 or more number of queues.
When the queue is not assigned to any function, function is in unfonfigured
state. Sysfs interface enables the users to configure the number of
queues to different functions. Upon adding the queues, function moves to
user configured state.




.. c:type:: enum cmpt_desc_sz_t


**Constants**

``CMPT_DESC_SZ_8B``
  completion size 8B 

``CMPT_DESC_SZ_16B``
  completion size 16B 

``CMPT_DESC_SZ_32B``
  completion size 32B 

``CMPT_DESC_SZ_64B``
  completion size 64B 




.. c:type:: enum desc_sz_t


**Constants**

``DESC_SZ_8B``
  descriptor size 8B 

``DESC_SZ_16B``
  descriptor size 16B 

``DESC_SZ_32B``
  descriptor size 32B 

``DESC_SZ_64B``
  descriptor size 64B 




.. c:type:: enum tigger_mode_t


**Constants**

``TRIG_MODE_DISABLE``
  disable trigger mode 

``TRIG_MODE_ANY``
  any trigger mode 

``TRIG_MODE_COUNTER``
  counter trigger mode 

``TRIG_MODE_USER``
  trigger mode of user choice 

``TRIG_MODE_TIMER``
  timer trigger mode 

``TRIG_MODE_COMBO``
  timer and counter combo trigger mode 




.. c:type:: enum q_state_t


**Constants**

``Q_STATE_DISABLED``
  Queue is not taken 

``Q_STATE_ENABLED``
  Assigned/taken. Partial config is done 

``Q_STATE_ONLINE``
  Resource/context is initialized for the queue
   and is available for data consumption




.. c:type:: struct drv_mode_name

   Structure to hold the driver name and mode

**Definition**

::

  struct drv_mode_name {
    enum qdma_drv_mode drv_mode;
    char name;
  };

**Members**

``drv_mode``
  Mode of the function 

``name``
  Driver Name 


**Description**


Mode can be set for each PF or VF group using module parameters
Refer enum qdma_drv_mode for different mode options




.. c:type:: struct qdma_q_type

   Queue type

**Definition**

::

  struct qdma_q_type {
    const char * name;
    enum queue_type_t q_type;
  };

**Members**

``name``
  Queue type name 

``q_type``
  Queue type 


**Description**


Look up table for name of the queue type and enum




.. c:type:: struct qdma_ul_cmpt_info

   Completion entry format

**Definition**

::

  struct qdma_ul_cmpt_info {
    union {unnamed_union};
    u8 rsvd;
    u16 len;
    unsigned int pidx;
    __be64 * entry;
  };

**Members**

``{unnamed_union}``
  anonymous

``rsvd``
  Reserved filed added for structure alignment 

``len``
  Length of the completion entry 

``pidx``
  Producer Index 

``entry``
  Completion entry 


**Description**


Completion Entry is user logic dependent
Current SW supported the following completion entry format




.. c:type:: struct qdma_dev_conf

   device qdma property.

**Definition**

::

  struct qdma_dev_conf {
    struct pci_dev * pdev;
    unsigned short qsets_max;
    unsigned short rsvd2;
    u8 zerolen_dma:1;
    u8 master_pf:1;
    u8 intr_moderation:1;
    u8 rsvd1:5;
    u8 vf_max;
    u8 intr_rngsz;
    u16 msix_qvec_max;
    u16 user_msix_qvec_max;
    u16 data_msix_qvec_max;
    unsigned long uld;
    enum qdma_drv_mode qdma_drv_mode;
    char name;
    char bar_num_config;
    char bar_num_user;
    char bar_num_bypass;
    int qsets_base;
    u32 bdf;
    u32 idx;
    void (* fp_user_isr_handler) (unsigned long dev_hndl, unsigned long uld);
    void (* fp_q_isr_top_dev) (unsigned long dev_hndl, unsigned long uld);
    void * debugfs_dev_root;
  };

**Members**

``pdev``
  pointer to pci_dev 

``qsets_max``
  Maximum number of queue pairs per device 

``rsvd2``
  Reserved 

``zerolen_dma``
  Indicates whether zero length
   DMA is allowed or not

``master_pf``
  Indicates whether the current pf
   is master_pf or not

``intr_moderation``
  moderate interrupt generation

``rsvd1``
  Reserved1 

``vf_max``
  Maximum number of virtual functions for
   current physical function

``intr_rngsz``
  Interrupt ring size 

``msix_qvec_max``
  max. of vectors used for queues.
   libqdma update w/ actual #

``user_msix_qvec_max``
  Max user msix vectors 

``data_msix_qvec_max``
  Max data msix vectors 

``uld``
  upper layer data, i.e. callback data 

``qdma_drv_mode``
  qdma driver mode 

``name``
  an unique string to identify the dev.
  current format: qdma[pf|vf][idx] filled in by libqdma

``bar_num_config``
  dma config bar #, < 0 not present 

``bar_num_user``
  user bar 

``bar_num_bypass``
  bypass bar 

``qsets_base``
  queue base for this funciton 

``bdf``
  device index 

``idx``
  index of device in device list 

``fp_user_isr_handler``
  user interrupt, if null,
   default libqdma handler is used

``fp_q_isr_top_dev``
  Q interrupt top,
   per-device addtional handling code

``debugfs_dev_root``
  root path for debugfs


**NOTE**

if any of the max requested is less than supported, the value will
      be updated




.. c:type:: struct qdma_version_info

   defines the per-device version information

**Definition**

::

  struct qdma_version_info {
    char rtl_version_str;
    char vivado_release_str;
    char versal_ip_str;
    char device_type_str;
  };

**Members**

``rtl_version_str``
  Version string 

``vivado_release_str``
  Release string 

``versal_ip_str``
  Versal IP version string 

``device_type_str``
  Qdma device type string 





.. c:type:: struct global_csr_conf


**Definition**

::

  struct global_csr_conf {
    unsigned int ring_sz;
    unsigned int c2h_timer_cnt;
    unsigned int c2h_cnt_th;
    unsigned int c2h_buf_sz;
    unsigned int wb_intvl;
  };

**Members**

``ring_sz``
  Descriptor ring size ie. queue depth 

``c2h_timer_cnt``
  C2H timer count  list 

``c2h_cnt_th``
  C2H counter threshold list

``c2h_buf_sz``
  C2H buffer size list 

``wb_intvl``
  Writeback interval 





.. c:type:: struct qdma_sw_sg

   qdma scatter gather request

**Definition**

::

  struct qdma_sw_sg {
    struct qdma_sw_sg * next;
    struct page * pg;
    unsigned int offset;
    unsigned int len;
    dma_addr_t dma_addr;
  };

**Members**

``next``
  pointer to next page 

``pg``
  pointer to current page 

``offset``
  offset in current page 

``len``
  length of the page 

``dma_addr``
  dma address of the allocated page 





.. c:type:: struct qdma_queue_conf

   qdma configuration parameters

**Definition**

::

  struct qdma_queue_conf {
    u32 qidx:24;
    u32 st:1;
    u32 q_type:2;
    u32 pipe:1;
    u32 irq_en:1;
    u32 desc_rng_sz_idx:4;
    u8 wb_status_en:1;
    u8 cmpl_status_acc_en:1;
    u8 cmpl_status_pend_chk:1;
    u8 desc_bypass:1;
    u8 pfetch_en:1;
    u8 fetch_credit:1;
    u8 st_pkt_mode:1;
    u8 c2h_buf_sz_idx:4;
    u8 cmpl_rng_sz_idx:4;
    u8 cmpl_desc_sz:2;
    u8 cmpl_stat_en:1;
    u8 cmpl_udd_en:1;
    u8 cmpl_timer_idx:4;
    u8 cmpl_cnt_th_idx:4;
    u8 cmpl_trig_mode:3;
    u8 cmpl_en_intr:1;
    u8 sw_desc_sz:2;
    u8 pfetch_bypass:1;
    u8 cmpl_ovf_chk_dis:1;
    u8 port_id:3;
    u8 at:1;
    u8 adaptive_rx:1;
    u8 latency_optimize:1;
    u8 init_pidx_dis:1;
    u8 mm_channel:1;
    unsigned long quld;
    void (* fp_descq_isr_top) (unsigned long qhndl, unsigned long quld);
    int (* fp_descq_c2h_packet) (unsigned long qhndl, unsigned long quld,unsigned int len, unsigned int sgcnt, struct qdma_sw_sg *sgl, void *udd);
    int (* fp_bypass_desc_fill) (void *q_hndl, enum qdma_q_mode q_mode, enum qdma_q_dir, struct qdma_request *req);
    int (* fp_proc_ul_cmpt_entry) (void *cmpt_entry, struct qdma_ul_cmpt_info *cmpt_info);
    char name;
    unsigned int rngsz;
    unsigned int rngsz_cmpt;
    unsigned int c2h_bufsz;
    u8 ping_pong_en:1;
  };

**Members**

``qidx``
  0xFFFF: libqdma choose the queue idx 0 ~
   (qdma_dev_conf.qsets_max - 1) the calling function choose the
    queue idx

``st``
  Indicates the streaming mode 

``q_type``
  queue_type_t 

``pipe``
  SDx only: inter-kernel communication pipe 

``irq_en``
  poll or interrupt 

``desc_rng_sz_idx``
  global_csr_conf.ringsz[N] 

``wb_status_en``
  writeback enable, disabled for ST C2H 

``cmpl_status_acc_en``
  sw context.cmpl_status_acc_en 

``cmpl_status_pend_chk``
  sw context.cmpl_stauts_pend_chk 

``desc_bypass``
  send descriptor to bypass out 

``pfetch_en``
  descriptor prefetch enable control 

``fetch_credit``
  sw context.frcd_en[32] 

``st_pkt_mode``
  SDx only: ST packet mode
   (i.e., with TLAST to identify the packet boundary)

``c2h_buf_sz_idx``
  global_csr_conf.c2h_buf_sz[N] 

``cmpl_rng_sz_idx``
  global_csr_conf.ringsz[N] 

``cmpl_desc_sz``
  C2H ST cmpt + immediate data, desc_sz_t 

``cmpl_stat_en``
  enable status desc. for CMPT 

``cmpl_udd_en``
  C2H Completion entry user-defined data 

``cmpl_timer_idx``
  global_csr_conf.c2h_timer_cnt[N] 

``cmpl_cnt_th_idx``
  global_csr_conf.c2h_cnt_th[N] 

``cmpl_trig_mode``
  tigger_mode_t 

``cmpl_en_intr``
  enable interrupt for CMPT 

``sw_desc_sz``
  SW Context desc size, desc_sz_t 

``pfetch_bypass``
  prefetch bypass en 

``cmpl_ovf_chk_dis``
  OVF_DIS C2H ST over flow disable 

``port_id``
  Port ID 

``at``
  Address Translation 

``adaptive_rx``
  Adaptive rx counter threshold 

``latency_optimize``
  optimize for latency 

``init_pidx_dis``
  Disable pidx initialiaztion for ST C2H 

``mm_channel``
  MM Channel 

``quld``
  user provided per-Q irq handler 

``fp_descq_isr_top``
  Q interrupt top, per-queue additional handling
   code for example, network rx napi_schedule(:c:type:`Q->napi <Q>`)

``fp_descq_c2h_packet``
  optional rx packet handler:
  	 called from irq BH (i.e.:c:func:`qdma_queue_service_bh()`)
  
  udd: user defined data in the completion entry
  sgcnt / sgl: packet data in scatter-gather list
  
    NOTE: a. do NOT modify any field of sgl
  	   b. if zero copy, do a :c:func:`get_page()` to prevent page freeing
  	   c. do loop through the sgl with sg->next and stop
  	      at sgcnt. the last sg may not have sg->next = NULL
  
  Returns:
  	0 to allow libqdma free/re-task the sgl
  	< 0, libqdma will keep the packet for processing again
  
  A single packet could contain:
  in the case of c2h_udd_en = 1:
  
  udd only (udd valid, sgcnt = 0, sgl = NULL), or
  udd + packet data in the case of c2h_udd_en = 0:
  packet data (udd = NULL, sgcnt > 0 and sgl valid)

``fp_bypass_desc_fill``
  fill the all the descriptors required for
                         transfer
  q_hndl: handle with which bypass module can request back info from
           libqdma
  
  q_mode: mode in which q is initialized
  q_dir: direction in which q is initialized
  sgcnt: number of scatter gather entries for this request
  sgl: list of scatter gather entries
  
   On calling this API, bypass module can request for descriptor using
   qdma_q_desc_get and set up as many descriptors as required for each
   scatter gather entry. If descriptors required are not available,
   it can return the number of sgcnt addressed till now and return <0
   in case of any failure

``fp_proc_ul_cmpt_entry``
  parse cmpt entry in bypass mode
  
  q_mode: mode in which q is initialized
  cmpt_entry: cmpt entry descriptor
  cmpt_info: parsed bypass related info from cmpt_entry

``name``
  name of the qdma device 

``rngsz``
  ring size of the queue 

``rngsz_cmpt``
  completion ring size of the queue 

``c2h_bufsz``
  C2H buffer size 

``ping_pong_en``
  Ping Pong measurement 


**Description**


qdma_queue_conf defines the per-dma Q property.
if any of the max requested is less than supported, the value will
be updated




.. c:type:: struct qdma_q_state

   display queue state in a string buffer

**Definition**

::

  struct qdma_q_state {
    enum q_state_t qstate;
    u32 qidx:24;
    u32 st:1;
    enum queue_type_t q_type;
  };

**Members**

``qstate``
  current q state 

``qidx``
  0xFFFF: libqdma choose the queue idx 0 ~
   (qdma_dev_conf.qsets_max - 1) the calling function choose the
    queue idx

``st``
  Indicates the streaming mode 

``q_type``
  queue type 





.. c:type:: struct qdma_request

   qdma request for read or write

**Definition**

::

  struct qdma_request {
    unsigned char opaque;
    unsigned long uld_data;
    int (* fp_done) (struct qdma_request *req, unsigned int bytes_done, int err);
    unsigned int timeout_ms;
    unsigned int count;
    u64 ep_addr;
    u8 no_memcpy:1;
    u8 write:1;
    u8 dma_mapped:1;
    u8 h2c_eot:1;
    u8 udd_len;
    unsigned int sgcnt;
    struct qdma_sw_sg * sgl;
    u8 udd;
  };

**Members**

``opaque``
  private to the dma driver, do NOT touch 

``uld_data``
  filled in by the calling function
   for the calling function

``fp_done``
  set fp_done for non-blocking mode 

``timeout_ms``
  timeout in mili-seconds, 0 - no timeout 

``count``
  total data size 

``ep_addr``
  MM only, DDR/BRAM memory addr 

``no_memcpy``
  flag to indicate if memcpy is required 

``write``
  if write to the device 

``dma_mapped``
  if sgt is already dma mapped 

``h2c_eot``
  user defined data present 

``udd_len``
  indicates end of transfer towards user kernel 

``sgcnt``
  # of scatter-gather entries < 64K 

``sgl``
  scatter-gather list of data bufs 

``udd``
  udd data 





.. c:type:: struct qdma_cmpl_ctrl

   completion control

**Definition**

::

  struct qdma_cmpl_ctrl {
    u8 cnt_th_idx:4;
    u8 timer_idx:4;
    u8 trigger_mode:3;
    u8 en_stat_desc:1;
    u8 cmpl_en_intr:1;
  };

**Members**

``cnt_th_idx``
  global_csr_conf.c2h_cnt_th[N] 

``timer_idx``
  global_csr_conf.c2h_timer_cnt[N] 

``trigger_mode``
  tigger_mode_t 

``en_stat_desc``
  enable status desc. for CMPT 

``cmpl_en_intr``
  enable interrupt for CMPT 



.. c:function:: int libqdma_init (unsigned int num_threads, void * debugfs_root)

   initializes the QDMA core library

**Parameters**

``unsigned int num_threads``
  number of threads to be created each for request
  processing and writeback processing

``void * debugfs_root``
  root path for debugfs

**Return**

0:	success <0:	error


.. c:function:: void libqdma_exit ( void)

   cleanup the QDMA core library before exiting

**Parameters**

``void``
  no arguments

**Description**


cleanup the QDMA core library before exiting


.. c:function:: void intr_legacy_init ( void)

   legacy interrupt init

**Parameters**

``void``
  no arguments


.. c:function:: int qdma_device_open (const char * mod_name, struct qdma_dev_conf * conf, unsigned long * dev_hndl)

   read the pci bars and configure the fpga This API should be called from :c:func:`probe()`

**Parameters**

``const char * mod_name``
  the module name, used for request_irq

``struct qdma_dev_conf * conf``
  device configuration

``unsigned long * dev_hndl``
  an opaque handle for libqdma to identify the device

**Description**


User interrupt will not be enabled until :c:func:`qdma_user_isr_enable()` is called

**Return**

0 in case of success and <0 in case of error


.. c:function:: int qdma_device_close (struct pci_dev * pdev, unsigned long dev_hndl)

   prepare fpga for removal: disable all interrupts (users and qdma) and release all resources.This API should be called from :c:func:`remove()`

**Parameters**

``struct pci_dev * pdev``
  ptr to struct pci_dev

``unsigned long dev_hndl``
  dev_hndl retured from :c:func:`qdma_device_open()`

**Return**

0 in case of success and <0 in case of error


.. c:function:: int qdma_device_offline (struct pci_dev * pdev, unsigned long dev_hndl, int reset)

   Set the device in offline mode

**Parameters**

``struct pci_dev * pdev``
  ptr to struct pci_dev

``unsigned long dev_hndl``
  dev_hndl retured from :c:func:`qdma_device_open()`

``int reset``
  0/1 function level reset active or not

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_online (struct pci_dev * pdev, unsigned long dev_hndl, int reset)

   Set the device in online mode and re-initialze it

**Parameters**

``struct pci_dev * pdev``
  ptr to struct pci_dev

``unsigned long dev_hndl``
  dev_hndl retured from :c:func:`qdma_device_open()`

``int reset``
  0/1 function level reset active or not

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_flr_quirk_set (struct pci_dev * pdev, unsigned long dev_hndl)

   start pre-flr processing

**Parameters**

``struct pci_dev * pdev``
  ptr to struct pci_dev

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_flr_quirk_check (struct pci_dev * pdev, unsigned long dev_hndl)

   check if pre-flr processing completed

**Parameters**

``struct pci_dev * pdev``
  ptr to struct pci_dev

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

**Return**

0 for success <0 for error


.. c:function:: int qdma_device_get_config (unsigned long dev_hndl, struct qdma_dev_conf * conf, char * ebuf, int ebuflen)

   retrieve the current device configuration

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``struct qdma_dev_conf * conf``
  device configuration

``char * ebuf``
  error message buffer, can be NULL/0 (i.e., optional)

``int ebuflen``
  input buffer length

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_clear_stats (unsigned long dev_hndl)

   clear device statistics

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_get_mmh2c_pkts (unsigned long dev_hndl, unsigned long long * mmh2c_pkts)

   get mm h2c packets processed

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``unsigned long long * mmh2c_pkts``
  number of mm h2c packets processed

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_get_mmc2h_pkts (unsigned long dev_hndl, unsigned long long * mmc2h_pkts)

   get mm c2h packets processed

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``unsigned long long * mmc2h_pkts``
  number of mm c2h packets processed

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_get_sth2c_pkts (unsigned long dev_hndl, unsigned long long * sth2c_pkts)

   get st h2c packets processed

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``unsigned long long * sth2c_pkts``
  number of st h2c packets processed

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_get_stc2h_pkts (unsigned long dev_hndl, unsigned long long * stc2h_pkts)

   get st c2h packets processed

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``unsigned long long * stc2h_pkts``
  number of st c2h packets processed

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_get_ping_pong_min_lat (unsigned long dev_hndl, unsigned long long * min_lat)

    Min latency (in CPU ticks) observed for all packets to do H2C-C2H loopback. Packet is transmitted in ST H2C direction, the user-logic ST Traffic generator is configured to loop back the packet in C2H direction. Timestamp (in CPU ticks) of the H2C transmission is embedded in H2C packet at time of PIDX update, then timestamp of the loopback packet is taken at time when data interrupt is hit, diff is used to measure roundtrip latency.

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``unsigned long long * min_lat``
  Minimum ping pong latency in CPU ticks. Divide with the nominal
  CPU freqeuncy to get latency in  NS.

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_get_ping_pong_max_lat (unsigned long dev_hndl, unsigned long long * max_lat)

    Max latency (in CPU ticks) observed for all packets to do H2C-C2H loopback. Packet is transmitted in ST H2C direction, the user-logic ST Traffic generator is configured to loop back the packet in C2H direction. Timestamp (in CPU ticks) of the H2C transmission is embedded in H2C packet at time of PIDX update, then timestamp of the loopback packet is taken at time when data interrupt is hit, diff is used to measure roundtrip latency.

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``unsigned long long * max_lat``
  Max ping pong latency in CPU ticks. Divide with the nominal
  CPU freqeuncy to get latency in  NS.

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_get_ping_pong_tot_lat (unsigned long dev_hndl, unsigned long long * lat_total)

    Total latency (in CPU ticks) observed for all packets to do H2C-C2H loopback. Packet is transmitted in ST H2C direction, the user-logic ST Traffic generator is configured to loop back the packet in C2H direction. Timestamp (in CPU ticks) of the H2C transmission is embedded in H2C packet at time of PIDX update, then timestamp of the loopback packet is taken at time when data interrupt is hit, diff is used to measure roundtrip latency.

**Parameters**

``unsigned long dev_hndl``
  dev_hndl retunred from :c:func:`qdma_device_open()`

``unsigned long long * lat_total``
  Total Ping Pong latency. Divide with total loopback C2H packets
  to get average ping pong latency. Divide further
  with the nominal CPU frequency
  to get the avg latency in NS.

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_set_config (unsigned long dev_hndl, struct qdma_dev_conf * conf)

   set the current device configuration

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``struct qdma_dev_conf * conf``
  device configuration to set

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_sriov_config (struct pci_dev * pdev, unsigned long dev_hndl, int num_vfs)

   configure sriov

**Parameters**

``struct pci_dev * pdev``
  ptr to struct pci_dev

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``int num_vfs``
  # of VFs to be instantiated

**Return**

0 for success and <0 for error

configures sriov


.. c:function:: int qdma_device_read_config_register (unsigned long dev_hndl, unsigned int reg_addr, unsigned int * value)

   read dma config register

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned int reg_addr``
  register address

``unsigned int * value``
  pointer to hold the read value

**Return**

0 for success and <0 for error

reads dma config register


.. c:function:: int qdma_device_write_config_register (unsigned long dev_hndl, unsigned int reg_addr, unsigned int value)

   write dma config register

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned int reg_addr``
  register address

``unsigned int value``
  register value to be writen

**Return**

0 for success and <0 for error
writes dma config register


.. c:function:: int qdma_device_capabilities_info (unsigned long dev_hndl, struct qdma_dev_attributes * dev_attr)

   retrieve the capabilities of a device.

**Parameters**

``unsigned long dev_hndl``
  handle returned from :c:func:`qdma_device_open()`

``struct qdma_dev_attributes * dev_attr``
  pointer to hold all the device attributes

**Return**

0 for success and <0 for error


.. c:function:: int qdma_device_version_info (unsigned long dev_hndl, struct qdma_version_info * version_info)

   retrieve the RTL version , Vivado Release ID and Versal IP info

**Parameters**

``unsigned long dev_hndl``
  handle returned from :c:func:`qdma_device_open()`

``struct qdma_version_info * version_info``
  pointer to hold all the version details

**Return**

0 for success and <0 for error

retrieves the RTL version , Vivado Release ID and Versal IP info


.. c:function:: int qdma_software_version_info (char * software_version)

   retrieve the software version

**Parameters**

``char * software_version``
  A pointer to a null-terminated string

**Return**

0 for success and <0 for error

retrieves the software version


.. c:function:: int qdma_global_csr_get (unsigned long dev_hndl, u8 index, u8 count, struct global_csr_conf * csr)

   retrieve the global csr settings

**Parameters**

``unsigned long dev_hndl``
  handle returned from :c:func:`qdma_device_open()`

``u8 index``
  Index from where the values needs to read

``u8 count``
  number of entries to be read

``struct global_csr_conf * csr``
  data structures to hold the csr values

**Return**

0 for success and <0 for error

retrieves the global csr settings


.. c:function:: int qdma_queue_add (unsigned long dev_hndl, struct qdma_queue_conf * qconf, unsigned long * qhndl, char * buf, int buflen)

   add a queue

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``struct qdma_queue_conf * qconf``
  queue configuration parameters

``unsigned long * qhndl``
  list of unsigned long values that are the opaque qhndl

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

0 for success and <0 for error


.. c:function:: int qdma_queue_config (unsigned long dev_hndl, unsigned long qid, struct qdma_queue_conf * qconf, char * buf, int buflen)

   configure the queue with qcong parameters

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long qid``
  queue id

``struct qdma_queue_conf * qconf``
  queue configuration parameters

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Description**

**return**	0: success
**return**	<0: error


.. c:function:: int qdma_queue_start (unsigned long dev_hndl, unsigned long id, char * buf, int buflen)

   start a queue (i.e, online, ready for dma)

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  the opaque qhndl

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

0 for success and <0 for error


.. c:function:: int qdma_queue_stop (unsigned long dev_hndl, unsigned long id, char * buf, int buflen)

   stop a queue (i.e., offline, NOT ready for dma)

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  the opaque qhndl

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

0 for success and <0 for error


.. c:function:: int qdma_get_queue_state (unsigned long dev_hndl, unsigned long id, struct qdma_q_state * qstate, char * buf, int buflen)

   Get the state of the queue

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  the opaque qhndl

``struct qdma_q_state * qstate``
  state of the queue

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

0 for success and <0 for error


.. c:function:: int qdma_queue_remove (unsigned long dev_hndl, unsigned long id, char * buf, int buflen)

   remove a queue

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  the opaque qhndl

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

0 for success and <0 for error


.. c:function:: int qdma_queue_get_config (unsigned long dev_hndl, unsigned long id, struct qdma_queue_conf * qconf, char * buf, int buflen)

   retrieve the configuration of a queue

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  an opaque queue handle of type unsigned long

``struct qdma_queue_conf * qconf``
  pointer to hold the qdma_queue_conf structure.

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Description**

**return**	0: success
**return**	<0: error


.. c:function:: int qdma_queue_list (unsigned long dev_hndl, char * buf, int buflen)

   display all configured queues in a string buffer

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

if optional message buffer used then strlen of buf,
	 otherwise QDMA_OPERATION_SUCCESSFUL and <0 for error


.. c:function:: int qdma_config_reg_dump (unsigned long dev_hndl, char * buf, int buflen)

   display a config registers in a string buffer

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Description**

Return	success: if optional message buffer used then strlen of buf,
	otherwise 0 and <0: error


.. c:function:: int qdma_queue_dump (unsigned long dev_hndl, unsigned long id, char * buf, int buflen)

   display a queue's state in a string buffer

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  an opaque queue handle of type unsigned long

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

if optional message buffer used then strlen of buf,
	 otherwise QDMA_OPERATION_SUCCESSFUL and <0 for error


.. c:function:: int qdma_queue_dump_desc (unsigned long dev_hndl, unsigned long id, unsigned int start, unsigned int end, char * buf, int buflen)

   display a queue's descriptor ring from index start ~ end in a string buffer

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  an opaque queue handle of type unsigned long

``unsigned int start``
  start index

``unsigned int end``
  end index

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

if optional message buffer used then strlen of buf,
	 otherwise QDMA_OPERATION_SUCCESSFUL and <0 for error


.. c:function:: int qdma_queue_dump_cmpt (unsigned long dev_hndl, unsigned long id, unsigned int start, unsigned int end, char * buf, int buflen)

   display a queue's descriptor ring from index start ~ end in a string buffer

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  an opaque queue handle of type unsigned long

``unsigned int start``
  start index

``unsigned int end``
  end index

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

if optional message buffer used then strlen of buf,
	 otherwise QDMA_OPERATION_SUCCESSFUL and <0 for error


.. c:function:: int qdma_queue_set_err_induction (unsigned long dev_hndl, unsigned long id, u32 err, char * buf, int buflen)

   Induce the error

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  error id

``u32 err``
  error info

``char * buf``
  message buffer

``int buflen``
  length of the input buffer

**Return**

if optional message buffer used then strlen of buf,
	 otherwise QDMA_OPERATION_SUCCESSFUL and <0 for error


.. c:function:: ssize_t qdma_request_submit (unsigned long dev_hndl, unsigned long id, struct qdma_request * req)

   submit a scatter-gather list of data for dma operation (for both read and write)

**Parameters**

``unsigned long dev_hndl``
  hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  queue index

``struct qdma_request * req``
  qdma request

**Return**

# of bytes transferred for success and  <0 for error


.. c:function:: ssize_t qdma_batch_request_submit (unsigned long dev_hndl, unsigned long id, unsigned long count, struct qdma_request ** reqv)

   submit a scatter-gather list of data for dma operation (for both read and write)

**Parameters**

``unsigned long dev_hndl``
  hndl returned from :c:func:`qdma_device_open()`

``unsigned long id``
  queue index

``unsigned long count``
  number of requests

``struct qdma_request ** reqv``
  qdma request

**Return**

# of bytes transferred for success and  <0 for error


.. c:function:: int qdma_queue_c2h_peek (unsigned long dev_hndl, unsigned long qhndl, unsigned int * udd_cnt, unsigned int * pkt_cnt, unsigned int * data_len)

   peek a receive (c2h) queue

**Parameters**

``unsigned long dev_hndl``
  hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  hndl returned from :c:func:`qdma_queue_add()`

``unsigned int * udd_cnt``
  # of udd received

``unsigned int * pkt_cnt``
  # of packets received

``unsigned int * data_len``
  # of bytes of packet data received

**Description**

filled in by libqdma:

**Return**

# of packets received in the Q or <0 for error


.. c:function:: int qdma_queue_avail_desc (unsigned long dev_hndl, unsigned long qhndl)

   query of # of free descriptor

**Parameters**

``unsigned long dev_hndl``
  hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  hndl returned from :c:func:`qdma_queue_add()`

**Return**

# of available desc in the queue or <0 for error


.. c:function:: int qdma_queue_cmpl_ctrl (unsigned long dev_hndl, unsigned long qhndl, struct qdma_cmpl_ctrl * cctrl, bool set)

   read/set the c2h Q's completion control

**Parameters**

``unsigned long dev_hndl``
  hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  hndl returned from :c:func:`qdma_queue_add()`

``struct qdma_cmpl_ctrl * cctrl``
  completion control

``bool set``
  read or set

**Return**

0 for success or <0 for error


.. c:function:: int qdma_queue_packet_read (unsigned long dev_hndl, unsigned long qhndl, struct qdma_request * req, struct qdma_cmpl_ctrl * cctrl)

   read rcv'ed data (ST C2H dma operation)

**Parameters**

``unsigned long dev_hndl``
  hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  hndl returned from :c:func:`qdma_queue_add()`

``struct qdma_request * req``
  pointer to the request data

``struct qdma_cmpl_ctrl * cctrl``
  completion control, if no change is desired,
  set it to NULL

**Return**

# of bytes transferred for success and  <0 for error


.. c:function:: int qdma_queue_packet_write (unsigned long dev_hndl, unsigned long qhndl, struct qdma_request * req)

   submit data for ST H2C dma operation

**Parameters**

``unsigned long dev_hndl``
  hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  hndl returned from :c:func:`qdma_queue_add()`

``struct qdma_request * req``
  pointer to the list of packet data

**Return**

# of bytes transferred for success and  <0 for error


.. c:function:: void qdma_queue_service (unsigned long dev_hndl, unsigned long qhndl, int budget, bool c2h_upd_cmpl)

   service the queue in the case of irq handler is registered by the user, the user should call :c:func:`qdma_queue_service()` in its interrupt handler to service the queue

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  hndl returned from :c:func:`qdma_queue_add()`

``int budget``
  ST C2H only, max number of completions to be processed.

``bool c2h_upd_cmpl``
  flag to update the completion


.. c:function:: void qdma_queue_update_pointers (unsigned long dev_hndl, unsigned long qhndl)

   update queue pointers

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  hndl returned from :c:func:`qdma_queue_add()`


.. c:function:: int qdma_intr_ring_dump (unsigned long dev_hndl, unsigned int vector_idx, int start_idx, int end_idx, char * buf, int buflen)

   display the interrupt ring info of a vector

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned int vector_idx``
  vector number

``int start_idx``
  interrupt ring start idx

``int end_idx``
  interrupt ring end idx

``char * buf``
  message bufferuffer

``int buflen``
  length of the input buffer

**Return**

0 for success or <0 for error


.. c:function:: int qdma_descq_get_cmpt_udd (unsigned long dev_hndl, unsigned long qhndl, char * buf, int buflen)

   function to receive the user defined data

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  queue handle

``char * buf``
  message bufferuffer

``int buflen``
  length of the input buffer

**Return**

0 for success or <0 for error


.. c:function:: int qdma_descq_read_cmpt_data (unsigned long dev_hndl, unsigned long qhndl, u32 * num_entries, u8 ** cmpt_entries, char * buf, int buflen)

   function to receive the completion data

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``unsigned long qhndl``
  queue handle

``u32 * num_entries``
  I/O number of entries

``u8 ** cmpt_entries``
  List of completion entries

``char * buf``
  message bufferuffer

``int buflen``
  length of the input buffer

**Return**

0 for success or <0 for error


.. c:function:: int qdma_vf_qconf (unsigned long dev_hndl, int qmax)

   call for VF to request qmax number of Qs

**Parameters**

``unsigned long dev_hndl``
  dev_hndl returned from :c:func:`qdma_device_open()`

``int qmax``
  number of qs requested by vf

**Return**

0 for success or <0 for error


