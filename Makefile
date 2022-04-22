SH := /bin/sh
ECHO := @/bin/echo -n
CD := cd
RSYNC := rsync -parv
MKDIR := mkdir -p
RM := rm -rfv
LSH := ls -larth
CP := @cp -rv
MV := @mv -v
CAT := `which cat`
SED := `which sed`
LS := ls -l@k

DEBUGFLAGS =
#DEBUGFLAGS = --list --c-code-in-asm
CRT=-startup=1 -clib=new

CC=zcc
CCFLAGS=+zxn -vn -O2 -clib=new
CZFLAGS=-Cz="--clean --fullsize --main-fence 0xBFE0"
LDFLAGS=-m -lm
INCFLAGS=-Iinc
BUILD_DIR = build

NAME = trammath

.PHONY: clean $(NAME)

default: all

all: $(NAME)

INSTALL_DIR = /Volumes/devnext.xalior.com

dist_clean: clean
	rm -f $(BUILD_DIR)/*
clean:
	rm -f **/*.o **/**/*.o *~ $(NAME)_*.bin *.map* **/*.lis *.lis

build/%.o: %.c inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
			$< -c -o$@

bin/%.o: lib/%.asm inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
			$< -c -o$@



bank43_banner:
	# ____              _    _  _  _____        #
	#| __ )  __ _ _ __ | | _| || ||___ /        #
	#|  _ \ / _` | '_ \| |/ / || |_ |_ \        #
	#| |_) | (_| | | | |   <|__   _|__) |       #
	#|____/ \__,_|_| |_|_|\_\  |_||____/        #
	#                                           # LOGIC
bank43/build/%.o: bank43/%.c bank43/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_43 --constsegBANK_43 --datasegBANK_43 --bsssegBANK_43 \
			$< -c -o$@

bank43/bin/%.o: bank43/%.asm bank43/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_43 --constsegBANK_43 --datasegBANK_43 --bsssegBANK_43 \
		 	$< -c -o$@

$(NAME)_bank_43_OBJS := \
	bank43/build/log.o \
	bank43/build/logic.o

banks/$(NAME)bank_43.o: bank43_banner $($(NAME)_bank_43_OBJS)
	$(CC) $(CCFLAGS) $(CRT) -c $(DEBUG) $(INCFLAGS) $(BUILDFLAGS) $(DEBUGFLAGS)\
		--codesegBANK_43 --constsegBANK_43 --datasegBANK_43 --bsssegBANK_43 \
			null.c $($(NAME)_bank_43_OBJS) -obanks/$(NAME)bank_43.o




bank44_banner:
	# ____              _      _  _   _  _   	#
	#| __ )  __ _ _ __ | | __ | || | | || |  	#
	#|  _ \ / _` | '_ \| |/ / | || |_| || |_ 	#
	#| |_) | (_| | | | |   <  |__   _|__   _|	#
	#|____/ \__,_|_| |_|_|\_\    |_|    |_|  	#
	#                                           # DIVIDE

bank44/build/%.o: bank44/%.c bank44/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_44 --constsegBANK_44 --datasegBANK_44 --bsssegBANK_44 \
			$< -c -o$@

bank44/bin/%.o: bank44/%.asm bank44/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_44 --constsegBANK_44 --datasegBANK_44 --bsssegBANK_44 \
		 	$< -c -o$@

$(NAME)_bank_44_OBJS := \
	bank44/build/div_two.o

banks/$(NAME)bank_44.o: bank44_banner $($(NAME)_bank_44_OBJS)
	$(CC) $(CCFLAGS) $(CRT) -c $(DEBUG) $(INCFLAGS) $(BUILDFLAGS) $(DEBUGFLAGS)\
		--codesegBANK_44 --constsegBANK_44 --datasegBANK_44 --bsssegBANK_44 \
			null.c $($(NAME)_bank_44_OBJS) -obanks/$(NAME)bank_44.o



bank45_banner:
	#  ____              _      _  _  ____  	#
	#| __ )  __ _ _ __ | | __ | || || ___|  	#
	#|  _ \ / _` | '_ \| |/ / | || ||___ \  	#
	#| |_) | (_| | | | |   <  |__   _|__) | 	#
	#|____/ \__,_|_| |_|_|\_\    |_||____/  	#
	#                                           # MULTIPLY

bank45/build/%.o: bank45/%.c bank45/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_45 --constsegBANK_45 --datasegBANK_45 --bsssegBANK_45 \
			$< -c -o$@

bank45/bin/%.o: bank45/%.asm bank45/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_45 --constsegBANK_45 --datasegBANK_45 --bsssegBANK_45 \
		 	$< -c -o$@

$(NAME)_bank_45_OBJS := \
	bank45/build/mul8bit.o

banks/$(NAME)bank_45.o: bank45_banner $($(NAME)_bank_45_OBJS)
	$(CC) $(CCFLAGS) $(CRT) -c $(DEBUG) $(INCFLAGS) $(BUILDFLAGS) $(DEBUGFLAGS)\
		--codesegBANK_45 --constsegBANK_45 --datasegBANK_45 --bsssegBANK_45 \
			null.c $($(NAME)_bank_45_OBJS) -obanks/$(NAME)bank_45.o



bank46_banner:
	#  ____              _      _  _    __    	#
	# | __ )  __ _ _ __ | | __ | || |  / /_   	#
	# |  _ \ / _` | '_ \| |/ / | || |_| '_ \  	#
	# | |_) | (_| | | | |   <  |__   _| (_) | 	#
	# |____/ \__,_|_| |_|_|\_\    |_|  \___/  	#
	#                                           # SUBTRACT

bank46/build/%.o: bank46/%.c bank46/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_46 --constsegBANK_46 --datasegBANK_46 --bsssegBANK_46 \
			$< -c -o$@

bank46/bin/%.o: bank46/%.asm bank46/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_46 --constsegBANK_46 --datasegBANK_46 --bsssegBANK_46 \
		 	$< -c -o$@

$(NAME)_bank_46_OBJS := \
	bank46/build/sub.o

banks/$(NAME)bank_46.o: bank46_banner $($(NAME)_bank_46_OBJS)
	$(CC) $(CCFLAGS) $(CRT) -c $(DEBUG) $(INCFLAGS) $(BUILDFLAGS) $(DEBUGFLAGS)\
		--codesegBANK_46 --constsegBANK_46 --datasegBANK_46 --bsssegBANK_46 \
			null.c $($(NAME)_bank_46_OBJS) -obanks/$(NAME)bank_46.o



bank47_banner:
	# ____              _      _  _ _____  	    #
	#| __ )  __ _ _ __ | | __ | || |___  | 	    #
	#|  _ \ / _` | '_ \| |/ / | || |_ / /  	    #
	#| |_) | (_| | | | |   <  |__   _/ /   	    #
	#|____/ \__,_|_| |_|_|\_\    |_|/_/    	    #
	#                                           # ADD

bank47/build/%.o: bank47/%.c bank47/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_47 --constsegBANK_47 --datasegBANK_47 --bsssegBANK_47 \
			$< -c -o$@


bank47/bin/%.o: bank47/%.asm bank47/inc/%.h
	$(CC) $(CCFLAGS) $(CRT) $(LDFLAGS) $(INCFLAGS) \
		--codesegBANK_47 --constsegBANK_47 --datasegBANK_47 --bsssegBANK_47 \
			$< -c -o$@

$(NAME)_bank_47_OBJS := \
	bank47/build/add_one.o

banks/$(NAME)bank_47.o: bank47_banner $($(NAME)_bank_47_OBJS)
	$(CC) $(CCFLAGS) $(CRT) -c $(DEBUG) $(INCFLAGS) $(BUILDFLAGS) $(DEBUGFLAGS)\
		--codesegBANK_47 --constsegBANK_47 --datasegBANK_47 --bsssegBANK_47 \
			null.c $($(NAME)_bank_47_OBJS) -obanks/$(NAME)bank_47.o



main_banner:
	#  __  __       _        	                    #
	# |  \/  | __ _(_)_ __   	                    #
	# | |\/| |/ _` | | '_ \  	                    #
	# | |  | | (_| | | | | | 	                    #
	# |_|  |_|\__,_|_|_| |_| 	                    #
	#                                           # TRAMPOLINE_EXAMPLE

$(NAME)_OBJS := \
	banks/$(NAME)bank_43.o \
	banks/$(NAME)bank_44.o \
	banks/$(NAME)bank_45.o \
	banks/$(NAME)bank_46.o \
	banks/$(NAME)bank_47.o

dotn: $($(NAME)_OBJS) main_banner
	$(CC) $(CCFLAGS) $(CRT) -startup=1 $(LDFLAGS) $(INCFLAGS)  $(DEBUGFLAGS) \
		$(NAME).c execfar.c $($(NAME)_OBJS) $($(NAME)_BANKS) -pragma-include:zpragma.inc \
			-o$(NAME) -create-app -subtype=dotn $(CZFLAGS) -Ddotn # same as "#define dotn"
	@$(ECHO) "Bank 4 & 5, allocate and load, "
	@$(ECHO) `expr 16656 - \`/bin/ls -l@k $(NAME)_CODE.bin | awk '{print $$5}'\``
	@$(ECHO) " tail bytes free" && echo
	$(MV) $(NAME) $(BUILD_DIR)/

nex: $($(NAME)_OBJS) main_banner
	$(CC) $(CCFLAGS) $(CRT) -startup=1 $(LDFLAGS) $(INCFLAGS)  $(DEBUGFLAGS) \
		$(NAME).c execfar.c $($(NAME)_OBJS) $($(NAME)_BANKS) -pragma-include:zpragma.inc \
			-o$(NAME) -create-app -subtype=nex $(CZFLAGS)
	@$(ECHO) "Bank 4 & 5, allocate and load, "
	@$(ECHO) `expr 16656 - \`/bin/ls -l@k $(NAME)_CODE.bin | awk '{print $$5}'\``
	@$(ECHO) " tail bytes free" && echo
	$(MV) $(NAME).nex $(BUILD_DIR)/

$(NAME): dotn nex

install:
	$(CP) $(BUILD_DIR)/$(NAME).nex $(INSTALL_DIR)/TestFiles
	$(CP) $(BUILD_DIR)/$(NAME) $(INSTALL_DIR)/dot
