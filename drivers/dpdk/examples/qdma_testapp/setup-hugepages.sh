# $1 = number of huges pages to boot with.
# reboot the system after executing the this script

sed -i '/GRUB_CMDLINE_LINUX_DEFAULT/c\GRUB_CMDLINE_LINUX_DEFAULT="splash \
	quiet hugepagesz=1GB hugepages='$1' default_hugepagesz=1GB iommu=pt \
	intel_iommu=on pci=realloc "' /etc/default/grub

update-grub
update-grub2
