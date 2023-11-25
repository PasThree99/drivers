# Main Makefile

SUBDIRS := 1_BasicDriver 2_registerModule 3_basicOperations 4_randNumber 5_persistentSave

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)

	$(SUBDIRS):
		$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
    	$(MAKE) -C $$dir clean; \
	done