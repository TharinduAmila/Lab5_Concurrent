time=0
average=0
sample_size=0
sample_size=$1  #first parameter
avg[0]=0
filename="./Lab5_concurrent.cpp"
g++ -fopenmp $filename

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
        time=$(./a.out $temp)
        echo -e "$i\t:  $time" 
        avg[$index]=$(echo "${avg[$index]} + $time" | bc)
done
done

for j in {0..9..1};
do 
avg[$j]=$(echo "scale=10; ${avg[$j]} / $sample_size" | bc)
let c=($j+1)*100
print=$(echo "if(${avg[$j]}<1) print 0; ${avg[$j]}"| bc)
echo -e "average time for case $c \t:$print"
done
