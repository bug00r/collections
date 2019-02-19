all:
	$(MAKE) -C array
	$(MAKE) -C linked_list
	#$(MAKE) -C tree

.PHONY: clean
clean:
	$(MAKE) -C array clean
	$(MAKE) -C linked_list clean
	#$(MAKE) -C tree clean
