cc=g++
LDFLAGS += -lpthread -lleveldb
exe=main
obj=test_levedb.o

$(exe):$(obj)
	$(cc) -o $(exe) $(obj) $(LDFLAGS)

ulucu_cloud_test.o:test_levedb.cpp
	$(cc) -c test_levedb.cpp

clean:
	rm -rf *.o main
