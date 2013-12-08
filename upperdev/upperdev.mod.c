#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xaf605240, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x3721d9cc, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0xf7452e85, __VMLINUX_SYMBOL_STR(softdev_ioctl) },
	{ 0xb8397675, __VMLINUX_SYMBOL_STR(softdev_send) },
	{ 0x362ef408, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2f287f0d, __VMLINUX_SYMBOL_STR(copy_to_user) },
	{ 0xddc3a3d9, __VMLINUX_SYMBOL_STR(softdev_recv) },
	{ 0x1f4fc7bb, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x48fe8c6a, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=softdev";


MODULE_INFO(srcversion, "4A65BA7B68F916BDE7C9995");
