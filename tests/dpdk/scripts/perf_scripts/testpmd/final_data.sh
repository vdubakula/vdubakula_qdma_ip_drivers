n=$1
while [ $n -gt 0 ]
do
	for i  in `grep "MIN" test_lat$n.csv`
	do
		echo -n $i >> test.csv
	done
	echo "" >> test.csv
	let n=$n/2
done
	echo "" >> test.csv
n=$1
while [ $n -gt 0 ]
do
        for i  in `grep "Average" test_lat$n.csv`
        do
                echo -n $i >> test.csv
        done
	echo "" >> test.csv
	let n=$n/2
done
	echo "" >> test.csv
n=$1
while [ $n -gt 0 ]
do
        for i  in `grep "MAX" test_lat$n.csv`
        do
                echo -n $i >> test.csv
        done
	echo "" >> test.csv
	let n=$n/2
done
	echo "" >> test.csv
n=$1
while [ $n -gt 0 ]
do
        for i  in `grep "Packet" test_lat$n.csv`
        do
                echo -n $i >> test.csv
        done
	echo "" >> test.csv
	let n=$n/2
done
	echo "" >> test.csv

echo "Final data in result_testpmd.csv"
