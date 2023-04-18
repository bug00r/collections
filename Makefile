all:
	$(MAKE) -C array
	$(MAKE) -C linked_list
	$(MAKE) -C dl_list
	#$(MAKE) -C tree

.PHONY: clean install test
clean:
	$(MAKE) -C array clean
	$(MAKE) -C linked_list clean
	$(MAKE) -C dl_list clean
	#$(MAKE) -C tree clean

test:
	$(MAKE) -C array test
	$(MAKE) -C linked_list test
	$(MAKE) -C dl_list test
	#$(MAKE) -C tree test

install:
	$(MAKE) -C array install
	$(MAKE) -C linked_list install
	$(MAKE) -C dl_list install
	#$(MAKE) -C tree clean
