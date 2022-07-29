mount -t hugetlbfs nodev /mnt/huge

systemctl stop irqbalance
iptables -F
ip6tables -F


echo 10 > /proc/sys/vm/stat_interval
echo 0 > /proc/sys/kernel/watchdog_thresh

host_isolcpus=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32

# Disable watchdogs to reduce overhead
echo 0 > /proc/sys/kernel/watchdog
echo 0 > /proc/sys/kernel/nmi_watchdog

#perf governor
for CPUFREQ in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do [ -f $CPUFREQ ] || continue; echo -n performance > $CPUFREQ; done
service cpuspeed stop

echo -1 > /proc/sys/kernel/sched_rt_period_us
echo -1 > /proc/sys/kernel/sched_rt_runtime_us

sysctl -w vm.zone_reclaim_mode=0
sysctl -w vm.swappiness=0

echo Change RT priority on isolcpus
#Change RT priority of ksoftirqd and rcuc kernel threads on isolated CPUs
i=0
for c in `echo $host_isolcpus | sed 's/,/ /g'` ; do
tid=`pgrep -a ksoftirq | grep "ksoftirqd/${c}$" | cut -d ' ' -f1`
chrt -fp 2 ${tid}
tid=`pgrep -a rcuc | grep "rcuc/${c}$" | cut -d ' ' -f1`
chrt -fp 3 ${tid}
cpu[$i]=${c}
i=`expr $i + 1`
done

echo Change RT priority of rcub
# Change RT priority of rcub kernel threads
for tid in `pgrep -a rcub | cut -d ' ' -f 1` ; do
chrt -fp 3 ${tid}
done

echo no irqs to isolcpus
# no interrupt will routed to the isolated CPUs
for irq in /proc/irq/* ; do
echo irq $irq
if [ -d ${irq} ] && ! grep - ${irq}/smp_affinity_list >/dev/null ; then
al=`cat ${irq}/smp_affinity_list`
echo al $al
if [[ ${cpu[*]} =~ ${al} ]] ; then
echo 0 > ${irq}/smp_affinity_list
printf ${irq}
printf "\n"
fi
fi
done

