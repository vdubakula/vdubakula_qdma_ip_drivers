#include <linux/module.h>
#include <linux/pci.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include "ktf.h"
#include "libqdma_export.h"

MODULE_LICENSE("GPL");

#define NUM_PFS     4
#define NUM_QS      2048

KTF_INIT();

static LIST_HEAD(dev_list);

/* qdma_test private structure */
struct qdma_test_priv {
	struct list_head list_head;
	int device_id;
	struct pci_dev *pcidev;
	void __iomem *bar_base;
	struct qdma_dev_conf qdma_dev_conf;
};

#define DRV_NAME            "qdma_test_drv"
#define DRV_MODULE_NAME		"qdma"

static const struct pci_device_id pci_ids[] = {
	{ PCI_DEVICE(0x10ee, 0x903f), },	/** PF 0 */
	{ PCI_DEVICE(0x10ee, 0x913f), },	/** PF 1 */
	{ PCI_DEVICE(0x10ee, 0x923f), },	/** PF 2 */
	{ PCI_DEVICE(0x10ee, 0x933f), },	/** PF 3 */
	{ PCI_DEVICE(0x10ee, 0xb03f), },	/** PF 0 */ //Everest
	{ PCI_DEVICE(0x10ee, 0xb13f), },	/** PF 1 */
	{ PCI_DEVICE(0x10ee, 0xb23f), },	/** PF 2 */
	{ PCI_DEVICE(0x10ee, 0xb33f), },	/** PF 3 */
	{0,}
};

static void qdev_set_default(struct qdma_dev_conf *qdev_conf)
{
	qdev_conf->qdma_drv_mode = AUTO_MODE;
	qdev_conf->bar_num_config = 0;
	qdev_conf->bar_num_user = -1;
	qdev_conf->bar_num_bypass = -1;
	qdev_conf->vf_max = 0;
	qdev_conf->intr_rngsz = INTR_RING_SZ_4KB;
	qdev_conf->qsets_max = 0;
	qdev_conf->qsets_base = -1;
	qdev_conf->msix_qvec_max = 32;
	qdev_conf->user_msix_qvec_max = 1;
}

struct qparam {
	int st_mode;
	int c2h_dir;
};
static void qconf_set_default(struct qdma_queue_conf *qconf, int qno, struct qparam *qp)
{
	memset(qconf, 0, sizeof(struct qdma_queue_conf));
	qconf->qidx = qno;
	qconf->st = qp->st_mode;
	qconf->q_type = qp->c2h_dir;
	qconf->desc_rng_sz_idx = 4;
	qconf->wb_status_en = 1;
	qconf->fetch_credit = 1;
	qconf->cmpl_stat_en = 1;

	if (qconf->st) {
		if (qconf->q_type) {
			qconf->cmpl_desc_sz = DESC_SZ_8B;
			qconf->cmpl_trig_mode = TRIG_MODE_TIMER;
			qconf->cmpl_rng_sz_idx = 4;
			qconf->c2h_buf_sz_idx = 0;
			qconf->cmpl_timer_idx = 9;
			qconf->cmpl_cnt_th_idx = 0;
		} else {
			qconf->cmpl_status_acc_en = 1;
			qconf->cmpl_status_pend_chk = 1;
		}
	}
}

/*checking the num_threads params */
TEST(qdma_test, api001_libqdma_init_num_threads)
{
	int rv = 0;
	unsigned int i, num_threads[] = { 1, 2, 4, 8, 16, 32};


	for (i = 0; i < ARRAY_SIZE(num_threads); i++) {

		rv = libqdma_init(i, NULL);
		ASSERT_TRUE_GOTO(rv == 0, done);

		libqdma_exit();
	}

done: /* This code under the label will only occur if ASSERT call is true */
	libqdma_exit();
}

/* checking the debugfs params */
TEST(qdma_test, api002_libqdma_init_debugfs)
{
	int rv = 0;
	struct dentry *qdmatest_debugfs_root, *qdmatest_debugfs_parent;

	qdmatest_debugfs_root = debugfs_create_dir("libqdma_test", qdmatest_debugfs_parent);
	if (!qdmatest_debugfs_root) {
		terr("Failed to create debugfs directory\n");
	}

	rv = libqdma_init(0, qdmatest_debugfs_root);
	ASSERT_TRUE_GOTO(rv == 0, done);

	libqdma_exit();
	debugfs_remove_recursive(qdmatest_debugfs_root);
	qdmatest_debugfs_root = NULL;

done:
	libqdma_exit();
	debugfs_remove_recursive(qdmatest_debugfs_root);
	qdmatest_debugfs_root = NULL;
}

//Param: Driver Mode
TEST(qdma_test, api003_qdma_device_open_drv_mode)
{
	struct qdma_test_priv *_qdev, *tmp;
	int i = 0, rv = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;
		_qdev->qdma_dev_conf.qdma_drv_mode = _i; /* param */

		pr_info("_qdev->qdma_dev_conf.qdma_drv_mode %d", _qdev->qdma_dev_conf.qdma_drv_mode);
		pr_info("_i %d", _i);
		pr_info("_iiii %d", AUTO_MODE);

		if (i == 0) {
			_qdev->qdma_dev_conf.master_pf = 1;
		}
		i++;
		
		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}

		if (_qdev->qdma_dev_conf.qdma_drv_mode == LEGACY_INTR_MODE)
			intr_legacy_init();

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		pr_info("_qdev->qdma_dev_conf.qdma_drv_mode %d", _qdev->qdma_dev_conf.qdma_drv_mode);

		pr_info("rv = %d", rv);
		if (_qdev->qdma_dev_conf.qdma_drv_mode > LEGACY_INTR_MODE) {
			ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		} else {
			ASSERT_TRUE_GOTO(rv == 0, done);
		}

		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_device_close(pdev, dev_hndl);
	return;
}

//Invalid pdev
TEST(qdma_test, api004_qdma_device_open_pdev)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0;
	unsigned long dev_hndl;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		_qdev->qdma_dev_conf.pdev = NULL;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(_qdev->qdma_dev_conf.pdev, dev_hndl);
		goto exit_func; /* run only once */
	}

exit_func:
	return;
done:
	qdma_device_close(_qdev->qdma_dev_conf.pdev, dev_hndl);
}

//Param:qsets_max
TEST(qdma_test, api005_qdma_device_open_qsets_max)
{
	struct qdma_test_priv *_qdev, *tmp;
	int i = 0, rv = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev;
	int total_queues = 0;
	int values[5] = {256, 128, 64, 512, 3000};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;
		_qdev->qdma_dev_conf.qsets_max = values[_i]; /* param */
		total_queues += values[_i];
		_qdev->qdma_dev_conf.qsets_base = total_queues - values[_i];

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		if ((values[_i] == 3000)) {
			ASSERT_TRUE_GOTO(rv == -EPERM, done); /* qdma_device_open shall fail in this case */
		} else {
			ASSERT_TRUE_GOTO(rv == 0, done);
		}

		qdma_device_close(pdev, dev_hndl);
	}

	return;

done:
	qdma_device_close(pdev, dev_hndl);
}

//Param: Config bar
TEST(qdma_test, api006_qdma_device_open_cnfg_bar)
{
	struct qdma_test_priv *_qdev, *tmp;
	int i = 0, rv = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev;
	int values[3] = {0, 2, 4};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;
		_qdev->qdma_dev_conf.bar_num_config = values[_i]; /* param */

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		if(values[_i] == 0) {
			ASSERT_TRUE_GOTO(rv == 0, done);
		} else {
			ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		}

		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

//Param: pdev
TEST(qdma_test, api007_qdma_device_online_pdev)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev, *invld_pdev;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		rv = qdma_device_online(pdev, dev_hndl, 1);
		ASSERT_TRUE_GOTO(rv == 0, done);
		qdma_device_offline(pdev, dev_hndl, 1);

		invld_pdev = NULL;
		rv = qdma_device_online(invld_pdev, dev_hndl, 1);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;
		qdma_device_close(pdev, dev_hndl);
		goto exit_func; /* run only once */
	}

exit_func:
	return;
done:
	qdma_device_offline(pdev, dev_hndl, 1);
	pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;
	qdma_device_close(pdev, dev_hndl);
}

//Invalid dev_hndl
TEST(qdma_test, api008_qdma_device_online_dev_hndl)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	struct pci_dev *pdev;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		invld_dev_hndl = dev_hndl + 10; /* Passing the wrong dev_hndl */
		rv = qdma_device_online(pdev, invld_dev_hndl, 1);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		goto exit_func; /* run only once */
	}

exit_func:
	return;
done:
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}
//Param: pdev
TEST(qdma_test, api009_qdma_flr_set_pdev)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev, *invld_pdev;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		rv = qdma_device_flr_quirk_set(pdev, dev_hndl);
		ASSERT_TRUE_GOTO(rv == 0, done);

		invld_pdev = NULL;
		rv = qdma_device_flr_quirk_set(invld_pdev, dev_hndl);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(pdev, dev_hndl);
		goto exit_func; /* run only once */
	}

exit_func:
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

//Invalid Dev_hndl
TEST(qdma_test, api010_qdma_flr_set_dev_hndl)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	struct pci_dev *pdev;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		invld_dev_hndl = dev_hndl + 10; /* Passing the wrong dev_hndl */
		rv = qdma_device_flr_quirk_set(pdev, invld_dev_hndl);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(pdev, dev_hndl);
		goto exit_func; /* run only once */
	}

exit_func:
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

//Param: pdev
TEST(qdma_test, api011_qdma_flr_check_pdev)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev, *invld_pdev;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		rv = qdma_device_flr_quirk_check(pdev, dev_hndl);
		ASSERT_TRUE_GOTO(rv == 0, done);

		invld_pdev = NULL;
		rv = qdma_device_flr_quirk_check(invld_pdev, dev_hndl);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(pdev, dev_hndl);
		goto exit_func; /* run only once */
	}

exit_func:
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

//Invalid dev_hndl
TEST(qdma_test, api012_qdma_flr_check_dev_hndl)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	struct pci_dev *pdev;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		invld_dev_hndl = dev_hndl + 10; /* Passing the wrong dev_hndl */
		rv = qdma_device_flr_quirk_check(pdev, invld_dev_hndl);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(pdev, dev_hndl);
		goto exit_func; /* run only once */
	}

exit_func:
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

// Read/write the Value and data validation
TEST(qdma_test, api013_qdma_config_register_rdwr)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0, j = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev;
	unsigned int reg_addr = 0x244;
	unsigned int value[4] = {0x5555AAAA, 0xAAAA5555, 0x0000FFFF, 0xFFFF0000};
	unsigned int rdval;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		for(j = 0; j < 4; j++) {
			qdma_device_write_config_register(dev_hndl, reg_addr, value[j]);

			rv = qdma_device_read_config_register(dev_hndl, reg_addr, &rdval);

			EXPECT_INT_EQ(rdval, value[j]);
		}

		qdma_device_close(pdev, dev_hndl);
	}
}

//Invalid dev_hndl
TEST(qdma_test, api014_qdma_config_register_dev_hndl)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	unsigned int reg_addr = 0x244;
	unsigned int rdval;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		_qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);

		invld_dev_hndl = dev_hndl + 10;
		rv = qdma_device_write_config_register(invld_dev_hndl, reg_addr, 0x5555AAAA);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		rv = qdma_device_read_config_register(invld_dev_hndl, reg_addr, &rdval);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(_qdev->qdma_dev_conf.pdev, dev_hndl);

		goto exit_func;
	}
exit_func:
	return;
done:
	qdma_device_close(_qdev->qdma_dev_conf.pdev, dev_hndl);
}

TEST(qdma_test, api014_qdma_device_capabilities)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	struct pci_dev *pdev;
	struct qdma_dev_attributes dev_attr;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_capabilities_info(dev_hndl, &dev_attr);

		pr_info("num_pfs = %d, num_qs = %d, flr_present = %d, st_en = %d,"
				" mm_en = %d, mm_cmpt_en = %d, mailbox_en = %d", dev_attr.num_pfs,
				dev_attr.num_qs, dev_attr.flr_present, dev_attr.st_en,
				dev_attr.mm_en, dev_attr.mm_cmpt_en,dev_attr.mailbox_en);

		ASSERT_TRUE_GOTO(rv == 0, done);
		ASSERT_TRUE_GOTO(dev_attr.num_pfs == NUM_PFS, done);
		ASSERT_TRUE_GOTO(dev_attr.num_qs == NUM_QS, done);
		ASSERT_TRUE_GOTO(((dev_attr.flr_present == 0) || (dev_attr.flr_present == 1)), done);
		ASSERT_TRUE_GOTO(((dev_attr.st_en == 0) || (dev_attr.st_en == 1)), done);
		ASSERT_TRUE_GOTO(((dev_attr.mm_en == 0) || (dev_attr.mm_en == 1)), done);
		ASSERT_TRUE_GOTO(((dev_attr.mm_cmpt_en == 0) || (dev_attr.mm_cmpt_en == 1)), done);
		ASSERT_TRUE_GOTO(((dev_attr.mailbox_en == 0) || (dev_attr.mailbox_en == 1)), done);

		invld_dev_hndl = dev_hndl + 10;
		rv = qdma_device_capabilities_info(invld_dev_hndl, &dev_attr);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api015_qdma_device_version)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	struct pci_dev *pdev;
	struct qdma_version_info ver_info;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_version_info(dev_hndl, &ver_info);
		ASSERT_TRUE_GOTO(rv == 0, done);

		invld_dev_hndl = dev_hndl + 10;
		rv = qdma_device_version_info(invld_dev_hndl, &ver_info);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api016_qdma_sw_version)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev;
	char sw_ver[100];

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_software_version_info(sw_ver, 100);

		ASSERT_TRUE_GOTO(rv == 0, done);

		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api017_qdma_csr_get)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	struct global_csr_conf csr_conf;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		_qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);
		rv = qdma_global_csr_get(dev_hndl, 0, 16, &csr_conf);

		ASSERT_TRUE_GOTO(rv == 0, done);

		invld_dev_hndl = dev_hndl + 10;
		rv = qdma_global_csr_get(invld_dev_hndl, 0, 16, &csr_conf);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_offline(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);
		qdma_device_close(_qdev->qdma_dev_conf.pdev, dev_hndl);
	}
	return;
done:
    qdma_device_offline(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);
	qdma_device_close(_qdev->qdma_dev_conf.pdev, dev_hndl);
}

TEST(qdma_test, api018_qdma_csr_get_index)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev;
	struct global_csr_conf csr_conf;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);
		rv = qdma_global_csr_get(dev_hndl, _i, 16, &csr_conf);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
    qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api019_qdma_csr_get_count)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl;
	struct pci_dev *pdev;
	struct global_csr_conf csr_conf;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);
		rv = qdma_global_csr_get(dev_hndl, 0, _i, &csr_conf);

		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
    qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api020_qdma_get_config)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	unsigned long dev_hndl, invld_dev_hndl;
	struct pci_dev *pdev;
	struct qdma_dev_conf conf;
	char ebuf[100];

	strcpy(ebuf, "deadbeef");

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_get_config(dev_hndl, &conf, ebuf, sizeof(ebuf));

		ASSERT_TRUE_GOTO(rv == 0, done);
		ASSERT_TRUE_GOTO(memcmp(&conf, &_qdev->qdma_dev_conf, sizeof(struct qdma_dev_conf)) == 0, done);
		pr_info("qdma_device_get_config buffer: %s", ebuf);
		ASSERT_TRUE_GOTO(strcmp(ebuf, "deadbeef") != 0, done);

		/* Invalid dev_hndl */
		invld_dev_hndl = dev_hndl + 10;
		rv = qdma_device_get_config(invld_dev_hndl, &conf, ebuf, sizeof(ebuf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api021_qdma_q_add)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl;
	struct pci_dev *pdev;
	char buf[100];
	struct qdma_queue_conf qconf;
	int qno;
	struct qparam qp[4] =
	{
			{0 , 0}, /* mm mode , h2c dir */
			{0 , 1}, /* mm mode, c2h dir */
			{1 , 0}, /* st mode, h2c dir */
			{1 , 1}  /* st mode, c2h dir */
	};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 64; /* param */
		total_queues += 64;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 64;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);

			strcpy(buf, "deadbeef");
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);

			ASSERT_TRUE_GOTO(strcmp(qconf.name, "deadbeef") != 0, done);

			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			strcpy(buf, "deadbeef");
			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);

			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api022_qdma_q_add_st_c2h_trig_mode)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl;
	struct pci_dev *pdev;
	char buf[100];
	struct qdma_queue_conf qconf;
	struct qparam qp = { 1 , 1};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 64; /* param */
		total_queues += 64;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 64;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		qconf_set_default(&qconf, 0, &qp);

		qconf.cmpl_trig_mode = _i; /* Param */
		pr_info("qconf.cmpl_trig_mode %d", qconf.cmpl_trig_mode);

		strcpy(buf, "deadbeef");
		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		if ( qconf.cmpl_trig_mode > TRIG_MODE_COMBO) {
			ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		} else {
			ASSERT_TRUE_GOTO(rv == 0, done);
		}

		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api023_qdma_q_add_invalid_qidx)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl;
	struct pci_dev *pdev;
	char buf[100];
	struct qdma_queue_conf qconf;
	struct qparam qp = { 1 , 1};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 64; /* param */
		total_queues += 64;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 64;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		/* Setting invalid qidx */
		qconf_set_default(&qconf, _qdev->qdma_dev_conf.qsets_max + 1, &qp);

		strcpy(buf, "deadbeef");

		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		strcpy(buf, "deadbeef");
		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api024_qdma_q_add_invalid_devhndl)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, dev_hndl_tmp;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	struct qparam qp = { 1 , 1};



	strcpy(buf, "deadbeef");

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 64; /* param */
		total_queues += 64;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 64;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		/* Setting invalid dev_hndl */
		qconf_set_default(&qconf, 0, &qp);

		dev_hndl_tmp = dev_hndl + 10;
		rv = qdma_queue_add(dev_hndl_tmp, &qconf, &qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api025_qdma_q_start)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, invld_dev_hndl, invld_qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	int qno;
	struct qparam qp[2] = { {1 , 0}, {1 , 1} };
	struct qparam qp1 = {1 , 0};



	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 64; /* param */
		total_queues += 64;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 64;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);

			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
			strcpy(buf, "deadbeef");
			rv = qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			/* add a delay */
			mdelay(10);

			strcpy(buf, "deadbeef");
			rv = qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		}

		qconf_set_default(&qconf, 0, &qp1);
		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		invld_dev_hndl = dev_hndl + 10;
		invld_qhndl = qhndl + 10;

		 //Invalid dev_hndl
		strcpy(buf, "deadbeef");
		rv = qdma_queue_start(invld_dev_hndl, qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_queue_start buffer: %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		strcpy(buf, "deadbeef");
		rv = qdma_queue_stop(invld_dev_hndl, qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_queue_stop buffer: %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		//invalid qhndl
		strcpy(buf, "deadbeef");
		rv = qdma_queue_start(dev_hndl, invld_qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_queue_start buffer: %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		strcpy(buf, "deadbeef");
		rv = qdma_queue_stop(dev_hndl, invld_qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_queue_start buffer: %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api026_qdma_q_state)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, invld_dev_hndl, invld_qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	struct qdma_q_state qstate;
	struct qparam qp[2] = { {1 , 0}, {1 , 1} };
	struct qparam qp1 = {1 , 0};
	int qno;



	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 64; /* param */
		total_queues += 64;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 64;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));

			strcpy(buf, "deadbeef");
			rv = qdma_get_queue_state(dev_hndl, qhndl, &qstate, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);
			ASSERT_TRUE_GOTO(qstate.qstate == 1, done);
			ASSERT_TRUE_GOTO(qstate.qidx == qno, done);
			ASSERT_TRUE_GOTO(qstate.st == 1, done);
			ASSERT_TRUE_GOTO(qstate.q_type == qp[_i].c2h_dir, done);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);


			rv = qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));
			strcpy(buf, "deadbeef");
			rv = qdma_get_queue_state(dev_hndl, qhndl, &qstate, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);
			ASSERT_TRUE_GOTO(qstate.qstate == 2, done);
			ASSERT_TRUE_GOTO(qstate.qidx == qno, done);
			ASSERT_TRUE_GOTO(qstate.st == 1, done);
			ASSERT_TRUE_GOTO(qstate.q_type == qp[_i].c2h_dir, done);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			/* add a delay */
			mdelay(10);

			rv = qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
			strcpy(buf, "deadbeef");
			rv = qdma_get_queue_state(dev_hndl, qhndl, &qstate, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);
			ASSERT_TRUE_GOTO(qstate.qstate == 1, done);
			ASSERT_TRUE_GOTO(qstate.qidx == qno, done);
			ASSERT_TRUE_GOTO(qstate.st == 1, done);
			ASSERT_TRUE_GOTO(qstate.q_type == qp[_i].c2h_dir, done);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		}

		qconf_set_default(&qconf, 0, &qp1);
		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		invld_dev_hndl = dev_hndl + 10;
		invld_qhndl = qhndl + 10;

		 //Invalid dev_hndl
		rv = qdma_get_queue_state(invld_dev_hndl, qhndl, &qstate, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_get_queue_state buffer: %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		//invalid qhndl
		strcpy(buf, "deadbeef");
		rv = qdma_get_queue_state(dev_hndl, invld_qhndl, &qstate, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_get_queue_state buffer: %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api027_qdma_q_get_config)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, invld_dev_hndl, invld_qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	struct qdma_queue_conf qconf_rd;
	struct qparam qp[2] = { {1 , 0}, {1 , 1} };
	int qno;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 64; /* param */
		total_queues += 64;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 64;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);

			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));

			strcpy(buf, "deadbeef");
			rv = qdma_queue_get_config(dev_hndl, qhndl, &qconf_rd, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == 0, done);
			ASSERT_TRUE_GOTO(memcmp(&qconf_rd, &qconf, sizeof(struct qdma_queue_conf)) == 0, done);
			pr_info("qdma_queue_get_config buffer: %s", buf);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			strcpy(buf, "deadbeef");
			invld_dev_hndl = dev_hndl + 10;
			rv = qdma_queue_get_config(invld_dev_hndl, qhndl, &qconf_rd, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == -EINVAL, done);
			pr_info("qdma_queue_get_config buffer: %s", buf);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);


			invld_qhndl = qhndl + 200;
			strcpy(buf, "deadbeef");
			rv = qdma_queue_get_config(dev_hndl, invld_qhndl, &qconf_rd, buf, sizeof(buf));
			ASSERT_TRUE_GOTO(rv == -EINVAL, done);
			pr_info("qdma_queue_get_config buffer: %s", buf);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api028_qdma_q_list_1)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, base_qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	int qno;
	struct qparam qp[2] = { {1, 0} , {1 , 1} };

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 8; /* param */
		total_queues += 8;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 8;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
			if (qno == 0)
				base_qhndl = qhndl;
			qhndl += qno;
		}

		strcpy(buf, "deadbeef");
		rv = qdma_queue_list(dev_hndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO((rv > 0), done);
		pr_info("qdma_queue_list buffer %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			rv = qdma_queue_remove(dev_hndl, (base_qhndl + qno), buf, sizeof(buf));
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api029_qdma_q_list_2)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, base_qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	int qno;
	struct qparam qp[2] = { {1, 0} , {1 , 1} };

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 8; /* param */
		total_queues += 8;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 8;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
			rv = qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));
			if (qno == 0)
				base_qhndl = qhndl;
			qhndl += qno;
		}

		strcpy(buf, "deadbeef");
		rv = qdma_queue_list(dev_hndl, buf, sizeof(buf));
		pr_info("rv = %d", rv);
		ASSERT_TRUE_GOTO((rv > 0), done);
		pr_info("qdma_queue_list buffer %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			rv = qdma_queue_stop(dev_hndl, (base_qhndl + qno), buf, sizeof(buf));
			rv = qdma_queue_remove(dev_hndl, (base_qhndl + qno), buf, sizeof(buf));
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api030_qdma_q_list_invalid_params)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, invld_dev_hndl, qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	char *buf1 = NULL;
	struct qdma_queue_conf qconf;
	struct qparam qp = { 1 , 0};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 8; /* param */
		total_queues += 8;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 8;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		qconf_set_default(&qconf, 0, &qp);
		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		rv = qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		/* invalid dev_hndl */
		invld_dev_hndl = dev_hndl + 10;
		strcpy(buf, "deadbeef");
		rv = qdma_queue_list(invld_dev_hndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		/* invalid buf */
		rv = qdma_queue_list(dev_hndl, buf1, sizeof(buf1));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		rv = qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api031_qdma_q_dump)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl;
	struct pci_dev *pdev;
	char buf[8000];
	struct qdma_queue_conf qconf;
	int qno;
	struct qparam qp[2] = { {1, 0} , {1 , 1} };

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 4; /* param */
		total_queues += 4;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 4;

		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));

			strcpy(buf, "deadbeef");
			rv = qdma_queue_dump(dev_hndl, qhndl, buf, sizeof(buf));
			pr_info("qdma_queue_dump rv %d", rv);
			ASSERT_TRUE_GOTO((rv > 0), done);
			pr_info("qdma_queue_dump buffer %s", buf);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api032_qdma_q_dump_invalid_params)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, invld_qhndl, invld_dev_hndl;
	struct pci_dev *pdev;
	char buf[3000];
	char *buf1;
	struct qdma_queue_conf qconf;
	struct qparam qp = { 1 , 0};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 2; /* param */
		total_queues += 2;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 2;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		qconf_set_default(&qconf, 0, &qp);
		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));

		/* invalid dev_hndl */
		invld_dev_hndl = dev_hndl + 10;
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump(invld_dev_hndl, qhndl, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		/* invalid qhndl */
		invld_qhndl = qhndl + 10;
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump(dev_hndl, invld_qhndl, buf, sizeof(buf));
		pr_info("qdma_queue_dump buffer %s", buf);
		pr_info("rv = %d", rv);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		/* invalid buf */
		rv = qdma_queue_dump(dev_hndl, qhndl, buf1, sizeof(buf1));
		pr_info("rv = %d", rv);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));


		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api033_qdma_q_dump_desc)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	int qno;
	struct qparam qp[2] = { {1, 0} , {1 , 1} };

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 8; /* param */
		total_queues += 8;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 8;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));

			strcpy(buf, "deadbeef");
			rv = qdma_queue_dump_desc(dev_hndl, qhndl, 0, 5, buf, sizeof(buf));
			ASSERT_TRUE_GOTO((rv > 0), done);
			pr_info("qdma_queue_dump_desc buffer %s", buf);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		}

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp[_i]);
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
			rv = qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

			strcpy(buf, "deadbeef");
			rv = qdma_queue_dump_desc(dev_hndl, qhndl, 0, 5, buf, sizeof(buf));
			ASSERT_TRUE_GOTO((rv > 0), done);
			pr_info("qdma_queue_dump_desc buffer %s", buf);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			rv = qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		}


		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api034_qdma_q_dump_desc_invalid_params)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, invld_dev_hndl, invld_qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	char *buf1;
	struct qdma_queue_conf qconf;
	struct qparam qp = { 1 , 1};

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 8; /* param */
		total_queues += 8;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 8;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		qconf_set_default(&qconf, 0, &qp);
		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));

		/* invalid dev_hndl */
		invld_dev_hndl = dev_hndl + 10;
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump_desc(invld_dev_hndl, qhndl, 0, 5, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		/* invalid qhndl */
		invld_qhndl = qhndl + 10;
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump_desc(dev_hndl, invld_qhndl, 0, 3, buf, sizeof(buf));
		pr_info("qdma_queue_dump_desc buffer %s", buf);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		/* invalid buf */
		rv = qdma_queue_dump_desc(dev_hndl, qhndl, 0, 3, buf1, sizeof(buf1));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		/* invalid end, start */
		/* start < end */
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump_desc(dev_hndl, qhndl, 3, 0, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_queue_dump_desc buffer %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api035_qdma_q_dump_cmpt)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	int qno;
	struct qparam qp = { 1 , 1};



	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 8; /* param */
		total_queues += 8;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 8;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		for(qno = 0; qno < _qdev->qdma_dev_conf.qsets_max; qno++) {
			qconf_set_default(&qconf, qno, &qp);
			rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
			rv = qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

			strcpy(buf, "deadbeef");
			rv = qdma_queue_dump_cmpt(dev_hndl, qhndl, 0, 3, buf, sizeof(buf));
			ASSERT_TRUE_GOTO((rv > 0), done);
			pr_info("qdma_queue_dump_cmpt buffer %s", buf);
			ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

			rv = qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
			rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
		}


		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api036_qdma_q_dump_cmpt_invalid_params)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0, i = 0;
	int total_queues = 0;
	unsigned long dev_hndl, qhndl, invld_dev_hndl, invld_qhndl;
	struct pci_dev *pdev;
	char buf[3000];
	struct qdma_queue_conf qconf;
	struct qparam qp = { 1 , 1};



	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 8; /* param */
		total_queues += 8;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 8;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(pdev, dev_hndl, 1);

		qconf_set_default(&qconf, 0, &qp);
		rv = qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		rv = qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		/* invalid dev_hndl */
		invld_dev_hndl = dev_hndl + 10;
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump_cmpt(invld_dev_hndl, qhndl, 0, 5, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		/* invalid qhndl */
		invld_qhndl = qhndl + 10;
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump_cmpt(dev_hndl, invld_qhndl, 0, 3, buf, sizeof(buf));
		pr_info("rv = %d", rv);
		pr_info("qdma_queue_dump_cmpt buffer %s", buf);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		/* invalid end, start */
		/* start < end */
		strcpy(buf, "deadbeef");
		rv = qdma_queue_dump_cmpt(dev_hndl, qhndl, 3, 0, buf, sizeof(buf));
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);
		pr_info("qdma_queue_dump_cmpt buffer %s", buf);
		ASSERT_TRUE_GOTO(strcmp(buf, "deadbeef") != 0, done);

		rv = qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		rv = qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));


		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();
	}
	return;
done:
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}


/* TRANSFER APIS*/
struct dma_addr {
	char *dmabuf;
	dma_addr_t phys_addr;
};

void prepare_qdma_request(struct qdma_sw_sg *sg, struct qdma_request *req, unsigned int sgcnt, unsigned long len, int write)
{
	req->sgcnt = sgcnt;
	req->count = len;
	req->sgl = sg;
	req->write = write;
	req->dma_mapped = 1;
	req->timeout_ms = 10 * 1000;	/* 10 seconds */
	req->udd_len = 0;
	req->ep_addr = 0;
	req->fp_done = NULL;		/* blocking */
	req->h2c_eot = 0;		/* set to 1 for STM tests */
}


TEST(qdma_test, api37_mm_transfer)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0;
	struct pci_dev *pdev;
	unsigned int sgcnt;
	unsigned long len, length;
	struct qdma_request req;
	struct qdma_sw_sg *sgl, *sg;
	struct dma_addr *wrbuf, *rdbuf;
	struct qdma_queue_conf qconf;
	unsigned long dev_hndl, qhndl;
	char buf[3000];
	unsigned int nbytes;
	int total_queues = 0;
	unsigned long i = 0, j = 0;
	unsigned long len_arr[4] = {64, 256, 4096, 8192};
	ssize_t rlen;
	unsigned long long mmh2c_pkts, mmc2h_pkts;

	length = len = len_arr[_i];
	sgcnt = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;

	memset(&req, 0, sizeof(struct qdma_request));

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sg = sgl;
	wrbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!wrbuf) {
		pr_err("allocation failed");
		return;
	}
	rdbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!rdbuf) {
		pr_err("allocation failed");
		return;
	}

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 2; /* param */
		total_queues += 2;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 2;

		_qdev->qdma_dev_conf.qdma_drv_mode = DIRECT_INTR_MODE;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);

		/* MM H2C */
		memset(&qconf, 0, sizeof(struct qdma_queue_conf));
		qconf.qidx = 0;
		qconf.st = 0;
		qconf.q_type = 0;
		qconf.desc_rng_sz_idx = 4;
		qconf.irq_en = 1;
		qconf.wb_status_en = 1;

		qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		qdma_queue_config(dev_hndl, qhndl, &qconf, buf, sizeof(buf));
		qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		sgl = sg;
		for(i = 0; i < sgcnt; i++,sgl++) {
			wrbuf[i].dmabuf = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					&wrbuf[i].phys_addr, GFP_KERNEL);

			nbytes = min_t(unsigned int, PAGE_SIZE, len);
			/* fill in the buffers with data */
			for(j = 0; j < nbytes; j++) {
				memset((wrbuf[i].dmabuf + j), j+1, 1);
			}

			if (i == sgcnt - 1)
				sgl->next = NULL;
			else
				sgl->next = sgl + 1;

			sgl->pg = virt_to_page(wrbuf[i].dmabuf);
			sgl->dma_addr = wrbuf[i].phys_addr;
			sgl->len = nbytes;
			sgl->offset = 0;

			len -= nbytes;
		}

		prepare_qdma_request(sg, &req, sgcnt, len_arr[_i], 1);

		rlen = qdma_request_submit(dev_hndl, qhndl, &req);

		rv = qdma_device_get_mmh2c_pkts(dev_hndl, &mmh2c_pkts);
		EXPECT_INT_EQ(rv, 0);
		EXPECT_INT_EQ(mmh2c_pkts, sgcnt);

		qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		/* MM C2H */
		memset(&qconf, 0, sizeof(struct qdma_queue_conf));
		qconf.qidx = 0;
		qconf.st = 0;
		qconf.q_type = 1;
		qconf.desc_rng_sz_idx = 4;
		qconf.irq_en = 1;
		qconf.wb_status_en = 1;

		len = len_arr[_i];
		qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		qdma_queue_config(dev_hndl, qhndl, &qconf, buf, sizeof(buf));
		qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		sgl = sg;
		for(i = 0; i < sgcnt; i++,sgl++) {
			rdbuf[i].dmabuf = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					&rdbuf[i].phys_addr, GFP_KERNEL);

			nbytes = min_t(unsigned int, PAGE_SIZE, len);

			if (i == sgcnt - 1)
				sgl->next = NULL;
			else
				sgl->next = sgl + 1;

			sgl->pg = virt_to_page(rdbuf[i].dmabuf);
			sgl->dma_addr = rdbuf[i].phys_addr;
			sgl->len = nbytes;
			sgl->offset = 0;

			len -= nbytes;
		}

		prepare_qdma_request(sg, &req, sgcnt, len_arr[_i], 0);

		rlen = qdma_request_submit(dev_hndl, qhndl, &req);

		rv = qdma_device_get_mmc2h_pkts(dev_hndl, &mmc2h_pkts);
		EXPECT_INT_EQ(rv, 0);
		EXPECT_INT_EQ(mmc2h_pkts, sgcnt);

		qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		/* COMPARISON */
		len = len_arr[_i];
		for(i = 0; i < sgcnt; i++) {
			nbytes = min_t(unsigned int, PAGE_SIZE, len);
			rv = memcmp(wrbuf[i].dmabuf, rdbuf[i].dmabuf, nbytes);
			EXPECT_INT_EQ(rv, 0);
			len -= nbytes;
		}

		/* CLEANUP */
		for(i = 0; i < sgcnt; i++) {
			dma_free_coherent(&pdev->dev, PAGE_SIZE, wrbuf[i].dmabuf,
					wrbuf[i].phys_addr);

			dma_free_coherent(&pdev->dev, PAGE_SIZE, rdbuf[i].dmabuf,
					rdbuf[i].phys_addr);
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();

		goto exit_func; /* run only once */
	}
exit_func:
	return;
}

TEST(qdma_test, api38_st_h2c_transfer)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0;
	struct pci_dev *pdev;
	unsigned int sgcnt;
	unsigned long len, length;
	struct qdma_request req;
	struct qdma_sw_sg *sgl, *sg;
	struct dma_addr *wrbuf, *rdbuf;
	struct qdma_queue_conf qconf;
	unsigned long dev_hndl, qhndl;
	char buf[3000];
	unsigned int nbytes;
	int total_queues = 0;
	unsigned long i = 0, j = 0;
	unsigned long len_arr[4] = {10, 256, 4096, 8192};
	ssize_t rlen;
	int map_len;
	void __iomem *user_bar_regs;
	unsigned long long sth2c_pkts;

	length = len = len_arr[_i];
	sgcnt = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;

	memset(&req, 0, sizeof(struct qdma_request));

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sg = sgl;
	wrbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!wrbuf) {
		pr_err("allocation failed");
		return;
	}
	rdbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!rdbuf) {
		pr_err("allocation failed");
		return;
	}

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 4; /* param */
		total_queues += 4;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 4;

		_qdev->qdma_dev_conf.qdma_drv_mode = DIRECT_INTR_MODE;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);

		/* ST H2C */
		memset(&qconf, 0, sizeof(struct qdma_queue_conf));
		qconf.qidx = 3;
		qconf.st = 1;
		qconf.q_type = 0;
		qconf.desc_rng_sz_idx = 4;
		qconf.irq_en = 1;
		qconf.wb_status_en = 1;

		qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		qdma_queue_config(dev_hndl, qhndl, &qconf, buf, sizeof(buf));
		qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		sgl = sg;
		for(i = 0; i < sgcnt; i++,sgl++) {
			wrbuf[i].dmabuf = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					&wrbuf[i].phys_addr, GFP_KERNEL);

			nbytes = min_t(unsigned int, PAGE_SIZE, len);

			/* fill in the buffers with data */
			for(j = 0; j < nbytes; j++) {
				memset((wrbuf[i].dmabuf + j), j, 1);
			}

			if (i == sgcnt - 1)
				sgl->next = NULL;
			else
				sgl->next = sgl + 1;

			sgl->pg = virt_to_page(wrbuf[i].dmabuf);
			sgl->dma_addr = wrbuf[i].phys_addr;
			sgl->len = nbytes;
			sgl->offset = 0;

			len -= nbytes;
		}

		prepare_qdma_request(sg, &req, sgcnt, len_arr[_i], 1);

		len = len_arr[_i];
		j = 0;
		for(i = 0; i < sgcnt; i++) {
			nbytes = min_t(unsigned int, PAGE_SIZE, len);
			for(; j < (nbytes + (i*PAGE_SIZE)); j++) {
				memset((wrbuf[i].dmabuf + j), j, 1);
			}
			len -= nbytes;
			j += nbytes;
		}

		rlen = qdma_request_submit(dev_hndl, qhndl, &req);

		rv = qdma_device_get_sth2c_pkts(dev_hndl, &sth2c_pkts);
		EXPECT_INT_EQ(rv, 0);
		EXPECT_INT_EQ(sth2c_pkts, sgcnt);

		map_len = pci_resource_len(pdev, 2);
		user_bar_regs = pci_iomap(pdev, 2, map_len);


		pr_info("value = 0x%x", readl(user_bar_regs + 0x10));

		EXPECT_INT_EQ(readl(user_bar_regs + 0x10), 0x30);

		qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		/* CLEANUP */
		for(i = 0; i < sgcnt; i++) {
			dma_free_coherent(&pdev->dev, PAGE_SIZE, wrbuf[i].dmabuf,
					wrbuf[i].phys_addr);
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();

		goto exit_func; /* run only once */
	}
exit_func:
	return;
}

TEST(qdma_test, api39_st_c2h_transfer)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0;
	struct pci_dev *pdev;
	unsigned int sgcnt;
	unsigned long len;
	struct qdma_request req;
	struct qdma_sw_sg *sgl, *sg;
	struct dma_addr *wrbuf, *rdbuf;
	struct qdma_queue_conf qconf;
	unsigned long dev_hndl, qhndl;
	char buf[3000];
	uint16_t dbuf[100];
	unsigned int nbytes;
	int total_queues = 0;
	unsigned long i = 0;
	unsigned long length = 64;
	ssize_t rlen;
	int map_len;
	void __iomem *user_bar_regs;
	unsigned long long stc2h_pkts;

	len = length;
	sgcnt = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;

	memset(&req, 0, sizeof(struct qdma_request));

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sg = sgl;
	wrbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!wrbuf) {
		pr_err("allocation failed");
		return;
	}
	rdbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!rdbuf) {
		pr_err("allocation failed");
		return;
	}

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 5; /* param */
		total_queues += 5;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 5;

		_qdev->qdma_dev_conf.qdma_drv_mode = DIRECT_INTR_MODE;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);

		/* MM C2H */
		memset(&qconf, 0, sizeof(struct qdma_queue_conf));
		qconf.qidx = 4;
		qconf.st = 1;
		qconf.q_type = 1;
		qconf.desc_rng_sz_idx = 4;
		qconf.irq_en = 1;
		qconf.wb_status_en = 1;
		qconf.cmpl_desc_sz = DESC_SZ_8B;
		qconf.cmpl_trig_mode = TRIG_MODE_ANY;
		qconf.cmpl_rng_sz_idx = 4;
		qconf.c2h_buf_sz_idx = 0;
		qconf.cmpl_timer_idx = 9;
		qconf.cmpl_cnt_th_idx = 0;
		qconf.fetch_credit = 1;
		qconf.cmpl_stat_en = 1;
		qconf.cmpl_en_intr = 1;

		len = length;
		qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		qdma_queue_config(dev_hndl, qhndl, &qconf, buf, sizeof(buf));
		qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		sgl = sg;
		for(i = 0; i < sgcnt; i++,sgl++) {
			rdbuf[i].dmabuf = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					&rdbuf[i].phys_addr, GFP_KERNEL);

			nbytes = min_t(unsigned int, PAGE_SIZE, len);

			if (i == sgcnt - 1)
				sgl->next = NULL;
			else
				sgl->next = sgl + 1;

			sgl->pg = virt_to_page(rdbuf[i].dmabuf);
			sgl->dma_addr = rdbuf[i].phys_addr;
			sgl->len = nbytes;
			sgl->offset = 0;

			len -= nbytes;
		}

		prepare_qdma_request(sg, &req, sgcnt, length, 0);

		map_len = pci_resource_len(pdev, 2);
		user_bar_regs = pci_iomap(pdev, 2, map_len);

		writel(4, (user_bar_regs + 0x0));
		/* Write transfer size to offset 0x04 */
		writel(length, (user_bar_regs + 0x4));
		/* Write number of packets to offset 0x20 */
		writel(1, (user_bar_regs + 0x20));
		/* Write to offset 0x80 bit [1] to trigger C2H data generator */
		writel(2, (user_bar_regs + 0x8));

		rlen = qdma_request_submit(dev_hndl, qhndl, &req);

		rv = qdma_device_get_stc2h_pkts(dev_hndl, &stc2h_pkts);
		EXPECT_INT_EQ(rv, 0);
		EXPECT_INT_EQ(stc2h_pkts, sgcnt);


		qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		for(i = 0; i < length; i++) {
			dbuf[i] = i;
		}
		/* COMPARISON */
		len = length;
		for(i = 0; i < sgcnt; i++) {
			nbytes = min_t(unsigned int, PAGE_SIZE, len);
			rv = memcmp(dbuf, rdbuf[i].dmabuf, nbytes);
			EXPECT_INT_EQ(rv, 0);
			len -= nbytes;
		}

		/* CLEANUP */
		for(i = 0; i < sgcnt; i++) {
			dma_free_coherent(&pdev->dev, PAGE_SIZE, rdbuf[i].dmabuf,
					rdbuf[i].phys_addr);
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();

		goto exit_func; /* run only once */
	}
exit_func:
	return;
}

TEST(qdma_test, api40_qdma_request_submit_invld_params)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0;
	struct pci_dev *pdev;
	unsigned int sgcnt;
	unsigned long len;
	struct qdma_request req;
	struct qdma_sw_sg *sgl, *sg;
	struct dma_addr *wrbuf, *rdbuf;
	struct qdma_queue_conf qconf;
	unsigned long dev_hndl, qhndl, invld_dev_hndl, invld_qhndl;
	char buf[3000];
	unsigned int nbytes;
	int total_queues = 0;
	unsigned long i = 0;
	unsigned long length = 64;

	len = length;
	sgcnt = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;

	memset(&req, 0, sizeof(struct qdma_request));

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sg = sgl;
	wrbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!wrbuf) {
		pr_err("allocation failed");
		return;
	}
	rdbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!rdbuf) {
		pr_err("allocation failed");
		return;
	}

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 5; /* param */
		total_queues += 5;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 5;

		_qdev->qdma_dev_conf.qdma_drv_mode = DIRECT_INTR_MODE;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);

		/* MM C2H */
		memset(&qconf, 0, sizeof(struct qdma_queue_conf));
		qconf.qidx = 4;
		qconf.st = 1;
		qconf.q_type = 1;
		qconf.desc_rng_sz_idx = 4;
		qconf.irq_en = 1;
		qconf.wb_status_en = 1;
		qconf.cmpl_desc_sz = DESC_SZ_8B;
		qconf.cmpl_trig_mode = TRIG_MODE_ANY;
		qconf.cmpl_rng_sz_idx = 4;
		qconf.c2h_buf_sz_idx = 0;
		qconf.cmpl_timer_idx = 9;
		qconf.cmpl_cnt_th_idx = 0;
		qconf.fetch_credit = 1;
		qconf.cmpl_stat_en = 1;
		qconf.cmpl_en_intr = 1;

		len = length;
		qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		qdma_queue_config(dev_hndl, qhndl, &qconf, buf, sizeof(buf));
		qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		sgl = sg;
		for(i = 0; i < sgcnt; i++,sgl++) {
			rdbuf[i].dmabuf = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					&rdbuf[i].phys_addr, GFP_KERNEL);

			nbytes = min_t(unsigned int, PAGE_SIZE, len);

			if (i == sgcnt - 1)
				sgl->next = NULL;
			else
				sgl->next = sgl + 1;

			sgl->pg = virt_to_page(rdbuf[i].dmabuf);
			sgl->dma_addr = rdbuf[i].phys_addr;
			sgl->len = nbytes;
			sgl->offset = 0;

			len -= nbytes;
		}

		prepare_qdma_request(sg, &req, sgcnt, length, 0);

		invld_dev_hndl = dev_hndl + 10;
		rv = qdma_request_submit(invld_dev_hndl, qhndl, &req);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		invld_qhndl = qhndl + 10;
		rv = qdma_request_submit(dev_hndl, invld_qhndl, &req);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		/* CLEANUP */
		for(i = 0; i < sgcnt; i++) {
			dma_free_coherent(&pdev->dev, PAGE_SIZE, rdbuf[i].dmabuf,
					rdbuf[i].phys_addr);
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();

		goto exit_func; /* run only once */
	}
exit_func:
	return;
done:
	qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api41_qdma_queue_packet_write)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0;
	struct pci_dev *pdev;
	unsigned int sgcnt;
	unsigned long len, length;
	struct qdma_request req;
	struct qdma_sw_sg *sgl, *sg;
	struct dma_addr *wrbuf, *rdbuf;
	struct qdma_queue_conf qconf;
	unsigned long dev_hndl, qhndl, invld_dev_hndl, invld_qhndl;
	char buf[3000];
	unsigned int nbytes;
	int total_queues = 0;
	unsigned long i = 0, j = 0;
	unsigned long len_arr[4] = {10, 256, 4096, 8192};
	ssize_t rlen;
	int map_len;
	void __iomem *user_bar_regs;

	length = len = len_arr[_i];
	sgcnt = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;

	memset(&req, 0, sizeof(struct qdma_request));

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sg = sgl;
	wrbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!wrbuf) {
		pr_err("allocation failed");
		return;
	}
	rdbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!rdbuf) {
		pr_err("allocation failed");
		return;
	}

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 4; /* param */
		total_queues += 4;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 4;

		_qdev->qdma_dev_conf.qdma_drv_mode = DIRECT_INTR_MODE;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);

		/* ST H2C */
		memset(&qconf, 0, sizeof(struct qdma_queue_conf));
		qconf.qidx = 3;
		qconf.st = 1;
		qconf.q_type = 0;
		qconf.desc_rng_sz_idx = 4;
		qconf.irq_en = 1;
		qconf.wb_status_en = 1;

		qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		qdma_queue_config(dev_hndl, qhndl, &qconf, buf, sizeof(buf));
		qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		sgl = sg;
		for(i = 0; i < sgcnt; i++,sgl++) {
			wrbuf[i].dmabuf = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					&wrbuf[i].phys_addr, GFP_KERNEL);

			nbytes = min_t(unsigned int, PAGE_SIZE, len);

			/* fill in the buffers with data */
			for(j = 0; j < nbytes; j++) {
				memset((wrbuf[i].dmabuf + j), j, 1);
			}

			if (i == sgcnt - 1)
				sgl->next = NULL;
			else
				sgl->next = sgl + 1;

			sgl->pg = virt_to_page(wrbuf[i].dmabuf);
			sgl->dma_addr = wrbuf[i].phys_addr;
			sgl->len = nbytes;
			sgl->offset = 0;

			len -= nbytes;
		}

		prepare_qdma_request(sg, &req, sgcnt, len_arr[_i], 1);

		len = len_arr[_i];
		j = 0;
		for(i = 0; i < sgcnt; i++) {
			nbytes = min_t(unsigned int, PAGE_SIZE, len);
			for(; j < (nbytes + (i*PAGE_SIZE)); j++) {
				memset((wrbuf[i].dmabuf + j), j, 1);
			}
			len -= nbytes;
			j += nbytes;
		}

		rlen = qdma_queue_packet_write(dev_hndl, qhndl, &req);

		map_len = pci_resource_len(pdev, 2);
		user_bar_regs = pci_iomap(pdev, 2, map_len);

		EXPECT_INT_EQ(readl(user_bar_regs + 0x10), 0x30);

		invld_dev_hndl = dev_hndl + 10;
		rv = qdma_queue_packet_write(invld_dev_hndl, qhndl, &req);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		invld_qhndl = qhndl + 10;
		rv = qdma_queue_packet_write(dev_hndl, invld_qhndl, &req);
		ASSERT_TRUE_GOTO(rv == -EINVAL, done);

		qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		/* CLEANUP */
		for(i = 0; i < sgcnt; i++) {
			dma_free_coherent(&pdev->dev, PAGE_SIZE, wrbuf[i].dmabuf,
					wrbuf[i].phys_addr);
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();

		goto exit_func; /* run only once */
	}
exit_func:
	return;
done:
	qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));
	qdma_device_offline(pdev, dev_hndl, 1);
	qdma_device_close(pdev, dev_hndl);
}

TEST(qdma_test, api42_qdma_queue_packet_read)
{
	struct qdma_test_priv *_qdev, *tmp;
	int rv = 0;
	struct pci_dev *pdev;
	unsigned int sgcnt;
	unsigned long len;
	struct qdma_request req;
	struct qdma_sw_sg *sgl, *sg;
	struct dma_addr *wrbuf, *rdbuf;
	struct qdma_queue_conf qconf;
	unsigned long dev_hndl, qhndl;
	char buf[3000];
	unsigned int nbytes;
	int total_queues = 0;
	unsigned long i = 0;
	unsigned long length = 64;
	int map_len;
	void __iomem *user_bar_regs;

	len = length;
	sgcnt = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;

	memset(&req, 0, sizeof(struct qdma_request));

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sgl = kzalloc(sgcnt * (sizeof(struct qdma_sw_sg) +
			sizeof(struct page *)), GFP_KERNEL);
	if (!sgl) {
		pr_err("sgl allocation failed for %u pages", sgcnt);
		return;
	}

	sg = sgl;
	wrbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!wrbuf) {
		pr_err("allocation failed");
		return;
	}
	rdbuf = kmalloc(sgcnt * sizeof(struct dma_addr), GFP_KERNEL);
	if (!rdbuf) {
		pr_err("allocation failed");
		return;
	}

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {

		/* Opening the device */
		qdev_set_default(&_qdev->qdma_dev_conf);
		pdev = _qdev->qdma_dev_conf.pdev = _qdev->pcidev;

		if (i == 0)
			_qdev->qdma_dev_conf.master_pf = 1;
		i++;

		if (_qdev->qdma_dev_conf.master_pf == 1) {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 5;
		} else {
			_qdev->qdma_dev_conf.data_msix_qvec_max = 6;
		}
		_qdev->qdma_dev_conf.qsets_max = 5; /* param */
		total_queues += 5;
		_qdev->qdma_dev_conf.qsets_base = total_queues - 5;

		_qdev->qdma_dev_conf.qdma_drv_mode = DIRECT_INTR_MODE;

		rv = libqdma_init(0, NULL);
		rv = qdma_device_open(DRV_MODULE_NAME, &_qdev->qdma_dev_conf, &dev_hndl);
		rv = qdma_device_online(_qdev->qdma_dev_conf.pdev, dev_hndl, 1);

		/* MM C2H */
		memset(&qconf, 0, sizeof(struct qdma_queue_conf));
		qconf.qidx = 4;
		qconf.st = 1;
		qconf.q_type = 1;
		qconf.desc_rng_sz_idx = 4;
		qconf.irq_en = 1;
		qconf.wb_status_en = 1;
		qconf.cmpl_desc_sz = DESC_SZ_8B;
		qconf.cmpl_trig_mode = TRIG_MODE_ANY;
		qconf.cmpl_rng_sz_idx = 4;
		qconf.c2h_buf_sz_idx = 0;
		qconf.cmpl_timer_idx = 9;
		qconf.cmpl_cnt_th_idx = 0;
		qconf.fetch_credit = 1;
		qconf.cmpl_stat_en = 1;
		qconf.cmpl_en_intr = 1;

		len = length;
		qdma_queue_add(dev_hndl, &qconf, &qhndl, buf, sizeof(buf));
		qdma_queue_config(dev_hndl, qhndl, &qconf, buf, sizeof(buf));
		qdma_queue_start(dev_hndl, qhndl, buf, sizeof(buf));

		sgl = sg;
		for(i = 0; i < sgcnt; i++,sgl++) {
			rdbuf[i].dmabuf = dma_alloc_coherent(&pdev->dev, PAGE_SIZE,
					&rdbuf[i].phys_addr, GFP_KERNEL);

			nbytes = min_t(unsigned int, PAGE_SIZE, len);

			if (i == sgcnt - 1)
				sgl->next = NULL;
			else
				sgl->next = sgl + 1;

			sgl->pg = virt_to_page(rdbuf[i].dmabuf);
			sgl->dma_addr = rdbuf[i].phys_addr;
			sgl->len = nbytes;
			sgl->offset = 0;

			len -= nbytes;
		}

		prepare_qdma_request(sg, &req, sgcnt, length, 0);

		map_len = pci_resource_len(pdev, 2);
		user_bar_regs = pci_iomap(pdev, 2, map_len);

		writel(4, (user_bar_regs + 0x0));
		/* Write transfer size to offset 0x04 */
		writel(length, (user_bar_regs + 0x4));
		/* Write number of packets to offset 0x20 */
		writel(1, (user_bar_regs + 0x20));
		/* Write to offset 0x80 bit [1] to trigger C2H data generator */
		writel(2, (user_bar_regs + 0x8));

		rv = qdma_queue_packet_read(dev_hndl, qhndl, &req, NULL);
		EXPECT_INT_EQ(rv, length);

		qdma_queue_stop(dev_hndl, qhndl, buf, sizeof(buf));
		qdma_queue_remove(dev_hndl, qhndl, buf, sizeof(buf));

		/* CLEANUP */
		for(i = 0; i < sgcnt; i++) {
			dma_free_coherent(&pdev->dev, PAGE_SIZE, rdbuf[i].dmabuf,
					rdbuf[i].phys_addr);
		}

		qdma_device_offline(pdev, dev_hndl, 1);
		qdma_device_close(pdev, dev_hndl);
		libqdma_exit();

		goto exit_func; /* run only once */
	}
exit_func:
	return;
}

static void add_tests(void)
{
	ADD_TEST(api001_libqdma_init_num_threads);
	ADD_TEST(api002_libqdma_init_debugfs);
	ADD_LOOP_TEST(api003_qdma_device_open_drv_mode, 0, 4);
	//ADD_TEST(api004_qdma_device_open_pdev);
	ADD_LOOP_TEST(api005_qdma_device_open_qsets_max, 0, 5);
	ADD_LOOP_TEST(api006_qdma_device_open_cnfg_bar, 0, 3);
	ADD_TEST(api007_qdma_device_online_pdev);
	ADD_TEST(api008_qdma_device_online_dev_hndl);
	ADD_TEST(api009_qdma_flr_set_pdev);
	ADD_TEST(api010_qdma_flr_set_dev_hndl);
	ADD_TEST(api011_qdma_flr_check_pdev);
	ADD_TEST(api012_qdma_flr_check_dev_hndl);
	ADD_TEST(api013_qdma_config_register_rdwr);
	ADD_TEST(api014_qdma_device_capabilities);
	ADD_TEST(api015_qdma_device_version);
	ADD_TEST(api016_qdma_sw_version);
	ADD_TEST(api017_qdma_csr_get);
	ADD_LOOP_TEST(api018_qdma_csr_get_index, 1, 3);
	ADD_LOOP_TEST(api019_qdma_csr_get_count, 17, 19);
	ADD_TEST(api020_qdma_get_config);
	ADD_LOOP_TEST(api021_qdma_q_add, 0, 4);
	ADD_LOOP_TEST(api022_qdma_q_add_st_c2h_trig_mode, TRIG_MODE_DISABLE, TRIG_MODE_COMBO+2);
	ADD_TEST(api023_qdma_q_add_invalid_qidx);
	ADD_TEST(api024_qdma_q_add_invalid_devhndl);
	ADD_LOOP_TEST(api025_qdma_q_start, 0, 2);
	ADD_LOOP_TEST(api026_qdma_q_state, 0, 2);
	ADD_LOOP_TEST(api027_qdma_q_get_config, 0, 2);
	ADD_LOOP_TEST(api028_qdma_q_list_1, 0, 2);
	ADD_LOOP_TEST(api029_qdma_q_list_2, 0, 2);
	ADD_TEST(api030_qdma_q_list_invalid_params);
	ADD_LOOP_TEST(api031_qdma_q_dump, 0, 2);
	ADD_TEST(api032_qdma_q_dump_invalid_params);
	ADD_LOOP_TEST(api033_qdma_q_dump_desc, 0, 2);
	ADD_TEST(api034_qdma_q_dump_desc_invalid_params);
	ADD_TEST(api035_qdma_q_dump_cmpt);
	ADD_LOOP_TEST(api37_mm_transfer, 0, 4);
	ADD_LOOP_TEST(api38_st_h2c_transfer, 0, 4);
	ADD_TEST(api39_st_c2h_transfer);
	ADD_TEST(api40_qdma_request_submit_invld_params);
	ADD_LOOP_TEST(api41_qdma_queue_packet_write, 0, 4);
	ADD_TEST(api42_qdma_queue_packet_read);
}

static int probe_one(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct qdma_test_priv *qdev = kzalloc(sizeof(struct qdma_test_priv),
			GFP_KERNEL);
	if (!qdev) {
		terr("Failed to allocate memory for qdev");
		return -ENOMEM;
	}

	qdev->device_id = pdev->device;
	qdev->pcidev = pdev;

	list_add_tail(&qdev->list_head, &dev_list);

	tlog(T_INFO, "probe successful for the PCIE function with deviceid 0x%x"
			" and pdev 0x%p ", qdev->device_id, qdev->pcidev);

	return 0;
}

static void remove_one(struct pci_dev *pdev)
{
	struct qdma_test_priv *_qdev, *tmp;

	list_for_each_entry_safe(_qdev, tmp, &dev_list, list_head) {
		list_del(&_qdev->list_head);
		kfree(_qdev);
	}
}

static struct pci_driver pci_driver = {
	.name = DRV_NAME,
	.id_table = pci_ids,
	.probe = probe_one,
	.remove = remove_one,
};

/* This is the entry point of the qdma_test driver.
 * This function will get called on insert of the driver into the kernel
 */
static int __init libqdmatest_init(void)
{
	int err = 0;

	err = pci_register_driver(&pci_driver);
	if (err < 0)
		terr("qdma_test: PCI registration failed with err=%d\n", err);

	add_tests();
	tlog(T_INFO, "libqdmatest: loaded");

	return 0;
}

static void __exit libqdmatest_exit(void)
{
	pci_unregister_driver(&pci_driver);
	KTF_CLEANUP();
	tlog(T_INFO, "libqdmatest: unloaded");
}

module_init(libqdmatest_init);
module_exit(libqdmatest_exit);
