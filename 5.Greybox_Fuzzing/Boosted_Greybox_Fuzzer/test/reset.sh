# !bin/bash

mv ./input/cjson_inp/input1 ./input/cjson_inp/temp1
mv ./input/cjson_inp/input2 ./input/cjson_inp/temp2
mv ./input/cjson_inp/input3 ./input/cjson_inp/temp3

rm ./input/cjson_inp/input*

mv ./input/cjson_inp/temp1 ./input/cjson_inp/input1
mv ./input/cjson_inp/temp2 ./input/cjson_inp/input2
mv ./input/cjson_inp/temp3 ./input/cjson_inp/input3
