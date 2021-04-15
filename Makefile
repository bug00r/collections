all:
	$(MAKE) -C array
	$(MAKE) -C linked_list
	$(MAKE) -C dl_list
	#$(MAKE) -C tree

.PHONY: clean install
clean:
	$(MAKE) -C array clean
	$(MAKE) -C linked_list clean
	$(MAKE) -C dl_list clean
	#$(MAKE) -C tree clean

install:
	$(MAKE) -C array install
	$(MAKE) -C linked_list install
	$(MAKE) -C dl_list install
	#$(MAKE) -C tree clean
