NAME = ShaderPixel
SRC = srcs/Camera.cpp srcs/Cube.cpp srcs/RenderObject.cpp \
srcs/Shader.cpp srcs/ShaderFrame.cpp srcs/ShaderPanel.cpp srcs/Window.cpp \
srcs/input.cpp srcs/main.cpp srcs/panel.cpp srcs/PostProcess.cpp
OBJ = $(SRC:.cpp=.o)
FRAMEWORKS = -framework OpenGl -w
BREW_INC = -I ~/.brew/include
STB_INC = -I ./stb
GLFW_LINK = -L ~/.brew/lib -lglfw

RED = "\033[1;38;2;225;20;20m"
ORANGE = "\033[1;38;2;255;120;10m"
YELLO = "\033[1;38;2;255;200;0m"
GREEN = "\033[1;38;2;0;170;101m"
LG = "\033[1;38;2;167;244;66m"
BLUE = "\033[1;38;2;50;150;250m"
PURPLE = "\033[1;38;2;150;75;255m"
WHITE = "\033[1;38;2;255;250;232m"

all: install $(NAME)

install:
ifneq ("$(shell test -e $(HOME)/.brew && echo ex)" , "ex")
	@echo "BREW INSTALLING ..."
	@curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	@echo $(YELLO)INSTALLING glfw: please be patient
endif
	@echo $(WHITE)Checking for graphics library ...
ifneq ("$(wildcard ~/.brew/include/GLFW/glfw3.h)","")
	@echo $(GREEN)"Already installed!"
else
	@brew install glfw
endif
	@echo $(WHITE)Checking for stb_image ...
ifneq ("$(wildcard ./stb/stb_image.h)","")
	@echo $(GREEN)"Already installed!"
else
	@echo $(YELLO)Downloading stb_image ...
	git clone https://github.com/nothings/stb.git stb
endif

$(NAME): $(SRC)
	@echo $(YELLO)Making $(NAME)
	@g++ -std=c++11 $(SRC) -o $(NAME) $(FRAMEWORKS) $(BREW_INC) $(STB_INC) $(GLFW_LINK)
	@echo $(GREEN)Done!

clean:
	@echo $(YELLO)Cleaning o files
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo $(YELLO)Removing excutable
	@rm -f $(NAME)

re:	fclean all
