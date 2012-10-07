
all: list data entry

list: list.c data.c entry.c test_list.c
	gcc list.c data.c entry.c test_list.c -o list

entry: data.c entry.c test_entry.c
	gcc data.c entry.c test_entry.c -o entry

data: data.c test_data.c
	gcc data.c test_data.c -o data


clean:
	@rm -f list data entry
