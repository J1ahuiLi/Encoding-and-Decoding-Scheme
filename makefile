all: preprocess encode decode


preprocess: preprocess.o
	g++ preprocess.o -o preprocess

encode: encode.o insertion.o merge.o defns.h merge.h insertion.h
	g++ encode.o insertion.o merge.o -o encode

decode: decode.o insertion.o merge.o defns.h merge.h insertion.h
	g++ decode.o insertion.o merge.o -o decode

preprocess.o: preprocess.cpp defns.h
	g++ preprocess.cpp -c -o preprocess.o

encode.o: encode.cpp  defns.h merge.h insertion.h
	g++ encode.cpp -c -o encode.o

decode.o: decode.cpp  defns.h merge.h insertion.h
	g++ decode.cpp -c -o decode.o

insertion.o: insertion.cpp  defns.h merge.h insertion.h
	g++ insertion.cpp -c -o insertion.o

merge.o: merge.cpp  defns.h merge.h insertion.h
	g++ merge.cpp -c -o merge.o

clean:
	rm *.o preprocess encode decode -rf
