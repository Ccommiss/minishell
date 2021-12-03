
i=1
while [ $i -le 1500 ]
do
    echo "ls |" >> infile
    i=$(($i+1))
done

tr -d '\n' < infile > outfile
