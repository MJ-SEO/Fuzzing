# !bin/bash

start_time=$(date +%s)

for i in 1;
do
	./jtest
	mv ./input/cjson_inp/input1 ./input/cjson_inp/temp1
	rm ./input/cjson_inp/input*
	mv ./input/cjson_inp/temp1 ./input/cjson_inp/input1
done

end_time=$(date +%s)

echo "It takes $(($end_time-$start_time)) seconds to complete this task."
