TARGET = Proteus

GITBINARY := git
FEHURL := google.com
FIRMWAREREPO := fehproteusfirmware

ifeq ($(OS),Windows_NT)	
	SHELL := CMD
endif

all:
ifeq ($(OS),Windows_NT)	
# check for internet connection
# if there's internet, check to see if FEHproteusfirmware folder exists
# if it does, remove it before cloning the repo
	@ping -n 1 -w 1000 $(FEHURL) > NUL & \
	if errorlevel 1 \
	( \
		( echo "Warning: No internet connection!" ) \
	) \
	else \
	( \
		( if exist "$(FIRMWAREREPO)" \
		( \
			cd $(FIRMWAREREPO) && \
			$(GITBINARY) stash && \
			$(GITBINARY) pull && \
			cd .. \
		) \
		else \
		( \
			$(GITBINARY) config --global http.sslVerify false  && \
			$(GITBINARY) clone https://code.osu.edu/fehelectronics/proteus_software/$(FIRMWAREREPO).git \
		) \
		) \
	) 
else
# Mac/Linux
	@ping -c 1 -W 1000 $(FEHURL) > NUL ; \
	if [ "$$?" -ne 0 ]; then \
		echo "Warning: No internet connection!"; \
	else \
		if [ -d "$(FIRMWAREREPO)" ]; then \
			cd $(FIRMWAREREPO) ; \
			$(GITBINARY) stash ; \
       		$(GITBINARY) pull ; \
       		cd .. ; \
		else \
       		$(GITBINARY) clone https://code.osu.edu/fehelectronics/proteus_software/$(FIRMWAREREPO).git ; \
		fi \
	fi \

endif

ifeq ($(OS),Windows_NT)	
	@cd $(FIRMWAREREPO) && mingw32-make all TARGET=$(TARGET)
	@cd $(FIRMWAREREPO) && mingw32-make deploy TARGET=$(TARGET)
else
	@cd $(FIRMWAREREPO) && make all TARGET=$(TARGET)
	@cd $(FIRMWAREREPO) && make deploy TARGET=$(TARGET)
endif

deploy:
ifeq ($(OS),Windows_NT)	
	@cd $(FIRMWAREREPO) && mingw32-make deploy TARGET=$(TARGET)
else
	@cd $(FIRMWAREREPO) && make deploy TARGET=$(TARGET)
endif

clean:
ifeq ($(OS),Windows_NT)	
	@cd $(FIRMWAREREPO) && mingw32-make clean TARGET=$(TARGET)
else
	@cd $(FIRMWAREREPO) && make clean TARGET=$(TARGET)
endif

run:
ifeq ($(OS),Windows_NT)	
	@cd $(FIRMWAREREPO) && mingw32-make run TARGET=$(TARGET)
else
	@cd $(FIRMWAREREPO) && make run TARGET=$(TARGET)
endif