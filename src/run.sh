time=0 
average=0
sample_size=0
sample_size=$2
parallel_true=$1
avg[0]=0
filename="./Lab5_concurrent.cpp"
g++ -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"./Lab5_concurrent.d" -MT"./Lab5_concurrent.d" -o "./Lab5_concurrent.o" $filename
g++ -fopenmp -o "Lab5_concurrent"  ./Lab5_concurrent.o 
#g++ -fopenmp $filename

echo "Bash version ${BASH_VERSION}..."

for i in {0..9..1}
do
avg[$i]=0
done

for j in $(eval echo {1..$sample_size..1});
do 
echo "Loop $j started"
for i in {100..1000..100}; 
do
	temp=$i
	let index=$i/100-1
        time=$(./Lab5_concurrent $parallel_true $temp)
        echo -e "$i\t:  $time" 
        avg[$index]=$(echo "${avg[$index]} + $time" | bc)
	sleep 2
done
done

for j in {0..9..1};
do 
avg[$j]=$(echo "scale=10; ${avg[$j]} / $sample_size" | bc)
let c=($j+1)*100
print=$(echo "if(${avg[$j]}<1) print 0; ${avg[$j]}"| bc)
echo -e "average time for case $c \t:$print"
done
