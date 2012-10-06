
all: list data entry

list: list.c data.c entry.c test_list.c
	gcc -w list.c data.c entry.c test_list.c -o list

data: data.c test_data.c
	gcc -w data.c test_data.c -o data

entry: data.c entry.c test_entry.c
	gcc -w data.c entry.c test_entry.c -o entry

clean:
	@rm -f list data entry
