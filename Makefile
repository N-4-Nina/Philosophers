# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 10:45:13 by chpl              #+#    #+#              #
#    Updated: 2021/11/02 13:16:33 by abouchau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#The Target Binary Program
TARGET      := philo
LINK		:= link
#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := srcs
INCDIR      := include
BUILDDIR    := objs
TARGETDIR   := .
SRCEXT      := c
DEPEXT      := d
OBJEXT      := o
LIBS = -lpthread
CFLAGS	:= -Wall -Wextra -Werror
CC := clang
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


#Default Make
all: directories $(TARGET)

#Remake
re: fclean all
#Clean only Objecst
clean:
	@$(RM) -rf $(BUILDDIR)
#Full Clean, Objects and Binaries
fclean: clean
	@$(RM) -rf $(TARGETDIR)/$(TARGET)
#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))
#Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIBS)

#Make the Directories
directories:
	@mkdir -p $(BUILDDIR)
#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -g -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp
	
#Non-File Targets
.PHONY: all remake clean cleaner resources

